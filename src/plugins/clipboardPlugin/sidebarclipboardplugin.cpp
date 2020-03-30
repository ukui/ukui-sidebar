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
    m_pSidebarClipboardWidget = new QWidget();
    m_pSidebarClipboardWidget->setObjectName("ClipboardWidget");
    m_pSidebarClipboardWidget->setContentsMargins(0,0,0,0);

    m_pClipboardLaout = new QVBoxLayout;
    m_pClipboardLaout->setContentsMargins(0,0,0,0);

    m_pShortcutOperationListWidget = new ClipBoardLisetWidget;
    m_pSearchWidgetListWidget      = new QListWidget;

    m_pSideBarClipboardLable = new QLabel(tr("No clip content"));

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

    /* 当有重复的时候将会置顶 */
    if(booleanExistWidgetItem(text)) {
        qDebug() << "此条内容已存在，就是当前置顶的条数";
        delete pListWidgetItem;
        delete w;
        return;
    }
    /* hash插入QMimeData，保留原数据 */
    registerMimeData(w, copyMinedata(mimeData));
    registerLabelText(w, text);

    /* 当超过一定数目的WidgetItem数目时，删除最后一条消息 */
    if (m_pShortcutOperationListWidget->count() >= WIDGET_ENTRY_COUNT) {
        removeLastWidgetItem();
    }

    pListWidgetItem->setSizeHint(QSize(397,42));
    pListWidgetItem->setFlags(Qt::NoItemFlags);
    //设置...字样
    QFontMetrics fontMetrics(w->m_pCopyDataLabal->font());
    int fontSize = fontMetrics.width(text);
    QString formatBody = text;
    if(fontSize > (200 - 70))
    {
        QStringList list = formatBody.split("\n");
        if (list.size() >= 2) {
            //当有几行时，只需要截取第一行就行，在第一行后面加...
            formatBody = list.at(0);
            int oneFontSize = fontMetrics.width(formatBody);
            if (oneFontSize > (200 - 50)) {
                formatBody = fontMetrics.elidedText(formatBody, Qt::ElideRight, 200 - 50);
            }
            formatBody = fontMetrics.elidedText(formatBody, Qt::ElideRight, oneFontSize - 1);
        } else {
            //说明只存在一行，在最后面加...就行
            formatBody = fontMetrics.elidedText(formatBody, Qt::ElideRight, 200 - 50);
        }
    } else {
        QStringList list = formatBody.split("\n");
        if (list.size() >= 2) {
            formatBody = list.at(0);
            qDebug() << "第一端" << formatBody;
            int oneFontSize = fontMetrics.width(formatBody);
            formatBody = fontMetrics.elidedText(formatBody, Qt::ElideRight, oneFontSize - 1);
        }
    }
    w->m_pCopyDataLabal->setText(formatBody);

    connect(w->m_pPopButton, &QPushButton::clicked, this, [=](){
        this->popButtonSlots(w);
    });

    connect(w->m_pEditButon, &QPushButton::clicked, this, [=](){
        this->editButtonSlots(w);
    });

    connect(w->m_pRemoveButton, &QPushButton::clicked, this, [=](){
        this->removeButtonSlots(w);
    });

    m_pShortcutOperationListWidget->insertItem(0, pListWidgetItem);
    m_pShortcutOperationListWidget->setItemWidget(pListWidgetItem, w);
    registerWidgetItem(w, pListWidgetItem);
    emit Itemchange();
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

//移除所有的widgetItem的值
void SidebarClipboardPlugin::removeHashAllWidgetItem()
{
    QHash<ClipboardWidgetEntry*, QListWidgetItem*>::const_iterator iter1 = m_pclipboardEntryItem.constBegin(); //遍历hash，方法1
    QHash<ClipboardWidgetEntry*, QListWidgetItem*>::const_iterator delIndex = iter1;
    while ((delIndex = iter1) != m_pclipboardEntryItem.constEnd()) {
        ++iter1;
        m_pclipboardEntryItem.remove(delIndex.key());
    }
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

//移除所有的Mindata数据类型
void SidebarClipboardPlugin::removeHashAllMimeData()
{
    QHash<ClipboardWidgetEntry*, const QMimeData*>::const_iterator iter1 = m_pclipbordMimeData.constBegin(); //遍历hash，方法1
    QHash<ClipboardWidgetEntry*, const QMimeData*>::const_iterator delIndex = iter1;
    while ((delIndex = iter1) != m_pclipbordMimeData.constEnd()) {
        const QMimeData* userInfo = (const QMimeData*)delIndex.value();
        if (userInfo != NULL)
        {
            delete userInfo;
            userInfo = NULL;
        }
        ++iter1;
        m_pclipbordMimeData.remove(delIndex.key());
    }
    return;
}

//注册条目中的lable与条目中的原始字符串文本相对应关系
void SidebarClipboardPlugin::registerLabelText(ClipboardWidgetEntry*key, QString value)
{
    if (nullptr == key || nullptr == value) {
        qWarning() << "QLabel *key," << key << "QString *value值有问题"  << value;
        return;
    }
    if (m_pLabelText.value(key) != nullptr) {
        qWarning() << "注册：value已存在";
        return;
    }
    m_pLabelText.insert(key, value);
    return;
}

//获取Label中的原始文本
QString SidebarClipboardPlugin::getLabelText(ClipboardWidgetEntry *key)
{
    if (key == nullptr) {
        qWarning() << "QLabel *key为空" << key;
        return nullptr;
    }
    return m_pLabelText.value(key);
}

//删除label中保存在hash表中的原始文本
void SidebarClipboardPlugin::removeLabelText(ClipboardWidgetEntry *key)
{
    if (nullptr == key) {
        qWarning() << "删除：QLabel *key 为空";
        return;
    }
    m_pLabelText.remove(key);
    return;
}

//移除lable hash表中所有键值对
void SidebarClipboardPlugin::removeHashAllLabelText()
{
    QHash<ClipboardWidgetEntry*, QString>::const_iterator iter1 = m_pLabelText.constBegin(); //遍历hash，方法1
    QHash<ClipboardWidgetEntry*, QString>::const_iterator delIndex = iter1;
    while ((delIndex = iter1) != m_pLabelText.constEnd()) {
        ++iter1;
        m_pLabelText.remove(delIndex.key());
    }
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
    removeLabelText(w);

    delete w;
    w = nullptr;
    QListWidgetItem *Item = m_pShortcutOperationListWidget->takeItem(m_pShortcutOperationListWidget->row(p)); //删除Item;
    delete Item;

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
    removeLabelText(w);
    delete w; //释放掉ClipboardWidgetEntry;
    w = nullptr;
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
    QMimeData* pMimeData = (QMimeData*)getMimeData(w);
    if (nullptr == pMimeData) {
        qDebug() << "剪贴板元数据不存在";
        return;
    }
    QListWidgetItem* p_wItem = (QListWidgetItem*)getWidgetItem(w);
    QString text = getLabelText(w);
    EditWidget.m_pEditingArea->setText(text);
    int nRet = EditWidget.exec();
    if (nRet == QDialog::Accepted) {
        QFontMetrics fontMetrics(w->m_pCopyDataLabal->font());
        int fontSize = fontMetrics.width(text);
        QString formatBody = EditWidget.m_pEditingArea->toPlainText();
        if(fontSize > (200 - 70)) {
            QStringList list = formatBody.split("\n");
            if (list.size() >= 2) {
                //当有几行时，只需要截取第一行就行，在第一行后面加...
                formatBody = list.at(0);
                int oneFontSize = fontMetrics.width(formatBody);
                if (oneFontSize > (200 - 50)) {
                    formatBody = fontMetrics.elidedText(formatBody, Qt::ElideRight, 200-50);
                }
                formatBody = fontMetrics.elidedText(formatBody, Qt::ElideRight, oneFontSize - 1);
            } else {
                //说明只存在一行，在最后面加...就行
                formatBody = fontMetrics.elidedText(formatBody, Qt::ElideRight, 200 - 50);
            }
        } else {
            QStringList list = formatBody.split("\n");
            if (list.size() >= 2) {
                formatBody = list.at(0);
                int oneFontSize = fontMetrics.width(formatBody);
                formatBody = fontMetrics.elidedText(formatBody, Qt::ElideRight, oneFontSize - 1);
            }
        }
        w->m_pCopyDataLabal->setText(formatBody);
        pMimeData->setText(EditWidget.m_pEditingArea->toPlainText());

        if (EditWidget.m_pEditingArea->toPlainText() != text) {
            //当编辑后数据改变时，就需要将m_pLabelText中的value改变
            removeLabelText(w);
            registerLabelText(w, EditWidget.m_pEditingArea->toPlainText());
        }

        //获取当前条目所在位置，是不是在第一
        int row_num = m_pShortcutOperationListWidget->row(p_wItem);
        if (row_num == 0) {
            popButtonSlots(w);
        }
        qDebug() << "d当前所在的条木" << row_num;
    }
    else if (nRet == QDialog::Rejected)
    {
        qDebug() << "不需要做其余操作";
    }
}

/* 当超过限制条数时删除最后一条消息 */
void SidebarClipboardPlugin::removeLastWidgetItem()
{
    ClipboardWidgetEntry *w = (ClipboardWidgetEntry*)m_pShortcutOperationListWidget->itemWidget(m_pShortcutOperationListWidget->item(m_pShortcutOperationListWidget->count()-1));
    qDebug() << "当前条目数目" << m_pShortcutOperationListWidget->count();

    removeWidgetItem(w);
    removeMimeData(w);
    removeLabelText(w);
    delete w;
    w = nullptr;
    QListWidgetItem *tmp = m_pShortcutOperationListWidget->takeItem(m_pShortcutOperationListWidget->count()-1);
    delete tmp;
}

/* 判断在ListWidget是否存在，如果不存在则返回fasle，创建，返回true，不创建 */
bool SidebarClipboardPlugin::booleanExistWidgetItem(QString Text)
{
    int tmp = m_pShortcutOperationListWidget->count();
    for (int i = 0; i < tmp; i++) {
        ClipboardWidgetEntry *w = (ClipboardWidgetEntry*)m_pShortcutOperationListWidget->itemWidget(m_pShortcutOperationListWidget->item(i));
        QString WidgetText = getLabelText(w);
        if (WidgetText == Text) {
            if(i == 0) {
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
    qDebug() << "m_pShortcutOperationListWidget->count()" << tmp;
    for (int i = 0; i < tmp; i++) {
        ClipboardWidgetEntry *w = (ClipboardWidgetEntry*)m_pShortcutOperationListWidget->itemWidget(m_pShortcutOperationListWidget->item(0));
        qDebug() << "w-->  " << w;
        removeWidgetItem(w);
        removeMimeData(w);
        removeLabelText(w);
        delete w;
        QListWidgetItem *tmp = m_pShortcutOperationListWidget->takeItem(0);
        delete tmp;
    }
    emit Itemchange();
}

/* 搜索 槽函数 */
void SidebarClipboardPlugin::searchClipboardLableTextSlots(QString Text)
{
    if (Text == "") {
        return;
    }
    qDebug() << "Text" << Text;
    QHash<ClipboardWidgetEntry*, QString>::const_iterator iter1 = m_pLabelText.constBegin();
    while (iter1 != m_pLabelText.constEnd()) {
        if (iter1.value().contains(Text, Qt::CaseSensitive)) {
            ClipboardWidgetEntry *p = iter1.key();
            ++iter1;
            popButtonSlots(p);
        } else {
//            iter1.key()->hide();
            ++iter1;
        }
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
