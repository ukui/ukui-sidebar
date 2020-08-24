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
#include "sidebarpluginswidgets.h"
#include <stdio.h>
#include <QtDBus>
#include <QGuiApplication>
#include "customstyle.h"

double tranSparency = 0.7;

Widget::Widget(QWidget *parent) : QWidget (parent)
{
    m_pTranslator = new QTranslator;
    if (m_pTranslator->load(QLocale(), QLatin1String("ukui-sidebar"), QLatin1String("_"), QLatin1String("/usr/share/ukui-sidebar")))
        QApplication::installTranslator(m_pTranslator);
    else
        qDebug() << "cannot load translator " << QLocale::system().name() << ".qm!";

    m_bShowFlag = false;
    m_bClipboardFlag = true;

    /* 初始化与任务栏交互的dbus和gsetting */
    initPanelDbusGsetting();

    /* 初始化屏幕 */
    initDesktopPrimary();

    /* 初始化主屏的X坐标 */
    InitializeHomeScreenGeometry();

    /* 获取屏幕可用高度区域 */
    GetsAvailableAreaScreen();

    /* 初始化动画 */
    initAimation();

    /* 主界面显示 */
    m_pMainQVBoxLayout = new QVBoxLayout;
    m_pMainQVBoxLayout->setContentsMargins(0, 0, 0, 0);
    m_pMainQVBoxLayout->setSpacing(0);

    /* 初始化剪贴板与小插件界面 */
    sidebarPluginsWidgets::initPluginsWidgets();
    sidebarPluginsWidgets::getInstancePluinsWidgets()->loadSmallPlugins();

    /* 加载通知中心插件 */
    if (false == loadNotificationPlugin())
        qDebug() << "Notification center plug-in failed to load";

    /* 加载剪贴板插件, 将剪贴板插件加入到sidebarPluginsWidgets的GroupBox中 */
    if (ListenClipboardSignal())
        qDebug() << "The clipboard plug-in failed to load";

    this->setLayout(m_pMainQVBoxLayout);

    /* 系统托盘栏显示 */
    createAction();
    createSystray();
    setIcon(QIcon::fromTheme("kylin-tool-box", QIcon(TRAY_ICON)));

    /* 安装事件过滤器 */
    installEventFilter(this);

    /* 监听gsetting，修改所有窗口的字体 */
    setAllWidgetFont();

    /* 将托盘栏图标和widget联系起来 */
    connect(trayIcon, &QSystemTrayIcon::activated, this, &Widget::iconActivated);
    trayIcon->setVisible(true);

    if (QGSettings::isSchemaInstalled(UKUI_TRANSPARENCY_SETTING)) {
        qDebug() << "分配gsetting值";
        m_pTransparency = new QGSettings(UKUI_TRANSPARENCY_SETTING);
    }

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
    qInfo() << "---------------------------主界面加载完毕---------------------------";

    m_pUpdateSmallPluginsWidget = new QTimer();
    connect(m_pUpdateSmallPluginsWidget, &QTimer::timeout, this, &Widget::updateSmallPluginsClipboardWidget);
}

Widget::~Widget()
{

}

//加载通知中心插件
bool Widget::loadNotificationPlugin()
{
    QDir pluginsDir;
    static bool installed = (QCoreApplication::applicationDirPath() == QDir(("/usr/bin")).canonicalPath());

    if (installed)
        pluginsDir = QDir(PLUGIN_INSTALL_DIRS);
    else
        pluginsDir = QDir(qApp->applicationDirPath() + "/plugins/ukui-sidebar-notification");

    pluginsDir.setFilter(QDir::Files);
    QPluginLoader pluginLoader(pluginsDir.absoluteFilePath("libnotification_plugin.so"));

    m_pNotificationPluginObject = pluginLoader.instance();
    if(nullptr == m_pNotificationPluginObject) {
        return false;
    }

    NotificationInterface* pNotificationPluginObject = qobject_cast<NotificationInterface*>(m_pNotificationPluginObject);
    if(nullptr == pNotificationPluginObject) {
        return false;
    }

    connect(m_pNotificationPluginObject, SIGNAL(Sig_onNewNotification()), this, SLOT(onNewNotification()));
    m_pMainQVBoxLayout->addWidget(pNotificationPluginObject->centerWidget(), 1);
    return true;
}

//加载剪贴板插件
int Widget::ListenClipboardSignal()
{
    QDir pluginsDir;
    static bool installed = (QCoreApplication::applicationDirPath() == QDir(("/usr/bin")).canonicalPath());

    if (installed)
        pluginsDir = QDir(PLUGIN_INSTALL_DIRS);
    else
        pluginsDir = QDir(qApp->applicationDirPath() + "/plugins/ukui-sidebar-clipboard");

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

    sidebarPluginsWidgets::getInstancePluinsWidgets()->m_pClipboardWidget = m_pSidebarClipboard->getClipbaordGroupBox();   /* 获取剪贴板的Widget指针; */
    sidebarPluginsWidgets::getInstancePluinsWidgets()->initCliboardAnimation();                     /* 初始化剪贴板动画 */
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
    Open = new QAction(QObject::tr("Open"), this);
    connect(Open, &QAction::triggered, this, &Widget::OpenSidebarSlots);

    OpenSetUp = new QAction(QIcon::fromTheme("application-menu", QIcon(SETTING_ICON)), QObject::tr("Set up notification center"), this);
    connect(OpenSetUp, &QAction::triggered, this, &Widget::OpenControlCenterSettings);
}

//添加动作和创建 systray实例
void Widget::createSystray()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->setProperty("iconHighlightEffectMode", 1);
    if (trayIconMenu == nullptr) {
        qWarning() << "分配空间trayIconMenu失败";
        return ;
    }
    trayIconMenu->addAction(Open);
    trayIconMenu->addAction(OpenSetUp);

    trayIcon = new QSystemTrayIcon(this);

    if (nullptr == trayIcon) {
        qWarning()<< "分配空间trayIcon失败";
        return ;
    }
    trayIcon->setContextMenu(trayIconMenu);
}

//设置托盘栏的图标
void Widget::setIcon(QIcon icon)
{
    trayIcon->setIcon(icon);
    setWindowIcon(icon);
    trayIcon->setToolTip(tr("Sidebar"));
}

//设置activated信号
void Widget::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    //获取透明度
    if (QGSettings::isSchemaInstalled(UKUI_TRANSPARENCY_SETTING)){
        if (m_pTransparency->keys().contains("transparency")) {
            tranSparency = m_pTransparency->get("transparency").toDouble();
        }
    }
    qDebug() << "获取的透明度为:" << tranSparency;
    switch (reason) {
        case QSystemTrayIcon::Trigger: {
            if (m_bShowFlag) {
                mostGrandWidget::getInstancemostGrandWidget()->topLevelWidget()->setProperty("blurRegion", QRegion(QRect(1, 1, 1, 1)));
                hideAnimation();
            } else {
                mostGrandWidget::getInstancemostGrandWidget()->hide();
                MostGrandWidgetCoordinates();
                mostGrandWidget::getInstancemostGrandWidget()->show();
                showAnimation();
                m_bShowFlag = true;
                setIcon(QIcon::fromTheme("kylin-tool-box", QIcon(TRAY_ICON)));
            }
            break;
        }
    case QSystemTrayIcon::Context:
        if (m_bShowFlag) {
            trayIconMenu->hide();  //先隐藏菜单栏，不让其显示出来， 然后将sidebar隐藏
            mostGrandWidget::getInstancemostGrandWidget()->topLevelWidget()->setProperty("blurRegion", QRegion(QRect(1, 1, 1, 1)));
            hideAnimation();
        }
        break;
   default:
        break;
    }
}

/* 初始化屏幕分辨率 */
void Widget::initDesktopPrimary()
{
    /* 监听屏幕分辨率是否变化 主频是否有变化 初始化屏幕宽高 和主屏起始X坐标值 */
    m_pDeskWgt = QApplication::desktop();
    connect(QApplication::primaryScreen(), &QScreen::geometryChanged, this, &Widget::onResolutionChanged);
    connect(m_pDeskWgt, &QDesktopWidget::primaryScreenChanged, this, &Widget::primaryScreenChangedSLot);
    connect(m_pDeskWgt, &QDesktopWidget::screenCountChanged, this, &Widget::screenCountChangedSlots);

}

void Widget::initPanelDbusGsetting()
{
    /* 链接任务栏Dbus接口，获取任务栏高度和位置 */
    m_pServiceInterface = new QDBusInterface(PANEL_DBUS_SERVICE, PANEL_DBUS_PATH, PANEL_DBUS_INTERFACE, QDBusConnection::sessionBus());
    m_pServiceInterface->setTimeout(2147483647);

    /* 链接任务栏Dbus接口，获取任务栏点击信号 */
    QDBusConnection::sessionBus().connect(QString(), QString("/taskbar/click"), \
                                          "com.ukui.panel.plugins.taskbar", "sendToUkuiDEApp", this, SLOT(ClickPanelHideSidebarSlots(void)));

    /* 链接任务栏dgsetting接口 */
    if(QGSettings::isSchemaInstalled(UKUI_PANEL_SETTING))
        m_pPanelSetting = new QGSettings(UKUI_PANEL_SETTING);
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

//获取屏幕的可用区域高度和宽度
void Widget::GetsAvailableAreaScreen()
{
    //如果取不到任务栏的高度,还是优先获取桌面分辨率,可用区域
    if ((0 == connectTaskBarDbus()) && (0 == getPanelSite())) {
        QScreen* pScreen = QGuiApplication::primaryScreen();
        QRect DeskSize = pScreen->availableGeometry();
        m_nScreenWidth = DeskSize.width();                      //桌面分辨率的宽
        m_nScreenHeight = DeskSize.height();                    //桌面分辨率的高
    } else {
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
    if (m_nScreenHeight >= 600 && m_nScreenHeight <= 768) {
        return m_nScreenHeight/2 - connectTaskBarDbus() - 60;
    } else if (m_nScreenHeight >= 900 && m_nScreenHeight <= 1080) {
        return m_nScreenHeight/3;
    } else if (m_nScreenHeight >= 1200 && m_nScreenHeight <= 2160) {
        return m_nScreenHeight/4;
    } else {
        return m_nScreenHeight/2 - connectTaskBarDbus();
    }
}

void Widget::initAimation()
{
    m_pAnimationShowSidebarWidget = new QPropertyAnimation(this, "geometry");
    m_pAnimationHideSidebarWidget = new QPropertyAnimation(this, "geometry");

    connect(m_pAnimationHideSidebarWidget, &QPropertyAnimation::finished, this, &Widget::hideAnimationFinish);
    connect(m_pAnimationShowSidebarWidget, &QPropertyAnimation::valueChanged, this, &Widget::showAnimationAction);
    connect(m_pAnimationShowSidebarWidget, &QPropertyAnimation::finished, this, &Widget::showAnimationFinish);
}

//动画展开
void Widget::showAnimation()
{
    NotificationInterface* pNotificationPluginObject = qobject_cast<NotificationInterface*>(m_pNotificationPluginObject);
    QWidget *widget = pNotificationPluginObject->centerWidget();
    QString sheet = QString("QWidget{background-color:rgba(19,19,20,%1);}").arg(tranSparency);
    widget->setStyleSheet(sheet);
    if (nullptr != pNotificationPluginObject && false == m_bfinish)
        pNotificationPluginObject->showNotification();       //当动画展开时给插件一个通知

    int  AnimaStartSideBarSite[4];                           //侧边栏动画开始位置
    int  AnimaStopSidebarSite[4];                            //侧边栏动画结束位置
    int clipboardhight = setClipBoardWidgetScaleFactor();
    sidebarPluginsWidgets::getInstancePluinsWidgets()->setClipboardWidgetSize(clipboardhight);      //设定剪贴板高度
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
                AnimaStartSideBarSite[0] = -400;
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

void Widget::showAnimationAction(const QVariant &value)
{
    QRect Rect = value.value<QRect>();
    int x = Rect.x();
    if (m_pPeonySite == Widget::PanelDown
          || m_pPeonySite == Widget::PanelUp) {
        mostGrandWidget::getInstancemostGrandWidget()->setProperty("blurRegion", QRegion(QRect(x, 0, 400, m_nScreenHeight - connectTaskBarDbus())));
    } else {
        mostGrandWidget::getInstancemostGrandWidget()->setProperty("blurRegion", QRegion(QRect(x, 0, 400, m_nScreenHeight)));
    }
}

void Widget::showAnimationFinish()
{
    if (m_bfinish) {
        mostGrandWidget::getInstancemostGrandWidget()->topLevelWidget()->setProperty("blurRegion", QRegion(QRect(1, 1, 1, 1)));
        hideAnimation();
        m_bfinish = false;
    }
    return;
}

/* 获取Getting值 */
void sidebarPluginsWidgets::getTransparencyValue(const QString key)
{
    if (key == "transparency") {
        tranSparency = m_pTransparency->get("transparency").toFloat();
        qDebug() << "获取到的值为----->" << tranSparency;
    }
    return;
}

//隐藏动画
void Widget::hideAnimation()
{
    m_bShowFlag = false;
    NotificationInterface* pNotificationPluginObject = qobject_cast<NotificationInterface*>(m_pNotificationPluginObject);
    if (nullptr != pNotificationPluginObject)
        pNotificationPluginObject->hideNotification();      //当动画隐藏时给插件一个通知

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
                AnimaStopSidebarSite[0]  = -400;
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
    return;
}

void Widget::hideAnimationFinish()
{
    mostGrandWidget::getInstancemostGrandWidget()->hide();
    return;
}

//当改变屏幕分辨率时重新获取屏幕分辨率
void Widget::onResolutionChanged(const QRect argc)
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
    return;
}

/* 屏幕数量改变时对应槽函数 */
void Widget::screenCountChangedSlots(int count)
{
    Q_UNUSED(count);
    qDebug() << "屏幕数量发生变化";
    GetsAvailableAreaScreen();
    ModifyScreenNeeds();
    InitializeHomeScreenGeometry();
    return;
}

/* 接受剪贴板信号，将bool值m_bClipboardFlag置为false; */
void Widget::ClipboardShowSlots()
{
    m_bClipboardFlag = false;
    return;
}

/* 接受剪贴板信号，将bool值m_bClipboardFlag置为true; */
void Widget::ClipboardHideSlots()
{
    m_bClipboardFlag = true;
    return;
}

/* 接受任务栏点击信号，当任务栏点击左键时，关闭任务栏 */
void Widget::ClickPanelHideSidebarSlots()
{
    mostGrandWidget::getInstancemostGrandWidget()->topLevelWidget()->setProperty("blurRegion", QRegion(QRect(1, 1, 1, 1)));
    hideAnimation();
    return;
}

/* 右键菜单打开侧边栏槽函数 */
void Widget::OpenSidebarSlots()
{
    mostGrandWidget::getInstancemostGrandWidget()->hide();
    MostGrandWidgetCoordinates();
    mostGrandWidget::getInstancemostGrandWidget()->show();
    showAnimation();
    m_bShowFlag = true;
    setIcon(QIcon::fromTheme("kylin-tool-box", QIcon(TRAY_ICON)));
    return;
}

/* 打开控制中心的通知中心 */
void Widget::OpenControlCenterSettings()
{
    QProcess p(0);
    p.startDetached("ukui-control-center -n");
    p.waitForStarted();
    return;
}

/* 修改屏幕分辨率或者主屏需要做的事情 */
void Widget::ModifyScreenNeeds()
{
    int clipboardhight = setClipBoardWidgetScaleFactor();
    sidebarPluginsWidgets::getInstancePluinsWidgets()->setClipboardWidgetSize(clipboardhight); //设定剪贴板高度
    return;
}

/* 初始化主屏的X坐标 */
void Widget::InitializeHomeScreenGeometry()
{
    QList<QScreen*> screen = QGuiApplication::screens();
    int count = m_pDeskWgt->screenCount();
    if (count > 1) {
        m_nScreen_x = screen[0]->geometry().x();
        m_nScreen_y = screen[0]->geometry().y();

    } else {
        m_nScreen_x = 0;
        m_nScreen_y = 0;
    }
    qDebug() << "偏移的x坐标" << m_nScreen_x;
    qDebug() << "偏移的Y坐标" << m_nScreen_y;
}

/* 监听gsetting，修改所有的字体 */
void Widget::setAllWidgetFont()
{
    const QByteArray id("org.ukui.style");
        QGSettings * fontSetting = new QGSettings(id);
        connect(fontSetting, &QGSettings::changed,[=](QString key){
            if ("systemFont" == key || "systemFontSize" ==key) {
                QFont font = this->font();
                for (auto widget : qApp->allWidgets()) {
                    widget->setFont(font);
                }
                emit sidebarPluginsWidgets::getInstancePluinsWidgets()->FontModifyComplete();
            }
        });
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
                emit m_pSidebarSignal->ClipboardPreviewSignal(400, m_nScreenHeight, m_nScreen_x + m_nScreenWidth - 400, m_nScreen_y, connectTaskBarDbus());
            }
            break;
        case Widget::PanelUp:
            {
                mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetSize(400, m_nScreenHeight - connectTaskBarDbus());
                mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetCoordinates(m_nScreen_x + m_nScreenWidth - 400, connectTaskBarDbus() + m_nScreen_y);
                emit m_pSidebarSignal->ClipboardPreviewSignal(400, m_nScreenHeight, m_nScreen_x + m_nScreenWidth - 400, connectTaskBarDbus() + m_nScreen_y, connectTaskBarDbus());
            }
            break;
        case Widget::PanelLeft:
            {
                mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetSize(400, m_nScreenHeight);
                mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetCoordinates(m_nScreen_x + connectTaskBarDbus(), m_nScreen_y);
                emit m_pSidebarSignal->ClipboardPreviewSignal(400, m_nScreenHeight, m_nScreen_x + connectTaskBarDbus() + 400 + 260, m_nScreen_y, 0);
                qDebug() << "当前 m_nScreen_x + m_nScreenWidth + connectTaskBarDbus()--》" << m_nScreen_x + connectTaskBarDbus() << "m_nScreen_y ----> "  << m_nScreen_y;

            }
            break;
        case Widget::PanelRight:
            {
                mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetSize(400, m_nScreenHeight);
                mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetCoordinates(m_nScreen_x + m_nScreenWidth - 400 - connectTaskBarDbus(), m_nScreen_y);
                emit m_pSidebarSignal->ClipboardPreviewSignal(400, m_nScreenHeight, m_nScreen_x + m_nScreenWidth - 400 - connectTaskBarDbus(), m_nScreen_y, 0);
            }
            break;
        default:
            break;
    }
}

//当没展开时，来了新通知才提示
void Widget::onNewNotification()
{
    if (false == m_bShowFlag) {
        setIcon(QIcon::fromTheme("kylin-tool-box-null", QIcon(TRAY_NULL_ICON)));
    }
    return;
}

/* 切换主题时，定时器槽函数 */
void Widget::updateSmallPluginsClipboardWidget()
{
    ModifyScreenNeeds();
    m_pUpdateSmallPluginsWidget->stop();
}

/* 事件过滤器 */
bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == this) {
        if (event->type() == QEvent::WindowDeactivate && true == m_bShowFlag && true == m_bClipboardFlag) {
            qDebug() << "Widget::eventFilter 消失";
            mostGrandWidget::getInstancemostGrandWidget()->topLevelWidget()->setProperty("blurRegion", QRegion(QRect(1, 1, 1, 1)));
            hideAnimation();
            m_bShowFlag = false;
            return true;
        } else if (event->type() == QEvent::StyleChange) {
            m_pUpdateSmallPluginsWidget->start(200);
            sidebarPluginsWidgets::getInstancePluinsWidgets()->setButtonFont();
            return true;
        }
    }


    if (!isActiveWindow() && true == m_bShowFlag) {
        activateWindow();
    }
    return false;
}
