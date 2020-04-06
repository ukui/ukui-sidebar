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
#include "item_new.h"
#include "ui_item_new.h"

item_new::item_new(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::item_new)
{
    ui->setupUi(this);

    this->setFixedSize(376, 56);

    alarmLabel_w0 = new QLabel(this);//闹钟用途
    alarmLabel_w0->move(22, 9);
    alarmLabel_w0->setFixedSize(100, 17);
    alarmLabel_w0->setStyleSheet("font: 11pt ;background-color: rgb();");
    alarmLabel_w0->setText(tr("闹钟"));

    alarmLabel_s0 = new QLabel( this);//闹钟重复
    alarmLabel_s0->move(24, 34);
    alarmLabel_s0->setFixedSize(100, 17);
    alarmLabel_s0->setStyleSheet("font: 9pt ;color: rgb(148, 148, 148);background-color: rgb();");
    alarmLabel_s0->setText(tr("工作日"));
    alarmLabel_s0->setVisible(true);


    alarm_line0 = new QFrame(this);
    alarm_line0->move(13, 52);
    alarm_line0->setFixedSize(350, 1);
    alarm_line0->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);background-color: rgb(102, 102, 102);"));


    alarmLabel0 = new QLabel(this);//闹钟，音乐，
    alarmLabel0->move(213,15);
    alarmLabel0->setFixedSize(78, 20);
    alarmLabel0->setStyleSheet("font: 17pt ;background-color: rgb();");
    alarmLabel0->setText("00:00");
    alarmLabel0->setVisible(true);
    alarmLabel0->show();

    alarm_on_off0 = new QPushButton(this);//闹钟开关
    alarm_on_off0->move(305,14);
    alarm_on_off0->setFixedSize(50, 24);
    alarm_on_off0->setFlat(true);
    alarm_on_off0->setVisible(true);
    alarm_on_off0->setStyleSheet("border-image: url(:/alarm_on.png);background-color: rgb();");
}

item_new::~item_new()
{
    delete ui;
}
