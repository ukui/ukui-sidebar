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

#include "notificationPlugin.h"
#include "appmsg.h"
#include "scrollareawidget.h"
#include "takeinboxtoolbutton.h"
#include "monitorthread.h"
#include <QSvgRenderer>
#include <QDebug>
#include <QPainter>
#include "customstylePushbutton2.h"
#include "notificationDbus.h"


NotificationPlugin::NotificationPlugin()
{
    //初始化翻译文件
    initTrans();

    //初始化界面
    initUI();

//    //新建一个监控dbus消息的线程
//    MonitorThread* pMonitorThread = new MonitorThread(this);
//    QGSettings* pEnablenotice = new QGSettings("org.ukui.control-center.notice", "", this);
//    if(pEnablenotice->get("enable-notice").toBool()) {
//        pMonitorThread->start();
//        pMonitorThread->switchEnable(pEnablenotice->get("enable-notice").toBool());
//    }

//    connect(pEnablenotice, &QGSettings::changed, [=](){
//        pMonitorThread->switchEnable(pEnablenotice->get("enable-notice").toBool());
//    });

    //注册dbus接口，接收通知中心发送的通知信息
    NotificationDbus *notifyDbus = new NotificationDbus(this);


    return;
}


QWidget* NotificationPlugin::centerWidget()
{
    return  m_pMainWidget;
}

void NotificationPlugin::initTrans()
{
    QTranslator *translator = new QTranslator;
    if (translator->load(QLocale(), QLatin1String("ukui-sidebar-notification"), QLatin1String("_"), QLatin1String("/usr/share/ukui-sidebar/ukui-sidebar-notification")))
        QApplication::installTranslator(translator);
    else
        qDebug() << "cannot load translator ukui-sidebar-notification_" << QLocale::system().name() << ".qm!";
}

void NotificationPlugin::initUI()
{
    m_pMainWidget = new external_widget;
    m_pMainWidget->setObjectName("NotificationCenter");

    //消息通知模块总VBoxLayout布局器
    QVBoxLayout* pNotificationVBoxLayout = new QVBoxLayout;
    pNotificationVBoxLayout->setContentsMargins(10,21,0,0);
    pNotificationVBoxLayout->setSpacing(0);

    //装第一行通知中心的Widget
    QWidget* pWidget1= new QWidget;
    pWidget1->setObjectName("NotificationName");
    pWidget1->setAttribute(Qt::WA_TranslucentBackground);

    //第一行通知中心标题栏，左侧-标题通知中心，右侧-收纳按钮
    QHBoxLayout* pQHBoxLayout1 = new QHBoxLayout;
    pQHBoxLayout1->setContentsMargins(11,0,28,0);
    pQHBoxLayout1->setSpacing(0);

    //标题-通知中心
    QLabel* pLabel = new QLabel(QObject::tr("Notification center"));
    pLabel->setObjectName("notificationcentername");
    pLabel->setAttribute(Qt::WA_TranslucentBackground);

    //收纳按钮
    m_pTakeInBoxToolButton = new TakeInBoxToolButton();
    m_pTakeInBoxToolButton->setStyle(new CustomStyle_pushbutton_2("ukui-default"));
    m_pTakeInBoxToolButton->setFocusPolicy(Qt::NoFocus);
    connect(m_pTakeInBoxToolButton, SIGNAL(Sig_clicked()), this, SLOT(onShowTakeInMessage()));

    m_pTakeInBoxToolButton->setFixedSize(30,30);
    m_pTakeInBoxToolButton->setIconSize(QSize(24,24));
    m_pTakeInBoxToolButton->setIcon(QIcon(":/images/box-24.svg"));

    pQHBoxLayout1->addWidget(pLabel, 0, Qt::AlignLeft);
    pQHBoxLayout1->addWidget(m_pTakeInBoxToolButton, 0, Qt::AlignRight);
    pWidget1->setLayout(pQHBoxLayout1);
    pNotificationVBoxLayout->addWidget(pWidget1);

    //悬浮收纳数标签
    m_pTakeInCoutLabel = new TakeInCoutLabel(m_pMainWidget);
    m_pTakeInCoutLabel->setObjectName("takeincout");
    m_pTakeInCoutLabel->setFixedSize(23,23);

    QPalette pe1;
    pe1.setColor(QPalette::WindowText,Qt::black);
    m_pTakeInCoutLabel->setPalette(pe1);
    m_pTakeInCoutLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_pTakeInCoutLabel->setVisible(false);

    //添加24px的间距
    QSpacerItem* pVFixedSpacer = new QSpacerItem(10, 24, QSizePolicy::Fixed, QSizePolicy::Fixed);
    pNotificationVBoxLayout->addSpacerItem(pVFixedSpacer);

    //装第二行重要通知中的Widget
    QWidget* pWidget2= new QWidget;
    pWidget2->setFixedWidth(390);

    //第二行左侧标签“重要的信息”，右侧一个清空按钮，一个设置按钮
    QHBoxLayout* pQHBoxLayout2 = new QHBoxLayout;
    pQHBoxLayout2->setContentsMargins(12,0,10,8);

    //标签-重要的信息
    m_pNotificationLabel = new QLabel(QObject::tr("Important notice"));
    m_pNotificationLabel->setObjectName("importantnotification");
    m_pNotificationLabel->setAttribute(Qt::WA_TranslucentBackground);

    //清空按钮
    m_pClearAllToolButton = new QPushButton();
    m_pClearAllToolButton->setObjectName("clearall");
    connect(m_pClearAllToolButton, SIGNAL(clicked()), this, SLOT(onClearAllMessage()));
    m_pClearAllToolButton->setText(QObject::tr("Clean up"));
    m_pClearAllToolButton->setStyle(new CustomStyle_pushbutton_2("ukui-default"));
    m_pClearAllToolButton->setVisible(false);

    //设置按钮
    QPushButton* pSettingToolButton = new QPushButton();
    pSettingToolButton->setObjectName("setting");
    connect(pSettingToolButton, SIGNAL(clicked()), this, SLOT(onCallControlPanel()));
    pSettingToolButton->setText(QObject::tr("Set up"));
    pSettingToolButton->setStyle(new CustomStyle_pushbutton_2("ukui-default"));

    //布局
    QSpacerItem* pFixSpacer = new QSpacerItem(5, 10, QSizePolicy::Fixed, QSizePolicy::Fixed);
    QSpacerItem* pHSpacer = new QSpacerItem(300, 10, QSizePolicy::Expanding, QSizePolicy::Fixed);
    pQHBoxLayout2->addWidget(m_pNotificationLabel, 0, Qt::AlignLeft);
    pQHBoxLayout2->addSpacerItem(pHSpacer);
    pQHBoxLayout2->addWidget(m_pClearAllToolButton, 0, Qt::AlignRight);
    pQHBoxLayout2->addSpacerItem(pFixSpacer);
    pQHBoxLayout2->addWidget(pSettingToolButton, 0, Qt::AlignRight);
    pWidget2->setLayout(pQHBoxLayout2);
    pNotificationVBoxLayout->addWidget(pWidget2, 0);

    //消息列表widget
    m_pMsgListWidget = new inside_widget;
    m_pMsgListWidget->setFixedSize(390,546);
    pNotificationVBoxLayout->addWidget(m_pMsgListWidget, 1);
    m_pMsgListWidget->setParent(m_pMainWidget);

    //消息列表部件，用于装两个消息列表的,浮动在m_pMsgListWidget里面
    m_pMsgDoubleListWidget = new inside_widget(m_pMsgListWidget);
    QHBoxLayout* pMsgDoubleListHBoxLayout = new QHBoxLayout;
    pMsgDoubleListHBoxLayout->setContentsMargins(0, 0, 0, 0);
    pMsgDoubleListHBoxLayout->setSpacing(0);
    m_pMsgDoubleListWidget->setLayout(pMsgDoubleListHBoxLayout);
    m_pMsgDoubleListWidget->setAttribute(Qt::WA_TranslucentBackground);

    //双列表部件切换动画
    m_pSwitchAnimation = new QPropertyAnimation(m_pMsgDoubleListWidget, "geometry", this);
    m_pSwitchAnimation->setDuration(300);
    connect(m_pSwitchAnimation, SIGNAL(finished()), this, SLOT(onSwitchMsgBoxFinish()));

    //通知列表
    m_pQScrollAreaNotify = new ScrollAreaWidget();
    m_pQScrollAreaNotify->setAttribute(Qt::WA_TranslucentBackground);
    m_pQScrollAreaNotify->setFrameShape(QFrame::NoFrame);
    m_pQScrollAreaNotify->setFixedWidth(390);
    m_pScrollAreaNotifyVBoxLayout = new QVBoxLayout();
    m_pScrollAreaNotifyVBoxLayout->setContentsMargins(0, 0, 0, 0);
    m_pScrollAreaNotifyVBoxLayout->setSpacing(6);

    //通知列表的最内层部件
    inside_widget* pInQWidget = new inside_widget();
    pInQWidget->setObjectName("QScrollAreaInQWidget");
    pInQWidget->setLayout(m_pScrollAreaNotifyVBoxLayout);
    pInQWidget->setAttribute(Qt::WA_TranslucentBackground);
    m_pQScrollAreaNotify->setWidget(pInQWidget);
    m_pMessageCenterLabel = new QLabel(QObject::tr("No new notifications"));
    m_pMessageCenterLabel->setStyleSheet("background:transparent");
    m_pScrollAreaNotifyVBoxLayout->addWidget(m_pMessageCenterLabel, 4, Qt::AlignCenter);
    m_pMessageCenterLabel->setAttribute(Qt::WA_TranslucentBackground);
    QSpacerItem* pVSpacer = new QSpacerItem(10, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_pScrollAreaNotifyVBoxLayout->addSpacerItem(pVSpacer);
    pMsgDoubleListHBoxLayout->addWidget(m_pQScrollAreaNotify, 0);

    //收纳列表
    m_pQScrollAreaTakeIn = new ScrollAreaWidget();
    m_pQScrollAreaTakeIn->setAttribute(Qt::WA_TranslucentBackground);
    m_pQScrollAreaTakeIn->setFrameShape(QFrame::NoFrame);
    m_pQScrollAreaTakeIn->setFixedWidth(390);

    m_pScrollAreaTakeInVBoxLayout = new QVBoxLayout();
    m_pScrollAreaTakeInVBoxLayout->setContentsMargins(0,0,0,0);
    m_pScrollAreaTakeInVBoxLayout->setSpacing(0);

    //收纳列表的最内层部件
    inside_widget* pTakeInQWidget = new inside_widget();
    pTakeInQWidget->setObjectName("QScrollAreaInQWidget");
    pTakeInQWidget->setLayout(m_pScrollAreaTakeInVBoxLayout);
    pTakeInQWidget->setAttribute(Qt::WA_TranslucentBackground);
    m_pQScrollAreaTakeIn->setWidget(pTakeInQWidget);
    m_pTakeinMessageCenterLabel = new QLabel(QObject::tr("No unimportant notice"));
    m_pTakeinMessageCenterLabel->setAttribute(Qt::WA_TranslucentBackground);

    m_pScrollAreaTakeInVBoxLayout->addWidget(m_pTakeinMessageCenterLabel, 4, Qt::AlignCenter);
    QSpacerItem* pVSpacer2 = new QSpacerItem(10, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_pScrollAreaTakeInVBoxLayout->addSpacerItem(pVSpacer2);
    pMsgDoubleListHBoxLayout->addWidget(m_pQScrollAreaTakeIn, 0);

    //通知中心最底部固定9px的空白
    QSpacerItem* pVBottomSpacer = new QSpacerItem(9, 9, QSizePolicy::Fixed, QSizePolicy::Fixed);
    pNotificationVBoxLayout->addSpacerItem(pVBottomSpacer);
    m_pMainWidget->setLayout(pNotificationVBoxLayout);

}

void NotificationPlugin::showNotification()
{
    if (false == m_bInitialFlag) {
        m_bInitialFlag = true;
        qDebug()<<"NotificationPlugin::showNotification 通知列表的高度"<<m_pMsgListWidget->height() <<m_pMsgListWidget->width();
        m_pMsgDoubleListWidget->setGeometry(0, 0, m_pMsgListWidget->width()*2, m_pMsgListWidget->height());
    }
    //上面不需要判断，因为在隐藏时，已经切换至通知中心，m_bShowTakeIn为false
    for (int i = 0; i < m_listAppMsg.count(); i++) {
        AppMsg* pAppMsg = m_listAppMsg.at(i);
        pAppMsg->updateAppPushTime();
    }
}

void NotificationPlugin::hideNotification()
{
    //侧边栏隐藏时，如果已经显示收纳盒，则切换至通知列表
    if (true == m_bShowTakeIn) {
        onShowTakeInMessage();
    }

    //隐藏时，因为上面已切换至通知列表，所以只需将通知列表都折叠即可
    for (int i = 0; i < m_listAppMsg.count(); i++) {
        AppMsg* pAppMsg = m_listAppMsg.at(i);
        pAppMsg->setAppFold();
    }

}

AppMsg* NotificationPlugin::getAppMsgAndIndexByName(QString strAppName, int& nIndex)
{
    AppMsg* pAppMsg = NULL;
    for (int i = 0; i < m_listAppMsg.count(); i++) {
        AppMsg* pTmpAppMsg = m_listAppMsg.at(i);
        if (strAppName == pTmpAppMsg->getAppName()) {
            pAppMsg = pTmpAppMsg;
            nIndex = i;
            break;
        }
    }
    return pAppMsg;
}

uint NotificationPlugin::onAddSingleNotify(QString strAppName, QString strIconPath, QString strSummary,
                                           QString strBody, QString urlStr,  QString actions,
                                           QDateTime dateTime, int maxNum, bool bNewNotificationFlag)
{
    qInfo()<<"------------->NotificationPlugin:"<<strAppName<<strIconPath<<strSummary<<strBody<<urlStr<<actions<<dateTime<<maxNum;
    if(true == bNewNotificationFlag)
    {
        emit Sig_onNewNotification();
    }

    //当列表信息为空表明第一次来通知，列表个数为2，一个表面是“没有新通知标签”，一个是底部弹簧
    if (0 == m_listAppMsg.count() && 2 == m_pScrollAreaNotifyVBoxLayout->count()) {
        m_pScrollAreaNotifyVBoxLayout->removeWidget(m_pMessageCenterLabel);
        m_pMessageCenterLabel->setVisible(false);
        m_pClearAllToolButton->setVisible(true);
    }

    int nIndex = -1;
    //通过查找m_listAppMsg列表看该app是否已存在
    AppMsg* pAppMsg = getAppMsgAndIndexByName(strAppName, nIndex);

    //如果不存在，则新建一个AppMsg消息,并且直接置顶
    if (NULL == pAppMsg) {
        pAppMsg = new AppMsg(this, strAppName);
    } else {
        m_listAppMsg.removeAt(nIndex);
        m_pScrollAreaNotifyVBoxLayout->removeWidget(pAppMsg);
    }

    if (true == bNewNotificationFlag) {
//        pAppMsg->setMaxNumMsg(maxNum);
    }

    //在strAppName对应的AppMsg中添加单条信息
    if(pAppMsg->getSingleMsgCount() < maxNum){
        pAppMsg->addSingleMsg(strIconPath, strSummary, dateTime, strBody, urlStr, actions);
    }
    else{
        pAppMsg->deleteExceedingMsg();
        pAppMsg->addSingleMsg(strIconPath, strSummary, dateTime, strBody, urlStr, actions);
    }

    int uIndex = m_listAppMsg.count();
    for (int i = m_listAppMsg.count() - 1; i >= 0; i--) {
        AppMsg* pTmpAppMsg = m_listAppMsg.at(i);
        if (pAppMsg->getAppPushTime() < pTmpAppMsg->getAppPushTime()) {
            break;
        }
        uIndex = i;
    }

    m_listAppMsg.insert(uIndex, pAppMsg);
    m_pScrollAreaNotifyVBoxLayout->insertWidget(uIndex, pAppMsg);

    //如果是新通知，有必要对通知列表更新推送时间；如果是恢复，说明在收纳盒中，所以更新收纳盒中的推送时间
    if (true == bNewNotificationFlag) {
        for (int i = 0; i < m_listAppMsg.count(); i++) {
            AppMsg* pTmpAppMsg = m_listAppMsg.at(i);
            pTmpAppMsg->updateAppPushTime();
        }
    } else {
        for (int i = 0; i < m_listTakeInAppMsg.count(); i++) {
            AppMsg* pTmpAppMsg = m_listTakeInAppMsg.at(i);
            pTmpAppMsg->updateAppPushTime();
        }
    }
    return 1;
}

void NotificationPlugin::onCountTakeInBitAndUpate() //统计收纳位数并更新至右上角提示
{
    int nCount = 0;
    for (int i = 0; i < m_listTakeInAppMsg.count(); i++) {
        AppMsg* pTmpAppMsg = m_listTakeInAppMsg.at(i);
        nCount = nCount + pTmpAppMsg->getSingleMsgCount();
    }

    QString strCount = QString::number(nCount);

    //收纳数的位数
    int nBit = 1;
    if (nCount > 999) {
        nBit = 3;
        strCount = "...";
    } else {
        while (nCount >= 10) {
            nCount = nCount / 10;
            nBit++;
        }
    }

    m_pTakeInCoutLabel->setGeometry(361, 21, (6 + 6 * nBit), 12);
    m_pTakeInCoutLabel->setText(strCount);
    if (false == m_bShowTakeIn) {
        m_pTakeInCoutLabel->setVisible(true);
    }
    return;
}

void NotificationPlugin::onClearAppMsg(AppMsg* pAppMsg)
{
    int nIndex = m_listAppMsg.indexOf(pAppMsg);
    if (-1 == nIndex) {
        qDebug()<<"NotificationPlugin::onClearAppMsg 在通知链表中未找到pSingleMsg指针";
        return;
    }

    m_listAppMsg.removeAt(nIndex);
    m_pScrollAreaNotifyVBoxLayout->removeWidget(pAppMsg);
    pAppMsg->deleteLater();

    if (0 == m_listAppMsg.count() && 1 == m_pScrollAreaNotifyVBoxLayout->count()) {
        m_pMessageCenterLabel->setVisible(true);
        m_pScrollAreaNotifyVBoxLayout->insertWidget(0, m_pMessageCenterLabel, 4, Qt::AlignHCenter);
        m_pClearAllToolButton->setVisible(false);
    }

    return;
}

void NotificationPlugin::onClearAllMessage()
{
    //当展示通知列表时
    if (false == m_bShowTakeIn) {
        while (m_listAppMsg.count() > 0) {
            AppMsg* pSingleMsg = m_listAppMsg.at(0);
            m_pScrollAreaNotifyVBoxLayout->removeWidget(pSingleMsg);
            pSingleMsg->deleteLater();
            m_listAppMsg.removeAt(0);
        }

        if (1 == m_pScrollAreaNotifyVBoxLayout->count()) {
            m_pMessageCenterLabel->setVisible(true);
            m_pScrollAreaNotifyVBoxLayout->insertWidget(0, m_pMessageCenterLabel, 4, Qt::AlignHCenter);
            m_pClearAllToolButton->setVisible(false);
        }
    } else {
        while (m_listTakeInAppMsg.count() > 0) {
            AppMsg* pSingleMsg = m_listTakeInAppMsg.at(0);
            m_pScrollAreaTakeInVBoxLayout->removeWidget(pSingleMsg);
            pSingleMsg->deleteLater();
            m_listTakeInAppMsg.removeAt(0);
        }

        if (1 == m_pScrollAreaTakeInVBoxLayout->count()) {
            m_pTakeinMessageCenterLabel->setVisible(true);
            m_pScrollAreaTakeInVBoxLayout->insertWidget(0, m_pTakeinMessageCenterLabel, 4, Qt::AlignHCenter);
            m_pClearAllToolButton->setVisible(false);
        }
        onCountTakeInBitAndUpate();
    }
    return;
}

//配置实时关闭通知消息和收纳消息
void NotificationPlugin::onCloseAppMsg(QString strAppName)
{
    int nIndex = -1;
    AppMsg* pAppMsg = getAppMsgAndIndexByName(strAppName, nIndex);
    if (NULL != pAppMsg) {
        onClearAppMsg(pAppMsg);
    }

    //通过查找m_listTakeInAppMsg列表看该app是否已存在
    //AppMsg* pTakeinAppMsg = getTakeinAppMsgAndIndexByName(strAppName, nIndex);
    //if(NULL != pTakeinAppMsg)
    //{
    //    onClearTakeInAppMsg(pTakeinAppMsg);
    //}
}

//配置实时更新通知消息最大数
void NotificationPlugin::onUpdateAppMaxNum(QString strAppName, int maxNum)
{
    int nIndex = -1;
    AppMsg* pAppMsg = getAppMsgAndIndexByName(strAppName, nIndex);
    if (NULL != pAppMsg) {
//        pAppMsg->setMaxNumMsg(maxNum);
        pAppMsg->deleteExceedingMsg();
    }

    //通过查找m_listTakeInAppMsg列表看该app是否已存在
    AppMsg* pTakeinAppMsg = getTakeinAppMsgAndIndexByName(strAppName, nIndex);
    if (NULL != pTakeinAppMsg) {
        pTakeinAppMsg->setMaxNumMsg(maxNum);
        pTakeinAppMsg->deleteExceedingMsg();
    }
}

AppMsg* NotificationPlugin::getTakeinAppMsgAndIndexByName(QString strAppName, int& nIndex)
{
    AppMsg* pAppMsg = NULL;
    for (int i = 0; i < m_listTakeInAppMsg.count(); i++) {
        AppMsg* pTmpAppMsg = m_listTakeInAppMsg.at(i);
        if (strAppName == pTmpAppMsg->getAppName()) {
            pAppMsg = pTmpAppMsg;
            nIndex = i;
            break;
        }
    }
    return pAppMsg;
}

void NotificationPlugin::onTakeInSingleNotify(QString strAppName, QString strIcon, QString strSummary, QString strBody, QString urlStr,  QString actions, QDateTime dateTime, int maxNum, bool bNewTakeinFlag)
{
    //当列表信息为空表明第一次来通知，列表个数为2，一个表面是“没有新通知标签”，一个是底部弹簧
    if (0 == m_listTakeInAppMsg.count() && 2 == m_pScrollAreaTakeInVBoxLayout->count()) {
        m_pScrollAreaTakeInVBoxLayout->removeWidget(m_pTakeinMessageCenterLabel);
        m_pTakeinMessageCenterLabel->setVisible(false);
        m_pClearAllToolButton->setVisible(true);
    }

    int nIndex = -1;
    //通过查找m_listTakeInAppMsg列表看该app是否已存在
    AppMsg* pAppMsg = getTakeinAppMsgAndIndexByName(strAppName, nIndex);
    //如果不存在，则新建一个AppMsg消息
    if (NULL == pAppMsg) {
        pAppMsg = new AppMsg(this, strAppName, true);
    } else {
        //如果找到该收纳应用，则先移除，后面根据时间插入
        m_listTakeInAppMsg.removeAt(nIndex);
        m_pScrollAreaTakeInVBoxLayout->removeWidget(pAppMsg);
    }

    if (true == bNewTakeinFlag) {
        pAppMsg->setMaxNumMsg(maxNum);
    }
    pAppMsg->addSingleMsg(strIcon, strSummary, dateTime, strBody, urlStr, actions);


    int uIndex = m_listTakeInAppMsg.count();
    for (int i = m_listTakeInAppMsg.count() - 1; i >= 0; i--) {
        AppMsg* pTmpAppMsg = m_listTakeInAppMsg.at(i);
        if (pAppMsg->getAppPushTime() < pTmpAppMsg->getAppPushTime()) {
            break;
        }
        uIndex = i;
    }

    m_listTakeInAppMsg.insert(uIndex, pAppMsg);
    m_pScrollAreaTakeInVBoxLayout->insertWidget(uIndex, pAppMsg);

    //收纳的时候没必要对收纳列表更新，可以对通知列表更新时间，反正点击进入收纳盒时，会更新收纳列表
    for (int i = 0; i < m_listAppMsg.count(); i++) {
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
    if (-1 == nIndex) {
        qDebug()<<"NotificationPlugin::onClearTakeInAppMsg 在收纳链表中未找到pSingleMsg指针";
        return;
    }

    m_listTakeInAppMsg.removeAt(nIndex);
    m_pScrollAreaTakeInVBoxLayout->removeWidget(pAppMsg);
    pAppMsg->deleteLater();

    onCountTakeInBitAndUpate();

    if (0 == m_listTakeInAppMsg.count() && 1 == m_pScrollAreaTakeInVBoxLayout->count()) {
        m_pTakeinMessageCenterLabel->setVisible(true);
        m_pScrollAreaTakeInVBoxLayout->insertWidget(0, m_pTakeinMessageCenterLabel, 4, Qt::AlignHCenter);
        m_pClearAllToolButton->setVisible(false);
    }
    return;
}

void NotificationPlugin::onCallControlPanel()
{
    QProcess p(0);
    p.startDetached("ukui-control-center -n");
    p.waitForStarted();
    return;
}

void NotificationPlugin::onShowTakeInMessage()
{
    if (false == m_bShowTakeIn) {
        m_pSwitchAnimation->setStartValue(QRect(0, 0, m_pMsgListWidget->width()*2, m_pMsgListWidget->height()));
        m_pSwitchAnimation->setEndValue(QRect(0 - m_pMsgListWidget->width(), 0, m_pMsgListWidget->width()*2, m_pMsgListWidget->height()));
        m_pSwitchAnimation->start();
    } else {
        m_pSwitchAnimation->setStartValue(QRect(0 - m_pMsgListWidget->width(), 0, m_pMsgListWidget->width()*2, m_pMsgListWidget->height()));
        m_pSwitchAnimation->setEndValue(QRect(0, 0, m_pMsgListWidget->width()*2, m_pMsgListWidget->height()));
        m_pSwitchAnimation->start();
    }
}

//收纳盒按钮切换动画完成后处理
void NotificationPlugin::onSwitchMsgBoxFinish()
{
    if (false == m_bShowTakeIn) {
        m_bShowTakeIn = true;
        m_pNotificationLabel->setText(QObject::tr("Unimportant notice"));
        if(m_pTakeinMessageCenterLabel->isVisible()) {
            m_pClearAllToolButton->setVisible(false);
        } else {
            m_pClearAllToolButton->setVisible(true);
        }
        m_pTakeInBoxToolButton->setIcon(QIcon(":/images/exitbox-24.svg"));
        m_pTakeInBoxToolButton->setEnterFlags(m_bShowTakeIn);
        m_pTakeInCoutLabel->setVisible(false);

        //当切换至收纳盒时，先将各个收纳应用更新下时间
        for (int i = 0; i < m_listTakeInAppMsg.count(); i++) {
            AppMsg* pAppMsg = m_listTakeInAppMsg.at(i);
            pAppMsg->updateAppPushTime();
        }

        //再将各个通知应用折叠起来
        for (int i = 0; i < m_listAppMsg.count(); i++) {
            AppMsg* pAppMsg = m_listAppMsg.at(i);
            pAppMsg->setAppFold();
        }
    } else {
        m_bShowTakeIn = false;
        m_pNotificationLabel->setText(QObject::tr("Important notice"));
        if(m_pMessageCenterLabel->isVisible()) {
            m_pClearAllToolButton->setVisible(false);
        } else {
            m_pClearAllToolButton->setVisible(true);
        }

        m_pTakeInBoxToolButton->setIcon(QIcon(":/images/box-24.svg"));
        m_pTakeInBoxToolButton->setEnterFlags(m_bShowTakeIn);

        if (m_listTakeInAppMsg.count() > 0) {
            m_pTakeInCoutLabel->setVisible(true);
        }

        //当切换至通知列表时，先将各个通知应用更新下时间
        for (int i = 0; i < m_listAppMsg.count(); i++) {
            AppMsg* pAppMsg = m_listAppMsg.at(i);
            pAppMsg->updateAppPushTime();
        }

        //再将各个收纳应用折叠起来
        for (int i = 0; i < m_listTakeInAppMsg.count(); i++) {
            AppMsg* pAppMsg = m_listTakeInAppMsg.at(i);
            pAppMsg->setAppFold();
        }
    }
}

external_widget::external_widget()
{
    initGsettingValue();
    initGsettingTransparency();
}

void external_widget::initGsettingTransparency()
{
    if(QGSettings::isSchemaInstalled(UKUI_TRANSPARENCY_SETTING)) {
        m_pTransparency = new QGSettings(UKUI_TRANSPARENCY_SETTING);
        m_dTranSparency = m_pTransparency->get("transparency").toDouble();
        connect(m_pTransparency, &QGSettings::changed, this, [=](QString value) {
            m_dTranSparency = m_pTransparency->get("transparency").toDouble();;
        });
    }
}

void external_widget::initGsettingValue()
{
    const QByteArray id(STYLE_FONT_SCHEMA);
    if (QGSettings::isSchemaInstalled(id))
        m_pStyleGsetting = new QGSettings(id);
}

void external_widget::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    QRect rect = this->rect();
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.setBrush(QBrush(QColor(220,220,220,255)));

    QString m_style = "ukui-light";
    const QByteArray id(STYLE_FONT_SCHEMA);
    if (QGSettings::isSchemaInstalled(id))
         m_style = m_pStyleGsetting->get("style-name").toString();

    if (m_style=="ukui-light")
        p.setBrush(QBrush(QColor(220,220,220)));
    else
        p.setBrush(QBrush(QColor(20,20,20)));

    p.setOpacity(m_dTranSparency);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(rect,0,0);

}

inside_widget::inside_widget(QWidget *parent) : QWidget(parent)
{
      initGsettingValue();
      initGsettingTransparency();
}

void inside_widget::initGsettingTransparency()
{
    if (QGSettings::isSchemaInstalled(UKUI_TRANSPARENCY_SETTING)) {
        m_pTransparency = new QGSettings(UKUI_TRANSPARENCY_SETTING);
        m_dTranSparency = m_pTransparency->get("transparency").toDouble();
        connect(m_pTransparency, &QGSettings::changed, this, [=](QString value) {
            m_dTranSparency = m_pTransparency->get("transparency").toDouble();;
        });
    }
}

void inside_widget::initGsettingValue()
{
    const QByteArray id(STYLE_FONT_SCHEMA);
    if (QGSettings::isSchemaInstalled(id))
        m_pStyleGsetting = new QGSettings(id);
}

void inside_widget::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    QRect rect = this->rect();
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;

    QString m_style = "ukui-light";
    const QByteArray id(STYLE_FONT_SCHEMA);
    if (QGSettings::isSchemaInstalled(id))
         m_style = m_pStyleGsetting->get("style-name").toString();

    if (m_style=="ukui-light")
        p.setBrush(QBrush(QColor(220,220,220)));
    else
        p.setBrush(QBrush(QColor(20,20,20)));

    p.setOpacity(m_dTranSparency);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(rect,0,0);
    QWidget::paintEvent(e);
}

TakeInCoutLabel::TakeInCoutLabel(QWidget *parent) : QLabel(parent)
{

}


void TakeInCoutLabel::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    QRect rect = this->rect();
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.setBrush(QBrush(QColor(255,255,255)));
    p.setOpacity(0.7);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(rect,20,20);
    QLabel::paintEvent(e);
}

