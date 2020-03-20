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
#ifndef ITEM_NEW_H
#define ITEM_NEW_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFrame>

namespace Ui {
class item_new;
}

class item_new : public QWidget
{
    Q_OBJECT

public:
    explicit item_new(QWidget *parent = nullptr);
    ~item_new();

//private:
    Ui::item_new *ui;

    QPushButton *deleteAlarmBtn0;
    QLabel *alarmLabel0;
    QLabel *alarmLabel_w0;
    QLabel *alarmLabel_s0;

    QPushButton *alarm_on_off0;
    QPushButton *alarm_changed0;
    QPushButton *alarm_edit0;

    QFrame *alarm_line0;
};

#endif // ITEM_NEW_H
