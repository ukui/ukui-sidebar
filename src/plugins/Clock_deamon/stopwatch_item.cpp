#include "stopwatch_item.h"
#include<QApplication>

stopwatch_item::stopwatch_item(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    this->setFixedSize(376, 56);
    stopwatch1 = new QLabel(this);//计次
    stopwatch1->move(24, 9);
    stopwatch1->setFixedSize(100, 17);
    stopwatch1->setStyleSheet("font: 11pt 'Sans Serif';background-color: rgb();width:45px;\
                              height:17px;\
                              font-size:18px;\
                              font-family:Source Han Sans CN;\
                              font-weight:400;\
                              color:rgba(255,255,255,1);");
    stopwatch1->setText("起床铃");


    stopwatch2 = new QLabel( this);//间隔
    stopwatch2->move(24, 34);
    stopwatch2->setFixedSize(100, 17);
    stopwatch2->setStyleSheet("font: 9pt 'Sans Serif';color: rgb(148, 148, 148);background-color: rgb();width:85px;\
                              height:14px;\
                              font-size:14px;\
                              font-family:Source Han Sans CN;\
                              font-weight:400;\
                              opacity:0.45;");
    stopwatch2->setText("工作日");
    stopwatch2->setVisible(true);


    stopwatch_line = new QFrame(this);//线
    stopwatch_line->move(13, 52);
    stopwatch_line->setFixedSize(350, 1);
    stopwatch_line->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);background-color: rgb(102, 102, 102);"));
    stopwatch3 = new QLabel(this);//记次时间
    stopwatch3->move(239,15);
    stopwatch3->setFixedSize(115, 29);
    stopwatch3->setStyleSheet("font: 17pt 'Sans Serif';background-color: rgb();width:114px;\
                              height:22px;\
                              font-size:30px;\
                              font-family:Source Han Sans CN;\
                              font-weight:400;\
                              color:rgba(255,255,255,1);");
    stopwatch3->setText("00:00");
    stopwatch3->setVisible(true);
}

stopwatch_item::~stopwatch_item()
{

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
