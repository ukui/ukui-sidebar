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
#include "clipboardpluginiface.h"
#include "sidebarSmallPluginInterface.h"
#include "realtimepropertyanimation.h"
#include "mostgrandwidget.h"

#define  TRAY_ICON           ":/data/images/kylin-tool-box.svg"
#define  TRAY_NULL_ICON      ":/data/images/kylin-tool-box-null.svg"

#define PANEL_DBUS_SERVICE "com.ukui.panel.desktop"
#define PANEL_DBUS_PATH "/"
#define PANEL_DBUS_INTERFACE "com.ukui.panel.desktop"

#define UKUI_PANEL_SETTING "org.ukui.panel.settings"

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
    void showAnimation();                                                       //show动作
    void hideAnimation();                                                       //hide动作
    int  ListenClipboardSignal();                                               //监听剪贴板发送的信号
    int  connectTaskBarDbus();                                                  //连接任务栏dbus接口，获取任务栏高度
    int  getPanelSite();                                                        //获取任务栏位置
    int  setClipBoardWidgetScaleFactor();                                       //获取通知中心下半部分高度比例系数

    //系统托盘
    void createAction();                                                        //连接信号和槽函数，设置其动作;
    void createSystray();                                                       //设置menu界面、添加动作 和 创建sysytray实例
    void setIcon(QString strIcon);                                              //设置图标和提示信息;
    void iconActivated(QSystemTrayIcon::ActivationReason reason);               //获取点击事件
    bool loadNotificationPlugin();                                              //加载通知中心插件
    bool loadClockPlugin();                                                     //加载闹钟插件
    bool loadfeedbackPlugin();                                                  //加载用户反馈程序
    bool loadnotebookPlugin();
    void ModifyScreenNeeds();                                                   //修改屏幕分辨率或者主屏需要做的事情
    void GetsAvailableAreaScreen();                                             //获取屏幕可用区域高度
    void MostGrandWidgetCoordinates();                                          //根据任务栏位置调整侧边栏位置
    void InitializeHomeScreenGeometry();                                        //初始化主屏的X坐标


protected:
    void mousePressEvent(QMouseEvent *event);                                   //鼠标点击事件
    void mouseMoveEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);                              //设置过滤事件

private:
    //主界面
    QVBoxLayout*                m_pMainOuterBoxLayout;                          //主界面最外框布局器

    QVBoxLayout*                m_pMainQVBoxLayout;                             //主界面垂直布局器
    QDBusInterface*             m_pServiceInterface;                            //获取任务栏的高度
    bool                        m_bShowFlag;                                    //控制托盘栏点击事件的标志位
    bool                        m_bClipboardFlag;                               //剪贴板编辑框打开和关闭时控制侧边栏是否关闭
    int                         m_nScreenWidth;                                 //屏幕分辨率的宽
    int                         m_nScreenHeight;                                //屏幕分辨率的高
    int                         m_nScreen_x;                                    //主屏的起始坐标X
    int                         m_nScreen_y;                                    //主屏的起始坐标Y

    QObject*                    m_pNotificationPluginObject;                    //通知中心插件对象

    SidebarSmallPluginInterface *m_pclock_Plugin;                               //闹钟插件全局变量
    SidebarSmallPluginInterface *m_pPlugin_Plugin;                              //问题反馈全局变量
    SidebarSmallPluginInterface *m_pnotebookPluginObject;
    int                         m_nInitalXPosition;
    QTranslator                 *m_pTranslator;
    QPropertyAnimation          *m_pAnimationShowSidebarWidget;
    QPropertyAnimation          *m_pAnimationHideSidebarWidget;
    QDesktopWidget              *m_pDeskWgt;                                    //桌面问题
    QGSettings                  *m_pPanelSetting = nullptr;

    //快捷操作面板
    ClipboardInterface*         m_pSidebarClipboard;                            //侧边栏剪贴板指针
    SidebarClipBoardSignal*     m_pSidebarSignal;                               //剪贴板通信类

    //系统托盘
    QSystemTrayIcon*            trayIcon;
    QMenu*                      trayIconMenu;
    QAction*                    minimizeAction;
    QAction*                    maximizeAction;
    QAction*                    restoreAction;
    QAction*                    quitAction;
    QTimer*                     m_pTimer;                                       //新通知闪烁定时器
    bool                        m_bFwinkleFlag;                                 //新通知闪烁标志

private slots :
    void onResolutionChanged(int);                                              //当改变屏幕分辨率时重新获取屏幕分辨率
    void onNewNotification();                                                   //当没展开时，来了新通知才提示
    void twinkle();                                                             //新消息闪烁设置
    void updateAnimationPosition(int, int, int, int);                           //更新动画坐标动态
    void showAnimationFinish();                                                 //展开动画完成
    void hideAnimationFinish();                                                 //隐藏动画完成
    void showAnimationAction(const QVariant &value);                            //展开动画开始
    void primaryScreenChangedSLot();                                            //主屏发生变化
    void ClipboardShowSlots();                                                  //接受剪贴板信号，将boll值m_bClipboardFlag置为false;
    void ClipboardHideSlots();                                                  //接受剪贴板信号，将boll值m_bClipboardFlag置为true;
    void screenCountChangedSlots(int count);                                    //屏幕数量改变时对应槽函数
};

#endif // WIDGET_H
