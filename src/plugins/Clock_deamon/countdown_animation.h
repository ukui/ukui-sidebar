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
#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include <QRoundProgressBar.h>

namespace Ui {
class Countdown_Animation;
}

class Countdown_Animation : public QWidget
{
    Q_OBJECT
public:

     Countdown_Animation( QWidget *parent = 0, int value_max = 0);
    ~Countdown_Animation();

    QRoundProgressBar *RoundBar3;

    void setupUi(QWidget *TestWidget);

    void retranslateUi(QWidget *TestWidget);

    QTimer *timer;

    int value_max=100;

private:
    void connectToSlider(class QRoundProgressBar* bar);

    void con();



    Ui::Countdown_Animation *ui;
};

#endif // TESTWIDGET_H
