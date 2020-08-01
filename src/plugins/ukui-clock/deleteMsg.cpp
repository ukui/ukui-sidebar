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
#include "deleteMsg.h"
#include "ui_deleteMsg.h"

delete_msg::delete_msg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_msg)
{
    ui->setupUi(this);
    this->setProperty("blurRegion", QRegion(QRect(1, 1, 1, 1)));
    setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
}

delete_msg::~delete_msg()
{
    delete ui;
}

void delete_msg::on_closebtn_clicked()
{
    close_sure = 0;
    this->close();
}

void delete_msg::on_surebtn_clicked()
{
    close_sure = 1;
    this->close();
}

void delete_msg::on_cancelbtn_clicked()
{
    close_sure = 0;
    this->close();
}
