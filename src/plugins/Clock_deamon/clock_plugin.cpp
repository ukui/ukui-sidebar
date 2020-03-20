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
#include "clock_plugin.h"
#include <QApplication>
#include "clock.h"
#include "connection.h"
#include "debug.h"
#include "clock_interface.h"
#include "qdebug.h"
#include <QDesktopWidget>


clock_plugin::clock_plugin()
{
    m_pClock = new Clock;
}

void clock_plugin::onNotification() {
    qDebug()<< "onNotification";
}

void clock_plugin::show() {
    QDesktopWidget *desk = QApplication::desktop();
    QRect deskRect = desk->availableGeometry();
    m_pClock->show();
    m_pClock->move((deskRect.width()-m_pClock->width())/2, (deskRect.height()-m_pClock->height())/2);
}
clock_plugin::~clock_plugin() {
    if( m_pClock)
    {
        delete m_pClock;
    }
    m_pClock = nullptr;

}

QWidget* clock_plugin::centerWidget()
{
    return  m_pClock;

}



