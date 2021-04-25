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
#ifndef NATICE_ALARM_H
#define NATICE_ALARM_H

#include <QWidget>
#include <QDialog>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QStyleOption>
#include <QSqlTableModel>

namespace Ui {
class Natice_alarm;
}

class Natice_alarm : public QDialog
{
    Q_OBJECT

public:
    explicit Natice_alarm( int close_time, int num,QWidget *parent = nullptr);
    ~Natice_alarm();
     Ui::Natice_alarm *ui;

     //bool eventFilter(QObject *watched, QEvent *event);
     void showPaint();
     void mousePressEvent(QMouseEvent *event);
     void mouseReleaseEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);
     void closeEvent(QCloseEvent *event);

     QTimer *timer = nullptr;
     QTimer *timer_xumhuan = nullptr;
     QMediaPlayer  *music;
     int timer_value;

protected:
     //绘制背景
     // Draw background
    void paintEvent(QPaintEvent *);

private slots:
    //窗口关闭    window closing
    void set_dialog_close();
    //关闭音乐    Turn off music
    void close_music();
    //再次弹出    Eject again
    void show_again();
    //响铃       Ring a bell
    void ring();

private:
    void natice_init();

    int num_flag;
    QMediaPlaylist *playlist;
    int ring_num;
    int timer_value2;
    int full_flag=1;
    QSqlTableModel *model_setup;
    QPoint dragPosition;                                            //拖动坐标
    bool mousePressed;                                              //鼠标是否按下
};

#endif // NATICE_ALARM_H
