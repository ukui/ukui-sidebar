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
#include "clock_interface.h"
#include <stdio.h>
#include <QtDBus>
#include "customstyle.h"


Widget::Widget(QWidget *parent) : QWidget (parent)
{
    m_bShowFlag = false;
    m_bFwinkleFlag = true;

    //监听屏幕分辨率是否变化
    QDesktopWidget* desk = QApplication::desktop();
    connect(desk, SIGNAL(resized(int)), this, SLOT(onResolutionChanged(int)));

    m_pServiceInterface = new QDBusInterface(PANEL_DBUS_SERVICE, PANEL_DBUS_PATH, PANEL_DBUS_INTERFACE, QDBusConnection::sessionBus());
    m_pServiceInterface->setTimeout(2147483647);

    //主界面最外框布局器
    m_pMainOuterBoxLayout = new QVBoxLayout;
    m_pMainOuterBoxLayout->setContentsMargins(0,0,0,0);
    m_pMainOuterBoxLayout->setSpacing(0);

    //主界面最外框架部件
    m_pMainOuterWidget = new QWidget(this);
    m_pMainOuterWidget->setStyleSheet("QWidget#MainOuterWidget{background:rgba(255, 255, 0, 0);}");
    m_pMainOuterReplaceWidget = new QWidget(this);
    m_pMainOuterReplaceWidget->setStyleSheet("background:transparent;");
    m_pMainOuterReplaceWidget->setVisible(false);

    //主界面显示
    m_pMainQVBoxLayout = new QVBoxLayout;
    m_pMainQVBoxLayout->setContentsMargins(0,0,0,0);
    m_pMainQVBoxLayout->setSpacing(0);

    /* 初始化剪贴板与小插件界面 */
    sidebarPluginsWidgets::initPluginsWidgets();

    if(loadnotebookPlugin())
    {
        qDebug() << "loadnotebookPlugin";
        connect(sidebarPluginsWidgets::getInstancePluinsWidgets()->m_pNotebookButton, &QToolButton::clicked, this, [=](){
            m_pnotebookPluginObject->show();
        });
    }

    /* load Feedback Plugins */
    if(loadfeedbackPlugin())
    {
        connect(sidebarPluginsWidgets::getInstancePluinsWidgets()->m_pFeedbackButtom, &QToolButton::clicked, this,[=](){
            m_pPlugin_Plugin->show();
        });
        qDebug() << "feedback插件加";
    }

    //加载闹钟插件
    if (loadClockPlugin()) {
        connect(sidebarPluginsWidgets::getInstancePluinsWidgets()->m_pAlarmClockButton, &QToolButton::clicked, this, [=]() {
            m_pclock_Plugin->show();
            });
    }

    //加载通知中心插件
    if(false == loadNotificationPlugin())
    {
        qDebug() << "通知中心插件加载失败";
    }

    //加载剪贴板插件, 将剪贴板插件加入到sidebarPluginsWidgets的GroupBox中
    if (ListenClipboardSignal()) {
        qDebug() << "剪贴板插件加载失败";
    }

    m_pMainOuterWidget->setLayout(m_pMainQVBoxLayout);
    this->setLayout(m_pMainOuterBoxLayout);

    //系统托盘栏显示
    createAction();
    createSystray();
    setIcon(TRAY_ICON);

    //安装事件过滤器
    installEventFilter(this);

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

/* load Notebook Plugins */
bool Widget::loadnotebookPlugin()
{

    QDir pluginsDir("/usr/lib/ukui-sidebar/sidebarNotebook");
    QPluginLoader pluginLoader(pluginsDir.absoluteFilePath("libukui_notebook.so"));

    m_pnotebook_PluginObject = pluginLoader.instance();

    if(nullptr == m_pnotebook_PluginObject)
    {
        qDebug() <<"notebook plugin loader failed";
        return false;
    }

    m_pnotebookPluginObject = qobject_cast<nood_bookInterface*>(m_pnotebook_PluginObject);
    if(nullptr == m_pnotebookPluginObject)
    {
        return false;
    }
    return true;
}

//加载feedback
bool Widget::loadfeedbackPlugin()
{

    QDir pluginsDir("/usr/lib/ukui-sidebar/sidebar_feedbackPlugin_plugins");
    QPluginLoader pluginLoader(pluginsDir.absoluteFilePath("libfeedback.so"));

    m_pfeedback_PluginObject = pluginLoader.instance();

    if(nullptr == m_pfeedback_PluginObject)
    {
        return false;
    }

    m_pPlugin_Plugin = qobject_cast<FeedbackInterface*>(m_pfeedback_PluginObject);
    if(nullptr == m_pPlugin_Plugin)
    {
        return false;
    }
    connect(m_pfeedback_PluginObject, SIGNAL(feedback_ification()), this, SLOT(onNewNotification()));

    return true;
}

//加载闹钟插件
bool Widget::loadClockPlugin()
{

    QDir pluginsDir("/usr/lib/ukui-sidebar/sidebaralarm");
    QPluginLoader pluginLoader(pluginsDir.absoluteFilePath("libClock_deamon.so"));

    m_pclock_PluginObject = pluginLoader.instance();

    if(nullptr == m_pclock_PluginObject)
    {
        return false;
    }

    m_pclock_Plugin = qobject_cast<ClockInterface*>(m_pclock_PluginObject);
    if(nullptr == m_pclock_Plugin)
    {
        return false;
    }
    connect(m_pclock_PluginObject, SIGNAL(Clock_ification()), this, SLOT(onNewNotification()));
    return true;
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
    PluginInterface* pPluginInterface = PluginManager::getInstance()->m_PluginInterfaceHash.value("ClipBoard");
    m_pSidebarClipboard = dynamic_cast<ClipboardInterface *>(pPluginInterface);                     //获取剪贴版插件指针;
    if (nullptr == m_pSidebarClipboard) {
        qWarning() << "剪贴板插件插件加载失败";
        return 1;
    }
    m_pSidebarSignal = m_pSidebarClipboard->createClipSignal();                                     //获取剪贴板的信号类指针
    /* 点击剪贴板空白区域时，隐藏侧边栏 */
    connect(m_pSidebarSignal, &SidebarClipBoardSignal::ClipboardHideSignal, this, [=]() {
        hideAnimation();
    });

    sidebarPluginsWidgets::getInstancePluinsWidgets()->m_pClipboardWidget = m_pSidebarClipboard->getClipbaordGroupBox();   //获取剪贴板的Groubox指针;
    GetsAvailableAreaScreen();                               //获取屏幕可用高度区域
    int clipboardhight = setClipBoardWidgetScaleFactor();
    qDebug() << "剪贴板高度" << clipboardhight;
    sidebarPluginsWidgets::getInstancePluinsWidgets()->setClipboardWidgetSize(clipboardhight); //设定剪贴板高度
    sidebarPluginsWidgets::getInstancePluinsWidgets()->AddPluginWidgetInterface();       //将下半部分所有控件加入到sidebarPluginsWidgets中
    m_pMainQVBoxLayout->addWidget( sidebarPluginsWidgets::getInstancePluinsWidgets(), 0);

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
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);

    qApp->setStyleSheet("QToolTip{border:1px solid rgba(255, 255, 255, 0.2); background-color: #1A1A1A; color:#FFFFFF; padding:2px; border-radius:6px; font-size:14px;}");

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
    trayIcon->setToolTip("侧边栏");
}

//设置activated信号
void Widget::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::Trigger:
        {
            if (m_bShowFlag)
            {
                qDebug() << "Widget::iconActivated 隐藏";
                hideAnimation();
            } else
            {
                qDebug() << "Widget::iconActivated 展开";
                showAnimation();
                m_bShowFlag = true;
                m_pTimer->stop();                               //当侧边栏展开时，停止闪烁定时器，并且设置有图标的托盘图标
                setIcon(TRAY_ICON);
            }
            break;
        }
        case QSystemTrayIcon::DoubleClick:
        {
            showAnimation();
            m_bShowFlag = true;
            m_pTimer->stop();                                   //当侧边栏展开时，停止闪烁定时器，并且设置有图标的托盘图标
            setIcon(TRAY_ICON);
            break;
        }
        default:
            break;
    }
}

//链接任务栏dbus获取高度的接口
int Widget::connectTaskBarDbus()
{
    QDBusMessage msg = m_pServiceInterface->call("GetPanelSize", QVariant("Hight"));
    int panelHight = msg.arguments().at(0).toInt();
    qDebug() << "panelHight" << panelHight;
    return panelHight;
}

//获取任务栏状态位置下上左右
int Widget::getPanelSite()
{
    QDBusMessage msg = m_pServiceInterface->call("GetPanelPosition", QVariant("Site"));
    int PanelSite = msg.arguments().at(0).toInt();
    qDebug() << "panel所在的位置" << PanelSite;
    return PanelSite;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        hideAnimation();
    }
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
        QDesktopWidget *deskWgt = QApplication::desktop();
        QRect screenRect = deskWgt->screenGeometry();
        m_nScreenWidth = screenRect.width();
        m_nScreenHeight = screenRect.height();
    }
}

/* 设定剪贴板高度 */
int Widget::setClipBoardWidgetScaleFactor()
{
    int x , y;
    x = m_nScreenWidth;
    y = m_nScreenHeight;
    if ((x >= 800 && x <= 1280)&&(y >= 600 && y <= 720)) {
        qDebug() << "800 <= x <= 1280 && 600 <= y <= 720 ";
        return m_nScreenHeight/2 - connectTaskBarDbus();
    } else if ((x >= 1280 && x <= 2048)&&(y >= 900 && y <= 1024)) {
        qDebug() << "1280 <= x <= 2048 && 900 <= y <= 1024";
        return m_nScreenHeight/3;
    } else if ((x >= 1920 && x <= 3840)&&(y >= 1200 && y <= 2160)) {
        qDebug() << "1920 <= x 3840 && y >= 1200 && y <= 2160";
        return m_nScreenHeight/4;
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

    GetsAvailableAreaScreen();                               //获取屏幕可用高度区域
    int clipboardhight = setClipBoardWidgetScaleFactor();
    qDebug() << "剪贴板高度" << clipboardhight;
    sidebarPluginsWidgets::getInstancePluinsWidgets()->setClipboardWidgetSize(clipboardhight); //设定剪贴板高度
    int  AnimaStartSideBarSite[4];                           //侧边栏动画开始位置
    int  AnimaStopSidebarSite[4];                            //侧边栏动画结束位置
    switch (getPanelSite())
    {
        case Widget::PanelDown :
            {
                //起始位置的坐标
                AnimaStartSideBarSite[0] = m_nScreenWidth;
                AnimaStartSideBarSite[1] = 0;
                AnimaStartSideBarSite[2] = 400;
                AnimaStartSideBarSite[3] = m_nScreenHeight - connectTaskBarDbus();
                //结束位置坐标
                AnimaStopSidebarSite[0]  = m_nScreenWidth - 400;
                AnimaStopSidebarSite[1]  = 0;
                AnimaStopSidebarSite[2]  = 400;
                AnimaStopSidebarSite[3]  = m_nScreenHeight  - connectTaskBarDbus();
            }
            break;
        case Widget::PanelUp:
            {
                //起始位置的坐标
                AnimaStartSideBarSite[0] = m_nScreenWidth;
                AnimaStartSideBarSite[1] = connectTaskBarDbus();
                AnimaStartSideBarSite[2] = 400;
                AnimaStartSideBarSite[3] = m_nScreenHeight  - connectTaskBarDbus();
                //结束位置坐标
                AnimaStopSidebarSite[0]  = m_nScreenWidth - 400;
                AnimaStopSidebarSite[1]  = connectTaskBarDbus();;
                AnimaStopSidebarSite[2]  = 400;
                AnimaStopSidebarSite[3]  = m_nScreenHeight - connectTaskBarDbus();
            }
            break;
        case Widget::PanelLeft:
            {
                //起始位置的坐标
                AnimaStartSideBarSite[0] = m_nScreenWidth;
                AnimaStartSideBarSite[1] = 0;
                AnimaStartSideBarSite[2] = 400;
                AnimaStartSideBarSite[3] = m_nScreenHeight;
                //结束位置坐标
                AnimaStopSidebarSite[0]  = m_nScreenWidth - 400;
                AnimaStopSidebarSite[1]  = 0;
                AnimaStopSidebarSite[2]  = 400;
                AnimaStopSidebarSite[3]  = m_nScreenHeight;
            }
            break;
        case Widget::PanelRight:
            {
                //起始位置的坐标
                AnimaStartSideBarSite[0] = m_nScreenWidth - connectTaskBarDbus();
                AnimaStartSideBarSite[1] = 0;
                AnimaStartSideBarSite[2] = 400;
                AnimaStartSideBarSite[3] = m_nScreenHeight;
                //结束位置坐标
                AnimaStopSidebarSite[0]  = m_nScreenWidth - 400 - connectTaskBarDbus();
                AnimaStopSidebarSite[1]  = 0;
                AnimaStopSidebarSite[2]  = 400;
                AnimaStopSidebarSite[3]  = m_nScreenHeight;

            }
            break;
        default:
            break;
    }

    m_nInitalXPosition =  AnimaStartSideBarSite[0];
    this->setGeometry(AnimaStartSideBarSite[0], AnimaStartSideBarSite[1], 0, AnimaStartSideBarSite[3]);
    m_pMainOuterReplaceWidget->setGeometry(0, 0, 0, AnimaStopSidebarSite[3]);
    m_pMainOuterReplaceWidget->setVisible(true);
    m_pMainOuterBoxLayout->addWidget(m_pMainOuterReplaceWidget);
    m_pMainOuterWidget->setGeometry(0, 0, 400, AnimaStopSidebarSite[3]);

    RealtimePropertyAnimation* pAnimation = new RealtimePropertyAnimation(m_pMainOuterWidget, "geometry");
    pAnimation->setDuration(400);
    connect(pAnimation, SIGNAL(Sig_currentRect(int, int, int, int)), this, SLOT(updateAnimationPosition(int, int, int, int)));
    connect(pAnimation, SIGNAL(finished()), this, SLOT(showAnimationFinish()));

    pAnimation->setStartValue(QRect(AnimaStartSideBarSite[0], AnimaStartSideBarSite[1], 400, AnimaStartSideBarSite[3]));
    pAnimation->setEndValue(QRect(AnimaStopSidebarSite[0], AnimaStopSidebarSite[1], 400, AnimaStopSidebarSite[3]));
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);

}

void Widget::updateAnimationPosition(int x1, int y1, int x2, int y2)
{
    this->setGeometry(x1, y1, m_nInitalXPosition - x1, y2);
    m_pMainOuterReplaceWidget->setFixedSize(m_nInitalXPosition - x1, y2);

}

void Widget::showAnimationFinish()
{
    m_pMainOuterBoxLayout->removeWidget(m_pMainOuterReplaceWidget);
    m_pMainOuterReplaceWidget->setVisible(false);
    m_pMainOuterBoxLayout->addWidget(m_pMainOuterWidget);
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
                AnimaStartSideBarSite[0] = m_nScreenWidth - 400;
                AnimaStartSideBarSite[1] = 0;
                AnimaStartSideBarSite[2] = 400;
                AnimaStartSideBarSite[3] = m_nScreenHeight - connectTaskBarDbus();
                //结束位置坐标
                AnimaStopSidebarSite[0]  = m_nScreenWidth;
                AnimaStopSidebarSite[1]  = 0;
                AnimaStopSidebarSite[2]  = 400;
                AnimaStopSidebarSite[3]  = m_nScreenHeight  - connectTaskBarDbus();
            }
            break;
        case Widget::PanelUp:
            {
                //起始位置的坐标
                AnimaStartSideBarSite[0] = m_nScreenWidth - 400;
                AnimaStartSideBarSite[1] = connectTaskBarDbus();
                AnimaStartSideBarSite[2] = 400;
                AnimaStartSideBarSite[3] = m_nScreenHeight  - connectTaskBarDbus();
                //结束位置坐标
                AnimaStopSidebarSite[0]  = m_nScreenWidth;
                AnimaStopSidebarSite[1]  = connectTaskBarDbus();;
                AnimaStopSidebarSite[2]  = 400;
                AnimaStopSidebarSite[3]  = m_nScreenHeight - connectTaskBarDbus();
            }
            break;
        case Widget::PanelLeft:
            {
                //起始位置的坐标
                AnimaStartSideBarSite[0] = m_nScreenWidth - 400;
                AnimaStartSideBarSite[1] = 0;
                AnimaStartSideBarSite[2] = 400;
                AnimaStartSideBarSite[3] = m_nScreenHeight;
                //结束位置坐标
                AnimaStopSidebarSite[0]  = m_nScreenWidth;
                AnimaStopSidebarSite[1]  = 0;
                AnimaStopSidebarSite[2]  = 400;
                AnimaStopSidebarSite[3]  = m_nScreenHeight;
            }
            break;
        case Widget::PanelRight:
            {
                //起始位置的坐标
                AnimaStartSideBarSite[0] = m_nScreenWidth - connectTaskBarDbus() - 400;
                AnimaStartSideBarSite[1] = 0;
                AnimaStartSideBarSite[2] = 400;
                AnimaStartSideBarSite[3] = m_nScreenHeight;
                //结束位置坐标
                AnimaStopSidebarSite[0]  = m_nScreenWidth - connectTaskBarDbus();
                AnimaStopSidebarSite[1]  = 0;
                AnimaStopSidebarSite[2]  = 400;
                AnimaStopSidebarSite[3]  = m_nScreenHeight;
            }
            break;
        default:
            break;
    }

    m_pMainOuterBoxLayout->removeWidget(m_pMainOuterWidget);
    m_pMainOuterReplaceWidget->setGeometry(0, 0, 400, AnimaStopSidebarSite[3]);
    m_pMainOuterReplaceWidget->setVisible(true);
    m_pMainOuterBoxLayout->addWidget(m_pMainOuterReplaceWidget);

    //设置hide动画
    RealtimePropertyAnimation* pAnimation = new RealtimePropertyAnimation(m_pMainOuterWidget, "geometry");
    pAnimation->setDuration(300);
    connect(pAnimation, SIGNAL(Sig_currentRect(int, int, int, int)), this, SLOT(updateAnimationPosition(int, int, int, int)));
    connect(pAnimation, SIGNAL(finished()), this, SLOT(hideAnimationFinish()));

    pAnimation->setStartValue(QRect(AnimaStartSideBarSite[0], AnimaStartSideBarSite[1], 400, AnimaStartSideBarSite[3]));
    pAnimation->setEndValue(QRect(AnimaStopSidebarSite[0], AnimaStopSidebarSite[1], 400, AnimaStopSidebarSite[3]));
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void Widget::hideAnimationFinish()
{
    m_pMainOuterBoxLayout->removeWidget(m_pMainOuterReplaceWidget);
    m_pMainOuterReplaceWidget->setVisible(false);
}

//当改变屏幕分辨率时重新获取屏幕分辨率
void Widget::onResolutionChanged(int argc)
{
    Q_UNUSED(argc);
    QDesktopWidget *deskWgt = QApplication::desktop();
    if (nullptr == deskWgt)
    {
        return;
    }

    QRect screenRect = deskWgt->screenGeometry();
    m_nScreenWidth = screenRect.width();
    m_nScreenHeight = screenRect.height() - connectTaskBarDbus();
    qInfo() << "screen width:" << m_nScreenWidth << ",height:" << m_nScreenHeight;

    //当展开时，才需要实时改变尺寸
    if(true == m_bShowFlag)
    {
        this->setGeometry(m_nScreenWidth - 400,0,400,m_nScreenHeight);
    }
    return;
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
    if (obj == this)
    {
        if (event->type() == QEvent::WindowDeactivate && true == m_bShowFlag)
        {
            qDebug() << "事件类型" << event->type();
            qDebug() << "Widget::eventFilter 消失";
            hideAnimation();
            m_bShowFlag = false;
            return true;
        }
    }

    if (!isActiveWindow())
    {
        activateWindow();
    }
    return false;
}
