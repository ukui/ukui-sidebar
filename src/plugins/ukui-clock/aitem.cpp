#include "aitem.h"
#include "clock.h"

aItem::aItem()
{
    aItem->setFixedSize(376, 56);
    alarmLabel_w0 = new QLabel();//闹钟用途
    alarmLabel_w0->move(22, 9);
    alarmLabel_w0->setFixedSize(100, 17);
    alarmLabel_w0->setStyleSheet("font: 11pt 'Sans Serif';");
    // alarmLabel_w[alarmNum]->setText(model->index(alarmNum, 5).data().toString());
    alarmLabel_w0->setText("起床铃");
    alarmLabel_w0->setVisible(true);

    alarmLabel_s0 = new QLabel( );//闹钟重复
    alarmLabel_s0->move(24, 34);
    alarmLabel_s0->setFixedSize(100, 17);
    alarmLabel_s0->setStyleSheet("font: 9pt 'Sans Serif';color: rgb(148, 148, 148);");
    // alarmLabel_w[alarmNum]->setText(model->index(alarmNum, 6).data().toString());
    alarmLabel_s0->setText("工作日");
    alarmLabel_s0->setVisible(true);


    alarm_line0 = new QFrame();
    alarm_line0->move(13, 52);
    alarm_line0->setFixedSize(350, 1);
    //alarm_line[alarmNum]->setStyleSheet("color: rgb(255, 255, 255);");
    alarm_line0->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);background-color: rgb(102, 102, 102);"));


    alarmLabel0 = new QLabel();//闹钟，音乐，
    alarmLabel0->move(213,15);
    alarmLabel0->setFixedSize(78, 20);
    alarmLabel0->setStyleSheet("font: 17pt 'Sans Serif';");
    alarmLabel0->setText("00:00");
    alarmLabel0->setVisible(true);
    alarmLabel0->show();

    alarm_on_off0 = new QPushButton();//闹钟开关
    alarm_on_off0->move(305,14);
    alarm_on_off0->setFixedSize(50, 24);
    alarm_on_off0->setFlat(true);
    alarm_on_off0->setVisible(true);
   // if(model->index(0, 3).data().toInt() == 1){
    //    alarm_on_off0->setStyleSheet("border-image: url(:/alarm_off.png);");
   // }else {
        alarm_on_off0->setStyleSheet("border-image: url(:/alarm_on.png);");
   // }
   // connect( alarm_on_off0, SIGNAL(clicked()), this, SLOT(on_off_Alarm()) );

    //w1->setStyleSheet("background-color: rgb(39, 207, 129);");
}
