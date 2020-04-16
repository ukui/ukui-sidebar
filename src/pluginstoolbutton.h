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
#ifndef PLUGINSTOOLBUTTON_H
#define PLUGINSTOOLBUTTON_H

#include <QWidget>
#include <QToolButton>
class PluginsToolButton : public QToolButton
{
public:
    explicit PluginsToolButton(QWidget *parent = nullptr);
    enum SidebarButtonStatus{NORMAL, HOVER, PRESS};
    SidebarButtonStatus status;
protected:
    void enterEvent(QEvent *e);             //鼠标进入事件
    void leaveEvent(QEvent *e);             //鼠标离开事件
    void mousePressEvent(QMouseEvent *e);   //按钮点击事件
    void paintEvent(QPaintEvent *e);
};

#endif // PLUGINSTOOLBUTTON_H
