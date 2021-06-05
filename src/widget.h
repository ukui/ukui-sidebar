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


#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include <QDBusInterface>
#include <QPropertyAnimation>
#include <QDBusPendingCallWatcher>
#include <QScreen>
#include <QGSettings>
#include <QGuiApplication>
#include <QPalette>
#include <QStyleOption>
#include "clipboardpluginiface.h"
#include "sidebarSmallPluginInterface.h"
#include "mostgrandwidget.h"
#include <stdlib.h>
#include <stdio.h>

#define  TRAY_ICON           ":/data/images/kylin-tool-box.svg"
#define  TRAY_NULL_ICON      ":/data/images/kylin-tool-box-null.svg"
#define  SETTING_ICON        ":/data/images/application-menu.svg"

#define PANEL_DBUS_SERVICE "com.ukui.panel.desktop"
#define PANEL_DBUS_PATH "/"
#define PANEL_DBUS_INTERFACE "com.ukui.panel.desktop"
#define UKUI_TRANSPARENCY_SETTING "org.ukui.control-center.personalise"
#define UKUI_PANEL_SETTING "org.ukui.panel.settings"

#define ENV_X11       "x11"
#define ENV_WAYLAND   "wayland"
#define ENV_XDG_SESSION_TYPE "XDG_SESSION_TYPE"

#define DBUS_NAME       "org.ukui.SettingsDaemon"
#define DBUS_PATH       "/org/ukui/SettingsDaemon/wayland"
#define DBUS_INTERFACE  "org.ukui.SettingsDaemon.wayland"

class QGroupBox;
class QGridLayout;
class QVBoxLayout;

class Widget : public QWidget
{
    Q_OBJECT

    //申明该类有D-BUS服务接口
    Q_CLASSINFO("D-Bus Interface", "com.ukui.panel.sidebar.value")

public:
    explicit Widget(QWidget *parent = nullptr);

    ~Widget();
    enum PanelStatePosition
    {
        PanelDown = 0,
        PanelUp,
        PanelLeft,
        PanelRight
    };
    //主界面
    void initTrayIcon();                                                        //初始化托盘
    void startBackgroundFunction();                                             //初始化功能
    void timerHandle();                                                         //定时器处理函数
    void clickTrayFunction(QSystemTrayIcon::ActivationReason reason);           //托盘点击处理函数
    void initTranslation();                                                     // 初始化翻译
    void initAimation();                                                        // 初始化动画
    void initOsSiteXY();                                                        // 初始化使用qt接口初始化接口
    void showAnimation();                                                       // show动作
    void hideAnimation();                                                       // hide动作
    void initDesktopPrimary();                                                  // 初始化分辨率和信号连接
    void initPanelDbusGsetting();                                               // 初始化与任务栏gsetting和dbus
    int  ListenClipboardSignal();                                               // 监听剪贴板发送的信号
    int  connectTaskBarDbus();                                                  // 连接任务栏dbus接口，获取任务栏高度
    bool initHuaWeiDbus();                                                      // 初始化华为990专用dbus
    int  getScreenGeometry(QString methodName);                                 // 华为990获取屏幕高度
    int  getPanelSite();                                                        // 获取任务栏位置
    int  setClipBoardWidgetScaleFactor();                                       // 获取通知中心下半部分高度比例系数


    //系统托盘
    void createAction();                                                        // 连接信号和槽函数，设置其动作;
    void createSystray();                                                       // 设置menu界面、添加动作 和 创建sysytray实例
    void setIcon(QIcon icon);                                                   // 设置图标和提示信息;
    void iconActivated(QSystemTrayIcon::ActivationReason reason);               // 获取点击事件
    bool loadNotificationPlugin();                                              // 加载通知中心插件
    void ModifyScreenNeeds();                                                   // 修改屏幕分辨率或者主屏需要做的事情
    void GetsAvailableAreaScreen();                                             // 获取屏幕可用区域高度
    void MostGrandWidgetCoordinates();                                          // 根据任务栏位置调整侧边栏位置
    void InitializeHomeScreenGeometry();                                        // 初始化主屏的X坐标
    void setAllWidgetFont();                                                    // 监听gsetting，修改所有窗口的字体
    bool m_bfinish;
    bool backgroundFunctionStatus = true;                                       //ture :未加载 false 已加载
    bool oneshut = true;
    bool startShowSidebarstatus =true;


protected:
    bool eventFilter(QObject *obj, QEvent *event);                              // 设置过滤事件

private:
    //主界面
    QVBoxLayout*                m_pMainQVBoxLayout;                             // 主界面垂直布局器
    QDBusInterface*             m_pServiceInterface;                            // 获取任务栏的高度
    QDBusInterface*             m_pDbusXrandInter=nullptr;                              // 华为990dbus接口
    bool                        m_bHWdbusExit;                                  // 华为dbus接口是否存在
    bool                        m_bShowFlag = false;                            // 控制托盘栏点击事件的标志位
    bool                        m_bClipboardFlag = true;                        // 剪贴板编辑框打开和关闭时控制侧边栏是否关闭
    bool                        m_winFlag = false;
    int                         m_nScreenWidth;                                 // 屏幕分辨率的宽
    int                         m_nScreenHeight;                                // 屏幕分辨率的高
    int                         m_nScreen_x;                                    // 主屏的起始坐标X
    int                         m_nScreen_y;                                    // 主屏的起始坐标Y
    int                         m_pPeonySite;                                   // 任务栏位置
    QTimer *startFunctionTimer;
    QTimer *startShowSidebar;

    QObject*                    m_pNotificationPluginObject;                    // 通知中心插件对象

    QTranslator                 *m_pTranslator;
    QPropertyAnimation          *m_pAnimationShowSidebarWidget;
    QPropertyAnimation          *m_pAnimationHideSidebarWidget;
    QDesktopWidget              *m_pDeskWgt;                                    // 桌面问题
    QGSettings                  *m_pPanelSetting = nullptr;

    //快捷操作面板
    ClipboardInterface*         m_pSidebarClipboard;                            // 侧边栏剪贴板指针
    SidebarClipBoardSignal*     m_pSidebarSignal;                               // 剪贴板通信类

    //系统托盘
    QSystemTrayIcon*            trayIcon;
    QMenu*                      trayIconMenu;
    QAction*                    Open;
    QAction*                    OpenSetUp;

    QGSettings                  *m_pTransparency;                               // 插件的界面的透明度

private slots :
    void onResolutionChanged(const QRect argc);                                 // 当改变屏幕分辨率时重新获取屏幕分辨率
    void onNewNotification();                                                   // 当没展开时，来了新通知才提示
    void hideAnimationFinish();                                                 // 隐藏动画完成
    void showAnimationAction(const QVariant &value);                            // 展开动画开始
    void showAnimationFinish();
    void primaryScreenChangedSLot();                                            // 主屏发生变化
    void ClipboardShowSlots();                                                  // 接受剪贴板信号，将boll值m_bClipboardFlag置为false;
    void ClipboardHideSlots();                                                  // 接受剪贴板信号，将boll值m_bClipboardFlag置为true;
    void screenCountChangedSlots(int count);                                    // 屏幕数量改变时对应槽函数
    void OpenSidebarSlots();                                                    // 打开侧边栏
    void OpenControlCenterSettings();                                           // 打开控制中心的通知中心
    void ClickPanelHideSidebarSlots();                                          // 左键点击任务栏时隐藏侧边栏
    void updateSmallPluginsClipboardWidget();                                   // 切换主题时，定时器槽函数
    void bootOptionsFilter(QString opt);                                        // 过滤当前的终端命令
    void XkbEventsPress(const QString &keycode);                                // 键盘按键按下事件
    void XkbEventsRelease(const QString &keycode);                              // 键盘按键弹出事件
    void priScreenChanged(int x, int y, int width, int height);                 // hw990屏幕分辨率变化后

Q_SIGNALS:
    void testssss();
};

#endif // WIDGET_H
