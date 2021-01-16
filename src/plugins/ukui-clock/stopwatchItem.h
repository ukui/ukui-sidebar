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
#ifndef STOPWATCH_ITEM_H
#define STOPWATCH_ITEM_H

#include <QWidget>
#include <QLabel>
#include <QGSettings>

#define ORG_UKUI_STYLE            "org.ukui.style"
#define STYLE_NAME                "styleName"
#define STYLE_NAME_KEY_DARK       "ukui-dark"
#define STYLE_NAME_KEY_DEFAULT    "ukui-default"
#define STYLE_NAME_KEY_BLACK       "ukui-black"
#define STYLE_NAME_KEY_LIGHT       "ukui-light"
#define STYLE_NAME_KEY_WHITE       "ukui-white"

namespace Ui {
class stopwatch_item;
}

class stopwatch_item : public QWidget
{
    Q_OBJECT

public:
    explicit stopwatch_item(QWidget *parent = nullptr);
    ~stopwatch_item();
    void setupUi(QWidget *stopwatch_item);
    void retranslateUi(QWidget *stopwatch_item);
    void  settingsStyle();
    void  blackStyle();                                                                  //黑色主题
    void  whiteStyle();                                                                  //白色主题

    QLabel *stopwatch1;
    QLabel *stopwatch2;
    QLabel *stopwatch3;

    QFrame *stopwatch_line;

private:
    Ui::stopwatch_item *ui;
};

#endif // STOPWATCH_ITEM_H
