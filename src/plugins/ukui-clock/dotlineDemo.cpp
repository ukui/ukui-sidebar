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
#include "dotlineDemo.h"
#include <QDebug>

DotLineDemo::DotLineDemo(QWidget *parent):
     QWidget(parent)
{
    this->resize(454, 370);
}

DotLineDemo::~DotLineDemo()
{
    //delete widget;
    qDebug()<<"-------DotLineDemo---------";

}

//绘制虚线圈
// Draw a dashed circle
void DotLineDemo::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    // 反走样  antialiasing
    painter.setRenderHint(QPainter::Antialiasing, true);

    //color: rgb(148, 148, 148);   Qt::gray
    painter.setPen(QPen(QColor(60, 60, 60), 4, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(QPointF(226, 180), 170, 170);
}
