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
#include "setuppage.h"
#include "ui_setuppage.h"
#include "QSlider"
#include <QPixmap>
#include "set_alarm_repeat_dialog.h"
#include <QDebug>
#include "customstyle.h"

setuppage::setuppage( double position_x, double position_y, QWidget *parent  ) :
    QWidget(parent),
    pos_x(position_x),
    pos_y(position_y),
    ui(new Ui::setuppage)
{
    ui->setupUi(this);
    this->setWindowOpacity(0.5);

    ui->horizontalSlider->setStyle(new CustomStyle("ukui"));
    ui->pushButton->hide();
    ui->label->hide();
    ui->label_2->setAlignment(Qt::AlignHCenter);
    ui->label_4->setAlignment(Qt::AlignHCenter);
    QPixmap bgPixmap = QPixmap(":/go-bottom-symbolic.png");
    ui->pushButton_10->setIcon(bgPixmap);
    ui->pushButton_11->setIcon(bgPixmap);
    ui->pushButton_12->setIcon(bgPixmap);
    ui->pushButton_13->setIcon(bgPixmap);
    ui->pushButton_14->setIcon(bgPixmap);

    dialog_werk_day = new  set_alarm_repeat_Dialog(ui->widget, 7);
    Time_format = new  set_alarm_repeat_Dialog(ui->widget, 3);
    Pop_up_window = new  set_alarm_repeat_Dialog(ui->widget, 2);
    Reminder_off = new  set_alarm_repeat_Dialog(ui->widget, 5);
    Default_ringtone = new  set_alarm_repeat_Dialog(ui->widget, 4);
    connect(dialog_werk_day->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(werk_day_listClickslot()));
    connect(Time_format->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(Time_format_listClickslot()));
    connect(Pop_up_window->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(Pop_up_window_listClickslot()));
    connect(Reminder_off->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(Reminder_off_listClickslot()));
    connect(Default_ringtone->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(Default_ringtone_listClickslot()));

    connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(werk_day_set()) );
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(werk_day_set()) );
    connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(Time_format_set()) );
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(Time_format_set()) );
    connect(ui->pushButton_12, SIGNAL(clicked()), this, SLOT(Pop_up_window_set()) );
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(Pop_up_window_set()) );
    connect(ui->pushButton_13, SIGNAL(clicked()), this, SLOT(Reminder_off_set()) );
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(Reminder_off_set()) );
    connect(ui->pushButton_14, SIGNAL(clicked()), this, SLOT(Default_ringtone_set()) );
    connect(ui->pushButton_15, SIGNAL(clicked()), this, SLOT(Default_ringtone_set()) );

    model_setup = new QSqlTableModel(this);
    model_setup->setTable("setup");
    model_setup->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_setup->select();
    model_setup->submitAll();

    repeat_on_Pixmap = QPixmap(":/object-select-symbolic.png");
    repeat_off_Pixmap = QPixmap("");

    ui->pushButton_6->setText(model_setup->index(0, 14).data().toString());
    ui->pushButton_7->setText(model_setup->index(0, 15).data().toString());
    ui->pushButton_8->setText(model_setup->index(0, 16).data().toString());
    ui->pushButton_9->setText(model_setup->index(0, 17).data().toString());
    ui->pushButton_15->setText(model_setup->index(0, 5).data().toString());

      dialog_werk_day->hide();
      Time_format->hide() ;
      Pop_up_window->hide() ;
      Reminder_off->hide() ;
      Default_ringtone->hide() ;
}

setuppage::~setuppage()
{
    delete  model_setup;
    delete  dialog_werk_day ;
    delete  Time_format ;
    delete  Pop_up_window ;
    delete  Reminder_off ;
    delete  Default_ringtone ;
    delete  ui;
     qDebug()<<"-------setuppage-----2----";
}

void setuppage::Mute_starting()
{

}
//默认工作日日期设置回调
// Default workday date setting callback
void setuppage::werk_day_set()
{
     dialog_werk_day->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
     dialog_werk_day->setAttribute(Qt::WA_TranslucentBackground);
     QPointF position = parentWidget()->pos();
     dialog_werk_day->move(position.x()+83,position.y()+162);
     dialog_werk_day->resize(280,225);
     dialog_werk_day->listWidget->setFixedSize(280,225);
     dialog_werk_day->widget[0]->alarmLabel0->setText(tr("周一"));
     dialog_werk_day->widget[1]->alarmLabel0->setText(tr("周二"));
     dialog_werk_day->widget[2]->alarmLabel0->setText(tr("周三"));
     dialog_werk_day->widget[3]->alarmLabel0->setText(tr("周四"));
     dialog_werk_day->widget[4]->alarmLabel0->setText(tr("周五"));
     dialog_werk_day->widget[5]->alarmLabel0->setText(tr("周六"));
     dialog_werk_day->widget[6]->alarmLabel0->setText(tr("周日"));

     for (int i=0; i<7; i++) {
         if (model_setup->index(0, i+7).data().toInt()) {
             dialog_werk_day->widget[i]->alarmLabel1->setIcon(repeat_on_Pixmap);
         } else {
             dialog_werk_day->widget[i]->alarmLabel1->setIcon(repeat_off_Pixmap);
         }
     }
     dialog_werk_day->show();
}
//工作日选择单击回调
// Weekday select click callback
void setuppage::werk_day_listClickslot()
{
    model_setup->select();
    QString repeat_str;
    int num=dialog_werk_day->listWidget->currentRow();
    QString day[7] ;
    day[0]= tr("周一");
    day[1] = tr("周二");
    day[2] = tr("周三");
    day[3] = tr("周四");
    day[4] = tr("周五");
    day[5] = tr("周六");
    day[6] = tr("周日");

    switch (num)
    {
    case 0:
        if (model_setup->index(0, 7).data().toInt() ) {
            model_setup->setData(model_setup->index(0, 7), 0);
            dialog_werk_day->widget[0]->alarmLabel1->setIcon(repeat_off_Pixmap);
        } else {
            model_setup->setData(model_setup->index(0, 7), 1);
            dialog_werk_day->widget[0]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }
        break;

    case 1:
        if (model_setup->index(0, 8).data().toInt() ) {
            model_setup->setData(model_setup->index(0, 8), 0);
            dialog_werk_day->widget[1]->alarmLabel1->setIcon(repeat_off_Pixmap);
        } else {
            model_setup->setData(model_setup->index(0, 8), 1);
            dialog_werk_day->widget[1]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }
        break;

    case 2:
        if (model_setup->index(0, 9).data().toInt() ) {
            model_setup->setData(model_setup->index(0, 9), 0);
            dialog_werk_day->widget[2]->alarmLabel1->setIcon(repeat_off_Pixmap);
        } else {
            model_setup->setData(model_setup->index(0, 9), 1);
            dialog_werk_day->widget[2]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }
        break;

    case 3:
        if (model_setup->index(0, 10).data().toInt() ) {
            model_setup->setData(model_setup->index(0, 10), 0);
            dialog_werk_day->widget[3]->alarmLabel1->setIcon(repeat_off_Pixmap);
        } else {
            model_setup->setData(model_setup->index(0, 10), 1);
            dialog_werk_day->widget[3]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }
        break;

    case 4:
        if (model_setup->index(0, 11).data().toInt()) {
            model_setup->setData(model_setup->index(0, 11), 0);
            dialog_werk_day->widget[4]->alarmLabel1->setIcon(repeat_off_Pixmap);
        } else {
            model_setup->setData(model_setup->index(0, 11), 1);
            dialog_werk_day->widget[4]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }
        break;

    case 5:
        if (model_setup->index(0, 12).data().toInt() ) {
            model_setup->setData(model_setup->index(0, 12), 0);
            dialog_werk_day->widget[5]->alarmLabel1->setIcon(repeat_off_Pixmap);
        } else {
            model_setup->setData(model_setup->index(0, 12), 1);
            dialog_werk_day->widget[5]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }
        break;

    case 6:
        if (model_setup->index(0, 13).data().toInt()) {
            model_setup->setData(model_setup->index(0, 13), 0);
            dialog_werk_day->widget[6]->alarmLabel1->setIcon(repeat_off_Pixmap);
        } else {
            model_setup->setData(model_setup->index(0, 13), 1);
            dialog_werk_day->widget[6]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }
        break;

    default:
        break;
    }

    for (int i=0; i<7; i++) {
        if (model_setup->index(0, i+7).data().toInt()) {
            repeat_str=repeat_str+day[i];
        }
    }
    if (model_setup->index(0, 7).data().toInt()&&model_setup->index(0, 8).data().toInt()\
            &&model_setup->index(0, 9).data().toInt()&&model_setup->index(0, 10).data().toInt() \
            &&model_setup->index(0, 11).data().toInt()&&model_setup->index(0, 12).data().toInt() \
            &&model_setup->index(0, 13).data().toInt()) {
        repeat_str = tr("每天");
    }
    ui->pushButton_6->setText(repeat_str);
    model_setup->setData(model_setup->index(0, 14), repeat_str);

    repeat_str="";
    model_setup->submitAll();
}

//时间格式设置回调
// Time format callback
void setuppage::Time_format_set()
{
    Time_format->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    Time_format->setAttribute(Qt::WA_TranslucentBackground);
    QPointF position = parentWidget()->pos();
    Time_format->move(position.x()+83,position.y()+212);
    Time_format->resize(280,110);
    Time_format->listWidget->setFixedSize(280,110);
    Time_format->widget[0]->alarmLabel0->setText(tr("跟随系统"));
    Time_format->widget[0]->alarmLabel0->setFixedSize(200,17);
    Time_format->widget[1]->alarmLabel0->setText(tr("24小时制(23:59:59)"));
    Time_format->widget[1]->alarmLabel0->setFixedSize(200,17);
    Time_format->widget[2]->alarmLabel0->setText(tr("12小时制(下午11:59:59)"));
    Time_format->widget[2]->alarmLabel0->setFixedSize(200,17);

    Time_format->show();

}

//时间格式选择单击回调
// Time format selection click callback
void setuppage::Time_format_listClickslot()
{
    model_setup->select();

    int num=Time_format->listWidget->currentRow();

    switch (num) {
    case 0:
        model_setup->setData(model_setup->index(0, 2), 0);
        model_setup->setData(model_setup->index(0, 15), tr("跟随系统"));
        break;

    case 1:
        model_setup->setData(model_setup->index(0, 2), 1);
        model_setup->setData(model_setup->index(0, 15), tr("24小时制(23:59:59)"));
        break;

    case 2:
        model_setup->setData(model_setup->index(0, 2), 2);
        model_setup->setData(model_setup->index(0, 15), tr("12小时制(上午11:59:59)"));
        break;
    default:
        break;
    }

    ui->pushButton_7->setText(model_setup->index(0, 15).data().toString());
    Time_format->hide();
    model_setup->submitAll();
}
//弹窗方式设置回调
// Pop up mode setting callback
void setuppage::Pop_up_window_set()
{
    Pop_up_window->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    Pop_up_window->setAttribute(Qt::WA_TranslucentBackground);;
    QPointF position = parentWidget()->pos();
    Pop_up_window->move(position.x()+83,position.y()+262);
    Pop_up_window->resize(280,75);
    Pop_up_window->listWidget->setFixedSize(280,75);
    Pop_up_window->widget[0]->alarmLabel0->setText(tr("通知栏弹窗"));
    Pop_up_window->widget[1]->alarmLabel0->setText(tr("全屏弹窗"));
    Pop_up_window->show();
}

//弹窗方式选择单击回调
// Pop up mode select click callback
void setuppage::Pop_up_window_listClickslot()
{
    model_setup->select();
    int num=Pop_up_window->listWidget->currentRow();
    switch (num) {
    case 0:
            model_setup->setData(model_setup->index(0, 3), 0);
        break;

    case 1:
            model_setup->setData(model_setup->index(0, 3), 1);
        break;
    default:
        break;
    }
    if (!model_setup->index(0, 3).data().toInt()) {
        model_setup->setData(model_setup->index(0, 16), tr("通知栏弹窗"));
    } else {
        model_setup->setData(model_setup->index(0, 16), tr("全屏弹窗"));
    }
    ui->pushButton_8->setText(model_setup->index(0, 16).data().toString());
    Pop_up_window->hide();
    model_setup->submitAll();
}

//提醒关闭回调
// Reminder close callback
void setuppage::Reminder_off_set()
{
    Reminder_off->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    Reminder_off->setAttribute(Qt::WA_TranslucentBackground);
    QPointF position = parentWidget()->pos();
    Reminder_off->move(position.x()+83,position.y()+312);
    Reminder_off->resize(280,170);
    Reminder_off->listWidget->setFixedSize(280,170);
    Reminder_off->widget[0]->alarmLabel0->setFixedSize(200,17);
    Reminder_off->widget[1]->alarmLabel0->setFixedSize(200,17);
    Reminder_off->widget[2]->alarmLabel0->setFixedSize(200,17);
    Reminder_off->widget[3]->alarmLabel0->setFixedSize(200,17);
    Reminder_off->widget[4]->alarmLabel0->setFixedSize(200,17);
    Reminder_off->widget[0]->alarmLabel0->setText(tr("2分钟后提醒"));
    Reminder_off->widget[1]->alarmLabel0->setText(tr("5分钟后提醒"));
    Reminder_off->widget[2]->alarmLabel0->setText(tr("10分钟后提醒"));
    Reminder_off->widget[3]->alarmLabel0->setText(tr("30分钟后提醒"));
    Reminder_off->widget[4]->alarmLabel0->setText(tr("60分钟后提醒"));
    Reminder_off->show();
}

//提醒关闭选择单击回调
// Reminder off select click callback
void setuppage::Reminder_off_listClickslot()
{
    model_setup->select();
    int num=Reminder_off->listWidget->currentRow();
    model_setup->setData(model_setup->index(0, 4), num);

    switch (num) {
    case 0:
        model_setup->setData(model_setup->index(0, 17), tr("2分钟后提醒"));
        break;
    case 1:
        model_setup->setData(model_setup->index(0, 17), tr("5分钟后提醒"));
        break;
    case 2:
        model_setup->setData(model_setup->index(0, 17), tr("10分钟后提醒"));
        break;
    case 3:
        model_setup->setData(model_setup->index(0, 17), tr("30分钟后提醒"));
        break;
    case 4:
        model_setup->setData(model_setup->index(0, 17), tr("60分钟后提醒"));
        break;
    default:
        break;
    }
    ui->pushButton_9->setText(model_setup->index(0, 17).data().toString());
    Reminder_off->hide();
    model_setup->submitAll();
}
//默认铃声设置回调
// Default ringtone setting callback
void setuppage::Default_ringtone_set()
{
    Default_ringtone->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    Default_ringtone->setAttribute(Qt::WA_TranslucentBackground);
    QPointF position = parentWidget()->pos();
    Default_ringtone->move(position.x()+83,position.y()+362);
    Default_ringtone->resize(280,129);
    Default_ringtone->listWidget->setFixedSize(280,129);
    Default_ringtone->widget[0]->alarmLabel0->setText(tr("玻璃"));
    Default_ringtone->widget[1]->alarmLabel0->setText(tr("犬吠"));
    Default_ringtone->widget[2]->alarmLabel0->setText(tr("声呐"));
    Default_ringtone->widget[3]->alarmLabel0->setText(tr("雨滴"));
    Default_ringtone->show();

}

//默认铃声选择单击回调
// Default ring tone selection click callback
void setuppage::Default_ringtone_listClickslot()
{
    model_setup->select();

    int num=Default_ringtone->listWidget->currentRow();

    switch (num)
    {
    case 0:
        model_setup->setData(model_setup->index(0, 5), tr("玻璃"));
        break;
    case 1:
        model_setup->setData(model_setup->index(0, 5), tr("犬吠"));
        break;
    case 2:
        model_setup->setData(model_setup->index(0, 5), tr("声呐"));
        break;
    case 3:
        model_setup->setData(model_setup->index(0, 5), tr("雨滴"));
        break;
    default:
        break;
    }
    ui->pushButton_15->setText(model_setup->index(0, 5).data().toString());
    Default_ringtone->hide();
    model_setup->submitAll();
}

