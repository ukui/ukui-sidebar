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
#include <QDebug>
#include <QPointF>
#include <QPainterPath>

#include "widget.h"
#include "ui_widget.h"
#include "setFontSizePage.h"
#include "ui_setFontSizePage.h"
#include "setFontColorPage.h"
#include "ui_setFontColorPage.h"
#include "textEditing.h"
#include "ui_textEditing.h"

#ifndef SHADOW_WIDTH
#define SHADOW_WIDTH 0
#endif

Text_editing::Text_editing(Widget* page,QWidget *parent) :
    QWidget(parent)
  , ui(new Ui::Text_editing)
  , pNotebook(page)
  , texteditwidget(new TextEditWidget(this))
{
    ui->setupUi(this);
    initSetup();
    slotsSetup();
}

Text_editing::~Text_editing()
{
    delete ui;
}

void Text_editing::paintEvent(QPaintEvent *)
{
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

void Text_editing::initSetup()
{
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    setProperty("blurRegion", QRegion(QRect(1, 1, 1, 1)));

    texteditwidget->setGeometry(QRect(0, 5, 250, 35));
    texteditwidget->show();

    set_size_page = new SetFontSize(this);
    set_size_page->hide();

    set_color_fort_page = new SetFontColor(this);
    set_color_fort_page->hide();
}

void Text_editing::slotsSetup()
{
    connect(texteditwidget->ui->fontSizeBtn, &QPushButton::clicked, this, [=](){
        QPointF position = this->pos();
        set_size_page->move(position.x()+183,position.y()+40);
        set_size_page->show();
    });
    connect(texteditwidget->ui->fontColorBtn, &QPushButton::clicked, this, [=](){
        QPointF position = this->pos();
        set_color_fort_page->move(position.x()+215,position.y()+40);
        set_color_fort_page->show();
    });
}
