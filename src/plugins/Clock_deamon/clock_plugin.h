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
#ifndef CLOCK_PLUGIN_H
#define CLOCK_PLUGIN_H

#include "clock_interface.h"
#include <QPushButton>
#include <QMainWindow>
#include <clock.h>

class clock_plugin : public QObject, public ClockInterface
{

    Q_OBJECT
    //Q_INTERFACES宏用于告诉Qt该类实现的接口
    Q_INTERFACES(ClockInterface)
    //Q_PLUGIN_METADATA宏用于描述插件元数据
    Q_PLUGIN_METADATA(IID ClockInterface_iid FILE "Clock.json")
    //申明该类有D-BUS服务接口
    //Q_CLASSINFO("D-Bus Interface", "com.scorpio.test.value")


public:
    bool Clockflag = false;
    clock_plugin();
    ~clock_plugin();
    void show();

    QWidget *m_pClock;
    QWidget*  centerWidget();
    void onNotification() ;
   // void UI_in_sidebar();

signals:
    void    Clock_ification();


};


#endif // CLOCK_PLUGIN_H
