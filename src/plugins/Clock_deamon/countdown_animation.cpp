#include "countdown_animation.h"
#include <QTimer>
#include <unistd.h>
#include <QDebug>
#include <QRoundProgressBar.h>
#include <QApplication>


Countdown_Animation::Countdown_Animation(QWidget *parent , int value) :
    value_max(value),
    QWidget(parent)
{
    setupUi(this);

//   ui->RoundBar3->setFormat("%p");
//   ui->RoundBar3->setBarStyle(QRoundProgressBar::StyleLine);
//   connectToSlider(ui->RoundBar3);

    QGradientStops gradientPoints;
    gradientPoints << QGradientStop(0.5, QColor(255, 160, 90)) << QGradientStop(1, QColor(180, 30, 10)); //渐变起止颜色设置
    RoundBar3->setDataColors(gradientPoints);
    connectToSlider(RoundBar3);
}

Countdown_Animation::~Countdown_Animation()
{
}

void Countdown_Animation::connectToSlider(QRoundProgressBar *bar)
{
    timer = new QTimer();
    timer->setInterval(1000);

    bar->setRange(0, 1000);
    bar->setValue(1000);
   // qDebug()<<value_max<<"----------------------------------------------------------";

    connect(timer, SIGNAL(timeout()), bar, SLOT(setValue()));
    timer->start();
}


void Countdown_Animation::setupUi(QWidget *TestWidget)
{
    if (TestWidget->objectName().isEmpty())
        TestWidget->setObjectName(QString::fromUtf8("TestWidget"));
    TestWidget->resize(454, 461);
    RoundBar3 = new QRoundProgressBar(TestWidget);
    RoundBar3->setObjectName(QString::fromUtf8("RoundBar3"));
    RoundBar3->setGeometry(QRect(0, 0, 454, 461));
    QPalette palette;
    QBrush brush(QColor(255, 255, 255, 0));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Base, brush);
    QBrush brush1(QColor(170, 0, 0, 255));
    brush1.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Highlight, brush1);
    palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush1);
    QBrush brush2(QColor(244, 244, 244, 255));
    brush2.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush2);
    QBrush brush3(QColor(50, 100, 150, 255));
    brush3.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::Highlight, brush3);
    RoundBar3->setPalette(palette);

    retranslateUi(TestWidget);

    QMetaObject::connectSlotsByName(TestWidget);
}

void Countdown_Animation::retranslateUi(QWidget *TestWidget)
{
    TestWidget->setWindowTitle(QApplication::translate("TestWidget", "TestWidget", nullptr));
}
