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
#include "noteHeadMenu.h"
#include "ui_noteHeadMenu.h"

noteHeadMenu::noteHeadMenu(QWidget *parent) :
    QWidget(parent)
  , ui(new Ui::noteHeadMenu)
  , color_widget(15,161,90)

{
    ui->setupUi(this);
    this->resize(250,20);
    buttonInit();
}

noteHeadMenu::~noteHeadMenu()
{
    delete ui;
}

void noteHeadMenu::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    painter.setBrush(QBrush(color_widget));
    painter.setPen(Qt::transparent);
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 0);
    rect.setHeight(rect.height() - 0);
    painter.drawRoundedRect(rect, 7, 0);
    //也可用QPainterPath 绘制代替 painter.drawRoundedRect(rect, 15, 15);
    {
        QPainterPath painterPath;
        painterPath.addRoundedRect(rect, 7, 0);
        painter.drawPath(painterPath);
    }
    QWidget::paintEvent(event);
}

void noteHeadMenu::buttonInit()
{
    QPixmap pixmap1;
    QPixmap pixmap2;
    pixmap1 = QPixmap(":/image/1x/close_block.png");
    pixmap2 = QPixmap(":/image/1x/more_block.png");
    ui->pushButtonExit->setIcon(pixmap1);
    ui->pushButtonExit->setIconSize(QSize(20,20));
    ui->pushButtonMenu->setIcon(pixmap2);
    ui->pushButtonMenu->setIconSize(QSize(20,20));

    ui->pushButtonMenu->hide();
}
