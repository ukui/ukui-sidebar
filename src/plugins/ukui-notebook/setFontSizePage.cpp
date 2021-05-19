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

#include "setFontSizePage.h"
#include "ui_setFontSizePage.h"
#include "fontButton.h"
#include "ui_fontButton.h"

SetFontSize::SetFontSize(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetFontSize)
{
    ui->setupUi(this);

    initSetup();
}

SetFontSize::~SetFontSize()
{
    delete ui;
    //释放内存
    for (int i=0; i < 10;i++)
    {
        delete list_aItem[i];
    }
}

void SetFontSize::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);

    p.setBrush(opt.palette.color(QPalette::Base));
    p.setOpacity(0.9);
    p.setPen(Qt::NoPen);

    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.drawRoundedRect(opt.rect,6,6);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SetFontSize::initSetup()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    setAttribute(Qt::WA_TranslucentBackground);

    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(int i=10; i<37 ; i++ )
    {
        int n = i-10;
        list_aItem[n] =new QListWidgetItem;
        list_aItem[n]->setSizeHint(QSize(30,27));

        ui->listWidget->addItem(list_aItem[n]);

        list_page[n] = new fontButton(this);
        list_page[n]->resize(QSize(30,23));

        ui->listWidget->setItemWidget(list_aItem[n],list_page[n]);
        list_page[n]->ui->label->setText(QString::number(i));
    }
}
