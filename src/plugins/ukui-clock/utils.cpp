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
#include "utils.h"

Utils::Utils()
{

}
/**
 * @brief 移到鼠标所在屏幕中央。兼容990
 */
void Utils::centerToScreen(QWidget *widget)
{
    if (!widget)

       return;

     QDesktopWidget* m = QApplication::desktop();

     QRect desk_rect = m->screenGeometry(m->screenNumber(QCursor::pos()));

     int desk_x = desk_rect.width();

     int desk_y = desk_rect.height();

     int x = widget->width();

     int y = widget->height();

     widget->move(desk_x / 2 - x / 2 + desk_rect.left(), desk_y / 2 - y / 2 + desk_rect.top());
}


