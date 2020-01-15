#ifndef CLIPBOARDPLUGINIFACE_H
#define CLIPBOARDPLUGINIFACE_H
#include <QObject>
#include <QListWidget>
#include <QGroupBox>
#include "plugin-iface.h"
#include "sidebarclipboardsignal.h"
class ClipboardInterface : public  PluginInterface
{
public:
    virtual ~ClipboardInterface() {}
    virtual QListWidget* getClipbaordListWidget() = 0;
    virtual SidebarClipBoardSignal* createClipSignal() = 0;
    virtual QGroupBox* getClipbaordGroupBox() = 0;
};
#define ClipboardInterface_iid "org.ukui.sidebar-qt.plugin-iface.ClipboardInterface"
Q_DECLARE_INTERFACE(ClipboardInterface, ClipboardInterface_iid)
#endif // CLIPBOARDPLUGINIFACE_H
