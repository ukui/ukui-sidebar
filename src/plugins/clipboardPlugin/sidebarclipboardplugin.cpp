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
#include <QTranslator>
#include <QStyle>
#include <QTimer>
#include <QStyleFactory>
ClipboardSignal *globalClipboardSignal;
SidebarClipboardPlugin::SidebarClipboardPlugin(QObject *parent)
{
    Q_UNUSED(parent);
    translator = new QTranslator;
    QLocale locale;
    //获取系统语言环境
    if ( locale.language() == QLocale::Chinese ) {
        qDebug() << "中文环境" ;
        translator->load(QString(":/translations/test_zh_CN.qm"));  //选择翻译文件
        QApplication::installTranslator(translator);
    }
    installEventFilter(this);
    m_bPromptBoxBool = true;
    m_pSidebarClipboardWidget = new QWidget();
    m_pSidebarClipboardWidget->setObjectName("ClipboardWidget");
    m_pSidebarClipboardWidget->setContentsMargins(0,0,0,0);

    m_pClipboardLaout = new QVBoxLayout;
    m_pClipboardLaout->setContentsMargins(0,0,0,0);
    m_pShortcutOperationListWidget = new ClipBoardLisetWidget;
    m_pSearchWidgetListWidget      = new QListWidget;

    m_pSideBarClipboardLable = new QLabel(tr("No clip content"));
    ClipBoardInternalSignal::initInternalSignal();
    ClipBoardInternalSignal *InternalSignal = ClipBoardInternalSignal::getGlobalInternalSignal();
    connect(InternalSignal, &ClipBoardInternalSignal::CheckBoxSelectedSignal, this, [=]() {
        m_bPromptBoxBool = false; //在点击确认键后判断是否有勾选不再提示这一功能
    });
    connect(this, &SidebarClipboardPlugin::Itemchange, this, &SidebarClipboardPlugin::ItemNumchagedSlots);

    m_pSearchWidgetListWidget->setFixedSize(400, 42);
    m_pShortcutOperationListWidget->setContentsMargins(0,0,0,0);
    m_pSearchWidgetListWidget->setContentsMargins(0,0,0,0);

    createFindClipboardWidgetItem();

    m_pClipboardLaout->addWidget(m_pSearchWidgetListWidget);
    m_pClipboardLaout->addWidget(m_pShortcutOperationListWidget);
    m_pClipboardLaout->addWidget(m_pSideBarClipboardLable);

    m_pSidebarClipboardWidget->setLayout(m_pClipboardLaout);
    m_pShortcutOperationListWidget->setVisible(false);

    m_pShortcutOperationListWidget->setObjectName("ShortcutOperationList");
    m_pSearchWidgetListWidget->setObjectName("SearchWidgetListWidget");
    m_pSideBarClipboardLable->setObjectName("SideBarClipboardLable");

    m_pSidebarClipboard = QApplication::clipboard();
    connect(m_pSidebarClipboard, &QClipboard::dataChanged, this, [=]() {
       const QMimeData *mimeData = new QMimeData();
       mimeData = m_pSidebarClipboard->mimeData();
       createWidgetEntry(mimeData);
    });

    /* 加载样式表 */
    QFile file(SIDEBAR_CLIPBOARD_QSS_PATH);
    if (file.open(QFile::ReadOnly)) {
        QString strQss = QLatin1String(file.readAll());
        m_pSidebarClipboardWidget->setStyleSheet(strQss);
        file.close();
    }
}

/* 构造原型的QMimeData数据类型 */
QMimeData * SidebarClipboardPlugin::copyMinedata(const QMimeData* mimeReference)
{
    QMimeData *mimecopy = new QMimeData();
    foreach (QString format, mimeReference->formats()) {

        QByteArray data = mimeReference->data(format);
//        if (format.startsWith("x-special/ukui-copied-files")) {
//            int indexBegin = format.indexOf('""') + 1;
//            int indexEnd = format.indexOf('""', indexBegin);
//            format = format.mid(indexBegin, indexEnd - indexBegin);
//        }
        mimecopy->setData(format, data);
//        qDebug() << "剪贴板数据的格式" << format;
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

/* 创建与侧边栏主app通信类 */
SidebarClipBoardSignal* SidebarClipboardPlugin :: createClipSignal()
{
    m_pClipSignal = new ClipboardSignal;
    globalClipboardSignal = m_pClipSignal;
    return m_pClipSignal;
}

/* 侧边栏接口，将整个剪贴板界面set进入侧边栏 */
QWidget* SidebarClipboardPlugin::getClipbaordGroupBox()
{
    if (m_pSidebarClipboardWidget == nullptr) {
        return nullptr;
    } else {
        return m_pSidebarClipboardWidget;
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
    pListWidgetItem->setSizeHint(QSize(400,38));
    m_pSearchWidgetListWidget->insertItem(0,pListWidgetItem);
    m_pSearchWidgetListWidget->setItemWidget(pListWidgetItem, m_pSearchArea);
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
    w->setFixedSize(397, 42);
    if (nullptr == mimeData->urls().value(0).toString()) {
        text = mimeData->text();
        qDebug() << "text文本数据为:" << text;
    } else if(mimeData->urls().value(0).toString() != "") {
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

    /* 当有重复的时候将会置顶 */
    if(booleanExistWidgetItem(text)) {
        qDebug() << "此条内容已存在，就是当前置顶的条数";
        delete pListWidgetItem;
        delete w;
        return;
    }
    /* hash插入QMimeData，保留原数据 */
    OriginalDataHashValue *s_pDataHashValue = new OriginalDataHashValue;
    s_pDataHashValue->WidgetEntry     = w;
    s_pDataHashValue->MimeData = copyMinedata(mimeData);
    s_pDataHashValue->text     = text;

    registerWidgetOriginalDataHash(pListWidgetItem, s_pDataHashValue);

    /* 当超过一定数目的WidgetItem数目时，删除最后一条消息 */
    if (m_pShortcutOperationListWidget->count() >= WIDGET_ENTRY_COUNT) {
        removeLastWidgetItem();
    }

    pListWidgetItem->setSizeHint(QSize(397,42));
    pListWidgetItem->setFlags(Qt::NoItemFlags);
    //设置...字样
    w->m_pCopyDataLabal->setText(SetFormatBody(text, w));

    /* 将按钮与槽对应上 */
    connectWidgetEntryButton(w);

    m_pShortcutOperationListWidget->insertItem(0, pListWidgetItem);
    m_pShortcutOperationListWidget->setItemWidget(pListWidgetItem, w);
    emit Itemchange();
}

/* 设置...字样 */
QString SidebarClipboardPlugin::SetFormatBody(QString text, ClipboardWidgetEntry *w)
{
    QFontMetrics fontMetrics(w->m_pCopyDataLabal->font());
    int LableWidth = w->m_pCopyDataLabal->width();
    int fontSize = fontMetrics.width(text);
    QString formatBody = text;
    qDebug() << "fontSize > (LableWidth - 10)" << LableWidth << "&&jiantieban---->" << fontSize;
    if(fontSize > (LableWidth - 10))
    {
        QStringList list = formatBody.split("\n");
        if (list.size() >= 2) {
            //当有几行时，只需要截取第一行就行，在第一行后面加...
            formatBody = list.at(0);
            int oneFontSize = fontMetrics.width(formatBody);
            if (oneFontSize > (LableWidth - 10)) {
                formatBody = fontMetrics.elidedText(formatBody, Qt::ElideRight, LableWidth - 10);
            }
            formatBody = fontMetrics.elidedText(formatBody, Qt::ElideRight, oneFontSize);
        } else {
            //说明只存在一行，在最后面加...就行
            qDebug() << "fontSize > (LableWidth - 10)" << LableWidth << "&&jiantieban---->" << fontSize;
            formatBody = fontMetrics.elidedText(formatBody, Qt::ElideRight, LableWidth - 10);
        }
    } else {
        QStringList list = formatBody.split("\n");
        if (list.size() >= 2) {
            formatBody = list.at(0);
            qDebug() << "第一端" << formatBody;
            int oneFontSize = fontMetrics.width(formatBody);
            qDebug () << "oneFontSize = fontMetrics.width(formatBody);" << oneFontSize;
            formatBody = fontMetrics.elidedText(formatBody, Qt::ElideRight, oneFontSize - 1);
        }
    }
    return formatBody;
}

void SidebarClipboardPlugin::connectWidgetEntryButton(ClipboardWidgetEntry *w)
{
    connect(w->m_pPopButton, &QPushButton::clicked, this, [=](){
        this->popButtonSlots(w);
    });

    connect(w->m_pEditButon, &QPushButton::clicked, this, [=](){
        this->editButtonSlots(w);
    });

    connect(w->m_pRemoveButton, &QPushButton::clicked, this, [=](){
        this->removeButtonSlots(w);
    });
}

void SidebarClipboardPlugin::registerWidgetOriginalDataHash(QListWidgetItem *key, OriginalDataHashValue *value)
{
    if (nullptr == key || nullptr == value) {
        qWarning() << "注册：ClipboardWidgetEntry *key," << key << "OriginalDataHashValue *value值有问题"  << value;
        return;
    }
    if (m_pClipboardDataHash.value(key)) {
        qWarning() << "注册：value已存在";
        return;
    }
    m_pClipboardDataHash.insert(key, value);
}

/* 从hash表中获取OriginalDataHashValue */
OriginalDataHashValue *SidebarClipboardPlugin::GetOriginalDataValue(QListWidgetItem *key)
{
    if (key == nullptr) {
        qWarning() << "获取：ClipboardWidgetEntry *key为空";
        return nullptr;
    }

    if (m_pClipboardDataHash.contains(key)) {
        return m_pClipboardDataHash.value(key);
    } else {
        return nullptr;
    }
}

void SidebarClipboardPlugin::removeOriginalDataHash(QListWidgetItem *key)
{
    if (key == nullptr) {
        qWarning() << "获取：ClipboardWidgetEntry *key为空";
        return;
    }
    if (m_pClipboardDataHash.contains(key))
        m_pClipboardDataHash.remove(key);
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
    QListWidgetItem *PopWidgetItem =  m_pShortcutOperationListWidget->item(0);
    qDebug() << "QListWidgetItem *PopWidgetItem" << PopWidgetItem;
    if (PopWidgetItem == nullptr) {
        qWarning() << "从剪贴板获取的PopWidgetItem指针为空";
        return;
    }

    const QMimeData* pMimeData = GetOriginalDataValue(PopWidgetItem)->MimeData;
    if (pMimeData == nullptr) {
        qWarning() << "从剪贴板获取的ClipboardWidgetEntry指针为空";
        return;
    }
    //获取hash表中minmete数据

    qDebug() << "dasdasdasdasdasdasd" << pMimeData;
    m_pSidebarClipboard->setMimeData((QMimeData*)pMimeData, QClipboard::Clipboard);
    m_pSidebarClipboard->setMimeData((QMimeData*)pMimeData, QClipboard::Selection);
    return;
}

QListWidgetItem* SidebarClipboardPlugin::iterationClipboardDataHash(ClipboardWidgetEntry *w)
{
    QHash<QListWidgetItem*, OriginalDataHashValue*>::const_iterator iter2 = m_pClipboardDataHash.constBegin();
    while (iter2 != m_pClipboardDataHash.constEnd()) {
        if (iter2.value()->WidgetEntry == w) {
            return iter2.key();
        }
        ++iter2;
    }
    qDebug() << "没有找到Widget所对应的Item";
    return nullptr;
}

/* 置顶槽函数 */
void SidebarClipboardPlugin::popButtonSlots(ClipboardWidgetEntry *w)
{
    if (w == nullptr) {
        qDebug() << "置顶槽函数ClipboardWidgetEntry *w 为空";
        return;
    }
    QListWidgetItem *Item = iterationClipboardDataHash(w);
    const QMimeData* pMimeData = GetOriginalDataValue(Item)->MimeData;
    if (nullptr == pMimeData) {
        qDebug() << "剪贴板元数据不存在";
        return;
    }
    removeOriginalDataHash(Item);
    QListWidgetItem *deleteItem = m_pShortcutOperationListWidget->takeItem(m_pShortcutOperationListWidget->row(Item)); //删除Item;
    delete deleteItem;

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
    QListWidgetItem *Item = iterationClipboardDataHash(w);
    int tmp = m_pShortcutOperationListWidget->row(Item); //记录删除时哪一行
    qDebug() << "在删除中行数removeButtonSlots:" << tmp;
    removeOriginalDataHash(Item);
    QListWidgetItem *item =  m_pShortcutOperationListWidget->takeItem(tmp); //删除Item;
    delete item;
    /* 判断当前删除的是不是第一个条目 */
    if (0 == tmp) {
        qDebug() << "删除当前的条目为第一个条目";
        /* 将新的第一个条目中的内容重新写到剪贴板中去 */
        WhetherTopFirst();
    }
    emit Itemchange();
    return;
}

/* 编辑槽函数 */
void SidebarClipboardPlugin::editButtonSlots(ClipboardWidgetEntry *w)
{
    qDebug() << "ClipboardWidgetEntry:::" << w;
    /* 防止重复创建 */
    if (w == nullptr) {
        qDebug() << "传入值为空";
        return;
    }
    EditorWidget EditWidget;
    /* 获取保存在hash表中的数据，改变之前保存的数据 */
    QListWidgetItem *Item = iterationClipboardDataHash(w);
    QMimeData* pMimeData = (QMimeData*)GetOriginalDataValue(Item)->MimeData;
    if (nullptr == pMimeData) {
        qDebug() << "剪贴板元数据不存在";
        return;
    }
    QString text = GetOriginalDataValue(Item)->text;
    EditWidget.m_pEditingArea->setText(text);
    int nRet = EditWidget.exec();
    if (nRet == QDialog::Accepted) {
        QString formatBody = SetFormatBody(EditWidget.m_pEditingArea->toPlainText(), w);  // 设置...字样
        qDebug () << "formatBody....." << formatBody;
        if (EditWidget.m_pEditingArea->toPlainText() != text) {
            //当编辑后数据改变时，就需要将m_pLabelText中的value改变
            w->m_pCopyDataLabal->setText(formatBody);
            pMimeData->setText(EditWidget.m_pEditingArea->toPlainText());
            GetOriginalDataValue(Item)->text = EditWidget.m_pEditingArea->toPlainText();
        }
        //获取当前条目所在位置，是不是在第一
        int row_num = m_pShortcutOperationListWidget->row(Item);
        if (row_num == 0) {
            popButtonSlots(w);
        }
        qDebug() << "d当前所在的条木" << row_num;
    }
    else if (nRet == QDialog::Rejected) {
        qDebug() << "不需要做其余操作";
    }
}

/* 当超过限制条数时删除最后一条消息 */
void SidebarClipboardPlugin::removeLastWidgetItem()
{
    ClipboardWidgetEntry *w = (ClipboardWidgetEntry*)m_pShortcutOperationListWidget->itemWidget(m_pShortcutOperationListWidget->item(m_pShortcutOperationListWidget->count()-1));
    qDebug() << "当前条目数目" << m_pShortcutOperationListWidget->count();

    QListWidgetItem *Item = iterationClipboardDataHash(w);
    removeOriginalDataHash(Item);
    QListWidgetItem *tmp = m_pShortcutOperationListWidget->takeItem(m_pShortcutOperationListWidget->count()-1);
    delete tmp;
}

/* 判断在ListWidget是否存在，如果不存在则返回fasle，创建，返回true，不创建 */
bool SidebarClipboardPlugin::booleanExistWidgetItem(QString Text)
{
    int tmp = m_pShortcutOperationListWidget->count();
    for (int i = 0; i < tmp; i++) {
        QString WidgetText = GetOriginalDataValue(m_pShortcutOperationListWidget->item(i))->text;
        if (WidgetText == Text) {
            if(i == 0) {
                qDebug() << "当前的数据就是置顶数据";
                return true;
            }
            removeButtonSlots(GetOriginalDataValue(m_pShortcutOperationListWidget->item(i))->WidgetEntry);
            return false;
        }
    }
    return false;
}

/* 删除所有的WidgetItem */
void SidebarClipboardPlugin::removeAllWidgetItem()
{
    int tmp = m_pShortcutOperationListWidget->count();
    qDebug() << "m_pShortcutOperationListWidget->count()" << tmp;
    if (tmp <= 0) {
        qDebug() << "条目为零，不需要清空";
        return;
    }
    /* 判断用户是否勾选了不再提醒这一功能 */
    if (m_bPromptBoxBool) {
        CleanPromptBox PromptBoxWidget;
        int nRet = PromptBoxWidget.exec();
        if (nRet == QDialog::Accepted) {
            qDebug() << "nRet == QDialog::Accepted";
        } else if (nRet == QDialog::Rejected) {
            qDebug() << "nRet == QDialog::Rejected";
            return;
        }
    }
    for (int i = 0; i < tmp; i++) {
        removeOriginalDataHash(m_pShortcutOperationListWidget->item(0));
        QListWidgetItem *tmp = m_pShortcutOperationListWidget->takeItem(0);
        delete tmp;
    }
    emit Itemchange();
}

/* 搜索 槽函数 */
void SidebarClipboardPlugin::searchClipboardLableTextSlots(QString Text)
{
    qDebug() << "hash表长度" << m_pClipboardDataHash.size();
    QHash<QListWidgetItem*, OriginalDataHashValue*>::const_iterator iter1 = m_pClipboardDataHash.constBegin();
    qDebug() << "Text" << Text;
    int tmp = m_pShortcutOperationListWidget->count();
    for (int i = 0; i < tmp; i++) {
        ClipboardWidgetEntry *w = (ClipboardWidgetEntry*)m_pShortcutOperationListWidget->itemWidget(m_pShortcutOperationListWidget->item(0));
        m_pShortcutOperationListWidget->item(0);
        m_pShortcutOperationListWidget->takeItem(0);
    }

    /* 当搜索栏中内容为空，还原之前的数据 */
    if (Text == "") {
        while (iter1 != m_pClipboardDataHash.constEnd()) {
            m_pShortcutOperationListWidget->insertItem(0, iter1.key());
            ClipboardWidgetEntry *w = new ClipboardWidgetEntry();
            w->setFixedSize(397, 42);
            connectWidgetEntryButton(w);
            QString Format = SetFormatBody(iter1.value()->text, w);
            w->m_pCopyDataLabal->setText(Format);
            iter1.value()->WidgetEntry = w;
            m_pShortcutOperationListWidget->setItemWidget(iter1.key(), w);
            ++iter1;
        }
        return;
    }

    /* 将包含有关键字的条目显示出来 */
    QHash<QListWidgetItem*, OriginalDataHashValue*>::const_iterator iter2 = m_pClipboardDataHash.constBegin();
    while (iter2 != m_pClipboardDataHash.constEnd()) {
        if (iter2.value()->text.contains(Text, Qt::CaseSensitive)) {
            m_pShortcutOperationListWidget->insertItem(0, iter2.key());
            ClipboardWidgetEntry *w = new ClipboardWidgetEntry();
            w->setFixedSize(397, 42);
            connectWidgetEntryButton(w);
            QString Format = SetFormatBody(iter2.value()->text, w);
            w->m_pCopyDataLabal->setText(Format);
            iter2.value()->WidgetEntry = w;
            m_pShortcutOperationListWidget->setItemWidget(iter2.key(), w);
        }
        ++iter2;
    }
    return;
}

/* Item数目发生变化 */
void SidebarClipboardPlugin::ItemNumchagedSlots()
{
    int num = m_pShortcutOperationListWidget->count();
    qDebug() << "Item数目发生变化， 当前Item数目" << num;
    if (num > 0) {
        m_pSideBarClipboardLable->setVisible(false);
        m_pShortcutOperationListWidget->setVisible(true);
    } else {
        m_pSideBarClipboardLable->setVisible(true);
        m_pShortcutOperationListWidget->setVisible(false);
    }
}
