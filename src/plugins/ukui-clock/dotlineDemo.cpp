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
#include <QStyleOption>
#include <QPainterPath>

DotLineDemo::DotLineDemo(QWidget *parent):
     QWidget(parent)
{
    this->resize(390, 310);
}

DotLineDemo::~DotLineDemo()
{
}

//绘制虚线圈
// Draw a dashed circle
void DotLineDemo::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    QStyleOption opt;
    opt.init(this);
    QColor mainColor;
    if(QColor(255,255,255) == opt.palette.color(QPalette::Base) || QColor(248,248,248) == opt.palette.color(QPalette::Base))
    {
        mainColor = QColor(255, 255, 255, 107);
    }else{
        mainColor = QColor(255, 255, 255, 40);
    }

    painter.save();
    painter.setPen(mainColor);
    painter.setBrush(mainColor);
    QPainterPath bigCircle;
    bigCircle.addEllipse(65, 13, 266, 266);
    QPainterPath path = bigCircle ;
    painter.drawPath(path);
    painter.restore();
}
