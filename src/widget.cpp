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
#include <QGuiApplication>
#include "customstyle.h"

extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);
double tranSparency = 0.7;

Widget::Widget(QWidget *parent) : QWidget (parent)
{
    /* 国际化 */
    initTranslation();

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
    initLayout();

    /* 加载通知中心插件 */
    if (false == loadNotificationPlugin())
        qWarning() << "Notification center plug-in failed to load";

    if (false == loadQuickOperationPlugin())
        qWarning() << "The shortcut panel failed to load";

    this->setLayout(m_pMainQVBoxLayout);

    /* 系统托盘栏显示 */
    createAction();
    createSystray();
    setIcon(QIcon::fromTheme("kylin-tool-box", QIcon(TRAY_ICON)));

    /* 安装事件过滤器 */
    installEventFilter(this);

    connect(qApp, &QApplication::paletteChanged, this, [=](){
        qDebug() << "系统画板变化";
    });
    /* 监听gsetting，修改所有窗口的字体 */
    setAllWidgetFont();

    if (QGSettings::isSchemaInstalled(UKUI_TRANSPARENCY_SETTING)) {
        m_pTransparency = new QGSettings(UKUI_TRANSPARENCY_SETTING);
    }

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
    qInfo() << "---------------------------主界面加载完毕---------------------------";
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
    if (nullptr == m_pNotificationPluginObject) {
        return false;
    }

    NotificationInterface* pNotificationPluginObject = qobject_cast<NotificationInterface*>(m_pNotificationPluginObject);
    if (nullptr == pNotificationPluginObject) {
        return false;
    }

    connect(m_pNotificationPluginObject, SIGNAL(Sig_onNewNotification()), this, SLOT(onNewNotification()));
    m_pMainQVBoxLayout->addWidget(pNotificationPluginObject->centerWidget(), 1);
    return true;
}

bool Widget::loadQuickOperationPlugin()
{
    QDir pluginsDir;
    static bool installed = (QCoreApplication::applicationDirPath() == QDir(("/usr/bin")).canonicalPath());

    if (installed)
        pluginsDir = QDir(PLUGIN_INSTALL_DIRS);
    else
        pluginsDir = QDir(qApp->applicationDirPath() + "/plugins/ukui-quick-operation-panel");

    pluginsDir.setFilter(QDir::Files);
    QPluginLoader pluginLoader(pluginsDir.absoluteFilePath("libshortcutPanel.so"));
    QObject *pPlugin = pluginLoader.instance();
    if (pPlugin == nullptr)
        return false;

    m_pShortCutPanelInterface = dynamic_cast<shortCutPanelInterface *>(pPlugin);
    QWidget* shortCutWidget = m_pShortCutPanelInterface->getShortCutPanelWidget();
    m_pMainQVBoxLayout->addWidget(shortCutWidget);
    return true;
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
    connect(trayIcon, &QSystemTrayIcon::activated, this, &Widget::iconActivated);
    trayIcon->setVisible(true);
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

void Widget::initTranslation()
{
    m_pTranslator = new QTranslator;
    if (m_pTranslator->load(QLocale(), QLatin1String("ukui-sidebar"), QLatin1String("_"), QLatin1String("/usr/share/ukui-sidebar")))
        QApplication::installTranslator(m_pTranslator);
    else
        qDebug() << "cannot load translator " << QLocale::system().name() << ".qm!";
}

void Widget::initLayout()
{
    m_pMainQVBoxLayout = new QVBoxLayout;
    m_pMainQVBoxLayout->setContentsMargins(8, 8, 8, 8);
    m_pMainQVBoxLayout->setSpacing(0);
    return;
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
    int  AnimaStartSideBarSite[4];                           //侧边栏动画开始位置
    int  AnimaStopSidebarSite[4];                            //侧边栏动画结束位置

    m_pPeonySite = getPanelSite();
    switch (m_pPeonySite)
    {
        case Widget::PanelDown :
            {
                //起始位置的坐标
                AnimaStartSideBarSite[0] = 408;
                AnimaStartSideBarSite[1] = 0;
                AnimaStartSideBarSite[2] = 408;
                AnimaStartSideBarSite[3] = m_nScreenHeight - connectTaskBarDbus() ;
                //结束位置坐标
                AnimaStopSidebarSite[0]  = 0;
                AnimaStopSidebarSite[1]  = 0;
                AnimaStopSidebarSite[2]  = 408;
                AnimaStopSidebarSite[3]  = m_nScreenHeight  - connectTaskBarDbus();
            }
            break;
        case Widget::PanelUp:
            {
                //起始位置的坐标
                AnimaStartSideBarSite[0] = 408;
                AnimaStartSideBarSite[1] = 0;
                AnimaStartSideBarSite[2] = 408;
                AnimaStartSideBarSite[3] = m_nScreenHeight  - connectTaskBarDbus();
                //结束位置坐标
                AnimaStopSidebarSite[0]  = 0;
                AnimaStopSidebarSite[1]  = 0;;
                AnimaStopSidebarSite[2]  = 408;
                AnimaStopSidebarSite[3]  = m_nScreenHeight - connectTaskBarDbus();
            }
            break;
        case Widget::PanelLeft:
            {
                //起始位置的坐标
                AnimaStartSideBarSite[0] = -408;
                AnimaStartSideBarSite[1] = 0;
                AnimaStartSideBarSite[2] = 408;
                AnimaStartSideBarSite[3] = m_nScreenHeight;
                //结束位置坐标
                AnimaStopSidebarSite[0]  = 0;
                AnimaStopSidebarSite[1]  = 0;
                AnimaStopSidebarSite[2]  = 408;
                AnimaStopSidebarSite[3]  = m_nScreenHeight;
            }
            break;
        case Widget::PanelRight:
            {
                //起始位置的坐标
                AnimaStartSideBarSite[0] = 408;
                AnimaStartSideBarSite[1] = 0;
                AnimaStartSideBarSite[2] = 408;
                AnimaStartSideBarSite[3] = m_nScreenHeight;
                //结束位置坐标
                AnimaStopSidebarSite[0]  = 0;
                AnimaStopSidebarSite[1]  = 0;
                AnimaStopSidebarSite[2]  = 408;
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
    QPainterPath path;
    if (m_pPeonySite == Widget::PanelDown
          || m_pPeonySite == Widget::PanelUp) {
        path.addRoundedRect(QRect(x + 8, 8, 392, m_nScreenHeight - connectTaskBarDbus() - 16), 12, 12);
    } else {
        path.addRoundedRect(QRect(x + 8, 8, 392, m_nScreenHeight - 16), 12, 12);
    }
    QRegion Region(path.toFillPolygon().toPolygon());
    mostGrandWidget::getInstancemostGrandWidget()->setProperty("blurRegion", Region);
    return;
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
                AnimaStartSideBarSite[2] = 408;
                AnimaStartSideBarSite[3] = m_nScreenHeight - connectTaskBarDbus();
                //结束位置坐标
                AnimaStopSidebarSite[0]  = 450;
                AnimaStopSidebarSite[1]  = 0;
                AnimaStopSidebarSite[2]  = 408;
                AnimaStopSidebarSite[3]  = m_nScreenHeight  - connectTaskBarDbus();
            }
            break;
        case Widget::PanelUp:
            {
                //起始位置的坐标
                AnimaStartSideBarSite[0] = 0;
                AnimaStartSideBarSite[1] = 0;
                AnimaStartSideBarSite[2] = 408;
                AnimaStartSideBarSite[3] = m_nScreenHeight  - connectTaskBarDbus();
                //结束位置坐标
                AnimaStopSidebarSite[0]  = 450;
                AnimaStopSidebarSite[1]  = 0;
                AnimaStopSidebarSite[2]  = 408;
                AnimaStopSidebarSite[3]  = m_nScreenHeight - connectTaskBarDbus();
            }
            break;
        case Widget::PanelLeft:
            {
                //起始位置的坐标
                AnimaStartSideBarSite[0] = 0;
                AnimaStartSideBarSite[1] = 0;
                AnimaStartSideBarSite[2] = 408;
                AnimaStartSideBarSite[3] = m_nScreenHeight;
                //结束位置坐标
                AnimaStopSidebarSite[0]  = -420;
                AnimaStopSidebarSite[1]  = 0;
                AnimaStopSidebarSite[2]  = 408;
                AnimaStopSidebarSite[3]  = m_nScreenHeight;
            }
            break;
        case Widget::PanelRight:
            {
                //起始位置的坐标
                AnimaStartSideBarSite[0] = 0;
                AnimaStartSideBarSite[1] = 0;
                AnimaStartSideBarSite[2] = 408;
                AnimaStartSideBarSite[3] = m_nScreenHeight;
                //结束位置坐标
                AnimaStopSidebarSite[0]  = 450;
                AnimaStopSidebarSite[1]  = 0;
                AnimaStopSidebarSite[2]  = 408;
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
    InitializeHomeScreenGeometry();
    return;
}

/* 主屏发生变化槽函数 */
void Widget::primaryScreenChangedSLot()
{
    qDebug() << "主屏发生变化";
    GetsAvailableAreaScreen();
    InitializeHomeScreenGeometry();
    return;
}

/* 屏幕数量改变时对应槽函数 */
void Widget::screenCountChangedSlots(int count)
{
    Q_UNUSED(count);
    qDebug() << "屏幕数量发生变化";
    GetsAvailableAreaScreen();
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

/* 过滤终端命令 */
void Widget::bootOptionsFilter(QString opt)
{
    if ((opt == "-s" || opt == "-show") && m_bShowFlag == false) {
        mostGrandWidget::getInstancemostGrandWidget()->hide();
        MostGrandWidgetCoordinates();
        mostGrandWidget::getInstancemostGrandWidget()->show();
        showAnimation();
        m_bShowFlag = true;
        setIcon(QIcon::fromTheme("kylin-tool-box", QIcon(TRAY_ICON)));
    }
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
}

/* 监听gsetting，修改所有的字体 */
void Widget::setAllWidgetFont()
{
    const QByteArray id("org.ukui.style");
        QGSettings * fontSetting = new QGSettings(id);
        connect(fontSetting, &QGSettings::changed,[=](QString key) {
            if ("systemFont" == key || "systemFontSize" ==key) {
                QFont font = this->font();
                for (auto widget : qApp->allWidgets()) {
                    widget->setFont(font);
                }
            }
        });
}

/* 根据任务栏位置调整侧边栏位置 */
void Widget::MostGrandWidgetCoordinates()
{
    switch (getPanelSite()) {
        case Widget::PanelDown :
            {
                mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetSize(408, m_nScreenHeight - connectTaskBarDbus());
                mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetCoordinates(m_nScreen_x + m_nScreenWidth - 408, m_nScreen_y);
            }
            break;
        case Widget::PanelUp:
            {
                mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetSize(408, m_nScreenHeight - connectTaskBarDbus()); \
                mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetCoordinates(m_nScreen_x + m_nScreenWidth - 408,  \
                                                                                             connectTaskBarDbus() \
                                                                                             + m_nScreen_y);
            }
            break;
        case Widget::PanelLeft:
            {
                mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetSize(408, m_nScreenHeight);
                mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetCoordinates(m_nScreen_x + connectTaskBarDbus(), m_nScreen_y);
            }
            break;
        case Widget::PanelRight:
            {
                mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetSize(408, m_nScreenHeight);
                mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetCoordinates(m_nScreen_x + m_nScreenWidth - 408 - connectTaskBarDbus(), \
                                                                                             m_nScreen_y);
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

/* 事件过滤器 */
bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == this) {
        if (event->type() == QEvent::WindowDeactivate && true == m_bShowFlag && true == m_bClipboardFlag) {
            mostGrandWidget::getInstancemostGrandWidget()->topLevelWidget()->setProperty("blurRegion", QRegion(QRect(1, 1, 1, 1)));
            hideAnimation();
            m_bShowFlag = false;
            return true;
        } else if (event->type() == QEvent::StyleChange) {
            return true;
        }
    }

    if (!isActiveWindow() && true == m_bShowFlag) {
        activateWindow();
    }
    return false;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    QPainterPath rectPath;
    rectPath.addRoundedRect(this->rect().adjusted(8, 8, -8, -8), 12, 12);

    QPixmap pixmap(this->rect().size());
    pixmap.fill(Qt::transparent);
    QPainter pixmapPainter(&pixmap);
    pixmapPainter.setRenderHint(QPainter::Antialiasing);
    pixmapPainter.setPen(Qt::transparent);
    pixmapPainter.setBrush(Qt::black);
    pixmapPainter.drawPath(rectPath);
    pixmapPainter.end();

    QImage img = pixmap.toImage();
    qt_blurImage(img, 10, false, false);


    pixmap = QPixmap::fromImage(img);
    QPainter pixmapPainter2(&pixmap);
    pixmapPainter2.setRenderHint(QPainter::Antialiasing);
    pixmapPainter2.setCompositionMode(QPainter::CompositionMode_Clear);
    pixmapPainter2.setPen(Qt::transparent);
    pixmapPainter2.setBrush(Qt::transparent);
    pixmapPainter2.drawPath(rectPath);

    p.drawPixmap(this->rect(), pixmap, pixmap.rect());
    QStyleOption *option = new QStyleOption();
    p.save();
    QColor color = option->palette.color(QPalette::Base);
    color.setAlphaF(tranSparency);
    p.fillPath(rectPath, color);
    p.restore();
}
