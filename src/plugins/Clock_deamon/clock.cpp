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
#include <QDebug>
#include <QTimer>
#include <QTime>
#include "connection.h"
#include <QMessageBox>
#include "item_new.h"
#include "set_clock.h"
#include "stopwatch_item.h"

const double PI=3.141592;

Clock::Clock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Clock)
{
    ui->setupUi(this);
    //this->setFixedSize(400, 660);
    createConnection();
    this->setWindowTitle(tr("闹钟"));
    setWindowFlags(Qt::FramelessWindowHint);   /* 开启窗口无边框 */
    //setAttribute(Qt::WA_TranslucentBackground);/* 开启窗口透明层 */

    ui->stackedWidget_2->setAttribute(Qt::WA_TranslucentBackground);

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
    pixmap11 = QPixmap(":/kylin-alarm-clock.svg");

    this->setWindowIcon(pixmap11);


    bgPixmap = QPixmap(":/background.png").scaled(size());
    clockPixmap = QPixmap(":/clock.png");
    delBtnPixmap = QPixmap(":/deleteBtn.png");
    on_pixmap = QPixmap(":/alarm_on.png");
    off_pixmap = QPixmap(":/alarm_off.png");

    ui->label->move(53,43);
    ui->label_2->move(187,43);
    ui->label_3->move(322,43);
    ui->label->setFixedSize(80,30);
    ui->label_2->setFixedSize(80,30);
    ui->label_3->setFixedSize(80,30);
    ui->label_3->setAlignment(Qt::AlignHCenter);
    ui->label_2->setAlignment(Qt::AlignHCenter);
    ui->label->setAlignment(Qt::AlignHCenter);
    ui->label_6->setStyleSheet("font: 36pt;");
    ui->label_4->setStyleSheet("font: 36pt;");
    ui->label_8->setStyleSheet("font: 36pt;");
    ui->label_9->setStyleSheet("font: 36pt;");


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
    //---------------倒计时-------------------------------------------------------------------------


    //初始化定时器
    countdown_timer = new QTimer();
    //信号和槽
    connect(ui->count_stat, SIGNAL(clicked()), this, SLOT(startbtn_countdown()) );
    connect(countdown_timer, SIGNAL(timeout()), this, SLOT(stat_countdown()));
    //设置定时器每个多少毫秒发送一个timeout()信号
    countdown_timer->setInterval(1000);
    ui->count_push->setStyleSheet("border-image: url(:/push_1.png);");
    countdown_hour = 0;
    countdown_minute = 0;
    countdown_second = 9;
    countdown_pushflag = 0;
    countdown_isStarted = 0;

    //------------秒表-----------------------------------------------------------------------------------
    //  ui->pushButton_Start->setIcon(pixmap8);
    ui->pushButton_Start->setFlat(true);
    ui->pushButton_Start->setVisible(true);
    ui->pushButton_Start->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_Start->setStyleSheet("border-image: url(:/start_1.png);");

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

    //----------------------闹钟---------------------------------
    QTimer *timer_clock = new QTimer(this);
    connect(timer_clock, SIGNAL(timeout()), this, SLOT(timerUpdate()) );//动态获取时间
    QTime time = QTime::currentTime();
    ui->label_6->setText(time.toString("hh")+":"+time.toString("mm")+":"+time.toString("ss"));
    timer_clock->start(1000);

    //单击时间提示计时器
    timer_Surplus = new QTimer();
    connect(timer_Surplus, SIGNAL(timeout()), this, SLOT(listClickslot()));
    timer_Surplus->setInterval(1000);

    connect( ui->addAlarmBtn, SIGNAL(clicked()), this, SLOT(setAlarmClock()) );//添加闹钟

    player_alarm = new QMediaPlayer(this);
    mediaList = new QMediaPlaylist(this);

    model = new QSqlTableModel(this);
    model->setTable("clock");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select(); //选取整个表的所有行

    connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(listdoubleClickslot()));
    connect(ui->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(listClickslot()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(deleteAlarm()) );
    updateAlarmClock();

}

Clock::~Clock()
{
    delete ui;
}


QPointF Clock::rotateAngle(int angle, int len)
{
    int x, y;

    x = 150+len*sin(angle*PI/180);
    y = 150-len*cos(angle*PI/180);

    return QPointF(x, y);
}

//绘制时钟界面
void Clock::paintEvent1(QPaintEvent *)
{
    QTime time = QTime::currentTime();
    int timeH = time.hour();
    int timeM = time.minute();
    int timeS = time.second();

    QDateTime dateTime = QDateTime::currentDateTime();
    // cTimeLabe->setText(dateTime.toString("yyyy-MM-dd hh:mm:ss ddd"));

    QPainter painter(ui->page_4);
    QPen pen;

    //painter.drawPixmap(this->rect(), bgPixmap);
    //绘制钟面
    pen.setWidth(1);
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    for(int i=0; i<60; i++)
    {
        painter.drawLine(rotateAngle(6*i, 100), rotateAngle(6*i, 95));
    }
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawEllipse(QPoint(150, 150), 100, 100);
    pen.setWidth(3);
    painter.setPen(pen);
    for(int i=0; i<12; i++)
    {
        painter.drawLine(rotateAngle(30*i, 100), rotateAngle(30*i, 90));
    }

    //绘制指针
    pen.setWidth(2);
    pen.setColor(Qt::black);//pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawLine(QPointF(150, 150), rotateAngle(6*timeS, 80));
    pen.setWidth(6);
    pen.setColor(Qt::black);//pen.setColor(Qt::blue);
    painter.setPen(pen);
    painter.drawLine(QPointF(150, 150), rotateAngle(6*timeM, 60));
    pen.setWidth(8);
    pen.setColor(Qt::black);//pen.setColor(Qt::green);
    painter.setPen(pen);
    painter.drawLine(QPointF(150, 150), rotateAngle(0.5*(timeH*60+timeM), 40));
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
        ui->pushButton_Start->setStyleSheet("border-image: url(:/push_1.png);");
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
        ui->pushButton_Start->setStyleSheet("border-image: url(:/continu.png);");
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
    ui->listWidget_2->addItem(stopwatch_aItem[stopwatch_item_flag]);
    ui->listWidget_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    stopwatch_w[stopwatch_item_flag] = new stopwatch_item(ui->listWidget_2);

    stopwatch_w[stopwatch_item_flag]->stopwatch1->setText(tr("计次")+QString::number(stopwatch_item_flag));
    stopwatch_w[stopwatch_item_flag]->stopwatch2->setText(stopwatch_jg_h+":"+stopwatch_jg_m+"."+stopwatch_jg_s);
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
        timer->stop();
        timer_2->stop();
        ui->label_4->setText("00:00.00");
        ui->label_5->setText("00:00.00");
        isStarted = 0;
        stopwatch_isStarted = 0;
        ui->pushButton_Start->setStyleSheet("border-image: url(:/start_1.png);");

        for (int i=0; i < stopwatch_item_flag; i++) {
            delete stopwatch_w[i];
            delete stopwatch_aItem[i];
        }
        stopwatch_item_flag = 0;
        hour = 0; minute = 0; second = 0;
        stopwatch_hour = 0; stopwatch_minute = 0; stopwatch_second = 0;
    }
}

//窗口关闭
void Clock::on_pushButton_5_clicked()
{
    this->close();
}

//窗口最小化
void Clock::on_pushButton_4_clicked()
{
    this->showMinimized();
}

//倒计时切换
void Clock::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton->setStyleSheet("background-color: rgb(39, 207, 129);");
    ui->label->setStyleSheet("color: rgb(39, 207, 129);");
    ui->pushButton_2->setStyleSheet("background-color: rgb(14, 19, 22);");
    ui->label_2->setStyleSheet("color: rgb(255, 255, 255);");
    ui->pushButton_3->setStyleSheet("background-color: rgb(14, 19, 22);");
    ui->label_3->setStyleSheet("color: rgb(255, 255, 255);");

    ui->pushButton->setFlat(0);
    ui->pushButton_2->setFlat(1);
    ui->pushButton_3->setFlat(1);
}

//闹钟窗口切换
void Clock::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->pushButton_2->setStyleSheet("background-color: rgb(39, 207, 129);");
    ui->label_2->setStyleSheet("color: rgb(39, 207, 129);");
    ui->pushButton->setStyleSheet("background-color: rgb(14, 19, 22);");
    ui->label->setStyleSheet("color: rgb(255, 255, 255);");
    ui->pushButton_3->setStyleSheet("background-color: rgb(14, 19, 22);");
    ui->label_3->setStyleSheet("color: rgb(255, 255, 255);");

    ui->pushButton->setFlat(1);
    ui->pushButton_2->setFlat(0);
    ui->pushButton_3->setFlat(1);
}

//秒表窗口切换
void Clock::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->pushButton_3->setStyleSheet("background-color: rgb(39, 207, 129);");
    ui->label_3->setStyleSheet("color: rgb(39, 207, 129);");
    ui->pushButton_2->setStyleSheet("background-color: rgb(14, 19, 22);");
    ui->label_2->setStyleSheet("color: rgb(255, 255, 255);");
    ui->pushButton->setStyleSheet("background-color: rgb(14, 19, 22);");
    ui->label->setStyleSheet("color: rgb(255, 255, 255);");

    ui->pushButton->setFlat(1);
    ui->pushButton_2->setFlat(1);
    ui->pushButton_3->setFlat(0);
}


//------------------------------------------------------------闹钟----------------------------------

//闹钟上方电子表
void Clock::text_timerUpdate()
{
    QTime time = QTime::currentTime();
    ui->label_6->setText(time.toString("hh")+":"+time.toString("mm")+":"+time.toString("ss"));
}


//动态监控闹钟与本地时间
void Clock::timerUpdate()
{
    //qDebug() << "timerupdate" << n++;

    QTime time = QTime::currentTime();
    int timeH = time.hour();
    int timeM = time.minute();
    int timeS = time.second();

    ui->label_6->setText(time.toString("hh")+":"+time.toString("mm")+":"+time.toString("ss"));

    int rowNum = model->rowCount();
    for(int i=0; i<rowNum; i++)
    {

        if( model->index(i, 3).data().toInt() == 1){
            continue;
        }
        if(timeH == model->index(i, 0).data().toInt()
                && timeM == model->index(i, 1).data().toInt()
                && timeS == 0)
        {
            QMediaPlayer  *music = new QMediaPlayer(this);//初始化音乐
            QMediaPlaylist *playlist = new QMediaPlaylist(this);//初始化播放列表
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/sounds/gnome/default/alerts/glass.ogg"));
            playlist->setPlaybackMode(QMediaPlaylist::Loop);//设置播放模式(顺序播放，单曲循环，随机播放等)
            music->setPlaylist(playlist);  //设置播放列表
            music->play();
            QMessageBox::warning(this, tr("提示"), tr("时间到！"), QMessageBox::Yes);
            music->stop();
        }
    }
    update();
}

//闹钟设置窗口
void Clock::setAlarmClock()
{

    dialog = new QDialog(this);
    hourBox = new QSpinBox(dialog);
    minuteBox = new QSpinBox(dialog);

    QLabel *label1 = new QLabel(dialog);

    dialog->setStyleSheet("background-color: rgb(122,122,122);");
    hourBox->setStyleSheet("background-color: rgb(250, 250, 250); color: rgb(0, 0, 0);");
    minuteBox->setStyleSheet("background-color: rgb(250, 250, 250);color: rgb(0, 0, 0);");

    label1->setText(tr("闹铃时间："));
    label1->setFont(alarmFont);
    label1->move(20, 30);

    //设置时间框
    hourBox->setPrefix("H: ");
    hourBox->setRange(0, 23);
    hourBox->setFixedSize(120, 40);
    hourBox->move(QPoint(20, 80));
    hourBox->setFont(alarmFont);

    minuteBox->setPrefix("M: ");
    minuteBox->setRange(0, 59);
    minuteBox->setFixedSize(120, 40);
    minuteBox->move(QPoint(150, 80));
    minuteBox->setFont(alarmFont);

    QPushButton *sureBtn = new QPushButton(tr("确定"), dialog);
    QPushButton *cancelBtn = new QPushButton(tr("取消"), dialog);

    sureBtn->move(50, 180);
    sureBtn->resize(80, 30);
    sureBtn->setFont(alarmFont);
    cancelBtn->move(170, 180);
    cancelBtn->resize(80, 30);
    cancelBtn->setFont(alarmFont);

    connect( sureBtn, SIGNAL(clicked()), this, SLOT(sureAlarmClock()) );
    connect( cancelBtn, SIGNAL(clicked()), this, SLOT(cancelAlarmClock()) );

    dialog->setWindowTitle(tr("添加闹钟"));
    // dialog->setWindowFlags(Qt::FramelessWindowHint);
    //设置固定窗口大小
    dialog->setFixedSize(300, 240);
    //模态对话框
    dialog->exec();
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
//重绘窗口，更新闹钟
void Clock::updateAlarmClock()
{
    int rowNum = model->rowCount();

    for(int alarmNum=0; alarmNum<rowNum; alarmNum++)
    {
        aItem[alarmNum] =new QListWidgetItem;
        aItem[alarmNum]->setSizeHint(QSize(376,56));
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
        connect( w1[alarmNum]->alarm_on_off0, SIGNAL(clicked()), this, SLOT(on_off_Alarm()) );
    }
}

//增加或重新编辑闹钟
void Clock::sureAlarmClock()
{
    int rowNum;
    alarmHour = hourBox->value();
    alarmMinute = minuteBox->value();
    /*

    if(add_change_flag == 1)// 如果add_change_flag == 1,编辑闹钟号
    {
        add_change_flag = 0;//进入编辑分支后，重置flag
        rowNum = change_alarm_line;

        qDebug() << rowNum << "闹钟数";

        model->setData(model->index(rowNum, 0), alarmHour);
        model->setData(model->index(rowNum, 1), alarmMinute);
        model->setData(model->index(rowNum, 2), musicPath);
        // alarmLabel
        model->submitAll();
        model->setTable("clock");
        model->select();

        int m = model->rowCount();
        for(int i=0; i<m; i++)  //每次updateAlarmClock()之前，删除全部闹钟相关控件
        {
            delete alarmLabel[i];
            delete deleteAlarmBtn[i];
            delete alarm_on_off[i];
            delete alarm_changed[i];
        }

        qDebug() << model->index(rowNum, 0).data().toString()
                 << model->index(rowNum, 1).data().toString()
                 << QFileInfo( model->index(rowNum, 2).data().toString() ).fileName();

        updateAlarmClock();

        dialog->close();
    }
    else {*/
    rowNum = model->rowCount();
    if(rowNum < 20)
    {
        model->insertRow(rowNum);
        model->setData(model->index(rowNum, 0), alarmHour);
        model->setData(model->index(rowNum, 1), alarmMinute);
        model->setData(model->index(rowNum, 2), musicPath);
        model->setData(model->index(rowNum, 3), int(0));
        model->setData(model->index(rowNum, 4), int(medel_flag++));

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
        QMessageBox::warning(this, tr("警告"), tr("闹钟数量已达上限！"), QMessageBox::Yes);
    }
    dialog->close();
    // }
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
    musicPath = QFileDialog::getOpenFileName(this, tr("选择铃声"),
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
    //qDebug() <<rowNum<<"-------------";
    aItem[rowNum] =new QListWidgetItem;
    aItem[rowNum]->setSizeHint(QSize(376,56));
    aItem[rowNum]->setTextColor(QColor(255, 0, 0, 255));
    ui->listWidget->addItem(aItem[rowNum]);
    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    w1[rowNum] = new item_new(ui->listWidget);
    ui->listWidget->setItemWidget(aItem[rowNum],w1[rowNum]);

}

void Clock::listdoubleClickslot()
{
    ui->stackedWidget_2->raise();

}

//单击闹钟显示铃声剩余时间
void Clock::listClickslot()
{

    timer_Surplus->start();

    int x_h, x_m ;
    int num=ui->listWidget->currentRow();
    // qDebug() <<num;

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
void Clock::deleteAlarm()
{
    int num=ui->listWidget->currentRow();
    int rowNum = model->rowCount();
    //QObject::sender()返回发送信号的对象的指针
    model->removeRows(num, 1);
    qDebug() << "delete " <<num;

    int ok = QMessageBox::warning(this, tr("删除当前闹钟！"),
                                  tr("您确定删除当前闹钟吗？"),
                                  QMessageBox::Yes, QMessageBox::No);
    if(ok == QMessageBox::No)
    {
        model->revertAll();   //如果不删除, 则撤销

        qDebug() << rowNum;
    }
    else
    {
        for(int i=0; i<rowNum; i++)
        {
            delete aItem[i];
            delete w1[i];
        }

        model->submitAll();   //否则提交, 在数据库中删除该行

        updateAlarmClock();

        rowNum = model->rowCount();

        qDebug() << rowNum;

        on_pushButton_7_clicked();
    }

}

//闹钟开关
void Clock::on_off_Alarm()
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

//void Clock::alarm_changed_clicked()

void Clock::on_pushButton_7_clicked()
{
    ui->stackedWidget_3->raise();
    this->raise();
    ui->stackedWidget->raise();//将页面放置最前方
}
//------------------------------------------------------倒计时----------------------------

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

    if(countdown_hour==0 && countdown_minute==0 && countdown_second==0){
        QMediaPlayer  *music = new QMediaPlayer(this);//初始化音乐
        QMediaPlaylist *playlist = new QMediaPlaylist(this);//初始化播放列表
        playlist->addMedia(QUrl::fromLocalFile("/usr/share/sounds/gnome/default/alerts/glass.ogg"));
        playlist->setPlaybackMode(QMediaPlaylist::Loop);//设置播放模式(顺序播放，单曲循环，随机播放等)
        music->setPlaylist(playlist);  //设置播放列表
        music->play();
        QMessageBox::warning(this, tr("时间到"), tr("该休息了"));
        music->stop();
        countdown_timer->stop();
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
//倒计时开始-结束
void Clock::startbtn_countdown(){
    if (!countdown_isStarted){
        if(countdown_hour<0){
            countdown_hour = 0 ; countdown_second = 0; countdown_second = 10;
        }
        ui->count_stat->setStyleSheet("width:100px;\
                                      height:32px;\
                                      background:rgba(44,44,46,1);\
                                      border:1px solid rgba(68,68,71,1);\
                                      border-radius:4px;");

        countdown_timer->start();
        countdown_isStarted=1;
        ui->count_stat->setText(tr("结束"));
        ui->stackedWidget_4->setCurrentIndex(1);
    } else {
        ui->count_stat->setStyleSheet("width:100px;\
                                      height:32px;\
                                      color: rgb(255, 255, 255);\
                                      background-color:rgb(37, 200, 124);\
                                      font: 11pt 'Sans Serif';");

        countdown_timer->stop();
        countdown_isStarted = 0;
        countdown_isStarted_2 = 0;
        ui->count_stat->setText(tr("开始"));
        ui->label_9->setText("00:00:00");
        ui->label_8->setText("00:00:00");
        ui->stackedWidget_4->setCurrentIndex(0);
        countdown_hour = 0 ; countdown_second = 0; countdown_second = 0;
        ui->count_push->setStyleSheet("border-image: url(:/push_1.png);");
    }
    return;
}

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

    get_countdown_over_time();
}

//倒计时5分钟
void Clock::on_min_5btn_clicked()
{
    setcoutdown_number(0, 5, 0);
}
//倒计时10分钟
void Clock::on_min_10btn_clicked()
{
    setcoutdown_number(0, 10, 0);
}
//倒计时20分钟
void Clock::on_min_20btn_clicked()
{
    setcoutdown_number(0, 20, 0);
}
//倒计时30分钟
void Clock::on_min_30btn_clicked()
{
    setcoutdown_number(0, 30, 0);
}
//倒计时60分钟
void Clock::on_min_60btn_clicked()
{
    setcoutdown_number(0,60, 0);
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
    if(x_h >= 24){
        x_h = x_h - 24;
        ui->label_11->setText(tr("明日")+QString::number(x_h)+":"+QString::number(x_m));
    }else if(x_h >= 12){
        x_h = x_h - 12;
        ui->label_11->setText(tr("下午")+QString::number(x_h)+":"+QString::number(x_m));
    }else {
        ui->label_11->setText(tr("上午")+QString::number(x_h)+":"+QString::number(x_m));
    }
}
//倒计时-暂停开始
void Clock::on_count_push_clicked()
{

    if (countdown_isStarted_2){
        ui->count_push->setStyleSheet("border-image: url(:/push_1.png);");
        countdown_timer->start();
        countdown_isStarted_2=0;

    } else {
        ui->count_push->setStyleSheet("border-image: url(:/continu.png);");
        countdown_timer->stop();
        countdown_isStarted_2=1;
    }
    return;
}
