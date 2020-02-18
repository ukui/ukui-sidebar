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


#include "sidebarclipboardplugin.h"
#include <QGuiApplication>
#include <QApplication>
#include <QMimeData>
#include <QFile>
SidebarClipboardPlugin::SidebarClipboardPlugin(QObject *parent)
{
    Q_UNUSED(parent);
    m_pSidebarClipboardBox = new QGroupBox(tr("  剪贴板"));
    m_pSidebarClipboardBox->setObjectName("ClipboardBox");
    m_pClipboardLaout = new QVBoxLayout;
    m_pShortcutOperationListWidget = new QListWidget;
    createFindClipboardWidgetItem();
    m_pClipboardLaout->addWidget(m_pShortcutOperationListWidget);
    m_pSidebarClipboardBox->setLayout(m_pClipboardLaout);
    m_pShortcutOperationListWidget->setObjectName("ShortcutOperationList");
    m_pSidebarClipboardBox->setObjectName("ClipboardBox");
    m_pSidebarClipboard = QApplication::clipboard();
    m_pEditWidget = nullptr;
    connect(m_pSidebarClipboard, &QClipboard::dataChanged, this, [=]() {
       const QMimeData *mimeData = new QMimeData();
       mimeData = m_pSidebarClipboard->mimeData();
       qDebug() << "文本的format" << m_pSidebarClipboard->mimeData()->formats();
       createWidgetEntry(mimeData);
    });

    qDebug() << "after connect, this =" << this;
    /* 加载样式表 */
    QFile file(SIDEBAR_CLIPBOARD_QSS_PATH);
    if (file.open(QFile::ReadOnly)) {
        QString strQss = QLatin1String(file.readAll());
        QString strPaletteColor = strQss.mid(20, 7);
        m_pSidebarClipboardBox->setPalette(QPalette(QColor(strPaletteColor)));
        m_pSidebarClipboardBox->setStyleSheet(strQss);
        file.close();
    }
}

/* 构造原型的QMimeData数据类型 */
QMimeData * SidebarClipboardPlugin::copyMinedata(const QMimeData* mimeReference)
{
    QMimeData *mimecopy = new QMimeData();
    foreach (QString format, mimeReference->formats()) {
//        qDebug() << "剪贴板数据的格式" << format;
        QByteArray data = mimeReference->data(format);
//        if (format.startsWith("x-special/ukui-copied-files")) {
//            int indexBegin = format.indexOf('""') + 1;
//            int indexEnd = format.indexOf('""', indexBegin);
//            format = format.mid(indexBegin, indexEnd - indexBegin);
//        }
        mimecopy->setData(format, data);
    }
    return mimecopy;
}

/* 获取剪贴板的中widgetItem这一条目 */
QListWidget* SidebarClipboardPlugin::getClipbaordListWidget()
{
    if (m_pShortcutOperationListWidget == nullptr) {
        return nullptr;
    } else {
        return m_pShortcutOperationListWidget;
    }
}

/* 创建与侧边栏主app通信类，暂时废弃 */
SidebarClipBoardSignal* SidebarClipboardPlugin :: createClipSignal()
{
    m_pClipSignal = new ClipboardSignal;
    return m_pClipSignal;
}

/* 侧边栏接口，将整个剪贴板界面set进入侧边栏 */
QGroupBox* SidebarClipboardPlugin::getClipbaordGroupBox()
{
    if (m_pSidebarClipboardBox == nullptr) {
        return nullptr;
    } else {
        return m_pSidebarClipboardBox;
    }
}

/* 创建查找条目 */
void SidebarClipboardPlugin::createFindClipboardWidgetItem()
{
    QListWidgetItem *pListWidgetItem = new QListWidgetItem;
    pListWidgetItem->setFlags(Qt::NoItemFlags);
    m_pSearchArea = new SearchWidgetItemContent;
    connect(m_pSearchArea->m_pClearListWidgetButton, &QPushButton::clicked, this, &SidebarClipboardPlugin::removeAllWidgetItem);
    connect(m_pSearchArea->m_pLineEditArea, SIGNAL(textChanged(QString)), this, SLOT(searchClipboardLableTextSlots(QString)));
    pListWidgetItem->setSizeHint(QSize(345,40));
    m_pShortcutOperationListWidget->insertItem(0,pListWidgetItem);
    m_pShortcutOperationListWidget->setItemWidget(pListWidgetItem, m_pSearchArea);
}

/*创建Widgetitem条目*/
void SidebarClipboardPlugin::createWidgetEntry(const QMimeData *mimeData)
{
    if (nullptr == mimeData) {
        qWarning() << "createWidgetEntry形参mimeData为空, 不创建";
        return;
    }
    QString text;
    QListWidgetItem *pListWidgetItem = new QListWidgetItem;
    ClipboardWidgetEntry *w = new ClipboardWidgetEntry;
    if (nullptr == mimeData->urls().value(0).toString()) {
        text = mimeData->text();
        qDebug() << "text文本数据为:" << text;
    } else if(mimeData->urls().value(0).toString() != ""){
        QList<QUrl> fileUrls = mimeData->urls();

        for (int i = 0; i < fileUrls.size(); ++i) {
            text += fileUrls.value(i).toString();
        }
        qDebug() << "text文本URL为:" << text;
    } else {
        qWarning() << "剪贴板数据为空";
        return;
    }

    if (text == "") {
        qWarning() << "text文本为空";
        return ;
    }

    //当有重复的时候将会置顶
    if(booleanExistWidgetItem(text)) {
        qDebug() << "此条内容已存在，就是当前置顶的条数";
        delete pListWidgetItem;
        delete w;
        return;
    }
    registerMimeData(w, copyMinedata(mimeData));  //hash插入QMimeData，保留原数据

    /* 当超过一定数目的WidgetItem数目时，删除最后一条消息 */
    if (m_pShortcutOperationListWidget->count() >= WIDGET_ENTRY_COUNT) {
        removeLastWidgetItem();
    }

    pListWidgetItem->setSizeHint(QSize(345,42));
    pListWidgetItem->setFlags(Qt::NoItemFlags);
    w->m_pCopyDataLabal->setText(text);
    connect(w->m_pPopButton, &QPushButton::clicked, this, [=](){
        this->popButtonSlots(w);
    });

    connect(w->m_pEditButon, &QPushButton::clicked, this, [=](){
        this->editButtonSlots(w);
    });

    connect(w->m_pRemoveButton, &QPushButton::clicked, this, [=](){
        this->removeButtonSlots(w);
    });

    m_pShortcutOperationListWidget->insertItem(1, pListWidgetItem);
    m_pShortcutOperationListWidget->setItemWidget(pListWidgetItem, w);
    registerWidgetItem(w, pListWidgetItem);
}

/* 注册WidgetItem条目与widgetItem的键值对关系 */
void SidebarClipboardPlugin::registerWidgetItem(ClipboardWidgetEntry *key, QListWidgetItem *value)
{
    if (nullptr == key || nullptr == value) {
        qWarning() << "注册：ClipboardWidgetEntry *key," << key << "QListWidgetItem *value值有问题"  << value;
        return;
    }
    if (m_pclipboardEntryItem.value(key)) {
        qWarning() << "注册：value已存在";
        return;
    }
    m_pclipboardEntryItem.insert(key, value);
    return;
}

/* 从hash表中获取QListWidgetItem */
QListWidgetItem *SidebarClipboardPlugin::getWidgetItem(ClipboardWidgetEntry *key)
{
    if (key == nullptr) {
        qWarning() << "获取：lipboardWidgetEntry *key为空";
        return nullptr;
    }
    return m_pclipboardEntryItem.value(key);
}


void SidebarClipboardPlugin::removeWidgetItem(ClipboardWidgetEntry *key)
{
    if (nullptr == key) {
        qWarning() << "删除：lipboardWidgetEntry *key 为空";
        return;
    }
    m_pclipboardEntryItem.remove(key);
    return;
}

/* 注册Mindata数据类型，保存到hash表中 */
void SidebarClipboardPlugin::registerMimeData(ClipboardWidgetEntry *key, const QMimeData *value)
{
    if (key == nullptr || value == nullptr) {
        qWarning() << "key == nullptr || value == nullptr:" << key << value;
        return;
    }
    if (m_pclipbordMimeData.value(key)) {
        qWarning() << "hash表中已存在";
        return;
    }
    m_pclipbordMimeData.insert(key, value);
    return;
}

/* 获取Mindata数据类型 */
const QMimeData* SidebarClipboardPlugin::getMimeData(ClipboardWidgetEntry *key)
{
    if (key == nullptr) {
        qWarning() << "ClipboardWidgetEntry *key为空" << key;
        return nullptr;
    }
    return m_pclipbordMimeData.value(key);
}

/* 移除Mindata数据类型 */
void SidebarClipboardPlugin::removeMimeData(ClipboardWidgetEntry *key)
{
    if (nullptr == key) {
        qWarning() << "删除：ClipboardWidgetEntry *key 为空";
        return;
    }
    m_pclipbordMimeData.remove(key);
    return;
}

/* 将新置顶widget写入到剪贴板中去 */
void SidebarClipboardPlugin::WhetherTopFirst()
{
    qDebug() << "进入了此函数WhetherTopFirst";
    /* 获取第一个条目 */
    //当删除为第一项时，则自动将第二项置顶
    int count = m_pShortcutOperationListWidget->count();
    qDebug() << "当前还剩多少条目" << count;
    QListWidgetItem *PopWidgetItem =  m_pShortcutOperationListWidget->item(1);
    qDebug() << "QListWidgetItem *PopWidgetItem" << PopWidgetItem;
    if (PopWidgetItem == nullptr) {
        qWarning() << "从剪贴板获取的PopWidgetItem指针为空";
        return;
    }

    ClipboardWidgetEntry *tmpWidget = (ClipboardWidgetEntry*)m_pShortcutOperationListWidget->itemWidget(PopWidgetItem);
    qDebug() << "QWidget *tmpWidget" << tmpWidget;
    if (tmpWidget == nullptr) {
        qWarning() << "从剪贴板获取的ClipboardWidgetEntry指针为空";
        return;
    }
    //获取hash表中minmete数据
    const QMimeData* pMimeData = getMimeData(tmpWidget);
    qDebug() << "dasdasdasdasdasdasd" << pMimeData;
    m_pSidebarClipboard->setMimeData((QMimeData*)pMimeData, QClipboard::Clipboard);
    m_pSidebarClipboard->setMimeData((QMimeData*)pMimeData, QClipboard::Selection);
    return;
}

/* 置顶槽函数 */
void SidebarClipboardPlugin::popButtonSlots(ClipboardWidgetEntry *w)
{
    if (w == nullptr) {
        qDebug() << "置顶槽函数ClipboardWidgetEntry *w 为空";
        return;
    }

    const QMimeData* pMimeData = getMimeData(w);
    if (nullptr == pMimeData) {
        qDebug() << "剪贴板元数据不存在";
        return;
    }
    QListWidgetItem *p = getWidgetItem(w); //获取Item
    removeWidgetItem(w); //移除hash表中保存的Widget和Item键值对
    removeMimeData(w);
    m_pShortcutOperationListWidget->takeItem(m_pShortcutOperationListWidget->row(p)); //删除Item;
    w->deleteLater(); //释放掉ClipboardWidgetEntry;
    m_pSidebarClipboard->setMimeData((QMimeData*)pMimeData, QClipboard::Clipboard);
    m_pSidebarClipboard->setMimeData((QMimeData*)pMimeData, QClipboard::Selection);
    return;
}

/* 删除槽函数 */
void SidebarClipboardPlugin::removeButtonSlots(ClipboardWidgetEntry *w)
{
    if (w == nullptr) {
        qWarning() << "删除槽函数ClipboardWidgetEntry *w 为空";
        return;
    }
    QListWidgetItem *p = getWidgetItem(w); //获取Item
    int tmp = m_pShortcutOperationListWidget->row(p); //记录删除时哪一行
    qDebug() << "在删除中行数removeButtonSlots:" << tmp;
    removeWidgetItem(w); //移除hash表中保存的Widget和Item键值对
    removeMimeData(w);
    m_pShortcutOperationListWidget->takeItem(tmp); //删除Item;
//    delete p;
    w->deleteLater(); //释放掉ClipboardWidgetEntry;

    /* 判断当前删除的是不是第一个条目 */
    if (1 == tmp) {
        qDebug() << "删除当前的条目为第一个条目";
        /* 将新的第一个条目中的内容重新写到剪贴板中去 */
        WhetherTopFirst();
        return;
    }
    return;
}

/* 编辑槽函数 */
void SidebarClipboardPlugin::editButtonSlots(ClipboardWidgetEntry *w)
{
    if (m_pEditWidget != nullptr) {
        qInfo() << "编辑界面已存在，不需要再创建";
        return;
    }

    /* 获取保存在hash表中的数据，改变之前保存的数据 */
    QMimeData* pMimeData = (QMimeData*)getMimeData(w);
    if (nullptr == pMimeData) {
        qDebug() << "剪贴板元数据不存在";
        return;
    }

    QListWidgetItem* p_wItem = (QListWidgetItem*)getWidgetItem(w);
    m_pEditWidget = new EditorWidget;
    QString text = w->m_pCopyDataLabal->text();
    m_pEditWidget->m_pEditingArea->setText(text);
    m_pEditWidget->show();

    connect(m_pEditWidget->m_pConfirmButton, &QPushButton::clicked, this, [=](){
        if (w == nullptr) {
            qWarning() << "ClipboardWidgetEntry为空，已被清除";
            return ;
        }

        w->m_pCopyDataLabal->setText(m_pEditWidget->m_pEditingArea->toPlainText());
        pMimeData->setText(m_pEditWidget->m_pEditingArea->toPlainText());

        //获取当前条目所在位置，是不是在第一
        int row_num = m_pShortcutOperationListWidget->row(p_wItem);
        if (row_num == 1) {
            m_pSidebarClipboard->setMimeData((QMimeData*)pMimeData, QClipboard::Clipboard);
            m_pSidebarClipboard->setMimeData((QMimeData*)pMimeData, QClipboard::Selection);
        }
        qDebug() << "d当前所在的条木" << row_num;
        m_pEditWidget->deleteLater();
        m_pEditWidget = nullptr;
    });

    connect(m_pEditWidget->m_pCancelButton, &QPushButton::clicked, this, [=](){
        m_pEditWidget->deleteLater();
        m_pEditWidget = nullptr;
    });
}

/* 当超过限制条数时删除最后一条消息 */
void SidebarClipboardPlugin::removeLastWidgetItem()
{
    ClipboardWidgetEntry *w = (ClipboardWidgetEntry*)m_pShortcutOperationListWidget->itemWidget(m_pShortcutOperationListWidget->item(m_pShortcutOperationListWidget->count()-1));
    qDebug() << "当前条目数目" << m_pShortcutOperationListWidget->count();
    //m_pShortcutOperationListWidget->takeItem(m_pShortcutOperationListWidget->count()-1);
    delete m_pShortcutOperationListWidget->item(m_pShortcutOperationListWidget->count()-1);
    removeWidgetItem(w);
    removeMimeData(w);
    qDebug() << "当前条目数目sadasdsad" << m_pShortcutOperationListWidget->count();
    w->deleteLater();
}

/* 判断在ListWidget是否存在，如果不存在则返回fasle，创建，返回true，不创建 */
bool SidebarClipboardPlugin::booleanExistWidgetItem(QString Text)
{
    int tmp = m_pShortcutOperationListWidget->count();
    for(int i = 1; i < tmp; i++) {
        ClipboardWidgetEntry *w = (ClipboardWidgetEntry*)m_pShortcutOperationListWidget->itemWidget(m_pShortcutOperationListWidget->item(i));
        QString WidgetText = w->m_pCopyDataLabal->text();
        if (WidgetText == Text) {
            if(i == 1) {
                qDebug() << "当前的数据就是置顶数据";
                return true;
            }
            removeButtonSlots(w);
            return false;
        }
    }
    return false;
}

/* 删除所有的WidgetItem */
void SidebarClipboardPlugin::removeAllWidgetItem()
{
    int tmp = m_pShortcutOperationListWidget->count();
    for(int i = 1; i < tmp; i++) {
        ClipboardWidgetEntry *w = (ClipboardWidgetEntry*)m_pShortcutOperationListWidget->itemWidget(m_pShortcutOperationListWidget->item(1));
        m_pShortcutOperationListWidget->takeItem(1);
        delete m_pShortcutOperationListWidget->item(1);
        removeWidgetItem(w);
        w->deleteLater();
    }
    if (m_pEditWidget == nullptr) {
        return ;
    } else {
        m_pEditWidget->deleteLater();
        m_pEditWidget = nullptr;
    }
}

/* 搜索 槽函数 */
void SidebarClipboardPlugin::searchClipboardLableTextSlots(QString Text)
{
    qDebug() << "Text" << Text;
    int row=1;
    QString line;
    while(row<(m_pShortcutOperationListWidget->count()))
    {
        ClipboardWidgetEntry *w = (ClipboardWidgetEntry*)m_pShortcutOperationListWidget->itemWidget(m_pShortcutOperationListWidget->item(row));
        line=w->m_pCopyDataLabal->text();
        if (line.contains(Text, Qt::CaseSensitive)) {
            popButtonSlots(w);
            w->show();
            //w->hide();
        } else {
            w->hide();
        }
        row++;
    }
    return;
}

