#ifndef SIDEBARCLIPBOARDPLUGIN_H
#define SIDEBARCLIPBOARDPLUGIN_H

#include <QGenericPlugin>
#include <QObject>
#include <QHash>
#include <QDebug>
#include <QListWidgetItem>
#include <QListWidget>
#include <QClipboard>
#include <QMimeData>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QStaticText>
#include "clipboardpluginiface.h"
#include "clipboardwidgetentry.h"
#include "sidebarclipboardsignal.h"
#include "searchwidgetitemcontent.h"
#include "editorwidget.h"
#include "clipboardsignal.h"
#define  WIDGET_ENTRY_COUNT 5
#define  SIDEBAR_CLIPBOARD_QSS_PATH  ":/qss/sidebarClipboard.css"
//static SidebarClipboardPlugin *global_instance = nullptr;
class SidebarClipboardPlugin:public QObject, public ClipboardInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.ukui.sidebar-qt.plugin-iface.ClipboardInterface" FILE "clipboardPlugin.json")
    Q_INTERFACES(ClipboardInterface)

public:
    SidebarClipboardPlugin(QObject *parent = 0);
    //plugin implement
    const QString name() override {return QObject::tr("ClipBoard");}
    PluginType pluginType() override {return PluginType::ClipBoard;}
    const QString description() override {return QObject::tr("Show the folder children as icons.");}
    const QIcon icon() override {return QIcon::fromTheme("view-grid-symbolic", QIcon::fromTheme("folder"));}
    void setEnable(bool enable) override {Q_UNUSED(enable)}
    bool isEnable() override {return true;}

    /* 剪贴板接口 */
    virtual QListWidget* getClipbaordListWidget() override;
    virtual SidebarClipBoardSignal* createClipSignal() override;
    virtual QGroupBox* getClipbaordGroupBox() override;
    //    static SidebarClipboardPlugin *getInstance();
    /* 剪贴板成员和成员函数 */
    QHash<ClipboardWidgetEntry*, QListWidgetItem*> m_pclipboardEntryItem;
    QHash<ClipboardWidgetEntry*, const QMimeData*> m_pclipbordMimeData; //保留从剪贴板拿到原数据
    QListWidget *m_pShortcutOperationListWidget;
    QGroupBox   *m_pSidebarClipboardBox;

    QVBoxLayout     *m_pClipboardLaout;
    QClipboard      *m_pSidebarClipboard;
    ClipboardSignal *m_pClipSignal;
    EditorWidget    *m_pEditWidget;
    SearchWidgetItemContent *m_pSearchArea;
    QMimeData mineData;

    void registerWidgetItem(ClipboardWidgetEntry *key, QListWidgetItem *value);
    QListWidgetItem* getWidgetItem(ClipboardWidgetEntry *key);
    void removeWidgetItem(ClipboardWidgetEntry *key);
    void registerMimeData(ClipboardWidgetEntry *key, const QMimeData *value);
    const QMimeData* getMimeData(ClipboardWidgetEntry *key);
    void removeMimeData(ClipboardWidgetEntry *key);
    void removeLastWidgetItem(); //限制复制条数
    bool booleanExistWidgetItem(QString Text);
    void createFindClipboardWidgetItem(); /* 创建查找条目 */
    QMimeData *copyMinedata(const QMimeData* mimeReference);


signals:
    void change();

public slots:
    void createWidgetEntry(const QMimeData *mimeData);
    void popButtonSlots(ClipboardWidgetEntry *w);
    void editButtonSlots(ClipboardWidgetEntry *w);
    void removeButtonSlots(ClipboardWidgetEntry *w);
    void removeAllWidgetItem();
    void searchClipboardLableTextSlots(QString Text);
};

#endif // SIDEBARCLIPBOARDPLUGIN_H
