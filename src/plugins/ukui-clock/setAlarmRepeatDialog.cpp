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
#include "setAlarmRepeatDialog.h"
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QBitmap>
#include <QPainter>
#include <QDebug>
#include <QScroller>
#include <QPainterPath>

extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);

set_alarm_repeat_Dialog::set_alarm_repeat_Dialog(QWidget *parent , int rowNum ) :
    rowNum_all(rowNum),
    QWidget(parent)
{
    setupUi(this);
    //this->setStyleSheet("border-radius:4px;border:0px  rgba();");
    //this->listWidget->setStyleSheet("background-color: rgba(233,233,233,0);");

    this->setWindowOpacity(0.9);
    for (int i = 0; i < rowNum_all; i++) {
        set_aItem(i);
    }
    listWidget->installEventFilter(this);
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
//  listWidget->setStyleSheet("selection-background-color: rgba(39,207,129,0.9);");

    retranslateUi(set_alarm_repeat_Dialog);

    QMetaObject::connectSlotsByName(set_alarm_repeat_Dialog);
}   // setupUi

void set_alarm_repeat_Dialog::retranslateUi(QWidget( *set_alarm_repeat_Dialog))
{
    set_alarm_repeat_Dialog->setWindowTitle(QApplication::translate("set_alarm_repeat_Dialog", "Dialog", nullptr));
}   // retranslateUi

void set_alarm_repeat_Dialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;

    QStyleOption opt;
    opt.init(this);
    painter.setBrush(opt.palette.color(QPalette::Base));

    if(QColor(255,255,255) == opt.palette.color(QPalette::Base) ||
       QColor(248,248,248) == opt.palette.color(QPalette::Base))
    {
        painter.setBrush(QColor(233, 233, 233));
    }else{
        painter.setBrush(QColor(48,48,51));
    }

    painter.setPen(Qt::transparent);
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 0);
    rect.setHeight(rect.height() - 0);
    painter.drawRoundedRect(rect, 7, 7);
    {
        QPainterPath painterPath;
        painterPath.addRoundedRect(rect, 4, 4);
        painter.drawPath(painterPath);
    }
    QWidget::paintEvent(event);
}

bool set_alarm_repeat_Dialog::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == listWidget && event->type() == QEvent::Paint)
    {
        showPaint(); //响应函数
    }
    return QWidget::eventFilter(watched,event);
}

//实现响应函数 listwidget上色
void set_alarm_repeat_Dialog::showPaint()
{
    QPalette palette = listWidget->palette();
    QColor ColorPlaceholderText(248,163,76,255);
    QBrush brush3;
    brush3.setColor(ColorPlaceholderText);
    QStyleOption opt;
    opt.init(this);
    if(QColor(255,255,255) == opt.palette.color(QPalette::Base) || QColor(248,248,248) == opt.palette.color(QPalette::Base))
    {
        palette.setBrush(QPalette::Background, QBrush(QColor(133, 233, 233)));
    }else{
        palette.setBrush(QPalette::Background, QBrush(QColor(48,48,51)));
    }
    listWidget->setPalette(palette);
}


set_alarm_repeat_widget::set_alarm_repeat_widget(QWidget *parent):
    QWidget(parent)
{
    this->setFixedSize(276, 32);

    alarmLabel0 = new QLabel(this);
    alarmLabel0->move(5, 0);
    alarmLabel0->setFixedSize(160, 32);
    alarmLabel0->setStyleSheet("background-color: rgb();");
    alarmLabel0->setText("选项");

    alarmLabel1 = new ClickableLabel(this);
    alarmLabel1->move(240, 0);
    alarmLabel1->setFixedSize(34, 32);
    alarmLabel1->setStyleSheet("background-color: rgb();");
    alarmLabel1->setText("");
}

set_alarm_repeat_widget::~set_alarm_repeat_widget()
{
    delete   alarmLabel0;
    delete   alarmLabel1;
    qDebug()<<"-------set_alarm_repeat_Dialog-----2----";
}

void set_alarm_repeat_widget::paintEvent(QPaintEvent *event)
{

}
