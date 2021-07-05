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

#include <QBitmap>
#include <QPalette>
#include <QPainter>
#include <QTextList>
//#include <QClipboard>
#include <QDebug>
#include <QtX11Extras/QX11Info>

#include "widget.h"
#include "ui_widget.h"
#include "editPage.h"
#include "ui_editPage.h"
#include "utils/xatom-helper.h"

extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);

Edit_page::Edit_page(Widget *page, int noteId, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Edit_page),
    m_editColor(0, 0, 0),
    m_noteId(noteId),
    m_lastBlockList(0),
    mousePressed(false),
    defaultFontColorChanged(false),
    pNotebook(page),
    color_page(new SelectColor(pNotebook, this)),
    set_size_page(new SetFontSize(pNotebook)),
    set_color_fort_page(new SetFontColor(pNotebook)),
    m_isFullscreen(false),
    m_isTopHit(false)
{
    ui->setupUi(this);
    initSetup();
    listenToGsettings();
    slotsSetup();
}

Edit_page::~Edit_page()
{
    delete ui;
}

void Edit_page::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    QPainterPath rectPath;
    rectPath.addRect(this->rect());
    p.fillPath(rectPath, palette().color(QPalette::Base));
}

void Edit_page::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_noteHead->hide();
    m_noteHeadMenu->show();
}

void Edit_page::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    if(!m_noteHeadMenu->ui->pushButtonMenu->isActiveWindow() && !m_noteHeadMenu->ui->pushButtonPalette->isActiveWindow())
    {
        m_noteHead->show();
        m_noteHeadMenu->hide();
    }
}

void Edit_page::initSetup()
{
    // 标题
    this->setWindowTitle(tr("Notes"));
    // 任务栏图标
    //setWindowIcon(QIcon::fromTheme("kylin-notebook"));
    //setWindowFlags(Qt::FramelessWindowHint);

#if (QT_VERSION >= QT_VERSION_CHECK(5, 12, 0))
    // 高分屏适配
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

    // 添加窗管协议
    MotifWmHints hints;
    hints.flags = MWM_HINTS_FUNCTIONS|MWM_HINTS_DECORATIONS;
    hints.functions = MWM_FUNC_ALL;
    hints.decorations = MWM_DECOR_BORDER;
    XAtomHelper::getInstance()->setWindowMotifHint(this->winId(), hints);
    // 配置按钮
    btnSetup();
    initColor();
    // 获取字体按钮状态
    fontChanged(ui->textEdit->font());

    m_noteHead = new noteHead(this);
    m_noteHeadMenu = new noteHeadMenu(this);

    ui->verticalLayout_3->addWidget(m_noteHead);
    ui->verticalLayout_3->addWidget(m_noteHeadMenu);
    m_noteHeadMenu->hide();

    ui->textEdit->setFrameShape(QFrame::NoFrame);
    ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 右键菜单
    ui->textEdit->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->textEdit, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(textRightMenu(QPoint)));

    // 设置字体大小
    set_size_page = new SetFontSize(this);
    set_size_page->hide();
    // 设置字体颜色
    set_color_fort_page = new SetFontColor(this);
    set_color_fort_page->hide();
}

void Edit_page::btnSetup()
{
    ui->boldBtn->setIcon(QPixmap(":/image/1x/bold.png"));
    ui->italicBtn->setIcon(QPixmap(":/image/1x/Italic.png"));
    ui->underlineBtn->setIcon(QPixmap(":/image/1x/under_line-new.png"));
    ui->strikeOutBtn->setIcon(QPixmap(":/image/1x/del_line.png"));
    ui->unorderedBtn->setIcon(QPixmap(":/image/1x/Symbol.png"));
    ui->orderedBtn->setIcon(QPixmap(":/image/1x/number.png"));

    ui->boldBtn->setToolTip(tr("Bold"));
    ui->italicBtn->setToolTip(tr("Italic"));
    ui->underlineBtn->setToolTip(tr("Underline"));
    ui->strikeOutBtn->setToolTip(tr("Strikeout"));
    ui->unorderedBtn->setToolTip(tr("Unordered"));
    ui->orderedBtn->setToolTip(tr("Ordered"));

    ui->fontSizeBtn->setToolTip(tr("Font Size"));
    ui->styleBtn->setToolTip(tr("Font Color"));

    // ui->underlineBtn->setIcon(QIcon::fromTheme("format-text-underline-symbolic"));
    // ui->boldBtn->setIcon(QIcon::fromTheme("format-text-bold-symbolic"));
    // ui->italicBtn->setIcon(QIcon::fromTheme("format-text-italic-symbolic"));

    // 取消按钮默认灰色背景
    QPalette palette = ui->boldBtn->palette();
    QColor ColorPlaceholderText(255, 255, 255, 0);
    QBrush brush;
    brush.setColor(ColorPlaceholderText);
    palette.setBrush(QPalette::Button, brush);
    palette.setBrush(QPalette::ButtonText, brush);
    ui->boldBtn->setPalette(palette);
    ui->italicBtn->setPalette(palette);
    ui->underlineBtn->setPalette(palette);
    ui->strikeOutBtn->setPalette(palette);
    ui->unorderedBtn->setPalette(palette);
    ui->orderedBtn->setPalette(palette);

    QPalette palette2 = ui->fontColorBtn->palette();
    palette2.setColor(QPalette::Highlight, Qt::transparent); /* 取消按钮高亮 */
    ui->fontColorBtn->setPalette(palette2);

    ui->boldBtn->setCheckable(true);
    ui->italicBtn->setCheckable(true);
    ui->underlineBtn->setCheckable(true);
    ui->strikeOutBtn->setCheckable(true);
    ui->unorderedBtn->setCheckable(true);
    ui->orderedBtn->setCheckable(true);
    ui->fontSizeBtn->setCheckable(false);

//变更btn的属性，hover态，蓝色变为灰色
#if 1
    ui->boldBtn->setProperty("isWindowButton", 0x1);
    ui->boldBtn->setProperty("useIconHighlightEffect", 0x2);

    ui->italicBtn->setProperty("isWindowButton", 0x1);
    ui->italicBtn->setProperty("useIconHighlightEffect", 0x2);

    ui->underlineBtn->setProperty("isWindowButton", 0x1);
    ui->underlineBtn->setProperty("useIconHighlightEffect", 0x2);

    ui->strikeOutBtn->setProperty("isWindowButton", 0x1);
    ui->strikeOutBtn->setProperty("useIconHighlightEffect", 0x2);

    ui->unorderedBtn->setProperty("isWindowButton", 0x1);
    ui->unorderedBtn->setProperty("useIconHighlightEffect", 0x2);

    ui->orderedBtn->setProperty("isWindowButton", 0x1);
    ui->orderedBtn->setProperty("useIconHighlightEffect", 0x2);
#else
    ui->boldBtn->setProperty("useIconHighlightEffect", true);
    ui->boldBtn->setProperty("iconHighlightEffectMode", 1);
    ui->italicBtn->setProperty("useIconHighlightEffect", true);
    ui->italicBtn->setProperty("iconHighlightEffectMode", 1);
    ui->underlineBtn->setProperty("useIconHighlightEffect", true);
    ui->underlineBtn->setProperty("iconHighlightEffectMode", 1);
    ui->strikeOutBtn->setProperty("useIconHighlightEffect", true);
    ui->strikeOutBtn->setProperty("iconHighlightEffectMode", 1);
    ui->unorderedBtn->setProperty("useIconHighlightEffect", true);
    ui->unorderedBtn->setProperty("iconHighlightEffectMode", 1);
    ui->orderedBtn->setProperty("useIconHighlightEffect", true);
    ui->orderedBtn->setProperty("iconHighlightEffectMode", 1);
#endif
}

void Edit_page::slotsSetup()
{
    connect(m_noteHeadMenu->ui->pushButtonExit, &QPushButton::clicked, this, [=](){
        if (ui->textEdit->document()->isEmpty()) {
            emit isEmptyNote(m_noteId);
        }
        this->close();
    });
    connect(m_noteHeadMenu->m_menuActionDel, &QAction::triggered, this, [=](){
        this->close();
        requestDel(m_noteId);
    });
    connect(ui->textEdit, &QTextEdit::textChanged, this, &Edit_page::textChangedSlot);
    // 调色板菜单
    connect(m_noteHeadMenu->ui->pushButtonPalette, &QPushButton::clicked, this, [=](){
        QPointF position = this->pos();
        color_page->move(position.x()+30, position.y()+34);
        color_page->show();
    });
    // 调色按钮
    connect(color_page->paletteWidget->ui->blueBtn, &QPushButton::clicked, this,
            &Edit_page::blueBtnSlot);
    connect(color_page->paletteWidget->ui->redBtn, &QPushButton::clicked, this,
            &Edit_page::redBtnSlot);
    connect(color_page->paletteWidget->ui->darkGreenBtn, &QPushButton::clicked, this,
            &Edit_page::darkGreenBtnSlot);
    connect(color_page->paletteWidget->ui->orangeBtn, &QPushButton::clicked, this,
            &Edit_page::orangeBtnSlot);
    connect(color_page->paletteWidget->ui->purpleBtn, &QPushButton::clicked, this,
            &Edit_page::purpleBtnSlot);
    connect(color_page->paletteWidget->ui->goldenBtn, &QPushButton::clicked, this,
            &Edit_page::goldenBtnSlot);
    connect(color_page->paletteWidget->ui->lightBlueBtn, &QPushButton::clicked, this,
            &Edit_page::lightBlueBtnSlot);
    connect(color_page->paletteWidget->ui->lightGreenBtn, &QPushButton::clicked, this,
            &Edit_page::lightGreenBtnSlot);
    connect(color_page->paletteWidget->ui->yellowBtn, &QPushButton::clicked, this,
            &Edit_page::yellowBtnSlot);
    connect(color_page->paletteWidget->ui->pinkBtn, &QPushButton::clicked, this,
            &Edit_page::pinkBtnSlot);
    // 字体颜色大小
    connect(set_size_page->ui->listWidget, &QListWidget::itemClicked, this,
            &Edit_page::setFontSizeSlot);
    connect(set_color_fort_page->ui->listWidget, &QListWidget::itemClicked, this,
            &Edit_page::setFontColorSlot);
    // 文本格式
    connect(ui->boldBtn, &QPushButton::clicked, this, &Edit_page::setBoldSlot);
    connect(ui->italicBtn, &QPushButton::clicked, this, &Edit_page::setItalicSlot);
    connect(ui->underlineBtn, &QPushButton::clicked, this, &Edit_page::setUnderlineSlot);
    connect(ui->strikeOutBtn, &QPushButton::clicked, this, &Edit_page::setStrikeOutSlot);
    connect(ui->unorderedBtn, &QPushButton::clicked, this, &Edit_page::setUnorderedListSlot);
    connect(ui->orderedBtn, &QPushButton::clicked, this, &Edit_page::setOrderedListSlot);
    connect(ui->textEdit, &QTextEdit::cursorPositionChanged, this,
            &Edit_page::cursorPositionChangedSlot);
    connect(ui->textEdit, &QTextEdit::currentCharFormatChanged, this,
            &Edit_page::currentCharFormatChangedSlot);

    connect(ui->fontSizeBtn, &QPushButton::clicked, this, [=](){

        QPointF position = this->pos();
        set_size_page->move(position.x()+227, position.y()+273);

        QDesktopWidget* desktopWidget = QApplication::desktop();
        QRect clientRect = desktopWidget->availableGeometry();                                   //获取整个屏幕（不包含任务栏）的rect数据

        int listHeight = 194;                                                                    //listwidget 原始高度
        int heightListCrossPeny = listHeight + set_size_page->pos().y() - clientRect.height();   //listwidget 超出任务栏显示的高度， 不超出时， 该数字为负数

        if(heightListCrossPeny > 0)                                                              //listwidget 超出任务栏显示
        {
            int fontButtonHeight = 27;                                                           //每个fontbutton高度,当前为27
            int keepNum = listHeight - heightListCrossPeny;                                      //listwidget 未超出任务栏显示的高度
            int realNum = keepNum - (keepNum % fontButtonHeight);                                //最后，实际显示的高度，应该是每个fontbutton高度（27）的整数倍，小于27时，为0

            //listWidget 向下显示，高度不够，此时，显示到set_size_page的上面
            if(realNum == 0){
               set_size_page->move(position.x()+227, position.y()+53);
               set_size_page->resize(30,194);
               set_size_page->ui->listWidget->resize(30,194);
               //set_size_page->ui->listWidget->sortItems(Qt::DescendingOrder);                 //倒序，但是数据会混乱，暂缓
            }
            else{
               set_size_page->resize(30, realNum);
               set_size_page->ui->listWidget->resize(30, realNum);
            }
        }
        else
        {
            set_size_page->move(position.x()+227, position.y()+273);
            set_size_page->resize(30,194);
            set_size_page->ui->listWidget->resize(30,194);
        }

        set_size_page->show();
    });
    connect(ui->fontColorBtn, &QPushButton::clicked, this, [=](){

        QPointF position = this->pos();
        set_color_fort_page->move(position.x()+260, position.y()+273);

        QDesktopWidget* desktopWidget = QApplication::desktop();
        QRect clientRect = desktopWidget->availableGeometry();                   //获取整个屏幕（不包含任务栏）的rect数据

        int listHeight = 194;                                                    //listwidget 原始高度
        int heightListCrossPeny = listHeight + set_color_fort_page->pos().y() - clientRect.height();   //listwidget 超出任务栏显示的高度， 不超出时， 该数字为负数

        if(heightListCrossPeny > 0)                                              //listwidget 超出任务栏显示
        {
            int fontButtonHeight = 27;                                           //每个fontbutton高度,当前为27
            int keepNum = listHeight - heightListCrossPeny;                      //listwidget 未超出任务栏显示的高度
            int realNum = keepNum - (keepNum % fontButtonHeight);                //最后，实际显示的高度，应该是每个fontbutton高度（27）的整数倍，小于27时，为0

            //listWidget 向下显示，高度不够，此时，显示到set_color_fort_page的上面
            if(realNum == 0){
               set_color_fort_page->move(position.x()+260, position.y()+53);
               set_color_fort_page->resize(30,194);
               set_color_fort_page->ui->listWidget->resize(30,194);
               //set_color_fort_page->ui->listWidget->sortItems(Qt::DescendingOrder);  //倒序，但是数据会混乱，暂缓
            }
            else{
               set_color_fort_page->resize(30, realNum);
               set_color_fort_page->ui->listWidget->resize(30, realNum);
            }
        }
        else
        {
            set_color_fort_page->move(position.x()+260, position.y()+273);
            set_color_fort_page->resize(30,194);
            set_color_fort_page->ui->listWidget->resize(30,194);
        }

        set_color_fort_page->show();
    });

     connect(m_noteHeadMenu, &noteHeadMenu::requestTopMost, this, [=](){
         if(m_isTopHit) {
             m_isTopHit = false;
             setStayOnTopSlot(m_isTopHit);
             m_noteHeadMenu->m_topAction->setIcon(QPixmap(""));
         }
         else {
             m_isTopHit = true;
             setStayOnTopSlot(m_isTopHit);
             m_noteHeadMenu->m_topAction->setIcon(QPixmap(":/image/1x/select.png"));
         }
     });
}

void Edit_page::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if (!cursor.hasSelection()) {
        cursor.select(QTextCursor::WordUnderCursor);
    }
    cursor.mergeCharFormat(format);
    ui->textEdit->mergeCurrentCharFormat(format);
    ui->textEdit->setFocus(Qt::TabFocusReason);
}

void Edit_page::fontChanged(const QFont &f)
{
    qDebug() << "font Changed" << f.pointSize() << f.bold();
    set_size_page->ui->listWidget->setCurrentRow(f.pointSize() - 10);
//    ui->fontSizeBtn->setText(QString::number(f.pointSize()));

    if(f.pointSize() < 10 )
    {
        ui->fontSizeBtn->setText(QString::number(10));
    }
    else
    {
        ui->fontSizeBtn->setText(QString::number(f.pointSize()));
    }
    ui->boldBtn->setChecked(f.bold());
    ui->italicBtn->setChecked(f.italic());
    ui->underlineBtn->setChecked(f.underline());
    ui->strikeOutBtn->setChecked(f.strikeOut());

    if (ui->textEdit->textCursor().currentList()) {
        QTextListFormat lfmt = ui->textEdit->textCursor().currentList()->format();
        if (lfmt.style() == QTextListFormat::ListDisc) {
            ui->unorderedBtn->setChecked(true);
            ui->orderedBtn->setChecked(false);
        } else if (lfmt.style() == QTextListFormat::ListDecimal) {
            ui->unorderedBtn->setChecked(false);
            ui->orderedBtn->setChecked(true);
        } else {
            ui->unorderedBtn->setChecked(false);
            ui->orderedBtn->setChecked(false);
        }
    } else {
        ui->unorderedBtn->setChecked(false);
        ui->orderedBtn->setChecked(false);
    }
}

void Edit_page::fontColorChanged(const QColor &c)
{
    qDebug() << "fontColorChanged" << c.name();
    QString _Stylesheet;
    QString _BgColor;
    _BgColor = c.name();
    _Stylesheet = "background-color: %1;";
    _Stylesheet = _Stylesheet.arg(_BgColor);

    ui->fontColorBtn->setStyleSheet(_Stylesheet +"border-radius:3px;");
}

void Edit_page::list(bool checked, QTextListFormat::Style style)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.beginEditBlock();
    if (!checked) {
        qDebug() << "unchecked";
        QTextBlockFormat obfmt = cursor.blockFormat();
        QTextBlockFormat bfmt;
        bfmt.setIndent(obfmt.indent());
        cursor.setBlockFormat(bfmt);
    } else {
        qDebug() << "checked";
        QTextListFormat listFmt;
        if (cursor.currentList()) {
            listFmt = cursor.currentList()->format();
        }
        listFmt.setStyle(style);
        QTextDocument *document = ui->textEdit->document();
        document->setIndentWidth(15);
        cursor.createList(listFmt);
    }
    cursor.endEditBlock();
}

/*!
 * \brief Edit_page::listenToGsettings
 *
 */
void Edit_page::listenToGsettings()
{
    // 监听主题改变
    const QByteArray id(THEME_QT_SCHEMA);
    if (QGSettings::isSchemaInstalled(id)) {
        QGSettings *styleSettings = new QGSettings(id, QByteArray(), this);
        auto style = styleSettings->get("styleName").toString();
        //if (ui->textEdit->document()->isEmpty()) {
            if (style == "ukui-default" || style == "ukui-white"
                || style == "ukui-light" || style == "ukui") {
                ui->fontColorBtn->setStyleSheet("background-color: black;"
                                                "border-radius:3px;");
            } else if (style == "ukui-dark" || style == "ukui-black") {
                ui->fontColorBtn->setStyleSheet("background-color: white;"
                                                "border-radius:3px;");
            }
        //}

        connect(styleSettings, &QGSettings::changed, this, [=](const QString &key){
            if (/*ui->textEdit->document()->isEmpty() && */!defaultFontColorChanged) {
                if (key == "styleName") {
                    QString currentTheme = styleSettings->get(MODE_QT_KEY).toString();
                    if (currentTheme == "ukui-default" || currentTheme == "ukui-white"
                        || currentTheme == "ukui-light" || currentTheme == "ukui") {
                        ui->fontColorBtn->setStyleSheet("background-color: black;"
                                                        "border-radius:3px;");
                        ui->frame->setStyleSheet("background-color:rgb(217, 217, 217)");
                        ui->frame_2->setStyleSheet("background-color:rgb(217, 217, 217)");

                    } else if (currentTheme == "ukui-dark" || currentTheme == "ukui-black") {
                        ui->fontColorBtn->setStyleSheet("background-color: white;"
                                                        "border-radius:3px;");
                        ui->frame->setStyleSheet("background-color:rgb(77, 77, 77)");
                        ui->frame_2->setStyleSheet("background-color:rgb(77, 77, 77)");

                    }
                }
            }
        });
    }
}

/**************** Slots *******************/

void Edit_page::cursorPositionChangedSlot()
{
    qDebug() << "cursorPositionChangedSlot";
    QTextList *l = ui->textEdit->textCursor().currentList();
    if (m_lastBlockList && (l == m_lastBlockList || (l != 0 && m_lastBlockList != 0
                                                     && l->format().style()
                                                     == m_lastBlockList->format().style()))) {
        return;
    }
    m_lastBlockList = l;
    if (l) {
        QTextListFormat lfmt = l->format();
        if (lfmt.style() == QTextListFormat::ListDisc) {
            ui->unorderedBtn->setChecked(true);
            ui->orderedBtn->setChecked(false);
        } else if (lfmt.style() == QTextListFormat::ListDecimal) {
            ui->unorderedBtn->setChecked(false);
            ui->orderedBtn->setChecked(true);
        } else {
            ui->unorderedBtn->setChecked(false);
            ui->orderedBtn->setChecked(false);
        }
    } else {
        ui->unorderedBtn->setChecked(false);
        ui->orderedBtn->setChecked(false);
    }
}

void Edit_page::currentCharFormatChangedSlot(const QTextCharFormat &format)
{
    qDebug() << "currentCharFormatChangedSlot";
    fontChanged(format.font());
    // fontColorChanged((format.foreground().isOpaque()) ? format.foreground().color() : QColor());
    fontColorChanged(format.foreground().color());
}

void Edit_page::textChangedSlot()
{
    qDebug() << "emit textchange" << "note id" << m_noteId << this->id;
    emit texthasChanged(m_noteId, this->id);
}

//textedit右键菜单
void Edit_page::textRightMenu(QPoint)
{
    QMenu *m_rightMenu = new QMenu;

    //定义action
    QAction *undoact = new QAction(tr("undo"));
    QAction *redoact = new QAction(tr("redo"));
    QAction *cutact = new QAction(tr("cut"));
    QAction *copyact = new QAction(tr("copy"));
    QAction *pasteact = new QAction(tr("paste"));
    QAction *textfornew = new QAction(tr("copy to newpage"));

    undoact->setIcon(QIcon::fromTheme("edit-undo"));
    redoact->setIcon(QIcon::fromTheme("edit-redo"));
    cutact->setIcon(QIcon::fromTheme("edit-cut"));
    copyact->setIcon(QIcon::fromTheme("edit-copy"));
    pasteact->setIcon(QIcon::fromTheme("edit-paste"));
//    textfornew->setIcon(QIcon::fromTheme("add-files-to-archive"));
    textfornew->setIcon(QIcon(":/image/1x/copy_to_new_note.png"));
    //定义action end

    //action使能与非使能
    connect(ui->textEdit->document(), SIGNAL(undoAvailable(bool)),
            undoact, SLOT(setEnabled(bool)));
    connect(ui->textEdit->document(), SIGNAL(redoAvailable(bool)),
            redoact, SLOT(setEnabled(bool)));
    undoact->setEnabled(ui->textEdit->document()->isUndoAvailable());
    redoact->setEnabled(ui->textEdit->document()->isRedoAvailable());

    cutact->setEnabled(!ui->textEdit->textCursor().selectedText().isEmpty());
    copyact->setEnabled(!ui->textEdit->textCursor().selectedText().isEmpty());
    pasteact->setEnabled(!QApplication::clipboard()->text().isEmpty());
    connect(QApplication::clipboard(), &QClipboard::dataChanged, this, [=](){
        pasteact->setEnabled(!QApplication::clipboard()->text().isEmpty());
    });

    textfornew->setEnabled(!ui->textEdit->textCursor().selectedText().isEmpty());
    //action使能与非使能 end

    //action绑定槽函数
    connect(undoact, SIGNAL(triggered(bool)), ui->textEdit, SLOT(undo()));
    connect(redoact, SIGNAL(triggered(bool)), ui->textEdit, SLOT(redo()));

    connect(cutact, SIGNAL(triggered()), ui->textEdit, SLOT(cut()));
    connect(copyact, SIGNAL(triggered()), ui->textEdit, SLOT(copy()));
    connect(pasteact, SIGNAL(triggered(bool)), ui->textEdit, SLOT(paste()));

    connect(textfornew, SIGNAL(triggered()), this, SLOT(textForNewEditpageSlot()));
    //action绑定槽函数 end

    //action添加到menu
    m_rightMenu->addAction(undoact);
    m_rightMenu->addAction(redoact);
    m_rightMenu->addSeparator();         // 添加分割线

    m_rightMenu->addAction(cutact);
    m_rightMenu->addAction(copyact);
    m_rightMenu->addAction(pasteact);
    m_rightMenu->addSeparator();         // 添加分割线

    m_rightMenu->addAction(textfornew);
    //action添加到menu end

    m_rightMenu->move (cursor().pos());
    m_rightMenu->show();

}

//拷贝选中内容到新便签页
void Edit_page::textForNewEditpageSlot()
{
    if(!ui->textEdit->textCursor().selectedText().isEmpty())
    {
        ui->textEdit->copy();
        emit textForNewEditpageSig();
    }
}

// 加粗
void Edit_page::setBoldSlot()
{
    qDebug() << "setBoldSlot";
    QTextCharFormat fmt;
    fmt.setFontWeight(ui->boldBtn->isCheckable() ? QFont::Bold : QFont::Normal);

    QTextCursor cursor = ui->textEdit->textCursor();
    if (cursor.charFormat().fontWeight() == QFont::Bold) {
        qDebug() << "current cursor charFormat QFont::Bold";
        fmt.setFontWeight(QFont::Normal);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    } else {
        qDebug() << "current cursor charFormat QFont::Normal";
        fmt.setFontWeight(QFont::Bold);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }
}

// 斜体
void Edit_page::setItalicSlot()
{
    qDebug()<<"-------setItalicSlot------------";
    QTextCharFormat fmt;
    fmt.setFontItalic(ui->italicBtn->isCheckable());// ? QFont::StyleItalic : QFont::Normal);
    // mergeFormatOnWordOrSelection(fmt);

    QTextCursor cursor = ui->textEdit->textCursor();
    if (cursor.charFormat().fontItalic()) { // return boolProperty(FontItalic)
        fmt.setFontItalic(QFont::StyleNormal);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    } else {
        fmt.setFontItalic(QFont::StyleItalic);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }
}

// 划线
void Edit_page::setUnderlineSlot()
{
    qDebug() << "setUnderlineSlot";
    QTextCharFormat fmt;
    fmt.setFontUnderline(ui->underlineBtn->isCheckable());// ? QFont::UnderlineResolved : QFont::Normal );
    // mergeFormatOnWordOrSelection(fmt);

    QTextCursor cursor = ui->textEdit->textCursor();
    if (cursor.charFormat().fontUnderline()) { //
        fmt.setFontUnderline(QFont::StyleNormal);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    } else {
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }
}

// 除线
void Edit_page::setStrikeOutSlot()
{
    qDebug() << "setStrikeOutSlot";
    QTextCharFormat fmt;
    fmt.setFontStrikeOut(ui->strikeOutBtn->isCheckable());// ? QFont::StrikeOutResolved : QFont::Normal );
    // mergeFormatOnWordOrSelection(fmt);

    QTextCursor cursor = ui->textEdit->textCursor();
    if (cursor.charFormat().fontStrikeOut()) {
        fmt.setFontStrikeOut(QFont::StyleNormal);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    } else {
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }
}

// 无序列表
void Edit_page::setUnorderedListSlot(bool checked)
{
    qDebug() << "setUnorderedListSlot" << checked;
    if (checked) {
        ui->orderedBtn->setChecked(false);
        qDebug() << "show list set false" << checked;
        qDebug() << "text_edit_page->ui->orderedBtn is checked ? :" << ui->orderedBtn->isChecked();
    }
    list(checked, QTextListFormat::ListDisc);
    qDebug() << "text_edit_page->ui->orderedBtn is checked ? :" << ui->orderedBtn->isChecked();
}

// 序列表
void Edit_page::setOrderedListSlot(bool checked)
{
    qDebug() << "show num list";
    if (checked) {
        ui->unorderedBtn->setChecked(false);
    }
    list(checked, QTextListFormat::ListDecimal);
}

// 字号
void Edit_page::setFontSizeSlot()
{
    qDebug() << "setFontSizeSlot";
    int num = set_size_page->ui->listWidget->currentRow();
    ui->fontSizeBtn->setText(QString::number(num+10));
    set_size_page->close();

    QTextCharFormat fmt;
    fmt.setFontPointSize(num+10);
    mergeFormatOnWordOrSelection(fmt);
}

// 调色板
void Edit_page::initColor()
{
    color[0] = "background:rgba(76,119,231,1);";
    color[1] = "background:rgba(250,108,99,1);";
    color[2] = "background:rgba(15,161,90,1);";
    color[3] = "background:rgba(255,151,47,1);";
    color[4] = "background:rgba(186,123,216,1);";
    color[5] = "background:rgba(248,209,93,1);";
    color[6] = "background:rgba(42,162,217,1);";
    color[7] = "background:rgba(110,207,67,1);";
    color[8] = "background:rgba(144,101,255,1);";

    color_num[0] = QColor(76, 119, 231);
    color_num[1] = QColor(250, 108, 99);
    color_num[2] = QColor(15, 161, 90);
    color_num[3] = QColor(255, 151, 47);
    color_num[4] = QColor(186, 123, 216);
    color_num[5] = QColor(248, 209, 93);
    color_num[6] = QColor(42, 162, 217);
    color_num[7] = QColor(110, 207, 67);
    color_num[8] = QColor(144, 101, 255);
}

void Edit_page::setFontColorSlot()
{
    qDebug() << "setFontColorSlot";
    int num = set_color_fort_page->ui->listWidget->currentRow();

    QTextCharFormat fmt;
    if (num != 9) {
        fmt.setForeground(color_num[num]);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    } else {
        defaultFontColorChanged = true;
        fmt.setForeground(palette().color(QPalette::Text));
        // fmt.clearForeground();
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }
    set_color_fort_page->close();
}

void Edit_page::blueBtnSlot()
{
    m_editColor = QColor(76, 119, 231);
    emit colorhasChanged(m_editColor, m_noteId);
    m_noteHead->color_widget = QColor(76, 119, 231);
    m_noteHeadMenu->color_widget = QColor(76, 119, 231);
    update();
}

void Edit_page::redBtnSlot()
{
    m_editColor = QColor(255, 108, 99);
    emit colorhasChanged(m_editColor, m_noteId);
    m_noteHead->color_widget = QColor(250, 108, 99);
    m_noteHeadMenu->color_widget = QColor(250, 108, 99);

    // QString _BgColor = m_editColor.name();
    // QString _Stylesheet = "background-color: %1;";
    // _Stylesheet = _Stylesheet.arg(_BgColor);
    // m_noteHeadMenu->ui->pushButtonExit->setStyleSheet(_Stylesheet);
    update();
}

void Edit_page::darkGreenBtnSlot()
{
    m_editColor = QColor(15, 161, 90);
    emit colorhasChanged(m_editColor, m_noteId);
    m_noteHead->color_widget = QColor(15, 161, 90);
    m_noteHeadMenu->color_widget = QColor(15, 161, 90);
    update();
}

void Edit_page::orangeBtnSlot()
{
    m_editColor = QColor(255, 151, 47);
    emit colorhasChanged(m_editColor, m_noteId);
    m_noteHead->color_widget = QColor(255, 151, 47);
    m_noteHeadMenu->color_widget = QColor(255, 151, 47);
    update();
}

void Edit_page::purpleBtnSlot()
{
    m_editColor = QColor(186, 123, 216);
    emit colorhasChanged(m_editColor, m_noteId);
    m_noteHead->color_widget = QColor(186, 123, 216);
    m_noteHeadMenu->color_widget = QColor(186, 123, 216);
    update();
}

void Edit_page::goldenBtnSlot()
{
    m_editColor = QColor(248, 209, 93);
    emit colorhasChanged(m_editColor, m_noteId);
    m_noteHead->color_widget = QColor(248, 209, 93);
    m_noteHeadMenu->color_widget = QColor(248, 209, 93);
    update();
}

void Edit_page::lightBlueBtnSlot()
{
    m_editColor = QColor(42, 162, 217);
    emit colorhasChanged(m_editColor, m_noteId);
    m_noteHead->color_widget = QColor(42, 162, 217);
    m_noteHeadMenu->color_widget = QColor(42, 162, 217);
    update();
}

void Edit_page::lightGreenBtnSlot()
{
    m_editColor = QColor(110, 207, 67);
    emit colorhasChanged(m_editColor, m_noteId);
    m_noteHead->color_widget = QColor(110, 207, 67);
    m_noteHeadMenu->color_widget = QColor(110, 207, 67);
    update();
}

void Edit_page::yellowBtnSlot()
{
    m_editColor = QColor(144, 101, 255);
    emit colorhasChanged(m_editColor, m_noteId);
    m_noteHead->color_widget = QColor(144, 101, 255);
    m_noteHeadMenu->color_widget = QColor(144, 101, 255);
    update();
}

void Edit_page::pinkBtnSlot()
{
    m_editColor = QColor(245, 80, 159);
    emit colorhasChanged(m_editColor, m_noteId);
    m_noteHead->color_widget = QColor(245, 80, 159);
    m_noteHeadMenu->color_widget = QColor(245, 80, 159);
    update();
}

void Edit_page::defaultBtnSlot()
{
    if (pNotebook->m_isThemeChanged) {
        qDebug() << "白色便签头";
        m_editColor = QColor(255, 255, 255);
        m_noteHead->color_widget = QColor(255, 255, 255);
        m_noteHeadMenu->color_widget = QColor(255, 255, 255);
        m_noteHeadMenu->ui->pushButtonExit->setIcon(QPixmap(":/image/1x/close_block.png"));
        m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20, 20));
        m_noteHeadMenu->ui->pushButtonMenu->setIcon(QPixmap(":/image/1x/more_block.png"));
        m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20, 20));
        m_noteHeadMenu->ui->pushButtonPalette->setIcon(QPixmap(":/image/1x/more_block.png"));
        m_noteHeadMenu->ui->pushButtonPalette->setIconSize(QSize(20, 20));

        QString _Stylesheet;
        QString _BgColor;
        _BgColor = m_editColor.name();
        _Stylesheet = "background-color: %1;";
        _Stylesheet = _Stylesheet.arg(_BgColor);
        m_noteHeadMenu->ui->pushButtonExit->setStyleSheet(_Stylesheet);
        m_noteHeadMenu->ui->pushButtonMenu->setStyleSheet(_Stylesheet);
        m_noteHeadMenu->ui->pushButtonPalette->setStyleSheet(_Stylesheet);
    } else {
        qDebug() << "黑色便签头";
        m_editColor = QColor(0, 0, 0);
        m_noteHead->color_widget = QColor(0, 0, 0);
        m_noteHeadMenu->color_widget = QColor(0, 0, 0);
        m_noteHeadMenu->ui->pushButtonExit->setIcon(QPixmap(":/image/1x/close_block.png"));
        m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20, 20));
        m_noteHeadMenu->ui->pushButtonMenu->setIcon(QPixmap(":/image/1x/more_block.png"));
        m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20, 20));
        m_noteHeadMenu->ui->pushButtonPalette->setIcon(QPixmap(":/image/1x/more_block.png"));
        m_noteHeadMenu->ui->pushButtonPalette->setIconSize(QSize(20, 20));

        QString _Stylesheet;
        QString _BgColor;
        QString _Color;
        _BgColor = m_editColor.name();
        _Color = QColor(19, 20, 20, 0).name();
        _Stylesheet = "background-color: %1; color: %2;";
        _Stylesheet = _Stylesheet.arg(_BgColor).arg(_Color);
        m_noteHeadMenu->ui->pushButtonExit->setStyleSheet(_Stylesheet);
        m_noteHeadMenu->ui->pushButtonMenu->setStyleSheet(_Stylesheet);
        m_noteHeadMenu->ui->pushButtonPalette->setStyleSheet(_Stylesheet);
    }

    emit colorhasChanged(m_editColor, m_noteId);
    update();
}

void Edit_page::showFullScreenSlot()
{
    if (!m_isFullscreen) {
        this->showFullScreen();
        m_isFullscreen = true;
    } else {
        this->showNormal();
        m_isFullscreen = false;
    }
}

void Edit_page::setStayOnTopSlot(bool b)
{
    //m_ignoreShowHideEvents = true;

    bool visible = isVisible();
    QPoint old_pos = pos();

    Display *display = QX11Info::display();
    XEvent event;
    event.xclient.type = ClientMessage;
    event.xclient.serial = 0;
    event.xclient.send_event = True;
    event.xclient.display = display;
    event.xclient.window = winId();
    event.xclient.message_type = XInternAtom(display, "_NET_WM_STATE", False);
    event.xclient.format = 32;

    event.xclient.data.l[0] = b;
    event.xclient.data.l[1] = XInternAtom(display, "_NET_WM_STATE_ABOVE", False);
    event.xclient.data.l[2] = 0;
    event.xclient.data.l[3] = 0;
    event.xclient.data.l[4] = 0;

    XSendEvent(display, DefaultRootWindow(display), False,
               SubstructureRedirectMask|SubstructureNotifyMask, &event);

    move(old_pos);

    if (visible) {
        show();
    }

    //m_ignoreShowHideEvents = false;
}


