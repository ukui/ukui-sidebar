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


#ifndef PLUGINIFACE_H
#define PLUGINIFACE_H
#include <QString>
#include <QIcon>

class PluginInterface
{
public:
    enum PluginType
    {
        PushBtton1 = 1,
        PushBtton2,
        PushBtton3,
        SmallPlugin,
        ClipBoard,
        Other
    };

    virtual ~PluginInterface() {}

    virtual PluginType pluginType() = 0;

    virtual const QString name() = 0;
    virtual const QString description() = 0;
    virtual const QIcon icon() = 0;
    virtual void setEnable(bool enable) = 0;
    virtual bool isEnable() = 0;
};
//#define PluginInterface_iid "org.ukui.peony-qt.plugin-iface.PluginInterface"
//Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_iid)

#endif // PLUGINIFACE_H
