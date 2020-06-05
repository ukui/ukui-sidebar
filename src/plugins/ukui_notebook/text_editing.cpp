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
#include <QPainter>
#include <QDebug>
#include <QPointF>
#include "widget.h"
#include "ui_widget.h"
#include "set_font_size_page.h"
#include "ui_set_font_size_page.h"
#include "set_font_color_page.h"
#include "ui_set_font_color_page.h"
#include "text_editing.h"
#include "ui_text_editing.h"

#ifndef SHADOW_WIDTH
#define SHADOW_WIDTH 0
#endif

Text_editing::Text_editing(Widget* page,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Text_editing)
{
    ui->setupUi(this);
    pNotebook = page;
    this->setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);

    set_btn_image();

    //ui->light_blue_btn->setStyle(new CustomStyle());
    //ui->colorBtn->setCheckable(true);
    ui->BoldBtn->setCheckable(true);
    ui->ItalicBtn->setCheckable(true);
    ui->underlineBtn->setCheckable(true);
    ui->StrikeOutResolvedBtn->setCheckable(true);
    ui->showListBtn->setCheckable(true);
    ui->showNUMList->setCheckable(true);

    set_size_page = new Set_font_size_page(this);
    set_size_page->hide();

    set_color_fort_page = new Set_font_color_page(this);
    set_color_fort_page->hide();
    connect(pNotebook->ui->sort_2_btn,SIGNAL(clicked()),this,SLOT(color_clicked()));
}

Text_editing::~Text_editing()
{
    delete ui;
}

void Text_editing::set_btn_image()
{
    pixmap1=QPixmap(":/image/1x/bold.png");
    pixmap2=QPixmap(":/image/1x/Italic.png");
    pixmap3=QPixmap(":/image/1x/under_line-new.png");
    pixmap4=QPixmap(":/image/1x/del_line.png");
    pixmap5=QPixmap(":/image/1x/Symbol.png");
    pixmap6=QPixmap(":/image/1x/number.png");

    ui->BoldBtn->setIcon(pixmap1);
    ui->BoldBtn->setIconSize(QSize(36,36));
    ui->ItalicBtn->setIcon(pixmap2);
    ui->ItalicBtn->setIconSize(QSize(36,36));
    ui->underlineBtn->setIcon(pixmap3);
    ui->underlineBtn->setIconSize(QSize(36,36));
    ui->StrikeOutResolvedBtn->setIcon(pixmap4);
    ui->StrikeOutResolvedBtn->setIconSize(QSize(36,36));
    ui->showListBtn->setIcon(pixmap5);
    ui->showListBtn->setIconSize(QSize(36,36));
    ui->showNUMList->setIcon(pixmap6);
    ui->showNUMList->setIconSize(QSize(36,36));
}

void Text_editing::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    if(pNotebook->m_isThemeChanged){
        painter.setBrush(QColor(0, 0, 0));
    }else{
        painter.setBrush(QColor(240, 240, 240));
    }
    // 小三角区域;
    QPolygon trianglePolygon;
    trianglePolygon << QPoint(m_startX, m_triangleHeight + SHADOW_WIDTH);
    trianglePolygon << QPoint(m_startX + m_triangleWidth / 2, SHADOW_WIDTH);
    trianglePolygon << QPoint(m_startX + m_triangleWidth, m_triangleHeight + SHADOW_WIDTH);

    QPainterPath drawPath;

    drawPath.addPolygon(trianglePolygon);
    painter.drawPath(drawPath);
}

void Text_editing::on_light_blue_btn_clicked()
{
    QPointF position = this->pos();
    set_size_page->move(position.x()+183,position.y()+40);
    set_size_page->show();
}

void Text_editing::on_blue_btn_2_clicked()
{
    QPointF position = this->pos();
    set_color_fort_page->move(position.x()+215,position.y()+40);
    set_color_fort_page->show();
}

void Text_editing::color_clicked()
{
    if(sink)
        light_show();
    else
        black_show();
}

void Text_editing::light_show()
{
    ui->widget->setStyleSheet(QString::fromUtf8("background:rgb(240,240,240);\n""border-radius:4px;"));
    ui->BoldBtn->setStyleSheet(QString::fromUtf8("background:rgba(240,240,240,0.9);"));
    ui->ItalicBtn->setStyleSheet(QString::fromUtf8("background:rgb(240,240,240);"));
    ui->underlineBtn->setStyleSheet(QString::fromUtf8("background:rgba(240,240,240,0.9);"));
    ui->StrikeOutResolvedBtn->setStyleSheet(QString::fromUtf8("background:rgba(240,240,240,0.9);"));
    ui->frame->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
    ui->showListBtn->setStyleSheet(QString::fromUtf8("background:rgba(240,240,240,0.9);"));
    ui->showNUMList->setStyleSheet(QString::fromUtf8("background:rgba(240,240,240,0.9);"));
    // ui->blue_btn_2->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 255, 180);\n"));
    ui->blue_btn->setStyleSheet(QString::fromUtf8("background-color: rgb(167, 167, 167);\n"
                                                  "border-top-right-radius:4px;\n"
                                                  "border-top-left-radius:0px;\n"
                                                  "border-bottom-right-radius:4px;\n"
                                                  "border-bottom-left-radius:0px;"));
    ui->light_blue_btn->setStyleSheet(QString::fromUtf8("\n"
                                                        "background-color: rgb(167, 167, 167);\n"
                                                        "color: rgba(145, 145, 145, 1);\n"
                                                        "border-top-left-radius:4px;\n"
                                                        "border-top-right-radius:0px;\n"
                                                        "border-bottom-left-radius:4px;\n"
                                                        "border-bottom-right-radius:0px;\n"));
}

void Text_editing::black_show()
{
    ui->widget->setStyleSheet(QString::fromUtf8("background:rgb(19,20,20);\n""border-radius:4px;"));
    ui->BoldBtn->setStyleSheet(QString::fromUtf8("background:rgba(19,20,20,0.9);"));
    ui->ItalicBtn->setStyleSheet(QString::fromUtf8("background:rgb(19,20,20);"));
    ui->underlineBtn->setStyleSheet(QString::fromUtf8("background:rgba(19,20,20,0.9);"));
    ui->StrikeOutResolvedBtn->setStyleSheet(QString::fromUtf8("background:rgba(19,20,20,0.9);"));
    ui->frame->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
    ui->showListBtn->setStyleSheet(QString::fromUtf8("background:rgba(19,20,20,0.9);"));
    ui->showNUMList->setStyleSheet(QString::fromUtf8("background:rgba(19,20,20,0.9);"));
    //ui->blue_btn_2->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 255, 180);\n"));
    ui->blue_btn->setStyleSheet(QString::fromUtf8("background-color: rgb(67, 67, 67);\n"
                                                  "border-top-right-radius:4px;\n"
                                                  "border-top-left-radius:0px;\n"
                                                  "border-bottom-right-radius:4px;\n"
                                                  "border-bottom-left-radius:0px;"));
    ui->light_blue_btn->setStyleSheet(QString::fromUtf8("\n"
                                                        "background-color: rgb(67, 67, 67);\n"
                                                        "color: rgba(145, 145, 145, 1);\n"
                                                        "border-top-left-radius:4px;\n"
                                                        "border-top-right-radius:0px;\n"
                                                        "border-bottom-left-radius:4px;\n"
                                                        "border-bottom-right-radius:0px;\n"));
}


