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
#include "set_alarm_repeat_dialog.h"
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QBitmap>
#include <QPainter>
#include <QDebug>
#include <QScroller>
set_alarm_repeat_Dialog::set_alarm_repeat_Dialog(QWidget *parent , int rowNum ) :
    rowNum_all(rowNum),
    QWidget(parent)
{
    setupUi(this);
    this->setStyleSheet("background:rgba(48,48,51,1);border-radius:4px;");
    this->setWindowOpacity(0.9);
    for (int i = 0; i < rowNum_all; i++) {
        set_aItem(i);
    }
}


set_alarm_repeat_Dialog::~set_alarm_repeat_Dialog()
{
    for (int i =0 ; i <rowNum_all; i++) {
        delete widget[i];
        delete aItem[i];
    }
    delete listWidget;
    qDebug()<<"-------set_alarm_repeat_Dialog---------";
}

void set_alarm_repeat_Dialog::set_aItem(int rowNum)
{
    aItem[rowNum] =new QListWidgetItem;
    aItem[rowNum]->setSizeHint(QSize(276, 32));
    aItem[rowNum]->setTextColor(QColor(255, 0, 0, 255));
    listWidget->addItem(aItem[rowNum]);
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    widget[rowNum] = new set_alarm_repeat_widget(listWidget);
    listWidget->setItemWidget(aItem[rowNum],widget[rowNum]);
    QScroller::grabGesture(listWidget,QScroller::LeftMouseButtonGesture); //设置鼠标左键拖动
    listWidget -> setVerticalScrollMode(QAbstractItemView::ScrollPerPixel); // 设置像素级滑动
}

void set_alarm_repeat_Dialog::setupUi(QWidget( *set_alarm_repeat_Dialog))
{
    if (set_alarm_repeat_Dialog->objectName().isEmpty())
        set_alarm_repeat_Dialog->setObjectName(QString::fromUtf8("set_alarm_repeat_Dialog"));
    set_alarm_repeat_Dialog->resize(280, 162);
    listWidget = new QListWidget(set_alarm_repeat_Dialog);
    listWidget->setObjectName(QString::fromUtf8("listWidget"));
    listWidget->setGeometry(QRect(0, 0, 280, 162));
    listWidget->setStyleSheet("selection-background-color: rgba(39,207,129,0.9);");

    retranslateUi(set_alarm_repeat_Dialog);

    QMetaObject::connectSlotsByName(set_alarm_repeat_Dialog);
} // setupUi

void set_alarm_repeat_Dialog::retranslateUi(QWidget( *set_alarm_repeat_Dialog))
{
    set_alarm_repeat_Dialog->setWindowTitle(QApplication::translate("set_alarm_repeat_Dialog", "Dialog", nullptr));
} // retranslateUi


set_alarm_repeat_widget::set_alarm_repeat_widget(QWidget *parent):
    QWidget(parent)
{
    this->setStyleSheet("border-radius:12px;");
    this->setFixedSize(276, 32);

    alarmLabel0 = new QLabel(this);
    alarmLabel0->move(5, 9);
    alarmLabel0->setFixedSize(100, 17);
    alarmLabel0->setStyleSheet("font: 11pt 'Sans Serif';background-color: rgb();");
    alarmLabel0->setText("选项");

    alarmLabel1 = new QPushButton(this);
    alarmLabel1->move(240, 9);
    alarmLabel1->setFixedSize(34, 17);
    alarmLabel1->setStyleSheet("font: 11pt 'Sans Serif';background-color: rgb();");
    alarmLabel1->setText("");
}

set_alarm_repeat_widget::~set_alarm_repeat_widget()
{
    delete   alarmLabel0;
    delete   alarmLabel1;
    qDebug()<<"-------set_alarm_repeat_Dialog-----2----";
}




