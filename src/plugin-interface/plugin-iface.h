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
