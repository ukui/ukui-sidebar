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
#include "emptyNotes.h"
#include "ui_emptyNotes.h"
#include <QBitmap>
#include <QDebug>
#include <QPainter>

emptyNotes::emptyNotes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::emptyNotes)
{
    ui->setupUi(this);

    ui->setupUi(this);
    //p = page;
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.setRenderHint(QPainter::Antialiasing);
    p.drawRoundedRect(bmp.rect(),6,6);
    setMask(bmp);

    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->widget->setStyleSheet("QWidget{background-color: rgba(255, 255, 255, 0.4);}");
    ui->label->setStyleSheet("background-color: rgba();\
                             font-size:20px;\
                                font-weight:400;\
                                color:rgba(40,40,40,1);\
                                line-height:34px;\
                                opacity:0.97;\
                                 ");
     ui->checkBox->setStyleSheet("background-color: rgba();\
                                 font-size:14px;\
                                 font-weight:400;\
                                 color:rgba(102,102,102,1);\
                                 line-height:40px;\
                                 opacity:0.91;");

    setWindowFlags(Qt::FramelessWindowHint);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()) );
}

emptyNotes::~emptyNotes()
{
    delete ui;
}

void emptyNotes::on_pushButton_clicked()
{
    qDebug()<<"111";
    this->close();
}
