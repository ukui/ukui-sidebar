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

#ifndef SIDEBARDBUSSERVICE_H
#define SIDEBARDBUSSERVICE_H

#include <QObject>
#include <QRect>
#include <QWidget>

class SidebarDbusService: public QObject
{
    Q_OBJECT
    //申明该类有D-BUS服务接口
    Q_CLASSINFO("D-Bus Interface", "org.ukui.Sidebar")
public:
    SidebarDbusService(QWidget *parent = nullptr);
    int m_sidebarWidth;                                    // 侧边栏宽度
    bool sidebarState;                                      //展开中/展开完成-true；

private:
    QWidget *m_parent;
public slots:
    int getWidth(); //获取侧边栏当前位置
signals:
    void animationAction(const uint time, const int distance);
};

#endif // SIDEBARDBUSSERVICE_H
