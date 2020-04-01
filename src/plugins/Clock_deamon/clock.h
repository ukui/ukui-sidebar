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

    void paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.fillRect(this->rect(), QColor(0, 0, 0, 0x20)); /* 设置透明颜色 */
    }
    //Qt::FramelessWindowHint会导致窗口不能被拖动。通过捕获鼠标移动事件从而实现窗口移动
    void mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton) {
            m_startPoint = frameGeometry().topLeft() - event->globalPos(); /* 捕获按下时坐标 */
        }
    }
    void mouseMoveEvent(QMouseEvent *event)
    {
        this->move(event->globalPos() + m_startPoint); /* 移动窗口 */
    }

    QPointF rotateAngle(int angle, int len);

protected:
    void paintEvent1(QPaintEvent *);

private slots:
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

    void setAlarmClock();

    void cancelAlarmClock();                                                         //添加闹钟dialog关闭

    void sureAlarmClock();

    void updateAlarmClock();

    void on_off_Alarm();                                                                //闹钟开关

    void deleteAlarm();

    void stopPlayMusic();

    void selectMusic();

    void rePlayMusic();

    void aItem_new();

    void listdoubleClickslot();

    void listClickslot();

    void on_pushButton_7_clicked();

    void stat_countdown();

    void setcoutdown_number(int h, int m, int s);

    void startbtn_countdown();

    void on_min_5btn_clicked();

    void on_min_10btn_clicked();

    void on_min_20btn_clicked();

    void on_min_30btn_clicked();

    void on_min_60btn_clicked();

    void get_countdown_over_time();

    void on_count_push_clicked();

    void stopwatch_jg();

    void change_time_NUM(int alarmHour, int alarmMinute);


private:
    QPoint m_startPoint;
    Ui::Clock *ui;
    QTimer *timer = NULL;
    QTimer *countdown_timer = NULL;
    QTimer *timer_2 = NULL;
    int hour, minute, second, pushflag ;
    int stopwatch_hour, stopwatch_minute, stopwatch_second ;
    int countdown_hour, countdown_minute, countdown_second, countdown_pushflag ;
    bool isStarted;
    bool countdown_isStarted;
    bool countdown_isStarted_2;
    bool stopwatch_isStarted;
    QMediaPlayer *player = new QMediaPlayer;
    QString ring;//铃声名字
    QString alarmHour_str; QString alarmMinute_str;
    QTimer *timer_Surplus;

    int alarmHour;
    int alarmMinute;
    int cPauseTime;

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
    QPixmap pixmap12;

    QPixmap bgPixmap;
    QPixmap clockPixmap;
    QPixmap hourPixmap;
    QPixmap minutePixmap;
    QPixmap secondPixmap;
    QPixmap delBtnPixmap;
    QPixmap on_pixmap;
    QPixmap off_pixmap;

    QLabel *cTimeLabe;

    QDialog *dialog;
    QFont alarmFont;
    QSpinBox *hourBox;
    QSpinBox *minuteBox;
    QComboBox *pauseTime;

    QMediaPlayer *player_alarm;
    QMediaPlaylist *mediaList; //播放列表
    QSqlTableModel *model;  //数据库
    QString musicPath;

    item_new *w1[20];
    QListWidgetItem *aItem[20];
    stopwatch_item *stopwatch_w[100];
    QListWidgetItem *stopwatch_aItem[100];
    QString stopwatch_h;QString stopwatch_m;QString stopwatch_s;
    QString stopwatch_jg_h ="00";QString stopwatch_jg_m= "00";QString stopwatch_jg_s= "00";

    int stopwatch_item_flag = 0;
    int clock_num = 0;
    int on_off_flag = 0;
    int add_change_flag = 0;
    int change_alarm_line = 0;
    int n = 0;
    int medel_flag = 0;
    int continu_flag = 0;
};


#endif // CLOCK_H
