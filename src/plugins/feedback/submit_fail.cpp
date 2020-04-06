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
#include "submit_fail.h"
#include "ui_submit_fail.h"

submit_fail::submit_fail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::submit_fail)
{
    ui->setupUi(this);

    setWindowTitle(tr("提交失败"));
    ui->pushButton_2->setFlat(true);
    ui->label->setStyleSheet("font: 30px;");
    ui->label_3->setStyleSheet("");
}


void submit_fail::show_faillinfo(int error_code)
{
    switch (error_code) {
    case 1:
        ui->label_3->setText(tr("远程服务器拒绝连接"));
        break;
    case 2:
        ui->label_3->setText(tr("服务器关闭"));
        break;
    case 3:
        ui->label_3->setText(tr("找不到远程主机名（无效的主机名）"));
        break;
    case 4:
        ui->label_3->setText(tr("与远程服务器的连接超时"));
        break;
    default:
        ui->label_3->setText(tr("未知错误"));
        break;
    }
}
submit_fail::~submit_fail()
{
    delete ui;
}

void submit_fail::on_pushButton_2_clicked()
{
    this->close();
}
