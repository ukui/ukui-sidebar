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
#include <item_new.h>
#include <QListWidgetItem>
#include "stopwatch_item.h"
#include <QPaintEvent>
#include "verticalscroll_24.h"
#include "verticalscroll_60.h"
#include "verticalscroll_99.h"
#include "DotLineDemo.h"
#include "set_alarm_repeat_dialog.h"
#include <QPointF>
#include <QLineEdit>
#include "setuppage.h"



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

namespace Ui {
class Clock;
}

class Clock : public QWidget
{
    Q_OBJECT

public:

    explicit Clock(QWidget *parent = nullptr);
    ~Clock();

protected:
    void paintEvent1(QPaintEvent *);

private slots:
    void notice_dialog_show(int,int);

    void model_setup_set();                                                    //全局设置数据库初始化

    void Count_down();//int Hour,int minute ,int second);

    void on_pushButton_Start_clicked();

    void on_pushButton_ring_clicked();

    void on_pushButton_timeselect_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void timerUpdate();

    void text_timerUpdate();

    void set_Alarm_Clock();                                                          //新建闹钟按钮回调

    void cancelAlarmClock();                                                         //添加闹钟dialog关闭

    void updateAlarmClock();

    void On_Off_Alarm();                                                             //闹钟开关

    void deleteAlarm();

    void stopPlayMusic();

    void selectMusic();

    void rePlayMusic();

    void aItem_new();

    void listdoubleClickslot();                                                       //双击闹钟打开重编辑页面

    void listClickslot();

    void on_pushButton_9_clicked();

    void stat_countdown();

    void setcoutdown_number(int h, int m, int s);

    void startbtn_countdown();                                                           //倒计时开始-结束回调

    void on_min_5btn_clicked();                                                          //倒计时5分钟设置回调

    void on_min_10btn_clicked();                                                         //倒计时10分钟设置回调

    void on_min_20btn_clicked();                                                         //倒计时20分钟设置回调

    void on_min_30btn_clicked();                                                         //倒计时30分钟设置回调

    void on_min_60btn_clicked();                                                         //倒计时60分钟设置回调

    void get_countdown_over_time();                                                      //获取倒计时结束时间

    void on_count_push_clicked();                                                        //倒计时-暂停继续回调

    void stopwatch_jg();                                                                 //时间间隔计算执行回调

    void change_time_NUM(int Hour,int Minute);                                           //修改时间单数 为两位数

    void countdown_set_start_time();                                                     //倒计时初始数字转盘

    void alarm_set_start_time();                                                         //闹钟初始化数字转盘绘制

    void alarm_Cancel_save();                                                            //闹钟新建界面取消回调

    void set_alarm_save();                                                               //闹钟新建界面保存回调

    void verticalscroll_ring_time();                                                     //闹钟新建与重编辑界面剩余时间实时显示回调

    void alarm_repeat();                                                                 //闹钟初始化工作日选择界面绘制回调

    void repeat_listClickslot();                                                         //重复选项单击回调

    void select_Music();                                                                 //闹钟初始化音乐选择界面回调

    void music_listClickslot();                                                          //闹钟初始化单击选择音乐

    void time_Music();                                                                   //闹钟初始化音乐时长选择界面回调

    void time_music_listClickslot();                                                     //单击选择音乐时长回调

    void clack_rename();                                                                 //闹钟命名输入框打开回调

    void set_up_page();                                                                  //设置页面绘制回调

    void alarm_clcok_Self_starting();                                                    //开机自启动开关回调

    void Mute_starting();                                                                //静音开关回调

    void set_volume_Value(int value);                                                    //设置音量回调



private:
    QPoint m_startPoint;
    Ui::Clock *ui;
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

    QMediaPlayer *player = new QMediaPlayer;
    QString ring;//铃声名字

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

    QLabel *cTimeLabe;

    QDialog *dialog;
    QFont alarmFont;
    QSpinBox *hourBox;
    QSpinBox *minuteBox;
    QComboBox *pauseTime;

    QMediaPlayer *player_alarm;
    QMediaPlaylist *mediaList; //播放列表
    QSqlTableModel *model;  //数据库
    QSqlTableModel *model_setup;
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
    int repeat_new_or_edit_flag;  //重复日判断 是新建,还是重编辑,两者获取数据库号不同;


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

    QWidget *grand = nullptr;
    setuppage  *setup_page= nullptr;
    QString repeat_str;
    QString repeat_str_model;
    QString music_str_model;
    QString time_music_str_model;
    QString clock_name;
    QLineEdit *lineEdit= nullptr ;

};


#endif // CLOCK_H
