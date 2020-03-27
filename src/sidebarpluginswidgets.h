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
#ifndef SIDEBARPLUGINSWIDGETS_H
#define SIDEBARPLUGINSWIDGETS_H

#define  KYLIN_ALARM_CLACK_ICON      ":/data/images/kylin-alarm-clock.svg"
#define  KYLIN_NOTEBOOK              ":/data/images/kylin-notebook.svg"
#define  KYLIN_FEEDBACK              ":/data/images/kylin-feedback.png"
#define  KYLIN_SIDEBAR_SMALL_PLUGINS ":/data/qss/SidebarSmallPlugins.css"
#define  KYLIN_STATE_CLIPBOARD       1
#define  KYLIN_STATE_SMALL_PLUGINS   2
#define  KYLIN_PLUGINS_NUM           8
#include <QtWidgets>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QToolButton>
#include "smallpluginsbutton.h"
#include "smallpluginsmanage.h"
#include "mostgrandwidget.h"
class sidebarPluginsWidgets : public QWidget
{
    Q_OBJECT
public:
    explicit sidebarPluginsWidgets(QWidget *parent = nullptr);
    ~sidebarPluginsWidgets();
    static sidebarPluginsWidgets* getInstancePluinsWidgets();
    static void initPluginsWidgets();
    void AddPluginWidgetInterface();
    void initUpGroupBoxButton();                                  //上半部分 剪贴板 小插件 俩按钮 groupBox初始化布局
    void initUnGroupBox();                                        //下半部分 剪贴板的界面  小插件按钮详情界面 初始化
    void initLableBackgroundAnimation();                          //初始化动画
    void setClipboardButtonBackgroundIsBlue();                    //设置侧边栏按钮背景色为蓝色
    void setSmallPluginsButtonBackgroudIsBlue();                  //设置小插件按钮背景色为蓝色
    void setClipboardButtonBackgroundIsBlank();                   //设置侧边栏按钮背景色为空白
    void setSmallPluginsButtonBackgroudIsBlank();                 //设置小插件按钮背景色为空白
    void setClipboardWidgetSize(int ClipHight);                   //设置此窗口的大小
    void loadSmallPlugins();                                      //加载小插件，放置到sidebar界面


    QVBoxLayout *m_pWidgetOutVLayout;                             //最外层布局
    QHBoxLayout *m_pGrouBoxUpButtonHLayout;                       //GroupBox中Button中的布局
    QGridLayout *m_pGroupBoxUnSmallPluginsGLayout;                //闹钟，便签本布局

    QWidget     *m_pButtonWidget;                                 //放置按钮Box
    QWidget     *m_pClipboardWidget;                              //放置剪贴板的Box
    QWidget     *m_pPluginsButtonWidget;                          //放置小插件按钮Box

    QPushButton      *m_pBlueBackgroundButton;                    //蓝色背景块
    SmallPluginsButton *m_pClipboardButton;                       //剪贴板 界面显示按钮
    SmallPluginsButton *m_pSidebarPluginButton;                   //插件 界面显示按钮
    QToolButton *m_pNotebookButton;                               //笔记本 按钮
    QToolButton *m_pAlarmClockButton;                             //闹钟  按钮
    QToolButton *m_pFeedbackButtom;                               //用户反馈按钮

    QPropertyAnimation *m_pAnimationLeftRight;
    QPropertyAnimation *m_pAnimationRightLeft;

    //状态机
    QStateMachine *m_pMachine;                                    //状态机
    QState *m_pClipBoardState;                                    //剪贴板状态
    QState *m_pSmallPluginsState;                                 //小插件状态
    bool    m_pBoolStates;                                        //第一次初始化状态机bool值
    bool    resizeFlagOne;                                        //第一次初始化状态机bool值
    bool    ClipBoardBool;                                        //剪贴板修改屏幕分辨率bool值
    bool    SmallPluginsBool;                                     //插件按钮修改屏幕分辨率bool值
    int     m_statusFlag;                                         //状态机位置
    int     flagnumClipboardState;

signals:

private slots:
    void m_pClipBoardStateSlots();
    void m_pSmallPluginsStateSlots();
protected:
    void paintEvent(QPaintEvent *);

};

#endif // SIDEBARPLUGINSWIDGETS_H
