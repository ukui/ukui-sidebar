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

    virtual QString PluginIconName() = 0;
    virtual int PluginIconSize_W() = 0;
    virtual int PluginIconSize_H() = 0;

    virtual void PluginsShowInterface() = 0;
};
#define SidebarSmallPluginInterface_iid "org.ukui.sidebar-qt.plugin-iface.SmallPluginInterface"
Q_DECLARE_INTERFACE(SidebarSmallPluginInterface, SidebarSmallPluginInterface_iid)
#endif // SIDEBARSMALLPLUGININTERFACE_H
