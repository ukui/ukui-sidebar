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
#include "select_color_page.h"
#include "ui_select_color_page.h"
#include <QPainter>
#include "widget.h"
#include "ui_widget.h"

#ifndef SHADOW_WIDTH
#define SHADOW_WIDTH 0
#endif

select_color_page::select_color_page(Widget* page ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::select_color_page)
{
    ui->setupUi(this);
    pNotebook = page;
    this->setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    light_show();
    connect(pNotebook->ui->sort_2_btn,SIGNAL(clicked()),this,SLOT(color_clicked()));
}

select_color_page::~select_color_page()
{
    delete ui;
}


void select_color_page::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0));

    // 小三角区域;
    QPolygon trianglePolygon;
    trianglePolygon << QPoint(m_startX, m_triangleHeight + SHADOW_WIDTH);
    trianglePolygon << QPoint(m_startX + m_triangleWidth / 2, SHADOW_WIDTH);
    trianglePolygon << QPoint(m_startX + m_triangleWidth, m_triangleHeight + SHADOW_WIDTH);

    QPainterPath drawPath;

    drawPath.addPolygon(trianglePolygon);
    painter.drawPath(drawPath);
}

void select_color_page::color_clicked()
{
    if(sink)
        light_show();
    else
        black_show();
}

void select_color_page::black_show()
{
    ui->widget->setStyleSheet(QString::fromUtf8("background:rgb(19,20,20);\n"
                                                "border-radius:4px;"));
    ui->wight_btn->setStyleSheet(QString::fromUtf8("background:rgba(236,238,242,1);\n"
                                                   "border-radius:2px;"));
}


void select_color_page::light_show()
{
    ui->widget->setStyleSheet(QString::fromUtf8("background:rgb(240,240,240);\n"
                                                "border-radius:4px;"));
    ui->wight_btn->setStyleSheet(QString::fromUtf8("background:rgb(19,20,20);\n"
                                                   "border-radius:2px;"));
}
