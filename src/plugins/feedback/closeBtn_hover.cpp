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
#include"closeBtn_hover.h"
#include <QStyleOption>
#include <QPainter>
#include <QDebug>
closeBtn_hover::closeBtn_hover(QWidget* parent) :QPushButton(parent)
{

}
closeBtn_hover::~closeBtn_hover()
{

}
void closeBtn_hover::enterEvent(QEvent *e)
{
    Q_UNUSED(e);
    setStyleSheet("background-color:rgb(240,65,52);border-image:url(:/image/close_hover.png);border-radius:4px;");

}
void closeBtn_hover::leaveEvent(QEvent *e)
{
    Q_UNUSED(e);
    setStyleSheet("background-color:rgb(255,255,255);border-image:url(:/image/close_default.png);border-radius:4px;");
}


