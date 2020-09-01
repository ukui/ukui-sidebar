#include "bsrwidget.h"
#include <QDebug>
#include <QPainterPath>
#include <QPainter>
#include <QStylePainter>
#include <QStyleOptionSlider>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

SliderButton::SliderButton(QWidget *parent) : QSlider(parent)
{
    setOrientation(Qt::Orientation::Vertical);
    setMaximum(100);
    setMinimumHeight(200);
    setMinimumWidth(20);

    setStyleSheet(

           "QSlider::groove:Vertical {"
            "border: 0px none;"
            "background: #F5F5F5;"
            "height: 188px;"
            "width: 20px;"
            "border-radius: 5px;"
            "}"

            "QSlider::handle:Vertical {"
            "background: #00BFFF;"
            "border: 0px none;"
            "width: 50px;"
            "height: 15px;"
            "border-radius: 5px;"
            "margin: 0px 0;"
            "border-image:url(:/image/abcd.png);"
            "}"

            "QSlider::add-page:Vertical {"
            "background: #00BFFF;"
            "border-radius: 5px;"
            "}"

            "QSlider::sub-page:horizontal {"
            "background: #DD4814;"
            "border-radius: 5px;"
            "}"

        );

}


BsrWidget::BsrWidget(QWidget *parent) : QWidget(parent)
{

    sliderP = new SliderButton;



    QHBoxLayout *layoutP = new QHBoxLayout;
    layoutP->addWidget(sliderP, 0, Qt::AlignCenter);


    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(layoutP);


    this->setLayout(layout);

    connect(sliderP,  SIGNAL(valueChanged(int)), this, SLOT(changeValueP(int)));


}

void BsrWidget::changeValueP(int value)
{
    qDebug() << "changeValueP()";
    state.p = value;
}

