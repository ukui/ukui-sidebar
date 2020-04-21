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
#include "widget.h"
#include "ui_widget.h"
#include "notewidgetdelegate.h"
#include "edit_page.h"

#define FIRST_LINE_MAX 80
int sink = 0;
int single = 0;

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
  , m_noteView(Q_NULLPTR)
  , m_noteModel(new NoteModel(this))
  , m_deletedNotesModel(new NoteModel(this))
  , m_proxyModel(new QSortFilterProxyModel(this))
  , m_dbManager(Q_NULLPTR)
  , m_dbThread(Q_NULLPTR)
  , m_isContentModified(false)
  , m_isColorModified(false)
  , m_isTemp(false)
  , m_isOperationRunning(false)
{    
    ui->setupUi(this);
    setupDatabases();
    setupModelView();
    kyNoteInit();
    kyNoteConn();
    QTimer::singleShot(200,this, SLOT(InitData()));
    black_show();
}

Widget::~Widget()
{
    for (auto it = m_editors.begin(); it!= m_editors.end();it++) {
        delete *it;
        qDebug()<<"aa-----------------------";
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

    // Check if it is running with an argument (ex. hide)
//    if (qApp->arguments().contains(QStringLiteral("--autostart"))) {
//        setMainWindowVisibility(false);
//    }
}

void Widget::setupModelView()
{
    m_noteView = static_cast<NoteView*>(ui->listView);
    m_proxyModel->setSourceModel(m_noteModel);          //代理真正的数据模型，对数据进行排序和过滤
    m_proxyModel->setFilterKeyColumn(0);                //此属性保存用于读取源模型内容的键的列,listview只有一列所以是0
    m_proxyModel->setFilterRole(NoteModel::NoteFullTitle);//此属性保留项目角色，该角色用于在过滤项目时查询源模型的数据
    m_proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);//

    m_noteView->setItemDelegate(new NoteWidgetDelegate(m_noteView));    //安装定制delegate提供编辑功能
    m_noteView->setModel(m_proxyModel);//设置view的model是proxyModel，proxyModel作为view和QAbstractListModel的桥梁
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
    sortflag = 1;//排序
    listflag = 1;//平铺\列表
    dack_wight_flag = -1;//主题

    m_ukui_SearchLine = ui->SearchLine;
    m_newKynote = ui->newKynote;
    m_trashButton = ui->add_more_btn;
    m_countLabel = ui->label;
    m_sortLabel = ui->sort_btn;

    //禁用双击编辑
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //隐藏滑动条
    ui->listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //窗口属性
    setWindowFlags(Qt::FramelessWindowHint);//开启窗口无边框
//    setWindowOpacity(0.8);//窗口透明度
    //弹出位置
    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
    //标题
    this->setWindowTitle(tr("ukui-note"));
    //任务栏图标
    setWindowIcon(QIcon(":/image/kylin-notebook.svg"));
    //按钮
    set_all_btn_attribute();
    //搜索框
    ui->SearchLine->setPlaceholderText(tr("Search"));//设置详细输入框的提示信息
    searchInit();//搜索栏属性

    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.setRenderHint(QPainter::Antialiasing);
    p.drawRoundedRect(bmp.rect(),6,6);
    setMask(bmp);

    ui->tableView->hide();
    ui->set_btn->hide();
    ui->change_page_btn->hide();
    ui->add_more_btn->move(575, 0);
    ui->frame->hide();
    setAttribute(Qt::WA_TranslucentBackground);
    //退出框
    tuichu = new tanchuang(this);
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
    //升/降序按钮
    connect(m_sortLabel,&QPushButton::clicked,this,&Widget::sortSlot);
    //搜索栏文本输入
    connect(m_ukui_SearchLine, &QLineEdit::textChanged, this, &Widget::onSearchEditTextChanged);
    //listview单击事件
    connect(m_noteView, &NoteView::pressed, this, &Widget::listClickSlot);
    //listview双击事件
    connect(m_noteView,&NoteView::doubleClicked,this,&Widget::listDoubleClickSlot);
    // noteView viewport pressed
    connect(m_noteView, &NoteView::viewportPressed, this, [this](){
        qDebug() << "receive signal viewportPressed";
        if(m_isTemp && m_proxyModel->rowCount() > 1){
            QModelIndex indexInProxy = m_proxyModel->index(1, 0);
            selectNote(indexInProxy);
        }else if(m_isTemp && m_proxyModel->rowCount() == 1){
            QModelIndex indexInProxy = m_proxyModel->index(0, 0);
            deleteNote(indexInProxy, false);
        }
    });
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
    pixmap8 = QPixmap(":/image/1x/array.png");
   // pixmap9 = QPixmap(":/image/1x/go-bottom-symbolic.png");
    pixmap9 = QPixmap(":/image/1x/skin.png");
    pixmap10 = QPixmap(":/image/1x/close_block.png");
    pixmap11 = QPixmap(":/image/1x/mini_block.png");
    pixmap12 = QPixmap(":/image/1x/more_block.png");
    pixmap13 = QPixmap(":/image/1x/mini2.png");
    pixmap14 = QPixmap(":/image/1x/mini3.png");
    pixmap15 = QPixmap(":/image/1x/close2.png");
    pixmap16 = QPixmap(":/image/1x/close3.png");



    ui->newKynote->setIcon(pixmap1);
    ui->pushButton_Exit->setIcon(pixmap10);
    ui->pushButton_Mini->setIcon(pixmap11);
    ui->set_btn->setIcon(pixmap12);

    ui->change_page_btn->setIcon(pixmap5);
    ui->add_more_btn->setIcon(pixmap6);
    ui->add_more_btn->setIconSize(QSize(36,36));

    ui->sort_btn->setIcon(pixmap8);
    ui->sort_btn->setIconSize(QSize(36,36));
    ui->sort_2_btn->setIcon(pixmap9);
    ui->sort_2_btn->setIconSize(QSize(36,36));

    ui->newKynote->setToolTip(tr("Create New Note"));
    ui->add_more_btn->setToolTip(tr("Delete Selected Note"));
    ui->sort_btn->setToolTip(tr("Sort"));
    ui->sort_2_btn->setToolTip(tr("Switching Themes"));
    ui->pushButton_Exit->setToolTip(tr("Exit"));
    ui->pushButton_Mini->setToolTip(tr("Mini"));
}

void Widget::deleteNote(const QModelIndex &noteIndex, bool isFromUser)
{
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    if(noteIndex.isValid()){
        // delete from model
        QModelIndex indexToBeRemoved = m_proxyModel->mapToSource(m_currentSelectedNoteProxy);
        NoteData* noteTobeRemoved = m_noteModel->removeNote(indexToBeRemoved);

        if(m_isTemp){
            m_isTemp = false;
            --m_noteCounter;
        }else{
            noteTobeRemoved->setDeletionDateTime(QDateTime::currentDateTime());
            qDebug() << "emit requestDeleteNote";
            //delete from sql
            emit requestDeleteNote(noteTobeRemoved);
        }

        if(isFromUser){
            if(m_noteModel->rowCount() > 0){
                QModelIndex index = m_noteView->currentIndex();
                m_currentSelectedNoteProxy = index;
            }else{
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
        m_isOperationRunning = true;
        if(m_currentSelectedNoteProxy.isValid()){
            qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
            qDebug() << m_currentSelectedNoteProxy;
            deleteNote(m_currentSelectedNoteProxy, true);
        }
        m_isOperationRunning = false;
    }
}

//双击选中笔记
void Widget::selectNote(const QModelIndex &noteIndex)
{
    QModelIndex indexSrc = m_proxyModel->mapToSource(noteIndex);
    showNoteInEditor(indexSrc);
    //m_currentSelectedNoteProxy = noteIndex;
    qDebug() << "selectNote" <<m_currentSelectedNoteProxy;
    return;
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    qDebug() << noteIndex;
    if(noteIndex.isValid()){
        // save the position of text edit scrollbar
//        if(!m_isTemp && m_currentSelectedNoteProxy.isValid()){
//            int pos = m_textEdit->verticalScrollBar()->value();
//            QModelIndex indexSrc = m_proxyModel->mapToSource(m_currentSelectedNoteProxy);
//            m_noteModel->setData(indexSrc, QVariant::fromValue(pos), NoteModel::NoteScrollbarPos);
//        }

        // show the content of the pressed note in the text editor
        showNoteInEditor(noteIndex);

//        if(m_isTemp && noteIndex.row() != (m_proxyModel->rowCount() - 1)){
//            // delete the unmodified new note
//            // deleteNote(m_currentSelectedNoteProxy, false);
//            // m_currentSelectedNoteProxy = m_proxyModel->index(noteIndex.row()-1, 0);
//        }
        //else{
        m_currentSelectedNoteProxy = noteIndex;
       // }

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
    const NoteWidgetDelegate delegate;
    QColor m_color = delegate.intToQcolor(noteColor);
    // set text and date
    m_notebook->ui->textEdit->setText(content);
    m_notebook->caitou->color_widget = QColor(m_color);
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
    qDebug() << m_isOperationRunning;
    if(!m_isOperationRunning){
        m_isOperationRunning = true;

        m_noteView->scrollToTop();

        if(!m_isTemp){
            ++m_noteCounter;
            NoteData* tmpNote = generateNote(m_noteCounter);
            m_isTemp = true;

            // insert the new note to NoteModel
            QModelIndex indexSrc = m_noteModel->insertNote(tmpNote, m_noteCounter-1);

            // update the editor header date label
            QString dateTimeFromDB = tmpNote->lastModificationdateTime().toString(Qt::ISODate);
            QString dateTimeForEditor = getNoteDateEditor(dateTimeFromDB);

            // 从排序过滤器模型返回与给定 indexSrc 对应的源模型索引。
            m_currentSelectedNoteProxy = m_proxyModel->mapFromSource(indexSrc);

        }else{
            qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
            int row = m_currentSelectedNoteProxy.row();
            m_noteView->animateAddedRow(QModelIndex(),row, row);
        }
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
{   //如果实例变量 noteIndex 是个有效对象 &&
    if(noteIndex.isValid() && m_isContentModified){
        //从排序过滤器模型返回与给定 noteIndex 对应的源模型索引。
        //QModelIndex indexInSrc = m_proxyModel->mapToSource(noteIndex);
        NoteData* note = m_noteModel->getNote(noteIndex);
        if(note != Q_NULLPTR)
            emit requestCreateUpdateNote(note);

        m_isContentModified = false;
    }else if(noteIndex.isValid() && m_isColorModified)
    {
        //从排序过滤器模型返回与给定 noteIndex 对应的源模型索引。
        //QModelIndex indexInSrc = m_proxyModel->mapToSource(noteIndex);
        NoteData* note = m_noteModel->getNote(noteIndex);
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
    newNote->setFullTitle(QStringLiteral("New Note"));

    return newNote;
}

void Widget::moveNoteToTop()
{
    // check if the current note is note on the top of the list
    // if true move the note to the top
    if(m_currentSelectedNoteProxy.isValid()){

        m_noteView->scrollToTop();

        // move the current selected note to the top
        //当前要移动到顶端的item QSortFilterProxyModel
        QModelIndex sourceIndex = m_proxyModel->mapToSource(m_currentSelectedNoteProxy);

        //目前顶端的item QAbstractListModel
        QModelIndex destinationIndex = m_noteModel->index(0);

        //将 sourceIndex.row() 移动到第0行,第0行变第一行
        m_noteModel->moveRow(sourceIndex, sourceIndex.row(), destinationIndex, 0);

        // 更新当前 最顶端QAbstractListModel item 并添加代理
        m_currentSelectedNoteProxy = m_proxyModel->mapFromSource(destinationIndex);

        //修改当前选中
        m_noteView->setCurrentIndex(m_currentSelectedNoteProxy);
    }else{
        qDebug() << "Widget::moveNoteTop : m_currentSelectedNoteProxy not valid";
    }
}

QString Widget::getFirstLine(const QString& str)
{
    if(str.simplified().isEmpty())
        return "New Note";

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
    searchAction = new QAction(ui->SearchLine);
    searchAction->setIcon(QIcon(":/image/1x/sourch.png"));
    ui->SearchLine->addAction(searchAction,QLineEdit::LeadingPosition);  //图片在左侧

    delAction = new QAction(ui->SearchLine);
   QPixmap  delActionimage =   pixmap2.scaled(QSize(16,16));
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

    //m_clearButton->hide();
    m_ukui_SearchLine->setFocus();
}

void Widget::black_show()
{
    this->setObjectName(QString::fromUtf8("便签本"));
    ui->widget->setStyleSheet("QWidget{background-color: rgba(19, 20, 20,, 0.1);}");
    ui->widget_3->setStyleSheet("QWidget{background-color: rgba(19, 20, 20,, 0.7);}");
    ui->widget_2->setStyleSheet("QWidget{background-color: rgba();}");
    ui->newKynote->setStyleSheet(QString::fromUtf8("background:rgba(61,107,229,1);\n"
                                                   "color: rgb(255, 255, 255);"));
    ui->SearchLine->setStyleSheet(QString::fromUtf8("background-color: rgb(43,49,56);\n"
                                                    "color: rgb(255, 255, 255);\n"
                                                    "opacity:0.08;\n"
                                                    "border-radius:4px;"));
    ui->listView->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255, 0);\n"
                                                  "selection-background-color:rgba(72,72,76,1);"));
    ui->label->setStyleSheet(QString::fromUtf8("background-color: rgb();\n"
                                               "color: rgb(126, 126, 126);"));
    ui->sort_btn->setStyleSheet(QString::fromUtf8("background-color: rgba(19,20,20,0);"));
    ui->sort_2_btn->setStyleSheet(QString::fromUtf8("background-color: rgba(19,20,20,0);"));
    ui->add_more_btn->setStyleSheet("background-color: rgb(43,49,56);\n");
    ui->change_page_btn->setStyleSheet("background-color: rgb(43,49,56);\n");

    ui->pushButton_Exit->setStyleSheet("background-color: rgba(19,20,20, 0);color: rgba(255, 255, 255,0.8);");
    ui->pushButton_Mini->setStyleSheet("background-color: rgba(19,20,20, 0);color: rgba(255, 255, 255,0.8);");
    ui->set_btn->setStyleSheet("background-color: rgba(19,20,20, 0.7);color: rgba(255, 255, 255,0.8);");

    ui->pushButton_Exit->setIcon(pixmap2);
    ui->pushButton_Exit->setIconSize(QSize(36,36));
    ui->pushButton_Mini->setIcon(pixmap3);
    ui->pushButton_Mini->setIconSize(QSize(36,36));
    ui->set_btn->setIcon(pixmap4);
    ui->set_btn->setIconSize(QSize(36,36));


    ui->pushButton_Exit->setStyleSheet("QPushButton{border-image: url(:/image/1x/close_light.png);background-color: rgba(19,20,20, 0);color: rgba(255, 255, 255,0.8);}"
                  "QPushButton:hover{border-image: url(:/image/1x/close2.png);background-color: rgba(19,20,20, 0);color: rgba(255, 255, 255,0.8);}"
                  "QPushButton:pressed{border-image: url(:/image/1x/close3.png);background-color: rgba(19,20,20, 0);color: rgba(255, 255, 255,0.8);}");
    ui->pushButton_Mini->setStyleSheet("QPushButton{border-image: url(:/image/1x/mini_light.png);background-color: rgba(19,20,20, 0);color: rgba(255, 255, 255,0.8);}"
                  "QPushButton:hover{border-image: url(:/image/1x/mini2.png);background-color: rgba(19,20,20, 0);color: rgba(255, 255, 255,0.8);}"
                  "QPushButton:pressed{border-image: url(:/image/1x/mini3.png);background-color: rgba(19,20,20, 0);color: rgba(255, 255, 255,0.8);}");

//    ui->newKynote->setStyleSheet("QPushButton{border-image: url(:/image/1x/new.png);background:rgba(61,107,229,1);color: rgb(255, 255, 255);}"
//                                  "QPushButton:hover{border-image: url(:/image/1x/new-big.png);background:rgba(61,107,229,1);color: rgb(255, 255, 255);}"
//                                  "QPushButton:pressed{border-image: url(:/image/1x/new-big-click.png);background:rgba(61,107,229,1);color: rgb(255, 255, 255);}");
}

void Widget::light_show()
{
    this->setObjectName(QString::fromUtf8("便签本"));
    ui->widget->setStyleSheet("QWidget{background-color: rgba(255, 255, 255, 0.9);}");
    ui->widget_3->setStyleSheet("QWidget{background-color: rgba();}");
    ui->newKynote->setStyleSheet(QString::fromUtf8("background:rgba(61,107,229,1);color: rgb(255, 255, 255);\n"
                                                   "color: rgb(255, 255, 255);"));
    ui->SearchLine->setStyleSheet(QString::fromUtf8("background-color: rgba(198, 198, 198,0.4);\n"
                                                    "color: rgb(0, 0, 0);\n"
                                                    "opacity:0.08;\n"
                                                    "border-radius:4px;"));
    ui->listView->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
                                                  "selection-background-color:rgba(255, 255, 255, 0);"));
    ui->label->setStyleSheet(QString::fromUtf8("background-color: rgba();\n"
                                               "color: rgb(43,49,56);\n"
                                               "color: rgb(126, 126, 126);"));
    ui->sort_btn->setStyleSheet(QString::fromUtf8("background-color: rgba(233,233,233,0); color: rgba(0,0,0,0.8);"));
    ui->sort_2_btn->setStyleSheet(QString::fromUtf8("background-color: rgba(233,233,233,0);color: rgba(0,0,0,0.8);"));
    ui->add_more_btn->setStyleSheet("background-color: rgba(198, 198, 198, 0.4);color: rgba(0,0,0,0.8);");
    ui->change_page_btn->setStyleSheet("background-color: rgb(198, 198, 198);color: rgba(0,0,0,0.8);");

    ui->pushButton_Exit->setIcon(pixmap10);
    ui->pushButton_Exit->setIconSize(QSize(36,36));
    ui->pushButton_Mini->setIcon(pixmap11);
    ui->pushButton_Mini->setIconSize(QSize(36,36));
    ui->set_btn->setIcon(pixmap12);
    ui->set_btn->setIconSize(QSize(36,36));

    ui->pushButton_Exit->setStyleSheet("background-color: rgba(255, 255, 255, 0);color: rgba(0,0,0,0.8);");
    ui->pushButton_Mini->setStyleSheet("background-color: rgba(255, 255, 255, 0);color: rgba(0,0,0,0.8);");
    ui->set_btn->setStyleSheet("background-color: rgba(255, 255, 255, 0.7);color: rgba(0,0,0,0.8);");

    ui->pushButton_Exit->setStyleSheet("QPushButton{border-image: url(:/image/1x/close_light.png);background-color: rgba(255, 255, 255, 0);color: rgba(0,0,0,0.8);}"
                  "QPushButton:hover{border-image: url(:/image/1x/close2.png);background-color: rgba(255, 255, 255, 0);color: rgba(0,0,0,0.8);}"
                  "QPushButton:pressed{border-image: url(:/image/1x/close3.png);background-color: rgba(255, 255, 255, 0);color: rgba(0,0,0,0.8);}");
    ui->pushButton_Mini->setStyleSheet("QPushButton{border-image: url(:/image/1x/mini_light.png);background-color: rgba(255, 255, 255, 0);color: rgba(0,0,0,0.8);}"
                  "QPushButton:hover{border-image: url(:/image/1x/mini2.png);background-color: rgba(255, 255, 255, 0);color: rgba(0,0,0,0.8);}"
                  "QPushButton:pressed{border-image: url(:/image/1x/mini3.png);background-color: rgba(255, 255, 255, 0);color: rgba(0,0,0,0.8);}");


//    ui->newKynote->setStyleSheet("QPushButton{border-image: url(:/image/1x/new.png);background:rgba(61,107,229,1);color: rgb(255, 255, 255);}"
//                                  "QPushButton:hover{border-image: url(:/image/1x/new-big.png);background:rgba(61,107,229,1);color: rgb(255, 255, 255);}"
//                                  "QPushButton:pressed{border-image: url(:/image/1x/new-big-click.png);background:rgba(61,107,229,1);color: rgb(255, 255, 255);}");


}

//********************Slots************************//

void Widget::onTextEditTextChanged(const QModelIndex &index,int i)
{
    qDebug() << "receive signal textchange";
    qDebug() << index;
    if(index.isValid()){
        QString content = index.data(NoteModel::NoteContent).toString();
        QString mdContent = index.data(NoteModel::NoteMdContent).toString();
        qDebug() << mdContent;
        if(m_editors[i]->ui->textEdit->toHtml().toUtf8() != content){
            //move note to the top of the list
            //QModelIndex sourceIndex = m_proxyModel->mapFromSource(index);
            // qDebug() << "!!!!!!!!" << sourceIndex;

            // qDebug() << sourceIndex.row();  //0
            // if(index.row() != 0){
            //moveNoteToTop();
            // }else if(!ui->SearchLine->text().isEmpty() && sourceIndex.row() != 0){
            //m_noteView->setAnimationEnabled(false);
            //moveNoteToTop();
            //m_noteView->setAnimationEnabled(true);
            // }

            // Get the new data
            QString firstline = getFirstLine(m_editors[i]->ui->textEdit->toPlainText());
            QDateTime dateTime = QDateTime::currentDateTime();
            QString noteDate = dateTime.toString(Qt::ISODate);

            // update model
            QMap<int, QVariant> dataValue;
            dataValue[NoteModel::NoteContent] = QVariant::fromValue(m_editors[i]->ui->textEdit->toHtml().toUtf8());
            dataValue[NoteModel::NoteMdContent] = QVariant::fromValue(m_editors[i]->ui->textEdit->toPlainText());
            dataValue[NoteModel::NoteFullTitle] = QVariant::fromValue(firstline);
            dataValue[NoteModel::NoteLastModificationDateTime] = QVariant::fromValue(dateTime);

            qDebug()<<"now change text is"<< firstline << m_editors[i]->ui->textEdit->toHtml().toUtf8();
            //QModelIndex index2 = m_proxyModel->mapToSource(index);
            m_noteModel->setItemData(index, dataValue);

            m_isContentModified = true;
            //m_autoSaveTimer->start(500);
            saveNoteToDB(index);
        }

        m_isTemp = false;
    }else{
        qDebug() << "Widget::onTextEditTextChanged() : index is not valid";
    }
}

void Widget::onColorChanged(const QColor &color)
{
    qDebug() << "receive signal onColorChanged";
    if(m_currentSelectedNoteProxy.isValid()){
        const NoteWidgetDelegate delegate;
        int m_color = delegate.qcolorToInt(color);
        qDebug () << "m_color" << m_color;
        QMap<int, QVariant> dataValue;
        dataValue[NoteModel::NoteColor] = QVariant::fromValue(m_color);

        QModelIndex index = m_proxyModel->mapToSource(m_currentSelectedNoteProxy);
        m_noteModel->setItemData(index, dataValue);
        qDebug() << "m_currentSelectedNoteProxy" << m_currentSelectedNoteProxy.data(NoteModel::NoteColor).toInt();
        m_isColorModified = true;
        m_autoSaveTimer->start(500);
    }
}

void Widget::exitSlot()
{

    tuichu->setWindowFlags(tuichu->windowFlags() | Qt::WindowStaysOnTopHint);
    tuichu->show();
    tuichu->raise();
}

void Widget::miniSlot()
{
    this->showMinimized();
}

void Widget::editSlot()
{
    qDebug() << "edit";
}

void Widget::newSlot()
{
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    //新建一个笔记本
    //m_notebook =  new Edit_page(this);
    //m_notebook->show();
    //m_notebook->ui->textEdit->setFocus();

    //如果搜索栏有内容,则在新建便签时清空
    if(!m_ukui_SearchLine->text().isEmpty())
    {
        clearSearch();
    }

    // save the data of the previous selected
    if(m_currentSelectedNoteProxy.isValid()
            && m_isContentModified){
        qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
        qDebug() << m_currentSelectedNoteProxy;
        saveNoteToDB(m_currentSelectedNoteProxy);
        m_isContentModified = false;
    }

    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    this->createNewNote();
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    m_countLabel->setText(QObject::tr("%1 records in total").arg(m_proxyModel->rowCount()));


   // connect(m_notebook,SIGNAL(texthasChanged()), this,SLOT(onTextEditTextChanged()));
   // connect(m_notebook,SIGNAL(colorhasChanged(QColor)),this,SLOT(onColorChanged(QColor)));
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
        qDebug() << indexInProxy;
        if(indexInProxy.isValid()){
            if(m_isTemp && indexInProxy.row() != 0){
                // delete the unmodified new note
                //deleteNote(m_currentSelectedNoteProxy, false);
                //m_currentSelectedNoteProxy = m_proxyModel->index(indexInProxy.row()-1, 0);
            }

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
    //QModelIndex  * p= const_cast<QModelIndex*>(&index);
    qDebug() << "listDoubleClickSlot(const QModelIndex& index)" << index;
    QModelIndex sourceIndex = m_proxyModel->mapToSource(index);
    qDebug() << "!!!!!!!!listDoubleClickSlot" << sourceIndex;
    m_notebook =  new Edit_page(this,sourceIndex);
    m_editors.push_back(m_notebook);
    m_notebook->id = m_editors.size() - 1;

    if(sender() != Q_NULLPTR){
        //获取当前选中item下标
        //QModelIndex indexInProxy = m_proxyModel->index(index.row(), 0);
        //加载便签
        selectNote(index);
        m_noteView->setCurrentRowActive(false);
    }

    //设置鼠标焦点
    m_notebook->ui->textEdit->setFocus();
    //移动光标至行末
    m_notebook->ui->textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    if(!single){
        m_notebook->show();
        single = 1;
    }

    connect(m_editors[m_editors.size() - 1] ,SIGNAL(texthasChanged(QModelIndex,int)), this,SLOT(onTextEditTextChanged(QModelIndex, int)));
    connect(m_notebook ,SIGNAL(colorhasChanged(QColor)),this,SLOT(onColorChanged(QColor)));
}

void Widget::onSearchEditTextChanged(const QString& keyword)
{
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    m_searchQueue.enqueue(keyword);

    if(!m_isOperationRunning){
        qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
        m_isOperationRunning = true;
        if(m_isTemp){
            qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
            m_isTemp = false;
            //--m_noteCounter;
            // prevent the line edit from emitting signal
            // while animation for deleting the new note is running
//            m_ukui_SearchLine->blockSignals(true);
//            m_currentSelectedNoteProxy = QModelIndex();
//            qDebug() << m_currentSelectedNoteProxy;
//            QModelIndex index = m_noteModel->index(0);
//            qDebug() << index;
//            m_noteModel->removeNote(index);
//            m_ukui_SearchLine->blockSignals(false);

        }

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
        if(!single){
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
}

void Widget::delAction_del_SearchLine()
{
    ui->SearchLine->setText("");
}

void Widget::on_sort_2_btn_clicked()
{
    if(dack_wight_flag)
    {

        light_show();
        dack_wight_flag = 0;
        sink = 1;
    }else{


        black_show();
        dack_wight_flag = 1;
        sink = 0;
    }
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
