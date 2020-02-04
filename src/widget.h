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


#define  PNG_PATH           ":/data/images/kylin-tool-box.svg"

#define PANEL_DBUS_SERVICE "com.ukui.panel.desktop"
#define PANEL_DBUS_PATH "/"
#define PANEL_DBUS_INTERFACE "com.ukui.panel.desktop"

class QGroupBox;
class QGridLayout;
class QVBoxLayout;

enum {
    NumGridRows = 3,
    NumButtons = 4,
    NumListButton = 5
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);

    ~Widget();
    //主界面
    void showAnimation();                                                       //show动作
    void hideAnimation();                                                       //hide动作
    void ListenClipboardSignal();                                               //监听剪贴板发送的信号
    int  connectTaskBarDbus();                                                  //连接任务栏dbus接口，获取任务栏高度

    //系统托盘
    void createAction();                                                        //连接信号和槽函数，设置其动作;
    void createSystray();                                                       //设置menu界面、添加动作 和 创建sysytray实例
    void setIcon();                                                             //设置图标和提示信息;
    void iconActivated(QSystemTrayIcon::ActivationReason reason);               //获取点击事件
    bool loadNotificationPlugin();                                              //加载通知中心插件

protected:
    void mousePressEvent(QMouseEvent *event);                                   //鼠标点击事件
    bool eventFilter(QObject *obj, QEvent *event);                              //设置过滤事件

private:
    //主界面
    QPropertyAnimation* m_pHideAnimation;                                       //隐藏动画对象
    QPropertyAnimation* m_pShowAnimation;                                       //展示动画对象
    QVBoxLayout*        m_pMainQVBoxLayout;                                     //主界面垂直布局器
    QDBusInterface*     m_pServiceInterface;                                      //获取任务栏的高度
    bool                m_bShowFlag;                                            //控制托盘栏点击事件的标志位
    int                 m_nScreenWidth;                                         //屏幕分辨率的宽
    int                 m_nScreenHeight;                                        //屏幕分辨率的高

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

private slots :
    void onResolutionChanged(int);
    void HideAnimationEndSlots();

};

#endif // WIDGET_H
