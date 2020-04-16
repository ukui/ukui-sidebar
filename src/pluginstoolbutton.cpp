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
#include "pluginstoolbutton.h"
#include <QStyleOption>
#include <QPainter>
PluginsToolButton::PluginsToolButton(QWidget *parent)
{
    status = NORMAL;
}

void PluginsToolButton::enterEvent(QEvent *e)
{
    status = HOVER;
}

void PluginsToolButton::leaveEvent(QEvent *e)
{
    status = NORMAL;
}

void PluginsToolButton::mousePressEvent(QMouseEvent *e)
{
    status = PRESS;
}

void PluginsToolButton::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    switch (status) {
      case NORMAL: {
              p.setBrush(QBrush(QColor(opt.palette.color(QPalette::WindowText))));
              p.setOpacity(0.12);
              p.setPen(Qt::NoPen);
              break;
          }
      case HOVER: {
              p.setBrush(QBrush(QColor(opt.palette.color(QPalette::WindowText))));
              p.setOpacity(0.2);
              p.setPen(Qt::NoPen);
              break;
          }
      case PRESS: {
              p.setBrush(QBrush(QColor(opt.palette.color(QPalette::WindowText))));
              p.setOpacity(0.08);
              p.setPen(Qt::NoPen);
              break;
          }
      }
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.drawRoundedRect(opt.rect,4,4);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
