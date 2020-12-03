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
#ifndef SET_ALARM_REPEAT_DIALOG_H
#define SET_ALARM_REPEAT_DIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include <QLabel>
#include <QPainter>
#include "clickableLabel.h"

namespace Ui {
class set_alarm_repeat_Dialog;
}

class set_alarm_repeat_widget;


class set_alarm_repeat_Dialog : public QWidget
{
    Q_OBJECT

public:
    explicit set_alarm_repeat_Dialog(QWidget *parent = nullptr , int rowNum = 0 );
    ~set_alarm_repeat_Dialog();

    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

    void showPaint();

    set_alarm_repeat_widget *widget[20];
    QListWidgetItem *aItem[20];
    int rowNum_all ;
    QListWidget *listWidget;

private:
  //  Ui::set_alarm_repeat_Dialog *ui;
    void setupUi(QWidget *set_alarm_repeat_Dialog);
    void retranslateUi(QWidget *set_alarm_repeat_Dialog);

    void set_aItem(int rowNum);

};



class set_alarm_repeat_widget : public QWidget
{
    Q_OBJECT

public:
    explicit set_alarm_repeat_widget(QWidget *parent = nullptr);
    ~set_alarm_repeat_widget();

    void paintEvent(QPaintEvent *event);

    QLabel *alarmLabel0;
    //QPushButton
    ClickableLabel *alarmLabel1;

private:

};

#endif // SET_ALARM_REPEAT_DIALOG_H
