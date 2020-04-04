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


#include "pluginmanage.h"
#include "clipboardpluginiface.h"
#include "widget.h"
#include "smallpluginsmanage.h"
#include <QDebug>
#include <QDir>
#include <QPluginLoader>
#include <QApplication>
static PluginManager *global_instance = nullptr;

PluginManager::PluginManager(QObject *parent) : QObject(parent)
{
    QDir pluginsDir("/usr/lib/ukui-sidebar/sidebarSmallPlugins");
    pluginsDir.setFilter(QDir::Files);

    qDebug()<<pluginsDir.entryList().count();
    Q_FOREACH(QString strPluginName, pluginsDir.entryList(QDir::Files)) {
        qDebug()<<strPluginName;
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(strPluginName));
        qDebug() << pluginLoader.fileName();
        qDebug() << pluginLoader.metaData();
        qDebug() << pluginLoader.load();
        qDebug() << pluginLoader.errorString();
        QObject *pPlugin = pluginLoader.instance();
        if (!pPlugin) {
            continue;
        }
        qDebug()<<"test start";
        PluginInterface *pPluginInterface = dynamic_cast<PluginInterface*>(pPlugin);
        if (!pPluginInterface) {
            continue;
        }

        qDebug()<<pPluginInterface->name();
        m_PluginInterfaceHash.insert(pPluginInterface->name(), pPluginInterface);
        switch (pPluginInterface->pluginType()) {
            case PluginInterface::SmallPlugin: {
                /* Plugins Num++, add Hash SmallPlugins pPluginInterface-->SmallPluginsInterface */
                qDebug() << "Plugins Num++, add Hash SmallPlugins pPluginInterface-->SmallPluginsInterface";
                SidebarSmallPluginInterface *p_SmallPluginsInterface = dynamic_cast<SidebarSmallPluginInterface*>(pPluginInterface);
                SmallPluginsManage::getInstance()->registerSmallplugin(pPluginInterface, p_SmallPluginsInterface);
                break;
            }
            case PluginInterface::ClipBoard: {
                break;
            }
            case PluginInterface::PushBtton3: {
                break;
            }
            default:
                break;
        }
    }
}

PluginManager::~PluginManager()
{
    m_PluginInterfaceHash.clear();
}

PluginManager *PluginManager::getInstance()
{
    if (!global_instance) {
        global_instance = new PluginManager;
    }
    return global_instance;
}

void PluginManager::setPluginEnableByName(const QString &name, bool enable)
{
    m_PluginInterfaceHash.value(name)->setEnable(enable);
}

void PluginManager::close()
{
    if (global_instance)
        global_instance->deleteLater();
}

void PluginManager::init()
{
    PluginManager::getInstance();
}
