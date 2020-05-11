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
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QStyleOption>
#include <QSqlTableModel>

namespace Ui {
class Natice_alarm;
}

class Natice_alarm : public QWidget
{
    Q_OBJECT

public:
    explicit Natice_alarm( int close_time, int num,QWidget *parent = nullptr);
    ~Natice_alarm();
     Ui::Natice_alarm *ui;

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void set_dialog_close();
    void close_music();
    void show_again();
    void ring();

private:
    void natice_init();
    QTimer *timer = nullptr;
    QTimer *timer_xumhuan = nullptr;

    int timer_value;
    int num_flag;
    QMediaPlayer  *music;
    QMediaPlaylist *playlist;
    int ring_num;
    int timer_value2;
    int full_flag=1;
    QSqlTableModel *model_setup;
};

#endif // NATICE_ALARM_H
