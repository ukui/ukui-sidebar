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

#include "smallpluginsmanage.h"
static SmallPluginsManage *SmallPluginsManage_global_instance = nullptr;
SmallPluginsManage::SmallPluginsManage()
{
    m_PluginsNum = 0;
}

SmallPluginsManage::~SmallPluginsManage()
{

}

void SmallPluginsManage::SmallPluginsManageInit()
{
    SmallPluginsManage::getInstance();
    return;
}

SmallPluginsManage* SmallPluginsManage::getInstance()
{
    if (nullptr == SmallPluginsManage_global_instance) {
        SmallPluginsManage_global_instance = new SmallPluginsManage();
        return SmallPluginsManage_global_instance;
    }
    return SmallPluginsManage_global_instance;
}

void SmallPluginsManage::registerSmallplugin(PluginInterface *key, SidebarSmallPluginInterface *value)
{
    qDebug() << "entre";
    qDebug() << "key" << key;
    qDebug() << "value" << value;
    if (key == nullptr || value == nullptr) {
        qDebug() << "registerSmallplugin --> key PluginInterface =nullptr || SidebarSmallPluginInterface = nullptr";
        return;
    }

    if (m_pSmallPluginsHash.value(key)) {
        qDebug() << "m_pSmallPluginsHash has key PluginInterface";
        return;
    }
    qDebug() << "zhangsan";
    m_pSmallPluginsHash.insert(key, value);
    m_PluginsNum++;
    return;
}

SidebarSmallPluginInterface* SmallPluginsManage::getSmallplugin(PluginInterface *key)
{
    if (key == nullptr) {
        qDebug() << "getSmallplugin --> PluginInterface key = nullptr";
        return nullptr;
    }
    return m_pSmallPluginsHash.value(key);
}

void SmallPluginsManage::removeSmallplugin(PluginInterface *key)
{
    if (key == nullptr) {
        qDebug() << "removeSmallplugin --> PluginInterface key = nullptr";
        return;
    }
    m_pSmallPluginsHash.remove(key);
    return;
}
