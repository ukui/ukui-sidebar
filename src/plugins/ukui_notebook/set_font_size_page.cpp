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
#include "set_font_size_page.h"
#include "ui_set_font_size_page.h"
#include "form.h"
#include "ui_form.h"

Set_font_size_page::Set_font_size_page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Set_font_size_page)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    //setAttribute(Qt::WA_TranslucentBackground);
    set_listwidget();
    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

Set_font_size_page::~Set_font_size_page()
{
    delete ui;
}


void Set_font_size_page::set_listwidget()
{
    for(int i=22; i<35 ; i++ )
    {
        int n = i-22;
        list_aItem[n] =new QListWidgetItem;
        list_aItem[n]->setSizeHint(QSize(30,27));

        ui->listWidget->addItem(list_aItem[n]);

        list_page[n] = new Form(this);
        list_page[n]->resize(QSize(30,23));

        ui->listWidget->setItemWidget(list_aItem[n],list_page[n]);
        list_page[n]->ui->label->setText(QString::number(i));
    }
}
