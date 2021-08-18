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
#ifndef BTN_NEW_H
#define BTN_NEW_H

#include <QWidget>
#include <QToolButton>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class Btn_new;
}
class Clock;
class Btn_new : public  QPushButton
{
    Q_OBJECT

public:
    explicit Btn_new(int num, QString name , QWidget *parent = nullptr);
    ~Btn_new();
    QLabel *nameLabel;
    QLabel *textLabel;
    QLabel *noName;
    QLabel *IconLabel;

    void paintEvent(QPaintEvent *event);
    void updateWidthForFontChange(int px);
private:
    Ui::Btn_new *ui;
    Clock * m_pclock;
    int clock_num;
    int pressflag;
protected:
};

#endif // BTN_NEW_H
