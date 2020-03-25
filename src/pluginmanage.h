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


#ifndef PLUGINMANAGE_H
#define PLUGINMANAGE_H

#include <QObject>
#include "plugin-iface.h"
#include "sidebarSmallPluginInterface.h"
class PluginManager : public QObject
{
    Q_OBJECT
public:
    static void init();
    static PluginManager *getInstance();
    void close();
    QHash<QString, PluginInterface*> m_PluginInterfaceHash;


Q_SIGNALS:
    void pluginStateChanged(const QString &pluginName, bool enable);

private:
    explicit PluginManager(QObject *parent = nullptr);
    ~PluginManager();


public Q_SLOTS:
    void setPluginEnableByName(const QString &pluginName, bool enable);


};

#endif // PLUGINMANAGE_H
