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


#ifndef SIDEBARCLIPBOARDPLUGIN_H
#define SIDEBARCLIPBOARDPLUGIN_H

#include <QGenericPlugin>
#include <QObject>
#include <QHash>
#include <QDebug>
#include <QListWidgetItem>
#include <QListWidget>
#include <QMouseEvent>
#include <QClipboard>
#include <QMimeData>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QStaticText>
#include <QColor>
#include <QLabel>
#include <QByteArray>
#include "clipboardpluginiface.h"
#include "clipboardwidgetentry.h"
#include "sidebarclipboardsignal.h"
#include "searchwidgetitemcontent.h"
#include "editorwidget.h"
#include "clipboardsignal.h"
#include "clipboardlisetwidget.h"
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
    //plugin implement 统一接口
    const QString name() override {return QObject::tr("ClipBoard");}
    PluginType pluginType() override {return PluginType::ClipBoard;}
    const QString description() override {return QObject::tr("Show the folder children as icons.");}
    const QIcon icon() override {return QIcon::fromTheme("view-grid-symbolic", QIcon::fromTheme("folder"));}
    void setEnable(bool enable) override {Q_UNUSED(enable)}
    bool isEnable() override {return true;}

    /* 剪贴板接口 */
    virtual QListWidget* getClipbaordListWidget() override;
    virtual SidebarClipBoardSignal* createClipSignal() override;
    virtual QWidget* getClipbaordGroupBox() override;
    //    static SidebarClipboardPlugin *getInstance();

    /* 剪贴板成员和成员函数 */
    QHash<ClipboardWidgetEntry*, QListWidgetItem*> m_pclipboardEntryItem;
    QHash<ClipboardWidgetEntry*, const QMimeData*> m_pclipbordMimeData; //保留从剪贴板拿到原数据
    QHash<ClipboardWidgetEntry*, QString> m_pLabelText; //条目中Label与label中的text对应关系
    QListWidget *m_pShortcutOperationListWidget;
    QListWidget *m_pSearchWidgetListWidget;
    QGroupBox   *m_pSidebarClipboardBox;
    QWidget     *m_pSidebarClipboardWidget;
    QLabel      *m_pSideBarClipboardLable;

    QVBoxLayout     *m_pClipboardLaout;
    QClipboard      *m_pSidebarClipboard;
    ClipboardSignal *m_pClipSignal;
    SearchWidgetItemContent *m_pSearchArea;
    QMimeData mineData;

    QTranslator *translator;

    /* 注册Widget条目界面和Item的hash表 */
    void registerWidgetItem(ClipboardWidgetEntry *key, QListWidgetItem *value);
    QListWidgetItem* getWidgetItem(ClipboardWidgetEntry *key);
    void removeWidgetItem(ClipboardWidgetEntry *key);
    void removeHashAllWidgetItem();

    /* 注册Widget条目和剪贴板数据的关系 */
    void registerMimeData(ClipboardWidgetEntry *key, const QMimeData *value);
    const QMimeData* getMimeData(ClipboardWidgetEntry *key);
    void removeMimeData(ClipboardWidgetEntry *key);
    void removeHashAllMimeData();

    /* 注册Widget界面和lable中的文本的关系 */
    void registerLabelText(ClipboardWidgetEntry *key, QString value);  //注册条目中的lable与条目中的原始字符串文本相对应关系
    QString getLabelText(ClipboardWidgetEntry *key);
    void removeLabelText(ClipboardWidgetEntry *key);
    void removeHashAllLabelText();

    void removeLastWidgetItem(); //限制复制条数
    bool booleanExistWidgetItem(QString Text);
    void createFindClipboardWidgetItem(); /* 创建查找条目 */
    void WhetherTopFirst(); /* 设置新置顶的条目写入到剪贴版中去 */
    QMimeData *copyMinedata(const QMimeData* mimeReference);

signals:
    void Itemchange();
    void EditConfirmButtonSignal(ClipboardWidgetEntry *, EditorWidget*);

public slots:
    void createWidgetEntry(const QMimeData *mimeData);
    void popButtonSlots(ClipboardWidgetEntry *w);
    void editButtonSlots(ClipboardWidgetEntry *w);
    void removeButtonSlots(ClipboardWidgetEntry *w);
    void removeAllWidgetItem();
    void searchClipboardLableTextSlots(QString Text);
    void ItemNumchagedSlots();
};

#endif // SIDEBARCLIPBOARDPLUGIN_H
