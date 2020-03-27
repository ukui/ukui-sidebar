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
#ifndef HIDEBTN_HOVER_H
#define HIDEBTN_HOVER_H
#include<QPushButton>
#include<QEvent>
#include <QToolButton>

class hideBtn_hover :public QPushButton
{
Q_OBJECT;
public:
    hideBtn_hover(QWidget *parent = 0);
    ~hideBtn_hover();

public:
    void enterEvent(QEvent *e); //鼠标进入事件
    void leaveEvent(QEvent *e);//鼠标离开事件


};


#endif // HIDEBTN_HOVER_H
