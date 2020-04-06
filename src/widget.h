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
#include "clipboardpluginiface.h"
#include "sidebarSmallPluginInterface.h"
#include "realtimepropertyanimation.h"
#include "mostgrandwidget.h"

#define  TRAY_ICON           ":/data/images/kylin-tool-box.svg"
#define  TRAY_NULL_ICON      ":/data/images/kylin-tool-box-null.svg"

#define PANEL_DBUS_SERVICE "com.ukui.panel.desktop"
#define PANEL_DBUS_PATH "/"
#define PANEL_DBUS_INTERFACE "com.ukui.panel.desktop"

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
    void GetsAvailableAreaScreen();                                             //获取屏幕可用区域高度
    void MostGrandWidgetCoordinates();                                          //根据任务栏位置调整侧边栏位置
    void ModifyScreenNeeds();                                                   //修改屏幕分辨率或者主屏需要做的事情
    void InitializeHomeScreenGeometry();                                        //初始化主屏的X坐标


protected:
    void mousePressEvent(QMouseEvent *event);                                   //鼠标点击事件
    bool eventFilter(QObject *obj, QEvent *event);                              //设置过滤事件

private:
    //主界面
    QVBoxLayout*                m_pMainOuterBoxLayout;                          //主界面最外框布局器
    QWidget*                    m_pMainOuterWidget;                             //主界面最外框架部件
    QWidget*                    m_pMainOuterReplaceWidget;                      //主界面最外框架动画时替代部件

    QVBoxLayout*                m_pMainQVBoxLayout;                             //主界面垂直布局器
    QDBusInterface*             m_pServiceInterface;                            //获取任务栏的高度
    bool                        m_bShowFlag;                                    //控制托盘栏点击事件的标志位
    int                         m_nScreenWidth;                                 //屏幕分辨率的宽
    int                         m_nScreenHeight;                                //屏幕分辨率的高
    int                         m_nScreen_x;
    int                         m_nScreen_y;
    QObject*                    m_pNotificationPluginObject;                    //通知中心插件对象
    QObject*                    m_pclock_PluginObject;                          //闹钟插件第一次加载插件对象
    QObject*                    m_pfeedback_PluginObject;
    QObject*                    m_pnotebook_PluginObject;
    SidebarSmallPluginInterface *m_pclock_Plugin;                               //闹钟插件全局变量
    SidebarSmallPluginInterface *m_pPlugin_Plugin;                              //问题反馈全局变量
    SidebarSmallPluginInterface *m_pnotebookPluginObject;
    int                         m_nInitalXPosition;
    QTranslator                 *m_pTranslator;
    QPropertyAnimation          *m_pAnimationShowSidebarWidget;
    QPropertyAnimation          *m_pAnimationHideSidebarWidget;
    QDesktopWidget              *m_pDeskWgt;                                    //桌面问题

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
    void screenCountChangedSlots(int count);
};

#endif // WIDGET_H
