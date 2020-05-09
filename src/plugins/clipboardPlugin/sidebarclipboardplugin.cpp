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

    /* 往文件类型链表中加入文件后缀类型 */
    AddfileSuffix();

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
    connect(m_pSidebarClipboard, &QClipboard::dataChanged, this, &SidebarClipboardPlugin::createWidgetEntry);

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
void SidebarClipboardPlugin::createWidgetEntry()
{
    const QMimeData *mimeData = m_pSidebarClipboard->mimeData();
    if (nullptr == mimeData) {
        qWarning() << "createWidgetEntry形参mimeData为空, 不创建";
        return;
    }
    qDebug() << "剪贴板的数据" << mimeData;
    QString text;
    QString format;
    QList<QUrl> fileUrls;
    QListWidgetItem *pListWidgetItem = new QListWidgetItem;
    OriginalDataHashValue *s_pDataHashValue = new OriginalDataHashValue;
    bool DeleteFlag = false;

    if (mimeData->hasImage()) {
        s_pDataHashValue->p_pixmap = new QPixmap((qvariant_cast<QPixmap>(mimeData->imageData())));
        format = "Image";
        if (nullptr == s_pDataHashValue->p_pixmap) {
           qWarning() << "构造数据类型有错误-->p_pixmap == nullptr";
           return;
        }
    } else if (nullptr == mimeData->urls().value(0).toString()) {
        text = mimeData->text();
        format = "Text";
    } else if(mimeData->urls().value(0).toString() != "") {
        fileUrls = mimeData->urls();
        format = "Url";
        qDebug() << "文件Url" << fileUrls;
        for (int i = 0; i < fileUrls.size(); ++i) {
            if (i == 0) {
                text += fileUrls.value(i).toString();
            } else {
                text += "\n" + fileUrls.value(i).toString();
            }
        }
    } else if(mimeData->hasHtml()) {
        qDebug() << "文本为Html";
    } else {
        qWarning() << "剪贴板数据为空";
        return;
    }

    if (text == "" && s_pDataHashValue->p_pixmap == nullptr) {
        qWarning() << "text文本为空 或者 s_pDataHashValue->p_pixmap == nullptr";
        return ;
    }

    if (format == "Text" || format == "Url") {
        /* 过滤重复文本 */
        if(booleanExistWidgetItem(text)) {
            DeleteFlag = true;
        }
    } else if (format == "Image") {
        /* 过滤重复图片 */
        if (booleanExistWidgetImagin(*s_pDataHashValue->p_pixmap)) {
            DeleteFlag = true;
        }
    }

    ClipboardWidgetEntry *w = new ClipboardWidgetEntry(format);
    w->setFixedSize(397, 42);

    if (DeleteFlag) {
        qDebug() << "此数据已存在，就是当前置顶的条数";
        delete pListWidgetItem;
        delete w;
        delete s_pDataHashValue;
        return;
    }

    /* hash插入QMimeData，保留原数据 */
    s_pDataHashValue->WidgetEntry  = w;
    s_pDataHashValue->MimeData = copyMinedata(mimeData);
    s_pDataHashValue->Clipbaordformat = format;
    if (s_pDataHashValue->Clipbaordformat == "Text") {
        s_pDataHashValue->text     = text;
    } else if (s_pDataHashValue->Clipbaordformat == "Url") {
        s_pDataHashValue->urls     = fileUrls;
        s_pDataHashValue->text     = text;
    }
    if (m_pClipboardDataHash.count() == 0) {
        s_pDataHashValue->Sequence = 0;
    } else {
        s_pDataHashValue->Sequence = iterationDataHashSearchSequence(m_pClipboardDataHash.count());
    }
    qDebug() << "hash表中的Sequence" << s_pDataHashValue->Sequence;
    registerWidgetOriginalDataHash(pListWidgetItem, s_pDataHashValue);

    // 当超过一定数目的WidgetItem数目时，删除最后一条消息
    if (m_pShortcutOperationListWidget->count() >= WIDGET_ENTRY_COUNT) {
        removeLastWidgetItem();
    }

    pListWidgetItem->setSizeHint(QSize(397,42));
    pListWidgetItem->setFlags(Qt::NoItemFlags);

    if (s_pDataHashValue->Clipbaordformat == "Text") {
        // 设置...字样
        w->m_pCopyDataLabal->setTextFormat(Qt::PlainText);
        w->m_pCopyDataLabal->setText(SetFormatBody(text, w));
    } else if (s_pDataHashValue->Clipbaordformat == "Image") {
        w->m_pCopyDataLabal->setPixmap(*s_pDataHashValue->p_pixmap);
    } else if (s_pDataHashValue->Clipbaordformat == "Url") {
        w->m_pCopyDataLabal->setTextFormat(Qt::PlainText);
        w->m_pCopyDataLabal->setText(SetFormatBody(text, w));
        if (s_pDataHashValue->urls.size() == 1) {
            //判断文件类型，根据文件类型去读取主题图标
            QIcon fileIcon(":/image/kylin-feedback.png");
            fileSuffixGetsIcon(text);
            QPixmap filePixmap = fileIcon.pixmap(QSize(34, 34));
            w->m_pCopyFileIcon->setPixmap(filePixmap);
        } else {
            //当有多个图标时，显示特定图标
            QIcon fileIcon(":/image/kylin-alarm-clock.svg");
            QPixmap filePixmap = fileIcon.pixmap(QSize(34, 34));
            w->m_pCopyFileIcon->setPixmap(filePixmap);
        }
    }
    //将按钮与槽对应上
    connectWidgetEntryButton(w);
    //插入剪贴板条码
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
            // 判断第一行是否是空行
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

/* 判断Url中当前后缀名，根据后缀名读取图标 */
QIcon SidebarClipboardPlugin::fileSuffixGetsIcon(QString Url)
{
    if (Url == nullptr) {
        qWarning() << "传入后缀名有错误， 为空";
    }
    int tmp = m_fileSuffix.size();
    QStringList UrlList = Url.split(".");
    qDebug() << "123123123" << UrlList;
    if (UrlList.size() < 2) {
        qDebug() << "此文件没有后缀";
        QString  filePath = Url.mid(7);
        QFileInfo fileinfo(filePath);
        if (fileinfo.isFile()) {
            qDebug() << "文件类型为普通文本";
            //返回其余文本图标
        } else if (fileinfo.isDir()){
            //返回文件夹的图标
            qDebug() << "文件类型为文件";
        }
        qDebug() << "FilePath ----> " << filePath;
        return QIcon(":/image/kylin-feedback.png");
    }
    int cnt;
    for(int i = 0; i < tmp; i++) {
        if (m_fileSuffix[i] == UrlList[1]) {
            cnt = i;
            break;
        }
    }

    switch (cnt) {
    case Txt:
        qDebug() << "Txt图标";
        return QIcon(":/image/kylin-feedback.png");
    case Svg:
        qDebug() << "Svg图标";
        return QIcon(":/image/kylin-feedback.png");
    case Png:
        qDebug() << "Png图标";
        return QIcon(":/image/kylin-feedback.png");
    case Bmp:
        qDebug() << "Bmp图标";
        return QIcon(":/image/kylin-feedback.png");
    case Xml:
        qDebug() << "Xml图标";
        return QIcon(":/image/kylin-feedback.png");
    case Docx:
        qDebug() << "Docx图标";
        return QIcon(":/image/kylin-feedback.png");
    case Pptx:
        qDebug() << "pptx图标";
        return QIcon(":/image/kylin-feedback.png");
    case Xlsx:
        qDebug() << "Xlsx图标";
        return QIcon(":/image/kylin-feedback.png");
    case Zip:
        qDebug() << "Zip图标";
        return QIcon(":/image/kylin-feedback.png");
    case Pdf:
        qDebug() << "Pdf图标";
        return QIcon(":/image/kylin-feedback.png");
    case Pro:
        qDebug() << "Pro图标";
        return QIcon(":/image/kylin-feedback.png");
    default:
        //读取一个默认的图标
        qDebug() << "读取一个默认的图标";
        return QIcon(":/image/kylin-feedback.png");
    }
}

/* 往链表中加入文件后缀 */
void SidebarClipboardPlugin::AddfileSuffix()
{
    m_fileSuffix << "txt" << "svg" << "png" << "bmp" << "xml" << "docx" << "pptx" << "xlsx" << "zip" << "pdf" << "pro";
    return;
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
    // 获取第一个条目 当删除为第一项时，则自动将第二项置顶
    QListWidgetItem *PopWidgetItem =  m_pShortcutOperationListWidget->item(0);
    qDebug() << "QListWidgetItem *PopWidgetItem" << PopWidgetItem;
    if (PopWidgetItem == nullptr) {
        qWarning() << "从剪贴板获取的PopWidgetItem指针为空";
        return;
    }

    OriginalDataHashValue *pOriginalData = GetOriginalDataValue(PopWidgetItem);
    auto data =  structureQmimeDate(pOriginalData);
    if (data == nullptr) {
        qWarning() << "构造Qmimedata数据有问题";
        return;
    }
    m_pSidebarClipboard->setMimeData(data);
    return;
}

/* 迭代Hash表m_pClipboardDataHash*/
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

/* 迭代Hash表查找其中的当前下标是否存在 */
int SidebarClipboardPlugin::iterationDataHashSearchSequence(int Index)
{
    QHash<QListWidgetItem*, OriginalDataHashValue*>::const_iterator iter2 = m_pClipboardDataHash.constBegin();
    int max = iter2.value()->Sequence;
    while (iter2 != m_pClipboardDataHash.constEnd()) {
        if (iter2.value()->Sequence > max) {
            qDebug() << "iter2.value()->Sequence" << iter2.value()->Sequence;
            max = iter2.value()->Sequence;
        }
        ++iter2;
    }
    qDebug() << "没有找到当前的下标，返回当前下标" << max + 1;
    return max + 1;
}

/* 置顶槽函数 */
void SidebarClipboardPlugin::popButtonSlots(ClipboardWidgetEntry *w)
{
    if (w == nullptr) {
        qWarning() << "置顶槽函数ClipboardWidgetEntry *w 为空";
        return;
    }
    QListWidgetItem *Item = iterationClipboardDataHash(w);
    // 构造QMimeData数据
    auto data= structureQmimeDate(GetOriginalDataValue(Item));

    removeOriginalDataHash(Item); //移除Hash表中的原始数据
    QListWidgetItem *deleteItem = m_pShortcutOperationListWidget->takeItem(m_pShortcutOperationListWidget->row(Item)); //删除Item;
    delete deleteItem;
    m_pSidebarClipboard->setMimeData(data); //将新的数据set剪贴板中去
    return;
}

/* 构造QMimeData数据 */
QMimeData *SidebarClipboardPlugin::structureQmimeDate(OriginalDataHashValue *value)
{
    auto data = new QMimeData;
    bool isCut = false;
    QVariant isCutData = QVariant(isCut);
    if (value->Clipbaordformat == "Text") {
        data->setData("text/plain", isCutData.toByteArray());
        data->setText(value->text);
    } else if (value->Clipbaordformat == "Url") {
        data->setData("peony-qt/is-cut", isCutData.toByteArray());
        QList<QUrl> urls;
        QStringList uris = value->text.split("\n");
        qDebug() << "分解后Url的个数" << uris.count();
        for (auto uri : uris) {
            urls << uri;
        }
        value->urls = urls;
        data->setUrls(value->urls);
    } else if (value->Clipbaordformat == "Image") {
        QVariant ImageDate = QVariant(*(value->p_pixmap));
        data->setData("application/x-qt-image", isCutData.toByteArray());
        data->setImageData(ImageDate);
    }
    return data;
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
    // 判断当前删除的是不是第一个条目
    if (0 == tmp) {
        qDebug() << "删除当前的条目为第一个条目";
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
    OriginalDataHashValue* pOriginalData = GetOriginalDataValue(Item);
    QString text = pOriginalData->text;
    EditWidget.m_pEditingArea->setPlainText(text);

    /* 设置左右填充 */
    QTextDocument *document = EditWidget.m_pEditingArea->document();
    QTextFrame *rootFrame=document->rootFrame();
    QTextFrameFormat format;
    format.setPadding(10);
    format.setBorderStyle(QTextFrameFormat::BorderStyle_Dotted);
    rootFrame->setFrameFormat(format);

    int nRet = EditWidget.exec();
    if (nRet == QDialog::Accepted) {
        QString formatBody = SetFormatBody(EditWidget.m_pEditingArea->toPlainText(), w);  // 设置...字样
        qDebug () << "formatBody....." << formatBody;
        if (EditWidget.m_pEditingArea->toPlainText() != text) {
            //当编辑后数据改变时，就需要将m_pLabelText中的value改变
            w->m_pCopyDataLabal->setText(formatBody);
            pOriginalData->text = EditWidget.m_pEditingArea->toPlainText();
            structureQmimeDate(pOriginalData);
        }
        //获取当前条目所在位置，是不是在第一
        int row_num = m_pShortcutOperationListWidget->row(Item);
        if (row_num == 0) {
            QMimeData *data = structureQmimeDate(pOriginalData);
            m_pSidebarClipboard->setMimeData(data); //将新的数据set剪贴板中去
        }
        qDebug() << "当前所在的条木" << row_num;
    } else if (nRet == QDialog::Rejected) {
        qDebug() << "编辑框取消操作";
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
        OriginalDataHashValue *p = GetOriginalDataValue(m_pShortcutOperationListWidget->item(i));
        if (p->Clipbaordformat == "Text" || p->Clipbaordformat == "Url") {
            QString WidgetText = p->text;
            if (WidgetText == Text) {
                if(i == 0) {
                    qDebug() << "当前的数据就是置顶数据";
                    return true;
                }
                removeButtonSlots(GetOriginalDataValue(m_pShortcutOperationListWidget->item(i))->WidgetEntry);
                return false;
            }
        }
    }
    return false;
}

/* 判断图片是否在hash表中，如果存在，则删除，然后将图片重新写入到剪贴板中去 */
bool SidebarClipboardPlugin::booleanExistWidgetImagin(QPixmap Pixmap)
{
    //将从剪贴板拿到的数据转换成Bit位进行比较
    QImage clipboardImage = Pixmap.toImage();
    int Clipboard_hight = clipboardImage.height();
    int Clipboard_width = clipboardImage.width();
    unsigned char *clipboard_data = clipboardImage.bits();
    int tmp = m_pShortcutOperationListWidget->count();
    if (tmp == 0) {
        qDebug() << "当前hash表中不存在数据， 直接返回即可";
        return false;
    }
    unsigned char r1, g1, b1, r2, g2, b2;
    int j;
    for (int i = 0; i < tmp; i++) {
        OriginalDataHashValue *p = GetOriginalDataValue(m_pShortcutOperationListWidget->item(i));
        if (p->Clipbaordformat == "Image") {
            //hash表中的Pixmap和刚从剪贴板中拿到的数据进行比较
            QPixmap Hash_Pixmap = *(p->p_pixmap);
            QImage Hash_Image = Hash_Pixmap.toImage();
            if (Clipboard_hight == Hash_Image.height() && Clipboard_width == Hash_Image.width()) {
                unsigned char *Hash_data = Hash_Image.bits();
                for (j = 0; j < Clipboard_hight; j++) {
                    for (int k = 0; k < Clipboard_width; k++) {
                        r1 = *(Hash_data + 2);
                        b1 = *(Hash_data + 1);
                        g1 = *(Hash_data);
                        r2 = *(clipboard_data + 2);
                        b2 = *(clipboard_data + 1);
                        g2 = *(clipboard_data);
                        if (r1 == r2 && b1 == b2 && g1 == g2) {
                            clipboard_data += 4;
                            Hash_data += 4;
                        } else {
                            return false;   //比对图片像素点不相等直接返回false
                        }
                    }
                }
                if (j == Clipboard_hight) {
                    //说明图片已经对比完成，且图片存在
                    if (i == 0) {
                        return true; //当前数据就是第一条数据， 不需要做其余处理，直接清理内存，退出；
                    }
                    /* 说明已存在此图片但是需要将该放置在第一个位置上去，同时写入剪贴板当中 */
                    qDebug() << "说明已存在此图片但是需要将该放置在第一个位置上去，同时写入剪贴板当中";
                    removeButtonSlots(GetOriginalDataValue(m_pShortcutOperationListWidget->item(i))->WidgetEntry);
                    return false;
                }
            }
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
            ClipboardWidgetEntry *w = new ClipboardWidgetEntry(iter2.value()->Clipbaordformat);
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
    WhetherTopFirst();
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
    } else {
        m_pSideBarClipboardLable->setVisible(true);
        m_pShortcutOperationListWidget->setVisible(false);
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
            qDebug() << "当前条目所处位置的位置-->Sequence -->" << iter1.value()->Sequence;
            if (index == iter1.value()->Sequence) {
                m_pShortcutOperationListWidget->insertItem(0, iter1.key());
                ClipboardWidgetEntry *w = new ClipboardWidgetEntry(iter1.value()->Clipbaordformat);
                w->setFixedSize(397, 42);
                connectWidgetEntryButton(w);
                QString Format = SetFormatBody(iter1.value()->text, w);
                w->m_pCopyDataLabal->setTextFormat(Qt::PlainText);
                w->m_pCopyDataLabal->setText(Format);
                iter1.value()->WidgetEntry = w;
                m_pShortcutOperationListWidget->setItemWidget(iter1.key(), w);
                IndexFlag = false;
                index++;
                qDebug() << "进入循环当前条目的下标" << index;
            }
            ++iter1;
        }
        /* 如果没有进入上面的While循环，说明此Index不存在，继续往后面走 */
        if (IndexFlag) {
            index++;
            count++;
        }
        if (index > 1000 || count > 1000) {
            qDebug() << "查找机制已经进入死循环";
            return;
        }
    }
    m_bsortEntryBool = true;
}
