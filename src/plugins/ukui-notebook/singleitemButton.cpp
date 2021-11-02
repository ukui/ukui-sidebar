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

#include "singleitemButton.h"

singleitemButton::singleitemButton()
{
    installEventFilter(this);
    QIcon pushdelIcon;
    this->setFixedSize(34,34);
    this->setIconSize(QSize(16,16));
    pushdelIcon.addFile(":/new/prefix1/SVG/delete-b.svg");
    this->setIcon(pushdelIcon);

}

singleitemButton::~singleitemButton()
{

}

void singleitemButton::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    QIcon pushdelIcon;
    this->setFixedSize(34,34);
    this->setIconSize(QSize(16,16));
    pushdelIcon.addFile(":/new/prefix1/SVG/delete-b-hover.svg");
    this->setIcon(pushdelIcon);
}

void singleitemButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    QIcon pushdelIcon;
    this->setFixedSize(34,34);
    this->setIconSize(QSize(16,16));
    pushdelIcon.addFile(":/new/prefix1/SVG/delete-b-click.svg");
    this->setIcon(pushdelIcon);
}

void singleitemButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    QIcon pushdelIcon;
    this->setFixedSize(34,34);
    this->setIconSize(QSize(16,16));
    pushdelIcon.addFile(":/new/prefix1/SVG/delete-b-hover.svg");
    this->setIcon(pushdelIcon);
    emit buttonclick();
}

void singleitemButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    QIcon pushdelIcon;
    this->setFixedSize(34,34);
    this->setIconSize(QSize(16,16));
    pushdelIcon.addFile(":/new/prefix1/SVG/delete-b.svg");
    this->setIcon(pushdelIcon);
}



