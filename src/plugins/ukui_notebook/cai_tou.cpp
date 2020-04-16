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
#include "cai_tou.h"
#include "ui_cai_tou.h"

cai_tou::cai_tou(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cai_tou)
{
    ui->setupUi(this);
    this->resize(250,8);
}

cai_tou::~cai_tou()
{
    delete ui;
}
