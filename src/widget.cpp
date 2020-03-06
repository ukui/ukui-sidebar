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


#include "widget.h"
#include "notification_interface.h"
#include "pluginmanage.h"
#include <stdio.h>
#include <QtDBus>


Widget::Widget(QWidget *parent) : QWidget (parent)
{
    m_bShowFlag = false;
    m_bFwinkleFlag = true;

    /* 监听屏幕分辨率是否变化 */
    QDesktopWidget* desk = QApplication::desktop();
    connect(desk, SIGNAL(resized(int)), this, SLOT(onResolutionChanged(int)));

    m_pServiceInterface = new QDBusInterface(PANEL_DBUS_SERVICE,
            PANEL_DBUS_PATH,
            PANEL_DBUS_INTERFACE,
            QDBusConnection::sessionBus());
    m_pServiceInterface->setTimeout(2147483647);

    //获取桌面分辨率大小
//    QScreen* pScreen = QGuiApplication::primaryScreen();
//    QRect DeskSize = pScreen->availableGeometry();
//    m_nDeskWidth = DeskSize.width();        //桌面分辨率的宽
//    m_nDeskHeight = DeskSize.height();      //桌面分辨率的高

//    qInfo() << "屏幕分辨率的宽" << m_nDeskWidth;
//    qInfo() << "屏幕分辨率的高" << m_nDeskHeight;

    /* 主界面显示 */
    m_pMainQVBoxLayout = new QVBoxLayout;
    m_pMainQVBoxLayout->setContentsMargins(0,0,0,0);

    /* 加载剪贴板插件 */
    ListenClipboardSignal();

    //加载通知中心插件
    if(false == loadNotificationPlugin())
    {
        qDebug() << "通知中心插件加载失败";
    }
    m_pShortcutOperationGroupBox->setObjectName("ShortcutOperationGroupBox");
//    m_pShortcutOperationGroupBox->setAttribute(Qt::WA_TranslucentBackground);
//    m_pShortcutOperationGroupBox->setStyleSheet("QGroupBox#ShortcutOperationGroupBox{background:rgba(19, 19, 20, 0)}");
    m_pMainQVBoxLayout->addWidget(m_pShortcutOperationGroupBox, 0);

    setLayout(m_pMainQVBoxLayout);

    /* 系统托盘栏显示 */
    createAction();
    createSystray();
    setIcon(TRAY_ICON);

    //安装事件过滤器
    installEventFilter(this);

    //设置hide动画
    m_pHideAnimation = new QPropertyAnimation(this, "geometry");
    m_pHideAnimation->setDuration(200);
    connect(m_pHideAnimation, &QPropertyAnimation::finished, this, &Widget::HideAnimationEndSlots);

    //设置show动画
    m_pShowAnimation = new QPropertyAnimation(this, "geometry");
    m_pShowAnimation->setDuration(400);
    //将托盘栏图标和widget联系起来
    connect(trayIcon, &QSystemTrayIcon::activated, this, &Widget::iconActivated);
    trayIcon->setVisible(true);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
    qInfo() << "---------------------------主界面加载完毕---------------------------";

    m_pTimer = new QTimer();
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(twinkle()));
}

Widget::~Widget()
{

}

uint Widget::panelSizeChangeNotify(uint uId)
{
//    QDesktopWidget *deskWgt = QApplication::desktop();
//    if (nullptr == deskWgt) {
//        return 0;
//    }

//    QRect screenRect = deskWgt->screenGeometry();
//    m_nDeskWidth = screenRect.width();
//    m_nDeskHeight = screenRect.height() - uId;
//    qInfo() << "screen width:" << m_nDeskWidth << ",height:" << m_nDeskHeight;

//    if(true == m_bShowFlag)  //当展开时，才需要实时改变尺寸
//    {
//        this->setGeometry(m_nDeskWidth - 400,0,400,m_nDeskHeight);
//    }

    return 1;
}

//加载通知中心插件
bool Widget::loadNotificationPlugin()
{
    QDir pluginsDir("/usr/lib/ukui-sidebar/notification");
    QPluginLoader pluginLoader(pluginsDir.absoluteFilePath("libnotification_plugin.so"));
    m_pNotificationPluginObject = pluginLoader.instance();
    if(nullptr == m_pNotificationPluginObject)
    {
        return false;
    }

    auto centerInterface = qobject_cast<NotificationInterface*>(m_pNotificationPluginObject);
    if(nullptr == centerInterface)
    {
        return false;
    }

    connect(m_pNotificationPluginObject, SIGNAL(Sig_onNewNotification()), this, SLOT(onNewNotification()));

    m_pMainQVBoxLayout->addWidget(centerInterface->centerWidget(), 1);

//    QDBusConnection connection = QDBusConnection::sessionBus();
//    if(!connection.registerService("com.scorpio.test"))
//    {
//        qDebug() << "error:" << connection.lastError().message();
//        return false;
//    }
//    connection.registerObject("/test/objects", pNotificationPluginObject, QDBusConnection::ExportAllSlots);

    return true;
}

/* 加载剪贴板插件 */
void Widget::ListenClipboardSignal()
{
    PluginInterface* pPluginInterface = PluginManager::getInstance()->m_PluginInterfaceHash.value("ClipBoard");
    m_pSidebarClipboard = dynamic_cast<ClipboardInterface *>(pPluginInterface);  //获取剪贴版插件指针;
    if (nullptr == m_pSidebarClipboard) {
        qWarning() << "剪贴板插件插件加载失败";
        return;
    }
    m_pSidebarSignal = m_pSidebarClipboard->createClipSignal();   //获取剪贴板的信号类指针
    m_pShortcutOperationListWidget = m_pSidebarClipboard->getClipbaordListWidget();  //获取剪贴板的ListWidget指针
    m_pShortcutOperationGroupBox = m_pSidebarClipboard->getClipbaordGroupBox();      //获取剪贴板的Groubox指针;
    return;
}

//创建动作
void Widget::createAction()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, &QAction::triggered, this, &QWidget::showMaximized);

    restoreAction = new QAction(tr("normal"), this);
    connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

//添加动作和创建 systray实例
void Widget::createSystray()
{
    trayIconMenu = new QMenu(this);
    if (trayIconMenu == nullptr) {
        qWarning() << "分配空间trayIconMenu失败";
        return ;
    }
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    if (nullptr == trayIcon) {
        qWarning() << "分配空间trayIcon失败";
        return ;
    }
    trayIcon->setContextMenu(trayIconMenu);
}

//设置托盘栏的图标
void Widget::setIcon(QString strIcon)
{
    QIcon icon = QIcon(strIcon);
    trayIcon->setIcon(icon);
    setWindowIcon(icon);
    trayIcon->setToolTip("侧边栏");
}

//设置activated信号
void Widget::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::Trigger:
        {
            if (m_bShowFlag) {
                qDebug() << "Widget::iconActivated 隐藏";
                hideAnimation();
                m_bShowFlag = false;;
            } else {
                showAnimation();
                this->show();
                qDebug() << "Widget::iconActivated 展开";
                m_bShowFlag = true;
                m_pTimer->stop();           //当侧边栏展开时，停止闪烁定时器，并且设置有图标的托盘图标
                setIcon(TRAY_ICON);
            }
            break;
        }
        case QSystemTrayIcon::DoubleClick:
        {
            showAnimation();
            this->show();
            m_bShowFlag = true;
            m_pTimer->stop();               //当侧边栏展开时，停止闪烁定时器，并且设置有图标的托盘图标
            setIcon(TRAY_ICON);
            break;
        }
        default:
            break;
    }
}

/* 链接任务栏dbus获取高度的接口 */
int Widget::connectTaskBarDbus()
{
    QDBusMessage msg = m_pServiceInterface->call("GetPanelSize", QVariant("Hight"));
    int panelHight = msg.arguments().at(0).toInt();
    qDebug() << "panelHight" << panelHight;
    return panelHight;
}

/* 获取任务栏状态位置 下 上 左 右 */
int Widget::getPanelSite()
{
    QDBusMessage msg = m_pServiceInterface->call("GetPanelPosition", QVariant("Site"));
    int PanelSite = msg.arguments().at(0).toInt();
    qDebug() << "panel所在的位置" << PanelSite;
    return PanelSite;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton) {
        hideAnimation();
        m_bShowFlag = false;
    }

}

//获取屏幕的可用区域高度和宽度
void Widget::GetsAvailableAreaScreen()
{
    //如果取不到任务栏的高度,还是优先获取桌面分辨率,可用区域
    if((0 == connectTaskBarDbus()) && (0 == getPanelSite())) {
        QScreen* pScreen = QGuiApplication::primaryScreen();
        QRect DeskSize = pScreen->availableGeometry();
        m_nDeskWidth = DeskSize.width();        //桌面分辨率的宽
        m_nDeskHeight = DeskSize.height();      //桌面分辨率的高
    } else {
        //如果取到任务栏的高度,还是用屏幕分辨率的高度减去任务栏的高度得到桌面高度
        QDesktopWidget *deskWgt = QApplication::desktop();
        QRect screenRect = deskWgt->screenGeometry();
        m_nDeskWidth = screenRect.width();
        m_nDeskHeight = screenRect.height();
    }
}

//动画展开
void Widget::showAnimation()
{
    auto centerInterface = qobject_cast<NotificationInterface*>(m_pNotificationPluginObject);
    if(nullptr != centerInterface)
    {
        centerInterface->updatePushTime(); //当动画展开时也更新一下通知列表或者收纳列表的推送时间显示
    }
    GetsAvailableAreaScreen(); //获取屏幕可用高度区域

    int  AnimaStartSideBarSite[4];                       //侧边栏动画开始位置
    int  AnimaStopSidebarSite[4];                        //侧边栏动画结束位置
    switch (getPanelSite()) {
        case Widget::PanelDown : {
            qDebug() << "所在位置" << getPanelSite();
            //起始位置的坐标
            AnimaStartSideBarSite[0] = m_nDeskWidth;
            AnimaStartSideBarSite[1] = 0;
            AnimaStartSideBarSite[2] = 400;
            AnimaStartSideBarSite[3] = m_nDeskHeight - connectTaskBarDbus();
            //结束位置坐标
            AnimaStopSidebarSite[0]  = m_nDeskWidth - 400;
            AnimaStopSidebarSite[1]  = 0;
            AnimaStopSidebarSite[2]  = 400;
            AnimaStopSidebarSite[3]  = m_nDeskHeight  - connectTaskBarDbus();
        }
        break;
        case Widget::PanelUp: {
            qDebug() << "所在位置" << getPanelSite();
            //起始位置的坐标
            AnimaStartSideBarSite[0] = m_nDeskWidth;
            AnimaStartSideBarSite[1] = connectTaskBarDbus();
            AnimaStartSideBarSite[2] = 400;
            AnimaStartSideBarSite[3] = m_nDeskHeight  - connectTaskBarDbus();
            //结束位置坐标
            AnimaStopSidebarSite[0]  = m_nDeskWidth - 400;
            AnimaStopSidebarSite[1]  = connectTaskBarDbus();;
            AnimaStopSidebarSite[2]  = 400;
            AnimaStopSidebarSite[3]  = m_nDeskHeight - connectTaskBarDbus();
        }
        break;
        case Widget::PanelLeft: {
            qDebug() << "所在位置" << getPanelSite();
            //起始位置的坐标
            AnimaStartSideBarSite[0] = m_nDeskWidth;
            AnimaStartSideBarSite[1] = 0;
            AnimaStartSideBarSite[2] = 400;
            AnimaStartSideBarSite[3] = m_nDeskHeight;
            //结束位置坐标
            AnimaStopSidebarSite[0]  = m_nDeskWidth - 400;
            AnimaStopSidebarSite[1]  = 0;
            AnimaStopSidebarSite[2]  = 400;
            AnimaStopSidebarSite[3]  = m_nDeskHeight;
        }
        break;
        case Widget::PanelRight: {
            qDebug() << "所在位置" << getPanelSite();
            //起始位置的坐标
            AnimaStartSideBarSite[0] = m_nDeskWidth - connectTaskBarDbus();
            AnimaStartSideBarSite[1] = 0;
            AnimaStartSideBarSite[2] = 400;
            AnimaStartSideBarSite[3] = m_nDeskHeight;
            //结束位置坐标
            AnimaStopSidebarSite[0]  = m_nDeskWidth - 400 - connectTaskBarDbus();
            AnimaStopSidebarSite[1]  = 0;
            AnimaStopSidebarSite[2]  = 400;
            AnimaStopSidebarSite[3]  = m_nDeskHeight;

        }
        break;
        default:
        break;
    }
    //动画起始位置，根据获取状态来进行状态设置
    m_pShowAnimation->setStartValue(QRect(AnimaStartSideBarSite[0], AnimaStartSideBarSite[1], AnimaStartSideBarSite[2], AnimaStartSideBarSite[3]));
    m_pShowAnimation->setEndValue(QRect(AnimaStopSidebarSite[0], AnimaStopSidebarSite[1], AnimaStopSidebarSite[2], AnimaStopSidebarSite[3]));
    m_pShowAnimation->start();
}

//隐藏动画
void Widget::hideAnimation()
{
    int  AnimaStartSideBarSite[4];                       //侧边栏动画开始位置
    int  AnimaStopSidebarSite[4];                        //侧边栏动画结束位置
    switch (getPanelSite()) {
        case Widget::PanelDown : {
            qDebug() << "所在位置" << getPanelSite();
            //起始位置的坐标
            AnimaStartSideBarSite[0] = m_nDeskWidth - 400;
            AnimaStartSideBarSite[1] = 0;
            AnimaStartSideBarSite[2] = 400;
            AnimaStartSideBarSite[3] = m_nDeskHeight - connectTaskBarDbus();
            //结束位置坐标
            AnimaStopSidebarSite[0]  = m_nDeskWidth;
            AnimaStopSidebarSite[1]  = 0;
            AnimaStopSidebarSite[2]  = 400;
            AnimaStopSidebarSite[3]  = m_nDeskHeight  - connectTaskBarDbus();
        }
        break;
        case Widget::PanelUp: {
            qDebug() << "所在位置" << getPanelSite();
            //起始位置的坐标
            AnimaStartSideBarSite[0] = m_nDeskWidth - 400;
            AnimaStartSideBarSite[1] = connectTaskBarDbus();
            AnimaStartSideBarSite[2] = 400;
            AnimaStartSideBarSite[3] = m_nDeskHeight  - connectTaskBarDbus();
            //结束位置坐标
            AnimaStopSidebarSite[0]  = m_nDeskWidth;
            AnimaStopSidebarSite[1]  = connectTaskBarDbus();;
            AnimaStopSidebarSite[2]  = 400;
            AnimaStopSidebarSite[3]  = m_nDeskHeight - connectTaskBarDbus();
        }
        break;
        case Widget::PanelLeft: {
            qDebug() << "所在位置" << getPanelSite();
            //起始位置的坐标
            AnimaStartSideBarSite[0] = m_nDeskWidth - 400;
            AnimaStartSideBarSite[1] = 0;
            AnimaStartSideBarSite[2] = 400;
            AnimaStartSideBarSite[3] = m_nDeskHeight;
            //结束位置坐标
            AnimaStopSidebarSite[0]  = m_nDeskWidth;
            AnimaStopSidebarSite[1]  = 0;
            AnimaStopSidebarSite[2]  = 400;
            AnimaStopSidebarSite[3]  = m_nDeskHeight;
        }
        break;
        case Widget::PanelRight: {
            qDebug() << "所在位置" << getPanelSite();
            //起始位置的坐标
            AnimaStartSideBarSite[0] = m_nDeskWidth - connectTaskBarDbus() - 400;
            AnimaStartSideBarSite[1] = 0;
            AnimaStartSideBarSite[2] = 400;
            AnimaStartSideBarSite[3] = m_nDeskHeight;
            //结束位置坐标
            AnimaStopSidebarSite[0]  = m_nDeskWidth - connectTaskBarDbus();
            AnimaStopSidebarSite[1]  = 0;
            AnimaStopSidebarSite[2]  = 400;
            AnimaStopSidebarSite[3]  = m_nDeskHeight;
        }
        break;
        default:
        break;
    }

    m_pHideAnimation->setStartValue(QRect(AnimaStartSideBarSite[0], AnimaStartSideBarSite[1], AnimaStartSideBarSite[2], AnimaStartSideBarSite[3]));
    m_pHideAnimation->setEndValue(QRect(AnimaStopSidebarSite[0], AnimaStopSidebarSite[1], AnimaStopSidebarSite[2], AnimaStopSidebarSite[3]));
    m_pHideAnimation->start();
}

/* 当改变屏幕分辨率时重新获取屏幕分辨率 */
void Widget::onResolutionChanged(int argc)
{
    Q_UNUSED(argc);
    QDesktopWidget *deskWgt = QApplication::desktop();
    if (nullptr == deskWgt) {
        return;
    }

    QRect screenRect = deskWgt->screenGeometry();
    m_nDeskWidth = screenRect.width();
    m_nDeskHeight = screenRect.height() - connectTaskBarDbus();
    qInfo() << "screen width:" << m_nDeskWidth << ",height:" << m_nDeskHeight;
    //if screen resolution changed while sidebar is visiable, sidebar could be display at unexpected places

    if(true == m_bShowFlag)  //当展开时，才需要实时改变尺寸
    {
        this->setGeometry(m_nDeskWidth - 400,0,400,m_nDeskHeight);
    }
    return;
}

/* 当隐藏动画结束时需要将widget隐藏 */
void Widget::HideAnimationEndSlots()
{
    this->hide();
    return;
}

void Widget::onNewNotification()
{
    if(false == m_bShowFlag)  //当没展开时，来了新通知才提示
    {
        m_bFwinkleFlag = true;
        m_pTimer->start(500);
    }
    return;
}

void Widget::twinkle()
{
    if(true == m_bFwinkleFlag)
    {
        m_bFwinkleFlag = false;
        setIcon(TRAY_NULL_ICON);
    }
    else
    {
        m_bFwinkleFlag = true;
        setIcon(TRAY_ICON);
    }
}

/* 事件过滤器 */
bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj);
    Q_UNUSED(event);
    if (obj == this) {
        if (event->type() == QEvent::WindowDeactivate && true == m_bShowFlag) {
            qDebug() << "Widget::eventFilter 消失";
            hideAnimation();
            m_bShowFlag = false;
            return true;
        }
    }

    if (!isActiveWindow()) {
        activateWindow();
    }
    return false;
}

/* 重新绘制背景色 */
void Widget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);

    p.setBrush(QBrush(QColor("#131314")));
    p.setOpacity(0.4);
    p.setPen(Qt::NoPen);

    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.drawRoundedRect(opt.rect,0,0);
    p.drawRect(opt.rect);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Widget:: focusOutEvent(QFocusEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "退出窗口";
    hideAnimation();
    m_bShowFlag = false;
    return;
}
