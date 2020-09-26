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
#include "stopwatchItem.h"
#include<QApplication>
#include <QDebug>

stopwatch_item::stopwatch_item(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    this->setFixedSize(376, 56);
    stopwatch1 = new QLabel(this);//计次
    stopwatch1->move(24, 9);
    stopwatch1->setFixedSize(100, 17);
    stopwatch1->setStyleSheet("font: 11pt ;background-color: rgb();width:45px;\
                              height:17px;\
                              font-size:18px;\
                              font-weight:400;\
                              color:rgba(255,255,255,1);");
    stopwatch1->setText("起床铃");


    stopwatch2 = new QLabel( this);//间隔
    stopwatch2->move(24, 34);
    stopwatch2->setFixedSize(110, 17);
    stopwatch2->setStyleSheet("font: 9pt ;color: rgb(148, 148, 148);background-color: rgb();width:85px;\
                              height:14px;\
                              font-size:14px;\
                              font-weight:400;\
                              opacity:0.45;");
    stopwatch2->setText("工作日");
    stopwatch2->setVisible(true);


    stopwatch_line = new QFrame(this);//线
    stopwatch_line->move(13, 55);
    stopwatch_line->setFixedSize(350, 1);
    stopwatch_line->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);background-color: rgb(102, 102, 102);"));
    stopwatch3 = new QLabel(this);//记次时间
    stopwatch3->move(209,12);
    stopwatch3->setFixedSize(145, 29);
    stopwatch3->setStyleSheet("font: 17pt ;background-color: rgb();width:114px;\
                              height:22px;\
                              font-size:30px;\
                              font-weight:400;\
                              color:rgba(255,255,255,1)\
                              ;");
    stopwatch3->setAlignment(Qt::AlignRight);
    stopwatch3->setText("00:00");
    stopwatch3->setVisible(true);
}

stopwatch_item::~stopwatch_item()
{
    delete stopwatch1;
    delete stopwatch2;
    delete stopwatch3;

    delete stopwatch_line;
     qDebug()<<"-------stopwatch_item---------";

}


void stopwatch_item::setupUi(QWidget *stopwatch_item)
{
    if (stopwatch_item->objectName().isEmpty())
        stopwatch_item->setObjectName(QString::fromUtf8("stopwatch_item"));
    stopwatch_item->resize(376, 56);

    retranslateUi(stopwatch_item);

    QMetaObject::connectSlotsByName(stopwatch_item);
} // setupUi

void stopwatch_item::retranslateUi(QWidget *stopwatch_item)
{
    stopwatch_item->setWindowTitle(QApplication::translate("stopwatch_item", "Form", nullptr));
} // retranslateUi
