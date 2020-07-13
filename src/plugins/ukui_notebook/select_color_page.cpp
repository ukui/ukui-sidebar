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
#include "paletteWidget.h"
#include "ui_paletteWidget.h"
#include "select_color_page.h"
#include "ui_select_color_page.h"

#ifndef SHADOW_WIDTH
#define SHADOW_WIDTH 0
#endif

select_color_page::select_color_page(Widget* page ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::select_color_page),
    paletteWidget(new PaletteWidget(this))
{
    ui->setupUi(this);
    pNotebook = page;
    this->setAttribute(Qt::WA_TranslucentBackground);    
    this->setProperty("blurRegion", QRegion(QRect(1, 1, 1, 1)));//透明
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    //connect(pNotebook->ui->sort_2_btn,SIGNAL(clicked()),this,SLOT(color_clicked()));

    paletteWidget->setGeometry(QRect(0, 5, 250, 35));
    paletteWidget->show();
}

select_color_page::~select_color_page()
{
    delete ui;
}



void select_color_page::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    QPainter painter(this);
    QStyleOption opt;
    opt.init(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(opt.palette.color(QPalette::Base));
//    if(painter.brush().color().value() == 34){
//        ui->white_btn->setStyleSheet(QString::fromUtf8("background:rgba(236,238,242,1);\n"
//                                                       "border-radius:2px;"));
//    }else if(painter.brush().color().value() == 255){
//        ui->white_btn->setStyleSheet(QString::fromUtf8("background:rgb(19,20,20);\n"
//                                                       "border-radius:2px;"));
//    }
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

void select_color_page::color_clicked()
{
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    if(sink)
    {
        qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
        light_show();
    }
    else
        black_show();
}

void select_color_page::black_show()
{
//    ui->widget->setStyleSheet(QString::fromUtf8("background:rgb(19,20,20);\n"
//                                                "border-radius:4px;"));
//    ui->white_btn->setStyleSheet(QString::fromUtf8("background:rgba(236,238,242,1);\n"
//                                                   "border-radius:2px;"));
}

void select_color_page::light_show()
{
//    ui->widget->setStyleSheet(QString::fromUtf8("background:rgb(240,240,240);\n"
//                                                "border-radius:4px;"));
//    ui->white_btn->setStyleSheet(QString::fromUtf8("background:rgb(19,20,20);\n"
//                                                   "border-radius:2px;"));
}
