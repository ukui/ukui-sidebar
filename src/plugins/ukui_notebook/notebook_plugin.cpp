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
#include "notebook_plugin.h"
#include "widget.h"
#include <QDesktopWidget>
#include <QApplication>

notebook_plugin::notebook_plugin()
{
    mp_notebook = new Widget;
}

void notebook_plugin::onNotification() {
    qDebug()<< "onNotification";
}

void notebook_plugin::PluginsShowInterface() {
    if(Notebookflag)
        mp_notebook = new Widget;
    QDesktopWidget *desk = QApplication::desktop();
    QRect deskRect = desk->availableGeometry();
    mp_notebook->show();
    mp_notebook->move((deskRect.width()-mp_notebook->width())/2, (deskRect.height()-mp_notebook->height())/2);
    Notebookflag = true;
}

notebook_plugin::~notebook_plugin() {
    if( mp_notebook)
    {
        delete mp_notebook;
    }
    mp_notebook = nullptr;

}

QWidget* notebook_plugin::centerWidget()
{
    return  mp_notebook;

}
