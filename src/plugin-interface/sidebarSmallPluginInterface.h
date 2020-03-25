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

#ifndef SIDEBARSMALLPLUGININTERFACE_H
#define SIDEBARSMALLPLUGININTERFACE_H
#include "plugin-iface.h"
class SidebarSmallPluginInterface :public PluginInterface
{
public:
    virtual ~SidebarSmallPluginInterface() {}

    virtual int PluginButtonLocation_X() = 0;
    virtual int PluginButtonLocation_Y() = 0;

    virtual QString PluginButtonName() = 0;
    virtual int     pluginsLoadingSequence() = 0;

    virtual QString PluginIconName() = 0;
    virtual int PluginIconSize_W() = 0;
    virtual int PluginIconSize_H() = 0;

    virtual void PluginsShowInterface() = 0;
};
#define SidebarSmallPluginInterface_iid "org.ukui.sidebar-qt.plugin-iface.SmallPluginInterface"
Q_DECLARE_INTERFACE(SidebarSmallPluginInterface, SidebarSmallPluginInterface_iid)
#endif // SIDEBARSMALLPLUGININTERFACE_H
