/*
* Copyright (C) 2019 Tianjin KYLIN Information Technology Co., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, see <http://www.gnu.org/licenses/&gt;.
*
*/

#include "notification_plugin.h"
#include "appmsg.h"
#include "scrollareawidget.h"
#include "takeinboxtoolbutton.h"
#include "monitorthread.h"
#include <QSvgRenderer>



NotificationPlugin::NotificationPlugin()
{
    m_bShowTakeIn = false;
    m_pMainWidget = new QWidget;
    m_pMainWidget->setObjectName("NotificationCenter");

    //获取系统语言环境,加载语言翻译
    QLocale locale;
    if (locale.language() == QLocale::Chinese)
    {
        QTranslator *qtTranslator = new QTranslator(this);
        qtTranslator->load("/usr/share/ukui-sidebar-notification/language.qm");
        QApplication::installTranslator(qtTranslator);
    }

    //加载样式表
    QFile file(":/qss/notification_plugin.css");
    if (file.open(QFile::ReadOnly))
    {
        QString strQss = QLatin1String(file.readAll());
        file.close();
        m_pMainWidget->setStyleSheet(strQss);
    }

    //插件的总VBoxLayout布局器
    QVBoxLayout* pNotificationVBoxLayout = new QVBoxLayout;
    pNotificationVBoxLayout->setContentsMargins(10,21,0,0);
    pNotificationVBoxLayout->setSpacing(0);

    //装第一行通知中心的Widget
    QWidget* pWidget1= new QWidget;
    pWidget1->setObjectName("NotificationName");

    //第一行通知中心标题栏，左侧标题“通知中心”，右侧收纳按钮
    QHBoxLayout* pQHBoxLayout1 = new QHBoxLayout;
    pQHBoxLayout1->setContentsMargins(11,0,28,0);
    pQHBoxLayout1->setSpacing(0);

    QLabel* pLabel = new QLabel(QObject::tr("Notification center"));
    pLabel->setObjectName("notificationcentername");

    //收纳按钮
    m_pTakeInBoxToolButton = new TakeInBoxToolButton();
    m_pTakeInBoxToolButton->setObjectName("takein");
    connect(m_pTakeInBoxToolButton, SIGNAL(clicked()), this, SLOT(onShowTakeInMessage()));

    //QToolButton添加svg图片
    m_pSvgRender = new QSvgRenderer(pWidget1);
    m_pSvgRender->load(QString(":/images/box-24.svg"));
    m_pPixmap = new QPixmap(24, 24);

    m_pPixmap->fill(Qt::transparent);
    QPainter painter(m_pPixmap);
    m_pSvgRender->render(&painter);
    m_pTakeInBoxToolButton->setIcon(QIcon(*m_pPixmap));

    pQHBoxLayout1->addWidget(pLabel, 0, Qt::AlignLeft);
    pQHBoxLayout1->addWidget(m_pTakeInBoxToolButton, 0, Qt::AlignRight);
    pWidget1->setLayout(pQHBoxLayout1);
    pNotificationVBoxLayout->addWidget(pWidget1);

    //悬浮收纳数标签
    m_pTakeInCoutLabel = new QLabel(m_pMainWidget);
    m_pTakeInCoutLabel->setObjectName("takeincout");
    m_pTakeInCoutLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_pTakeInCoutLabel->setVisible(false);

    QSpacerItem* pVFixedSpacer = new QSpacerItem(10, 24, QSizePolicy::Fixed, QSizePolicy::Fixed);
    pNotificationVBoxLayout->addSpacerItem(pVFixedSpacer);

    //装第二行重要通知中的Widget
    QWidget* pWidget2= new QWidget;
    pWidget2->setFixedWidth(390);

    //第二行左侧标签“重要的信息”，右侧一个清空按钮，一个设置按钮
    QHBoxLayout* pQHBoxLayout2 = new QHBoxLayout;
    pQHBoxLayout2->setContentsMargins(12,0,10,8);

    m_pNotificationLabel = new QLabel(QObject::tr("Important notice"));
    m_pNotificationLabel->setObjectName("importantnotification");

    QSpacerItem* pHSpacer = new QSpacerItem(300, 10, QSizePolicy::Expanding, QSizePolicy::Fixed);

    QPushButton* pClearAllToolButton = new QPushButton();
    pClearAllToolButton->setObjectName("clearall");
    connect(pClearAllToolButton, SIGNAL(clicked()), this, SLOT(onClearAllMessage()));
    pClearAllToolButton->setText(QObject::tr("Clean up"));

    QSpacerItem* pFixSpacer = new QSpacerItem(5, 10, QSizePolicy::Fixed, QSizePolicy::Fixed);

    QPushButton* pSettingToolButton = new QPushButton();
    pSettingToolButton->setObjectName("setting");
    connect(pSettingToolButton, SIGNAL(clicked()), this, SLOT(onCallControlPanel()));
    pSettingToolButton->setText(QObject::tr("Set up"));


    pQHBoxLayout2->addWidget(m_pNotificationLabel, 0, Qt::AlignLeft);
    pQHBoxLayout2->addSpacerItem(pHSpacer);
    pQHBoxLayout2->addWidget(pClearAllToolButton, 0, Qt::AlignRight);
    pQHBoxLayout2->addSpacerItem(pFixSpacer);
    pQHBoxLayout2->addWidget(pSettingToolButton, 0, Qt::AlignRight);
    pWidget2->setLayout(pQHBoxLayout2);
    pNotificationVBoxLayout->addWidget(pWidget2, 0);

    //通知列表
    m_pQScrollAreaNotify = new ScrollAreaWidget();
    m_pQScrollAreaNotify->setStyleSheet("QWidget{background:transparent;}");

    m_pScrollAreaNotifyVBoxLayout = new QVBoxLayout();
    m_pScrollAreaNotifyVBoxLayout->setContentsMargins(0,0,0,0);
    m_pScrollAreaNotifyVBoxLayout->setSpacing(0);

    //通知列表的最内层部件
    QWidget* pInQWidget = new QWidget();
    pInQWidget->setObjectName("QScrollAreaInQWidget");
    pInQWidget->setLayout(m_pScrollAreaNotifyVBoxLayout);
    m_pQScrollAreaNotify->setWidget(pInQWidget);

    m_pMessageCenterLabel = new QLabel(QObject::tr("No new notifications"));
    m_pMessageCenterLabel->setStyleSheet("QLabel{color:rgba(255,255,255,0.91);padding:119px 0px 0px 0px;font-size:14px;}");
    m_pScrollAreaNotifyVBoxLayout->addWidget(m_pMessageCenterLabel, 0, Qt::AlignHCenter);

    QSpacerItem* pVSpacer = new QSpacerItem(10, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_pScrollAreaNotifyVBoxLayout->addSpacerItem(pVSpacer);
    pNotificationVBoxLayout->addWidget(m_pQScrollAreaNotify, 0);

    //收纳列表
    m_pQScrollAreaTakeIn = new ScrollAreaWidget();
    m_pQScrollAreaTakeIn->setStyleSheet("QWidget{background:transparent;}");

    m_pScrollAreaTakeInVBoxLayout = new QVBoxLayout();
    m_pScrollAreaTakeInVBoxLayout->setContentsMargins(0,0,0,0);
    m_pScrollAreaTakeInVBoxLayout->setSpacing(0);

    //收纳列表的最内层部件
    QWidget* pTakeInQWidget = new QWidget();
    pTakeInQWidget->setObjectName("QScrollAreaInQWidget");
    pTakeInQWidget->setLayout(m_pScrollAreaTakeInVBoxLayout);
    m_pQScrollAreaTakeIn->setWidget(pTakeInQWidget);
    m_pQScrollAreaTakeIn->setVisible(false);

    m_pTakeinMessageCenterLabel = new QLabel(QObject::tr("No unimportant notice"));
    m_pTakeinMessageCenterLabel->setStyleSheet("QLabel{color:rgba(255,255,255,0.91);padding:119px 0px 0px 0px;font-size:14px;}");
    m_pScrollAreaTakeInVBoxLayout->addWidget(m_pTakeinMessageCenterLabel, 0, Qt::AlignHCenter);

    QSpacerItem* pVSpacer2 = new QSpacerItem(10, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_pScrollAreaTakeInVBoxLayout->addSpacerItem(pVSpacer2);
    pNotificationVBoxLayout->addWidget(m_pQScrollAreaTakeIn, 0);

    //通知中心最底部固定9px的空白
    QSpacerItem* pVBottomSpacer = new QSpacerItem(9, 9, QSizePolicy::Fixed, QSizePolicy::Fixed);
    pNotificationVBoxLayout->addSpacerItem(pVBottomSpacer);

    m_pMainWidget->setLayout(pNotificationVBoxLayout);

    //新建一个监控dbus消息的线程
    MonitorThread* pMonitorThread = new MonitorThread(this);
    pMonitorThread->start();

    return;
}


QWidget* NotificationPlugin::centerWidget()
{
    return  m_pMainWidget;
}

void NotificationPlugin::showNotification()
{
    //上面不需要判断，因为在隐藏时，已经切换至通知中心，m_bShowTakeIn为false
    for(int i = 0; i < m_listAppMsg.count(); i++)
    {
        AppMsg* pAppMsg = m_listAppMsg.at(i);
        pAppMsg->updateAppPushTime();
    }
}

void NotificationPlugin::hideNotification()
{
    //侧边栏隐藏时，如果已经显示收纳盒，则切换至通知列表
    if(true == m_bShowTakeIn)
    {
        onShowTakeInMessage();
    }

    //隐藏时，因为上面已切换至通知列表，所以只需将通知列表都折叠即可
    for(int i = 0; i < m_listAppMsg.count(); i++)
    {
        AppMsg* pAppMsg = m_listAppMsg.at(i);
        pAppMsg->setAppFold();
    }

}

AppMsg* NotificationPlugin::getAppMsgAndIndexByName(QString strAppName, int& nIndex)
{
    AppMsg* pAppMsg = NULL;
    for(int i = 0; i < m_listAppMsg.count(); i++)
    {
        AppMsg* pTmpAppMsg = m_listAppMsg.at(i);
        if(strAppName == pTmpAppMsg->getAppName())
        {
            pAppMsg = pTmpAppMsg;
            nIndex = i;
            break;
        }
    }
    return pAppMsg;
}

uint NotificationPlugin::onAddSingleNotify(QString strAppName, QString strIconPath, QString strSummary, QString strBody, QDateTime dateTime, bool bNewNotificationFlag)
{
    qDebug() <<"NotificationPlugin::onAddSingleNotify strAppName=" <<strAppName;
    if(true == bNewNotificationFlag)
    {
        emit Sig_onNewNotification();
    }

    //当列表信息为空表明第一次来通知，列表个数为2，一个表面是“没有新通知标签”，一个是底部弹簧
    if(0 == m_listAppMsg.count() && 2 == m_pScrollAreaNotifyVBoxLayout->count())
    {
        m_pScrollAreaNotifyVBoxLayout->removeWidget(m_pMessageCenterLabel);
        m_pMessageCenterLabel->setVisible(false);
    }

    int nIndex = -1;
    //通过查找m_listAppMsg列表看该app是否已存在
    AppMsg* pAppMsg = getAppMsgAndIndexByName(strAppName, nIndex);

    //如果不存在，则新建一个AppMsg消息,并且直接置顶
    if(NULL == pAppMsg)
    {
        pAppMsg = new AppMsg(this, strAppName);
    }
    else
    {
        m_listAppMsg.removeAt(nIndex);
        m_pScrollAreaNotifyVBoxLayout->removeWidget(pAppMsg);
    }

    //在strAppName对应的AppMsg中添加单条信息
    pAppMsg->addSingleMsg(strIconPath, strSummary, dateTime, strBody);

    int uIndex = m_listAppMsg.count();
    for(int i = m_listAppMsg.count() - 1; i >= 0; i--)
    {
        AppMsg* pTmpAppMsg = m_listAppMsg.at(i);
        if(pAppMsg->getAppPushTime() < pTmpAppMsg->getAppPushTime())
        {
            break;
        }
        uIndex = i;
    }

    m_listAppMsg.insert(uIndex, pAppMsg);
    m_pScrollAreaNotifyVBoxLayout->insertWidget(uIndex, pAppMsg);

    //如果是新通知，有必要对通知列表更新推送时间；如果是恢复，说明在收纳盒中，所以更新收纳盒中的推送时间
    if(true == bNewNotificationFlag)
    {
        for(int i = 0; i < m_listAppMsg.count(); i++)
        {
            AppMsg* pTmpAppMsg = m_listAppMsg.at(i);
            pTmpAppMsg->updateAppPushTime();
        }
    }
    else
    {
        for(int i = 0; i < m_listTakeInAppMsg.count(); i++)
        {
            AppMsg* pTmpAppMsg = m_listTakeInAppMsg.at(i);
            pTmpAppMsg->updateAppPushTime();
        }
    }



    return 1;
}

void NotificationPlugin::onCountTakeInBitAndUpate() //统计收纳位数并更新至右上角提示
{
    int nCount = 0;
    for(int i = 0; i < m_listTakeInAppMsg.count(); i++)
    {
        AppMsg* pTmpAppMsg = m_listTakeInAppMsg.at(i);
        nCount = nCount + pTmpAppMsg->getSingleMsgCount();
    }

    QString strCount = QString::number(nCount);

    //收纳数的位数
    int nBit = 1;
    if(nCount > 999)
    {
        nBit = 3;
        strCount = "...";
    }
    else
    {
        while(nCount >= 10)
        {
            nCount = nCount / 10;
            nBit++;
        }
    }

    m_pTakeInCoutLabel->setGeometry(361, 21, (6 + 6 * nBit), 12);
    m_pTakeInCoutLabel->setText(strCount);
    if(false == m_bShowTakeIn)
    {
        m_pTakeInCoutLabel->setVisible(true);
    }
    return;
}

void NotificationPlugin::onClearAppMsg(AppMsg* pAppMsg)
{
    int nIndex = m_listAppMsg.indexOf(pAppMsg);
    if(-1 == nIndex)
    {
        qDebug()<<"NotificationPlugin::onClearAppMsg 在通知链表中未找到pSingleMsg指针";
        return;
    }

    m_listAppMsg.removeAt(nIndex);
    m_pScrollAreaNotifyVBoxLayout->removeWidget(pAppMsg);
    pAppMsg->deleteLater();

    if(0 == m_listAppMsg.count() && 1 == m_pScrollAreaNotifyVBoxLayout->count())
    {
        m_pMessageCenterLabel->setVisible(true);
        m_pScrollAreaNotifyVBoxLayout->insertWidget(0, m_pMessageCenterLabel, 0, Qt::AlignHCenter);
    }

    return;
}

void NotificationPlugin::onClearAllMessage()
{
    //当展示通知列表时
    if(false == m_bShowTakeIn)
    {
        while (m_listAppMsg.count() > 0)
        {
            AppMsg* pSingleMsg = m_listAppMsg.at(0);
            m_pScrollAreaNotifyVBoxLayout->removeWidget(pSingleMsg);
            pSingleMsg->deleteLater();
            m_listAppMsg.removeAt(0);
        }

        if(1 == m_pScrollAreaNotifyVBoxLayout->count())
        {
            m_pMessageCenterLabel->setVisible(true);
            m_pScrollAreaNotifyVBoxLayout->insertWidget(0, m_pMessageCenterLabel, 0, Qt::AlignHCenter);
        }

    }
    else
    {
        while (m_listTakeInAppMsg.count() > 0)
        {
            AppMsg* pSingleMsg = m_listTakeInAppMsg.at(0);
            m_pScrollAreaTakeInVBoxLayout->removeWidget(pSingleMsg);
            pSingleMsg->deleteLater();
            m_listTakeInAppMsg.removeAt(0);
        }

        if(1 == m_pScrollAreaTakeInVBoxLayout->count())
        {
            m_pTakeinMessageCenterLabel->setVisible(true);
            m_pScrollAreaTakeInVBoxLayout->insertWidget(0, m_pTakeinMessageCenterLabel, 0, Qt::AlignHCenter);
        }
        onCountTakeInBitAndUpate();
        m_pTakeInCoutLabel->setVisible(false);
    }

    return;
}

AppMsg* NotificationPlugin::getTakeinAppMsgAndIndexByName(QString strAppName, int& nIndex)
{
    AppMsg* pAppMsg = NULL;
    for(int i = 0; i < m_listTakeInAppMsg.count(); i++)
    {
        AppMsg* pTmpAppMsg = m_listTakeInAppMsg.at(i);
        if(strAppName == pTmpAppMsg->getAppName())
        {
            pAppMsg = pTmpAppMsg;
            nIndex = i;
            break;
        }
    }
    return pAppMsg;
}

void NotificationPlugin::onTakeInSingleNotify(QString strAppName, QString strIcon, QString strSummary, QString strBody, QDateTime dateTime)
{
    //当列表信息为空表明第一次来通知，列表个数为2，一个表面是“没有新通知标签”，一个是底部弹簧
    if(0 == m_listTakeInAppMsg.count() && 2 == m_pScrollAreaTakeInVBoxLayout->count())
    {
        m_pScrollAreaTakeInVBoxLayout->removeWidget(m_pTakeinMessageCenterLabel);
        m_pTakeinMessageCenterLabel->setVisible(false);
    }

    int nIndex = -1;
    //通过查找m_listTakeInAppMsg列表看该app是否已存在
    AppMsg* pAppMsg = getTakeinAppMsgAndIndexByName(strAppName, nIndex);
    //如果不存在，则新建一个AppMsg消息
    if(NULL == pAppMsg)
    {
        pAppMsg = new AppMsg(this, strAppName, true);
    }
    else
    {
        //如果找到该收纳应用，则先移除，后面根据时间插入
        m_listTakeInAppMsg.removeAt(nIndex);
        m_pScrollAreaTakeInVBoxLayout->removeWidget(pAppMsg);
    }
    pAppMsg->addSingleMsg(strIcon, strSummary, dateTime, strBody);


    int uIndex = m_listTakeInAppMsg.count();
    for(int i = m_listTakeInAppMsg.count() - 1; i >= 0; i--)
    {
        AppMsg* pTmpAppMsg = m_listTakeInAppMsg.at(i);
        if(pAppMsg->getAppPushTime() < pTmpAppMsg->getAppPushTime())
        {
            break;
        }
        uIndex = i;
    }

    m_listTakeInAppMsg.insert(uIndex, pAppMsg);
    m_pScrollAreaTakeInVBoxLayout->insertWidget(uIndex, pAppMsg);

    //收纳的时候没必要对收纳列表更新，可以对通知列表更新时间，反正点击进入收纳盒时，会更新收纳列表
    for(int i = 0; i < m_listAppMsg.count(); i++)
    {
        AppMsg* pTmpAppMsg = m_listAppMsg.at(i);
        pTmpAppMsg->updateAppPushTime();
    }

    onCountTakeInBitAndUpate();

    return;
}

//处理删除收纳应用的槽函数
void NotificationPlugin::onClearTakeInAppMsg(AppMsg* pAppMsg)
{
    int nIndex = m_listTakeInAppMsg.indexOf(pAppMsg);
    if(-1 == nIndex)
    {
        qDebug()<<"NotificationPlugin::onClearTakeInAppMsg 在收纳链表中未找到pSingleMsg指针";
        return;
    }

    m_listTakeInAppMsg.removeAt(nIndex);
    m_pScrollAreaTakeInVBoxLayout->removeWidget(pAppMsg);
    pAppMsg->deleteLater();

    onCountTakeInBitAndUpate();

    if(0 == m_listTakeInAppMsg.count() && 1 == m_pScrollAreaTakeInVBoxLayout->count())
    {
        m_pTakeinMessageCenterLabel->setVisible(true);
        m_pScrollAreaTakeInVBoxLayout->insertWidget(0, m_pTakeinMessageCenterLabel, 0, Qt::AlignHCenter);
    }
    return;
}

void NotificationPlugin::onCallControlPanel()
{
    QProcess p(0);
    p.startDetached("ukui-control-center");
    p.waitForStarted();

    return;
}

void NotificationPlugin::onShowTakeInMessage()
{
    if(false == m_bShowTakeIn)
    {
        m_bShowTakeIn = true;
        m_pQScrollAreaNotify->setVisible(false);
        m_pQScrollAreaTakeIn->setVisible(true);
        m_pNotificationLabel->setText(QObject::tr("Unimportant notice"));

        m_pSvgRender->load(QString(":/images/exitbox-24.svg"));
        m_pPixmap->fill(Qt::transparent);
        QPainter painter(m_pPixmap);
        m_pSvgRender->render(&painter);
        m_pTakeInBoxToolButton->setIcon(QIcon(*m_pPixmap));
        m_pTakeInBoxToolButton->setEnterFlags(m_bShowTakeIn);

        m_pTakeInCoutLabel->setVisible(false);

        //当切换至收纳盒时，先将各个收纳应用更新下时间
        for(int i = 0; i < m_listTakeInAppMsg.count(); i++)
        {
            AppMsg* pAppMsg = m_listTakeInAppMsg.at(i);
            pAppMsg->updateAppPushTime();
        }

        //再将各个通知应用折叠起来
        for(int i = 0; i < m_listAppMsg.count(); i++)
        {
            AppMsg* pAppMsg = m_listAppMsg.at(i);
            pAppMsg->setAppFold();
        }
    }
    else
    {
        m_bShowTakeIn = false;
        m_pQScrollAreaNotify->setVisible(true);
        m_pQScrollAreaTakeIn->setVisible(false);
        m_pNotificationLabel->setText(QObject::tr("Important notice"));

        m_pSvgRender->load(QString(":/images/box-24.svg"));
        m_pPixmap->fill(Qt::transparent);
        QPainter painter(m_pPixmap);
        m_pSvgRender->render(&painter);
        m_pTakeInBoxToolButton->setIcon(QIcon(*m_pPixmap));
        m_pTakeInBoxToolButton->setEnterFlags(m_bShowTakeIn);

        if(m_listTakeInAppMsg.count() > 0)
        {
            m_pTakeInCoutLabel->setVisible(true);
        }

        //当切换至通知列表时，先将各个通知应用更新下时间
        for(int i = 0; i < m_listAppMsg.count(); i++)
        {
            AppMsg* pAppMsg = m_listAppMsg.at(i);
            pAppMsg->updateAppPushTime();
        }

        //再将各个收纳应用折叠起来
        for(int i = 0; i < m_listTakeInAppMsg.count(); i++)
        {
            AppMsg* pAppMsg = m_listTakeInAppMsg.at(i);
            pAppMsg->setAppFold();
        }
    }
}
