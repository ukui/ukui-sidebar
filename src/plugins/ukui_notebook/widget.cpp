/*
* Copyright (C) 2020 Tianjin KYLIN Information Technology Co., Ltd.
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

#include "widget.h"
#include "ui_widget.h"
#include "listViewModeDelegate.h"
#include "iconviewmodedelegate.h"
#include "edit_page.h"
#include "headerbar.h"
#include "customStyle.h"

#define FIRST_LINE_MAX 80
int sink = 0;
extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
  , m_autoSaveTimer(new QTimer(this))
  , m_settingsDatabase(Q_NULLPTR)
  , m_ukui_SearchLine(Q_NULLPTR)
  , m_newKynote(Q_NULLPTR)
  , m_trashButton(Q_NULLPTR)
  , m_countLabel(Q_NULLPTR)
  , m_sortLabel(Q_NULLPTR)
  , m_viewChangeButton(Q_NULLPTR)
  , m_noteView(Q_NULLPTR)
  , m_noteTable(Q_NULLPTR)
  , m_noteModel(new NoteModel(this))
  , m_deletedNotesModel(new NoteModel(this))
  , m_proxyModel(new QSortFilterProxyModel(this))
  , m_dbManager(Q_NULLPTR)
  , m_dbThread(Q_NULLPTR)
  , m_isContentModified(false)
  , m_isColorModified(false)
  , m_isOperationRunning(false)
{    
    translator = new QTranslator;
    QLocale locale;
    //获取系统语言环境
    if ( locale.language() == QLocale::Chinese ) {
        translator->load(QString(":/translation/ukui_notebook_zh_CN.qm"));  //选择翻译文件
        QApplication::installTranslator(translator);
    }
    ui->setupUi(this);
    setupDatabases();
    kyNoteInit();
    kyNoteConn();
    QTimer::singleShot(200,this, SLOT(InitData()));
    //setStyle(new CustomStyle("ukui-light"));
}

Widget::~Widget()
{
    for (auto it = m_editors.begin(); it!= m_editors.end();it++) {
        delete *it;
    }
    m_editors.clear();
    delete ui;
    m_dbThread->quit();
    m_dbThread->wait();
    delete m_dbThread;
}

// 初始化数据库中的数据并选中第一个便签（如果有）
void Widget::InitData()
{
    QFileInfo fi(m_settingsDatabase->fileName());
    QDir dir(fi.absolutePath());
    QString oldNoteDBPath(dir.path() + QStringLiteral("/Notes.ini"));
    QString oldTrashDBPath(dir.path() + QStringLiteral("/Trash.ini"));

    bool exist = (QFile::exists(oldNoteDBPath) || QFile::exists(oldTrashDBPath));

    if(exist){
        QProgressDialog* pd = new QProgressDialog(QStringLiteral("Migrating database, please wait."), QString(), 0, 0, this);
        pd->setCancelButton(Q_NULLPTR);
        pd->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        pd->setMinimumDuration(0);
        pd->show();

        //setButtonsAndFieldsEnabled(false);

        QFutureWatcher<void>* watcher = new QFutureWatcher<void>(this);
        connect(watcher, &QFutureWatcher<void>::finished, this, [&, pd](){
            pd->deleteLater();
            //setButtonsAndFieldsEnabled(true);
            emit requestNotesList();
        });

        QFuture<void> migration = QtConcurrent::run(this, &Widget::checkMigration);
        watcher->setFuture(migration);

    } else {
        emit requestNotesList();
    }
}

void Widget::setupListModeModel()
{
    m_proxyModel->setSourceModel(m_noteModel);          //代理真正的数据模型，对数据进行排序和过滤
    m_proxyModel->setFilterKeyColumn(0);                //此属性保存用于读取源模型内容的键的列,listview只有一列所以是0
    m_proxyModel->setFilterRole(NoteModel::NoteFullTitle);//此属性保留项目角色，该角色用于在过滤项目时查询源模型的数据
    m_proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);//

    m_noteView->setItemDelegate(new listViewModeDelegate(m_noteView));    //安装定制delegate提供编辑功能
    m_noteView->setModel(m_proxyModel);//设置view的model是proxyModel，proxyModel作为view和QAbstractListModel的桥梁
}

void Widget::setupIconModeModel()
{
    m_proxyModel->setSourceModel(m_noteModel);          //代理真正的数据模型，对数据进行排序和过滤
    m_proxyModel->setFilterKeyColumn(0);                //此属性保存用于读取源模型内容的键的列,listview只有一列所以是0
    m_proxyModel->setFilterRole(NoteModel::NoteFullTitle);//此属性保留项目角色，该角色用于在过滤项目时查询源模型的数据
    m_proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);//

    m_noteView->setItemDelegate(new iconViewModeDelegate(m_noteView));    //安装定制delegate提供编辑功能
    m_noteView->setModel(m_proxyModel);//设置view的model是proxyModel，proxyModel作为view和QAbstractListModel的桥
}

void Widget::initializeSettingsDatabase()
{
    if(m_settingsDatabase->value(QStringLiteral("version"), "NULL") == "NULL")
        m_settingsDatabase->setValue(QStringLiteral("version"), qApp->applicationVersion());

    if(m_settingsDatabase->value(QStringLiteral("windowGeometry"), "NULL") == "NULL"){
        int initWidth = 704;
        int initHeight = 590;
        QPoint center = qApp->desktop()->geometry().center();
        QRect rect(center.x() - initWidth/2, center.y() - initHeight/2, initWidth, initHeight);
        setGeometry(rect);      //设置窗口居中
        m_settingsDatabase->setValue(QStringLiteral("windowGeometry"), saveGeometry());     //保存窗口的几何形状
    }
}

void Widget::setupDatabases()
{
    //QSettings::IniFormat 将设置存储在INI文件中。从INI文件读取设置时不会保留类型信息。所有值将作为QString返回
    //QSettings::UserScope 将设置存储在特定于当前用户的位置
    m_settingsDatabase = new QSettings(QSettings::IniFormat, QSettings::UserScope,
                                       QStringLiteral("kylin-note"), QStringLiteral("Settings"), this);
    m_settingsDatabase->setFallbacksEnabled(false);     //禁用回退
    initializeSettingsDatabase();

    bool doCreate = false;
    QFileInfo fi(m_settingsDatabase->fileName());
    QDir dir(fi.absolutePath());
    bool folderCreated = dir.mkpath(QStringLiteral("."));
    if(!folderCreated)
        qFatal("ERROR: Can't create settings folder : %s", dir.absolutePath().toStdString().c_str());

    QString noteDBFilePath(dir.path() + QDir::separator() + QStringLiteral("kyNotes.db"));

    if(!QFile::exists(noteDBFilePath)){
        QFile noteDBFile(noteDBFilePath);
        if(!noteDBFile.open(QIODevice::WriteOnly))
            qFatal("ERROR : Can't create database file");

        noteDBFile.close();
        doCreate = true;
    }

    m_dbManager = new DBManager;
    m_dbThread = new QThread;
    m_dbThread->setObjectName(QStringLiteral("dbThread"));
    m_dbManager->moveToThread(m_dbThread);
    connect(m_dbThread, &QThread::started, [=](){emit requestOpenDBManager(noteDBFilePath, doCreate);});
    connect(this, &Widget::requestOpenDBManager, m_dbManager, &DBManager::onOpenDBManagerRequested);
    connect(m_dbThread, &QThread::finished, m_dbManager, &QObject::deleteLater);
    m_dbThread->start();
}

void Widget::error_throw()
{
    try
    {
        MY_THROW(ExceptionDerived,"error throw");
    }
    catch(ExceptionDerived &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void Widget::kyNoteInit()
{
    qDebug() << "kyNote init";
    sortflag = 1;//排序
    m_listflag = 1;//平铺\列表
    m_isThemeChanged = -1;//主题

    m_ukui_SearchLine = ui->SearchLine;
    m_newKynote = ui->newKynote;
    m_trashButton = ui->trashButton;
    m_countLabel = ui->label;
    m_sortLabel = ui->sort_btn;
    m_viewChangeButton = ui->viewChangeButton;

    initListMode();

    //设置鼠标追踪
    ui->widget->setMouseTracking(true);
    this->setMouseTracking(true);
    //窗口属性
    setWindowFlags(Qt::FramelessWindowHint);//开启窗口无边框
    setAttribute(Qt::WA_TranslucentBackground);//设置窗口透明显示(毛玻璃效果)
    //    setWindowOpacity(0.8);//窗口透明度
    //弹出位置
    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
    //标题
    this->setWindowTitle(tr("ukui-note"));
    //任务栏图标
    //setWindowIcon(QIcon::fromTheme("kylin-notebook",QIcon(":/image/kylin-notebook.svg")));
    setWindowIcon(QIcon::fromTheme("kylin-notebook"));
    //按钮
    set_all_btn_attribute();
    //搜索框
    searchInit();//搜索栏属性

    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.setRenderHint(QPainter::Antialiasing);
    p.drawRoundedRect(bmp.rect(),6,6);
    setMask(bmp);


    //ui->set_btn->hide();
    //m_viewChangeButton->hide();
    //ui->frame->hide();
//    ui->sort_btn->hide();

    //退出框
    m_noteExitWindow = new noteExitWindow(this);

    auto headerBar = new HeaderBar(this);
    headerBar->hide();
    //headerBar->move(650,546);
}

void Widget::kyNoteConn()
{
    qDebug() << "init connect slot";
    //主界面退出按钮
    connect(ui->pushButton_Exit,SIGNAL(clicked()),this,SLOT(exitSlot()));
    //主界面最小化按钮
    connect(ui->pushButton_Mini,SIGNAL(clicked()),this,SLOT(miniSlot()));
    //新建按钮
    connect(m_newKynote,&QPushButton::clicked, this, &Widget::newSlot);
    //删除按钮
    connect(m_trashButton, &QPushButton::clicked, this, &Widget::onTrashButtonClicked);
    // note model rows moved
//    connect(m_noteModel, &NoteModel::rowsAboutToBeMoved, m_noteView, &NoteView::rowsAboutToBeMoved);
//    connect(m_noteModel, &NoteModel::rowsMoved, m_noteView, &NoteView::rowsMoved);
    //升/降序按钮
    connect(m_sortLabel,&QPushButton::clicked,this,&Widget::sortSlot);
    //清空便签
    connect(m_menuAction,&QAction::triggered,this,&Widget::emptyNoteSLot);
    //列表平铺切换
    connect(m_viewChangeButton,&QPushButton::clicked,this,&Widget::changePageSlot);
    //搜索栏文本输入
    connect(m_ukui_SearchLine, &QLineEdit::textChanged, this, &Widget::onSearchEditTextChanged);
    //退出弹窗
    connect(m_noteExitWindow,&noteExitWindow::requestSetNoteNull,this,&Widget::setNoteNullSlot);
    //listview单击事件
    connect(m_noteView, &NoteView::pressed, this, &Widget::listClickSlot);
    //listview双击事件
    connect(m_noteView,&NoteView::doubleClicked,this,&Widget::listDoubleClickSlot);

    //connect(ui->ukui_SearchLine,&QLineEdit::textChanged,this,&Widget::lineeditChangedSlot);
    //    connect(ui->searchClearButton,&QPushButton::clicked,this,[=]{
    //        ui->ukui_SearchLine->setText("");
    //    });

    // auto save timer
    connect(m_autoSaveTimer, &QTimer::timeout, [this](){
        m_autoSaveTimer->stop();
        saveNoteToDB(m_currentSelectedNoteProxy);
    });
    //指定传递信号的方式Qt::BlockingQueuedConnection
    //这种类型类似于QueuedConnection，但是它只能应用于跨线程操作即发送者和接收者处于不同的线程中的情况
    //并且信号发送者线程会阻塞等待接收者的槽函数执行结束
    connect(this, &Widget::requestNotesList,
            m_dbManager,&DBManager::onNotesListRequested, Qt::BlockingQueuedConnection);
    connect(this, &Widget::requestCreateUpdateNote,
            m_dbManager, &DBManager::onCreateUpdateRequested, Qt::BlockingQueuedConnection);
    connect(this, &Widget::requestDeleteNote,
            m_dbManager, &DBManager::onDeleteNoteRequested);
    //    connect(this, &Widget::requestRestoreNotes,
    //            m_dbManager, &DBManager::onRestoreNotesRequested, Qt::BlockingQueuedConnection);
    //    connect(this, &Widget::requestImportNotes,
    //            m_dbManager, &DBManager::onImportNotesRequested, Qt::BlockingQueuedConnection);
    //    connect(this, &Widget::requestExportNotes,
    //            m_dbManager, &DBManager::onExportNotesRequested, Qt::BlockingQueuedConnection);
    connect(this, &Widget::requestMigrateNotes,
            m_dbManager, &DBManager::onMigrateNotesRequested, Qt::BlockingQueuedConnection);
    connect(this, &Widget::requestMigrateTrash,
            m_dbManager, &DBManager::onMigrateTrashRequested, Qt::BlockingQueuedConnection);
    connect(this, &Widget::requestForceLastRowIndexValue,
            m_dbManager, &DBManager::onForceLastRowIndexValueRequested, Qt::BlockingQueuedConnection);

    connect(m_dbManager, &DBManager::notesReceived, this, &Widget::loadNotes);
}

void Widget::checkMigration()
{
    QFileInfo fi(m_settingsDatabase->fileName());
    QDir dir(fi.absolutePath());

    QString oldNoteDBPath(dir.path() + QDir::separator() + "Notes.ini");
    if(QFile::exists(oldNoteDBPath))
        migrateNote(oldNoteDBPath);

    QString oldTrashDBPath(dir.path() + QDir::separator() + "Trash.ini");
    if(QFile::exists(oldTrashDBPath))
        //migrateTrash(oldTrashDBPath);

        emit requestForceLastRowIndexValue(m_noteCounter);
}

void Widget::migrateNote(QString notePath)
{
    QSettings notesIni(notePath, QSettings::IniFormat);
    QStringList dbKeys = notesIni.allKeys();

    m_noteCounter = notesIni.value(QStringLiteral("notesCounter"), "0").toInt();
    QList<NoteData *> noteList;

    auto it = dbKeys.begin();
    for(; it < dbKeys.end()-1; it += 3){
        QString noteName = it->split(QStringLiteral("/"))[0];
        int id = noteName.split(QStringLiteral("_"))[1].toInt();

        // sync db index with biggest notes id
        m_noteCounter = m_noteCounter < id ? id : m_noteCounter;

        NoteData* newNote = new NoteData(this);
        newNote->setId(id);

        QString createdDateDB = notesIni.value(noteName + QStringLiteral("/dateCreated"), "Error").toString();
        newNote->setCreationDateTime(QDateTime::fromString(createdDateDB, Qt::ISODate));
        QString lastEditedDateDB = notesIni.value(noteName + QStringLiteral("/dateEdited"), "Error").toString();
        newNote->setLastModificationDateTime(QDateTime::fromString(lastEditedDateDB, Qt::ISODate));
        QString contentText = notesIni.value(noteName + QStringLiteral("/content"), "Error").toString();
        newNote->setContent(contentText);
        QString firstLine = getFirstLine(contentText);
        newNote->setFullTitle(firstLine);

        noteList.append(newNote);
    }

    if(!noteList.isEmpty())
        emit requestMigrateNotes(noteList);

    QFile oldNoteDBFile(notePath);
    oldNoteDBFile.rename(QFileInfo(notePath).dir().path() + QDir::separator() + QStringLiteral("oldNotes.ini"));
}

void Widget::set_all_btn_attribute()
{
    pixmap1 = QPixmap(":/image/1x/new.png");
    pixmap2 = QPixmap(":/image/1x/close_light.png");
    pixmap3 = QPixmap(":/image/1x/mini_light.png");
    pixmap4 = QPixmap(":/image/1x/more_light.png");
    pixmap5 = QPixmap(":/image/1x/table.png");
    // pixmap6 = QPixmap(":/image/1x/ Insert_multiple_box .png");
    pixmap6 = QPixmap(":/image/1x/delete.png");
    pixmap7 = QPixmap(":/image/1x/Symbol.png");
    //pixmap8 = QPixmap(":/image/1x/array.png");
    //pixmap8 = QPixmap();
    // pixmap9 = QPixmap(":/image/1x/go-bottom-symbolic.png");
    pixmap9 = QPixmap(":/image/1x/skin.png");
    pixmap10 = QPixmap(":/image/1x/close_block.png");
    pixmap11 = QPixmap(":/image/1x/mini_block.png");
    pixmap12 = QPixmap(":/image/1x/more_block.png");
    pixmap13 = QPixmap(":/image/1x/mini2.png");
    pixmap14 = QPixmap(":/image/1x/mini3.png");
    pixmap15 = QPixmap(":/image/1x/close2.png");
    pixmap16 = QPixmap(":/image/1x/close3.png");

    m_menu = new QMenu(this);
    m_menuAction = new QAction(m_menu);
    m_menuAction->setText(tr("Empty Note"));
    //m_menu->addAction(tr("Empty Note"));
    m_menu->addAction(m_menuAction);
    ui->menuBtn->setMenu(m_menu);



    ui->newKynote->setIcon(pixmap1);
    //ui->pushButton_Exit->setIcon(pixmap10);
    //ui->pushButton_Mini->setIcon(pixmap11);
    //ui->set_btn->setIcon(pixmap12);

    //m_viewChangeButton->setIcon(pixmap5);
    m_trashButton->setIcon(pixmap6);
    m_trashButton->setIconSize(QSize(36,36));

//    ui->sort_btn->setIcon(pixmap8);
//    ui->sort_btn->setIconSize(QSize(36,36));
    ui->sort_btn->setStyleSheet("QPushButton{border-image:url(:/image/1x/sort.png);}"
                                "QPushButton:hover{border-image:url(:/image/1x/sort-hover.png);}"
                                "QPushButton:pressed{border-image:url(:/image/1x/sort-click.png);}");
    //隐藏menu下箭头
    //ui->menuBtn->setStyleSheet("QPushButton::menu-indicator{image:none}");
    ui->menuBtn->setProperty("isOptionButton", true);
    //设置是否自动凸起
    ui->menuBtn->setAutoRaise(false);
    ui->menuBtn->setIconSize(QSize(16, 16));
    ui->menuBtn->setPopupMode(QToolButton::InstantPopup);

    ui->menuBtn->setIcon(QIcon::fromTheme("open-menu-symbolic"));
    m_viewChangeButton->setIcon(QIcon::fromTheme("view-grid-symbolic"));
    ui->pushButton_Exit->setIcon(QIcon::fromTheme("window-close-symbolic"));
    ui->pushButton_Mini->setIcon(QIcon::fromTheme("window-minimize-symbolic"));

    ui->menuBtn->setProperty("useIconHighlightEffect", true);
    ui->menuBtn->setProperty("iconHighlightEffectMode", 1);
    m_viewChangeButton->setProperty("useIconHighlightEffect", true);
    m_viewChangeButton->setProperty("iconHighlightEffectMode", 1);
    ui->pushButton_Exit->setProperty("useIconHighlightEffect", true);
    ui->pushButton_Exit->setProperty("iconHighlightEffectMode", 1);
    ui->pushButton_Mini->setProperty("useIconHighlightEffect", true);
    ui->pushButton_Mini->setProperty("iconHighlightEffectMode", 1);

    //取消按钮默认主题灰色背景
    QPalette palette = ui->pushButton_Mini->palette();
    QColor ColorPlaceholderText(255,255,255,0);
    QBrush brush;
    brush.setColor(ColorPlaceholderText);
    palette.setBrush(QPalette::Button, brush);
    palette.setBrush(QPalette::ButtonText, brush);
    //palette.setColor(QPalette::Highlight, Qt::transparent); /* 取消按钮高亮 */
    ui->pushButton_Mini->setPalette(palette);
    ui->pushButton_Exit->setPalette(palette);
    ui->menuBtn->setPalette(palette);
    ui->searchBtn->setPalette(palette);

    //设置新建按钮背景文本颜色
    QPalette palette2 = ui->newKynote->palette();
    QColor ColorPlaceholderText2(61,107,229,255);
    QBrush brush2;
    brush2.setColor(ColorPlaceholderText2);
    palette2.setColor(QPalette::Button,QColor(61,107,229,255));
    palette2.setBrush(QPalette::ButtonText, QBrush(Qt::white));
//    palette2.setBrush(QPalette::Button, QBrush(Qt::blue));
//    palette2.setBrush(QPalette::ButtonText, QBrush(Qt::white));
    ui->newKynote->setPalette(palette2);


    ui->newKynote->setToolTip(tr("Create New Note"));
    m_trashButton->setToolTip(tr("Delete Selected Note"));
    m_viewChangeButton->setToolTip(tr("Switch View"));
    ui->sort_btn->setToolTip(tr("Sort"));
    ui->pushButton_Exit->setToolTip(tr("Exit"));
    ui->pushButton_Mini->setToolTip(tr("Mini"));
    ui->menuBtn->setToolTip(tr("Menu"));
}

int Widget::getListFlag() const
{
    return m_listflag;
}

void Widget::setListFlag(const int &listflag)
{
    m_listflag = listflag;
}

void Widget::initIconMode()
{
    qDebug() << "init Icon Mode";
//    m_noteView = new NoteView(this);
//    m_noteView->setMinimumSize(686,480);
    //m_noteView = static_cast<NoteView*>(ui->listView);
    m_noteView->setViewMode(QListView::IconMode);
    qDebug() << "initIconMode : current mode : " << m_noteView->viewMode();

    m_noteView->setSelectionMode(QListView::ExtendedSelection);
    m_noteView->setEditTriggers(QListView::NoEditTriggers);
    m_noteView->setResizeMode(QListView::Adjust);
    //m_noteView->setMovement(QListView::Snap);
    m_noteView->setContextMenuPolicy(Qt::CustomContextMenu);
    //m_noteView->setGridSize(QSize(227, 246));
    //m_noteView->setIconSize(QSize(227, 246));
    setupIconModeModel();
}

void Widget::initListMode()
{
    qDebug() << "init List Mode";
    m_noteView = static_cast<NoteView*>(ui->listView);
//    ui->listView->hide();
//    m_noteView = new NoteView(this);
//    m_noteView->setGeometry(9,55,686,480);
    //列表模式
    m_noteView->setViewMode(QListView::ListMode);
    qDebug() << "initListMode : current mode : " << m_noteView->viewMode();
    //禁用双击编辑
    m_noteView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //隐藏滑动条
    m_noteView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_noteView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_noteView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    //视图将一次滚动一个像素的内容
    m_noteView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_noteView->setFrameShape(QListView::NoFrame);
    //启用项的拖动
    //m_noteView->setDragEnabled(true);
    //允许用户将内部或外部项拖放到视图中
    //m_noteView->setAcceptDrops(true);
    //显示当前拖动的项将被放在什么地方
    //m_noteView->setDropIndicatorShown(true);
    setupListModeModel();
}

void Widget::deleteNote(const QModelIndex &noteIndex, bool isFromUser)
{
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    if(noteIndex.isValid()){
        // delete from model
        QModelIndex indexToBeRemoved = m_proxyModel->mapToSource(m_currentSelectedNoteProxy);
        NoteData* noteTobeRemoved = m_noteModel->removeNote(indexToBeRemoved);

        noteTobeRemoved->setDeletionDateTime(QDateTime::currentDateTime());
        qDebug() << "emit requestDeleteNote";
        //delete from sql
        emit requestDeleteNote(noteTobeRemoved);

        if(isFromUser){
            if(m_noteModel->rowCount() > 0){
                qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
                QModelIndex index = m_noteView->currentIndex();
                m_currentSelectedNoteProxy = index;
                qDebug() << m_currentSelectedNoteProxy;
            }else{
                qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
                m_currentSelectedNoteProxy = QModelIndex();
            }
        }
    }else{
        qDebug() << "Widget::deleteNote noteIndex is not valid";
    }

    m_noteView->setFocus();
}

void Widget::deleteSelectedNote()
{
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    if(!m_isOperationRunning){
        qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
        m_isOperationRunning = true;
        if(m_currentSelectedNoteProxy.isValid()){
            qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
            int noteId = m_currentSelectedNoteProxy.data(NoteModel::NoteID).toInt();
            qDebug() << noteId << m_currentSelectedNoteProxy;

            for(auto it = m_editors.begin(); it!=m_editors.end();it++)
            {
                if ((*it)->m_noteId == noteId) {
                    m_notebook = *it;
                    m_notebook->close();
                    delete m_notebook;
                    m_editors.erase(it);
                    break;
                }
            }
            qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
            qDebug() << m_currentSelectedNoteProxy;
            //--m_noteCounter;
            deleteNote(m_currentSelectedNoteProxy, true);
//            int row = m_currentSelectedNoteProxy.row();
//            m_noteView->animateRemovedRow(QModelIndex(),row, row);
        }
        m_isOperationRunning = false;
    }
}

//双击选中笔记
void Widget::selectNote(const QModelIndex &noteIndex)
{
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    //qDebug() << noteIndex;
    if(noteIndex.isValid()){
        // show the content of the pressed note in the text editor
        QModelIndex indexSrc = m_proxyModel->mapToSource(noteIndex);
        showNoteInEditor(indexSrc);

        m_currentSelectedNoteProxy = noteIndex;

        m_noteView->selectionModel()->select(m_currentSelectedNoteProxy, QItemSelectionModel::ClearAndSelect);
        m_noteView->setCurrentIndex(m_currentSelectedNoteProxy);
        m_noteView->scrollTo(m_currentSelectedNoteProxy);
    }else{
        qDebug() << "Widget::selectNote() : noteIndex is not valid";
    }
}

void Widget::showNoteInEditor(const QModelIndex &noteIndex)
{
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;

    QString content = noteIndex.data(NoteModel::NoteContent).toString();
    QDateTime dateTime = noteIndex.data(NoteModel::NoteLastModificationDateTime).toDateTime();
    //int scrollbarPos = noteIndex.data(NoteModel::NoteScrollbarPos).toInt();
    int noteColor = noteIndex.data(NoteModel::NoteColor).toInt();
    QString mdContent = noteIndex.data(NoteModel::NoteMdContent).toString();

    qDebug() << mdContent << "!!!!!!!!" << content;
    const listViewModeDelegate delegate;
    QColor m_color = delegate.intToQcolor(noteColor);
    // set text and date
    m_notebook->ui->textEdit->setText(content);
    m_notebook->m_noteHead->color_widget = QColor(m_color);
    m_notebook->m_noteHeadMenu->color_widget = QColor(m_color);
    QString _Stylesheet;
    QString _BgColor;
    _BgColor = m_color.name();
    _Stylesheet = "background-color: %1;";
    _Stylesheet = _Stylesheet.arg(_BgColor);
    m_notebook->m_noteHeadMenu->ui->pushButtonExit->setStyleSheet(_Stylesheet);
    m_notebook->m_noteHeadMenu->ui->pushButtonMenu->setStyleSheet(_Stylesheet);
    if(m_color == QColor(0,0,0))
    {qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
        QPixmap pixmap1;
        QPixmap pixmap2;
        pixmap1 = QPixmap(":/image/1x/close_light.png");
        pixmap2 = QPixmap(":/image/1x/more_light.png");
        m_notebook->m_noteHeadMenu->ui->pushButtonExit->setIcon(pixmap1);
        m_notebook->m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
        m_notebook->m_noteHeadMenu->ui->pushButtonMenu->setIcon(pixmap2);
        m_notebook->m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));
    }else
    {qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
        QPixmap pixmap1;
        QPixmap pixmap2;
        pixmap1 = QPixmap(":/image/1x/close_block.png");
        pixmap2 = QPixmap(":/image/1x/more_block.png");
        m_notebook->m_noteHeadMenu->ui->pushButtonExit->setIcon(pixmap1);
        m_notebook->m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
        m_notebook->m_noteHeadMenu->ui->pushButtonMenu->setIcon(pixmap2);
        m_notebook->m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));
    }
    m_notebook->update();

    QString noteDate = dateTime.toString(Qt::ISODate);
    QString noteDateEditor = getNoteDateEditor(noteDate);
    // set scrollbar position
    //m_textEdit->verticalScrollBar()->setValue(scrollbarPos);
}

void Widget::selectFirstNote()
{
    if(m_proxyModel->rowCount() > 0){
        QModelIndex index = m_proxyModel->index(0,0);
        m_noteView->selectionModel()->select(index, QItemSelectionModel::ClearAndSelect);
        //设置索引index所在的页面为当前页面
        m_noteView->setCurrentIndex(index);

        m_currentSelectedNoteProxy = index;
    }
}

void Widget::createNewNoteIfEmpty()
{
    if(m_proxyModel->rowCount() == 0)
        createNewNote();
}

/*
 * create a new note
 * add it to the database
 * add it to the scrollArea
 */
void Widget::createNewNote()
{
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    if(!m_isOperationRunning){
        m_isOperationRunning = true;

        m_noteView->scrollToTop();

        ++m_noteCounter;
        NoteData* tmpNote = generateNote(m_noteCounter);

        // insert the new note to NoteModel
        QModelIndex indexSrc = m_noteModel->insertNote(tmpNote, 0);

        // update the editor header date label
        QString dateTimeFromDB = tmpNote->lastModificationdateTime().toString(Qt::ISODate);
        QString dateTimeForEditor = getNoteDateEditor(dateTimeFromDB);

        // 从排序过滤器模型返回与给定 indexSrc 对应的源模型索引。
        m_currentSelectedNoteProxy = m_proxyModel->mapFromSource(indexSrc);
        saveNoteToDB(m_currentSelectedNoteProxy);

        qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
        //int row = m_currentSelectedNoteProxy.row();
        //m_noteView->animateAddedRow(QModelIndex(),row, row);

        qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
        //设置索引 m_currentSelectedNoteProxy 所在的页面为当前页面
        m_noteView->setCurrentIndex(m_currentSelectedNoteProxy);
        m_isOperationRunning = false;
    }
}

void Widget::loadNotes(QList<NoteData *> noteList, int noteCounter)
{
    //排序
    if(!noteList.isEmpty()){
        m_noteModel->addListNote(noteList);
        //Qt::AscendingOrder 升序排序
        //参见 NoteModel::sort
        m_noteModel->sort(0,Qt::AscendingOrder);
    }

    m_noteCounter = noteCounter;

    // TODO: move this from here
    createNewNoteIfEmpty();
    selectFirstNote();
    m_countLabel->setText(QObject::tr("%1 records in total").arg(m_proxyModel->rowCount()));
}

//将当前便笺保存到数据库
void Widget::saveNoteToDB(const QModelIndex& noteIndex)
{
    if(noteIndex.isValid()){
        //从排序过滤器模型返回与给定 noteIndex 对应的源模型索引。
        QModelIndex indexInSrc = m_proxyModel->mapToSource(noteIndex);
        NoteData* note = m_noteModel->getNote(indexInSrc);
        if(note != Q_NULLPTR)
            emit requestCreateUpdateNote(note);

        m_isContentModified = false;
    }else if(noteIndex.isValid() && m_isColorModified)
    {
        //从排序过滤器模型返回与给定 noteIndex 对应的源模型索引。
        QModelIndex indexInSrc = m_proxyModel->mapToSource(noteIndex);
        NoteData* note = m_noteModel->getNote(indexInSrc);
        if(note != Q_NULLPTR)
            emit requestCreateUpdateNote(note);
        m_isColorModified = false;
    }
}

QDateTime Widget::getQDateTime(QString date)
{
    QDateTime dateTime = QDateTime::fromString(date, Qt::ISODate);
    return dateTime;
}

QString Widget::getNoteDateEditor(QString dateEdited)
{
    QDateTime dateTimeEdited(getQDateTime(dateEdited));
    QLocale usLocale = QLocale::system();

    return usLocale.toString(dateTimeEdited, QStringLiteral("yyyy/MM/dd hh:mm"));
}

//初始化一个笔记
NoteData* Widget::generateNote(const int noteID)
{
    NoteData* newNote = new NoteData(this);
    newNote->setId(noteID);

    QDateTime noteDate = QDateTime::currentDateTime();
    newNote->setCreationDateTime(noteDate);
    newNote->setLastModificationDateTime(noteDate);
    newNote->setFullTitle(tr("Welcome to use Kylin Note."));
    //newNote->setNoteColor(16777215);
    newNote->setNoteColor(15169356);//15169356  //231
    newNote->m_note = nullptr;
    return newNote;
}

void Widget::moveNoteToTop()
{
    qDebug() << "movenote to top";
    // check if the current note is note on the top of the list
    // if true move the note to the top
    if(m_tmpIndex.isValid()){

        m_noteView->scrollToTop();

        //NoteData* note = m_noteModel->getNote(index);

        // move the current selected note to the top
        //当前要移动到顶端的item QSortFilterProxyModel
        QModelIndex sourceIndex = m_proxyModel->mapToSource(m_tmpIndex);
        //目前顶端的item QAbstractListModel
        QModelIndex destinationIndex = m_noteModel->index(0);
        qDebug() << "move" << destinationIndex << m_tmpIndex;
        //将 sourceIndex.row() 移动到第0行,第0行变第一行
        qDebug() << sourceIndex << destinationIndex;
        m_noteModel->moveRow(sourceIndex, sourceIndex.row(), destinationIndex, 0);

        // 更新当前 最顶端QAbstractListModel item 并添加代理
        m_tmpIndex = m_proxyModel->mapFromSource(destinationIndex);
        m_currentSelectedNoteProxy = m_tmpIndex;
        //修改当前选中
        m_noteView->setCurrentIndex(m_tmpIndex);
    }else{
        qDebug() << "Widget::moveNoteTop : m_currentSelectedNoteProxy not valid";
    }
}

QString Widget::getFirstLine(const QString& str)
{
    if(str.simplified().isEmpty())
    {
        return tr("Welcome to use Kylin Note.");
    }

    QString text = str.trimmed();
    QTextStream ts(&text);
    return ts.readLine(FIRST_LINE_MAX);
}

void Widget::findNotesContain(const QString& keyword)
{
    //将用于过滤源模型内容的固定字符串设置为给定模式
    m_proxyModel->setFilterFixedString(keyword);

    //如果匹配到不止一行
    if(m_proxyModel->rowCount() > 0){
        selectFirstNote();
    }else{
        m_currentSelectedNoteProxy = QModelIndex();
    }
}

void Widget::searchInit()
{
    // 禁用右键菜单
    ui->SearchLine->setContextMenuPolicy(Qt::NoContextMenu);
    ui->SearchLine->setPlaceholderText(tr("Search"));//设置详细输入框的提示信息
    searchAction = new QAction(ui->SearchLine);
    //searchAction->setIcon(QIcon(":/image/1x/sourch.png"));
    searchAction->setIcon(QIcon::fromTheme("system-search-symbolic"));
    ui->SearchLine->setProperty("useIconHighlightEffect", true);
    ui->SearchLine->setProperty("iconHighlightEffectMode", 1);
    ui->SearchLine->addAction(searchAction,QLineEdit::LeadingPosition);  //图片在左侧

//    ui->searchBtn->setIcon(QIcon::fromTheme("system-search-symbolic"));
//    ui->searchBtn->setProperty("useIconHighlightEffect", true);
//    ui->searchBtn->setProperty("iconHighlightEffectMode", 1);
    ui->searchBtn->hide();
//    ui->SearchLine->addAction(QIcon::fromTheme("system-search-symbolic"),QLineEdit::LeadingPosition);

    delAction = new QAction(ui->SearchLine);
    QPixmap  delActionimage = pixmap2.scaled(QSize(16,16));
    delAction->setIcon(delActionimage);

    connect(delAction, SIGNAL(triggered()), this, SLOT(delAction_del_SearchLine()));
}

void Widget::clearSearch()
{
    m_noteView->setFocusPolicy(Qt::StrongFocus);

    m_ukui_SearchLine->blockSignals(true);
    m_ukui_SearchLine->clear();
    m_ukui_SearchLine->blockSignals(false);
    m_proxyModel->setFilterFixedString(QString());
    m_ukui_SearchLine->setFocus();
    m_ukui_SearchLine->addAction(searchAction,QLineEdit::LeadingPosition);  //图片在左侧
    m_ukui_SearchLine->removeAction(delAction);

}

void Widget::black_show()
{
    this->setObjectName(QString::fromUtf8("便签本"));
//    ui->widget->setStyleSheet("QWidget{background-color: rgba(19, 20, 20,, 0.1);}");
//    ui->widget_3->setStyleSheet("QWidget{background-color: rgba(19, 20, 20,, 0.7);}");
//    ui->widget_2->setStyleSheet("QWidget{background-color: rgba();}");
//    ui->newKynote->setStyleSheet(QString::fromUtf8("background:rgba(61,107,229,1);\n"
//                                                   "color: rgb(255, 255, 255);"));
//    ui->SearchLine->setStyleSheet(QString::fromUtf8("background-color: rgb(43,49,56);\n"
//                                                    "color: rgb(255, 255, 255);\n"
//                                                    "opacity:0.08;\n"
//                                                    "border-radius:4px;"));
//    m_noteView->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255, 0);\n"
//                                                  "selection-background-color:rgba(72,72,76,1);"));
//    ui->label->setStyleSheet(QString::fromUtf8("background-color: rgb();\n"
//                                               "color: rgb(126, 126, 126);"));
//    ui->sort_btn->setStyleSheet(QString::fromUtf8("background-color: rgba(19,20,20,0);"));
//    ui->sort_2_btn->setStyleSheet(QString::fromUtf8("background-color: rgba(19,20,20,0);"));
//    m_trashButton->setStyleSheet("background-color: rgb(43,49,56);\n");
//    m_viewChangeButton->setStyleSheet("background-color: rgb(43,49,56);\n");

//    ui->set_btn->setStyleSheet("background-color: rgba(19,20,20, 0.7);color: rgba(255, 255, 255,0.8);");

//    ui->pushButton_Exit->setIcon(pixmap2);
//    ui->pushButton_Exit->setIconSize(QSize(36,36));
//    ui->pushButton_Mini->setIcon(pixmap3);
//    ui->pushButton_Mini->setIconSize(QSize(36,36));
//    ui->set_btn->setIcon(pixmap4);
//    ui->set_btn->setIconSize(QSize(36,36));


//    ui->pushButton_Exit->setStyleSheet("QPushButton{border-image: url(:/image/1x/close_light.png);background-color: rgba(19,20,20, 0);color: rgba(255, 255, 255,0.8);}"
//                                       "QPushButton:hover{border-image: url(:/image/1x/close2.png);background-color: rgba(19,20,20, 0);color: rgba(255, 255, 255,0.8);}"
//                                       "QPushButton:pressed{border-image: url(:/image/1x/close3.png);background-color: rgba(19,20,20, 0);color: rgba(255, 255, 255,0.8);}");
//    ui->pushButton_Mini->setStyleSheet("QPushButton{border-image: url(:/image/1x/mini_light.png);background-color: rgba(19,20,20, 0);color: rgba(255, 255, 255,0.8);}"
//                                       "QPushButton:hover{border-image: url(:/image/1x/mini2.png);background-color: rgba(19,20,20, 0);color: rgba(255, 255, 255,0.8);}"
//                                       "QPushButton:pressed{border-image: url(:/image/1x/mini3.png);background-color: rgba(19,20,20, 0);color: rgba(255, 255, 255,0.8);}");

    //    ui->newKynote->setStyleSheet("QPushButton{border-image: url(:/image/1x/new.png);background:rgba(61,107,229,1);color: rgb(255, 255, 255);}"
    //                                  "QPushButton:hover{border-image: url(:/image/1x/new-big.png);background:rgba(61,107,229,1);color: rgb(255, 255, 255);}"
    //                                  "QPushButton:pressed{border-image: url(:/image/1x/new-big-click.png);background:rgba(61,107,229,1);color: rgb(255, 255, 255);}");
}

void Widget::light_show()
{
    this->setObjectName(QString::fromUtf8("便签本"));
//    ui->widget->setStyleSheet("QWidget{background-color: rgba(255, 255, 255, 0.9);}");
//    ui->widget_3->setStyleSheet("QWidget{background-color: rgba();}");
//    ui->newKynote->setStyleSheet(QString::fromUtf8("background:rgba(61,107,229,1);color: rgb(255, 255, 255);\n"
//                                                   "color: rgb(255, 255, 255);"));
//    ui->SearchLine->setStyleSheet(QString::fromUtf8("background-color: rgba(198, 198, 198,0.4);\n"
//                                                    "color: rgb(0, 0, 0);\n"
//                                                    "opacity:0.08;\n"
//                                                    "border-radius:4px;"));
//    m_noteView->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
//                                                  "selection-background-color:rgba(255, 255, 255, 0);"));
//    ui->label->setStyleSheet(QString::fromUtf8("background-color: rgba();\n"
//                                               "color: rgb(43,49,56);\n"
//                                               "color: rgb(126, 126, 126);"));
//    ui->sort_btn->setStyleSheet(QString::fromUtf8("background-color: rgba(233,233,233,0); color: rgba(0,0,0,0.8);"));
//    ui->sort_2_btn->setStyleSheet(QString::fromUtf8("background-color: rgba(233,233,233,0);color: rgba(0,0,0,0.8);"));
//    m_trashButton->setStyleSheet("background-color: rgba(198, 198, 198, 0.4);color: rgba(0,0,0,0.8);");
//    m_viewChangeButton->setStyleSheet("background-color: rgb(198, 198, 198);color: rgba(0,0,0,0.8);");

//    ui->pushButton_Exit->setIcon(pixmap10);
//    ui->pushButton_Exit->setIconSize(QSize(36,36));
//    ui->pushButton_Mini->setIcon(pixmap11);
//    ui->pushButton_Mini->setIconSize(QSize(36,36));
//    ui->set_btn->setIcon(pixmap12);
//    ui->set_btn->setIconSize(QSize(36,36));

//    ui->set_btn->setStyleSheet("background-color: rgba(255, 255, 255, 0.7);color: rgba(0,0,0,0.8);");

//    ui->pushButton_Exit->setStyleSheet("QPushButton{border-image: url(:/image/1x/close_light.png);background-color: rgba(255, 255, 255, 0);color: rgba(0,0,0,0.8);}"
//                                       "QPushButton:hover{border-image: url(:/image/1x/close2.png);background-color: rgba(255, 255, 255, 0);color: rgba(0,0,0,0.8);}"
//                                       "QPushButton:pressed{border-image: url(:/image/1x/close3.png);background-color: rgba(255, 255, 255, 0);color: rgba(0,0,0,0.8);}");
//    ui->pushButton_Mini->setStyleSheet("QPushButton{border-image: url(:/image/1x/mini_light.png);background-color: rgba(255, 255, 255, 0);color: rgba(0,0,0,0.8);}"
//                                       "QPushButton:hover{border-image: url(:/image/1x/mini2.png);background-color: rgba(255, 255, 255, 0);color: rgba(0,0,0,0.8);}"
//                                       "QPushButton:pressed{border-image: url(:/image/1x/mini3.png);background-color: rgba(255, 255, 255, 0);color: rgba(0,0,0,0.8);}");


    //    ui->newKynote->setStyleSheet("QPushButton{border-image: url(:/image/1x/new.png);background:rgba(61,107,229,1);color: rgb(255, 255, 255);}"
    //                                  "QPushButton:hover{border-image: url(:/image/1x/new-big.png);background:rgba(61,107,229,1);color: rgb(255, 255, 255);}"
    //                                  "QPushButton:pressed{border-image: url(:/image/1x/new-big-click.png);background:rgba(61,107,229,1);color: rgb(255, 255, 255);}");
}

void Widget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
//    系统默认 255 、 248  深色模式 30 34
//    QStyleOption opt;
//    opt.init(this);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
//    p.setBrush(opt.palette.color(QPalette::Base));
//    //qDebug() << "paintEvent" << p.brush().color().value();
//    //p.setOpacity(0.3);
//    p.setPen(Qt::NoPen);
//    p.drawRoundedRect(opt.rect,6,6);
//    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QPainterPath rectPath;
    rectPath.addRoundedRect(this->rect().adjusted(6, 6, -6, -6), 6, 6);

    // 画一个黑底
    QPixmap pixmap(this->rect().size());
    pixmap.fill(Qt::transparent);
    QPainter pixmapPainter(&pixmap);
    pixmapPainter.setRenderHint(QPainter::Antialiasing);
    pixmapPainter.setPen(Qt::transparent);
    pixmapPainter.setBrush(Qt::black);
    pixmapPainter.drawPath(rectPath);
    pixmapPainter.end();

    // 模糊这个黑底
    QImage img = pixmap.toImage();
    qt_blurImage(img, 10, false, false);

    // 挖掉中心
    pixmap = QPixmap::fromImage(img);
    QPainter pixmapPainter2(&pixmap);
    pixmapPainter2.setRenderHint(QPainter::Antialiasing);
    pixmapPainter2.setCompositionMode(QPainter::CompositionMode_Clear);
    pixmapPainter2.setPen(Qt::transparent);
    pixmapPainter2.setBrush(Qt::transparent);
    pixmapPainter2.drawPath(rectPath);

    // 绘制阴影
    p.drawPixmap(this->rect(), pixmap, pixmap.rect());

    // 绘制一个背景
    p.save();
    p.fillPath(rectPath,palette().color(QPalette::Base));
    p.restore();
}

//********************Slots************************//

void Widget::onTextEditTextChanged(int noteId, int i)
{
    qDebug() << "receive signal textchange";
    //qDebug() << index;
    qDebug() << noteId;
    for(int count = 0; count <= m_proxyModel->rowCount();count ++)
    {
        m_tmpIndex = m_proxyModel->index(count,0);
        if(m_tmpIndex.data(NoteModel::NoteID).toInt() == noteId){
            qDebug() << m_tmpIndex.data(NoteModel::NoteID).toInt();
            break;
        }
    }
    qDebug() << m_tmpIndex;
    if(m_tmpIndex.isValid()){
        qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
        QString content = m_tmpIndex.data(NoteModel::NoteContent).toString();
        QString mdContent = m_tmpIndex.data(NoteModel::NoteMdContent).toString();

        if(m_editors[i]->ui->textEdit->toHtml().toUtf8() != content){
            qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
            //move note to the top of the list
            QModelIndex sourceIndex = m_proxyModel->mapToSource(m_tmpIndex);

            qDebug() << m_currentSelectedNoteProxy;
            if(m_tmpIndex.row() != 0){
                //m_noteView->setAnimationEnabled(false);
                moveNoteToTop();
                //m_noteView->setAnimationEnabled(true);
            }
            else if(!ui->SearchLine->text().isEmpty() && sourceIndex.row() != 0){
                m_noteView->setAnimationEnabled(false);
                moveNoteToTop();
                m_noteView->setAnimationEnabled(true);
            }

            //QModelIndex firstIndex = m_proxyModel->index(0,0);
            // Get the new data
            QString firstline = getFirstLine(m_editors[i]->ui->textEdit->toPlainText());
            QDateTime dateTime = QDateTime::currentDateTime();
            //QString noteDate = dateTime.toString(Qt::ISODate);

            // update model
            QMap<int, QVariant> dataValue;
            dataValue[NoteModel::NoteContent] = QVariant::fromValue(m_editors[i]->ui->textEdit->toHtml().toUtf8());
            dataValue[NoteModel::NoteMdContent] = QVariant::fromValue(m_editors[i]->ui->textEdit->toPlainText());
            dataValue[NoteModel::NoteFullTitle] = QVariant::fromValue(firstline);
            dataValue[NoteModel::NoteLastModificationDateTime] = QVariant::fromValue(dateTime);

            //qDebug()<<"now change text is"<< firstline << m_editors[i]->ui->textEdit->toHtml().toUtf8();
            QModelIndex currentIndex = m_proxyModel->mapToSource(m_tmpIndex);
            m_noteModel->setItemData(currentIndex, dataValue);

            m_isContentModified = true;
            //m_autoSaveTimer->start(500);
            qDebug() << "saveNotetodb" << m_tmpIndex;
            saveNoteToDB(m_tmpIndex);
        }
    }else{
        qDebug() << "Widget::onTextEditTextChanged() : index is not valid";
    }
}

void Widget::onColorChanged(const QColor &color,int noteId)
{
    qDebug() << "oncolorchanged noteid111" << noteId;
    for(int count = 0; count <= m_proxyModel->rowCount();count ++)
    {
        qDebug() << "####";
        m_tmpColorIndex = m_proxyModel->index(count,0);
        if(m_tmpColorIndex.data(NoteModel::NoteID).toInt() == noteId){
            qDebug() << "oncolorchanged noteid222" << m_tmpColorIndex.data(NoteModel::NoteID).toInt();
            break;
        }
    }
    qDebug() << "receive signal onColorChanged";
    if(m_tmpColorIndex.isValid()){
        const listViewModeDelegate delegate;
        int m_color = delegate.qcolorToInt(color);
        qDebug () << "m_color" << m_color;
        QMap<int, QVariant> dataValue;
        dataValue[NoteModel::NoteColor] = QVariant::fromValue(m_color);

        QModelIndex index = m_proxyModel->mapToSource(m_tmpColorIndex);
        m_noteModel->setItemData(index, dataValue);
        qDebug() << "m_tmpColorIndex" << m_tmpColorIndex.data(NoteModel::NoteColor).toInt();
        m_isColorModified = true;
        saveNoteToDB(m_tmpColorIndex);
    }
}

void Widget::exitSlot()
{
    //m_noteExitWindow->setWindowFlags(m_noteExitWindow->windowFlags() | Qt::WindowStaysOnTopHint);
    m_noteExitWindow->show();
    m_noteExitWindow->raise();
}

void Widget::miniSlot()
{
    this->showNormal();
    this->showMinimized();
}

void Widget::editSlot()
{
    qDebug() << "edit";
}

void Widget::newSlot()
{
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;    
    //如果搜索栏有内容,则在新建便签时清空
    if(!m_ukui_SearchLine->text().isEmpty())
    {
        clearSearch();
    }
    //新建一个笔记本
    this->createNewNote();
    m_countLabel->setText(QObject::tr("%1 records in total").arg(m_proxyModel->rowCount()));
}

void Widget::onTrashButtonClicked()
{
    m_trashButton->blockSignals(true);
    deleteSelectedNote();
    m_trashButton->blockSignals(false);

    m_countLabel->setText(QObject::tr("%1 records in total").arg(m_proxyModel->rowCount()));
}

//listview单击事件
void Widget::listClickSlot(const QModelIndex& index)
{
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    if(sender() != Q_NULLPTR){
        QModelIndex indexInProxy = m_proxyModel->index(index.row(), 0);
        //qDebug() << indexInProxy;
        if(indexInProxy.isValid()){
            m_currentSelectedNoteProxy = indexInProxy;

            m_noteView->selectionModel()->select(m_currentSelectedNoteProxy, QItemSelectionModel::ClearAndSelect);
            m_noteView->setCurrentIndex(m_currentSelectedNoteProxy);
            m_noteView->scrollTo(m_currentSelectedNoteProxy);
        }else{
            qDebug() << "Widget::selectNote() : indexInProxy is not valid";
        }
        m_noteView->setCurrentRowActive(false);
    }
}

//* 在滚动区域中单击便笺时：
//* 取消突出显示上一个选定的便笺
//* 如果在临时便笺存在时选择便笺，请删除临时便笺
//* 突出显示所选便笺
//* 将所选便笺内容加载到textedit
void Widget::listDoubleClickSlot(const QModelIndex& index)
{
    int noteId = index.data(NoteModel::NoteID).toInt();
    qDebug() << noteId << index;
    int isExistInMeditors = 0;

    for(auto it = m_editors.begin(); it!=m_editors.end();it++)
    {
        if ((*it)->m_noteId == noteId) {
            qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
            isExistInMeditors = 1;
            m_notebook = *it;
            break;
        }
    }
    if (isExistInMeditors == 0) {
        qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
        m_notebook =  new Edit_page(this,noteId);
        m_editors.push_back(m_notebook);
        m_notebook->id = m_editors.size() - 1;

        if(sender() != Q_NULLPTR){
            //获取当前选中item下标
            //QModelIndex indexInProxy = m_proxyModel->index(index.row(), 0);
            //加载便签
            selectNote(index);
            m_noteView->setCurrentRowActive(false);
        }

        connect(m_editors[m_editors.size() - 1] ,SIGNAL(texthasChanged(int,int)), this,SLOT(onTextEditTextChanged(int, int)));
        connect(m_editors[m_editors.size() - 1] ,SIGNAL(colorhasChanged(QColor,int)),this,SLOT(onColorChanged(QColor,int)));
    }
    //设置鼠标焦点
    m_notebook->ui->textEdit->setFocus();
    //移动光标至行末
    m_notebook->ui->textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    m_notebook->show();
}

void Widget::onSearchEditTextChanged(const QString& keyword)
{
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    m_searchQueue.enqueue(keyword);

    if(!m_isOperationRunning){
        qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
        m_isOperationRunning = true;

        // disable animation while searching
        m_noteView->setAnimationEnabled(false);

        while(!m_searchQueue.isEmpty()){
            qApp->processEvents();
            QString str = m_searchQueue.dequeue();
            if(str.isEmpty()){
                clearSearch();
            }else{
                m_noteView->setFocusPolicy(Qt::NoFocus);
                //过滤
                findNotesContain(str);
            }
        }

        m_noteView->setAnimationEnabled(true);
        m_isOperationRunning = false;
    }
}

void Widget::changePageSlot()
{
    if(getListFlag() != 0){
        //IconMode
        initIconMode();
        m_viewChangeButton->setIcon(QIcon::fromTheme("view-list-symbolic"));
        setListFlag(0);
    }else if(getListFlag() == 0)
    {
        //ListMode
        initListMode();
        m_viewChangeButton->setIcon(QIcon::fromTheme("view-grid-symbolic"));
        setListFlag(1);
    }
}

void Widget::sortSlot()
{
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    //排序
    //if(!noteList.isEmpty()){
    //m_noteModel->addListNote(noteList);
    //Qt::AscendingOrder 升序排序
    //参见 NoteModel::sort
    if(m_proxyModel->rowCount())
    {
        if(sortflag)
        {
            m_noteModel->sort(0,Qt::DescendingOrder);
            sortflag = 0;

        }else
        {
            m_noteModel->sort(0,Qt::AscendingOrder);
            sortflag = 1;
        }
    }
}

void Widget::emptyNoteSLot()
{
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    while(m_currentSelectedNoteProxy.isValid())
    {
        deleteSelectedNote();
    }
    m_countLabel->setText(QObject::tr("%1 records in total").arg(m_proxyModel->rowCount()));
}

void Widget::delAction_del_SearchLine()
{
    ui->SearchLine->setText("");
}

void Widget::on_SearchLine_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    if(ui->SearchLine->text().isEmpty()){
        ui->SearchLine->addAction(searchAction,QLineEdit::LeadingPosition);  //图片在左侧
        ui->SearchLine->removeAction(delAction);
    }
    else{
        ui->SearchLine->removeAction(searchAction);
        ui->SearchLine->addAction(delAction,QLineEdit::TrailingPosition);  //图片在右侧
    }
}

void Widget::setNoteNullSlot()
{
    //qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    for (int i = 0; i < m_proxyModel->rowCount(); i++){
        QModelIndex index = m_proxyModel->index(i,0);
        NoteData* note = m_noteModel->getNote(index);
        note->m_note = nullptr;
    }
}
