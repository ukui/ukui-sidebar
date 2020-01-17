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


#include "scrollareawidget.h"
#include <QDebug>


ScrollBarWidget::ScrollBarWidget()
{
    setStyleSheet("QScrollBar:vertical{width: 5;}");
//    setFixedHeight(100);
    return;
}

void ScrollBarWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    setStyleSheet("QScrollBar:vertical{width: 10;}");
    return;
}

void ScrollBarWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    setStyleSheet("QScrollBar:vertical{width: 5;}");
    return;
}

ScrollAreaWidget::ScrollAreaWidget()
{
    setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    setWidgetResizable(true);
    ScrollBarWidget *pScrollbar = new ScrollBarWidget;
    setVerticalScrollBar(pScrollbar);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //隐藏横向滚动条
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //隐藏纵向滚动条
}

void ScrollAreaWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); //隐藏纵向滚动条
    return;
}

void ScrollAreaWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //隐藏纵向滚动条
    return;
}
