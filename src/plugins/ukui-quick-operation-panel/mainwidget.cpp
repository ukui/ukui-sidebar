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
#include "mainwidget.h"
#include <QDebug>
MainWidget::MainWidget()
{
    createAction();
}

// 创建动作
void MainWidget::createAction()
{
    SetAction = new QAction(QIcon::fromTheme(KYLIN_SET_MENU_ICON_NAME, QIcon(KYLIN_EDIT_MENU_ICON_PATH)), QObject::tr("Open"), this);
//    connect(Open, &QAction::triggered, this, &Widget::OpenSidebarSlots);

    EditAction = new QAction(QIcon::fromTheme(KYLIN_EDIT_MENU_ICON_NAME, QIcon(KYLIN_EDIT_MENU_ICON_PATH)), QObject::tr("Edit"), this);
    connect(EditAction, &QAction::triggered, this, &MainWidget::EditOptionSignal);
    this->addAction(SetAction);
    this->addAction(EditAction);
//    this->setContextMenuPolicy(Qt::ActionsContextMenu);
}

//重新绘制背景色
void MainWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    QRect rect = this->rect();
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.setBrush(opt.palette.color(QPalette::Base));
    p.setOpacity(1);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(rect, 12, 12);
    QWidget::paintEvent(event);
}

void MainWidget::mouseReleaseEvent(QMouseEvent *event)
{
    emit hideDropdownBox();
    QWidget::mouseReleaseEvent(event);
}
