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


#ifndef CLIPBOARDPLUGINIFACE_H
#define CLIPBOARDPLUGINIFACE_H
#include <QObject>
#include <QListWidget>
#include <QGroupBox>
#include "plugin-iface.h"
#include "sidebarclipboardsignal.h"
class ClipboardInterface : public  PluginInterface
{
public:
    virtual ~ClipboardInterface() {}
    virtual QListWidget* getClipbaordListWidget() = 0;
    virtual SidebarClipBoardSignal* createClipSignal() = 0;
    virtual QWidget* getClipbaordGroupBox() = 0;
};
#define ClipboardInterface_iid "org.ukui.sidebar-qt.plugin-iface.ClipboardInterface"
Q_DECLARE_INTERFACE(ClipboardInterface, ClipboardInterface_iid)
#endif // CLIPBOARDPLUGINIFACE_H
