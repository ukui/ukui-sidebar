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
#include<QApplication>
#include <QDebug>

item_new::item_new(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    this->setStyleSheet("border-radius:12px;");

    this->setFixedSize(376, 58);

    alarmLabel_w0 = new QLabel(this);//闹钟用途
    alarmLabel_w0->move(22, ４);
    alarmLabel_w0->setFixedSize(170, 2５);
    alarmLabel_w0->setStyleSheet("font: 11pt 'Sans Serif';background-color: rgb();\
                                 width:35px;\
                                 height:17px;\
                                 font-size:18px;\
                                 font-weight:500;\
                                 color:rgba(255,255,255,1);\
                                 ");
    alarmLabel_w0->setText("闹钟");


    alarmLabel_s0 = new QLabel( this);//闹钟重复
    alarmLabel_s0->move(24, 34);
    alarmLabel_s0->setFixedSize(170, 17);
    alarmLabel_s0->setStyleSheet("font: 9pt 'Sans Serif';color: rgb(148, 148, 148);background-color: rgb();\
                                 width:42px;\
                                 height:14px;\
                                 font-size:14px;\
                                 font-weight:400;\
                                 color:rgba(148, 148, 148,1);\
                                 opacity:0.45;\
                                 ");
    alarmLabel_s0->setText("工作日");
    alarmLabel_s0->setVisible(true);


    alarm_line0 = new QFrame(this);
    alarm_line0->move(13, 57);
    alarm_line0->setFixedSize(350, 1);
    alarm_line0->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);background-color: rgb(102, 102, 102);"));

    alarmLabel0 = new QLabel(this);//闹钟，音乐，
    alarmLabel0->move(200,13);
    alarmLabel0->setFixedSize(89, 27);
    alarmLabel0->setStyleSheet("font: 17pt;background-color: rgb();\
                               width:78px;\
                               height:22px;\
                               font-size:30px;\
                               font-weight:400;\
                               color:rgba(255,255,255,1);");
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
   delete  alarmLabel_w0;
   delete  alarmLabel_s0;
   delete  alarm_line0;
   delete  alarmLabel0;
   delete  alarm_on_off0;
    qDebug()<<"------item_new---------";

}

void item_new::setupUi(QWidget *item_new)
{
    if (item_new->objectName().isEmpty())
        item_new->setObjectName(QString::fromUtf8("item_new"));
    item_new->resize(376, 56);
    item_new->setStyleSheet(QString::fromUtf8("border-radius:12px;\n"
""));

    retranslateUi(item_new);

    QMetaObject::connectSlotsByName(item_new);
} // setupUi

void item_new::retranslateUi(QWidget *item_new)
{
    item_new->setWindowTitle(QApplication::translate("item_new", "Form", nullptr));
} // retranslateUi
