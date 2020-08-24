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
#include <glib.h>
#include <QToolButton>
#include <QStyle>
#include <QStackedWidget>
#include <QGSettings>
#include "smallpluginsbutton.h"
#include "smallpluginsmanage.h"
#include "mostgrandwidget.h"
#include "pluginstoolbutton.h"
#include "customstyleCleanPushbutton.h"
#include "customstyle.h"

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
    void initCliboardAnimation();                                 //初始化剪贴板动画类
    void initSmallPluginsAnimation();                             //初始化小插件动画类
    void setClipboardButtonBackgroundIsBlue();                    //设置侧边栏按钮背景色为蓝色
    void setSmallPluginsButtonBackgroudIsBlue();                  //设置小插件按钮背景色为蓝色
    void setClipboardButtonBackgroundIsBlank();                   //设置侧边栏按钮背景色为空白
    void setSmallPluginsButtonBackgroudIsBlank();                 //设置小插件按钮背景色为空白
    void setClipboardWidgetSize(int ClipHight);                   //设置此窗口的大小
    void loadSmallPlugins();                                      //加载小插件，放置到sidebar界面
    void setButtonFont();

    QString getAppIcon(QString desktopfp);                        //解析desktop文件，获取插件图标
    QString getAppName(QString desktopfp);                        //获取插件名称
    QString getAppExec(QString desktopfp);                        //获取应用可执行文件路径
    void    addDesktopFileName();                                 //将小插件desktop文件名称放入到desktopfpList中

    void    parsingDesktopFile();                                 //解析desktop文件
    QToolButton* StructToolButtol(QString icon, QString name);    //构建QToolButton
    QStringList m_desktopfpList;                                  //保存当前小插件desktop文件名称

    QString SetFormatBody(QString text, QLabel *label);           //设置...
    QString judgeBlankLine(QStringList list);
    bool    substringSposition(QString formatBody, QStringList list);

    QVBoxLayout *m_pWidgetOutVLayout;                             //最外层布局
    QHBoxLayout *m_pGrouBoxUpButtonHLayout;                       //GroupBox中Button中的布局
    QGridLayout *m_pGroupBoxUnSmallPluginsGLayout;                //闹钟，便签本布局

    QStackedWidget  *m_pstackWidget;                              //放置剪贴板和小插件的容器窗口
    QWidget     *m_pButtonWidget;                                 //放置按钮Box
    QWidget     *m_pClipboardWidget;                              //放置剪贴板的Box
    QWidget     *m_pPluginsButtonWidget;                          //放置小插件按钮Box

    QPushButton     *m_pFoldButton;                               //折叠按钮
    QPushButton     *m_pSpreadButton;                             //展开按钮
    QPushButton     *m_pBlueBackgroundButton;                     //蓝色背景块
    SmallPluginsButton *m_pClipboardButton;                       //剪贴板 界面显示按钮
    SmallPluginsButton *m_pSidebarPluginButton;                   //插件 界面显示按钮
    QToolButton *m_pNotebookButton;                               //笔记本 按钮
    QToolButton *m_pAlarmClockButton;                             //闹钟  按钮
    QToolButton *m_pFeedbackButtom;                               //用户反馈按钮

    QPropertyAnimation *m_pAnimationLeftRight;
    QPropertyAnimation *m_pAnimationRightLeft;
    QPropertyAnimation *m_pAnimationClipbarod;
    QPropertyAnimation *m_pAnimationSmallWidget;

    QGSettings      *m_pTransparency = nullptr;                   // 透明度gsetting值

    //状态机
    bool    ClipBoardBool = false;                                // 剪贴板修改屏幕分辨率bool值
    bool    SmallPluginsBool = false;                             // 插件按钮修改屏幕分辨率bool值

    int     m_add_x = 0;
    int     m_add_y = 1;
    int     m_cliboardHight;                                      // 剪贴板和小插件的高度
    QMap<QLabel*, QString> m_LabelTextMap;                        // 保存label原始字符串的Map表


signals:
    void FontModifyComplete();

private slots:
    void m_pClipBoardStateSlots();
    void m_pSmallPluginsStateSlots();

    void m_ClipboardButtonSlots();
    void m_SidebarPluginButtonSlots();

    void m_pFoldButtonSlots();
    void m_pSpreadButtonSlots();

    void m_AnimationClipbarodEndSlots();
    void m_AnimationSmallWidgetEndSlots();
    void getTransparencyValue(const QString key);                                                //获取个gsetting值
protected:
    void paintEvent(QPaintEvent *e);

};

#endif // SIDEBARPLUGINSWIDGETS_H
