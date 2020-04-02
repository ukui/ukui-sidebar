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
#include "feedback.h"




submit_fail::submit_fail(QWidget *parent) :
    QDialog(parent)
{

    UI_init();
    parentWnd = (feedback *)parent;

}

void submit_fail::UI_init()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("submit_fail"));
    setWindowTitle(tr("提交失败"));

    this->resize(430, 260);
    this->setStyleSheet(QString::fromUtf8("border:2px;"));
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);//设置窗口无边框
    label = new QLabel(this);
    label->setText(tr("问题提交失败"));
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(130, 85, 281, 60));
    label->setStyleSheet(QString::fromUtf8("font: 30px;\n"
                                           "color: rgb(68, 68, 68);"));


    fail_closeBtn = new closeBtn_hover(this);
    fail_closeBtn->setGeometry(QRect(396, 4, 30, 30));
    fail_closeBtn->setStyleSheet("background-color: rgb(255,255,255);border-image:url(:/image/close_default.png);border-radius:4px;");

    connect(fail_closeBtn,SIGNAL(clicked()),this,SLOT(close_fail_window()));

    resendBtn = new QPushButton(this);
    resendBtn->setGeometry(QRect(130, 160, 60, 26));
    resendBtn->setText(tr("重新发送"));
    resendBtn->setFlat(true);
    resendBtn->setStyleSheet(QString::fromUtf8("color: rgb(61, 107, 229);"));
    connect(resendBtn,SIGNAL(clicked()),this,SLOT(resend_feedbackinfo()));

    pushButton_2 = new QPushButton(this);
    pushButton_2->setText(tr("退出"));
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_2->setGeometry(QRect(220, 160, 40, 26));
    pushButton_2->setStyleSheet(QString::fromUtf8("color: rgb(61, 107, 229);"));
    pushButton_2->setFlat(true);
    label_2 = new QLabel(this);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(70, 94, 50, 50));
    label_2->setStyleSheet(QString::fromUtf8("background-image: url(://fail.png);"));
    label_3 = new QLabel(this);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setGeometry(QRect(130, 140, 291, 16));
    label_3->setStyleSheet(QString::fromUtf8("font: 12px;\n"
                                             "color: rgb(33, 33, 33);"));

    connect(pushButton_2,SIGNAL(clicked()),this,SLOT(on_pushButton_2_clicked()));
}
void submit_fail::show_faillinfo(int error_code)
{
    switch (error_code) {
    case 1:
        label_3->setText(tr("远程服务器拒绝连接"));
        break;
    case 2:
        label_3->setText(tr("服务器关闭"));
        break;
    case 3:
        label_3->setText(tr("找不到远程主机名（无效的主机名）"));
        break;
    case 4:
        label_3->setText(tr("与远程服务器的连接超时"));
        break;
    default:
        label_3->setText(tr("未知错误"));
        break;
    }
}
submit_fail::~submit_fail()
{
}

void submit_fail::on_pushButton_2_clicked()
{
    this->close();
    parentWnd->window_close();
}
void submit_fail::close_fail_window()
{
    this->close();
}
void submit_fail::resend_feedbackinfo()
{
    parentWnd->resend_info_when_sendfail();
    this->close();
}
