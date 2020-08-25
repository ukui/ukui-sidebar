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
#include "pushbutton.h"

PushButton::PushButton(QStringList path, QStringList iconNameList)
{
    IconPath = path;
    IconNameList = iconNameList;
    this->setIcon(QIcon::fromTheme(IconNameList.at(0), QIcon(IconPath.at(0))));

    QPalette palette = this->palette();
    palette.setColor(QPalette::Highlight, Qt::transparent); /* 取消按钮高亮 */
    this->setPalette(palette);
}

void PushButton::mousePressEvent(QMouseEvent *event)
{
    this->setIcon(QIcon::fromTheme(IconNameList.at(2), QIcon(IconPath.at(2))));
    QPushButton::mousePressEvent(event);
}

void PushButton::enterEvent(QEvent *event)
{
    this->setIcon(QIcon::fromTheme(IconNameList.at(1), QIcon(IconPath.at(1))));
    QPushButton::enterEvent(event);
}

void PushButton::mouseReleaseEvent(QMouseEvent *e)
{
    this->setIcon(QIcon::fromTheme(IconNameList.at(0), QIcon(IconPath.at(0))));
    QPushButton::mouseReleaseEvent(e);
}
