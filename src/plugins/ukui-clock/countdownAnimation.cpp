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
#include "countdownAnimation.h"
#include <QTimer>
#include <unistd.h>
#include <QDebug>
#include <qroundProgressBar.h>
#include <QApplication>


Countdown_Animation::Countdown_Animation(QWidget *parent , int value) :
    value_max(value),
    QWidget(parent)
{
    setupUi(this);
    //渐变色
    QGradientStops gradientPoints;
    gradientPoints << QGradientStop(0.5, QColor(255, 160, 90)) << QGradientStop(1, QColor(180, 30, 10)); //渐变起止颜色设置
                                                                                                         // Gradient start and stop color settings
    RoundBar3->setDataColors(gradientPoints);
    //设置动态光圈转动频率
    connectToSlider(RoundBar3);
}

Countdown_Animation::~Countdown_Animation()
{
    delete timer;
    delete RoundBar3;
    qDebug()<<"-------Countdown_Animation---------";
}
//设置动态光圈转动频率
// Set dynamic diaphragm rotation frequency
void Countdown_Animation::connectToSlider(QRoundProgressBar *bar)
{
    timer = new QTimer();
    timer->setInterval(1000);

    bar->setRange(0, 3600);
    bar->setValue(3600);

    connect(timer, SIGNAL(timeout()), bar, SLOT(setValue()));
//    timer->start();
}

/**
 * @brief 设置UI
 * @param TestWidget  窗体
 * @param
 *
 * @return 返回说明
 */
void Countdown_Animation::setupUi(QWidget *TestWidget)
{
    if (TestWidget->objectName().isEmpty())
        TestWidget->setObjectName(QString::fromUtf8("TestWidget"));
    TestWidget->resize(454, 461);
    //时间滚轮
    RoundBar3 = new QRoundProgressBar(TestWidget);
    RoundBar3->setObjectName(QString::fromUtf8("RoundBar3"));
    RoundBar3->setGeometry(QRect(0, 0, 454, 461));
    //管理着控件或窗体的所有颜色信息
    QPalette palette;
    QBrush brush(QColor(255, 255, 255, 0));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Base, brush);
    //红色
    QBrush brushRed(QColor(170, 0, 0, 255));
    brushRed.setStyle(Qt::SolidPattern);
    //活跃状态（获得焦点） 高亮背景色
    palette.setBrush(QPalette::Active, QPalette::Highlight, brushRed);
    palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
    //不活跃状态（未获得焦点）
    palette.setBrush(QPalette::Inactive, QPalette::Highlight, brushRed);
    //白色
    QBrush brushWhite(QColor(244, 244, 244, 255));
    brushWhite.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brushWhite);
    //深蓝
    QBrush brushBlue(QColor(50, 100, 150, 255));
    brushBlue.setStyle(Qt::SolidPattern);
    //不可用状态
    palette.setBrush(QPalette::Disabled, QPalette::Highlight, brushBlue);
    RoundBar3->setPalette(palette);

    retranslateUi(TestWidget);

    QMetaObject::connectSlotsByName(TestWidget);
}
/**
 * @brief 翻译窗体名称
 * @param
 * @param
 *
 * @return 返回说明
 */
void Countdown_Animation::retranslateUi(QWidget *TestWidget)
{
    //翻译标题是个""
    TestWidget->setWindowTitle(QApplication::translate("TestWidget", "TestWidget", nullptr));
}
