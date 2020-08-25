#ifndef SHORTCUTPANELINTERFACE_H
#define SHORTCUTPANELINTERFACE_H
#include <QWidget>

class shortCutPanelInterface
{
public:
    virtual ~shortCutPanelInterface() {}
    virtual QWidget *getShortCutPanelWidget() = 0;              //获取快捷操作面板的界面
};
#define shortCutPanelInterface_iid "org.ukui.sidebar-qt.plugin-iface.shortCutPanelInterface"
Q_DECLARE_INTERFACE(shortCutPanelInterface, shortCutPanelInterface_iid)

#endif // SHORTCUTPANELINTERFACE_H
