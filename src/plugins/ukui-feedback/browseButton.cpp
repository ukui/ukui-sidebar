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
#include"browseButton.h"
#include <QDebug>
browseButton::browseButton(QWidget* parent) :QPushButton(parent)
{

}
browseButton::~browseButton()
{

}
void browseButton::enterEvent(QEvent *e)
{
    Q_UNUSED(e);
    QFont font;
    font.setUnderline(true);
    setFont(font);
}
void browseButton::leaveEvent(QEvent *e)
{
    Q_UNUSED(e);
    QFont font;
    font.setUnderline(false);
    setFont(font);
}
