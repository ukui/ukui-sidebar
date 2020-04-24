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
#include "clock.h"
#include "ui_clock.h"
#include <QPainter>
#include <math.h>
#include <QTimerEvent>
#include <QTime>
#include <QTimer>
#include <QDialog>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QMatrix>
#include <QFont>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QUrl>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QModelIndex>
#include <QSqlQuery>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QVBoxLayout>
#include <QDebug>
#include "debug.h"
#include <unistd.h>
#include <QTimer>
#include <QTime>
#include "connection.h"
#include <QMessageBox>
#include "item_new.h"
#include "set_clock.h"
#include "stopwatch_item.h"
#include "messagebox.h"
#include "notice_dialog.h"
#include <QBitmap>
#include <QProcess>
#include<QScreen>
#include "notice_alarm.h"
#include "ui_notice_alarm.h"


const double PI=3.141592;

Clock::Clock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Clock)
{
    ui->setupUi(this);
    createConnection();

    QBitmap bmp(this->size());

    bmp.fill();

    QPainter p(&bmp);

    p.setPen(Qt::NoPen);

    p.setBrush(Qt::black);

    p.setRenderHint(QPainter::Antialiasing);

    p.drawRoundedRect(bmp.rect(),6,6);

    setMask(bmp);

    this->setWindowTitle(tr("闹钟"));
    setWindowFlags(Qt::FramelessWindowHint);   /* 开启窗口无边框 */
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->set_page->setStyleSheet("QWidget{background-color: rgba(14, 19, 22, 0.95);}");
    button_image_init();
    Countdown_init();
    stopwatch_init();
    clock_init();
    setup_init();
    this->setFixedSize(454,660);
}

Clock::~Clock()
{
    delete timer_set_page;
    delete timer_Surplus;
    delete timer;
    delete timer_2;
    delete countdown_timer;
    delete model;
    delete model_setup;
    delete setup_page;
    delete dialog_repeat;
    delete dialog_music;
    delete time_music;
    delete count_music_sellect;
    delete ui->page_5;
    delete ui;
}

void Clock::button_image_init()
{
    pixmap1 = QPixmap(":/icon-1.png");
    pixmap2 = QPixmap(":/icon-2.png");
    pixmap3 = QPixmap(":/icon-3.png");
    pixmap4 = QPixmap(":/icon-4-16x16.png");
    pixmap5 = QPixmap(":/window-close-symbolic.png");
    pixmap6 = QPixmap(":/window-minimize-symbolic.png");
    pixmap7 = QPixmap(":/open-menu-symbolic.png");
    pixmap8 = QPixmap(":/start_1.png");
    pixmap9 = QPixmap(":/start_2.png");
    pixmap10 = QPixmap(":/push_1.png");
    pixmap11 = QPixmap(":/push_2.png");
    bgPixmap = QPixmap(":/go-bottom-symbolic.png");
    repeat_on_Pixmap = QPixmap(":/object-select-symbolic.png");
    repeat_off_Pixmap = QPixmap("");
    delBtnPixmap = QPixmap(":/deleteBtn.png");
    on_pixmap = QPixmap(":/alarm_on.png");
    off_pixmap = QPixmap(":/alarm_off.png");
    clock_icon = QPixmap(":/kylin-alarm-clock.svg");
    this->setWindowIcon(clock_icon);

    ui->pushButton->setIcon(pixmap1);
    ui->pushButton_2->setIcon(pixmap4);
    ui->pushButton_3->setIcon(pixmap2);

    ui->pushButton_4->setIcon(pixmap6);
    ui->pushButton_4->setFlat(true);
    ui->pushButton_4->setVisible(true);
    ui->pushButton_4->setFocusPolicy(Qt::NoFocus);

    ui->pushButton_5->setIcon(pixmap5);
    ui->pushButton_5->setFlat(true);
    ui->pushButton_5->setVisible(true);
    ui->pushButton_5->setFocusPolicy(Qt::NoFocus);

    ui->pushButton_12->setIcon(pixmap7);
    ui->pushButton_12->setFlat(true);
    ui->pushButton_12->setVisible(true);
    ui->pushButton_12->setFocusPolicy(Qt::NoFocus);

    ui->pushButton_4->setStyleSheet("QPushButton{border-image: url(://image/mini_light.png);}"
                  "QPushButton:hover{border-image: url(://image/mini2.png);}"
                  "QPushButton:pressed{border-image: url(://image/mini3.png);}");
    ui->pushButton_5->setStyleSheet("QPushButton{border-image: url(://image/close_light.png);}"
                  "QPushButton:hover{border-image: url(://image/close2.png);}"
                  "QPushButton:pressed{border-image: url(://image/close3.png);}");
    ui->pushButton_12->setStyleSheet("QPushButton{border-image: url(://image/more_light.png);}"
                  "QPushButton:hover{border-image: url(://image/more2.png);}"
                  "QPushButton:pressed{border-image: url(://image/more3.png);}");
}

void Clock::Countdown_init()
{
    //初始化定时器
    countdown_timer = new QTimer();
    //信号和槽
    connect(ui->count_stat, SIGNAL(clicked()), this, SLOT(startbtn_countdown()) );
    connect(countdown_timer, SIGNAL(timeout()), this, SLOT(stat_countdown()));
    ui->pushButton_19->setIcon(bgPixmap);
    //设置定时器每个多少毫秒发送一个timeout()信号
    countdown_timer->setInterval(1000);
    countdown_hour = 0;
    countdown_minute = 0;
    countdown_second = 9;
    countdown_pushflag = 0;
    countdown_isStarted = 0;
    countdown_isStarted_2 = 0;
    ui->page_5->RoundBar3->ring_max = 3600;
    ui->page_5->RoundBar3->setValue(3600);//初始化倒计时进度圈
}

void Clock::stopwatch_init()
{
    //初始化定时器
    timer = new QTimer();
    //信号和槽
    connect(timer, SIGNAL(timeout()), this, SLOT(Count_down()));
    //设置定时器每个多少毫秒发送一个timeout()信号
    timer->setInterval(10);
    ui->label_4->setText("00:00.00");
    isStarted = 0;
    hour=0;
    minute=0;
    second=0;
    pushflag=0 ;
    on_pushButton_2_clicked();//初始显示闹钟界面
    //时间间隔定时器
    timer_2 = new QTimer();
    connect(timer_2, SIGNAL(timeout()), this, SLOT(stopwatch_jg()));
    timer_2->setInterval(10);
    stopwatch_hour = 0;
    stopwatch_minute = 0;
    stopwatch_second = 0;
    stopwatch_isStarted = 0;
}

void Clock::clock_init()
{
    ui->pushButton_10->setIcon(bgPixmap);
    ui->pushButton_7->setIcon(bgPixmap);
    ui->pushButton_16->setIcon(bgPixmap);
    ui->lineEdit->setAlignment(Qt::AlignRight);
    QTimer *timer_clock = new QTimer(this);
    connect(timer_clock, SIGNAL(timeout()), this, SLOT(timerUpdate()) );//动态获取时间
    timer_clock->start(1000);
    connect( ui->addAlarmBtn, SIGNAL(clicked()), this, SLOT(set_Alarm_Clock()) );//添加闹钟

    ui->label_6->setAlignment(Qt::AlignHCenter);
    ui->label_7->setAlignment(Qt::AlignHCenter);
    ui->label_12->setAlignment(Qt::AlignHCenter);
    ui->label_4->setAlignment(Qt::AlignHCenter);
    ui->label->setAlignment(Qt::AlignHCenter);
    ui->label_2->setAlignment(Qt::AlignHCenter);
    ui->label_3->setAlignment(Qt::AlignHCenter);
    model = new QSqlTableModel(this);
    model->setTable("clock");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select(); //选取整个表的所有行

    model_setup = new QSqlTableModel(this);
    model_setup->setTable("setup");
    model_setup->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_setup->select();

    connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(listdoubleClickslot()));
    connect(ui->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(listClickslot()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(deleteAlarm()) );
    connect(ui->set_alarm_savebtn, SIGNAL(clicked()), this, SLOT(set_alarm_save()) );
    connect(ui->set_alarm_cancelbtn, SIGNAL(clicked()), this, SLOT(alarm_Cancel_save()) );
    connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(alarm_repeat()) );
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(alarm_repeat()) );
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(select_Music()) );
    connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(select_Music()) );
    connect(ui->pushButton_16, SIGNAL(clicked()), this, SLOT(time_Music()) );
    connect(ui->pushButton_17, SIGNAL(clicked()), this, SLOT(time_Music()) );
    connect(ui->pushButton_12, SIGNAL(clicked()), this, SLOT(set_up_page()) );
    connect(ui->pushButton_20, SIGNAL(clicked()), this, SLOT(countdown_music_sellect()));

    //单击时间提示计时器
    timer_Surplus = new QTimer();
    connect(timer_Surplus, SIGNAL(timeout()), this, SLOT(listClickslot()));
    timer_Surplus->setInterval(1000);
    //闹钟设置界面时间提示计时器
    timer_set_page = new QTimer();
    connect(timer_set_page, SIGNAL(timeout()), this, SLOT(verticalscroll_ring_time()));
    timer_set_page->setInterval(100);
    updateAlarmClock();
}


void Clock::setup_init()
{
    countdown_set_start_time();//倒计时初始化数字转盘
    ui->label_8->hide();
    connect(ui->label, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()) );//扩大页面切换反映区
    connect(ui->label_2, SIGNAL(clicked()), this, SLOT(on_pushButton_2_clicked()) );
    connect(ui->label_3, SIGNAL(clicked()), this, SLOT(on_pushButton_3_clicked()) );
    ui->pushButton_20->setText(model_setup->index(0, 19).data().toString());
    alarm_set_start_time();//闹钟初始化数字转盘
    model_setup_set(); //人设置数据库初始化
    text_timerUpdate();
    ui->pushButton_20->setText(model_setup->index(0, 19).data().toString());
    for (int i=0; i<9; i++) {
        repeat_day[i] = 0;
    }
    dialog_repeat = new  set_alarm_repeat_Dialog(ui->set_page, 9);dialog_repeat->hide();
    dialog_music = new  set_alarm_repeat_Dialog(ui->set_page, 4);dialog_music->hide();
    time_music = new  set_alarm_repeat_Dialog(ui->set_page, 5);time_music->hide();
    count_music_sellect = new  set_alarm_repeat_Dialog(ui->page, 4);count_music_sellect->hide();
    connect(dialog_repeat->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(repeat_listClickslot()));
    connect(dialog_music->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(music_listClickslot()));
    connect(time_music->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(time_music_listClickslot()));
}


//时间间隔执行
void Clock::stopwatch_jg()
{
    if(stopwatch_hour < 10){
        QString hours_str = QString::number(stopwatch_hour);
        stopwatch_jg_h = "0"+hours_str;
    }else {
        stopwatch_jg_h = QString::number(stopwatch_hour);
    }

    if(stopwatch_minute < 10){
        QString minute_str = QString::number(stopwatch_minute);
        stopwatch_jg_m = "0"+minute_str;
    }else {
        stopwatch_jg_m = QString::number(stopwatch_minute);
    }

    if(stopwatch_second < 10){
        QString second_str = QString::number(stopwatch_second);
        stopwatch_jg_s = "0"+second_str;
    }else {
        stopwatch_jg_s = QString::number(stopwatch_second);
    }

    ui->label_5->setText(stopwatch_jg_h+":"+stopwatch_jg_m+"."+stopwatch_jg_s);

    stopwatch_second++;
    if(stopwatch_second==100){
        stopwatch_minute++; stopwatch_second=0;}
    if(stopwatch_minute==60){
        stopwatch_hour++; stopwatch_minute=0;}
}

//秒表执行
void Clock::Count_down()
{
    if(hour < 10){
        QString hours_str = QString::number(hour);
        stopwatch_h = "0"+hours_str;
    }else {
        stopwatch_h = QString::number(hour);
    }

    if(minute < 10){
        QString minute_str = QString::number(minute);
        stopwatch_m = "0"+minute_str;
    }else {
        stopwatch_m = QString::number(minute);
    }

    if(second < 10){
        QString second_str = QString::number(second);
        stopwatch_s = "0"+second_str;
    }else {
        stopwatch_s = QString::number(second);
    }

    ui->label_4->setText(stopwatch_h+":"+stopwatch_m+"."+stopwatch_s);

    second++;
    if(second==100){
        minute++; second=0;}
    if(minute==60){
        hour++; minute=0;}

}

void Clock::on_pushButton_Start_clicked()
{
    if (!isStarted){
        ui->pushButton_Start->setText(tr("暂停"));
        ui->pushButton_Start->setStyleSheet("QPushButton{color: rgb(255, 255, 255);\
                                            background-color: rgba(231,159,78,0.9);\
                                            border-radius:34px;}\
                                            QPushButton:hover{background:rgba(143, 97, 47, 0.6)}");
        ui->pushButton_ring->setStyleSheet("QPushButton{color: rgb(255, 255, 255);\
                                           background:rgba(44,44,46,1);\
                                           border:1px solid rgba(68,68,71,1);\
                                           border-radius:4px;}\
                                           QPushButton:hover{background:rgba(143, 97, 47, 0.1)}");
        ui->pushButton_timeselect->setStyleSheet("background:rgba(28,28,30,1);\
                                           border:1px solid rgba(52,52,56,1);\
                                           border-radius:4px;\
                                           color: rgb(65, 65, 65);");

        if(stopwatch_isStarted == 0)
        {
            timer_2->start();
            stopwatch_isStarted = 1;
        }
        timer->start();
        isStarted=1;
    } else {
        timer->stop();
        if(stopwatch_isStarted == 1)//查询间隔计时器是否启动
        {
            timer_2->stop();
            stopwatch_isStarted = 0;
        }
        isStarted=0;
        ui->pushButton_Start->setText(tr("继续"));
        ui->pushButton_Start->setStyleSheet("QPushButton{\
                                            color: rgb(255, 255, 255);\
                                            background-color: rgba(39,207,129,0.9);\
                                            border-radius:34px;\
                                            }QPushButton:hover{background-color: rgb(27, 143, 89);}");
        ui->pushButton_ring->setStyleSheet("background:rgba(28,28,30,1);\
                                           border:1px solid rgba(52,52,56,1);\
                                           border-radius:4px;\
                                           color: rgb(65, 65, 65);");
        ui->pushButton_timeselect->setStyleSheet("QPushButton{color: rgb(255, 255, 255);\
                                           background:rgba(44,44,46,1);\
                                           border:1px solid rgba(68,68,71,1);\
                                           border-radius:4px;}\
                                           QPushButton:hover{background:rgba(143, 97, 47, 0.1)}");
    }
    return;
}

//计次
void Clock::on_pushButton_ring_clicked()
{
    if(!isStarted)
    {
        return;
    }

    if(stopwatch_isStarted == 0)
    {
        timer_2->start();
        stopwatch_isStarted = 1;
    }
    if(stopwatch_item_flag < 100){
        stopwatch_aItem[stopwatch_item_flag] =new QListWidgetItem;
        stopwatch_aItem[stopwatch_item_flag]->setSizeHint(QSize(376,56));
        stopwatch_aItem[stopwatch_item_flag]->setTextColor(QColor(255, 0, 0, 255));
        ui->listWidget_2->insertItem(0,stopwatch_aItem[stopwatch_item_flag]);

        ui->listWidget_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->listWidget_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        stopwatch_w[stopwatch_item_flag] = new stopwatch_item(ui->listWidget_2);

        stopwatch_w[stopwatch_item_flag]->stopwatch1->setText(tr("计次")+QString::number(stopwatch_item_flag));
        stopwatch_w[stopwatch_item_flag]->stopwatch2->setText(tr("间隔 ")+stopwatch_jg_h+":"+stopwatch_jg_m+"."+stopwatch_jg_s);
        stopwatch_w[stopwatch_item_flag]->stopwatch3->setText(stopwatch_h+":"+stopwatch_m+"."+stopwatch_s);

        ui->listWidget_2->setItemWidget(stopwatch_aItem[stopwatch_item_flag],stopwatch_w[stopwatch_item_flag]);

        stopwatch_hour = 0;
        stopwatch_minute = 0;
        stopwatch_second = 0;

        qDebug()<< stopwatch_item_flag;

        stopwatch_item_flag++;
    }
}


//复位
void Clock::on_pushButton_timeselect_clicked()
{
    if(nullptr != timer){
        if(isStarted)
        {
            return;
        }

        timer->stop();
        timer_2->stop();
        ui->label_4->setText("00:00.00");
        ui->label_5->setText("00:00.00");
        isStarted = 0;
        stopwatch_isStarted = 0;
        hour = 0; minute = 0;second = 0;
        stopwatch_hour = 0;
        stopwatch_minute = 0;
        stopwatch_second = 0;
        ui->pushButton_Start->setText(tr("开始"));
        ui->pushButton_Start->setStyleSheet("QPushButton{\
                                            color: rgb(255, 255, 255);\
                                            background-color: rgba(39,207,129,0.9);\
                                            border-radius:34px;\
                                            }QPushButton:hover{background-color: rgb(27, 143, 89);}");
        ui->pushButton_timeselect->setStyleSheet("background:rgba(28,28,30,1);\
                                           border:1px solid rgba(52,52,56,1);\
                                           border-radius:4px;\
                                           color: rgb(65, 65, 65);");

        for (int i=0; i < stopwatch_item_flag; i++) {
            delete stopwatch_w[i];
            delete stopwatch_aItem[i];
        }
        stopwatch_item_flag = 0;
    }
}

//窗口关闭
void Clock::on_pushButton_5_clicked()
{
    ui->stackedWidget_3->raise();
    ui->stackedWidget->raise();
    ui->pushButton_4->raise();
    ui->pushButton_5->raise();
    ui->pushButton_12->raise();
    this->hide();
}

//窗口最小化
void Clock::on_pushButton_4_clicked()
{
    this->showNormal();
    this->showMinimized();
}

//倒计时切换
void Clock::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton->setStyleSheet("background-color: rgba(39,207,129,0.9); border-radius:4px;");
    ui->label->setStyleSheet("color: rgb(39, 207, 129);");
    ui->pushButton_2->setStyleSheet("QPushButton{background-color: rgb(14, 19, 22);}"
                                    "QPushButton:hover{background-color: rgb(27, 143, 89);border-radius:4px;}");
    ui->label_2->setStyleSheet("color: rgb(255, 255, 255);");
    ui->pushButton_3->setStyleSheet("QPushButton{background-color: rgb(14, 19, 22);}"
                                    "QPushButton:hover{background-color: rgb(27, 143, 89);border-radius:4px;}");
    ui->label_3->setStyleSheet("color: rgb(255, 255, 255);");

    ui->pushButton->setFlat(0);
    ui->pushButton_2->setFlat(1);
    ui->pushButton_3->setFlat(1);
}

//闹钟窗口切换
void Clock::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->pushButton_2->setStyleSheet("background-color: rgba(39,207,129,0.9); border-radius:4px;");
    ui->label_2->setStyleSheet("color: rgb(39, 207, 129);");
    ui->pushButton->setStyleSheet("QPushButton{background-color: rgb(14, 19, 22);}"
                                  "QPushButton:hover{background-color: rgb(27, 143, 89);border-radius:4px;}");
    ui->label->setStyleSheet("color: rgb(255, 255, 255);");
    ui->pushButton_3->setStyleSheet("QPushButton{background-color: rgb(14, 19, 22);}"
                                    "QPushButton:hover{background-color: rgb(27, 143, 89);border-radius:4px;}");
    ui->label_3->setStyleSheet("color: rgb(255, 255, 255);");

    ui->pushButton->setFlat(1);
    ui->pushButton_2->setFlat(0);
    ui->pushButton_3->setFlat(1);
}

//秒表窗口切换
void Clock::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->pushButton_3->setStyleSheet("background-color:rgba(39,207,129,0.9); border-radius:4px;");
    ui->label_3->setStyleSheet("color: rgb(39, 207, 129);");
    ui->pushButton_2->setStyleSheet("QPushButton{background-color: rgb(14, 19, 22);}"
                                    "QPushButton:hover{background-color: rgb(27, 143, 89);border-radius:4px;}");
    ui->label_2->setStyleSheet("color: rgb(255, 255, 255);");
    ui->pushButton->setStyleSheet("QPushButton{background-color: rgb(14, 19, 22);}"
                                  "QPushButton:hover{background-color: rgb(27, 143, 89);border-radius:4px;}");
    ui->label->setStyleSheet("color: rgb(255, 255, 255);");

    ui->pushButton->setFlat(1);
    ui->pushButton_2->setFlat(1);
    ui->pushButton_3->setFlat(0);
}

//------------------------------------------------------闹钟------------------------------------------------------

//闹钟上方电子表
void Clock::text_timerUpdate()
{
    QProcess process;
    process.start("gsettings get org.ukui.control-center.panel.plugins hoursystem");
    process.waitForFinished();
    QByteArray output = process.readAllStandardOutput();
    QString str_output = output;

    model_setup->select();
    QTime time = QTime::currentTime();
    int timeH = time.hour();

    if(model_setup->index(0, 2).data().toInt() == 1){
        ui->label_6->setText(time.toString("hh")+":"+time.toString("mm")+":"+time.toString("ss"));
        ui->label_15->setText("");
    }else if(model_setup->index(0, 2).data().toInt() == 2){
        if(timeH > 12){
            timeH = timeH - 12;
            if(timeH<10){
                ui->label_6->setText("0"+QString::number(timeH)+":"+time.toString("mm")+":"+time.toString("ss"));
            }else{
                ui->label_6->setText(QString::number(timeH)+":"+time.toString("mm")+":"+time.toString("ss"));
            }
            ui->label_15->setText(tr("下午"));
        }else{
            ui->label_6->setText(time.toString("hh")+":"+time.toString("mm")+":"+time.toString("ss"));
            ui->label_15->setText(tr("上午"));
        }
    }else{
        if(str_output.compare("'24'\n") == 0){
            ui->label_6->setText(time.toString("hh")+":"+time.toString("mm")+":"+time.toString("ss"));
            ui->label_15->setText("");
        }else{
            if(timeH > 12){
                timeH = timeH - 12;
                if(timeH<10){
                    ui->label_6->setText("0"+QString::number(timeH)+":"+time.toString("mm")+":"+time.toString("ss"));
                }else{
                    ui->label_6->setText(QString::number(timeH)+":"+time.toString("mm")+":"+time.toString("ss"));
                }
                ui->label_6->setText(QString::number(timeH)+":"+time.toString("mm")+":"+time.toString("ss"));
                ui->label_15->setText(tr("下午"));
            }else{
                ui->label_6->setText(QString::number(timeH)+":"+time.toString("mm")+":"+time.toString("ss"));
                ui->label_15->setText(tr("上午"));
            }
        }
    }
}

//动态监控闹钟与本地时间
void Clock::timerUpdate()
{
    QTime time = QTime::currentTime();
    int timeH = time.hour();
    int timeM = time.minute();
    int timeS = time.second();

    model_setup->select();
    text_timerUpdate();

    int rowNum = model->rowCount();
    for(int i=0; i<rowNum; i++)
    {
        //判断星期
        QDateTime current_date_time = QDateTime::currentDateTime();

        if(current_date_time.toString("ddd").compare(tr("周一"))==0 &&  model->index(i, 6).data().toInt() == 0)
            continue;
        if(current_date_time.toString("ddd").compare(tr("周二"))==0 &&  model->index(i, 7).data().toInt() == 0)
            continue;
        if(current_date_time.toString("ddd").compare(tr("周三"))==0 &&  model->index(i, 8).data().toInt() == 0)
            continue;
        if(current_date_time.toString("ddd").compare(tr("周四"))==0 &&  model->index(i, 9).data().toInt() == 0)
            continue;
        if(current_date_time.toString("ddd").compare(tr("周五"))==0 &&  model->index(i, 10).data().toInt() == 0)
            continue;
        if(current_date_time.toString("ddd").compare(tr("周六"))==0 &&  model->index(i, 11).data().toInt() == 0)
            continue;
        if(current_date_time.toString("ddd").compare(tr("周日"))==0 &&  model->index(i, 12).data().toInt() == 0)
            continue;

        //判断开关
        if( model->index(i, 3).data().toInt() == 1){
            continue;

        }
        if(timeH == model->index(i, 0).data().toInt()
                && timeM == model->index(i, 1).data().toInt()
                && timeS == 0)
        {
            double music_time = 30;
            if(model->index(i, 13).data().toString().compare(tr("2分钟"))==0){
                music_time = 2*60;
            }else if (model->index(i, 13).data().toString().compare(tr("3分钟"))==0) {
                music_time = 3*60;
            }else if (model->index(i, 13).data().toString().compare(tr("4分钟"))==0) {
                music_time = 4*60;
            }else if (model->index(i, 13).data().toString().compare(tr("6分钟"))==0){
                music_time = 6*60;
            }else {
                music_time = 60;
            }
            notice_dialog_show(music_time, i );
            if(model->index(i, 5).data().toString().compare(tr("不重复"))==0)
                off_Alarm(i);
        }
    }
    update();
}

//通知弹窗
void Clock::notice_dialog_show(int close_time, int alarm_num)
{
    model_setup->select();
    QScreen *screen=QGuiApplication::primaryScreen ();
    QRect mm=screen->availableGeometry() ;
    int screen_width = mm.width();
    int screen_height = mm.height();
      Natice_alarm  *dialog1 = new Natice_alarm(close_time,alarm_num);
      dialog1->ui->label_2->setText(model->index(alarm_num, 14).data().toString());
      dialog1->ui->label_3->setText(change_NUM_to_str(model->index(alarm_num, 0).data().toInt())+" : "+change_NUM_to_str(model->index(alarm_num, 1).data().toInt()));
      dialog1->ui->label_4->setText(QString::number(close_time)+tr("秒后自动关闭"));
      if(model_setup->index(0, 3).data().toInt())
      {
          dialog1->showFullScreen();
      }else{
          dialog1->move(screen_width-450,screen_height-300);
      }
      Qt::WindowFlags m_flags = windowFlags();
      dialog1->setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);
      dialog1->show();
}

//重绘窗口，更新闹钟
void Clock::updateAlarmClock()
{
    int rowNum = model->rowCount();

    for(int alarmNum=0; alarmNum<rowNum; alarmNum++)
    {
        aItem[alarmNum] =new QListWidgetItem;
        aItem[alarmNum]->setSizeHint(QSize(376,58));
        aItem[alarmNum]->setTextColor(QColor(255, 0, 0, 255));
        ui->listWidget->addItem(aItem[alarmNum]);
        ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        w1[alarmNum] = new item_new(ui->listWidget);
        ui->listWidget->setItemWidget(aItem[alarmNum],w1[alarmNum]);

        change_time_NUM(model->index(alarmNum, 0).data().toInt(),model->index(alarmNum, 1).data().toInt());//转换int为QString
        w1[alarmNum]->alarmLabel0->setText(alarmHour_str+" : "+alarmMinute_str);

        //闹钟开关
        if(model->index(alarmNum, 3).data().toInt() == 1){
            w1[alarmNum]->alarm_on_off0->setStyleSheet("border-image: url(:/alarm_off.png);background-color: rgb();");
        }else {
            w1[alarmNum]->alarm_on_off0->setStyleSheet("border-image: url(:/alarm_on.png);background-color: rgb();");
        }
        w1[alarmNum]->alarmLabel_w0->setText(model->index(alarmNum, 14).data().toString());
        w1[alarmNum]->alarmLabel_s0->setText(model->index(alarmNum, 5).data().toString());

        connect( w1[alarmNum]->alarm_on_off0, SIGNAL(clicked()), this, SLOT(On_Off_Alarm()) );
    }
}

//修改时间单数 为两位数
void Clock::change_time_NUM(int alarmHour, int alarmMinute)
{
    if(alarmHour < 10){
        QString hours_str = QString::number(alarmHour);
        alarmHour_str = "0"+hours_str;
    }else {
        alarmHour_str = QString::number(alarmHour);
    }

    if(alarmMinute < 10){
        QString minute_str = QString::number(alarmMinute);
        alarmMinute_str = "0"+minute_str;
    }else {
        alarmMinute_str = QString::number(alarmMinute);
    }
}

void Clock::cancelAlarmClock()
{
    dialog->close();
}

void Clock::stopPlayMusic()
{
    player->stop();
}

void Clock::selectMusic()
{
    musicPath = QFileDialog::getOpenFileName(this, "选择铃声",
                                             "G:/歌曲", "*.mp3");
}
void Clock::rePlayMusic()
{
    player->play();
}

//增加item
void Clock::aItem_new()
{
    int rowNum = model->rowCount();
    aItem[rowNum] =new QListWidgetItem;
    aItem[rowNum]->setSizeHint(QSize(376,56));
    aItem[rowNum]->setTextColor(QColor(255, 0, 0, 255));
    ui->listWidget->addItem(aItem[rowNum]);
    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    w1[rowNum] = new item_new(ui->listWidget);
    ui->listWidget->setItemWidget(aItem[rowNum],w1[rowNum]);
}

//新建闹钟按钮回调
void Clock::set_Alarm_Clock()
{
    ui->set_page->raise();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();
    ui->set_alarm_savebtn->show();
    ui->set_alarm_cancelbtn->show();
    timer_set_page->start();
    ui->label_13->setText(tr("新建闹钟"));
    repeat_new_or_edit_flag = 0;

    model_setup->select();//调用默认设置

    repeat_str_model = tr("工作日");
    ui->pushButton_6->setText(repeat_str_model+tr("(默认)"));
    for (int i=0; i<7; i++) {
        repeat_day[i] = model_setup->index(0, i+7).data().toInt();
    }
    if(model_setup->index(0, 4).data().toInt() == 0){
        time_music_str_model = tr("1分钟");
    }else if (model_setup->index(0, 4).data().toInt() == 1) {
        time_music_str_model = tr("2分钟");
    }else if (model_setup->index(0, 4).data().toInt() == 2) {
        time_music_str_model = tr("3分钟");
    }else if (model_setup->index(0, 4).data().toInt() == 3){
        time_music_str_model = tr("4分钟");
    }else if (model_setup->index(0, 4).data().toInt() == 4){
        time_music_str_model = tr("6分钟");
    }
    ui->pushButton_17->setText(time_music_str_model+tr("(默认)"));
    music_str_model = model_setup->index(0, 5).data().toString();
    ui->pushButton_11->setText(music_str_model+tr("(默认)"));
    clock_name = tr("闹钟");
    ui->lineEdit->setText(clock_name);
}

//闹钟新建界面保存回调
void Clock::set_alarm_save()
{
    int rowNum;
    rowNum = model->rowCount();

    qDebug() << rowNum << "闹钟数";
    if(rowNum < 20)
    {
        model->insertRow(rowNum);
        model->setData(model->index(rowNum, 0), timer_alarm_start24->m_currentValue);
        model->setData(model->index(rowNum, 1), timer_alarm_start60->m_currentValue);
        model->setData(model->index(rowNum, 2), music_str_model);
        model->setData(model->index(rowNum, 3), int(0));
        model->setData(model->index(rowNum, 4), int(model->index(rowNum-1, 4).data().toInt()+1));
        model->setData(model->index(rowNum, 5), repeat_str_model);
        model->setData(model->index(rowNum, 13), time_music_str_model);
        model->setData(model->index(rowNum, 14), ui->lineEdit->text());
        qDebug() << repeat_str;

        for (int i=0; i<7; i++) {
            model->setData(model->index(rowNum, i+6), repeat_day[i]);
        }

        model->submitAll();

        for(int i=0; i<rowNum; i++)
        {
            delete aItem[i];
            delete w1[i];
        }
        qDebug() << model->index(rowNum, 0).data().toString()
                 << model->index(rowNum, 1).data().toString()
                 << QFileInfo( model->index(rowNum, 2).data().toString() ).fileName();

        updateAlarmClock();
    }
    else
    {
        QMessageBox::warning(this, "警告", "闹钟数量已达上限！", QMessageBox::Yes);
    }
    ui->stackedWidget_3->raise();
    ui->stackedWidget->raise();//将页面放置最前方
    ui->pushButton_4->raise();
    ui->pushButton_5->raise();
    ui->pushButton_12->raise();
    timer_set_page->stop();

    if(dialog_repeat)
    {
        dialog_repeat->close();
    }
    if(dialog_music)
    {
        dialog_music->close();
    }
    if(time_music)
    {
        time_music->close();
    }
}

//闹钟新建与重编辑界面剩余时间显示
void Clock::verticalscroll_ring_time()
{
    int x_h, x_m ;

    QTime time = QTime::currentTime();
    int timeH = time.hour();
    int timeM = time.minute();

    int hour_time = timer_alarm_start24->m_currentValue;
    int minute_time= timer_alarm_start60->m_currentValue;

    if(hour_time > timeH){
        x_h = hour_time - timeH;
    }else{
        x_h = hour_time + 24 - timeH;
    }

    if(minute_time > timeM){
        x_m = minute_time - timeM;
    }else {
        x_m = minute_time + 60 - timeM;
        x_h --;
    }
    if(x_m == 60)
    {
        x_m = 0;
        x_h++;
    }
    if(x_h ==24)
    {
        x_h = 0;
    }
    ui->label_12->setText(QString::number(x_h)+tr("小时")+QString::number(x_m)+tr("分钟后铃响"));
}

//闹钟新建界面取消回调
void Clock::alarm_Cancel_save()
{
    ui->stackedWidget_3->raise();
    ui->stackedWidget->raise();
    timer_set_page->stop();
    ui->pushButton_4->raise();
    ui->pushButton_5->raise();
    ui->pushButton_12->raise();
}

//双击闹钟打开重编辑页面
void Clock::listdoubleClickslot()
{
    ui->pushButton_8->show();
    ui->pushButton_9->show();
    ui->set_alarm_savebtn->hide();
    ui->set_alarm_cancelbtn->hide();
    timer_alarm_start24->m_currentValue=model->index(ui->listWidget->currentRow(), 0).data().toInt();
    timer_alarm_start60->m_currentValue=model->index(ui->listWidget->currentRow(), 1).data().toInt();
    ui->set_page->raise();
    timer_set_page->start();
    ui->label_13->setText(tr("编辑闹钟"));
    repeat_new_or_edit_flag = 1;

    int num = ui->listWidget->currentRow();

    qDebug() << num  <<model->index(num, 5).data().toString();
    qDebug() << num  <<model->index(num, 2).data().toString();

    ui->pushButton_6->setText(model->index(num, 5).data().toString());
    repeat_str_model = model->index(num, 5).data().toString();
    ui->pushButton_11->setText(model->index(num, 2).data().toString());
    music_str_model = model->index(num, 2).data().toString();
    ui->pushButton_17->setText(model->index(num, 13).data().toString());
    time_music_str_model = model->index(num, 13).data().toString();
    clock_name = model->index(num, 14).data().toString();
    ui->lineEdit->setText(clock_name);

    for (int i=0; i<7; i++) {
        if(model->index(num, 6+i).data().toInt())
        {
            repeat_day[i] = 1;
        }
        else {
            repeat_day[i] = 0;
        }
    }
}


//闹钟重编辑保存回调
void Clock::on_pushButton_9_clicked()
{
    int rowNum = ui->listWidget->currentRow();

    qDebug() << rowNum << "要修改的闹钟号";

    model->setData(model->index(rowNum, 0), timer_alarm_start24->m_currentValue);
    model->setData(model->index(rowNum, 1), timer_alarm_start60->m_currentValue);
    model->setData(model->index(rowNum, 2), music_str_model);
    model->setData(model->index(rowNum, 5), repeat_str_model);
    model->setData(model->index(rowNum, 13), time_music_str_model);
    model->setData(model->index(rowNum, 14), ui->lineEdit->text());

    for (int i=0; i<7; i++) {
        if(repeat_day[i])
        {
            model->setData(model->index(rowNum, i+6), 1);
        }
        else {
            model->setData(model->index(rowNum, i+6), 0);
        }
    }

    // alarmLabel
    model->submitAll();

    int m = model->rowCount();
    for(int i=0; i<m; i++)  //每次updateAlarmClock()之前，删除全部闹钟相关控件
    {
        delete aItem[i];
        delete w1[i];
    }

    qDebug() << model->index(rowNum, 0).data().toString()
             << model->index(rowNum, 1).data().toString()
             << QFileInfo( model->index(rowNum, 2).data().toString() ).fileName();

    updateAlarmClock();

    ui->stackedWidget_3->raise();
    ui->stackedWidget->raise();//将页面放置最前方
    ui->pushButton_4->raise();
    ui->pushButton_5->raise();
    ui->pushButton_12->raise();
    timer_set_page->stop();

    if(dialog_repeat)
    {
        dialog_repeat->close();
    }
    if(dialog_music)
    {
        dialog_music->close();
    }
    if(time_music)
    {
        time_music->close();
    }
}


//单击闹钟显示铃声剩余时间
void Clock::listClickslot()
{
    timer_Surplus->start();

    int x_h, x_m ;
    int num=ui->listWidget->currentRow();

    QTime time = QTime::currentTime();
    int timeH = time.hour();
    int timeM = time.minute();

    int hour_time = model->index(num, 0).data().toInt();
    int minute_time= model->index(num, 1).data().toInt();

    if(hour_time > timeH){
        x_h = hour_time - timeH;
    }else{
        x_h = hour_time + 24 - timeH;
    }

    if(minute_time > timeM){
        x_m = minute_time - timeM;
    }else {
        x_m = minute_time + 60 - timeM;
        x_h --;
    }

    if(x_m == 60)
    {
        x_m = 0;
        x_h++;
    }
    if(x_h ==24)
    {
        x_h = 0;
    }

    if(num < 0){
        ui->label_7->setText(QApplication::translate("Clock", "\347\202\271\345\207\273\351\227\271\351\222\237\346\230\276\347\244\272\345\211\251\344\275\231\346\227\266\351\227\264", nullptr));
    }else{
        ui->label_7->setText(QString::number(x_h)+tr("小时")+QString::number(x_m)+tr("分钟后铃响"));
    }
}

//闹钟重编辑页面删除闹钟回调
void Clock::deleteAlarm()
{
    int num=ui->listWidget->currentRow();
    int rowNum = model->rowCount();
    model->removeRows(num, 1);
    qDebug() << "delete " <<num <<rowNum;

    int ok = QMessageBox::warning(this, tr("删除当前闹钟！"),
                                  tr("您确定删除当前闹钟吗？"),
                                  QMessageBox::Yes, QMessageBox::No);
    if(ok == QMessageBox::No)
    {
        model->revertAll();//如果不删除, 则撤销
        qDebug() << rowNum;
    }
    else
    {
        for(int i=0; i<rowNum; i++)
        {
            delete w1[i];
            delete aItem[i];
        }
        model->submitAll();   //否则提交, 在数据库中删除该行
        updateAlarmClock();
        rowNum = model->rowCount();
        qDebug() << rowNum;

        ui->stackedWidget_3->raise();
        ui->stackedWidget->raise();//将页面放置最前方
        ui->pushButton_4->raise();
        ui->pushButton_5->raise();
        ui->pushButton_12->raise();

    }

    timer_set_page->stop();
}

//闹钟开关
void Clock::On_Off_Alarm()
{
    int i=0 ;
    QPushButton *btn = qobject_cast<QPushButton*>(QObject::sender());
    while (btn != w1[i]->alarm_on_off0) {
        i++;
    }
    if(model->index(i, 3).data().toInt() == 0){
        btn->setStyleSheet("border-image: url(:/alarm_off.png);background-color: rgb();");
        qDebug() << "off";

        model->setData(model->index(i, 3), int(1));
        model->submitAll();
    } else {

        btn->setStyleSheet("border-image: url(:/alarm_off.png);background-color: rgb();");
        qDebug() << "on";

        model->setData(model->index(i, 3), int(0));
        model->submitAll();
    }
    int rowNum = model->rowCount();
    for(int i=0; i<rowNum; i++)
    {
        delete aItem[i];
        delete w1[i];
    }
    updateAlarmClock();
}
void Clock::off_Alarm(int i)
{
    w1[i]->alarm_on_off0->setStyleSheet("border-image: url(:/alarm_off.png);background-color: rgb();");
    qDebug() << "on";

    model->setData(model->index(i, 3), int(1));
    model->submitAll();

    int rowNum = model->rowCount();
    for(int i=0; i<rowNum; i++)
    {
        delete aItem[i];
        delete w1[i];
    }
    updateAlarmClock();
}

//------------------------------------------------------倒计时--------------------------------------------------------------------
//倒计时音乐选择
void Clock::countdown_music_sellect()
{


        QPointF position = this->pos();
        count_music_sellect->move(position.x()+87,position.y()+552);
        count_music_sellect->resize(280,141);
        count_music_sellect->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
        count_music_sellect->setAttribute(Qt::WA_TranslucentBackground);
        count_music_sellect->listWidget->setFixedSize(280,141);
        count_music_sellect->widget[0]->alarmLabel0->setText(tr("玻璃"));
        count_music_sellect->widget[1]->alarmLabel0->setText(tr("犬吠"));
        count_music_sellect->widget[2]->alarmLabel0->setText(tr("声呐"));
        count_music_sellect->widget[3]->alarmLabel0->setText(tr("雨滴"));
        count_music_sellect->show();

        connect(count_music_sellect->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(count_music_listClickslot()));
}

void Clock::count_music_listClickslot()
{
    QString music;
    int num=count_music_sellect->listWidget->currentRow();
    switch (num)
    {
    case 0:
            music = tr("玻璃");
        break;
    case 1:
            music = tr("犬吠");
        break;
    case 2:
            music = tr("声呐");
        break;
    case 3:
            music = tr("雨滴");
        break;
    default:
        break;
    }

    model_setup->setData(model_setup->index(0, 19), music);
    ui->pushButton_20->setText(music);
    count_music_sellect->close();
    model_setup->submitAll();
}

//倒计时执行
void Clock::stat_countdown(){
    QString h; QString m; QString s;
    if(countdown_hour < 10){
        QString hours_str = QString::number(countdown_hour);
        h = "0"+hours_str;
    }else {
        h = QString::number(countdown_hour);
    }

    if(countdown_minute < 10){
        QString minute_str = QString::number(countdown_minute);
        m = "0"+minute_str;
    }else {
        m = QString::number(countdown_minute);
    }

    if(countdown_second < 10){
        QString second_str = QString::number(countdown_second);
        s = "0"+second_str;
    }else {
        s = QString::number(countdown_second);
    }
    ui->label_9->setText(h+":"+m+":"+s);

    if(countdown_hour==0 && countdown_minute==0 && countdown_second==1){
        countdown_timer->stop();
        countdown_notice_dialog_show();
        startbtn_countdown();
    }

    countdown_second--;
    if(countdown_second==-1){
        countdown_minute--;
        countdown_second=59;
    }
    if(countdown_minute==-1){
        countdown_hour--;
        countdown_minute=59;
    }
}

//倒计时通知弹窗
void Clock::countdown_notice_dialog_show()
{
    model_setup->select();
    QScreen *screen=QGuiApplication::primaryScreen ();
    QRect mm=screen->availableGeometry() ;
    int screen_width = mm.width();
    int screen_height = mm.height();
    model_setup->select();
    Natice_alarm *dialog1 = new Natice_alarm(360,-1);
    dialog1->ui->label_4->setText(tr("360秒后自动关闭"));
    dialog1->ui->label_2->hide();
    dialog1->ui->label->setText(tr("倒计时"));
    dialog1->ui->label_3->setText(tr("时间到"));
    if(model_setup->index(0, 3).data().toInt())
    {
        dialog1->showFullScreen();
    }else{
        dialog1->move(screen_width-450,screen_height-300);
    }
    Qt::WindowFlags m_flags = windowFlags();
    dialog1->setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);
    dialog1->show();
}

//倒计时开始-结束
void Clock::startbtn_countdown(){
    if (!countdown_isStarted){
        if(timer_ring99->m_currentValue==0 && timer_ring60->m_currentValue==0 && timer_ring60_2->m_currentValue==0){
            return;
        }
        int ringmax = timer_ring99->m_currentValue*3600 + timer_ring60->m_currentValue*60 + timer_ring60_2->m_currentValue;
        ui->page_5->RoundBar3->time_max = ringmax;
        ui->count_stat->setStyleSheet("QPushButton{background:rgba(44,44,46,1);\
                                        border:1px solid rgba(68,68,71,1);\
                                        border-radius:4px;\
                                        font: 11pt; }\
                                        QPushButton:hover{background:rgba(143, 97, 47, 0.1)}");
        countdown_isStarted=1;
        ui->count_stat->setText(tr("结束"));
        ui->stackedWidget_4->setCurrentIndex(1);
        setcoutdown_number(timer_ring99->m_currentValue, timer_ring60->m_currentValue, timer_ring60_2->m_currentValue);//获取转轮当前值
        countdown_timer->start();
        ui->page_5->timer->start();
    } else {
        ui->page_5->RoundBar3->ring_max = 3600;
        ui->page_5->RoundBar3->setValue(3600);//初始化倒计时进度圈
        ui->count_stat->setStyleSheet("QPushButton{color: rgb(255, 255, 255);\
                                      background-color: rgba(39,207,129,0.9);\
                                       border-radius:4px;\
                                      font: 11pt ;}\
                                      QPushButton:hover{background-color: rgb(27, 143, 89);}");

        countdown_timer->stop();
        ui->page_5->timer->stop();
        countdown_isStarted=0;
        countdown_isStarted_2=0;
        timer_ring99->m_currentValue = 0;
        timer_ring60->m_currentValue = 0;
        timer_ring60_2->m_currentValue = 0;
        ui->count_stat->setText(tr("开始"));
        ui->label_9->setText("00:00:00");
        ui->label_8->setText("00:00:00");
        ui->stackedWidget_4->setCurrentIndex(0);
        ui->count_push->setText(tr("暂停"));
        ui->count_push->setStyleSheet("QPushButton{color: rgb(255, 255, 255);\
                                      background-color: rgba(231,159,78,0.9);\
                                      border-radius:34px;}\
                                      QPushButton:hover{background:rgba(143, 97, 47, 0.6)}");
    }
    return;
}
//设置倒计时初始时间
void Clock::setcoutdown_number(int h1, int m1, int s1){
    countdown_hour=h1; countdown_minute=m1 ; countdown_second=s1;
    QString h; QString m; QString s;

    if(countdown_hour < 10){
        QString hours_str = QString::number(countdown_hour);
        h = "0"+hours_str;
    }else {
        h = QString::number(countdown_hour);
    }

    if(countdown_minute < 10){
        QString minute_str = QString::number(countdown_minute);
        m = "0"+minute_str;
    }else {
        m = QString::number(countdown_minute);
    }

    if(countdown_second < 10){
        QString second_str = QString::number(countdown_second);
        s = "0"+second_str;
    }else {
        s = QString::number(countdown_second);
    }

    ui->label_9->setText(h+":"+m+":"+s);
    ui->label_8->setText(h+":"+m+":"+s);
    //ui->page_5->a =countdown_hour*3600+countdown_minute*60+countdown_second;

    get_countdown_over_time();
}

//倒计时5分钟
void Clock::on_min_5btn_clicked()
{
    timer_ring99->m_currentValue = 0;
    timer_ring60->m_currentValue = 5;
    timer_ring60_2->m_currentValue = 0;
    setcoutdown_number(0, 5, 0);
}
//倒计时10分钟
void Clock::on_min_10btn_clicked()
{
    timer_ring99->m_currentValue = 0;
    timer_ring60->m_currentValue = 10;
    timer_ring60_2->m_currentValue = 0;
    setcoutdown_number(0, 10, 0);
}
//倒计时20分钟
void Clock::on_min_20btn_clicked()
{
    timer_ring99->m_currentValue = 0;
    timer_ring60->m_currentValue = 20;
    timer_ring60_2->m_currentValue = 0;
    setcoutdown_number(0, 20, 0);
}
//倒计时30分钟
void Clock::on_min_30btn_clicked()
{
    timer_ring99->m_currentValue = 0;
    timer_ring60->m_currentValue = 30;
    timer_ring60_2->m_currentValue = 0;
    setcoutdown_number(0, 30, 0);
}
//倒计时60分钟
void Clock::on_min_60btn_clicked()
{
    timer_ring99->m_currentValue = 1;
    timer_ring60->m_currentValue = 0;
    timer_ring60_2->m_currentValue = 0;
    setcoutdown_number(1,0, 0);
}
//获取倒计时结束时间
void Clock::get_countdown_over_time()
{
    int x_h, x_m ;
    QTime time = QTime::currentTime();
    int timeH = time.hour();
    int timeM = time.minute();

    x_h = countdown_hour + timeH;
    x_m = countdown_minute + timeM;

    if(x_m >= 60){
        x_m = x_m - 60;
        x_h ++;
    }
   if(x_h >= 48){
        x_h = x_h - 48;
        ui->label_11->setText(tr("后天")+change_NUM_to_str(x_h)+":"+change_NUM_to_str(x_m));
    }else if(x_h >= 24){
        x_h = x_h - 24;
        ui->label_11->setText(tr("明天")+change_NUM_to_str(x_h)+":"+change_NUM_to_str(x_m));
    }else if(x_h >= 12){
        x_h = x_h - 12;
        ui->label_11->setText(tr("下午")+change_NUM_to_str(x_h)+":"+change_NUM_to_str(x_m));
    }else {
        ui->label_11->setText(tr("上午")+change_NUM_to_str(x_h)+":"+change_NUM_to_str(x_m));
    }
}


//单位变双位
QString Clock::change_NUM_to_str(int alarmHour)
{
    QString str;
    if(alarmHour < 10){
        QString hours_str = QString::number(alarmHour);
        str = "0"+hours_str;
    }else {
        str = QString::number(alarmHour);
    }
    return str;
}
//倒计时-暂停继续
void Clock::on_count_push_clicked()
{
    if (countdown_isStarted_2){
        ui->count_push->setText(tr("暂停"));
        ui->count_push->setStyleSheet("QPushButton{color: rgb(255, 255, 255);\
                                      background-color: rgba(231,159,78,0.9);\
                                      border-radius:34px;}\
                                      QPushButton:hover{background:rgba(143, 97, 47, 0.6)}");
        countdown_timer->start();
        ui->page_5->timer->start();
        countdown_isStarted_2=0;

    } else {
        ui->count_push->setText(tr("继续"));
        ui->count_push->setStyleSheet("QPushButton{\
                                      color: rgb(255, 255, 255);\
                                      background-color: rgba(39,207,129,0.9);\
                                      border-radius:34px;\
                                      }\
                                      QPushButton:hover{background-color: rgb(27, 143, 89);}");
        countdown_timer->stop();
        ui->page_5->timer->stop();
        countdown_isStarted_2=1;
    }
    return;
}
//倒计时初始数字转盘
void Clock::countdown_set_start_time()
{
    DotLineDemo *ring_widget = new DotLineDemo(ui->page_4);
    ring_widget->move(0,0);

    timer_ring99 = new VerticalScroll_99(ring_widget);
    QLabel * h_in_m = new QLabel (ring_widget);
    timer_ring60 = new VerticalScroll_60(ring_widget);
    QLabel * m_in_s = new QLabel (ring_widget);
    timer_ring60_2 = new VerticalScroll_60(ring_widget);

    QLabel * hour_ring = new QLabel (ring_widget);
    QLabel * min_ring = new QLabel (ring_widget);
    QLabel * sec_ring = new QLabel (ring_widget);

    hour_ring->setAlignment(Qt::AlignHCenter);
    min_ring->setAlignment(Qt::AlignHCenter);
    sec_ring->setAlignment(Qt::AlignHCenter);

    hour_ring->resize(50,30);
    hour_ring->setText(tr("时"));
    hour_ring->setStyleSheet("font: 13pt ;color: rgb(148, 148, 148);");
    min_ring->resize(50,30);
    min_ring->setText(tr("分"));
    min_ring->setStyleSheet("font: 13pt ;color: rgb(148, 148, 148);");
    sec_ring->resize(50,30);
    sec_ring->setText(tr("秒"));
    sec_ring->setStyleSheet("font: 13pt ;color: rgb(148, 148, 148);");

    h_in_m->resize(10,40);
    h_in_m->setText(":");
    h_in_m->setStyleSheet("font: 30pt 'Sans Serif';");
    m_in_s->resize(10,40);
    m_in_s->setText(":");
    m_in_s->setStyleSheet("font: 30pt 'Sans Serif';");

    timer_ring99->move(125, 115);
    hour_ring->move(129,110);
    h_in_m->move(185,192);
    timer_ring60->move(200, 115);
    min_ring->move(201,110);
    m_in_s->move(257,192);
    timer_ring60_2->move(272, 115);
    sec_ring->move(273,110);
}
//-----------------------------------------闹钟初始化--------------------------------------------
//闹钟初始化数字转盘
void Clock::alarm_set_start_time()
{
    timer_alarm_start24 = new VerticalScroll_24(ui->set_page);
    QLabel * h_in_m = new QLabel (ui->set_page);
    timer_alarm_start60 = new VerticalScroll_60(ui->set_page);

    QLabel * hour_ring = new QLabel (ui->set_page);
    QLabel * min_ring = new QLabel (ui->set_page);

    hour_ring->setAlignment(Qt::AlignHCenter);
    min_ring->setAlignment(Qt::AlignHCenter);

    h_in_m->resize(10,40);
    h_in_m->setText(":");
    h_in_m->setStyleSheet("font: 30pt 'Sans Serif';");

    hour_ring->resize(50,30);
    hour_ring->setText(tr("时"));
    hour_ring->setStyleSheet("font: 13pt ;color: rgb(148, 148, 148);");
    min_ring->resize(50,30);
    min_ring->setText(tr("分"));
    min_ring->setStyleSheet("font: 13pt ;color: rgb(148, 148, 148);");

    timer_alarm_start24->move(161, 105);
    hour_ring->move(161,100);
    h_in_m->move(217,182);
    timer_alarm_start60->move(233, 105);
    min_ring->move(233,100);
}
//闹钟初始化工作日选择界面绘制回调
void Clock::alarm_repeat()
{
    int num;
    if(repeat_new_or_edit_flag)
        num = ui->listWidget->currentRow();
    else {
        num= model->rowCount();
    }


        QPointF position = this->pos();
        dialog_repeat->move(position.x()+87,position.y()+446);
        dialog_repeat->resize(280,270);
        dialog_repeat->listWidget->setFixedSize(280,270);
        dialog_repeat->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
        dialog_repeat->setAttribute(Qt::WA_TranslucentBackground);
        dialog_repeat->widget[0]->alarmLabel0->setText(tr("不重复"));
        dialog_repeat->widget[1]->alarmLabel0->setText(tr("工作日"));
        dialog_repeat->widget[2]->alarmLabel0->setText(tr("周一"));
        dialog_repeat->widget[3]->alarmLabel0->setText(tr("周二"));
        dialog_repeat->widget[4]->alarmLabel0->setText(tr("周三"));
        dialog_repeat->widget[5]->alarmLabel0->setText(tr("周四"));
        dialog_repeat->widget[6]->alarmLabel0->setText(tr("周五"));
        dialog_repeat->widget[7]->alarmLabel0->setText(tr("周六"));
        dialog_repeat->widget[8]->alarmLabel0->setText(tr("周日"));
        for (int i=0; i<7; i++) {
            if(repeat_day[i])
            {
                dialog_repeat->widget[i+2]->alarmLabel1->setIcon(repeat_on_Pixmap);
            }
            else {
                dialog_repeat->widget[i+2]->alarmLabel1->setIcon(repeat_off_Pixmap);
            }
        }
        dialog_repeat->show();

}
//重复选项单击回调
void Clock::repeat_listClickslot()
{
    int num=dialog_repeat->listWidget->currentRow();
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
        ui->pushButton_6->setText(tr("不重复"));
        repeat_str_model = tr("不重复");
        for (int i=0; i<7; i++) {
            repeat_day[i] = 1;
            qDebug() << repeat_day[i];
            dialog_repeat->widget[i+2]->alarmLabel1->setIcon(repeat_off_Pixmap);
        }

        dialog_repeat->close();
        return;
        break;
    case 1:
        ui->pushButton_6->setText(tr("工作日"));
        repeat_str_model = tr("工作日");
        for (int i=0; i<7; i++) {
            if(model_setup->index(0, i+7).data().toInt())
            {
                repeat_day[i] = 1;
                qDebug() << repeat_day[i];
                dialog_repeat->widget[i+2]->alarmLabel1->setIcon(repeat_on_Pixmap);
            }else{
                repeat_day[i] = 0;
                dialog_repeat->widget[i+2]->alarmLabel1->setIcon(repeat_off_Pixmap);
            }
        }
        dialog_repeat->widget[7]->alarmLabel1->setIcon(repeat_on_Pixmap);
        dialog_repeat->widget[8]->alarmLabel1->setIcon(repeat_on_Pixmap);
        dialog_repeat->close();
        return;
        break;
    case 2:
        if(repeat_day[0] == 0 )
        {
            repeat_day[0] = 1;
            dialog_repeat->widget[2]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }else {
            repeat_day[0] = 0;
            dialog_repeat->widget[2]->alarmLabel1->setIcon(repeat_off_Pixmap);
        }
        break;
    case 3:
        if(repeat_day[1] == 0 )
        {
            repeat_day[1] = 1;
            dialog_repeat->widget[3]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }else {
            repeat_day[1] = 0;
            dialog_repeat->widget[3]->alarmLabel1->setIcon(repeat_off_Pixmap);
        }
        break;
    case 4:
        if(repeat_day[2] == 0 )
        {
            repeat_day[2] = 1;
            dialog_repeat->widget[4]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }else {
            repeat_day[2] = 0;
            dialog_repeat->widget[4]->alarmLabel1->setIcon(repeat_off_Pixmap);
        }
        break;
    case 5:
        if(repeat_day[3] == 0 )
        {
            repeat_day[3] = 1;
            dialog_repeat->widget[5]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }else {
            repeat_day[3] = 0;
            dialog_repeat->widget[5]->alarmLabel1->setIcon(repeat_off_Pixmap);
        }
        break;
    case 6:

        if(repeat_day[4] == 0 )
        {
            repeat_day[4] = 1;
            dialog_repeat->widget[6]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }else {
            repeat_day[4] = 0;
            dialog_repeat->widget[6]->alarmLabel1->setIcon(repeat_off_Pixmap);
        }
        break;
    case 7:

        if(repeat_day[5] == 0 )
        {
            repeat_day[5] = 1;
            dialog_repeat->widget[7]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }else {
            repeat_day[5] = 0;
            dialog_repeat->widget[7]->alarmLabel1->setIcon(repeat_off_Pixmap);
        }
        break;
    case 8:

        if(repeat_day[6] == 0 )
        {
            repeat_day[6] = 1;
            dialog_repeat->widget[8]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }else {
            repeat_day[6] = 0;
            dialog_repeat->widget[8]->alarmLabel1->setIcon(repeat_off_Pixmap);
        }
        break;
    default:
        break;
    }
    for (int i=0; i<7; i++) {
        if(repeat_day[i])
        {
            repeat_str=repeat_str+day[i];
        }
    }
    ui->pushButton_6->setText(repeat_str);
    repeat_str_model = repeat_str;
    repeat_str="";
}

//闹钟初始化音乐选择界面回调
void Clock::select_Music()
{
    int num;
    if(repeat_new_or_edit_flag)
        num = ui->listWidget->currentRow();
    else {
        num= model->rowCount();
    }

        QPointF position = this->pos();
        dialog_music->move(position.x()+87,position.y()+496);
        dialog_music->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
        dialog_music->setAttribute(Qt::WA_TranslucentBackground);
        dialog_music->resize(280,129);
        dialog_music->listWidget->setFixedSize(280,129);
        dialog_music->widget[0]->alarmLabel0->setText(tr("玻璃"));
        dialog_music->widget[1]->alarmLabel0->setText(tr("犬吠"));
        dialog_music->widget[2]->alarmLabel0->setText(tr("声呐"));
        dialog_music->widget[3]->alarmLabel0->setText(tr("雨滴"));

        if(model_setup->index(0, 5).data().toString().compare(tr("玻璃"))==0){
            dialog_music->widget[0]->alarmLabel0->setText(tr("玻璃(默认)"));
        }else if (model_setup->index(0, 5).data().toString().compare(tr("犬吠"))==0) {
            dialog_music->widget[1]->alarmLabel0->setText(tr("犬吠(默认)"));
        }else if (model_setup->index(0, 5).data().toString().compare(tr("声呐"))==0) {
            dialog_music->widget[2]->alarmLabel0->setText(tr("声呐(默认)"));
        }else if (model_setup->index(0, 5).data().toString().compare(tr("雨滴"))==0){
            dialog_music->widget[3]->alarmLabel0->setText(tr("雨滴(默认)"));
        }

        dialog_music->show();

}
//闹钟初始化单击选择音乐
void Clock::music_listClickslot()
{
    int num=dialog_music->listWidget->currentRow();

    switch (num)
    {
    case 0:
        music_str_model=tr("玻璃");
        break;
    case 1:
        music_str_model=tr("犬吠");
        break;
    case 2:
        music_str_model=tr("声呐");
        break;
    case 3:
        music_str_model=tr("雨滴");
        break;
    default:
        break;
    }
    ui->pushButton_11->setText(music_str_model);
    dialog_music->close();
}

void Clock::time_Music()
{
    int num;
    if(repeat_new_or_edit_flag)
        num = ui->listWidget->currentRow();
    else {
        num= model->rowCount();
    }


        QPointF position = this->pos();
        time_music->move(position.x()+87,position.y()+546);
        time_music->listWidget->setFixedSize(280,180);
        time_music->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
        time_music->setAttribute(Qt::WA_TranslucentBackground);
        time_music->resize(280,180);
        time_music->listWidget->move(0,0);
        time_music->widget[0]->alarmLabel0->setText(tr("1分钟"));
        time_music->widget[1]->alarmLabel0->setText(tr("2分钟"));
        time_music->widget[2]->alarmLabel0->setText(tr("3分钟"));
        time_music->widget[3]->alarmLabel0->setText(tr("4分钟"));
        time_music->widget[4]->alarmLabel0->setText(tr("6分钟"));

        if(model_setup->index(0, 4).data().toInt() == 0){
            time_music->widget[0]->alarmLabel0->setText(tr("1分钟(默认)"));
        }else if (model_setup->index(0, 4).data().toInt() == 1) {
            time_music->widget[1]->alarmLabel0->setText(tr("2分钟(默认)"));
        }else if (model_setup->index(0, 4).data().toInt() == 2) {
            time_music->widget[2]->alarmLabel0->setText(tr("3分钟(默认)"));
        }else if (model_setup->index(0, 4).data().toInt() == 3){
            time_music->widget[3]->alarmLabel0->setText(tr("4分钟(默认)"));
        }else if (model_setup->index(0, 4).data().toInt() == 4){
            time_music->widget[4]->alarmLabel0->setText(tr("6分钟(默认)"));
        }
        // set_border_radius(time_music);
        time_music->show();

}

void Clock::time_music_listClickslot()
{
    int num=time_music->listWidget->currentRow();
    switch (num)
    {
    case 0:
        time_music_str_model=tr("1分钟");
        break;
    case 1:
        time_music_str_model=tr("2分钟");
        break;
    case 2:
        time_music_str_model=tr("3分钟");
        break;
    case 3:
        time_music_str_model=tr("4分钟");
        break;
    case 4:
        time_music_str_model=tr("6分钟");
        break;
    default:
        break;
    }
    ui->pushButton_17->setText(time_music_str_model);
    time_music->close();
}



//------------------------------------------全局设置----------------------------------

//默认设置数据库数据初始化
void Clock::model_setup_set()
{
    int setup_rowNum;
    setup_rowNum = model_setup->rowCount();
    if(setup_rowNum < 1)
    {
        model_setup->insertRow(setup_rowNum);
        model_setup->setData(model_setup->index(setup_rowNum, 0), int(0));//自启动
        model_setup->setData(model_setup->index(setup_rowNum, 1), int(0));//静音
        model_setup->setData(model_setup->index(setup_rowNum, 2), int(1));//时间格式
        model_setup->setData(model_setup->index(setup_rowNum, 3), int(0));//弹窗
        model_setup->setData(model_setup->index(setup_rowNum, 4), int(0));//提醒关闭
        model_setup->setData(model_setup->index(setup_rowNum, 5), tr("玻璃"));
        model_setup->setData(model_setup->index(setup_rowNum, 6), int(100));//音量
        model_setup->setData(model_setup->index(setup_rowNum, 7), int(1));
        model_setup->setData(model_setup->index(setup_rowNum, 8), int(1));
        model_setup->setData(model_setup->index(setup_rowNum, 9), int(1));
        model_setup->setData(model_setup->index(setup_rowNum, 10), int(1));
        model_setup->setData(model_setup->index(setup_rowNum, 11), int(1));
        model_setup->setData(model_setup->index(setup_rowNum, 12), int(0));
        model_setup->setData(model_setup->index(setup_rowNum, 13), int(0));
        model_setup->setData(model_setup->index(setup_rowNum, 14), tr("周一周二周三周四周五"));
        model_setup->setData(model_setup->index(setup_rowNum, 15), tr("24小时制(23:59:59)"));
        model_setup->setData(model_setup->index(setup_rowNum, 16), tr("通知栏弹窗"));
        model_setup->setData(model_setup->index(setup_rowNum, 17), tr("一分钟后自动关闭"));
        model_setup->setData(model_setup->index(setup_rowNum, 19), tr("玻璃"));
    }
    model_setup->submitAll();
}


//设置页绘制
void Clock::set_up_page()
{
        QPointF position1 = QCursor::pos();
        if(!setup_page){
        setup_page = new setuppage(position1.x(), position1.y(),  this);
        connect(setup_page->ui->pushButton, SIGNAL(clicked()), this, SLOT(alarm_clcok_Self_starting()) );
        connect(setup_page->ui->pushButton_2, SIGNAL(clicked()), this, SLOT(Mute_starting()) );
        connect(setup_page->ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(set_volume_Value(int)));
        grand = new QWidget(setup_page->ui->widget);
        }
        setup_page->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
        setup_page->setFixedSize(380,450);

        QPointF position = this->pos();

        setup_page->move(position.x()+38,position.y()+27);
        setup_page->setWindowOpacity(0.95);

        //属性记忆重绘制
        if(model_setup->index(0, 0).data().toInt()){
            setup_page->ui->pushButton->setStyleSheet("border-image: url(:/alarm_on.png);");
        }else {
            setup_page->ui->pushButton->setStyleSheet("border-image: url(:/alarm_off.png);");
        }
        if(model_setup->index(0, 1).data().toInt()){
            setup_page->ui->pushButton_2->setStyleSheet("border-image: url(:/alarm_on.png);");
        }else {
            setup_page->ui->pushButton_2->setStyleSheet("border-image: url(:/alarm_off.png);");
        }
        setup_page->ui->horizontalSlider->setValue(model_setup->index(0, 6).data().toInt());

        if(model_setup->index(0, 1).data().toInt()){
            grand->resize(197,24);
            grand->move(128,406);
            grand->setStyleSheet("QWidget{background-color: rgba(14, 19, 22, 0);}");
            grand->show();
        }else{
            grand->hide();
        }
        setup_page->show();
}

//开机自启动开关;
void Clock::alarm_clcok_Self_starting()
{
    if(model_setup->index(0, 0).data().toInt()){
        setup_page->ui->pushButton->setStyleSheet("border-image: url(:/alarm_off.png);");
        model_setup->setData(model_setup->index(0, 0), 0);
    }else {
        setup_page->ui->pushButton->setStyleSheet("border-image: url(:/alarm_on.png);");
        model_setup->setData(model_setup->index(0, 0), 1);
    }

    model_setup->submitAll();
}

//静音开关回调  静音不可调节音量
void Clock::Mute_starting()
{
    if(model_setup->index(0, 1).data().toInt()){
        setup_page->ui->pushButton_2->setStyleSheet("border-image: url(:/alarm_off.png);");
        model_setup->setData(model_setup->index(0, 1), 0);
        grand->hide();
        model_setup->setData(model_setup->index(0, 6),model_setup->index(0, 18).data().toInt());//滑动条记忆回复
        setup_page->ui->horizontalSlider->setValue(model_setup->index(0, 6).data().toInt());
    }else {
        setup_page->ui->pushButton_2->setStyleSheet("border-image: url(:/alarm_on.png);");
        model_setup->setData(model_setup->index(0, 1), 1);

        model_setup->setData(model_setup->index(0, 18),model_setup->index(0, 6).data().toInt());//记忆滑动条
        model_setup->setData(model_setup->index(0, 6),0 );
        setup_page->ui->horizontalSlider->setValue(0);

        grand->move(128,406);
        grand->setStyleSheet("QWidget{background-color: rgba(14, 19, 22, 0);}");
        grand->show();
    }
    model_setup->submitAll();
}

//设置音量回调
void Clock::set_volume_Value(int value)
{
    qDebug()<< value ;
    model_setup->setData(model_setup->index(0, 6),value );
    model_setup->submitAll();
}
