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
#include <QGSettings>

#define ORG_UKUI_STYLE            "org.ukui.style"
#define STYLE_NAME                "styleName"
#define STYLE_NAME_KEY_DARK       "ukui-dark"
#define STYLE_NAME_KEY_DEFAULT    "ukui-default"
#define STYLE_NAME_KEY_BLACK       "ukui-black"
#define STYLE_NAME_KEY_LIGHT       "ukui-light"
#define STYLE_NAME_KEY_WHITE       "ukui-white"

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

    void  setupUi(QWidget *item_new);
    void  retranslateUi(QWidget *item_new);
    void  settingsStyle();
    void  blackStyle();                                                                  //黑色主题
    void  whiteStyle();                                                                  //白色主题

    Ui::item_new *ui;

    QPushButton *deleteAlarmBtn0;
    QLabel *alarmLabel0;
    QLabel *alarmLabel1;
    QLabel *alarmLabel_w0;
    QLabel *alarmLabel_s0;

    QPushButton *alarm_on_off0;
    QPushButton *alarm_changed0;
    QPushButton *alarm_edit0;

    QFrame *alarm_line0;

};

#endif // ITEM_NEW_H
