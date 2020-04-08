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
#include "realtimepropertyanimation.h"
#include "sidebarpluginswidgets.h"
#include <stdio.h>
#include <QtDBus>
#include <QGuiApplication>
#include "customstyle.h"


Widget::Widget(QWidget *parent) : QWidget (parent)
{
    m_pTranslator = new QTranslator;
    QLocale locale;
    if( locale.language() == QLocale::Chinese )                             /* 获取系统语言环境 */
    {
        m_pTranslator->load(QString(":/sidebartranslat/Sidebar_zh_CN.qm"));  /* 选择翻译文件 */
        QApplication::installTranslator(m_pTranslator);
    }
    m_bShowFlag = false;
    m_bClipboardFlag = true;
    m_bFwinkleFlag = true;

    m_pServiceInterface = new QDBusInterface(PANEL_DBUS_SERVICE, PANEL_DBUS_PATH, PANEL_DBUS_INTERFACE, QDBusConnection::sessionBus());
    m_pServiceInterface->setTimeout(2147483647);

    /* 链接任务栏dgsetting接口 */
    if(QGSettings::isSchemaInstalled(UKUI_PANEL_SETTING)){
        m_pPanelSetting = new QGSettings(UKUI_PANEL_SETTING);
        qDebug() << "m_pPanelSetting = new QGSettings(UKUI_PANEL_SETTING)";
    }

    /* 监听屏幕分辨率是否变化 主频是否有变化 初始化屏幕宽高 和主屏起始X坐标值 */
    m_pDeskWgt = QApplication::desktop();
    connect(m_pDeskWgt, SIGNAL(resized(int)), this, SLOT(onResolutionChanged(int)));
    connect(m_pDeskWgt, &QDesktopWidget::primaryScreenChanged, this, &Widget::primaryScreenChangedSLot);
    connect(m_pDeskWgt, &QDesktopWidget::screenCountChanged, this, &Widget::screenCountChangedSlots);

    InitializeHomeScreenGeometry();  /* 初始化主屏的X坐标 */
    GetsAvailableAreaScreen();       /* 获取屏幕可用高度区域 */

    /* 主界面最外框布局器 */
    m_pMainOuterBoxLayout = new QVBoxLayout;
    m_pMainOuterBoxLayout->setContentsMargins(0,0,0,0);
    m_pMainOuterBoxLayout->setSpacing(0);

    /* 主界面显示 */
    m_pMainQVBoxLayout = new QVBoxLayout;
    m_pMainQVBoxLayout->setContentsMargins(0,0,0,0);
    m_pMainQVBoxLayout->setSpacing(0);

    /* 初始化剪贴板与小插件界面 */
    sidebarPluginsWidgets::initPluginsWidgets();
    sidebarPluginsWidgets::getInstancePluinsWidgets()->loadSmallPlugins();

    /* 加载通知中心插件 */
    if (false == loadNotificationPlugin()) {
        qDebug() << "通知中心插件加载失败";
    }

    /* 加载剪贴板插件, 将剪贴板插件加入到sidebarPluginsWidgets的GroupBox中 */
    if (ListenClipboardSignal()) {
        qDebug() << "剪贴板插件加载失败";
    }

    this->setLayout(m_pMainQVBoxLayout);

    /* 系统托盘栏显示 */
    createAction();
    createSystray();
    setIcon(TRAY_ICON);

    /* 安装事件过滤器 */
    installEventFilter(this);

    m_pAnimationShowSidebarWidget = new QPropertyAnimation(this, "geometry");
    m_pAnimationHideSidebarWidget = new QPropertyAnimation(this, "geometry");

    connect(m_pAnimationHideSidebarWidget, &QPropertyAnimation::finished, this, &Widget::hideAnimationFinish);
    connect(m_pAnimationShowSidebarWidget, &QPropertyAnimation::finished, this, &Widget::showAnimationFinish);
    connect(m_pAnimationShowSidebarWidget, &QPropertyAnimation::valueChanged, this, &Widget::showAnimationAction);

    /* 将托盘栏图标和widget联系起来 */
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

    NotificationInterface* pNotificationPluginObject = qobject_cast<NotificationInterface*>(m_pNotificationPluginObject);
    if(nullptr == pNotificationPluginObject)
    {
        return false;
    }

    connect(m_pNotificationPluginObject, SIGNAL(Sig_onNewNotification()), this, SLOT(onNewNotification()));
    m_pMainQVBoxLayout->addWidget(pNotificationPluginObject->centerWidget(), 1);

    return true;
}

//加载剪贴板插件
int Widget::ListenClipboardSignal()
{
    QDir pluginsDir("/usr/lib/ukui-sidebar/sidebar_clipboardPlugin_plugins");
    pluginsDir.setFilter(QDir::Files);

    QPluginLoader pluginLoader(pluginsDir.absoluteFilePath("libclipboardPlugin.so"));
    QObject *pClipPlugin = pluginLoader.instance();

    m_pSidebarClipboard = dynamic_cast<ClipboardInterface *>(pClipPlugin);                          /* 获取剪贴版插件指针; */

    if (nullptr == m_pSidebarClipboard) {
        qWarning() << "剪贴板插件插件加载失败";
        return 1;
    }
    m_pSidebarSignal = m_pSidebarClipboard->createClipSignal();                                     /* 获取剪贴板的信号类指针 */
    /* 点击剪贴板空白区域时，隐藏侧边栏 */
    connect(m_pSidebarSignal, &SidebarClipBoardSignal::ClipboardHideSignal, this, [=]() {
        mostGrandWidget::getInstancemostGrandWidget()->topLevelWidget()->setProperty("blurRegion", QRegion(QRect(1, 1, 1, 1)));
        hideAnimation();
    });

    connect(m_pSidebarSignal, &SidebarClipBoardSignal::CLipBoardEditConfirmButtonSignal, this, &Widget::ClipboardHideSlots);

    connect(m_pSidebarSignal, &SidebarClipBoardSignal::ClipBoardWidgetEntryEditButtonSignal, this, &Widget::ClipboardShowSlots);

    sidebarPluginsWidgets::getInstancePluinsWidgets()->m_pClipboardWidget = m_pSidebarClipboard->getClipbaordGroupBox();   /* 获取剪贴板的Groubox指针; */
    int clipboardhight = setClipBoardWidgetScaleFactor();
    qDebug() << "剪贴板高度" << clipboardhight;
    sidebarPluginsWidgets::getInstancePluinsWidgets()->setClipboardWidgetSize(clipboardhight);      /* 设定剪贴板高度 */
    sidebarPluginsWidgets::getInstancePluinsWidgets()->AddPluginWidgetInterface();                  /* 将下半部分所有控件加入到sidebarPluginsWidgets中 */
    m_pMainQVBoxLayout->addWidget(sidebarPluginsWidgets::getInstancePluinsWidgets(), 0);
    return 0;
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
    if (trayIconMenu == nullptr)
    {
        qWarning() << "分配空间trayIconMenu失败";
        return ;
    }
//    trayIconMenu->addAction(minimizeAction);
//    trayIconMenu->addAction(maximizeAction);
//    trayIconMenu->addAction(restoreAction);
//    trayIconMenu->addSeparator();
//    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);

    if (nullptr == trayIcon)
    {
        qWarning()<< "分配空间trayIcon失败";
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
    trayIcon->setToolTip(tr("Sidebar"));
}

//设置activated信号
void Widget::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::Trigger:
        {
            if (m_bShowFlag) {
                qDebug() << "Widget::iconActivated 隐藏";
                mostGrandWidget::getInstancemostGrandWidget()->topLevelWidget()->setProperty("blurRegion", QRegion(QRect(1, 1, 1, 1)));
                hideAnimation();
            } else {
                mostGrandWidget::getInstancemostGrandWidget()->hide();
                MostGrandWidgetCoordinates();
                qDebug() << "Widget::iconActivated 展开";
                mostGrandWidget::getInstancemostGrandWidget()->show();
                showAnimation();
                m_bShowFlag = true;
//                m_pTimer->stop();                               //当侧边栏展开时，停止闪烁定时器，并且设置有图标的托盘图标
                setIcon(TRAY_ICON);
            }
            break;
        }
//        case QSystemTrayIcon::DoubleClick:
//        {
//            mostGrandWidget::getInstancemostGrandWidget()->hide();
//            MostGrandWidgetCoordinates();
//            qDebug() << "Widget::iconActivated 展开";
//            mostGrandWidget::getInstancemostGrandWidget()->show();
//            showAnimation();
//            m_bShowFlag = true;
//            m_pTimer->stop();                                   //当侧边栏展开时，停止闪烁定时器，并且设置有图标的托盘图标
//            setIcon(TRAY_ICON);
//            break;
//        }
        default:
            break;
    }
}

//链接任务栏dbus获取高度的接口
int Widget::connectTaskBarDbus()
{
    int panelHeight = 46;
    if (m_pPanelSetting != nullptr) {
        QStringList keys = m_pPanelSetting->keys();
        if (keys.contains("panelsize")) {
            panelHeight = m_pPanelSetting->get("panelsize").toInt();
        }
    } else {
        QDBusMessage msg = m_pServiceInterface->call("GetPanelSize", QVariant("Hight"));
        panelHeight = msg.arguments().at(0).toInt();
        return panelHeight;
    }
    return panelHeight;
}

//获取任务栏状态位置下上左右
int Widget::getPanelSite()
{
    int panelPosition = 0;
    if (m_pPanelSetting != nullptr) {
        QStringList keys = m_pPanelSetting->keys();
        if (keys.contains("panelposition")) {
            panelPosition = m_pPanelSetting->get("panelposition").toInt();
        }
    } else {
        QDBusMessage msg = m_pServiceInterface->call("GetPanelPosition", QVariant("Site"));
        panelPosition = msg.arguments().at(0).toInt();
    }
    qDebug() << "panel所在的位置" << panelPosition;
    return panelPosition;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        mostGrandWidget::getInstancemostGrandWidget()->topLevelWidget()->setProperty("blurRegion", QRegion(QRect(1, 1, 1, 1)));
        hideAnimation();
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint p_ab = event->globalPos();//整个桌面位置
    qDebug() << "个桌面位置 x-->" << p_ab.x() << "y-->" << p_ab.y();
}

//获取屏幕的可用区域高度和宽度
void Widget::GetsAvailableAreaScreen()
{
    //如果取不到任务栏的高度,还是优先获取桌面分辨率,可用区域
    if((0 == connectTaskBarDbus()) && (0 == getPanelSite()))
    {
        QScreen* pScreen = QGuiApplication::primaryScreen();
        QRect DeskSize = pScreen->availableGeometry();
        m_nScreenWidth = DeskSize.width();                      //桌面分辨率的宽
        m_nScreenHeight = DeskSize.height();                    //桌面分辨率的高
    }
    else
    {
        //如果取到任务栏的高度,则取屏幕分辨率的高度
        QRect screenRect = m_pDeskWgt->screenGeometry();
        m_nScreenWidth = screenRect.width();
        m_nScreenHeight = screenRect.height();
    }
    qDebug() << "主屏Width  --> " << m_nScreenWidth;
    qDebug() << "主屏Height --> " << m_nScreenHeight;
}

/* 设定剪贴板高度 */
int Widget::setClipBoardWidgetScaleFactor()
{
    if ((m_nScreenWidth >= 800 && m_nScreenWidth <= 1280)&&(m_nScreenHeight >= 600 && m_nScreenHeight <= 768)) {
        qDebug() << "800 <= x <= 1280 && 600 <= y <= 720 ";
        return m_nScreenHeight/2 - connectTaskBarDbus();
    } else if ((m_nScreenWidth >= 1280 && m_nScreenWidth <= 2048)&&(m_nScreenHeight >= 900 && m_nScreenHeight <= 1080)) {
        qDebug() << "1280 <= x <= 2048 && 900 <= y <= 1080";
        return m_nScreenHeight/3;
    } else if ((m_nScreenWidth >= 1920 && m_nScreenWidth <= 3840)&&(m_nScreenHeight >= 1200 && m_nScreenHeight <= 2160)) {
        qDebug() << "1920 <= x 3840 && y >= 1200 && y <= 2160";
        return m_nScreenHeight/4;
    } else {
        return m_nScreenHeight/2 - connectTaskBarDbus();
        qDebug() << "y <= 600 || y>= 2160";
    }
}

//动画展开
void Widget::showAnimation()
{
    NotificationInterface* pNotificationPluginObject = qobject_cast<NotificationInterface*>(m_pNotificationPluginObject);
    if(nullptr != pNotificationPluginObject)
    {
        pNotificationPluginObject->showNotification();       //当动画展开时给插件一个通知
    }
    int clipboardhight = setClipBoardWidgetScaleFactor();
    qDebug() << "剪贴板高度" << clipboardhight;
    sidebarPluginsWidgets::getInstancePluinsWidgets()->setClipboardWidgetSize(clipboardhight);      /* 设定剪贴板高度 */
    int  AnimaStartSideBarSite[4];                           //侧边栏动画开始位置
    int  AnimaStopSidebarSite[4];                            //侧边栏动画结束位置
    m_pPeonySite = getPanelSite();
    switch (m_pPeonySite)
    {
        case Widget::PanelDown :
            {
                //起始位置的坐标
                AnimaStartSideBarSite[0] = 400;
                AnimaStartSideBarSite[1] = 0;
                AnimaStartSideBarSite[2] = 400;
                AnimaStartSideBarSite[3] = m_nScreenHeight - connectTaskBarDbus();
                //结束位置坐标
                AnimaStopSidebarSite[0]  = 0;
                AnimaStopSidebarSite[1]  = 0;
                AnimaStopSidebarSite[2]  = 400;
                AnimaStopSidebarSite[3]  = m_nScreenHeight  - connectTaskBarDbus();
            }
            break;
        case Widget::PanelUp:
            {
                //起始位置的坐标
                AnimaStartSideBarSite[0] = 400;
                AnimaStartSideBarSite[1] = 0;
                AnimaStartSideBarSite[2] = 400;
                AnimaStartSideBarSite[3] = m_nScreenHeight  - connectTaskBarDbus();
                //结束位置坐标
                AnimaStopSidebarSite[0]  = 0;
                AnimaStopSidebarSite[1]  = 0;;
                AnimaStopSidebarSite[2]  = 400;
                AnimaStopSidebarSite[3]  = m_nScreenHeight - connectTaskBarDbus();
            }
            break;
        case Widget::PanelLeft:
            {
                //起始位置的坐标
                AnimaStartSideBarSite[0] = 400;
                AnimaStartSideBarSite[1] = 0;
                AnimaStartSideBarSite[2] = 400;
                AnimaStartSideBarSite[3] = m_nScreenHeight;
                //结束位置坐标
                AnimaStopSidebarSite[0]  = 0;
                AnimaStopSidebarSite[1]  = 0;
                AnimaStopSidebarSite[2]  = 400;
                AnimaStopSidebarSite[3]  = m_nScreenHeight;
            }
            break;
        case Widget::PanelRight:
            {
                //起始位置的坐标
                AnimaStartSideBarSite[0] = 400;
                AnimaStartSideBarSite[1] = 0;
                AnimaStartSideBarSite[2] = 400;
                AnimaStartSideBarSite[3] = m_nScreenHeight;
                //结束位置坐标
                AnimaStopSidebarSite[0]  = 0;
                AnimaStopSidebarSite[1]  = 0;
                AnimaStopSidebarSite[2]  = 400;
                AnimaStopSidebarSite[3]  = m_nScreenHeight;
            }
            break;
        default:
            break;
    }
    m_pAnimationShowSidebarWidget->setDuration(400);
    m_pAnimationShowSidebarWidget->setStartValue(QRect(AnimaStartSideBarSite[0], AnimaStartSideBarSite[1], AnimaStartSideBarSite[2], AnimaStartSideBarSite[3]));
    m_pAnimationShowSidebarWidget->setEndValue(QRect(AnimaStopSidebarSite[0], AnimaStopSidebarSite[1], AnimaStopSidebarSite[2], AnimaStopSidebarSite[3]));
    m_pAnimationShowSidebarWidget->start();
}

void Widget::showAnimationFinish()
{
}

void Widget::showAnimationAction(const QVariant &value)
{
    QRect Rect = value.value<QRect>();
    int x = Rect.x();
    if (m_pPeonySite == Widget::PanelDown || m_pPeonySite == Widget::PanelUp) {
        mostGrandWidget::getInstancemostGrandWidget()->setProperty("blurRegion", QRegion(QRect(x, 0, 400, m_nScreenHeight - connectTaskBarDbus())));
    }
    else {
        mostGrandWidget::getInstancemostGrandWidget()->setProperty("blurRegion", QRegion(QRect(x, 0, 400, m_nScreenHeight)));
    }
}

//隐藏动画
void Widget::hideAnimation()
{
    m_bShowFlag = false;
    NotificationInterface* pNotificationPluginObject = qobject_cast<NotificationInterface*>(m_pNotificationPluginObject);
    if(nullptr != pNotificationPluginObject)
    {
        pNotificationPluginObject->hideNotification();      //当动画隐藏时给插件一个通知
    }

    int  AnimaStartSideBarSite[4];                          //侧边栏动画开始位置
    int  AnimaStopSidebarSite[4];                           //侧边栏动画结束位置
    switch (getPanelSite()) {
        case Widget::PanelDown :
            {
                //起始位置的坐标
                AnimaStartSideBarSite[0] = 0;
                AnimaStartSideBarSite[1] = 0;
                AnimaStartSideBarSite[2] = 400;
                AnimaStartSideBarSite[3] = m_nScreenHeight - connectTaskBarDbus();
                //结束位置坐标
                AnimaStopSidebarSite[0]  = 450;
                AnimaStopSidebarSite[1]  = 0;
                AnimaStopSidebarSite[2]  = 400;
                AnimaStopSidebarSite[3]  = m_nScreenHeight  - connectTaskBarDbus();
            }
            break;
        case Widget::PanelUp:
            {
                //起始位置的坐标
                AnimaStartSideBarSite[0] = 0;
                AnimaStartSideBarSite[1] = 0;
                AnimaStartSideBarSite[2] = 400;
                AnimaStartSideBarSite[3] = m_nScreenHeight  - connectTaskBarDbus();
                //结束位置坐标
                AnimaStopSidebarSite[0]  = 450;
                AnimaStopSidebarSite[1]  = 0;
                AnimaStopSidebarSite[2]  = 400;
                AnimaStopSidebarSite[3]  = m_nScreenHeight - connectTaskBarDbus();
            }
            break;
        case Widget::PanelLeft:
            {
                //起始位置的坐标
                AnimaStartSideBarSite[0] = 0;
                AnimaStartSideBarSite[1] = 0;
                AnimaStartSideBarSite[2] = 400;
                AnimaStartSideBarSite[3] = m_nScreenHeight;
                //结束位置坐标
                AnimaStopSidebarSite[0]  = 450;
                AnimaStopSidebarSite[1]  = 0;
                AnimaStopSidebarSite[2]  = 400;
                AnimaStopSidebarSite[3]  = m_nScreenHeight;
            }
            break;
        case Widget::PanelRight:
            {
                //起始位置的坐标
                AnimaStartSideBarSite[0] = 0;
                AnimaStartSideBarSite[1] = 0;
                AnimaStartSideBarSite[2] = 400;
                AnimaStartSideBarSite[3] = m_nScreenHeight;
                //结束位置坐标
                AnimaStopSidebarSite[0]  = 450;
                AnimaStopSidebarSite[1]  = 0;
                AnimaStopSidebarSite[2]  = 400;
                AnimaStopSidebarSite[3]  = m_nScreenHeight;
            }
            break;
        default:
            break;
    }
    m_pAnimationHideSidebarWidget->setDuration(200);
    m_pAnimationHideSidebarWidget->setStartValue(QRect(AnimaStartSideBarSite[0], AnimaStartSideBarSite[1], AnimaStartSideBarSite[2], AnimaStartSideBarSite[3]));
    m_pAnimationHideSidebarWidget->setEndValue(QRect(AnimaStopSidebarSite[0], AnimaStopSidebarSite[1], AnimaStopSidebarSite[2], AnimaStopSidebarSite[3]));
    m_pAnimationHideSidebarWidget->start();
}

void Widget::hideAnimationFinish()
{
    mostGrandWidget::getInstancemostGrandWidget()->hide();
}

//当改变屏幕分辨率时重新获取屏幕分辨率
void Widget::onResolutionChanged(int argc)
{
    Q_UNUSED(argc);
    qDebug() << "屏幕分辨率发生变化";
    GetsAvailableAreaScreen();                               //获取屏幕可用高度区域
    ModifyScreenNeeds();                                     //修改屏幕分辨率或者主屏需要做的事情
    InitializeHomeScreenGeometry();
    return;
}

/* 主屏发生变化槽函数 */
void Widget::primaryScreenChangedSLot()
{
    qDebug() << "主屏发生变化";
    GetsAvailableAreaScreen();
    ModifyScreenNeeds();
    InitializeHomeScreenGeometry();
}

/* 屏幕数量改变时对应槽函数 */
void Widget::screenCountChangedSlots(int count)
{
    Q_UNUSED(count);
    qDebug() << "屏幕数量发生变化";
    GetsAvailableAreaScreen();
    ModifyScreenNeeds();
    InitializeHomeScreenGeometry();
}

/* 接受剪贴板信号，将boll值m_bClipboardFlag置为false; */
void Widget::ClipboardShowSlots()
{
    m_bClipboardFlag = false;
}

/* 接受剪贴板信号，将boll值m_bClipboardFlag置为true; */
void Widget::ClipboardHideSlots()
{
    m_bClipboardFlag = true;
}

/* 修改屏幕分辨率或者主屏需要做的事情 */
void Widget::ModifyScreenNeeds()
{
    int clipboardhight = setClipBoardWidgetScaleFactor();

    qDebug() << "剪贴板高度" << clipboardhight;
    sidebarPluginsWidgets::getInstancePluinsWidgets()->setClipboardWidgetSize(clipboardhight); //设定剪贴板高度

    /* 先将侧边栏show出来，改变一次状态机，将修改分辨率后，对布局的影响去掉 */
    mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetCoordinates(-500, 0);
    mostGrandWidget::getInstancemostGrandWidget()->setVisible(true);

    if (sidebarPluginsWidgets::getInstancePluinsWidgets()->m_statusFlag == KYLIN_STATE_CLIPBOARD) {
        sidebarPluginsWidgets::getInstancePluinsWidgets()->m_pSidebarPluginButton->SendSingal();
        sidebarPluginsWidgets::getInstancePluinsWidgets()->m_pClipboardButton->SendSingal();
        sidebarPluginsWidgets::getInstancePluinsWidgets()->ClipBoardBool = true;
    } else if (sidebarPluginsWidgets::getInstancePluinsWidgets()->m_statusFlag == KYLIN_STATE_SMALL_PLUGINS) {
        sidebarPluginsWidgets::getInstancePluinsWidgets()->m_pClipboardButton->SendSingal();
        sidebarPluginsWidgets::getInstancePluinsWidgets()->m_pSidebarPluginButton->SendSingal();
        sidebarPluginsWidgets::getInstancePluinsWidgets()->SmallPluginsBool = true;
    }
}

/* 初始化主屏的X坐标 */
void Widget::InitializeHomeScreenGeometry()
{
    QList<QScreen*> screen = QGuiApplication::screens();
    int count = m_pDeskWgt->screenCount();
    if (count > 1) {
//        m_nScreen_x = screen[0]->availableGeometry().x();
//        m_nScreen_y = screen[0]->availableGeometry().y();
        m_nScreen_x = screen[0]->geometry().x();
        m_nScreen_y = screen[0]->geometry().y();

    } else {
        m_nScreen_x = 0;
        m_nScreen_y = 0;
    }
    qDebug() << "偏移的x坐标" << m_nScreen_x;
    qDebug() << "偏移的Y坐标" << m_nScreen_y;
}

/* 根据任务栏位置调整侧边栏位置 */
void Widget::MostGrandWidgetCoordinates()
{
    switch (getPanelSite()) {
        case Widget::PanelDown :
            {
                mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetSize(400, m_nScreenHeight - connectTaskBarDbus());
                mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetCoordinates(m_nScreen_x + m_nScreenWidth - 400, m_nScreen_y);
                qDebug() << "m_nScreen_x + m_nScreenWidth - 400-->" << m_nScreen_x + m_nScreenWidth - 400 << "&&" << m_nScreen_x << "&&" << m_nScreenWidth;
            }
            break;
        case Widget::PanelUp:
            {
                mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetSize(400, m_nScreenHeight - connectTaskBarDbus());
                mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetCoordinates(m_nScreen_x + m_nScreenWidth - 400, connectTaskBarDbus() + m_nScreen_y);
            }
            break;
        case Widget::PanelLeft:
            {
                mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetSize(400, m_nScreenHeight);
                mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetCoordinates(m_nScreen_x + m_nScreenWidth - 400, m_nScreen_y);
                qDebug() << m_nScreen_x << m_nScreenWidth;
                qDebug() << "m_nScreen_x + m_nScreenWidth - 400" << m_nScreen_x + m_nScreenWidth - 400;
            }
            break;
        case Widget::PanelRight:
            {
                mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetSize(400, m_nScreenHeight);
                mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetCoordinates(m_nScreen_x + m_nScreenWidth - 400 - connectTaskBarDbus(), m_nScreen_y);
            }
            break;
        default:
            break;
    }
}

//当没展开时，来了新通知才提示
void Widget::onNewNotification()
{
    if(false == m_bShowFlag)
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
        m_pTimer->stop();
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
//    Q_UNUSED(obj);
//    Q_UNUSED(event);
    if (obj == this)
    {
        if (event->type() == QEvent::WindowDeactivate && true == m_bShowFlag && true == m_bClipboardFlag)
        {
            qDebug() << "Widget::eventFilter 消失";
            mostGrandWidget::getInstancemostGrandWidget()->topLevelWidget()->setProperty("blurRegion", QRegion(QRect(1, 1, 1, 1)));
            hideAnimation();
            m_bShowFlag = false;
            return true;
        } else if (event->type() == QEvent::StyleChange) {
            ModifyScreenNeeds();
        }
    }

    if (!isActiveWindow())
    {
        activateWindow();
    }
    return false;
}
