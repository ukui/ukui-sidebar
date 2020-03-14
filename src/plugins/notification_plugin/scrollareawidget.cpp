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


ScrollBarWidget::ScrollBarWidget()
{
    setStyleSheet("QScrollBar::vertical {width:10px;padding-left:3px;padding-top:0px;padding-right:3px;padding-bottom:0px;background:transparent;border-radius:6px;}"
                  "QScrollBar::handle:vertical {width:4px;background-color:transparent;border-radius:2px;}"
                  "QScrollBar::sub-line:vertical {background-color:transparent;height:0px;width:0px;}"
                  "QScrollBar::add-line:vertical {background-color:transparent;height:0px;width:0px;}");
    return;
}

void ScrollBarWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    setStyleSheet("QScrollBar::vertical {width:10px;padding-left:2px;padding-top:0px;padding-right:2px;padding-bottom:0px;background:transparent;border-radius:6px;}"
                  "QScrollBar::handle:vertical {width:6px;background-color:rgba(72,72,76,1);border-radius:3px;}"
                  "QScrollBar::handle:vertical:hover{width:6px;background-color:rgba(97,97,102,1);border-radius:3px;}"
                  "QScrollBar::handle:vertical:pressed{width:6px;background-color:rgba(133,133,140,1);border-radius:3px;}"
                  "QScrollBar::sub-line:vertical {background-color:transparent;height:0px;width:0px;}"
                  "QScrollBar::add-line:vertical {background-color:transparent;height:0px;width:0px;}");
    return;
}

void ScrollBarWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    setStyleSheet("QScrollBar::vertical {width:10px;padding-left:3px;padding-top:0px;padding-right:3px;padding-bottom:0px;background:transparent;border-radius:6px;}"
                  "QScrollBar::handle:vertical {width:4px;background-color:rgba(61,61,65,1);border-radius:2px;}"
                  "QScrollBar::sub-line:vertical {background-color:transparent;height:0px;width:0px;}"
                  "QScrollBar::add-line:vertical {background-color:transparent;height:0px;width:0px;}");
    return;
}

ScrollAreaWidget::ScrollAreaWidget()
{
    setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    setWidgetResizable(true);
    ScrollBarWidget *pScrollbar = new ScrollBarWidget;
    setVerticalScrollBar(pScrollbar);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);       //隐藏横向滚动条
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);          //显示纵向滚动条
}

void ScrollAreaWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->verticalScrollBar()->setStyleSheet("QScrollBar::vertical {width:10px;padding-left:3px;padding-top:0px;padding-right:3px;padding-bottom:0px;background:transparent;border-radius:6px;}"
                  "QScrollBar::handle:vertical {width:4px;background-color:rgba(61,61,65,1);border-radius:2px;}"
                  "QScrollBar::sub-line:vertical {background-color:transparent;height:0px;width:0px;}"
                  "QScrollBar::add-line:vertical {background-color:transparent;height:0px;width:0px;}");
    return;
}

void ScrollAreaWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->verticalScrollBar()->setStyleSheet("QScrollBar::vertical {width:10px;padding-left:3px;padding-top:0px;padding-right:3px;padding-bottom:0px;background:transparent;border-radius:6px;}"
                  "QScrollBar::handle:vertical {width:4px;background-color:transparent;border-radius:2px;}"
                  "QScrollBar::sub-line:vertical {background-color:transparent;height:0px;width:0px;}"
                  "QScrollBar::add-line:vertical {background-color:transparent;height:0px;width:0px;}");
    return;
}
