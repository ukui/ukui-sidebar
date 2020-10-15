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
    void showPaint2();
    void showPaint3();
    void showPaint4();
    void showPaint5();
    void showPaint6();
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

public slots:
    void on_pushButton_clicked();                                                        //倒计时切换
                                                                                         // Countdown switch
    void on_pushButton_2_clicked();                                                      //闹钟窗口切换
                                                                                         // Alarm window switching
    void on_pushButton_3_clicked();                                                      //秒表窗口切换
                                                                                         // Stopwatch window switch
private slots:
    void button_image_init();                                                            //闹钟按钮图片初始化
                                                                                         // Alarm button picture initialization
    void Countdown_init();                                                               //倒计时页初始化
                                                                                         // Countdown page initialization
    void stopwatch_init();                                                               //秒表页初始化
                                                                                         // Stopwatch page initialization
    void clock_init();                                                                   //闹钟页初始化
                                                                                         // Alarm page initialization
    void setup_init();                                                                   //默认初始设置
                                                                                         // Default initial settings
    void notice_dialog_show(int,int);                                                    //通知弹窗
                                                                                         // Notification Popup
    void model_setup_set();                                                              //默认设置数据库数据初始化
                                                                                         // Default setting database data initialization
    void Count_down();//int Hour,int minute ,int second);                                //秒表执行
                                                                                         // Stopwatch execution
    void on_pushButton_Start_clicked();                                                  //秒表开始暂停继续
                                                                                         // Stopwatch start pause continue
    void on_pushButton_ring_clicked();                                                   //计次
                                                                                         // times count
    void on_pushButton_timeselect_clicked();                                             //复位
                                                                                         // reset
    void on_pushButton_5_clicked();                                                      //窗口关闭
                                                                                         // window closing
    void on_pushButton_4_clicked();                                                      //窗口最小化
                                                                                         // window minimizing
    void timerUpdate();                                                                  //动态监控闹钟与本地时间
                                                                                         // Dynamic monitoring alarm clock and local time
    void text_timerUpdate();                                                             //闹钟上方电子表
                                                                                         // Electronic watch above alarm clock
    void set_Alarm_Clock();                                                              //新建闹钟按钮回调
                                                                                         // New alarm button callback
    void cancelAlarmClock();                                                             //添加闹钟dialog关闭
                                                                                         // Add alarm dialogclose
    void updateAlarmClock();                                                             //重绘窗口，更新闹钟
                                                                                         // Redraw window, update alarm clock
    void On_Off_Alarm();                                                                 //闹钟开关
                                                                                         // Alarm switch
    void deleteAlarm();                                                                  //闹钟重编辑页面删除闹钟回调
                                                                                         // Alarm re edit page delete alarm callback
    void stopPlayMusic();                                                                //停止音乐
                                                                                         // Stop music
    void selectMusic();                                                                  //选择音乐
                                                                                         //Choose music
    void rePlayMusic();                                                                  //播放音乐
                                                                                         // Play music
    void aItem_new();                                                                    //增加item
                                                                                         // Add item
    void listdoubleClickslot();                                                          //双击闹钟打开重编辑页面
                                                                                         // Double click the alarm clock to open the re edit page
    void listClickslot();                                                                //单击闹钟显示铃声剩余时间
                                                                                         // Click the alarm to display the remaining time
    void on_pushButton_9_clicked();                                                      //闹钟重编辑保存回调
                                                                                         // Alarm re edit save callback
    void stopwatch_start_Animation();                                                    //倒计时开始动画移动
                                                                                         // Countdown start animation move
    void stopwatch_stop_Animation();                                                     //倒计时结束动画移动
                                                                                         // Countdown start animation move
    void stat_countdown();                                                               //倒计时执行
                                                                                         // Countdown execution
    void setcoutdown_number(int h, int m, int s);                                        //设置倒计时初始时间
                                                                                         // Set the initial countdown time
    void startbtn_countdown();                                                           //倒计时开始-结束回调
                                                                                         // Countdown start end callback
    void on_min_5btn_clicked();                                                          //倒计时5分钟设置回调
                                                                                         // Countdown 5 minutes set callback
    void on_min_10btn_clicked();                                                         //倒计时10分钟设置回调
                                                                                         // Countdown 10 minutes set callback
    void on_min_20btn_clicked();                                                         //倒计时20分钟设置回调
                                                                                         // Countdown 20 minutes set callback
    void on_min_30btn_clicked();                                                         //倒计时30分钟设置回调
                                                                                         // Countdown 30 minutes set callback
    void on_min_60btn_clicked();                                                         //倒计时60分钟设置回调
                                                                                         // Countdown 60 minutes set callback
    void get_countdown_over_time();                                                      //获取倒计时结束时间
                                                                                         // Get countdown end time
    void on_count_push_clicked();                                                        //倒计时-暂停继续回调
                                                                                         // Countdown - pause resume callback
    void stopwatch_jg();                                                                 //时间间隔计算执行回调
                                                                                         // Interval calculation execution callback
    void change_time_NUM(int Hour,int Minute);                                           //修改时间单数 为两位数
                                                                                         // Modify time singular to two digits
    void countdown_set_start_time();                                                     //倒计时初始数字转盘
                                                                                         // Countdown initial digital dial
    void alarm_set_start_time();                                                         //闹钟初始化数字转盘绘制
                                                                                         // Alarm clock initialization digital turntable drawing
    void alarm_Cancel_save();                                                            //闹钟新建界面取消回调
                                                                                         // Cancel callback in alarm new interface
    void set_alarm_save();                                                               //闹钟新建界面保存回调
                                                                                         // Alarm new interface save callback
    void verticalscroll_ring_time();                                                     //闹钟新建与重编辑界面剩余时间实时显示回调
                                                                                         // Alarm clock new and re edit interface remaining time real-time display callback
    void alarm_repeat();                                                                 //闹钟初始化工作日选择界面绘制回调
                                                                                         // Alarm clock initialization workday selection interface drawing callback
    void repeat_listClickslot();                                                         //重复选项单击回调
                                                                                         // Repeat option click callback
    void select_Music();                                                                 //闹钟初始化音乐选择界面回调
                                                                                         // Alarm clock initialization music selection interface callback
    void music_listClickslot();                                                          //闹钟初始化单击选择音乐
                                                                                         // Alarm initialization Click to select music
    void time_Music();                                                                   //闹钟初始化音乐时长选择界面回调
                                                                                         // Alarm clock initialization music time selection interface callback
    void time_music_listClickslot();                                                     //单击选择音乐时长回调
                                                                                         // Click to select music duration callback
    void set_up_page();                                                                  //设置页面绘制回调
                                                                                         // Set page draw callback
    void alarm_clcok_Self_starting();                                                    //开机自启动开关回调
                                                                                         // Power on self start switch callback
    void Mute_starting();                                                                //静音开关回调
                                                                                         // Mute switch callback
    void set_volume_Value(int value);                                                    //设置音量回调
                                                                                         // Set volume callback
    void countdown_music_sellect();                                                      //倒计时音乐选择
                                                                                         // Countdown music selection
    void count_music_listClickslot();                                                    //倒计时音乐选择单机回调
                                                                                         // Countdown music selection single callback
    void countdown_notice_dialog_show();                                                 //倒计时通知弹窗
                                                                                         // Countdown notification pop-up
    void off_Alarm(int );                                                                //不重复时单独关闭闹钟
                                                                                         // Turn off the alarm separately if it is not repeated
    int get_alarm_clock_will_ring_days(int num);                                         //计算下次闹钟响起天数间隔
                                                                                         // Calculate the next alarm ring interval
    int get_alarm_clock_will_ring_days_2(int num);                                       //计算下次闹钟响起天数间隔
                                                                                         // Calculate the next alarm ring interval
    QString change_NUM_to_str(int alarmHour);                                            //整型转字符
                                                                                         // Integer to character
    void count_stat_btn_gray();

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
    QMediaPlaylist *mediaList; //播放列表
                               //playlist
    QSqlTableModel *model;  //数据库
                            //data base
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
    int repeat_day[9];   //重复日选择保存中介
                         // Select and save mediation for duplicate days
    int repeat_new_or_edit_flag;  //重复日判断 是新建,还是重编辑,两者获取数据库号不同;
                                  // Whether to create or re edit the duplicate day is determined. The database numbers obtained by the two methods are different
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

    close_or_hide *close_or_hide_page;
    adaptScreenInfo *m_pSreenInfo = nullptr;
    QPushButton *pushcount;
    QPushButton *pushclock;
    QPushButton *pushstop;
    QPushButton *count_stat;
    QWidget *shadow;
    QWidget *shadow1;

    QPoint dragPosition;                                            //拖动坐标
    bool mousePressed;                                              //鼠标是否按下
};


#endif // CLOCK_H
