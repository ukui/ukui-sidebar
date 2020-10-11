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

#include <QPainterPath>

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
    ui->pushButtonExit->setIcon(QPixmap(":/image/1x/close_block.png"));
//    ui->pushButtonExit->setIcon(QIcon::fromTheme("window-close-symbolic"));
    ui->pushButtonExit->setIconSize(QSize(20,20));
    ui->pushButtonMenu->setIcon(QPixmap(":/image/1x/more_block.png"));
    ui->pushButtonMenu->setIconSize(QSize(20,20));
    ui->pushButtonExit->setProperty("useIconHighlightEffect", true);
    ui->pushButtonExit->setProperty("iconHighlightEffectMode", 1);
    ui->pushButtonMenu->hide();
    QPalette palette2 = ui->pushButtonExit->palette();
    palette2.setColor(QPalette::Highlight, Qt::transparent); /* 取消按钮高亮 */
    ui->pushButtonExit->setPalette(palette2);
}
