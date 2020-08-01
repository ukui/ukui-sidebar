#include "widget.h"
#include "ui_widget.h"
#include <unistd.h>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QMessageBox>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
   // setWindowFlags(Qt::FramelessWindowHint);   /* 开启窗口无边框 */
   // setAttribute(Qt::WA_TranslucentBackground);/* 开启窗口透明层 */

    numb=new QLCDNumber(this);
    numb2=new QLCDNumber(this);
    numb3=new QLCDNumber(this);

    numb->setAutoFillBackground(true);//设置lcd背景
    numb2->setAutoFillBackground(true);
    numb3->setAutoFillBackground(true);
    // QPalette pal=numb->palette();
    // pal.setBrush(numb->backgroundRole(),QBrush(QColor(0,0,0)));//lcd背景颜色
    //numb->setPalette(pal);
    numb->resize(10,5);
    numb->setGeometry(12,10,60,30);
    numb2->setGeometry(72,10,60,30);
    numb3->setGeometry(132,10,60,30);
    numb->setSegmentStyle(QLCDNumber::Outline);
    numb->setDecMode();
    numb->setSmallDecimalPoint(1);

}


void Widget::settime_number(int h, int m, int s){
    hour=h; minute=m ; second=s;
}

void Widget::timestart(){
    //定时器---------------------------------
    //新建一个QTimer对象
    timer = new QTimer();
    //设置定时器每个多少毫秒发送一个timeout()信号
    timer->setInterval(1000);
    //启动定时器
    timer->start();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(numb);
    layout->addWidget(numb2);
    layout->addWidget(numb3);

    //信号和槽
    connect(timer, SIGNAL(timeout()), this, SLOT(Count_down()));
    return ;
}

Widget::~Widget()
{
    delete ui;
}

//倒计时执行
void Widget::Count_down()
{
    /*
    //获取系统当前时间
    QTime time = QTime::currentTime();
    //设置晶体管控件QLCDNumber上显示的内容
    numb->display(time.toString("hh"));
    numb2->display(time.toString("mm"));
    numb3->display(time.toString("ss"));
*/
    numb->display(hour);
    numb2->display(minute);
    numb3->display(second);
    if(hour==0 && minute==0 && second==0){


        player->play();
        QMessageBox::warning(this, "Warning", "该休息了");
        player->stop();
        timer->stop();
      //  exit(0);
    }

    second--;
    if(second==-1){
        minute--; second=59;}
    if(minute==-1){
        hour--; minute=59;}

}

void Widget::on_pushButton_Start_clicked()
{
    settime_number(0,0,6);
    timestart();
}

void Widget::on_pushButton_pause_clicked()
{
    if(nullptr != timer && pushflag ==0){
        timer->stop();
        pushflag = 1;
        ui->pushButton_pause->setText("继续");
    }else{
        timer->start();
        pushflag = 0;
        ui->pushButton_pause->setText("暂停");
    }

}

void Widget::on_pushButton_ring_clicked()
{
     player->setVolume(60);
     player->setMedia(QUrl::fromLocalFile("/home/hyd/桌面/sax.mp3"));

  // ring="/home/hyd/桌面/sax.mp3";


}

//void Widget::on_pushButton_timeselect_2_clicked()
//{
//    //settime_number(hour, minute , second);
//}
