#ifndef SIDEBARPLUGINSWIDGETS_H
#define SIDEBARPLUGINSWIDGETS_H

#define  KYLIN_ALARM_CLACK_ICON      ":/data/images/kylin-alarm-clock.svg"
#define  KYLIN_NOTEBOOK              ":/data/images/kylin-notebook.svg"

#include <QtWidgets>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QToolButton>
#include "smallpluginsbutton.h"
class sidebarPluginsWidgets : public QWidget
{
    Q_OBJECT
public:
    explicit sidebarPluginsWidgets(QWidget *parent = nullptr);
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


    QVBoxLayout *m_pWidgetOutVLayout;                             //最外层布局
    QHBoxLayout *m_pGrouBoxUpButtonHLayout;                       //GroupBox中Button中的布局
    QGridLayout *m_pGroupBoxUnSmallPluginsGLayout;                //闹钟，便签本布局

    QWidget     *m_pButtonWidget;                                 //放置按钮Box
    QWidget     *m_pClipboardWidget;                              //放置剪贴板的Box
    QWidget     *m_pPluginsButtonWidget;                          //放置小插件按钮Box

    QPushButton      *m_pBlueBackgroundButton;                          //蓝色背景块
    SmallPluginsButton *m_pClipboardButton;                       //剪贴板 界面显示按钮
    SmallPluginsButton *m_pSidebarPluginButton;                   //插件 界面显示按钮
    QToolButton *m_pNotebookButton;                               //笔记本 按钮
    QToolButton *m_pAlarmClockButton;                             //闹钟  按钮
    QPropertyAnimation *m_pAnimationLeftRight;
    QPropertyAnimation *m_pAnimationRightLeft;

    //状态机
    QStateMachine *m_pMachine;                                    //状态机
    QState *m_pClipBoardState;                                    //剪贴板状态
    QState *m_pSmallPluginsState;                                 //小插件状态
    bool    m_pBoolStates;
signals:

private slots:
    void m_pClipBoardStateSlots();
    void m_pSmallPluginsStateSlots();

};

#endif // SIDEBARPLUGINSWIDGETS_H
