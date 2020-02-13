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
//    m_pMainWidget->setObjectName("NotificationCenter");

    /* 加载样式表 */
    QFile file(":/qss/notification_plugin.css");
    if (file.open(QFile::ReadOnly)) {
        m_strQss = QLatin1String(file.readAll());
        file.close();
        m_pMainWidget->setStyleSheet(m_strQss);
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
    QLabel* pLabel = new QLabel("通知中心");
    pLabel->setObjectName("notificationcentername");

    //收纳按钮
    m_pTakeInBoxToolButton = new TakeInBoxToolButton();
    m_pTakeInBoxToolButton->setObjectName("takein");
    connect(m_pTakeInBoxToolButton, SIGNAL(clicked()), this, SLOT(showTakeInMessage()));

    //QToolButton添加svg图片
    m_pSvgRender = new QSvgRenderer(pWidget1);
    m_pSvgRender->load(QString(":/images/box.svg"));
    m_pPixmap = new QPixmap(24, 24);

    m_pPixmap->fill(Qt::transparent);
    QPainter painter(m_pPixmap);
    m_pSvgRender->render(&painter);
    m_pTakeInBoxToolButton->setIcon(QIcon(*m_pPixmap));

    pQHBoxLayout1->addWidget(pLabel, 0, Qt::AlignLeft);
    pQHBoxLayout1->addWidget(m_pTakeInBoxToolButton, 0, Qt::AlignRight);
    pWidget1->setLayout(pQHBoxLayout1);
    pNotificationVBoxLayout->addWidget(pWidget1);

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
    pQHBoxLayout2->setContentsMargins(12,0,10,10);
    m_pNotificationLabel = new QLabel("重要的通知");
    m_pNotificationLabel->setObjectName("importantnotification");

    QSpacerItem* pHSpacer = new QSpacerItem(300, 10, QSizePolicy::Expanding, QSizePolicy::Fixed);

    QPushButton* pClearAllToolButton = new QPushButton();
    pClearAllToolButton->setObjectName("clearall");
    connect(pClearAllToolButton, SIGNAL(clicked()), this, SLOT(clearAllMessage()));
    pClearAllToolButton->setText("清空");

    QSpacerItem* pFixSpacer = new QSpacerItem(5, 10, QSizePolicy::Fixed, QSizePolicy::Fixed);

    QPushButton* pSettingToolButton = new QPushButton();
    pSettingToolButton->setObjectName("setting");
    connect(pSettingToolButton, SIGNAL(clicked()), this, SLOT(callControlPanel()));
    pSettingToolButton->setText("设置");


    pQHBoxLayout2->addWidget(m_pNotificationLabel, 0, Qt::AlignLeft);
    pQHBoxLayout2->addSpacerItem(pHSpacer);
    pQHBoxLayout2->addWidget(pClearAllToolButton, 0, Qt::AlignRight);
    pQHBoxLayout2->addSpacerItem(pFixSpacer);
    pQHBoxLayout2->addWidget(pSettingToolButton, 0, Qt::AlignRight);
    pWidget2->setLayout(pQHBoxLayout2);
    pNotificationVBoxLayout->addWidget(pWidget2, 0);

    //通知列表
    m_pQScrollAreaNotify = new ScrollAreaWidget();
    m_pQScrollAreaNotify->setStyleSheet("QWidget{border:0px;}");

    m_pScrollAreaNotifyVBoxLayout = new QVBoxLayout();
    m_pScrollAreaNotifyVBoxLayout->setContentsMargins(0,0,0,0);
    m_pScrollAreaNotifyVBoxLayout->setSpacing(0);

    QWidget* pInQWidget = new QWidget();  //通知列表的最内层部件
    pInQWidget->setLayout(m_pScrollAreaNotifyVBoxLayout);
    m_pQScrollAreaNotify->setWidget(pInQWidget);

    m_pMessageCenterLabel = new QLabel("没有新通知");
    m_pMessageCenterLabel->setStyleSheet("QLabel{padding:10px 0px 0px 11px;}");
    m_pScrollAreaNotifyVBoxLayout->addWidget(m_pMessageCenterLabel);
    QSpacerItem* pVSpacer = new QSpacerItem(10, 10, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_pScrollAreaNotifyVBoxLayout->addSpacerItem(pVSpacer);

    pNotificationVBoxLayout->addWidget(m_pQScrollAreaNotify, 0);

    //收纳列表
    m_pQScrollAreaTakeIn = new ScrollAreaWidget();
    m_pQScrollAreaTakeIn->setStyleSheet("QWidget{border:0px;}");

    m_pScrollAreaTakeInVBoxLayout = new QVBoxLayout();
    m_pScrollAreaTakeInVBoxLayout->setContentsMargins(0,0,0,0);
    m_pScrollAreaTakeInVBoxLayout->setSpacing(0);

    QWidget* pTakeInQWidget = new QWidget();  //收纳列表的最内层部件
    pTakeInQWidget->setLayout(m_pScrollAreaTakeInVBoxLayout);
    m_pQScrollAreaTakeIn->setWidget(pTakeInQWidget);

    QSpacerItem* pVSpacer2 = new QSpacerItem(10, 10, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_pScrollAreaTakeInVBoxLayout->addSpacerItem(pVSpacer2);
    pNotificationVBoxLayout->addWidget(m_pQScrollAreaTakeIn, 0);
    m_pQScrollAreaTakeIn->setVisible(false);

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

void NotificationPlugin::updatePushTime()
{
    if(false == m_bShowTakeIn)
    {
        for(int i = 0; i < m_listAppMsg.count(); i++)
        {
            AppMsg* pAppMsg = m_listAppMsg.at(i);
            pAppMsg->updateAppPushTime();
        }
    }
    else
    {
        for(int i = 0; i < m_listAppTakeInMsg.count(); i++)
        {
            AppMsg* pAppMsg = m_listAppTakeInMsg.at(i);
            pAppMsg->updateAppPushTime();
        }
    }
}

//uint NotificationPlugin::Notify(QString strAppName, uint uId, QString strIconPath, QString strSummary, QString strBody, QStringList actions, QVariantMap hint, int nTimeout)
//{
//    Q_UNUSED(uId);
//    Q_UNUSED(actions);
//    Q_UNUSED(hint);
//    Q_UNUSED(nTimeout);

//    qDebug() <<"NotificationPlugin::Notify strAppName=" <<strAppName;
//    if(0 == m_listAppMsg.count() && 2 == m_pScrollAreaNotifyVBoxLayout->count()) //当列表信息为空表明第一次来通知，列表个数为2，一个表面是“没有新通知标签”，一个是底部弹簧
//    {
//        m_pScrollAreaNotifyVBoxLayout->removeWidget(m_pMessageCenterLabel);
//        m_pMessageCenterLabel->setVisible(false);
//    }

//    QDateTime dateTime(QDateTime::currentDateTime());

//    AppMsg* pSingleMsg = new AppMsg(this, strAppName, strIconPath, strSummary, dateTime, strBody);
//    m_listAppMsg.append(pSingleMsg);
//    m_pScrollAreaNotifyVBoxLayout->insertWidget((m_pScrollAreaNotifyVBoxLayout->count() - 1), pSingleMsg);

//    return 1;
//}

AppMsg* NotificationPlugin::getAppMsgByName(QString strAppName)
{
    AppMsg* pAppMsg = NULL;
    for(int i = 0; i < m_listAppMsg.count(); i++)
    {
        AppMsg* pTmpAppMsg = m_listAppMsg.at(i);
        if(strAppName == pTmpAppMsg->getAppName())
        {
            pAppMsg = pTmpAppMsg;
            break;
        }
    }
    return pAppMsg;
}

uint NotificationPlugin::Notify(QString strAppName, QString strIconPath, QString strSummary, QString strBody)
{
    QDateTime dateTime(QDateTime::currentDateTime());
    qDebug() <<"NotificationPlugin::Notify strAppName=" <<strAppName;

    if(0 == m_listAppMsg.count() && 2 == m_pScrollAreaNotifyVBoxLayout->count()) //当列表信息为空表明第一次来通知，列表个数为2，一个表面是“没有新通知标签”，一个是底部弹簧
    {
        m_pScrollAreaNotifyVBoxLayout->removeWidget(m_pMessageCenterLabel);
        m_pMessageCenterLabel->setVisible(false);
    }

    AppMsg* pAppMsg = getAppMsgByName(strAppName);  //通过查找m_listAppMsg列表看该app是否已存在
    if(NULL == pAppMsg)         //如果不存在，则新建一个AppMsg消息
    {
        pAppMsg = new AppMsg(this, strAppName, strIconPath);
        m_listAppMsg.insert(0, pAppMsg);
        m_pScrollAreaNotifyVBoxLayout->insertWidget(0, pAppMsg);
    }

    pAppMsg->addSingleMsg(strSummary, dateTime, strBody); //在strAppName对应的AppMsg中添加单条信息

    for(int i = 0; i < m_listAppMsg.count(); i++)
    {
        AppMsg* pTmpAppMsg = m_listAppMsg.at(i);
        pTmpAppMsg->updateAppPushTime();
    }

    return 1;
}

void NotificationPlugin::countTakeInBitAndUpate() //统计收纳位数并更新至右上角提示
{
    int nCount = m_listAppTakeInMsg.count();
    QString strCount = QString::number(nCount);
    int nBit = 1; //收纳数的位数
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
    if(false == m_pTakeInCoutLabel->isVisible())
    {
        m_pTakeInCoutLabel->setVisible(true);
    }
    return;
}

void NotificationPlugin::onTakeinMsg(AppMsg* pSingleMsg)
{
    int nIndex = m_listAppMsg.indexOf(pSingleMsg);
    if(-1 == nIndex)
    {
        qDebug()<<"Widget::onClearMsg 在链表中未找到pSingleMsg指针";
        return;
    }

    m_listAppMsg.removeAt(nIndex);
    m_pScrollAreaNotifyVBoxLayout->removeWidget(pSingleMsg);

    if(0 == m_listAppMsg.count() && 1 == m_pScrollAreaNotifyVBoxLayout->count()) //列表个数为1是指底部弹簧
    {
        m_pMessageCenterLabel->setVisible(true);
        m_pScrollAreaNotifyVBoxLayout->insertWidget(0, m_pMessageCenterLabel);
    }

    uint uIndex = m_listAppTakeInMsg.count();
    for(int i = m_listAppTakeInMsg.count() - 1; i >= 0; i--)
    {
        AppMsg* pTmpSingleMsg = m_listAppTakeInMsg.at(i);
        if(pSingleMsg->getNotifyAbsuluteTime() < pTmpSingleMsg->getNotifyAbsuluteTime())
        {
            break;
        }
        uIndex = i;
    }
    m_listAppTakeInMsg.insert(uIndex, pSingleMsg);
    m_pScrollAreaTakeInVBoxLayout->insertWidget(uIndex, pSingleMsg);

    countTakeInBitAndUpate();

    return;
}

void NotificationPlugin::onClearMsg(AppMsg* pSingleMsg)
{
    if(true == m_bShowTakeIn)  //当展示收纳列表时
    {
        qDebug()<<"NotificationPlugin::onClearMsg 在收纳盒时，是不应该点击到删除按钮的";
        return;
    }

    int nIndex = m_listAppMsg.indexOf(pSingleMsg);
    if(-1 == nIndex)
    {
        qDebug()<<"NotificationPlugin::onClearMsg 在通知链表中未找到pSingleMsg指针";
        return;
    }

    m_listAppMsg.removeAt(nIndex);
    m_pScrollAreaNotifyVBoxLayout->removeWidget(pSingleMsg);
    pSingleMsg->deleteLater();

    if(0 == m_listAppMsg.count() && 1 == m_pScrollAreaNotifyVBoxLayout->count())
    {
        m_pMessageCenterLabel->setVisible(true);
        m_pScrollAreaNotifyVBoxLayout->insertWidget(0, m_pMessageCenterLabel);
    }

    return;
}


void NotificationPlugin::clearAllMessage()
{
    if(false == m_bShowTakeIn)  //当展示通知列表时
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
            m_pScrollAreaNotifyVBoxLayout->insertWidget(0, m_pMessageCenterLabel);
        }

    }
    else    //当展示收纳列表时
    {
        while (m_listAppTakeInMsg.count() > 0)
        {
            AppMsg* pSingleMsg = m_listAppTakeInMsg.at(0);
            m_pScrollAreaTakeInVBoxLayout->removeWidget(pSingleMsg);
            pSingleMsg->deleteLater();
            m_listAppTakeInMsg.removeAt(0);
        }
        m_pTakeInCoutLabel->setVisible(false);
    }

    return;
}

void NotificationPlugin::callControlPanel()
{
    QProcess p(0);
    p.startDetached("ukui-control-center");
    p.waitForStarted();
    return;
}

void NotificationPlugin::showTakeInMessage()
{
    if(false == m_bShowTakeIn)
    {
        m_bShowTakeIn = true;
        m_pQScrollAreaNotify->setVisible(false);
        m_pQScrollAreaTakeIn->setVisible(true);
        m_pNotificationLabel->setText("不重要的通知");

        m_pSvgRender->load(QString(":/images/exitbox.svg"));
        m_pPixmap->fill(Qt::transparent);
        QPainter painter(m_pPixmap);
        m_pSvgRender->render(&painter);
        m_pTakeInBoxToolButton->setIcon(QIcon(*m_pPixmap));
        m_pTakeInBoxToolButton->setEnterFlags(m_bShowTakeIn);

        m_pTakeInCoutLabel->setVisible(false);

        for(int i = 0; i < m_listAppTakeInMsg.count(); i++)
        {
            AppMsg* pAppMsg = m_listAppTakeInMsg.at(i);
            pAppMsg->updateAppPushTime();
        }
    }
    else
    {
        m_bShowTakeIn = false;
        m_pQScrollAreaNotify->setVisible(true);
        m_pQScrollAreaTakeIn->setVisible(false);
        m_pNotificationLabel->setText("重要的通知");

        m_pSvgRender->load(QString(":/images/box.svg"));
        m_pPixmap->fill(Qt::transparent);
        QPainter painter(m_pPixmap);
        m_pSvgRender->render(&painter);
        m_pTakeInBoxToolButton->setIcon(QIcon(*m_pPixmap));
        m_pTakeInBoxToolButton->setEnterFlags(m_bShowTakeIn);

        if(m_listAppTakeInMsg.count() > 0)
        {
            m_pTakeInCoutLabel->setVisible(true);
        }

        for(int i = 0; i < m_listAppMsg.count(); i++)
        {
            AppMsg* pAppMsg = m_listAppMsg.at(i);
            pAppMsg->updateAppPushTime();
        }
    }
}
