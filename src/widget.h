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
#include <QDBusPendingCallWatcher>
#include "clipboardpluginiface.h"


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
    void ListenClipboardSignal();                                               //监听剪贴板发送的信号
    int  connectTaskBarDbus();                                                  //连接任务栏dbus接口，获取任务栏高度
    int  getPanelSite();                                                        //获取任务栏位置

    //系统托盘
    void createAction();                                                        //连接信号和槽函数，设置其动作;
    void createSystray();                                                       //设置menu界面、添加动作 和 创建sysytray实例
    void setIcon(QString strIcon);                                              //设置图标和提示信息;
    void iconActivated(QSystemTrayIcon::ActivationReason reason);               //获取点击事件
    bool loadNotificationPlugin();                                              //加载通知中心插件
    void GetsAvailableAreaScreen();                                             //获取屏幕可用区域高度

public slots :
    uint panelSizeChangeNotify(uint uId);


protected:
    void mousePressEvent(QMouseEvent *event);                                   //鼠标点击事件
    bool eventFilter(QObject *obj, QEvent *event);                              //设置过滤事件
    void paintEvent(QPaintEvent *);
    virtual void focusOutEvent(QFocusEvent *event);
private:
    //主界面
    QPropertyAnimation* m_pHideAnimation;                                       //隐藏动画对象
    QPropertyAnimation* m_pShowAnimation;                                       //展示动画对象
    QVBoxLayout*        m_pMainQVBoxLayout;                                     //主界面垂直布局器
    QDBusInterface*     m_pServiceInterface;                                    //获取任务栏的高度
    bool                m_bShowFlag;                                            //控制托盘栏点击事件的标志位
    int                 m_nDeskWidth;                                           //屏幕分辨率的宽
    int                 m_nDeskHeight;                                          //屏幕分辨率的高
    QObject*            m_pNotificationPluginObject;                            //通知中心插件对象

    //快捷操作面板
    QGroupBox*      m_pShortcutOperationGroupBox;                               //快捷操作面板中的主Group
    QGridLayout*    m_pShortcutOperationGridLayout;                             //快捷操作面板的总体GridLayout
    QListWidget*    m_pShortcutOperationListWidget;                             //快捷操作面板的总体GridLayout中右边的ListWidget
    ClipboardInterface *m_pSidebarClipboard;                                    //侧边栏剪贴板指针
    SidebarClipBoardSignal *m_pSidebarSignal;                                   //剪贴板通信类

    //系统托盘
    QSystemTrayIcon*    trayIcon;
    QMenu*              trayIconMenu;
    QAction*            minimizeAction;
    QAction*            maximizeAction;
    QAction*            restoreAction;
    QAction*            quitAction;
    QTimer*             m_pTimer;                           //新通知闪烁定时器
    bool                m_bFwinkleFlag;                     //新通知闪烁标志

private slots :
    void onResolutionChanged(int);
    void HideAnimationEndSlots();
    void onNewNotification();
    void twinkle();

};

#endif // WIDGET_H
