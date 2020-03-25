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

#ifndef SMALLPLUGINSMANAGE_H
#define SMALLPLUGINSMANAGE_H
#include <QObject>
#include <QDebug>
#include "sidebarSmallPluginInterface.h"
#include "plugin-iface.h"
class SmallPluginsManage : public QObject
{
    Q_OBJECT
public:
    SmallPluginsManage();
    ~SmallPluginsManage();

    static void SmallPluginsManageInit();
    static SmallPluginsManage *getInstance();

    QHash<PluginInterface*, SidebarSmallPluginInterface*> m_pSmallPluginsHash;
    void registerSmallplugin(PluginInterface *key, SidebarSmallPluginInterface *value);
    SidebarSmallPluginInterface* getSmallplugin(PluginInterface *key);
    void removeSmallplugin(PluginInterface *key);
    int m_PluginsNum;
};

#endif // SMALLPLUGINSMANAGE_H
