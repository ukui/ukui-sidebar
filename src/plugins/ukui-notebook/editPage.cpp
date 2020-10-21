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
#include <QDebug>

#include "ui_textEditing.h"
#include "setFontSizePage.h"
#include "ui_setFontSizePage.h"
#include "setFontColorPage.h"
#include "ui_setFontColorPage.h"
#include "ui_selectColorPage.h"
#include "noteHead.h"
#include "widget.h"
#include "ui_widget.h"
#include "editPage.h"
#include "ui_editPage.h"

extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);

Edit_page::Edit_page(Widget* page, int noteId, QWidget *parent) :
    QWidget(parent)
  , ui(new Ui::Edit_page)
  , m_editColor(0,0,0)
  , m_noteId(noteId)
  , m_lastBlockList(0)
  , mousePressed(false)
  , defaultStyle(true)
  , pNotebook(page)
  , color_page(new select_color_page(pNotebook))
  , text_edit_page(new Text_editing(pNotebook))
{
    ui->setupUi(this);
    initSetup();
    slotsSetup();
//    listenToGsettings();
}

Edit_page::~Edit_page()
{
    delete ui;
}

void Edit_page::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->dragPosition = event->globalPos() - frameGeometry().topLeft();
        this->mousePressed = true;
    }
    QWidget::mousePressEvent(event);
}

void Edit_page::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->mousePressed = false;
    }
    QWidget::mouseReleaseEvent(event);
}

void Edit_page::mouseMoveEvent(QMouseEvent *event)
{
    if (this->mousePressed) {
        move(event->globalPos() - this->dragPosition);
    }
    QWidget::mouseMoveEvent(event);
}

void Edit_page::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;

    QPainterPath rectPath;
    rectPath.addRoundedRect(this->rect().adjusted(1, 1, -1, -1), 6, 6);

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

void Edit_page::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_noteHead->hide();
    m_noteHeadMenu->show();
}

void Edit_page::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_noteHeadMenu->hide();
    m_noteHead->show();
}

void Edit_page::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
    QMenu * menu = new QMenu(this);
    menu->resize(50,20);
    if(!pNotebook->m_isThemeChanged)
    {
        menu->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
                                              "background:rgb(255,255,255);\n"
                                              ""));
    }else{

        menu->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
                                              "background:rgb(19,20,20);\n"
                                              ""));
    }
#if (QT_VERSION >= QT_VERSION_CHECK(5,12,0))
    QAction * delete_the_widget = new QAction(tr("Close"));
    delete_the_widget->setIcon(QIcon(":/image/1x/delete.png"));
    QAction * t3 = new QAction(tr("Open Notepad"));
    t3->setIcon(QIcon(":/image/1x/open_note-book.png"));
//    connect(delete_the_widget, SIGNAL(triggered()), this, SLOT(closeSlot()));
//    connect(t3, SIGNAL(triggered()), this, SLOT(show_note_page()));
    menu->addAction(delete_the_widget);
    menu->addAction(t3);
//    QAction * t1 = new QAction(tr("New"));
//    t1->setIcon(QIcon(":/image/1x/sourch.png"));
//    connect(t1, SIGNAL(triggered()), this, SLOT(add_new_page()));
//    menu->addAction(t1);
    menu->move(cursor().pos()); //让菜单显示的位置在鼠标的坐标上
    //menu->show();
#endif
}

void Edit_page::initSetup()
{
    //标题
    this->setWindowTitle(tr("ukui-memo"));
    //任务栏图标
    setWindowIcon(QIcon::fromTheme("kylin-notebook"));

    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.setRenderHint(QPainter::Antialiasing);
    p.drawRoundedRect(bmp.rect(),6,6);
    setMask(bmp);

    setWindowOpacity(0.9);
    setWindowFlags(Qt::FramelessWindowHint);
    // 配置按钮
    btnSetup();
    initColor();
    // 获取字体按钮状态
    fontChanged(ui->textEdit->font());

    m_noteHead = new noteHead(this);
    m_noteHeadMenu = new noteHeadMenu(this);

    m_noteHead->move(0,0);
    m_noteHeadMenu->move(0,0);
    m_noteHead->show();
    m_noteHeadMenu->hide();

    ui->textEdit->setFrameShape(QFrame::NoFrame);
    ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 禁用右键菜单
    ui->textEdit->setContextMenuPolicy(Qt::NoContextMenu);
//    ui->textEdit->setFontPointSize(14);
}

void Edit_page::btnSetup()
{
    ui->formatBtn->setIcon(QPixmap(":/image/1x/adjustment.png"));
    ui->formatBtn->setIconSize(QSize(36,36));
    ui->paletteBtn->setIcon(QPixmap(":/image/1x/note_color.png"));
    ui->paletteBtn->setIconSize(QSize(36,36));
    QPalette palette = ui->paletteBtn->palette();
    QColor ColorPlaceholderText(255,255,255,0);
    QBrush brush;
    brush.setColor(ColorPlaceholderText);
    palette.setBrush(QPalette::Button, brush);
    palette.setBrush(QPalette::ButtonText, brush);
    //palette.setColor(QPalette::Highlight, Qt::transparent); /* 取消按钮高亮 */
    ui->paletteBtn->setPalette(palette);
    ui->formatBtn->setPalette(palette);
    ui->paletteBtn->setProperty("useIconHighlightEffect", true);
    ui->paletteBtn->setProperty("iconHighlightEffectMode", 1);
    ui->formatBtn->setProperty("useIconHighlightEffect", true);
    ui->formatBtn->setProperty("iconHighlightEffectMode", 1);
}

void Edit_page::slotsSetup()
{
    connect(m_noteHeadMenu->ui->pushButtonExit, &QPushButton::clicked, this, [=](){
        this->close();
    });
    connect(ui->textEdit,&QTextEdit::textChanged,this,&Edit_page::textChangedSlot);
    // 调色板菜单
    connect(ui->paletteBtn, &QPushButton::clicked, this, [=](){
        QPointF position = this->pos();
        color_page->move(position.x(),position.y()+224);
        color_page->show();
    });
    // 格式菜单
    connect(ui->formatBtn, &QPushButton::clicked, this, [=](){
        QPointF position = this->pos();
        //QPointF position = parentWidget()->pos();
        text_edit_page->move(position.x(),position.y()+224);
        text_edit_page->show();
    });
    // 调色按钮
    connect(color_page->paletteWidget->ui->blueBtn, &QPushButton::clicked, this, &Edit_page::blueBtnSlot);
    connect(color_page->paletteWidget->ui->redBtn, &QPushButton::clicked, this, &Edit_page::redBtnSlot);
    connect(color_page->paletteWidget->ui->darkGreenBtn, &QPushButton::clicked, this, &Edit_page::darkGreenBtnSlot);
    connect(color_page->paletteWidget->ui->orangeBtn, &QPushButton::clicked, this, &Edit_page::orangeBtnSlot);
    connect(color_page->paletteWidget->ui->purpleBtn, &QPushButton::clicked, this, &Edit_page::purpleBtnSlot);
    connect(color_page->paletteWidget->ui->goldenBtn, &QPushButton::clicked, this, &Edit_page::goldenBtnSlot);
    connect(color_page->paletteWidget->ui->lightBlueBtn, &QPushButton::clicked, this, &Edit_page::lightBlueBtnSlot);
    connect(color_page->paletteWidget->ui->lightGreenBtn, &QPushButton::clicked, this, &Edit_page::lightGreenBtnSlot);
    connect(color_page->paletteWidget->ui->yellowBtn, &QPushButton::clicked, this, &Edit_page::yellowBtnSlot);
    connect(color_page->paletteWidget->ui->pinkBtn, &QPushButton::clicked, this, &Edit_page::pinkBtnSlot);
    // 字体颜色大小
    connect(text_edit_page->set_size_page->ui->listWidget, &QListWidget::itemClicked, this, &Edit_page::setFontSizeSlot);
    connect(text_edit_page->set_color_fort_page->ui->listWidget, &QListWidget::itemClicked, this, &Edit_page::setFontColorSlot);
    // 文本格式
    connect(text_edit_page->texteditwidget->ui->boldBtn, &QPushButton::clicked, this, &Edit_page::setBoldSlot);
    connect(text_edit_page->texteditwidget->ui->italicBtn, &QPushButton::clicked, this, &Edit_page::setItalicSlot);
    connect(text_edit_page->texteditwidget->ui->underlineBtn, &QPushButton::clicked, this, &Edit_page::setUnderlineSlot);
    connect(text_edit_page->texteditwidget->ui->strikeOutBtn, &QPushButton::clicked, this, &Edit_page::setStrikeOutSlot);
    connect(text_edit_page->texteditwidget->ui->unorderedBtn, &QPushButton::clicked, this, &Edit_page::setUnorderedListSlot);
    connect(text_edit_page->texteditwidget->ui->orderedBtn, &QPushButton::clicked, this, &Edit_page::setOrderedListSlot);
    connect(ui->textEdit, &QTextEdit::cursorPositionChanged, this, &Edit_page::cursorPositionChangedSlot);
    connect(ui->textEdit, &QTextEdit::currentCharFormatChanged, this, &Edit_page::currentCharFormatChangedSlot);
}

void Edit_page::listenToGsettings()
{
    qDebug() << "Edit_page::listenToGsettings";
    //监听主题改变
    const QByteArray id(THEME_QT_SCHEMA);
    if(QGSettings::isSchemaInstalled(id)){
        QGSettings *styleSettings = new QGSettings(id);
        auto style = styleSettings->get(MODE_QT_KEY).toString();
        if(style == "ukui-default"){
//            QPalette palette = color_page->paletteWidget->ui->pinkBtn->palette();
//            palette.setBrush(QPalette::Button, QColor(0,0,0));
//            color_page->paletteWidget->ui->pinkBtn->setPalette(palette);
            color_page->paletteWidget->ui->pinkBtn->setStyleSheet("background:rgba(0,0,0,1);"
                                                                     "border-radius:2px;");
        }else if(style == "ukui-dark"){
            color_page->paletteWidget->ui->pinkBtn->setStyleSheet("background:rgba(255,255,255,1);"
                                                                     "border-radius:2px;");
        }
        qDebug() << "Edit_page::listenToGsettings 当前主题名:" << style;
        connect(styleSettings, &QGSettings::changed, this, [=](const QString &key){
            qDebug() << "当前主题改变" << key;
            if (key == "styleName"){
                QString currentTheme = styleSettings->get(MODE_QT_KEY).toString();
                qDebug() << "currentTheme" << currentTheme;
                if(currentTheme == "ukui-default"){
                    qDebug() << "styleSettings changed ukui-default";
                    color_page->paletteWidget->ui->pinkBtn->setStyleSheet("background:rgba(0,0,0,1);"
                                                                             "border-radius:2px;");
                }else if(currentTheme == "ukui-dark"){
                    qDebug() << "styleSettings changed ukui-dark";
                    color_page->paletteWidget->ui->pinkBtn->setStyleSheet("background:rgba(255,255,255,1);"
                                                                             "border-radius:2px;");
                }
            }
        });
    }

    const QByteArray idd(PERSONALISE_SCHEMA);

    if(QGSettings::isSchemaInstalled(idd))
    {
        QGSettings *opacitySettings = new QGSettings(idd);
        connect(opacitySettings,&QGSettings::changed, this, [=](const QString &key){
            if(key == "transparency"){
                QStringList keys = opacitySettings->keys();
                if (keys.contains("transparency")){
                    double m_transparency = opacitySettings->get("transparency").toDouble();
                }
            }
            repaint();
        });
        double m_transparency = opacitySettings->get("transparency").toDouble();
    }
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
    qDebug() << "font Changed" << f.pointSize();
    text_edit_page->set_size_page->ui->listWidget->setCurrentRow(f.pointSize() - 10);
    text_edit_page->texteditwidget->ui->fontSizeBtn->setText(QString::number(f.pointSize()));
    text_edit_page->texteditwidget->ui->boldBtn->setChecked(f.bold());
    text_edit_page->texteditwidget->ui->italicBtn->setChecked(f.italic());
    text_edit_page->texteditwidget->ui->underlineBtn->setChecked(f.underline());
    text_edit_page->texteditwidget->ui->strikeOutBtn->setChecked(f.strikeOut());

    if (ui->textEdit->textCursor().currentList()) {
        QTextListFormat lfmt = ui->textEdit->textCursor().currentList()->format();
        if (lfmt.style() == QTextListFormat::ListDisc) {
            text_edit_page->texteditwidget->ui->unorderedBtn->setChecked(true);
            text_edit_page->texteditwidget->ui->orderedBtn->setChecked(false);
          } else if (lfmt.style() == QTextListFormat::ListDecimal) {
            text_edit_page->texteditwidget->ui->unorderedBtn->setChecked(false);
            text_edit_page->texteditwidget->ui->orderedBtn->setChecked(true);
          } else {
            text_edit_page->texteditwidget->ui->unorderedBtn->setChecked(false);
            text_edit_page->texteditwidget->ui->orderedBtn->setChecked(false);
            }
      } else {
        text_edit_page->texteditwidget->ui->unorderedBtn->setChecked(false);
        text_edit_page->texteditwidget->ui->orderedBtn->setChecked(false);
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

    text_edit_page->texteditwidget->ui->fontColorBtn->setStyleSheet(_Stylesheet +"border-radius:3px;");
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
        cursor.createList(listFmt);
        }
    cursor.endEditBlock();
}

/**************** Slots *******************/

void Edit_page::cursorPositionChangedSlot()
{
    qDebug() << "cursorPositionChangedSlot";
    QTextList *l = ui->textEdit->textCursor().currentList();
    if (m_lastBlockList && (l == m_lastBlockList || (l != 0 && m_lastBlockList != 0
                                                     && l->format().style() == m_lastBlockList->format().style()))) {
        return;
    }
    m_lastBlockList = l;
    if (l) {
        QTextListFormat lfmt = l->format();
        if (lfmt.style() == QTextListFormat::ListDisc) {
            text_edit_page->texteditwidget->ui->unorderedBtn->setChecked(true);
            text_edit_page->texteditwidget->ui->orderedBtn->setChecked(false);
        } else if (lfmt.style() == QTextListFormat::ListDecimal) {
            text_edit_page->texteditwidget->ui->unorderedBtn->setChecked(false);
            text_edit_page->texteditwidget->ui->orderedBtn->setChecked(true);
        } else {
            text_edit_page->texteditwidget->ui->unorderedBtn->setChecked(false);
            text_edit_page->texteditwidget->ui->orderedBtn->setChecked(false);
        }
    } else {
        text_edit_page->texteditwidget->ui->unorderedBtn->setChecked(false);
        text_edit_page->texteditwidget->ui->orderedBtn->setChecked(false);
    }
}

void Edit_page::currentCharFormatChangedSlot(const QTextCharFormat &format)
{
    qDebug() << "currentCharFormatChangedSlot";
    fontChanged(format.font());
    fontColorChanged((format.foreground().isOpaque()) ? format.foreground().color() : QColor());
}

void Edit_page::textChangedSlot()
{
    qDebug() << "emit textchange";
    emit texthasChanged(m_noteId, this->id);
}

//加粗
void Edit_page::setBoldSlot()
{
    qDebug() << "setBoldSlot";
    QTextCharFormat fmt;
    fmt.setFontWeight(text_edit_page->texteditwidget->ui->boldBtn->isCheckable() ? QFont::Bold : QFont::Normal);
//    mergeFormatOnWordOrSelection(fmt);
    QTextCursor cursor = ui->textEdit->textCursor();
    if (!cursor.hasSelection()){
        cursor.select(QTextCursor::WordUnderCursor);
    }
    if(cursor.charFormat().fontWeight() == QFont::Bold)
    {
        qDebug() << "current cursor charFormat QFont::Bold";
        fmt.setFontWeight(QFont::Normal);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }else{
        qDebug() << "current cursor charFormat QFont::Normal";
        fmt.setFontWeight(QFont::Bold);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }
}

//斜体
void Edit_page::setItalicSlot()
{
    qDebug()<<"-------setItalicSlot------------";
    QTextCharFormat fmt;
    fmt.setFontItalic(text_edit_page->texteditwidget->ui->italicBtn->isCheckable());// ? QFont::StyleItalic : QFont::Normal);
//    mergeFormatOnWordOrSelection(fmt);

    QTextCursor cursor = ui->textEdit->textCursor();
    if(cursor.charFormat().fontItalic())  //return boolProperty(FontItalic)
    {
        fmt.setFontItalic(QFont::StyleNormal);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }else{
        fmt.setFontItalic(QFont::StyleItalic);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }
}

//下划线
void Edit_page::setUnderlineSlot()
{
    qDebug() << "setUnderlineSlot";
    QTextCharFormat fmt;
    fmt.setFontUnderline(text_edit_page->texteditwidget->ui->underlineBtn->isCheckable());// ? QFont::UnderlineResolved : QFont::Normal );
//    mergeFormatOnWordOrSelection(fmt);

    QTextCursor cursor = ui->textEdit->textCursor();
    if(cursor.charFormat().fontUnderline())  //
    {
        fmt.setFontUnderline(QFont::StyleNormal);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }else{
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }
}

//删除线
void Edit_page::setStrikeOutSlot()
{
    qDebug() << "setStrikeOutSlot";
    QTextCharFormat fmt;
    fmt.setFontStrikeOut(text_edit_page->texteditwidget->ui->strikeOutBtn->isCheckable());// ? QFont::StrikeOutResolved : QFont::Normal );
//    mergeFormatOnWordOrSelection(fmt);

    QTextCursor cursor = ui->textEdit->textCursor();
    if(cursor.charFormat().fontStrikeOut())
    {
        fmt.setFontStrikeOut(QFont::StyleNormal);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }else{
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }
}

//无序列表
void Edit_page::setUnorderedListSlot(bool checked)
{
    qDebug() << "setUnorderedListSlot" << checked;
    if(checked)
    {
        text_edit_page->texteditwidget->ui->orderedBtn->setChecked(false);
        qDebug() << "show list set false" << checked;
        qDebug() << "text_edit_page->ui->orderedBtn is checked ? :" << text_edit_page->texteditwidget->ui->orderedBtn->isChecked();
    }
    list(checked, QTextListFormat::ListDisc);
    qDebug() << "text_edit_page->ui->orderedBtn is checked ? :" << text_edit_page->texteditwidget->ui->orderedBtn->isChecked();
}

//有序列表
void Edit_page::setOrderedListSlot(bool checked)
{
    qDebug() << "show num list";
    if (checked) {
        text_edit_page->texteditwidget->ui->unorderedBtn->setChecked(false);
        }
    list(checked, QTextListFormat::ListDecimal);
}

//字号
void Edit_page::setFontSizeSlot()
{
    qDebug() << "setFontSizeSlot";
    int num = text_edit_page->set_size_page->ui->listWidget->currentRow();
    text_edit_page->texteditwidget->ui->fontSizeBtn->setText(QString::number(num+10));
    text_edit_page->set_size_page->close();

    QTextCharFormat fmt;
    fmt.setFontPointSize(num+10);
    mergeFormatOnWordOrSelection(fmt);
}

//调色板
void Edit_page::initColor()
{
    color[0]="background:rgba(76,119,231,1);";
    color[1]="background:rgba(250,108,99,1);";
    color[2]="background:rgba(15,161,90,1);";
    color[3]="background:rgba(255,151,47,1);";
    color[4]="background:rgba(186,123,216,1);";
    color[5]="background:rgba(248,209,93,1);";
    color[6]="background:rgba(42,162,217,1);";
    color[7]="background:rgba(110,207,67,1);";
    color[8]="background:rgba(250,243,175,1);";

    color_num[0]=QColor(76,119,231);
    color_num[1]=QColor(250,108,99);
    color_num[2]=QColor(15,161,90);
    color_num[3]=QColor(255,151,47);
    color_num[4]=QColor(186,123,216);
    color_num[5]=QColor(248,209,93);
    color_num[6]=QColor(42,162,217);
    color_num[7]=QColor(110,207,67);
    color_num[8]=QColor(250,243,175);
    color_num[9]=QColor(0,0,0);

    //监听主题改变
    const QByteArray id(THEME_QT_SCHEMA);
    if(QGSettings::isSchemaInstalled(id)){
        QGSettings *styleSettings = new QGSettings(id);
        QString style = styleSettings->get(MODE_QT_KEY).toString();
        if(style == "ukui-default"){
            color[9]="background:rgba(0,0,0,1);";
        }else {
            color[9]="background:rgba(255,255,255,1);";
        }
        text_edit_page->texteditwidget->ui->fontColorBtn->setStyleSheet(color[9]+"border-radius:3px;");
        connect(styleSettings, &QGSettings::changed, this, [=](const QString &key){
            if (key == "styleName"){
                QString currentTheme = styleSettings->get(MODE_QT_KEY).toString();
                if(currentTheme == "ukui-default"){
                    color[9]="background:rgba(0,0,0,1);";
                }else if(currentTheme == "ukui-dark"){
                    color[9]="background:rgba(255,255,255,1);";
                }
            }
            if(defaultStyle){
                text_edit_page->texteditwidget->ui->fontColorBtn->setStyleSheet(color[9]+"border-radius:3px;");
            }
        });
    }
}

void Edit_page::setFontColorSlot ()
{
    qDebug() << "setFontColorSlot";
    int num = text_edit_page->set_color_fort_page->ui->listWidget->currentRow();
    text_edit_page->texteditwidget->ui->fontColorBtn->setStyleSheet(color[num]+"border-radius:3px;");

    QTextCharFormat fmt;
    if(num != 9){
        defaultStyle = false;
        fmt.setForeground(color_num[num]);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }else {
        defaultStyle = true;
        fmt.setForeground(palette().color(QPalette::Text));
//        fmt.clearForeground();
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }
    text_edit_page->set_color_fort_page->close();
}

void Edit_page::blueBtnSlot()
{
    m_editColor = QColor(76,119,231);
    emit colorhasChanged(m_editColor,m_noteId);
    m_noteHead->color_widget = QColor(76,119,231);
    m_noteHeadMenu->color_widget = QColor(76,119,231);
    QString _Stylesheet;
    QString _BgColor;
    _BgColor = m_editColor.name();
    _Stylesheet = "background-color: %1;";
    _Stylesheet = _Stylesheet.arg(_BgColor);
    m_noteHeadMenu->ui->pushButtonExit->setStyleSheet(_Stylesheet);
    m_noteHeadMenu->ui->pushButtonMenu->setStyleSheet(_Stylesheet);
    m_noteHeadMenu->ui->pushButtonExit->setIcon(QPixmap(":/image/1x/close_block.png"));
    m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
    m_noteHeadMenu->ui->pushButtonMenu->setIcon(QPixmap(":/image/1x/more_block.png"));
    m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));
    update();
}

void Edit_page::redBtnSlot()
{
    m_editColor = QColor(250,108,99);
    emit colorhasChanged(m_editColor,m_noteId);
    m_noteHead->color_widget = QColor(250,108,99);
    m_noteHeadMenu->color_widget = QColor(250,108,99);
    QString _Stylesheet;
    QString _BgColor;
    _BgColor = m_editColor.name();
    _Stylesheet = "background-color: %1;";
    _Stylesheet = _Stylesheet.arg(_BgColor);
    m_noteHeadMenu->ui->pushButtonExit->setStyleSheet(_Stylesheet);
    m_noteHeadMenu->ui->pushButtonMenu->setStyleSheet(_Stylesheet);
    m_noteHeadMenu->ui->pushButtonExit->setIcon(QPixmap(":/image/1x/close_block.png"));
    m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
    m_noteHeadMenu->ui->pushButtonMenu->setIcon(QPixmap(":/image/1x/more_block.png"));
    m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));
    update();
}

void Edit_page::darkGreenBtnSlot()
{
    m_editColor = QColor(15,161,90);
    emit colorhasChanged(m_editColor,m_noteId);
    m_noteHead->color_widget =QColor(15,161,90);
    m_noteHeadMenu->color_widget =QColor(15,161,90);
    QString _Stylesheet;
    QString _BgColor;
    _BgColor = m_editColor.name();
    _Stylesheet = "background-color: %1;";
    _Stylesheet = _Stylesheet.arg(_BgColor);
    m_noteHeadMenu->ui->pushButtonExit->setStyleSheet(_Stylesheet);
    m_noteHeadMenu->ui->pushButtonMenu->setStyleSheet(_Stylesheet);
    m_noteHeadMenu->ui->pushButtonExit->setIcon(QPixmap(":/image/1x/close_block.png"));
    m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
    m_noteHeadMenu->ui->pushButtonMenu->setIcon(QPixmap(":/image/1x/more_block.png"));
    m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));
    update();
}

void Edit_page::orangeBtnSlot()
{
    m_editColor = QColor(255,151,47);
    emit colorhasChanged(m_editColor,m_noteId);
    m_noteHead->color_widget =QColor(255,151,47);
    m_noteHeadMenu->color_widget =QColor(255,151,47);
    QString _Stylesheet;
    QString _BgColor;
    _BgColor = m_editColor.name();
    _Stylesheet = "background-color: %1;";
    _Stylesheet = _Stylesheet.arg(_BgColor);
    m_noteHeadMenu->ui->pushButtonExit->setStyleSheet(_Stylesheet);
    m_noteHeadMenu->ui->pushButtonMenu->setStyleSheet(_Stylesheet);
    m_noteHeadMenu->ui->pushButtonExit->setIcon(QPixmap(":/image/1x/close_block.png"));
    m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
    m_noteHeadMenu->ui->pushButtonMenu->setIcon(QPixmap(":/image/1x/more_block.png"));
    m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));
    update();
}

void Edit_page::purpleBtnSlot()
{
    m_editColor = QColor(186,123,216);
    emit colorhasChanged(m_editColor,m_noteId);
    m_noteHead->color_widget = QColor(186,123,216);
    m_noteHeadMenu->color_widget = QColor(186,123,216);
    QString _Stylesheet;
    QString _BgColor;
    _BgColor = m_editColor.name();
    _Stylesheet = "background-color: %1;";
    _Stylesheet = _Stylesheet.arg(_BgColor);
    m_noteHeadMenu->ui->pushButtonExit->setStyleSheet(_Stylesheet);
    m_noteHeadMenu->ui->pushButtonMenu->setStyleSheet(_Stylesheet);
    m_noteHeadMenu->ui->pushButtonExit->setIcon(QPixmap(":/image/1x/close_block.png"));
    m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
    m_noteHeadMenu->ui->pushButtonMenu->setIcon(QPixmap(":/image/1x/more_block.png"));
    m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));
    update();
}

void Edit_page::goldenBtnSlot()
{
    m_editColor = QColor(248,209,93);
    emit colorhasChanged(m_editColor,m_noteId);
    m_noteHead->color_widget = QColor(248,209,93);
    m_noteHeadMenu->color_widget = QColor(248,209,93);
    QString _Stylesheet;
    QString _BgColor;
    _BgColor = m_editColor.name();
    _Stylesheet = "background-color: %1;";
    _Stylesheet = _Stylesheet.arg(_BgColor);
    m_noteHeadMenu->ui->pushButtonExit->setStyleSheet(_Stylesheet);
    m_noteHeadMenu->ui->pushButtonMenu->setStyleSheet(_Stylesheet);
    m_noteHeadMenu->ui->pushButtonExit->setIcon(QPixmap(":/image/1x/close_block.png"));
    m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
    m_noteHeadMenu->ui->pushButtonMenu->setIcon(QPixmap(":/image/1x/more_block.png"));
    m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));
    update();
}

void Edit_page::lightBlueBtnSlot()
{
    m_editColor = QColor(42,162,217);
    emit colorhasChanged(m_editColor,m_noteId);
    m_noteHead->color_widget = QColor(42,162,217);
    m_noteHeadMenu->color_widget = QColor(42,162,217);
    QString _Stylesheet;
    QString _BgColor;
    _BgColor = m_editColor.name();
    _Stylesheet = "background-color: %1;";
    _Stylesheet = _Stylesheet.arg(_BgColor);
    m_noteHeadMenu->ui->pushButtonExit->setStyleSheet(_Stylesheet);
    m_noteHeadMenu->ui->pushButtonMenu->setStyleSheet(_Stylesheet);
    m_noteHeadMenu->ui->pushButtonExit->setIcon(QPixmap(":/image/1x/close_block.png"));
    m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
    m_noteHeadMenu->ui->pushButtonMenu->setIcon(QPixmap(":/image/1x/more_block.png"));
    m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));
    update();
}

void Edit_page::lightGreenBtnSlot()
{
    m_editColor = QColor(110,207,67);
    emit colorhasChanged(m_editColor,m_noteId);
    m_noteHead->color_widget = QColor(110,207,67);
    m_noteHeadMenu->color_widget = QColor(110,207,67);
    QString _Stylesheet;
    QString _BgColor;
    _BgColor = m_editColor.name();
    _Stylesheet = "background-color: %1;";
    _Stylesheet = _Stylesheet.arg(_BgColor);
    m_noteHeadMenu->ui->pushButtonExit->setStyleSheet(_Stylesheet);
    m_noteHeadMenu->ui->pushButtonMenu->setStyleSheet(_Stylesheet);
    m_noteHeadMenu->ui->pushButtonExit->setIcon(QPixmap(":/image/1x/close_block.png"));
    m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
    m_noteHeadMenu->ui->pushButtonMenu->setIcon(QPixmap(":/image/1x/more_block.png"));
    m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));
    update();
}

void Edit_page::yellowBtnSlot()
{
    m_editColor = QColor(250,243,175);
    emit colorhasChanged(m_editColor,m_noteId);
    m_noteHead->color_widget = QColor(250,243,175);
    m_noteHeadMenu->color_widget = QColor(250,243,175);
    QString _Stylesheet;
    QString _BgColor;
    _BgColor = m_editColor.name();
    _Stylesheet = "background-color: %1;";
    _Stylesheet = _Stylesheet.arg(_BgColor);
    m_noteHeadMenu->ui->pushButtonExit->setStyleSheet(_Stylesheet);
    m_noteHeadMenu->ui->pushButtonMenu->setStyleSheet(_Stylesheet);
    m_noteHeadMenu->ui->pushButtonExit->setIcon(QPixmap(":/image/1x/close_block.png"));
    m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
    m_noteHeadMenu->ui->pushButtonMenu->setIcon(QPixmap(":/image/1x/more_block.png"));
    m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));
    update();
}

void Edit_page::pinkBtnSlot()
{
    m_editColor = QColor(245,80,159);
    emit colorhasChanged(m_editColor,m_noteId);
    m_noteHead->color_widget = QColor(245,80,159);
    m_noteHeadMenu->color_widget = QColor(245,80,159);
    QString _Stylesheet;
    QString _BgColor;
    _BgColor = m_editColor.name();
    _Stylesheet = "background-color: %1;";
    _Stylesheet = _Stylesheet.arg(_BgColor);
    m_noteHeadMenu->ui->pushButtonExit->setStyleSheet(_Stylesheet);
    m_noteHeadMenu->ui->pushButtonMenu->setStyleSheet(_Stylesheet);
    m_noteHeadMenu->ui->pushButtonExit->setIcon(QPixmap(":/image/1x/close_block.png"));
    m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
    m_noteHeadMenu->ui->pushButtonMenu->setIcon(QPixmap(":/image/1x/more_block.png"));
    m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));
    update();
}

void Edit_page::defaultBtnSlot()
{
    if(pNotebook->m_isThemeChanged){
        qDebug() << "白色便签头";
        m_editColor = QColor(255,255,255);
        m_noteHead->color_widget = QColor(255,255,255);
        m_noteHeadMenu->color_widget = QColor(255,255,255);
        m_noteHeadMenu->ui->pushButtonExit->setIcon(QPixmap(":/image/1x/close_block.png"));
        m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
        m_noteHeadMenu->ui->pushButtonMenu->setIcon(QPixmap(":/image/1x/more_block.png"));
        m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));

        QString _Stylesheet;
        QString _BgColor;
        _BgColor = m_editColor.name();
        _Stylesheet = "background-color: %1;";
        _Stylesheet = _Stylesheet.arg(_BgColor);
        m_noteHeadMenu->ui->pushButtonExit->setStyleSheet(_Stylesheet);
        m_noteHeadMenu->ui->pushButtonMenu->setStyleSheet(_Stylesheet);
    }else{
        qDebug() << "黑色便签头";
        m_editColor = QColor(0,0,0);
        m_noteHead->color_widget = QColor(0,0,0);
        m_noteHeadMenu->color_widget = QColor(0,0,0);
        m_noteHeadMenu->ui->pushButtonExit->setIcon(QPixmap(":/image/1x/close_block.png"));
        m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
        m_noteHeadMenu->ui->pushButtonMenu->setIcon(QPixmap(":/image/1x/more_block.png"));
        m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));

        QString _Stylesheet;
        QString _BgColor;
        QString _Color;
        _BgColor = m_editColor.name();
        _Color = QColor(19,20,20,0).name();
        _Stylesheet = "background-color: %1; color: %2;";
        _Stylesheet = _Stylesheet.arg(_BgColor).arg(_Color);
        m_noteHeadMenu->ui->pushButtonExit->setStyleSheet(_Stylesheet);
        m_noteHeadMenu->ui->pushButtonMenu->setStyleSheet(_Stylesheet);
    }

    emit colorhasChanged(m_editColor,m_noteId);
    update();
}
