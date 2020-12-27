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
#ifndef CLOCK_H
#define CLOCK_H
#include <QPainterPath>
#include <QWidget>
#include <QTimer>
#include <QQueue>
#include <QSlider>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include <QLCDNumber>
#include <QMediaPlayer>
#include <QFrame>
#include <itemNew.h>
#include <QListWidgetItem>
#include "stopwatchItem.h"
#include <QPaintEvent>
#include "verticalScroll24.h"
#include "verticalScroll60.h"
#include "verticalScroll99.h"
#include "dotlineDemo.h"
#include "setAlarmRepeatDialog.h"
#include <QPointF>
#include <QLineEdit>
#include "setupPage.h"
#include <QPropertyAnimation>
#include "adaptscreeninfo.h"
#include <QCloseEvent>
#include "about.h"
#include <QMenu>

class QSpinBox;
class QComboBox;
class QDialog;
class QSpinBox;
class QComboBox;
class QLabel;
class QFont;
class QPushButton;
class QMediaPlaylist;
class QSqlTableModel;
class QTimer;
class Btn_new;
class close_or_hide;

namespace Ui {
class Clock;
}

class Clock : public QWidget
{
    Q_OBJECT

public:

    explicit Clock(QWidget *parent = nullptr);
    ~Clock();

    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
    void showPaint();
    void showPaint1();
    void showPaint7();
    void showPaint8();

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    Ui::Clock *ui;
    QSqlTableModel *model_setup;

protected:
    void paintEvent1(QPaintEvent *);
    QPixmap ChangeImageColor(QPixmap sourcePixmap, QColor origColor, QColor destColor);
    void closeEvent(QCloseEvent *event);

public slots:
    void  CountdownPageSwitch ();                                                        //倒计时切换
                                                                                         // Countdown switch
    void  AlarmPageSwitch ();                                                            //闹钟窗口切换
                                                                                         // Alarm window switching
    void  StopwatchPageSwitch ();                                                        //秒表窗口切换
                                                                                         // Stopwatch window switch
private slots:
    void buttonImageInit();                                                              //闹钟按钮图片初始化
                                                                                         // Alarm button picture initialization
    void CountdownInit();                                                                //倒计时页初始化
                                                                                         // Countdown page initialization
    void stopwatchInit();                                                                //秒表页初始化
                                                                                         // Stopwatch page initialization
    void clockInit();                                                                    //闹钟页初始化
                                                                                         // Alarm page initialization
    void setupInit();                                                                    //默认初始设置
                                                                                         // Default initial settings
    void noticeDialogShow(int,int);                                                      //通知弹窗
                                                                                         // Notification Popup
    void modelSetupSet();                                                                //默认设置数据库数据初始化
                                                                                         // Default setting database data initialization
    void CountDown();                                                                    //秒表执行
                                                                                         // Stopwatch execution
    void onPushbuttonStartClicked();                                                     //秒表开始暂停继续
                                                                                         // Stopwatch start pause continue
    void onPushbuttonRingClicked();                                                      //计次
                                                                                         // times count
    void onPushbuttonTimeselectClicked();                                                //复位
                                                                                         // reset
    void windowClosingClicked();                                                         //窗口关闭
                                                                                         // window closing
    void windowMinimizingClicked();                                                      //窗口最小化
                                                                                         // window minimizing
    void timerUpdate();                                                                  //动态监控闹钟与本地时间
                                                                                         // Dynamic monitoring alarm clock and local time
    void textTimerupdate();                                                              //闹钟上方电子表
                                                                                         // Electronic watch above alarm clock
    void setAlarmClock();                                                                //新建闹钟按钮回调
                                                                                         // New alarm button callback
    void cancelAlarmClock();                                                             //添加闹钟dialog关闭
                                                                                         // Add alarm dialogclose
    void updateAlarmClock();                                                             //重绘窗口，更新闹钟
                                                                                         // Redraw window, update alarm clock
    void OnOffAlarm();                                                                   //闹钟开关
                                                                                         // Alarm switch
    void deleteAlarm();                                                                  //闹钟重编辑页面删除闹钟回调
                                                                                         // Alarm re edit page delete alarm callback
    void stopPlayMusic();                                                                //停止音乐
                                                                                         // Stop music
    void ChooseAlarmMusic();                                                                  //选择音乐
                                                                                         //Choose music
    void rePlayMusic();                                                                  //播放音乐
                                                                                         // Play music
    void aitemNew();                                                                     //增加item
                                                                                         // Add item
    void listdoubleClickslot();                                                          //双击闹钟打开重编辑页面
                                                                                         // Double click the alarm clock to open the re edit page
    void listClickslot();                                                                //单击闹钟显示铃声剩余时间
                                                                                         // Click the alarm to display the remaining time
    void alarmReEditClicked();                                                           //闹钟重编辑保存回调
                                                                                         // Alarm re edit save callback
    void stopwatchStartAnimation();                                                      //倒计时开始动画移动
                                                                                         // Countdown start animation move
    void stopwatchStopAnimation();                                                       //倒计时结束动画移动
                                                                                         // Countdown start animation move
    void statCountdown();                                                                //倒计时执行
                                                                                         // Countdown execution
    void setcoutdownNumber(int h, int m, int s);                                         //设置倒计时初始时间
                                                                                         // Set the initial countdown time
    void startbtnCountdown();                                                            //倒计时开始-结束回调
                                                                                         // Countdown start end callback
    void onMin_5btnClicked();                                                            //倒计时5分钟设置回调
                                                                                         // Countdown 5 minutes set callback
    void onMin_10btnClicked();                                                           //倒计时10分钟设置回调
                                                                                         // Countdown 10 minutes set callback
    void onMin_20btnClicked();                                                           //倒计时20分钟设置回调
                                                                                         // Countdown 20 minutes set callback
    void onMin_30btnClicked();                                                           //倒计时30分钟设置回调
                                                                                         // Countdown 30 minutes set callback
    void onMin_60btnClicked();                                                           //倒计时60分钟设置回调
                                                                                         // Countdown 60 minutes set callback
    void getCountdownOverTime();                                                         //获取倒计时结束时间
                                                                                         // Get countdown end time
    void onCountPushClicked();                                                           //倒计时-暂停继续回调
                                                                                         // Countdown - pause resume callback
    void stopwatchJg();                                                                  //时间间隔计算执行回调
                                                                                         // Interval calculation execution callback
    void changeTimeNum(int Hour,int Minute);                                             //修改时间单数 为两位数
                                                                                         // Modify time singular to two digits
    void countdownSetStartTime();                                                        //倒计时初始数字转盘
                                                                                         // Countdown initial digital dial
    void alarmSetStartTime();                                                            //闹钟初始化数字转盘绘制
                                                                                         // Alarm clock initialization digital turntable drawing
    void alarmCancelSave();                                                              //闹钟新建界面取消回调
                                                                                         // Cancel callback in alarm new interface
    void setAlarmSave();                                                                 //闹钟新建界面保存回调
                                                                                         // Alarm new interface save callback
    void verticalscrollRingTime();                                                       //闹钟新建与重编辑界面剩余时间实时显示回调
                                                                                         // Alarm clock new and re edit interface remaining time real-time display callback
    void alarmRepeat();                                                                  //闹钟初始化工作日选择界面绘制回调
                                                                                         // Alarm clock initialization workday selection interface drawing callback
    void repeatListclickslot();                                                          //重复选项单击回调
                                                                                         // Repeat option click callback
    void selectAlarmMusic();                                                                  //闹钟初始化音乐选择界面回调
                                                                                         // Alarm clock initialization music selection interface callback
    void musicListclickslot();                                                           //闹钟初始化单击选择音乐
                                                                                         // Alarm initialization Click to select music
    void timeMusic();                                                                    //闹钟初始化音乐时长选择界面回调
                                                                                         // Alarm clock initialization music time selection interface callback
    void timeMusicListclickslot();                                                       //单击选择音乐时长回调
                                                                                         // Click to select music duration callback
    void setUpPage();                                                                    //设置页面绘制回调
                                                                                         // Set page draw callback
    void alarmClcokSelfStarting();                                                       //开机自启动开关回调
                                                                                         // Power on self start switch callback
    void MuteStarting();                                                                 //静音开关回调
                                                                                         // Mute switch callback
    void setVolumeValue(int value);                                                      //设置音量回调
                                                                                         // Set volume callback
    void countdownMusicSellect();                                                        //倒计时音乐选择
                                                                                         // Countdown music selection
    void countMusicListclickslot();                                                      //倒计时音乐选择单机回调
                                                                                         // Countdown music selection single callback
    void countdownNoticeDialogShow();                                                    //倒计时通知弹窗
                                                                                         // Countdown notification pop-up
    void offAlarm(int );                                                                 //不重复时单独关闭闹钟
                                                                                         // Turn off the alarm separately if it is not repeated
    int getAlarmClockWillRingDays(int num);                                              //计算下次闹钟响起天数间隔
                                                                                         // Calculate the next alarm ring interval
    int getAlarmClockWillRingDays_2(int num);                                            //计算下次闹钟响起天数间隔
                                                                                         // Calculate the next alarm ring interval
    QString changeNumToStr(int alarmHour);                                               //整型转字符
                                                                                         // Integer to character
    void countStatBtnGray();

private:
    QPoint m_startPoint;
    QTimer *timer = nullptr;
    QTimer *countdown_timer = nullptr;
    QTimer *timer_2 = nullptr;
    int hour, minute, second, pushflag ;
    int stopwatch_hour, stopwatch_minute, stopwatch_second ;
    int countdown_hour, countdown_minute, countdown_second, countdown_pushflag ;
    int alarmHour;
    int alarmMinute;
    int cPauseTime;
    bool isStarted;
    bool countdown_isStarted;
    bool countdown_isStarted_2;
    bool stopwatch_isStarted;

    QMediaPlayer *player;
    QString ring;//铃声名字
                 // Ring name
    QPixmap pixmap1;
    QPixmap pixmap2;
    QPixmap pixmap3;
    QPixmap pixmap4;
    QPixmap pixmap5;
    QPixmap pixmap6;
    QPixmap pixmap7;
    QPixmap pixmap8;
    QPixmap pixmap9;
    QPixmap pixmap10;
    QPixmap pixmap11;
    QPixmap bgPixmap;
    QPixmap repeat_on_Pixmap;
    QPixmap repeat_off_Pixmap;
    QPixmap hourPixmap;
    QPixmap minutePixmap;
    QPixmap secondPixmap;
    QPixmap delBtnPixmap;
    QPixmap on_pixmap;
    QPixmap off_pixmap;
    QPixmap clock_icon;

    QDialog *dialog;
    QFont alarmFont;
    QSpinBox *hourBox;
    QSpinBox *minuteBox;
    QComboBox *pauseTime;

    QMediaPlayer *player_alarm;
    QMediaPlaylist *mediaList; /*播放列表
                                 playlist*/
    QSqlTableModel *model;  /*数据库
                              data base*/
    QSqlTableModel *model_Stopwatch;
    QString musicPath;

    item_new *w1[20];
    QListWidgetItem *aItem[20];
    stopwatch_item *stopwatch_w[100];
    QListWidgetItem *stopwatch_aItem[100];
    QString stopwatch_h;QString stopwatch_m;QString stopwatch_s;
    QString stopwatch_jg_h ="00";QString stopwatch_jg_m= "00";QString stopwatch_jg_s= "00";
    QString alarmHour_str; QString alarmMinute_str;

    int stopwatch_item_flag = 0;
    int clock_num = 0;
    int on_off_flag = 0;
    int add_change_flag = 0;
    int change_alarm_line = 0;
    int medel_flag = 0;
    int continu_flag = 0;
    int alarm_repeat_flag = 0;
    int repeat_day[9];   /*重复日选择保存中介
                           Select and save mediation for duplicate days*/
    int repeat_new_or_edit_flag;  /*重复日判断 是新建,还是重编辑,两者获取数据库号不同;
                                    Whether to create or re edit the duplicate day is determined. The database numbers obtained by the two methods are different*/
    int stopwatch_Animation = 0;
    int system_time_flag;
    int last_day_ring = 0;

    QTimer *timer_Surplus;
    QTimer *timer_set_page;
    VerticalScroll_99 * timer_ring99;
    VerticalScroll_60 * timer_ring60;
    VerticalScroll_60 * timer_ring60_2;
    VerticalScroll_24 * timer_alarm_start24;
    VerticalScroll_60 * timer_alarm_start60;

    set_alarm_repeat_Dialog *dialog_repeat = nullptr;
    set_alarm_repeat_Dialog *dialog_music = nullptr;
    set_alarm_repeat_Dialog *time_music = nullptr;
    set_alarm_repeat_Dialog *count_music_sellect = nullptr;

    close_or_hide *close_or_hide_page;
    adaptScreenInfo *m_pSreenInfo = nullptr;

    QWidget *grand = nullptr;
    setuppage  *setup_page= nullptr;
    QString repeat_str;
    QString repeat_str_model;
    QString music_str_model;
    QString time_music_str_model;
    QString clock_name;
    QLineEdit *lineEdit= nullptr ;
    QPropertyAnimation *animation1;
    QPropertyAnimation *animation2;
    QPropertyAnimation *animation3;

    QPushButton *pushcount;
    QPushButton *pushclock;
    QPushButton *pushstop;
    QPushButton *count_stat;
    QWidget *shadow;
    QWidget *shadow1;

    QPoint dragPosition;                                            /*拖动坐标*/
    bool mousePressed;                                              /*鼠标是否按下*/

    Btn_new *count_sel;
    Btn_new *count_sel_1;
    Btn_new *repeat_sel;
    Btn_new *time_sel;
    Btn_new *ring_sel;
    QMenu *m_menu;                                                  /*功能菜单*/
    QAction *m_menuAction;                                          /*菜单动作*/
};


#endif // CLOCK_H
