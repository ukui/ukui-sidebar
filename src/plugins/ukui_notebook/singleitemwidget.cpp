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
#include "singleitemwidget.h"
#include "ui_singleitemwidget.h"

SingleItemWidget::SingleItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleItemWidget)
{
    ui->setupUi(this);
    SingleItem_init();
    SingleItem_conn();
}

SingleItemWidget::~SingleItemWidget()
{
    delete ui;
}



void SingleItemWidget::SingleItem_conn()
{
    connect(ui->toolButtonDel,SIGNAL(clicked()),this,SLOT(clickDelBtn()));
}

//void SingleItemWidget::paintEvent(QPaintEvent *)
//{
//    QStyleOption opt;
//    opt.init(this);
//    QPainter p(this);

//    p.setBrush(QBrush(QColor("#161617")));
//    p.setOpacity(0.42);
//    p.setPen(Qt::NoPen);

//    p.drawRoundedRect(opt.rect,0,0);
//    p.drawRect(opt.rect);
//    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
//}

/****************Slots*******************/

void SingleItemWidget::clickDelBtn()
{
    qDebug() << "child  click del";
    emit childDelEvent();
}

void SingleItemWidget::SingleItem_init()
{
    qDebug() << "";
//    //设置图片大小
//    ui->toolButtonDel->setIconSize(QSize(12,16));
//    ui->toolButtonLock->setIconSize(QSize(12,16));
    //文本框属性
    ui->textEdit_Item->setReadOnly(true);//只读
    //ui->textEdit_Item->setFocusPolicy(Qt::NoFocus);//无焦点
    ui->textEdit_ItemDate->setReadOnly(true);
}




