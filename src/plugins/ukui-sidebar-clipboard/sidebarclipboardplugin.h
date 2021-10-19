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
#include <QBitmap>
#include <QFileInfo>
#include <QThread>
#include <QProcess>
#include <QScrollBar>
#include <unistd.h>
#include "clipboardpluginiface.h"
#include "clipboardwidgetentry.h"
#include "sidebarclipboardsignal.h"
#include "searchwidgetitemcontent.h"
#include "editorwidget.h"
#include "clipboardsignal.h"
#include "clipboardlisetwidget.h"
#include "cleanpromptbox.h"
#include "clipBoardInternalSignal.h"
#include "clipboarddb.h"
#include "previewimagewidget.h"
//#include "clipbaordstructoriginaldata.h"
#define  WIDGET_ENTRY_COUNT 10
#define  SIDEBAR_CLIPBOARD_QSS_PATH  ":/qss/sidebarClipboard.css"
#define  TEXT   "Text"
#define  URL    "Url"
#define  IMAGE  "Image"
#define  DBDATA "Dbdata"
enum fileType {
    Txt,
    Svg,
    Png,
    Bmp,
    Xml,
    Docx,
    Pptx,
    Xlsx,
    Zip,
    Pdf,
    Pro,
    Esle
};

typedef struct  clipboardOriginalDataHash {
    ClipboardWidgetEntry* WidgetEntry;
    const QMimeData* MimeData;
    QPixmap          *p_pixmap;
    QString          text;
    QString          Clipbaordformat;
    QList<QUrl>      urls;
    int              Sequence;
    QString          associatedDb;
} OriginalDataHashValue;

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
    QHash<QListWidgetItem*, OriginalDataHashValue*> m_pClipboardDataHash;
    QList<OriginalDataHashValue*> m_ListClipboardData;
    QListWidget *m_pShortcutOperationListWidget;
    QListWidget *m_pSearchWidgetListWidget;
    QGroupBox   *m_pSidebarClipboardBox;
    QWidget     *m_pSidebarClipboardWidget;
    QLabel      *m_pSideBarClipboardLable;
    QStringList  m_fileSuffix;
    bool         m_bPromptBoxBool;
    bool         m_bsortEntryBool = true;

    QVBoxLayout     *m_pClipboardLaout;
    QClipboard      *m_pSidebarClipboard;
    ClipboardSignal *m_pClipSignal;
    SearchWidgetItemContent *m_pSearchArea;
    QMimeData mineData;

    QTranslator *translator;

    clipboardDb *m_pClipboardDb;

    QThread     *m_pThread;

    previewImageWidget *m_pPreviewImage = nullptr;

    int m_nScreenWidth;
    int m_nScreenHeight;
    int m_nclipboardsite_x = 1200;
    int m_nclipboardsite_y = 0;
    int m_taskHeight = 46;

    /* 注册Widget界面和Item/lable/剪贴板数据/的关系 */
    void registerWidgetOriginalDataHash(QListWidgetItem *key, OriginalDataHashValue *value);
    OriginalDataHashValue *GetOriginalDataValue(QListWidgetItem *key);
    void removeOriginalDataHash(QListWidgetItem *key);
    void sortingEntrySequence();

    /* 对m_ListClipboardData链表的操作 */
    void inserOriginalDataList(OriginalDataHashValue *value);
    void removeOriginalDataList(OriginalDataHashValue *value);
    int  ItertionOriginalDataList(OriginalDataHashValue *value);
    void moveOriginalDataFirstList(OriginalDataHashValue *value);

    //void FixOriginalDataFirstList(OriginalDataHashValue *value, QString text, const QMimeData mimedata);

    void removeLastWidgetItem();                                            /* 限制复制条数 */
    bool booleanExistWidgetItem(QString Text);                              /* 判断在ListWidget是否存在，如果不存在则返回fasle，创建，返回true，不创建 */
    void createFindClipboardWidgetItem();                                   /* 创建查找条目 */
    void WhetherTopFirst();                                                 /* 设置新置顶的条目写入到剪贴版中去 */
    void connectWidgetEntryButton(ClipboardWidgetEntry * w);                /* 连接WIdgetEntry条目中三个按钮的槽函数 */
    void createTipLable();                                                  /* 创建无剪贴板板字样 */
    void createWidget();                                                    /* 创建剪贴板主Widget和搜索栏与条目的ListWidget界面 */
    void sortingEntryShow();                                                /* 將條目有序的展現出來 */
    bool booleanExistWidgetImagin(QPixmap Pixmap);                          /* 判断图片是否在hash表中，如果存在，则删除，然后将图片重新写入到剪贴板中去 */
    void AddfileSuffix();                                                   /* 往链表中加入文件后缀 */
    void creatLoadClipboardDbData(OriginalDataHashValue *value);            /* 加载从数据库中拿到的数据，加入到剪贴板 */
    bool judgeFileExit(QString fullFilePath);                               /* 判断此路径下该文件是否存在 */
    OriginalDataHashValue *saveOriginalData(OriginalDataHashValue *value);  /* 保存OriginalData数据 */
    void setOriginalDataSequence(OriginalDataHashValue *value);             /* 设置条目的sequence */
    void popCreatorDbHaveDate(OriginalDataHashValue *value);                /* 加入关联数据库的置顶条目 */
    QIcon fileSuffixGetsIcon(QString Url);                                  /* 判断Url中当前后缀名，根据后缀名读取图标 */
    QIcon fileSuffixeMatchIcon(int cnt);                                    /* 根据文件名后缀匹配对应的图标 */
    void  getPixmapListFileIcon(QString UrlText, pixmapLabel *pixmapListclass);  /* 多文件时，将图标加入到链表中 */
    QString SetFormatBody(QString text, ClipboardWidgetEntry *w);           /* 设置... */
    QString setMiddleFormatBody(QString text, ClipboardWidgetEntry *w);     /* 从文本中间设置... */
    QString setSpecificString(QString text);                                /* 复制多文件时，设置特殊的字符串 */
    QString catUrlFileName(QString Url);                                    /* 截取Url中的文件名 */
    QString judgeBlankLine(QStringList list);                               /* 去除掉空行，显示有字体的行 */
    bool    substringSposition(QString formatBody, QStringList list);       /* 判断后面是否还有子串 */
    QListWidgetItem* iterationClipboardDataHash(ClipboardWidgetEntry *w);   /* 迭代Hash表m_pClipboardDataHash */
    int iterationDataHashSearchSequence(int Index);                         /* 迭代Hash表查找其中的当前下标是否存在 */
    int setClipBoardWidgetScaleFactor();                                    /* 设置剪贴板的高度，用来作为预览窗体的显示位置 */
    QMimeData *copyMinedata(const QMimeData* mimeReference);                /* 拷贝QMimeData拷贝数据类型 */
    QMimeData *structureQmimeDate(OriginalDataHashValue *value);            /* 构造一个QMimeDate类型数据 */
    void AddWidgetEntry(OriginalDataHashValue *s_pDataHashValue, ClipboardWidgetEntry *w, QString text);     /* 将信息写入到WidgetEntry条目中去 */
    void setEntryItemSize(OriginalDataHashValue* value, ClipboardWidgetEntry *w, QListWidgetItem *item);    /* 设置条目大小 */
    void resetWidgetLabelText();

signals:
    void Itemchange();
    void EditConfirmButtonSignal(ClipboardWidgetEntry *, EditorWidget*);

public slots:
    void createWidgetEntry();
    void popButtonSlots(QWidget *w);                                        /* 置顶槽函数 */
    void editButtonSlots(ClipboardWidgetEntry *w);                          /* 编辑槽函数 */
    void removeButtonSlots(ClipboardWidgetEntry *w);                        /* 编辑槽函数 */
    void fixedWidgetEntrySlots(ClipboardWidgetEntry *w);                    /* 固定槽函数 */
    void cancelFixedWidgetEntrySLots(ClipboardWidgetEntry *w);              /* 取消固定槽函数 */
    void removeAllWidgetItem();                                             /* 移除所有条目槽函数 */
    void searchClipboardLableTextSlots(QString Text);                       /* 查找槽函数 */
    void ItemNumchagedSlots();                                              /* Item条目发生改变槽函数 */
    void loadClipboardDb();                                                 /* 加载数据Text线程槽函数 */
    void previewShowImageSlots(QWidget *w);                                 /* 加载预览图片窗口槽函数 */
    void previewHideImageSlots(QWidget *w);                                 /* 退出预览图片窗口槽函数 */
};

#endif // SIDEBARCLIPBOARDPLUGIN_H
