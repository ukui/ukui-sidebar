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
#include "iconViewModeDelegate.h"
#include "editPage.h"
#include "customStyle.h"
#include "CloseButton/closebutton.h"
#include "utils/xatom-helper.h"

/*!
 * 系统时间
 */
#define FORMAT_SCHEMA   "org.ukui.control-center.panel.plugins"
#define TIME_FORMAT_KEY "hoursystem"

extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);

/*!
 * \brief Widget::Widget
 * \param parent
 */
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_noteExitWindow(new noteExitWindow(this, this)),
    m_emptyNotes(Q_NULLPTR),
    m_autoSaveTimer(new QTimer(this)),
    m_settingsDatabase(Q_NULLPTR),
    m_searchLine(Q_NULLPTR),
    m_newKynote(Q_NULLPTR),
    m_trashButton(Q_NULLPTR),
    m_viewChangeButton(Q_NULLPTR),
    m_noteView(Q_NULLPTR),
    m_noteTable(Q_NULLPTR),
    m_noteModel(new NoteModel(this)),
    m_deletedNotesModel(new NoteModel(this)),
    m_proxyModel(new QSortFilterProxyModel(this)),
    m_dbManager(Q_NULLPTR),
    m_dbThread(Q_NULLPTR),
    m_isContentModified(false),
    m_isColorModified(false),
    m_isOperationRunning(false),
    mousePressed(false)
{
    translator = new QTranslator;
    if (translator->load(QLocale(), QLatin1String("ukui-notebook"), QLatin1String("_"),
                         QLatin1String("/usr/share/ukui-sidebar/ukui-notebook")))
        QApplication::installTranslator(translator);
    else
        qDebug() << "cannot load translator ukui-notebook_" << QLocale::system().name() << ".qm!";

    ui->setupUi(this);
    m_noteView = static_cast<NoteView *>(ui->listView);
    setupDatabases();
    listenToGsettings();
    kyNoteInit();
    kyNoteConn();
    QTimer::singleShot(200, this, SLOT(initData()));
}

/*!
 * \brief Widget::~Widget
 * Deconstructor of the class
 */
Widget::~Widget()
{
    for (auto it = m_editors.begin(); it != m_editors.end(); it++) {
        delete *it;
    }
    m_editors.clear();
    delete ui;
    m_dbThread->quit();
    m_dbThread->wait();
    delete m_dbThread;
}

/*!
 * \brief Widget::initData
 * Init the data from database and select the first note if there is one
 * 初始化数据库中的数据并选中第一个便签（如果有）
 */
void Widget::initData()
{
    qDebug() << "kyNote initData";

    QFileInfo fi(m_settingsDatabase->fileName());
    QDir dir(fi.absolutePath());
    QString oldNoteDBPath(dir.path() + QStringLiteral("/Notes.ini"));
    QString oldTrashDBPath(dir.path() + QStringLiteral("/Trash.ini"));

    bool exist = (QFile::exists(oldNoteDBPath) || QFile::exists(oldTrashDBPath));

    if (exist) {
        QProgressDialog *pd = new QProgressDialog(QStringLiteral(
                                                      "Migrating database, please wait."),
                                                  QString(), 0, 0, this);
        pd->setCancelButton(Q_NULLPTR);
        pd->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        pd->setMinimumDuration(0);
        pd->show();

        // setButtonsAndFieldsEnabled(false);

        QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);
        connect(watcher, &QFutureWatcher<void>::finished, this, [&, pd](){
            pd->deleteLater();
            // setButtonsAndFieldsEnabled(true);
            emit requestNotesList();
        });

        QFuture<void> migration = QtConcurrent::run(this, &Widget::checkMigration);
        watcher->setFuture(migration);
    } else {
        emit requestNotesList();
    }
}

/*!
 * \brief Widget::setupListModeModel
 *
 */
void Widget::setupListModeModel()
{
    m_proxyModel->setSourceModel(m_noteModel);          // 代理真正的数据模型，对数据进行排序和过滤
    m_proxyModel->setFilterKeyColumn(0);                // 此属性保存用于读取源模型内容的键的列,listview只有一列所以是0
    m_proxyModel->setFilterRole(NoteModel::NoteMdContent);// 此属性保留项目角色，该角色用于在过滤项目时查询源模型的数据
    m_proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);//

    m_noteView->setItemDelegate(new listViewModeDelegate(m_noteView));    // 安装定制delegate提供编辑功能
    m_noteView->setModel(m_proxyModel); // 设置view的model是proxyModel，proxyModel作为view和QAbstractListModel的桥梁
}

/*!
 * \brief Widget::setupIconModeModel
 *
 */
void Widget::setupIconModeModel()
{
    m_proxyModel->setSourceModel(m_noteModel);          // 代理真正的数据模型，对数据进行排序和过滤
    m_proxyModel->setFilterKeyColumn(0);                // 此属性保存用于读取源模型内容的键的列,listview只有一列所以是0
    m_proxyModel->setFilterRole(NoteModel::NoteMdContent);// 此属性保留项目角色，该角色用于在过滤项目时查询源模型的数据
    m_proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);//

    m_noteView->setItemDelegate(new iconViewModeDelegate(m_noteView));    // 安装定制delegate提供编辑功能
    m_noteView->setModel(m_proxyModel); // 设置view的model是proxyModel，proxyModel作为view和QAbstractListModel的桥
}

/*!
 * \brief Widget::initializeSettingsDatabase
 *
 */
void Widget::initializeSettingsDatabase()
{
    if (m_settingsDatabase->value(QStringLiteral("version"), "NULL") == "NULL")
        m_settingsDatabase->setValue(QStringLiteral("version"), qApp->applicationVersion());

    if (m_settingsDatabase->value(QStringLiteral("windowGeometry"), "NULL") == "NULL") {
        int initWidth = 704;
        int initHeight = 590;
        QPoint center = qApp->desktop()->geometry().center();
        QRect rect(center.x() - initWidth/2, center.y() - initHeight/2, initWidth, initHeight);
        setGeometry(rect);      // 设置窗口居中
        m_settingsDatabase->setValue(QStringLiteral("windowGeometry"), saveGeometry());     // 保存窗口的几何形状
    }
}

/*!
 * \brief Widget::setupDatabases
 *
 */
void Widget::setupDatabases()
{
    // QSettings::IniFormat 将设置存储在INI文件中。从INI文件读取设置时不会保留类型信息。所有值将作为QString返回
    // QSettings::UserScope 将设置存储在特定于当前用户的位置
    m_settingsDatabase = new QSettings(QSettings::IniFormat, QSettings::UserScope,
                                       QStringLiteral("kylin-note"), QStringLiteral(
                                           "Settings"), this);
    m_settingsDatabase->setFallbacksEnabled(false);     // 禁用回退
    initializeSettingsDatabase();

    bool doCreate = false;
    QFileInfo fi(m_settingsDatabase->fileName());
    QDir dir(fi.absolutePath());
    bool folderCreated = dir.mkpath(QStringLiteral("."));
    if (!folderCreated)
        qFatal("ERROR: Can't create settings folder : %s",
               dir.absolutePath().toStdString().c_str());

    QString noteDBFilePath(dir.path() + QDir::separator() + QStringLiteral("kyNotes.db"));

    if (!QFile::exists(noteDBFilePath)) {
        QFile noteDBFile(noteDBFilePath);
        if (!noteDBFile.open(QIODevice::WriteOnly))
            qFatal("ERROR : Can't create database file");

        noteDBFile.close();
        doCreate = true;
    }

    m_dbManager = new DBManager;
    m_dbThread = new QThread;
    m_dbThread->setObjectName(QStringLiteral("dbThread"));
    m_dbManager->moveToThread(m_dbThread);
    connect(m_dbThread, &QThread::started, [=](){
        emit requestOpenDBManager(noteDBFilePath, doCreate);
    });
    connect(this, &Widget::requestOpenDBManager, m_dbManager, &DBManager::onOpenDBManagerRequested);
    connect(m_dbThread, &QThread::finished, m_dbManager, &QObject::deleteLater);
    m_dbThread->start();
}

/*!
 * \brief Widget::error_throw
 *
 */
void Widget::error_throw()
{
    try{
        MY_THROW(ExceptionDerived, "error throw");
    }
    catch (ExceptionDerived &e) {
        std::cout << e.what() << std::endl;
    }
}

/*!
 * \brief Widget::kyNoteInit
 *
 */
void Widget::kyNoteInit()
{
    qDebug() << "\033[32m" << "kyNote init";
    sortflag = 1;           // 排序
    m_listflag = 1;         // 平铺\列表
    m_isThemeChanged = 0;   // ukui-default

    m_searchLine = ui->SearchLine;
    m_newKynote = ui->newKynote;
    m_trashButton = ui->trashButton;
    m_viewChangeButton = ui->viewChangeButton;

    initListMode();
    setFixedSize(712, 590);
    setMouseTracking(true);               // 设置鼠标追踪
    // 窗口属性
    // setWindowFlags(Qt::FramelessWindowHint);    //开启窗口无边框
    // setAttribute(Qt::WA_TranslucentBackground); //设置窗口透明显示(毛玻璃效果)

    // QPainterPath blurPath;
    // blurPath.addRoundedRect(rect().adjusted(0, 0, -0, -0), 6, 6);
    // setProperty("useSystemStyleBlur", true);
    // setProperty("blurRegion", QRegion(blurPath.toFillPolygon().toPolygon()));//使用QPainterPath的api生成多边形Region

    // 弹出位置
    m_pSreenInfo = new adaptScreenInfo();
    move((m_pSreenInfo->m_screenWidth - this->width() + m_pSreenInfo->m_nScreen_x)/2,
         (m_pSreenInfo->m_screenHeight - this->height())/2);
    // 标题
    this->setWindowTitle(tr("Notes"));
    // 任务栏图标
    setWindowIcon(QIcon::fromTheme("kylin-notebook"));
    ui->iconLabel->setPixmap(QIcon::fromTheme("kylin-notebook").pixmap(24, 24));
    ui->titleLabel->setText(tr("Notes"));
    // 钮
    btnInit();
    // 搜索
    searchInit();

    // QBitmap bmp(this->size());
    // bmp.fill();
    // QPainter p(&bmp);
    // p.setPen(Qt::NoPen);
    // p.setBrush(Qt::black);
    // p.setRenderHint(QPainter::Antialiasing);
    // p.drawRoundedRect(bmp.rect(),6,6);
    // setMask(bmp);

    // 退出框
    m_noteExitWindow = new noteExitWindow(this, this);
    //清除便签页弹框
    m_emptyNotes = new emptyNotes(this);
}

/*!
 * \brief Widget::kyNoteConn
 *
 */
void Widget::kyNoteConn()
{
    qDebug() << "init connect slot";
    // 主界面退出按钮
    connect(ui->pushButton_Exit, SIGNAL(clicked()), this, SLOT(exitSlot()));
    // 主界面最小化按钮
    connect(ui->pushButton_Mini, SIGNAL(clicked()), this, SLOT(miniSlot()));
    // 新建按钮
    connect(m_newKynote, &QPushButton::clicked, this, &Widget::newSlot);
    // 除按钮
    connect(m_trashButton, &QPushButton::clicked, this, &Widget::onTrashButtonClicked);

    // connect(m_noteModel, &NoteModel::rowsAboutToBeMoved, m_noteView, &NoteView::rowsAboutToBeMoved);
    // connect(m_noteModel, &NoteModel::rowsMoved, m_noteView, &NoteView::rowsMoved);
    // 升/降序按钮
    // connect(m_sortLabel,&QPushButton::clicked,this,&Widget::sortSlot);
    connect(this, &Widget::switchSortTypeRequest, this, &Widget::sortSlot);
    // 清空便签
    connect(m_menuActionEmpty, &QAction::triggered, this, &Widget::trashSlot);
    connect(m_emptyNotes, &emptyNotes::requestEmptyNotes, this, &Widget::clearNoteSlot);
    // 设置界面
    // connect(m_menuActionSet,&QAction::triggered,this,&Widget::SetNoteSlot);
    // 列表平铺切换
    connect(m_viewChangeButton, &QPushButton::clicked, this, &Widget::changePageSlot);
    // 搜索栏文本输入
    connect(m_searchLine, &QLineEdit::textChanged, this, &Widget::onSearchEditTextChanged);
    // 退出弹窗
    connect(m_noteExitWindow, &noteExitWindow::requestSetNoteNull, this, &Widget::setNoteNullSlot);
    // listview单击事件
    connect(m_noteView, &NoteView::pressed, this, &Widget::listClickSlot);
    // listview双击事件
    connect(m_noteView, &NoteView::doubleClicked, this, &Widget::listDoubleClickSlot);
    connect(m_noteView, &NoteView::viewportPressed, this, [this](){
        if (m_noteModel->rowCount() > 0) {
            QModelIndex index = m_noteView->currentIndex();
            m_currentSelectedNoteProxy = index;
            m_noteView->selectionModel()->select(m_currentSelectedNoteProxy,
                                                 QItemSelectionModel::ClearAndSelect);
            m_noteView->setCurrentIndex(m_currentSelectedNoteProxy);
            m_noteView->scrollTo(m_currentSelectedNoteProxy);
        }
    });

    // auto save timer
    connect(m_autoSaveTimer, &QTimer::timeout, [this](){
        m_autoSaveTimer->stop();
        saveNoteToDB(m_currentSelectedNoteProxy);
    });
    // 指定传递信号的方式Qt::BlockingQueuedConnection
    // 这种类型类似于QueuedConnection，但是它只能应用于跨线程操作即发送者和接收者处于不同的线程中的情况
    // 并且信号发送者线程会阻塞等待接收者的槽函数执行结束
    connect(this, &Widget::requestNotesList,
            m_dbManager, &DBManager::onNotesListRequested, Qt::BlockingQueuedConnection);
    connect(this, &Widget::requestCreateUpdateNote,
            m_dbManager, &DBManager::onCreateUpdateRequested, Qt::BlockingQueuedConnection);
    connect(this, &Widget::requestDeleteNote,
            m_dbManager, &DBManager::onDeleteNoteRequested);
    connect(this, &Widget::requestClearNote,
            m_dbManager, &DBManager::permanantlyRemoveAllNotes);
    // connect(this, &Widget::requestRestoreNotes,
    // m_dbManager, &DBManager::onRestoreNotesRequested, Qt::BlockingQueuedConnection);
    // connect(this, &Widget::requestImportNotes,
    // m_dbManager, &DBManager::onImportNotesRequested, Qt::BlockingQueuedConnection);
    // connect(this, &Widget::requestExportNotes,
    // m_dbManager, &DBManager::onExportNotesRequested, Qt::BlockingQueuedConnection);
    connect(this, &Widget::requestMigrateNotes,
            m_dbManager, &DBManager::onMigrateNotesRequested, Qt::BlockingQueuedConnection);
    connect(this, &Widget::requestMigrateTrash,
            m_dbManager, &DBManager::onMigrateTrashRequested, Qt::BlockingQueuedConnection);
    connect(this, &Widget::requestForceLastRowIndexValue,
            m_dbManager, &DBManager::onForceLastRowIndexValueRequested,
            Qt::BlockingQueuedConnection);

    connect(m_dbManager, &DBManager::notesReceived, this, &Widget::loadNotes);
    // 快捷键
    new QShortcut(QKeySequence(Qt::Key_F1), this, SLOT(onF1ButtonClicked()));
}

/*!
 * \brief Widget::listenToGsettings
 *
 */
void Widget::listenToGsettings()
{
    // 监听主题改变
    const QByteArray id(THEME_QT_SCHEMA);

    if (QGSettings::isSchemaInstalled(id)) {
        QGSettings *styleSettings = new QGSettings(id);
        connect(styleSettings, &QGSettings::changed, this, [=](const QString &key){
            auto style = styleSettings->get(key).toString();
            if (key == "styleName") {
                currentTheme = styleSettings->get(MODE_QT_KEY).toString();
                if (currentTheme == "ukui-default" || currentTheme == "ukui-white"
                    || currentTheme == "ukui-light" || currentTheme == "ukui") {
                    m_isThemeChanged = 0;
                } else if (style == "ukui-dark" || currentTheme == "ukui-black") {
                    m_isThemeChanged = 1;
                }
            }
            QTimer::singleShot(500, this, [=](){
                QList<QWidget *> wid = m_searchLine->findChildren<QWidget *>();
                for (int i = 0; i < wid.count(); i++) {
                    wid.at(i)->setAttribute(Qt::WA_Hover, false);
                }
            });
        });
    }

    // 监听控制面板字体变化
    const QByteArray idd(PERSONALISE_SCHEMA);

    if (QGSettings::isSchemaInstalled(idd)) {
        QGSettings *opacitySettings = new QGSettings(idd);
        connect(opacitySettings, &QGSettings::changed, this, [=](const QString &key){
            if (key == "transparency") {
                QStringList keys = opacitySettings->keys();
                if (keys.contains("transparency")) {
                    m_transparency = opacitySettings->get("transparency").toDouble();
                }
            }
            repaint();
        });
        m_transparency = opacitySettings->get("transparency").toDouble();
    }

    // 用户手册
    QString serviceName = "com.kylinUserGuide.hotel"
                          + QString("%1%2").arg("_").arg(QString::number(getuid()));
    userGuideInterface = new QDBusInterface(serviceName,
                                            "/",
                                            "com.guide.hotel",
                                            QDBusConnection::sessionBus());
    qDebug() << "connect to kylinUserGuide" << userGuideInterface->isValid();
    if (!userGuideInterface->isValid()) {
        qDebug() << "fail to connect to kylinUserGuide";
        qDebug() << qPrintable(QDBusConnection::sessionBus().lastError().message());
        return;
    }

    // 监听时区变化
    const QByteArray iddd(FORMAT_SCHEMA);

    if (QGSettings::isSchemaInstalled(iddd)) {
        QGSettings *m_formatsettings = new QGSettings(iddd);

        connect(m_formatsettings, &QGSettings::changed, this, [=](const QString &key) {
            if (key == "hoursystem") {
                QString value = m_formatsettings->get(TIME_FORMAT_KEY).toString();
                qDebug() << "hoursystem changed" << value;
                m_noteView->viewport()->update();
            }
        });
    }
}

/*!
 * \brief Widget::checkMigration
 *
 */
void Widget::checkMigration()
{
    qDebug() << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    QFileInfo fi(m_settingsDatabase->fileName());
    QDir dir(fi.absolutePath());

    QString oldNoteDBPath(dir.path() + QDir::separator() + "Notes.ini");
    if (QFile::exists(oldNoteDBPath))
        migrateNote(oldNoteDBPath);

    QString oldTrashDBPath(dir.path() + QDir::separator() + "Trash.ini");
    if (QFile::exists(oldTrashDBPath)) {
        // migrateTrash(oldTrashDBPath);
        emit requestForceLastRowIndexValue(m_noteCounter);
    }
}

/*!
 * \brief Widget::migrateNote
 *
 */
void Widget::migrateNote(QString notePath)
{
    qDebug() << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    QSettings notesIni(notePath, QSettings::IniFormat);
    QStringList dbKeys = notesIni.allKeys();

    m_noteCounter = notesIni.value(QStringLiteral("notesCounter"), "0").toInt();
    QList<NoteData *> noteList;

    auto it = dbKeys.begin();
    for (; it < dbKeys.end() - 1; it += 3) {
        QString noteName = it->split(QStringLiteral("/"))[0];
        int id = noteName.split(QStringLiteral("_"))[1].toInt();

        // sync db index with biggest notes id
        m_noteCounter = m_noteCounter < id ? id : m_noteCounter;

        NoteData *newNote = new NoteData(this);
        newNote->setId(id);

        QString createdDateDB
            = notesIni.value(noteName + QStringLiteral("/dateCreated"), "Error").toString();
        newNote->setCreationDateTime(QDateTime::fromString(createdDateDB, Qt::ISODate));
        QString lastEditedDateDB
            = notesIni.value(noteName + QStringLiteral("/dateEdited"), "Error").toString();
        newNote->setLastModificationDateTime(QDateTime::fromString(lastEditedDateDB, Qt::ISODate));
        QString contentText
            = notesIni.value(noteName + QStringLiteral("/content"), "Error").toString();
        newNote->setContent(contentText);
        QString firstLine = getFirstLine(contentText);
        newNote->setFullTitle(firstLine);

        noteList.append(newNote);
    }

    if (!noteList.isEmpty())
        emit requestMigrateNotes(noteList);

    QFile oldNoteDBFile(notePath);
    oldNoteDBFile.rename(QFileInfo(notePath).dir().path() + QDir::separator()
                         + QStringLiteral("oldNotes.ini"));
}

/*!
 * \brief Widget::btnInit
 *
 */
void Widget::btnInit()
{
    m_menu = new QMenu(ui->menuBtn);
    m_menu->setProperty("fillIconSymbolicColor", true);

    m_menuActionEmpty = new QAction(m_menu);
    QAction *m_helpAction = new QAction(m_menu);
    QAction *m_aboutAction = new QAction(m_menu);
    // m_menuActionSet = new QAction(m_menu);

    m_helpAction->setText(tr("Help"));
    m_aboutAction->setText(tr("About"));
    m_menuActionEmpty->setText(tr("Empty Note"));
    // m_menuActionSet->setText(tr("Set Note"));

    m_menu->addAction(m_menuActionEmpty);
    m_menu->addAction(m_helpAction);
    m_menu->addAction(m_aboutAction);
    // m_menu->addAction(m_menuActionSet);
    ui->menuBtn->setMenu(m_menu);

    connect(m_helpAction, &QAction::triggered, this, [=](){
        qDebug() << "help clicked";
        userGuideInterface->call(QString("showGuide"), "ukui/ukui-notebook");
    });
    connect(m_aboutAction, &QAction::triggered, this, [=](){
        About *dialog = new About();
        dialog->exec();
    });
    // 隐藏menu下箭头
    // ui->menuBtn->setStyleSheet("QPushButton::menu-indicator{image:none}");
    ui->menuBtn->setProperty("isOptionButton", true);
    // 设置是否自动凸起
    ui->menuBtn->setAutoRaise(false);
    ui->menuBtn->setIconSize(QSize(16, 16));
    ui->menuBtn->setPopupMode(QToolButton::InstantPopup);

    m_newKynote->setIcon(QPixmap(":/image/1x/new-hover.png"));

    ui->menuBtn->setIcon(QIcon::fromTheme("open-menu-symbolic"));
    m_viewChangeButton->setIcon(QIcon::fromTheme("view-grid-symbolic"));
    m_trashButton->setIcon(QIcon::fromTheme("edit-delete-symbolic"));
    ui->pushButton_Exit->setIcon(QIcon::fromTheme("window-close-symbolic"));
    ui->pushButton_Mini->setIcon(QIcon::fromTheme("window-minimize-symbolic"));

    ui->menuBtn->setProperty("useIconHighlightEffect", true);
    ui->menuBtn->setProperty("iconHighlightEffectMode", 1);
    m_viewChangeButton->setProperty("useIconHighlightEffect", true);
    m_viewChangeButton->setProperty("iconHighlightEffectMode", 1);

    ui->pushButton_Exit->setProperty("isWindowButton", 0x2);
    ui->pushButton_Exit->setProperty("useIconHighlightEffect", 0x8);
    ui->pushButton_Exit->setFlat(true);

    ui->pushButton_Mini->setProperty("isWindowButton", 0x1);
    ui->pushButton_Mini->setProperty("useIconHighlightEffect", 0x2);
    ui->pushButton_Mini->setFlat(true);

    ui->menuBtn->setProperty("isWindowButton", 0x1);
    ui->menuBtn->setProperty("useIconHighlightEffect", 0x2);
    ui->menuBtn->setAutoRaise(true);

    m_trashButton->setProperty("useIconHighlightEffect", true);
    m_trashButton->setProperty("iconHighlightEffectMode", 1);

    // 取消按钮默认主题灰色背景
    QPalette palette = ui->pushButton_Mini->palette();
    QColor ColorPlaceholderText(255, 255, 255, 0);
    QBrush brush;
    brush.setColor(ColorPlaceholderText);
    palette.setBrush(QPalette::Button, brush);
    palette.setBrush(QPalette::ButtonText, brush);
    // palette.setColor(QPalette::Highlight, Qt::transparent); /* 取消按钮高亮 */
    // ui->pushButton_Mini->setPalette(palette);

    // 设置新建按钮背景文本颜色
    QPalette palette2 = m_newKynote->palette();
    QColor ColorPlaceholderText2(61, 107, 229, 255);
    QBrush brush2;
    brush2.setColor(ColorPlaceholderText2);
    palette2.setColor(QPalette::Button, QColor(61, 107, 229, 255));
    palette2.setBrush(QPalette::ButtonText, QBrush(Qt::white));
    m_newKynote->setPalette(palette2);

    m_newKynote->setToolTip(tr("Create New Note"));
    m_trashButton->setToolTip(tr("Delete Selected Note"));
    m_viewChangeButton->setToolTip(tr("Switch View"));
    ui->pushButton_Exit->setToolTip(tr("Close"));
    ui->pushButton_Mini->setToolTip(tr("Minimize"));
    ui->menuBtn->setToolTip(tr("Menu"));
}

/*!
 * \brief Widget::getListFlag
 *
 */
int Widget::getListFlag() const
{
    return m_listflag;
}

/*!
 * \brief Widget::setListFlag
 *
 */
void Widget::setListFlag(const int &listflag)
{
    m_listflag = listflag;
}

/*!
 * \brief Widget::initIconMode
 *
 */
void Widget::initIconMode()
{
    qDebug() << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    m_noteView->setViewMode(QListView::IconMode);
    m_noteView->setSelectionMode(QListView::ExtendedSelection);
    m_noteView->setEditTriggers(QListView::NoEditTriggers);
    m_noteView->setResizeMode(QListView::Adjust);
    // m_noteView->setMovement(QListView::Snap);
    m_noteView->setContextMenuPolicy(Qt::CustomContextMenu);
    // m_noteView->setGridSize(QSize(227, 246));
    // m_noteView->setIconSize(QSize(227, 246));
    setupIconModeModel();
}

/*!
 * \brief Widget::initListMode
 *
 */
void Widget::initListMode()
{
    qDebug() << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    // 列表模式
    m_noteView->setViewMode(QListView::ListMode);
    // 禁用双击编辑
    m_noteView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 隐藏滑动条
    m_noteView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_noteView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_noteView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    // 视图将一次滚动一个像素的内容
    m_noteView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_noteView->setFrameShape(QListView::NoFrame);
    // 启用项的拖动
    // m_noteView->setDragEnabled(true);
    // 允许用户将内部或外部项拖放到视图中
    // m_noteView->setAcceptDrops(true);
    // 显示当前拖动的项将被放在什么地方
    // m_noteView->setDropIndicatorShown(true);
    setupListModeModel();
}

/*!
 * \brief Widget::deleteNote
 *
 */
void Widget::deleteNote(const QModelIndex &noteIndex, bool isFromUser)
{
    qDebug() << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    if (noteIndex.isValid()) {
        // delete from model
        QModelIndex indexToBeRemoved = m_proxyModel->mapToSource(noteIndex);
        NoteData *noteTobeRemoved = m_noteModel->removeNote(indexToBeRemoved);

        noteTobeRemoved->setDeletionDateTime(QDateTime::currentDateTime());
        qDebug() << "emit requestDeleteNote";
        // delete from sql
        emit requestDeleteNote(noteTobeRemoved);
        if (isFromUser) {
            if (m_noteModel->rowCount() > 0) {
                QModelIndex index = m_noteView->currentIndex();
                m_currentSelectedNoteProxy = index;
                m_noteView->selectionModel()->select(m_currentSelectedNoteProxy,
                                                     QItemSelectionModel::ClearAndSelect);
                m_noteView->setCurrentIndex(m_currentSelectedNoteProxy);
                m_noteView->scrollTo(m_currentSelectedNoteProxy);
            } else {
                // 创建新的空模型索引 此类型的模型索引用于指示模型中的位置无效
                m_currentSelectedNoteProxy = QModelIndex();
            }
        }
    } else {
        qDebug() << "Widget::deleteNote noteIndex is not valid";
    }

    m_noteView->setFocus();
}

/*!
 * \brief Widget::deleteSelectedNote
 *
 */
void Widget::deleteSelectedNote()
{
    qDebug() << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    if (!m_isOperationRunning) {
        m_isOperationRunning = true;
        if (m_noteModel->rowCount() > 0 && m_currentSelectedNoteProxy.isValid()) {
            int noteId = m_currentSelectedNoteProxy.data(NoteModel::NoteID).toInt();
            for (auto it = m_editors.begin(); it != m_editors.end(); it++) {
                if ((*it)->m_noteId == noteId) {
                    m_notebook = *it;
                    m_notebook->close();
                    delete m_notebook;
                    m_editors.erase(it);
                    break;
                }
            }
            // --m_noteCounter;
            deleteNote(m_currentSelectedNoteProxy, true);
            // int row = m_currentSelectedNoteProxy.row();
            // m_noteView->animateRemovedRow(QModelIndex(),row, row);
        }
        m_isOperationRunning = false;
    }
}

/*!
 * \brief Widget::selectNote
 *
 */
// 双击选中笔记
void Widget::selectNote(const QModelIndex &noteIndex)
{
    qDebug() << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    if (noteIndex.isValid()) {
        // show the content of the pressed note in the text editor
        QModelIndex indexSrc = m_proxyModel->mapToSource(noteIndex);
        showNoteInEditor(indexSrc);

        m_currentSelectedNoteProxy = noteIndex;

        m_noteView->selectionModel()->select(m_currentSelectedNoteProxy,
                                             QItemSelectionModel::ClearAndSelect);
        m_noteView->setCurrentIndex(m_currentSelectedNoteProxy);
        m_noteView->scrollTo(m_currentSelectedNoteProxy);
    } else {
        qDebug() << "Widget::selectNote() : noteIndex is not valid";
    }
}

/*!
 * \brief Widget::showNoteInEditor
 *
 */
void Widget::showNoteInEditor(const QModelIndex &noteIndex)
{
    qDebug() << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    QString content = noteIndex.data(NoteModel::NoteContent).toString();
    QDateTime dateTime = noteIndex.data(NoteModel::NoteLastModificationDateTime).toDateTime();
    // int scrollbarPos = noteIndex.data(NoteModel::NoteScrollbarPos).toInt();
    int noteColor = noteIndex.data(NoteModel::NoteColor).toInt();
    // QString mdContent = noteIndex.data(NoteModel::NoteMdContent).toString();

    const listViewModeDelegate delegate;
    QColor m_color = delegate.intToQcolor(noteColor);
    // set text and date
    m_notebook->ui->textEdit->setText(content);
    m_notebook->m_noteHead->color_widget = QColor(m_color);
    m_notebook->m_noteHeadMenu->color_widget = QColor(m_color);
    m_notebook->update();

    QString noteDate = dateTime.toString(Qt::ISODate);
    QString noteDateEditor = getNoteDateEditor(noteDate);
    // set scrollbar position
    // m_textEdit->verticalScrollBar()->setValue(scrollbarPos);
}

/*!
 * \brief Widget::selectFirstNote
 *
 */
void Widget::selectFirstNote()
{
    if (m_proxyModel->rowCount() > 0) {
        QModelIndex index = m_proxyModel->index(0, 0);
        m_noteView->selectionModel()->select(index, QItemSelectionModel::ClearAndSelect);
        // 设置索引index所在的页面为当前页面
        m_noteView->setCurrentIndex(index);

        m_currentSelectedNoteProxy = index;
    }
}

/*!
 * \brief Widget::createNewNoteIfEmpty
 *
 */
void Widget::createNewNoteIfEmpty()
{
    // if(m_proxyModel->rowCount() == 0)
    createNewNote();
}

/*!
 * \brief Widget::createNewNote
 * add note
 * save to db
 */
void Widget::createNewNote()
{
    qDebug() << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    if (!m_isOperationRunning) {
        m_isOperationRunning = true;

        m_noteView->scrollToTop();

        ++m_noteCounter;
        qDebug() << "创建便签 m_noteCounter:" << m_noteCounter;
        NoteData *tmpNote = generateNote(m_noteCounter);

        // insert the new note to NoteModel
        QModelIndex indexSrc = m_noteModel->insertNote(tmpNote, 0);

        // update the editor header date label
        QString dateTimeFromDB = tmpNote->lastModificationdateTime().toString(Qt::ISODate);
        QString dateTimeForEditor = getNoteDateEditor(dateTimeFromDB);
        // 从排序过滤器模型返回与给定 indexSrc 对应的源模型索引。
        m_currentSelectedNoteProxy = m_proxyModel->mapFromSource(indexSrc);
        saveNoteToDB(m_currentSelectedNoteProxy);
        // int row = m_currentSelectedNoteProxy.row();
        // m_noteView->animateAddedRow(QModelIndex(),row, row);

        // 设置索引 m_currentSelectedNoteProxy 所在的页面为当前页面
        m_noteView->setCurrentIndex(m_currentSelectedNoteProxy);
        m_isOperationRunning = false;
    }
    int noteId = m_currentSelectedNoteProxy.data(NoteModel::NoteID).toInt();
    m_notebook = new Edit_page(this, noteId);
    m_editors.push_back(m_notebook);
    m_notebook->id = m_editors.size() - 1;

    if (sender() != Q_NULLPTR) {
        // 获取当前选中item下标
        // QModelIndex indexInProxy = m_proxyModel->index(index.row(), 0);
        // 加载便签
        selectNote(m_currentSelectedNoteProxy);
        m_noteView->setCurrentRowActive(false);
    }
    connect(m_editors[m_editors.size() - 1], &Edit_page::isEmptyNote, this, [=](int noteId){
        // m_editors.erase(m_editors[m_editors.size() - 1]);
        qDebug() << "receive signal isEmptyNote" << noteId;
        for (int count = 0; count <= m_proxyModel->rowCount(); count++) {
            QModelIndex m_tmpIndex = m_proxyModel->index(count, 0);
            if (m_tmpIndex.data(NoteModel::NoteID).toInt() == noteId) {
                QModelIndex sourceIndex = m_proxyModel->mapToSource(m_tmpIndex);
                deleteNote(m_tmpIndex, true);
                break;
            }
        }
    });
    connect(m_editors[m_editors.size() - 1], &Edit_page::requestDel, this, [=](int noteId){
        for (int count = 0; count <= m_proxyModel->rowCount(); count++) {
            QModelIndex m_tmpIndex = m_proxyModel->index(count, 0);
            if (m_tmpIndex.data(NoteModel::NoteID).toInt() == noteId) {
                QModelIndex sourceIndex = m_proxyModel->mapToSource(m_tmpIndex);
                deleteNote(m_tmpIndex, true);
                break;
            }
        }
    });
    connect(m_notebook->m_noteHeadMenu, &noteHeadMenu::requestNewNote, this, [=](){
        newSlot();
    });
    connect(m_notebook->m_noteHeadMenu, &noteHeadMenu::requestShowNote, this, [=] {
        // 添加窗管协议
        MotifWmHints hints;
        hints.flags = MWM_HINTS_FUNCTIONS|MWM_HINTS_DECORATIONS;
        hints.functions = MWM_FUNC_ALL;
        hints.decorations = MWM_DECOR_BORDER;
        XAtomHelper::getInstance()->setWindowMotifHint(this->winId(), hints);
        this->raise();
        this->activateWindow();
        this->show();
    });
    connect(m_editors[m_editors.size() - 1], SIGNAL(texthasChanged(int,int)), this,
            SLOT(onTextEditTextChanged(int,int)));
    connect(m_editors[m_editors.size() - 1], SIGNAL(colorhasChanged(QColor,int)), this,
            SLOT(onColorChanged(QColor,int)));
    // 设置鼠标焦点
    m_notebook->ui->textEdit->setFocus();
    // 移动光标至行末
    m_notebook->ui->textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    m_notebook->show();
}

/*!
 * \brief Widget::loadNotes
 *
 */
void Widget::loadNotes(QList<NoteData *> noteList, int noteCounter)
{
    if (!noteList.isEmpty()) {
        m_noteModel->addListNote(noteList);
        // Qt::AscendingOrder 升序排序
        m_noteModel->sort(1, Qt::AscendingOrder);
    }

    m_noteCounter = noteCounter;

    createNewNoteIfEmpty();
    selectFirstNote();
}

/*!
 * \brief Widget::saveNoteToDB
 *
 */
// 将当前便笺保存到数据库
void Widget::saveNoteToDB(const QModelIndex &noteIndex)
{
    if (noteIndex.isValid()) {
        // 从排序过滤器模型返回与给定 noteIndex 对应的源模型索引。
        QModelIndex indexInSrc = m_proxyModel->mapToSource(noteIndex);
        NoteData *note = m_noteModel->getNote(indexInSrc);
        if (note != Q_NULLPTR)
            emit requestCreateUpdateNote(note);

        m_isContentModified = false;
    } else if (noteIndex.isValid() && m_isColorModified) {
        // 从排序过滤器模型返回与给定 noteIndex 对应的源模型索引。
        QModelIndex indexInSrc = m_proxyModel->mapToSource(noteIndex);
        NoteData *note = m_noteModel->getNote(indexInSrc);
        if (note != Q_NULLPTR)
            emit requestCreateUpdateNote(note);
        m_isColorModified = false;
    }
}

/*!
 * \brief Widget::getQDateTime
 *
 */
QDateTime Widget::getQDateTime(QString date)
{
    QDateTime dateTime = QDateTime::fromString(date, Qt::ISODate);
    return dateTime;
}

/*!
 * \brief Widget::getNoteDateEditor
 *
 */
QString Widget::getNoteDateEditor(QString dateEdited)
{
    QDateTime dateTimeEdited(getQDateTime(dateEdited));
    QLocale usLocale = QLocale::system();

    return usLocale.toString(dateTimeEdited, QStringLiteral("yyyy/MM/dd hh:mm"));
}

/*!
 * \brief Widget::generateNote
 * 初始化一个笔记
 */
NoteData *Widget::generateNote(const int noteID)
{
    NoteData *newNote = new NoteData(this);
    newNote->setId(noteID);

    QDateTime noteDate = QDateTime::currentDateTime();
    newNote->setCreationDateTime(noteDate);
    newNote->setLastModificationDateTime(noteDate);
    newNote->setFullTitle(tr("Welcome to use Notes."));
    newNote->setNoteColor(15169356);
    newNote->m_note = nullptr;
    return newNote;
}

/*!
 * \brief Widget::moveNoteToTop
 *
 */
void Widget::moveNoteToTop()
{
    qDebug() << "movenote to top";
    // check if the current note is note on the top of the list
    // if true move the note to the top
    if (m_tmpIndex.isValid()) {
        m_noteView->scrollToTop();

        // NoteData* note = m_noteModel->getNote(index);

        // move the current selected note to the top
        // 当前要移动到顶端的item QSortFilterProxyModel
        QModelIndex sourceIndex = m_proxyModel->mapToSource(m_tmpIndex);

        // 目前顶端的item QAbstractListModel
        QModelIndex destinationIndex = m_noteModel->index(0);

        // 将 sourceIndex.row() 移动到第0行,第0行变第一行
        m_noteModel->moveRow(sourceIndex, sourceIndex.row(), destinationIndex, 0);

        // 更新当前 最顶端QAbstractListModel item 并添加代理
        m_tmpIndex = m_proxyModel->mapFromSource(destinationIndex);
        m_currentSelectedNoteProxy = m_tmpIndex;
        // 修改当前选中
        m_noteView->setCurrentIndex(m_tmpIndex);
    } else {
        qDebug() << "Widget::moveNoteTop : m_currentSelectedNoteProxy not valid";
    }
}

/*!
 * \brief Widget::getFirstLine
 *
 */
QString Widget::getFirstLine(const QString &str)
{
    if (str.simplified().isEmpty()) {
        return tr("Welcome to use Notes.");
    }

    QString text = str.trimmed();
    QTextStream ts(&text);
    return ts.readLine(FIRST_LINE_MAX);
}

/*!
 * \brief Widget::findNotesContain
 *
 */
void Widget::findNotesContain(const QString &keyword)
{
    // 将用于过滤源模型内容的固定字符串设置为给定模式
    m_proxyModel->setFilterFixedString(keyword);

    // 如果匹配到不止一行
    if (m_proxyModel->rowCount() > 0) {
        selectFirstNote();
    } else {
        m_currentSelectedNoteProxy = QModelIndex();
    }
}

/*!
 * \brief Widget::searchInit
 *
 */
void Widget::searchInit()
{
    m_searchLine->setContextMenuPolicy(Qt::NoContextMenu);  // 禁用右键菜单
    m_searchLine->setPlaceholderText(tr("Search"));         // 设置详细输入框的提示信息
    searchAction = new QAction(m_searchLine);
    searchAction->setIcon(QIcon::fromTheme("system-search-symbolic"));
    m_searchLine->setProperty("useIconHighlightEffect", true);
    m_searchLine->setProperty("iconHighlightEffectMode", 1);
    m_searchLine->addAction(searchAction, QLineEdit::LeadingPosition);  // 图片在左侧
    // m_searchLine->setAttribute(Qt::WA_Hover, true);

    QTimer::singleShot(500, this, [=](){
        QList<QWidget *> wid = m_searchLine->findChildren<QWidget *>();
        for (int i = 0; i < wid.count(); i++) {
            wid.at(i)->setAttribute(Qt::WA_Hover, false);
        }
    });

    delAction = new QAction(m_searchLine);
    delAction->setIcon(QIcon::fromTheme("edit-clear-symbolic"));
    connect(delAction, &QAction::triggered, this, [=](){
        m_searchLine->setText("");
    });
}

/*!
 * \brief Widget::clearSearch
 *
 */
void Widget::clearSearch()
{
    m_noteView->setFocusPolicy(Qt::StrongFocus);

    m_searchLine->blockSignals(true);
    m_searchLine->clear();
    m_searchLine->blockSignals(false);
    m_proxyModel->setFilterFixedString(QString());
    m_searchLine->setFocus();
    m_searchLine->addAction(searchAction, QLineEdit::LeadingPosition);  // 图片在左侧
    m_searchLine->removeAction(delAction);
}

/*!
 * \brief Widget::mousePressEvent
 *
 */
// void Widget::mousePressEvent(QMouseEvent *event)
// {
// if (event->button() == Qt::LeftButton) {
// this->dragPosition = event->globalPos() - frameGeometry().topLeft();
// this->mousePressed = true;
// }
// QWidget::mousePressEvent(event);
// }

/*!
 * \brief Widget::mouseReleaseEvent
 *
 */
// void Widget::mouseReleaseEvent(QMouseEvent *event)
// {
// if (event->button() == Qt::LeftButton) {
// this->mousePressed = false;
// }
// QWidget::mouseReleaseEvent(event);
// }

/*!
 * \brief Widget::mouseMoveEvent
 *
 */
// void Widget::mouseMoveEvent(QMouseEvent *event)
// {
// if (this->mousePressed) {
// int dpiRatio = qApp->devicePixelRatio();
// move(event->globalPos() - this->dragPosition.x() * dpiRatio,
// (event->globalPos() - this->dragPosition.y() * dpiRatio));
// this->setCursor(Qt::ClosedHandCursor);
// }
// QWidget::mouseMoveEvent(event);
// }

/*!
 * \brief Widget::paintEvent
 *
 */
void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    // QStyleOption opt;
    // opt.init(this);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    QPainterPath rectPath;
    rectPath.addRect(this->rect());
    // rectPath.addRoundedRect(this->rect(), 6, 6); // 左上右下

    // 画一个黑底
    // QPixmap pixmap(this->rect().size());
    // pixmap.fill(Qt::transparent);
    // QPainter pixmapPainter(&pixmap);
    // pixmapPainter.setRenderHint(QPainter::Antialiasing);
    // pixmapPainter.setPen(Qt::transparent);
    // pixmapPainter.setBrush(Qt::black);
    // pixmapPainter.drawPath(rectPath);
    // pixmapPainter.end();

    // 模糊这个黑底
    // QImage img = pixmap.toImage();
    // qt_blurImage(img, 10, false, false);

    // 挖掉中心
    // pixmap = QPixmap::fromImage(img);
    // QPainter pixmapPainter2(&pixmap);
    // pixmapPainter2.setRenderHint(QPainter::Antialiasing);
    // pixmapPainter2.setCompositionMode(QPainter::CompositionMode_Clear);
    // pixmapPainter2.setPen(Qt::transparent);
    // pixmapPainter2.setBrush(Qt::transparent);
    // pixmapPainter2.drawPath(rectPath);

    // 绘制阴影
    // p.drawPixmap(this->rect(), pixmap, pixmap.rect());

    // 绘制一个背景
    // p.save();
    // p.setOpacity(0.7);
    p.fillPath(rectPath, palette().color(QPalette::Base));
    // p.restore();
}

/********************Slots************************/

/*!
 * \brief Widget::onTextEditTextChanged
 *
 */
void Widget::onTextEditTextChanged(int noteId, int i)
{
    qDebug() << "receive signal textchange" << noteId;
    for (int count = 0; count <= m_proxyModel->rowCount(); count++) {
        m_tmpIndex = m_proxyModel->index(count, 0);
        if (m_tmpIndex.data(NoteModel::NoteID).toInt() == noteId) {
            qDebug() << m_tmpIndex.data(NoteModel::NoteID).toInt();
            break;
        }
    }

    if (m_tmpIndex.isValid()) {
        QString content = m_tmpIndex.data(NoteModel::NoteContent).toString();
        QString mdContent = m_tmpIndex.data(NoteModel::NoteMdContent).toString();

        if (m_editors[i]->ui->textEdit->toHtml().toUtf8() != content) {
            // move note to the top of the list
            QModelIndex sourceIndex = m_proxyModel->mapToSource(m_tmpIndex);

            qDebug() << m_currentSelectedNoteProxy;
            if (m_tmpIndex.row() != 0) {
                // m_noteView->setAnimationEnabled(false);
                moveNoteToTop();
                // m_noteView->setAnimationEnabled(true);
            } else if (!m_searchLine->text().isEmpty() && sourceIndex.row() != 0) {
                m_noteView->setAnimationEnabled(false);
                moveNoteToTop();
                m_noteView->setAnimationEnabled(true);
            }

            // QModelIndex firstIndex = m_proxyModel->index(0,0);
            // Get the new data
            QString firstline = getFirstLine(m_editors[i]->ui->textEdit->toPlainText());
            QDateTime dateTime = QDateTime::currentDateTime();
            // QString noteDate = dateTime.toString(Qt::ISODate);

            // update model
            QMap<int, QVariant> dataValue;
            dataValue[NoteModel::NoteContent] = QVariant::fromValue(
                m_editors[i]->ui->textEdit->toHtml().toUtf8());
            dataValue[NoteModel::NoteMdContent] = QVariant::fromValue(
                m_editors[i]->ui->textEdit->toPlainText());
            dataValue[NoteModel::NoteFullTitle] = QVariant::fromValue(firstline);
            dataValue[NoteModel::NoteLastModificationDateTime] = QVariant::fromValue(dateTime);

            QModelIndex currentIndex = m_proxyModel->mapToSource(m_tmpIndex);
            m_noteModel->setItemData(currentIndex, dataValue);

            m_isContentModified = true;
            // m_autoSaveTimer->start(500);
            saveNoteToDB(m_tmpIndex);
        }
    } else {
        qDebug() << "Widget::onTextEditTextChanged() : index is not valid";
    }
}

/*!
 * \brief Widget::onColorChanged
 *
 */
void Widget::onColorChanged(const QColor &color, int noteId)
{
    qDebug() << "receive signal onColorChanged";
    for (int count = 0; count <= m_proxyModel->rowCount(); count++) {
        m_tmpColorIndex = m_proxyModel->index(count, 0);
        if (m_tmpColorIndex.data(NoteModel::NoteID).toInt() == noteId) {
            break;
        }
    }

    if (m_tmpColorIndex.isValid()) {
        const listViewModeDelegate delegate;
        int m_color = delegate.qcolorToInt(color);
        QMap<int, QVariant> dataValue;
        dataValue[NoteModel::NoteColor] = QVariant::fromValue(m_color);

        QModelIndex index = m_proxyModel->mapToSource(m_tmpColorIndex);
        m_noteModel->setItemData(index, dataValue);
        m_isColorModified = true;
        saveNoteToDB(m_tmpColorIndex);
    }
}

/*!
 * \brief Widget::exitSlot
 *
 */
void Widget::exitSlot()
{
    this->close();
}

/*!
 * \brief Widget::trashSlot
 *
 */
void Widget::trashSlot()
{
    m_emptyNotes->exec();
}

/*!
 * \brief Widget::miniSlot
 *
 */
void Widget::miniSlot()
{
    this->showNormal();
    this->showMinimized();
}

/*!
 * \brief Widget::newSlot
 *
 */
void Widget::newSlot()
{
    // 如果搜索栏有内容,则在新建便签时清空
    if (!m_searchLine->text().isEmpty()) {
        clearSearch();
    }
    this->createNewNote();
}

/*!
 * \brief Widget::onTrashButtonClicked
 *
 */
void Widget::onTrashButtonClicked()
{
    m_trashButton->blockSignals(true);
    deleteSelectedNote();
    m_trashButton->blockSignals(false);
}

/*!
 * \brief Widget::listClickSlot
 * listview单击事件
 */
void Widget::listClickSlot(const QModelIndex &index)
{
    if (sender() != Q_NULLPTR) {
        QModelIndex indexInProxy = m_proxyModel->index(index.row(), 0);
        if (indexInProxy.isValid()) {
            m_currentSelectedNoteProxy = indexInProxy;

            m_noteView->selectionModel()->select(m_currentSelectedNoteProxy,
                                                 QItemSelectionModel::ClearAndSelect);
            m_noteView->setCurrentIndex(m_currentSelectedNoteProxy);
            m_noteView->scrollTo(m_currentSelectedNoteProxy);
        } else {
            qDebug() << "Widget::selectNote() : indexInProxy is not valid";
            m_currentSelectedNoteProxy = QModelIndex();
        }
        m_noteView->setCurrentRowActive(false);
    }
}

/*!
 * \brief Widget::listDoubleClickSlot
 * 在滚动区域中单击便笺时：
 * 取消突出显示上一个选定的便笺
 * 如果在临时便笺存在时选择便笺，请删除临时便笺
 * 突出显示所选便笺
 * 将所选便笺内容加载到textedit
 */
void Widget::listDoubleClickSlot(const QModelIndex &index)
{
    int noteId = index.data(NoteModel::NoteID).toInt();
    int isExistInMeditors = 0;
    qDebug() << "list double click" << noteId << index;
    for (auto it = m_editors.begin(); it != m_editors.end(); it++) {
        if ((*it)->m_noteId == noteId) {
            isExistInMeditors = 1;
            m_notebook = *it;
            m_notebook->raise();
            m_notebook->activateWindow();
            break;
        }
    }
    if (isExistInMeditors == 0) {
        m_notebook = new Edit_page(this, noteId);
        m_editors.push_back(m_notebook);
        m_notebook->id = m_editors.size() - 1;

        if (sender() != Q_NULLPTR) {
            // 获取当前选中item下标
            // QModelIndex indexInProxy = m_proxyModel->index(index.row(), 0);
            // 加载便签
            selectNote(index);
            m_noteView->setCurrentRowActive(false);
        }
        connect(m_notebook->m_noteHeadMenu, &noteHeadMenu::requestNewNote, this, [=](){
            newSlot();
        });
        connect(m_notebook->m_noteHeadMenu, &noteHeadMenu::requestShowNote, this, [=] {
            // 添加窗管协议
            MotifWmHints hints;
            hints.flags = MWM_HINTS_FUNCTIONS|MWM_HINTS_DECORATIONS;
            hints.functions = MWM_FUNC_ALL;
            hints.decorations = MWM_DECOR_BORDER;
            XAtomHelper::getInstance()->setWindowMotifHint(this->winId(), hints);
            this->raise();
            this->activateWindow();
            this->show();
        });
        connect(m_editors[m_editors.size() - 1], &Edit_page::requestDel, this, [=](int noteId){
            for (int count = 0; count <= m_proxyModel->rowCount(); count++) {
                QModelIndex m_tmpIndex = m_proxyModel->index(count, 0);
                if (m_tmpIndex.data(NoteModel::NoteID).toInt() == noteId) {
                    QModelIndex sourceIndex = m_proxyModel->mapToSource(m_tmpIndex);
                    deleteNote(m_tmpIndex, true);
                    break;
                }
            }
        });
        connect(m_editors[m_editors.size() - 1], SIGNAL(texthasChanged(int,int)), this,
                SLOT(onTextEditTextChanged(int,int)));
        connect(m_editors[m_editors.size() - 1], SIGNAL(colorhasChanged(QColor,int)), this,
                SLOT(onColorChanged(QColor,int)));
    }
    // 设置鼠标焦点
    m_notebook->ui->textEdit->setFocus();
    // 移动光标至行末
    m_notebook->ui->textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    m_notebook->show();
}

/*!
 * \brief Widget::onSearchEditTextChanged
 *
 */
void Widget::onSearchEditTextChanged(const QString &keyword)
{
    qDebug() << "onSearchEditTextChanged";
    m_searchQueue.enqueue(keyword);

    if (m_searchLine->text().isEmpty()) {
        m_searchLine->addAction(searchAction, QLineEdit::LeadingPosition);  // 图片在左侧
        m_searchLine->removeAction(delAction);
    } else {
        m_searchLine->removeAction(searchAction);
        m_searchLine->addAction(delAction, QLineEdit::TrailingPosition);  // 图片在右侧
    }

    if (!m_isOperationRunning) {
        m_isOperationRunning = true;

        // disable animation while searching
        m_noteView->setAnimationEnabled(false);

        while (!m_searchQueue.isEmpty()) {
            qApp->processEvents();
            QString str = m_searchQueue.dequeue();
            if (str.isEmpty()) {
                clearSearch();
            } else {
                m_noteView->setFocusPolicy(Qt::NoFocus);
                // 过滤
                findNotesContain(str);
            }
        }

        m_noteView->setAnimationEnabled(true);
        m_isOperationRunning = false;
    }
}

/*!
 * \brief Widget::changePageSlot
 *
 */
void Widget::changePageSlot()
{
    if (getListFlag() != 0) {
        initIconMode();
        m_viewChangeButton->setIcon(QIcon::fromTheme("view-list-symbolic"));
        setListFlag(0);
    } else if (getListFlag() == 0) {
        initListMode();
        m_viewChangeButton->setIcon(QIcon::fromTheme("view-grid-symbolic"));
        setListFlag(1);
    }
    if (m_noteModel->rowCount() > 0) {
        QModelIndex index = m_noteView->currentIndex();
        m_currentSelectedNoteProxy = index;
        m_noteView->selectionModel()->select(m_currentSelectedNoteProxy,
                                             QItemSelectionModel::ClearAndSelect);
        m_noteView->setCurrentIndex(m_currentSelectedNoteProxy);
        m_noteView->scrollTo(m_currentSelectedNoteProxy);
    } else {
        // 创建新的空模型索引 此类型的模型索引用于指示模型中的位置无效
        m_currentSelectedNoteProxy = QModelIndex();
    }
}

/*!
 * \brief Widget::sortSlot
 *
 */
void Widget::sortSlot(int index)
{
    // Qt::AscendingOrder 升序排序
    // 参见 NoteModel::sort
    if (m_proxyModel->rowCount()) {
        if (sortflag) {
            m_noteModel->sort(index, Qt::DescendingOrder);
            sortflag = 0;
        } else {
            m_noteModel->sort(index, Qt::AscendingOrder);
            sortflag = 1;
        }
    }
}

/*!
 * \brief Widget::clearNoteSlot
 *
 */
void Widget::clearNoteSlot()
{
    qDebug() << "empty note" << m_editors.size();
    for (auto it = m_editors.begin(); it != m_editors.end(); it++) {
        (*it)->close();
        // m_editors.erase(it);
        delete (*it);
    }
    m_editors.clear();
    qDebug() << "清空vector" << m_editors.size();
    m_noteModel->clearNotes();
    emit requestClearNote();
}

/*!
 * \brief Widget::SetNoteSlot
 *
 */
// void Widget::SetNoteSlot()
// {
// qDebug() << "SetNoteSlot";
// }

/*!
 * \brief Widget::setNoteNullSlot
 *
 */
void Widget::setNoteNullSlot()
{
    for (int i = 0; i < m_proxyModel->rowCount(); i++) {
        QModelIndex index = m_proxyModel->index(i, 0);
        NoteData *note = m_noteModel->getNote(index);
        note->m_note = nullptr;
    }
}

/*!
 * \brief Widget::onF1ButtonClicked
 *
 */
void Widget::onF1ButtonClicked()
{
    qDebug() << "onF1ButtonClicked";
    userGuideInterface->call(QString("showGuide"), "tools/ukui-notebook");
}
