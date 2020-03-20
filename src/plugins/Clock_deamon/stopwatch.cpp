#include "stopwatch.h"
#include "ui_stopwatch.h"
#include <unistd.h>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include "countdown.h"
#include <QMessageBox>

stopwatch::stopwatch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stopwatch)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);   /* 开启窗口无边框 */
    //   setAttribute(Qt::WA_TranslucentBackground);/* 开启窗口透明层 */

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

    ui->label_4->setText("00:00:00");
    isStarted = 0;
    hour=0;
    minute=0;
    second=0;
    pushflag=0 ;

}

stopwatch::~stopwatch()
{
    delete ui;
}

//倒计时执行
void stopwatch::Count_down()
{

    QString h;QString m;QString s;

    if(hour < 10){
        QString hours_str = QString::number(hour);
        h = "0"+hours_str;
    }else {
        h = QString::number(hour);
    }

    if(minute < 10){
        QString minute_str = QString::number(minute);
        m = "0"+minute_str;
    }else {
        m = QString::number(minute);
    }

    if(second < 10){
        QString second_str = QString::number(second);
        s = "0"+second_str;
    }else {
        s = QString::number(second);
    }

    ui->label_4->setText(h+":"+m+":"+s);

    second++;
    if(second==100){
        minute++; second=0;}
    if(minute==60){
        hour++; minute=0;}

}

void stopwatch::on_pushButton_Start_clicked()
{
    if (!isStarted){
        ui->pushButton_Start->setStyleSheet("border-image: url(:/push_1.png);");

        timer->start();
        isStarted=1;
    } else {
        timer->stop();
        isStarted=0;
        ui->pushButton_Start->setStyleSheet("border-image: url(:/start_1.png);");
    }
    return;
}

//计次
void stopwatch::on_pushButton_ring_clicked()
{
    if (isStarted){
        ui->textEdit->append((QString::number(hour,10)+":"+QString::number(minute,10)+":"+QString::number(second,10)));
    }
}

//复位
void stopwatch::on_pushButton_timeselect_clicked()
{
    if(nullptr != timer){
        timer->stop();
        ui->label_4->setText("00:00:00");
        isStarted=0;
        ui->textEdit->setText("");
        ui->pushButton_Start->setStyleSheet("border-image: url(:/start_1.png);");
    }
}

//窗口最大话
void stopwatch::on_pushButton_5_clicked()
{
    this->close();
}

//窗口最小化
void stopwatch::on_pushButton_4_clicked()
{
    this->showMinimized();
}

//倒计时切换    background-color: rgb(14, 19, 22);
void stopwatch::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton->setStyleSheet("background-color: rgb(0, 107, 0);");
    ui->label->setStyleSheet("color: rgb(0, 107, 0);");
    ui->pushButton_2->setStyleSheet("background-color: rgb(14, 19, 22);");
    ui->label_2->setStyleSheet("color: rgb(255, 255, 255);");
    ui->pushButton_3->setStyleSheet("background-color: rgb(14, 19, 22);");
    ui->label_3->setStyleSheet("color: rgb(255, 255, 255);");

    //countdown= new  countdown;
}

//闹钟窗口切换
void stopwatch::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->pushButton_2->setStyleSheet("background-color: rgb(0, 107, 0);");
    ui->label_2->setStyleSheet("color: rgb(0, 107, 0);");
    ui->pushButton->setStyleSheet("background-color: rgb(14, 19, 22);");
    ui->label->setStyleSheet("color: rgb(255, 255, 255);");
    ui->pushButton_3->setStyleSheet("background-color: rgb(14, 19, 22);");
    ui->label_3->setStyleSheet("color: rgb(255, 255, 255);");
}

//秒表窗口切换
void stopwatch::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->pushButton_3->setStyleSheet("background-color: rgb(0, 107, 0);");
    ui->label_3->setStyleSheet("color: rgb(0, 107, 0);");
    ui->pushButton_2->setStyleSheet("background-color: rgb(14, 19, 22);");
    ui->label_2->setStyleSheet("color: rgb(255, 255, 255);");
    ui->pushButton->setStyleSheet("background-color: rgb(14, 19, 22);");
    ui->label->setStyleSheet("color: rgb(255, 255, 255);");
}
