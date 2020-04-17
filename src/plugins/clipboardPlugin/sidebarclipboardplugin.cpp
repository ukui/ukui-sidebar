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
#include <QTextFrame>
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

    /* 创建剪贴板主Widget和搜索栏与条目的ListWidget界面 */
    createWidget();

    /* 创建无剪贴板板字样 */
    createTipLable();

    /* 创建查找条目 */
    createFindClipboardWidgetItem();

    /* 插件内部通信的信号类 */
    ClipBoardInternalSignal::initInternalSignal();
    ClipBoardInternalSignal *InternalSignal = ClipBoardInternalSignal::getGlobalInternalSignal();

    /* 在点击确认键后判断是否有勾选不再提示这一功能 */
    connect(InternalSignal, &ClipBoardInternalSignal::CheckBoxSelectedSignal, this, [=]() {
        m_bPromptBoxBool = false;
    });

    /* 当剪贴板条目发生变化的时候执行该槽函数 */
    connect(this, &SidebarClipboardPlugin::Itemchange, this, &SidebarClipboardPlugin::ItemNumchagedSlots);

    /* 将控件加入到剪贴板界面中 */
    m_pClipboardLaout = new QVBoxLayout;
    m_pClipboardLaout->setContentsMargins(0,0,0,0);
    m_pClipboardLaout->addWidget(m_pSearchWidgetListWidget);
    m_pClipboardLaout->addWidget(m_pShortcutOperationListWidget);
    m_pClipboardLaout->addWidget(m_pSideBarClipboardLable);

    m_pSidebarClipboardWidget->setLayout(m_pClipboardLaout);
    m_pShortcutOperationListWidget->setVisible(false);

    m_pShortcutOperationListWidget->setObjectName("ShortcutOperationList");
    m_pSearchWidgetListWidget->setObjectName("SearchWidgetListWidget");
    m_pSideBarClipboardLable->setObjectName("SideBarClipboardLable");

    /* 监听系统剪贴板 */
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

/* 创建剪贴板主Widget和搜索栏与条目的ListWidget界面 */
void SidebarClipboardPlugin::createWidget()
{
    m_pSidebarClipboardWidget = new QWidget();
    m_pSidebarClipboardWidget->setObjectName("ClipboardWidget");
    m_pSidebarClipboardWidget->setContentsMargins(0,0,0,0);

    m_pShortcutOperationListWidget = new ClipBoardLisetWidget;
    m_pShortcutOperationListWidget->setContentsMargins(0,0,0,0);

    m_pSearchWidgetListWidget      = new QListWidget;
    m_pSearchWidgetListWidget->setFixedSize(400, 42);
    m_pSearchWidgetListWidget->setContentsMargins(0,0,0,0);
}

/* 创建无剪贴板板字样 */
void SidebarClipboardPlugin::createTipLable()
{
    m_pSideBarClipboardLable = new QLabel(tr("No clip content"));
    m_pSideBarClipboardLable->setContentsMargins(165, 70, 132, 90);
    QTimer::singleShot(1, m_pSideBarClipboardLable, [=](){
        QFont font = m_pSideBarClipboardLable->font();
        font.setPixelSize(14);
        font.setFamily("Noto Sans CJK SC");
        m_pSideBarClipboardLable->setFont(font);
    });
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
        qDebug() << "剪贴板中文本" << text;
    } else if(mimeData->urls().value(0).toString() != "") {
        QList<QUrl> fileUrls = mimeData->urls();

        for (int i = 0; i < fileUrls.size(); ++i) {
            text += fileUrls.value(i).toString();
        }
    } else if(mimeData->hasHtml()) {
        qDebug() << "文本为Html";
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
    s_pDataHashValue->Sequence = 0;

    registerWidgetOriginalDataHash(pListWidgetItem, s_pDataHashValue);

    /* 当超过一定数目的WidgetItem数目时，删除最后一条消息 */
    if (m_pShortcutOperationListWidget->count() >= WIDGET_ENTRY_COUNT) {
        removeLastWidgetItem();
    }

    pListWidgetItem->setSizeHint(QSize(397,42));
    pListWidgetItem->setFlags(Qt::NoItemFlags);

    /* 设置...字样 */
    w->m_pCopyDataLabal->setTextFormat(Qt::PlainText);
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
    if(fontSize > (LableWidth - 10)) {
        QStringList list = formatBody.split("\n");
        if (list.size() >= 2) {
            //当有几行时，只需要截取第一行就行，在第一行后面加...
            /* 判断第一行是否是空行 */
            formatBody = judgeBlankLine(list);
            formatBody = formatBody + "aa";
            int oneFontSize = fontMetrics.width(formatBody);
            if (oneFontSize > (LableWidth - 10)) {
                formatBody = fontMetrics.elidedText(formatBody, Qt::ElideRight, LableWidth - 10);
                return formatBody;
            } else {
                if (!substringSposition(formatBody, list)) {
                    int oneFontSize = fontMetrics.width(formatBody);
                    formatBody = fontMetrics.elidedText(formatBody, Qt::ElideRight, oneFontSize - 1);
                    return formatBody;
                }
            }
        } else {
            //说明只存在一行，在最后面加...就行
            formatBody = fontMetrics.elidedText(formatBody, Qt::ElideRight, LableWidth - 10);
            return formatBody;
        }
    } else {
        QStringList list = formatBody.split("\n");
        if (list.size() >= 2) {
            //取得当前的有字符串的子串
            formatBody = judgeBlankLine(list);
            formatBody = formatBody + "aa";
            if (!substringSposition(formatBody, list)) {
                int oneFontSize = fontMetrics.width(formatBody);
                formatBody = fontMetrics.elidedText(formatBody, Qt::ElideRight, oneFontSize - 1);
            }
        }
    }
    return formatBody;
}

/* 去除掉空行，显示有字体的行 */
QString SidebarClipboardPlugin::judgeBlankLine(QStringList list)
{
    int tmp = list.count();
    for (int i = 0; i < tmp; i++) {
        QString dest = list.at(i);
        dest = dest.trimmed();
        if (dest.size() != 0) {
           return list.at(i);
        }
    }
    return list.at(0);
}

/* 判断当前子串位置，后面是否还有子串 */
bool SidebarClipboardPlugin::substringSposition(QString formatBody, QStringList list)
{
    int tmp = list.count();
    for (int i = 0; i < tmp; i++) {
        QString dest = list.at(i);
        if (dest == formatBody && i == tmp - 1) {
            qDebug() << "后面没有字串，返回true";
            return true;
        }
    }
    return false;
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

/* 将数据保存到Hash表中 */
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

/* 将剪贴板中的数据从Hash表中移除 */
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

/* 将数据有顺序的加入到链表中 */
void SidebarClipboardPlugin::inserOriginalDataList(OriginalDataHashValue *value)
{
    if (m_ListClipboardData.contains(value)) {
        qDebug() << "链表中存在";
        return;
    }
    m_ListClipboardData.insert(0, value);
    return;
}

/* 删除链表中某一个数据 */
void SidebarClipboardPlugin::removeOriginalDataList(OriginalDataHashValue *value)
{
    if (!m_ListClipboardData.contains(value)) {
        qDebug() << "链表中不存在此节点";
        return;
    }
    /* 迭代链表 */
    int tmp = ItertionOriginalDataList(value);
    if (tmp == -1) {
        qWarning() << "在list未此值";
        return;
    }
    m_ListClipboardData.removeAt(tmp);
    return;
}

/* 迭代链表 */
int SidebarClipboardPlugin::ItertionOriginalDataList(OriginalDataHashValue *value)
{
    //stl类型的迭代器
    int length = m_ListClipboardData.count();
    for (int i = 0; i < length; i++) {
        if (m_ListClipboardData.at(i) == value) {
            return i;
        }
    }
    return -1;
}

/* 移动链表中某一个数据到最前面 */
void SidebarClipboardPlugin::moveOriginalDataFirstList(OriginalDataHashValue *value)
{
    /* 从链表中先移除改数据, 然后再重新插入链表的最前面 */
    removeOriginalDataList(value);
    inserOriginalDataList(value);
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

    qDebug() << "获取hash表中minmete数据" << pMimeData;
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
        qWarning() << "置顶槽函数ClipboardWidgetEntry *w 为空";
        return;
    }
    QListWidgetItem *Item = iterationClipboardDataHash(w);
    const QMimeData* pMimeData = GetOriginalDataValue(Item)->MimeData;
    if (nullptr == pMimeData) {
        qWarning() << "剪贴板元数据不存在";
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
        qWarning() << "传入值为空";
        return;
    }
    EditorWidget EditWidget;
    /* 获取保存在hash表中的数据，改变之前保存的数据 */
    QListWidgetItem *Item = iterationClipboardDataHash(w);
    QMimeData* pMimeData = (QMimeData*)GetOriginalDataValue(Item)->MimeData;
    if (nullptr == pMimeData) {
        qWarning() << "剪贴板元数据不存在";
        return;
    }
    QString text = GetOriginalDataValue(Item)->text;
    EditWidget.m_pEditingArea->setPlainText(text);

    QTextDocument *document = EditWidget.m_pEditingArea->document();
    QTextFrame *rootFrame=document->rootFrame();//获取根框架

    QTextFrameFormat format;

    format.setPadding(10);//设置填衬

    format.setBorderStyle(QTextFrameFormat::BorderStyle_Dotted);//设置边框样式

    rootFrame->setFrameFormat(format);//往根框架中加载设置好的格式
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
    } else if (nRet == QDialog::Rejected) {
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
        emit globalClipboardSignal->ClipBoardWidgetEntryEditButtonSignal(); //当点击清楚时，将侧边栏置为不Hide状态
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
    qDebug() << "Text" << Text;

    /* 在清除条目前，先记住每一个当前的位置 */
    if (m_bsortEntryBool) {
        sortingEntrySequence();
    }

    /* 清空之前listWidget中的條目 */
    int tmp = m_pShortcutOperationListWidget->count();
    for (int i = 0; i < tmp; i++) {
        ClipboardWidgetEntry *w = (ClipboardWidgetEntry*)m_pShortcutOperationListWidget->itemWidget(m_pShortcutOperationListWidget->item(0));
        m_pShortcutOperationListWidget->item(0);
        m_pShortcutOperationListWidget->takeItem(0);
    }

    /* 当搜索栏中内容为空，还原之前的数据 */
    if (Text == "") {
        sortingEntryShow();
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
            w->m_pCopyDataLabal->setTextFormat(Qt::PlainText);
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
    int num = m_pClipboardDataHash.size();
    qDebug() << "Item数目发生变化， 当前Item数目" << num;
    if (num > 0) {
        m_pSideBarClipboardLable->setVisible(false);
        m_pShortcutOperationListWidget->setVisible(true);
        m_pSearchArea->m_pClearListWidgetButton->setEnabled(true);
    } else {
        m_pSideBarClipboardLable->setVisible(true);
        m_pShortcutOperationListWidget->setVisible(false);
        m_pSearchArea->m_pClearListWidgetButton->setEnabled(false);
    }
}

void SidebarClipboardPlugin::sortingEntrySequence()
{
    int tmp = m_pShortcutOperationListWidget->count();
    for (int i = 0; i < tmp; i++) {
        GetOriginalDataValue(m_pShortcutOperationListWidget->item(i))->Sequence = tmp - i - 1;
    }
    m_bsortEntryBool = false;
}

void SidebarClipboardPlugin::sortingEntryShow()
{
    int index = 0;
    int count = m_pClipboardDataHash.size();
    bool IndexFlag = true;
    while(index != count) {
        IndexFlag = true;
        qDebug() << "当前条目的下标" << index;
        QHash<QListWidgetItem*, OriginalDataHashValue*>::const_iterator iter1 = m_pClipboardDataHash.constBegin();
        while (iter1 != m_pClipboardDataHash.constEnd()) {
            qDebug() << "當前條目所處的位置-->Sequence -->" << iter1.value()->Sequence;
            if (index == iter1.value()->Sequence) {
                m_pShortcutOperationListWidget->insertItem(0, iter1.key());
                ClipboardWidgetEntry *w = new ClipboardWidgetEntry();
                w->setFixedSize(397, 42);
                connectWidgetEntryButton(w);
                QString Format = SetFormatBody(iter1.value()->text, w);
                w->m_pCopyDataLabal->setTextFormat(Qt::PlainText);
                w->m_pCopyDataLabal->setText(Format);
                iter1.value()->WidgetEntry = w;
                m_pShortcutOperationListWidget->setItemWidget(iter1.key(), w);
                IndexFlag = false;
                index++;
                qDebug() << "進入循環體当前条目的下标" << index;
            }
            ++iter1;
        }
        /* 如果没有进入上面的While循环，说明此Index不存在，继续往后面走 */
        if (IndexFlag) {
            index++;
            count++;
        }
    }
    m_bsortEntryBool = true;
}
