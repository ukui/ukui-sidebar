/*
* Copyright (C) 2020 Tianjin KYLIN Information Technology Co., Ltd.
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

#include <QPainter>
#include <QPainterPath>

#include "widget.h"
#include "ui_widget.h"
#include "ui_paletteWidget.h"
#include "selectColorPage.h"
#include "ui_selectColorPage.h"

#ifndef SHADOW_WIDTH
#define SHADOW_WIDTH 0
#endif

SelectColor::SelectColor(Widget* page, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectColor),
    paletteWidget(new PaletteWidget(this))
{
    ui->setupUi(this);
    pNotebook = page;
    initSetup();
}

SelectColor::~SelectColor()
{
    delete ui;
}

void SelectColor::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    QStyleOption opt;
    opt.init(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(opt.palette.color(QPalette::Base));
    painter.setOpacity(0.9);

    // 小三角区域;
    QPolygon trianglePolygon;
    trianglePolygon << QPoint(m_startX, m_triangleHeight + SHADOW_WIDTH);
    trianglePolygon << QPoint(m_startX + m_triangleWidth / 2, SHADOW_WIDTH);
    trianglePolygon << QPoint(m_startX + m_triangleWidth, m_triangleHeight + SHADOW_WIDTH);

    QPainterPath drawPath;

    drawPath.addPolygon(trianglePolygon);
    painter.drawPath(drawPath);
}

void SelectColor::initSetup()
{
    setAttribute(Qt::WA_TranslucentBackground);
    setProperty("blurRegion", QRegion(QRect(1, 1, 1, 1)));//透明
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);

    paletteWidget->setGeometry(QRect(0, 5, 250, 35));
    paletteWidget->show();
}
