#ifndef PLUGINMANAGE_H
#define PLUGINMANAGE_H

#include <QObject>
#include "plugin-iface.h"
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
