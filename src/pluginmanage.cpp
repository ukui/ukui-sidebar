#include "pluginmanage.h"
#include "clipboardpluginiface.h"
#include "widget.h"
#include <QDebug>
#include <QDir>
#include <QPluginLoader>
#include <QApplication>
static PluginManager *global_instance = nullptr;

PluginManager::PluginManager(QObject *parent) : QObject(parent)
{
    QDir pluginsDir("/usr/lib/ukui-sidebar/sidebar_pushbutton_plugins");
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
            case PluginInterface::PushBtton1: {
                break;
            }
            case PluginInterface::PushBtton2: {
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
