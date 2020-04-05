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
#include "submit_success.h"
#include "ui_submit_success.h"
#include "feedback.h"

submit_success::submit_success(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::submit_success)
{
    ui->setupUi(this);
    parentWnd =dynamic_cast<feedback*>(parent);
    setWindowTitle(tr("提交成功 "));
    ui->pushButton->setFlat(true);
    ui->pushButton_2->setFlat(true);
    ui->label->setStyleSheet("font: 30px;");
}

submit_success::~submit_success()
{

    delete ui;
}

void submit_success::on_pushButton_2_clicked()
{
    close();
}

void submit_success::on_pushButton_clicked()
{
    parentWnd ->feedback_info_init();
    close();
}
