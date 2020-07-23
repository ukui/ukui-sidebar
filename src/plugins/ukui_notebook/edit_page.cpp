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

#include "ui_text_editing.h"
#include "set_font_size_page.h"
#include "ui_set_font_size_page.h"
#include "set_font_color_page.h"
#include "ui_set_font_color_page.h"
#include "ui_select_color_page.h"
#include "noteHead.h"
#include "widget.h"
#include "ui_widget.h"
#include "edit_page.h"
#include "ui_edit_page.h"

Edit_page::Edit_page(Widget* page, int noteId, QWidget *parent) :
    QWidget(parent)
  , ui(new Ui::Edit_page)
  , m_editColor(0,0,0)
  , m_noteId(noteId)
  , m_lastBlockList(0)
{
    ui->setupUi(this);
    //标题
    this->setWindowTitle(tr("ukui-memo"));
    //任务栏图标
    //setWindowIcon(QIcon(":/image/kylin-notebook.svg"));
    setWindowIcon(QIcon::fromTheme("kylin-notebook"));

    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.setRenderHint(QPainter::Antialiasing);
    p.drawRoundedRect(bmp.rect(),6,6);
    setMask(bmp);
    pNotebook = page;
    setWindowOpacity(0.9);
    setWindowFlags(Qt::FramelessWindowHint);
    set_all_btn_attribute();
    set_select_color_page();
    set_text_editing_page();
    set_color();

    m_noteHead = new noteHead(this);
    m_noteHeadMenu = new noteHeadMenu(this);

    m_noteHead->move(0,0);
    m_noteHeadMenu->move(0,0);
    m_noteHead->show();
    m_noteHeadMenu->hide();
    ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 禁用右键菜单
    ui->textEdit->setContextMenuPolicy(Qt::NoContextMenu);
//    ui->textEdit->setFontPointSize(14);

    connect(m_noteHeadMenu->ui->pushButtonExit,&QPushButton::clicked,this,&Edit_page::closeSlot);
    connect(ui->textEdit,&QTextEdit::textChanged,this,&Edit_page::textChangedSlot);

    fontChanged();
    color_clicked();
}

Edit_page::~Edit_page()
{
    delete ui;
}

void Edit_page::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);

    p.setBrush(opt.palette.color(QPalette::Base));
    //p.setOpacity(0.7);
    p.setPen(Qt::NoPen);

    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.drawRoundedRect(opt.rect,6,6);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Edit_page::enterEvent(QEvent *)
{
    m_noteHead->hide();
    m_noteHeadMenu->show();
}

void Edit_page::leaveEvent(QEvent *)
{
    m_noteHeadMenu->hide();
    m_noteHead->show();
}

void Edit_page::set_select_color_page()
{
    color_page = new select_color_page(pNotebook);
    ui->textEdit->setFrameShape(QFrame::NoFrame);
    connect(color_page->paletteWidget->ui->blueBtn, SIGNAL(clicked()), this, SLOT(blue_btn_change()));
    connect(color_page->paletteWidget->ui->pinkBtn, SIGNAL(clicked()), this, SLOT(pink_btn_change()));
    connect(color_page->paletteWidget->ui->darkGreenBtn, SIGNAL(clicked()), this, SLOT(dark_green_btn_change()));
    connect(color_page->paletteWidget->ui->orangeBtn, SIGNAL(clicked()), this, SLOT(orang_btn_change()));
    connect(color_page->paletteWidget->ui->violetBtn, SIGNAL(clicked()), this, SLOT(Violet_btn_change()));
    connect(color_page->paletteWidget->ui->goldenBtn, SIGNAL(clicked()), this, SLOT(Golden_btn_change()));
    connect(color_page->paletteWidget->ui->lightBlueBtn, SIGNAL(clicked()), this, SLOT(light_blue_btn_change()));
    connect(color_page->paletteWidget->ui->lightGreenBtn, SIGNAL(clicked()), this, SLOT(light_green_btn_change()));
    connect(color_page->paletteWidget->ui->yellowBtn, SIGNAL(clicked()), this, SLOT(yellow_btn_change()));
    connect(color_page->paletteWidget->ui->defaultBtn, SIGNAL(clicked()), this, SLOT(white_btn_change()));
}

void Edit_page::set_text_editing_page()
{
    text_edit_page = new Text_editing(pNotebook);
    text_edit_page->texteditwidget->ui->showListBtn->setCheckable(true);
    text_edit_page->texteditwidget->ui->showNUMList->setCheckable(true);

    qDebug() << "text_edit_page->ui->showNUMList is checkable ? :" << text_edit_page->texteditwidget->ui->showNUMList->isCheckable();
    connect(text_edit_page->set_size_page->ui->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(showSizeSpinBix()));
    connect(text_edit_page->set_color_fort_page->ui->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(showFontColorSlot()));

    connect(text_edit_page->texteditwidget->ui->BoldBtn,SIGNAL(clicked()),this,SLOT(showBoldBtn()));
    connect(text_edit_page->texteditwidget->ui->ItalicBtn,SIGNAL(clicked(bool)),this,SLOT(showItalicBtn()));
    connect(text_edit_page->texteditwidget->ui->underlineBtn,SIGNAL(clicked(bool)),this,SLOT(showUnderlineBtn()));
    connect(text_edit_page->texteditwidget->ui->StrikeOutResolvedBtn,SIGNAL(clicked(bool)),this,SLOT(showStrikeOutResolved()));
    connect(text_edit_page->texteditwidget->ui->showListBtn,SIGNAL(clicked(bool)),this,SLOT(showList(bool)));
    connect(text_edit_page->texteditwidget->ui->showNUMList,SIGNAL(clicked(bool)),this,SLOT(showNUMList(bool)));
    connect(ui->textEdit,&QTextEdit::cursorPositionChanged,this,&Edit_page::slotCursorPositionChanged);

}

void Edit_page::fontChanged() {
    qDebug() << "font Changed";
    if (ui->textEdit->textCursor().currentList()) {
        QTextListFormat lfmt = ui->textEdit->textCursor().currentList()->format();
        if (lfmt.style() == QTextListFormat::ListDisc) {
            text_edit_page->texteditwidget->ui->showListBtn->setChecked(true);
            text_edit_page->texteditwidget->ui->showNUMList->setChecked(false);
          } else if (lfmt.style() == QTextListFormat::ListDecimal) {
            text_edit_page->texteditwidget->ui->showListBtn->setChecked(false);
            text_edit_page->texteditwidget->ui->showNUMList->setChecked(true);
          } else {
            text_edit_page->texteditwidget->ui->showListBtn->setChecked(false);
            text_edit_page->texteditwidget->ui->showNUMList->setChecked(false);
            }
      } else {
        text_edit_page->texteditwidget->ui->showListBtn->setChecked(false);
        text_edit_page->texteditwidget->ui->showNUMList->setChecked(false);
      }
}

void Edit_page::slotCursorPositionChanged() {
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    QTextList *l = ui->textEdit->textCursor().currentList();
    if (m_lastBlockList && (l == m_lastBlockList || (l != 0 && m_lastBlockList != 0
                                 && l->format().style() == m_lastBlockList->format().style()))) {
        return;
        }
    m_lastBlockList = l;
    if (l) {
        QTextListFormat lfmt = l->format();
        if (lfmt.style() == QTextListFormat::ListDisc) {
            text_edit_page->texteditwidget->ui->showListBtn->setChecked(true);
            text_edit_page->texteditwidget->ui->showNUMList->setChecked(false);
          } else if (lfmt.style() == QTextListFormat::ListDecimal) {
            text_edit_page->texteditwidget->ui->showListBtn->setChecked(false);
            text_edit_page->texteditwidget->ui->showNUMList->setChecked(true);
          } else {
            text_edit_page->texteditwidget->ui->showListBtn->setChecked(false);
            text_edit_page->texteditwidget->ui->showNUMList->setChecked(false);
            }
      } else {
        text_edit_page->texteditwidget->ui->showListBtn->setChecked(false);
        text_edit_page->texteditwidget->ui->showNUMList->setChecked(false);
        }
}

void Edit_page::textChangedSlot()
{
    qDebug() << "emit textchange";
    emit texthasChanged(m_noteId, this->id);
}

//加粗
void Edit_page::showBoldBtn()
{
    qDebug()<<"-------showBoldBtn------------";
    QTextCharFormat fmt;
    fmt.setFontWeight(text_edit_page->texteditwidget->ui->BoldBtn->isCheckable() ? QFont::Bold : QFont::Normal);

    QTextCursor cursor = ui->textEdit->textCursor();
    if (!cursor.hasSelection()){
        qDebug()<<"-------showBoldBtn------------111";
        cursor.select(QTextCursor::WordUnderCursor);
    }
    if(cursor.charFormat().fontWeight() == QFont::Bold)
    {
        qDebug() << "textfont bold";
        fmt.setFontWeight(QFont::Normal);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }else{
        qDebug() << "textfont bold222";
        fmt.setFontWeight(QFont::Bold);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }
}

//斜体
void Edit_page::showItalicBtn()
{
    qDebug()<<"-------showItalicBtn------------";
    QTextCharFormat fmt;
    fmt.setFontItalic(text_edit_page->texteditwidget->ui->ItalicBtn->isCheckable() );// ? QFont::StyleItalic : QFont::Normal);

    QTextCursor cursor = ui->textEdit->textCursor();
    qDebug() << cursor.charFormat().fontItalic();
    if(cursor.charFormat().fontItalic())  //return boolProperty(FontItalic)
    {
        qDebug() << "italic true";
        fmt.setFontItalic(QFont::StyleNormal);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }else{
        qDebug() << "italic false";
        fmt.setFontItalic(QFont::StyleItalic);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }
}

//下划线
void Edit_page::showUnderlineBtn()
{
    qDebug()<<"-------showUnderlineBtn------------";
    QTextCharFormat fmt;
    fmt.setFontUnderline(text_edit_page->texteditwidget->ui->underlineBtn->isCheckable());// ? QFont::UnderlineResolved : QFont::Normal );

    QTextCursor cursor = ui->textEdit->textCursor();
    qDebug() << cursor.charFormat().fontItalic();
    if(cursor.charFormat().fontUnderline())  //
    {
        fmt.setFontUnderline(QFont::StyleNormal);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }else{
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }
}

//删除线
void Edit_page::showStrikeOutResolved()
{
    qDebug()<<"-------showStrikeOutResolved------------";
    QTextCharFormat fmt;
    fmt.setFontStrikeOut(text_edit_page->texteditwidget->ui->StrikeOutResolvedBtn->isCheckable());// ? QFont::StrikeOutResolved : QFont::Normal );

    QTextCursor cursor = ui->textEdit->textCursor();
    qDebug() << cursor.charFormat().fontItalic();
    if(cursor.charFormat().fontStrikeOut())  //
    {
        fmt.setFontStrikeOut(QFont::StyleNormal);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }else{
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }
}

//无序列表
void Edit_page::showList(bool checked)
{
    qDebug() << "showlist" << checked;
    if(checked)
    {
        text_edit_page->texteditwidget->ui->showNUMList->setChecked(false);
        qDebug() << "show list set false" << checked;
        qDebug() << "text_edit_page->ui->showNUMList is checked ? :" << text_edit_page->texteditwidget->ui->showNUMList->isChecked();
    }
    list(checked, QTextListFormat::ListDisc);
    qDebug() << "text_edit_page->ui->showNUMList is checked ? :" << text_edit_page->texteditwidget->ui->showNUMList->isChecked();
}

//有序列表
void Edit_page::showNUMList(bool checked)
{
    qDebug() << "show num list";
    if (checked) {
        text_edit_page->texteditwidget->ui->showListBtn->setChecked(false);
        }
    list(checked, QTextListFormat::ListDecimal);
}

void Edit_page::list(bool checked, QTextListFormat::Style style) {
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

//字号
void Edit_page::showSizeSpinBix()
{
    qDebug()<<"--------------";
    int num = text_edit_page->set_size_page->ui->listWidget->currentRow();
    text_edit_page->texteditwidget->ui->light_blue_btn->setText(QString::number(num+10));
    text_edit_page->set_size_page->close();

    QTextCharFormat fmt;
    fmt.setFontPointSize(num+10);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

//调色板
void Edit_page::set_color()
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
    color[9]="background:rgba(236,238,242,1);";
    color[10]="background:rgba(0,0,0,1);";

    color_num[0]=QColor(76,119,231);
    color_num[1]=QColor(250,108,99);
    color_num[2]=QColor(15,161,90);
    color_num[3]=QColor(255,151,47);
    color_num[4]=QColor(186,123,216);
    color_num[5]=QColor(248,209,93);
    color_num[6]=QColor(42,162,217);
    color_num[7]=QColor(110,207,67);
    color_num[8]=QColor(250,243,175);
    color_num[9]=QColor(236,238,242);
    color_num[10]=QColor(0,0,0);
}

void Edit_page::showFontColorSlot ()
{
    qDebug()<<"--------------";
    int num = text_edit_page->set_color_fort_page->ui->listWidget->currentRow();
    text_edit_page->texteditwidget->ui->blue_btn_2->setStyleSheet(color[num]+"border-radius:3px;");

    QTextCharFormat fmt;
    fmt.setForeground(color_num[num]);
    ui->textEdit->mergeCurrentCharFormat(fmt);

    text_edit_page->set_color_fort_page->close();
}

void Edit_page::blue_btn_change()
{
    m_editColor = QColor(76,119,231);
    qDebug() << "blue btn click" << m_editColor.value();
    emit colorhasChanged(m_editColor,m_noteId);
    qDebug() << "emit colorhasChanged";
    m_noteHead->color_widget = QColor(76,119,231);
    m_noteHeadMenu->color_widget = QColor(76,119,231);
    QString _Stylesheet;
    QString _BgColor;
    _BgColor = m_editColor.name();
    _Stylesheet = "background-color: %1;";
    _Stylesheet = _Stylesheet.arg(_BgColor);
    m_noteHeadMenu->ui->pushButtonExit->setStyleSheet(_Stylesheet);
    m_noteHeadMenu->ui->pushButtonMenu->setStyleSheet(_Stylesheet);

    QPixmap pixmap1;
    QPixmap pixmap2;
    pixmap1 = QPixmap(":/image/1x/close_block.png");
    pixmap2 = QPixmap(":/image/1x/more_block.png");
    m_noteHeadMenu->ui->pushButtonExit->setIcon(pixmap1);
    m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
    m_noteHeadMenu->ui->pushButtonMenu->setIcon(pixmap2);
    m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));
    update();
}

void Edit_page::pink_btn_change()
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

    QPixmap pixmap1;
    QPixmap pixmap2;
    pixmap1 = QPixmap(":/image/1x/close_block.png");
    pixmap2 = QPixmap(":/image/1x/more_block.png");
    m_noteHeadMenu->ui->pushButtonExit->setIcon(pixmap1);
    m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
    m_noteHeadMenu->ui->pushButtonMenu->setIcon(pixmap2);
    m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));
    update();
}

void Edit_page::dark_green_btn_change()
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

    QPixmap pixmap1;
    QPixmap pixmap2;
    pixmap1 = QPixmap(":/image/1x/close_block.png");
    pixmap2 = QPixmap(":/image/1x/more_block.png");
    m_noteHeadMenu->ui->pushButtonExit->setIcon(pixmap1);
    m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
    m_noteHeadMenu->ui->pushButtonMenu->setIcon(pixmap2);
    m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));
    update();
}

void Edit_page::orang_btn_change()
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

    QPixmap pixmap1;
    QPixmap pixmap2;
    pixmap1 = QPixmap(":/image/1x/close_block.png");
    pixmap2 = QPixmap(":/image/1x/more_block.png");
    m_noteHeadMenu->ui->pushButtonExit->setIcon(pixmap1);
    m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
    m_noteHeadMenu->ui->pushButtonMenu->setIcon(pixmap2);
    m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));
    update();
}

void Edit_page::Violet_btn_change()
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

    QPixmap pixmap1;
    QPixmap pixmap2;
    pixmap1 = QPixmap(":/image/1x/close_block.png");
    pixmap2 = QPixmap(":/image/1x/more_block.png");
    m_noteHeadMenu->ui->pushButtonExit->setIcon(pixmap1);
    m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
    m_noteHeadMenu->ui->pushButtonMenu->setIcon(pixmap2);
    m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));
    update();
}

void Edit_page::Golden_btn_change()
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

    QPixmap pixmap1;
    QPixmap pixmap2;
    pixmap1 = QPixmap(":/image/1x/close_block.png");
    pixmap2 = QPixmap(":/image/1x/more_block.png");
    m_noteHeadMenu->ui->pushButtonExit->setIcon(pixmap1);
    m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
    m_noteHeadMenu->ui->pushButtonMenu->setIcon(pixmap2);
    m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));
    update();
}

void Edit_page::light_blue_btn_change()
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

    QPixmap pixmap1;
    QPixmap pixmap2;
    pixmap1 = QPixmap(":/image/1x/close_block.png");
    pixmap2 = QPixmap(":/image/1x/more_block.png");
    m_noteHeadMenu->ui->pushButtonExit->setIcon(pixmap1);
    m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
    m_noteHeadMenu->ui->pushButtonMenu->setIcon(pixmap2);
    m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));
    update();
}

void Edit_page::light_green_btn_change()
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

    QPixmap pixmap1;
    QPixmap pixmap2;
    pixmap1 = QPixmap(":/image/1x/close_block.png");
    pixmap2 = QPixmap(":/image/1x/more_block.png");
    m_noteHeadMenu->ui->pushButtonExit->setIcon(pixmap1);
    m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
    m_noteHeadMenu->ui->pushButtonMenu->setIcon(pixmap2);
    m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));
    update();
}

void Edit_page::yellow_btn_change()
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

    QPixmap pixmap1;
    QPixmap pixmap2;
    pixmap1 = QPixmap(":/image/1x/close_block.png");
    pixmap2 = QPixmap(":/image/1x/more_block.png");
    m_noteHeadMenu->ui->pushButtonExit->setIcon(pixmap1);
    m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
    m_noteHeadMenu->ui->pushButtonMenu->setIcon(pixmap2);
    m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));
    update();
}

void Edit_page::white_btn_change()
{
    if(pNotebook->m_isThemeChanged){
        m_editColor = QColor(255,255,255);
        m_noteHead->color_widget = QColor(255,255,255);
        m_noteHeadMenu->color_widget = QColor(255,255,255);
        QPixmap pixmap1;
        QPixmap pixmap2;
        pixmap1 = QPixmap(":/image/1x/close_block.png");
        pixmap2 = QPixmap(":/image/1x/more_block.png");
        m_noteHeadMenu->ui->pushButtonExit->setIcon(pixmap1);
        m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
        m_noteHeadMenu->ui->pushButtonMenu->setIcon(pixmap2);
        m_noteHeadMenu->ui->pushButtonMenu->setIconSize(QSize(20,20));

        QString _Stylesheet;
        QString _BgColor;
        _BgColor = m_editColor.name();
        _Stylesheet = "background-color: %1;";
        _Stylesheet = _Stylesheet.arg(_BgColor);
        m_noteHeadMenu->ui->pushButtonExit->setStyleSheet(_Stylesheet);
        m_noteHeadMenu->ui->pushButtonMenu->setStyleSheet(_Stylesheet);
    }else{
        m_editColor = QColor(0,0,0);
        m_noteHead->color_widget = QColor(0,0,0);
        m_noteHeadMenu->color_widget = QColor(0,0,0);
        QPixmap pixmap1;
        QPixmap pixmap2;
        pixmap1 = QPixmap(":/image/1x/close_light.png");
        pixmap2 = QPixmap(":/image/1x/more_light.png");
        m_noteHeadMenu->ui->pushButtonExit->setIcon(pixmap1);
        m_noteHeadMenu->ui->pushButtonExit->setIconSize(QSize(20,20));
        m_noteHeadMenu->ui->pushButtonMenu->setIcon(pixmap2);
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

void Edit_page::set_all_btn_attribute()
{
    pixmap1 = QPixmap(":/image/1x/note_color.png");
    pixmap2 = QPixmap(":/image/1x/adjustment.png");
    pixmap3 = QPixmap(":/image/1x/note_color.png");
    ui->chang_btn->setIcon(pixmap2);
    ui->chang_btn->setIconSize(QSize(36,36));
    ui->color_btn->setIcon(pixmap3);
    ui->color_btn->setIconSize(QSize(36,36));
    QPalette palette = ui->color_btn->palette();
    QColor ColorPlaceholderText(255,255,255,0);
    QBrush brush;
    brush.setColor(ColorPlaceholderText);
    palette.setBrush(QPalette::Button, brush);
    palette.setBrush(QPalette::ButtonText, brush);
    //palette.setColor(QPalette::Highlight, Qt::transparent); /* 取消按钮高亮 */
    ui->color_btn->setPalette(palette);
    ui->chang_btn->setPalette(palette);
}

void Edit_page::on_color_btn_clicked()
{
    QPointF position = this->pos();
    //QPointF position = parentWidget()->pos();
    color_page->move(position.x(),position.y()+224);
    if(sink){
        qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
//        color_page->ui->widget->setStyleSheet(QString::fromUtf8("background:rgb(240,240,240);\n"
//                                                    "border-radius:4px;"));
//        color_page->ui->white_btn->setStyleSheet(QString::fromUtf8("background:rgb(19,20,20);\n"
//                                                       "border-radius:2px;"));
    }else{
//        color_page->ui->widget->setStyleSheet(QString::fromUtf8("background:rgb(19,20,20);\n"
//                                                    "border-radius:4px;"));
//        color_page->ui->white_btn->setStyleSheet(QString::fromUtf8("background:rgba(236,238,242,1);\n"
//                                                       "border-radius:2px;"));
    }
    color_page->show();
}

void Edit_page::on_chang_btn_clicked()
{
    QPointF position = this->pos();
    //QPointF position = parentWidget()->pos();
    text_edit_page->move(position.x(),position.y()+224);
    if(sink){
        //light theme
        //text_edit_page->ui->widget->setStyleSheet(QString::fromUtf8("background:rgb(240,240,240);\n""border-radius:4px;"));
//        text_edit_page->texteditwidget->ui->BoldBtn->setStyleSheet(QString::fromUtf8("background:rgba(240,240,240,0.9);"));
//        text_edit_page->texteditwidget->ui->ItalicBtn->setStyleSheet(QString::fromUtf8("background:rgb(240,240,240);"));
//        text_edit_page->texteditwidget->ui->underlineBtn->setStyleSheet(QString::fromUtf8("background:rgba(240,240,240,0.9);"));
//        text_edit_page->texteditwidget->ui->StrikeOutResolvedBtn->setStyleSheet(QString::fromUtf8("background:rgba(240,240,240,0.9);"));
//        text_edit_page->texteditwidget->ui->frame->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
//        text_edit_page->texteditwidget->ui->showListBtn->setStyleSheet(QString::fromUtf8("background:rgba(240,240,240,0.9);"));
//        text_edit_page->texteditwidget->ui->showNUMList->setStyleSheet(QString::fromUtf8("background:rgba(240,240,240,0.9);"));
//        //text_edit_page->ui->blue_btn_2->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 255, 180);\n"));
//        text_edit_page->texteditwidget->ui->blue_btn->setStyleSheet(QString::fromUtf8("background-color: rgb(167, 167, 167);\n"
//                                                      "border-top-right-radius:4px;\n"
//                                                      "border-top-left-radius:0px;\n"
//                                                      "border-bottom-right-radius:4px;\n"
//                                                      "border-bottom-left-radius:0px;"));
//        text_edit_page->texteditwidget->ui->light_blue_btn->setStyleSheet(QString::fromUtf8("\n"
//                                                            "background-color: rgb(167, 167, 167);\n"
//                                                            "color: rgba(145, 145, 145, 1);\n"
//                                                            "border-top-left-radius:4px;\n"
//                                                            "border-top-right-radius:0px;\n"
//                                                            "border-bottom-left-radius:4px;\n"
//                                                            "border-bottom-right-radius:0px;\n"));
    }else{
        //dark theme
        //text_edit_page->ui->widget->setStyleSheet(QString::fromUtf8("background:rgb(19,20,20);\n""border-radius:4px;"));
//        text_edit_page->texteditwidget->ui->BoldBtn->setStyleSheet(QString::fromUtf8("background:rgba(19,20,20,0.9);"));
//        text_edit_page->texteditwidget->ui->ItalicBtn->setStyleSheet(QString::fromUtf8("background:rgb(19,20,20);"));
//        text_edit_page->texteditwidget->ui->underlineBtn->setStyleSheet(QString::fromUtf8("background:rgba(19,20,20,0.9);"));
//        text_edit_page->texteditwidget->ui->StrikeOutResolvedBtn->setStyleSheet(QString::fromUtf8("background:rgba(19,20,20,0.9);"));
//        text_edit_page->texteditwidget->ui->frame->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
//        text_edit_page->texteditwidget->ui->showListBtn->setStyleSheet(QString::fromUtf8("background:rgba(19,20,20,0.9);"));
//        text_edit_page->texteditwidget->ui->showNUMList->setStyleSheet(QString::fromUtf8("background:rgba(19,20,20,0.9);"));
//        //text_edit_page->ui->blue_btn_2->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 255, 180);\n"));
//        text_edit_page->texteditwidget->ui->blue_btn->setStyleSheet(QString::fromUtf8("background-color: rgb(67, 67, 67);\n"
//                                                      "border-top-right-radius:4px;\n"
//                                                      "border-top-left-radius:0px;\n"
//                                                      "border-bottom-right-radius:4px;\n"
//                                                      "border-bottom-left-radius:0px;"));
//        text_edit_page->texteditwidget->ui->light_blue_btn->setStyleSheet(QString::fromUtf8("\n"
//                                                            "background-color: rgb(67, 67, 67);\n"
//                                                            "color: rgba(145, 145, 145, 1);\n"
//                                                            "border-top-left-radius:4px;\n"
//                                                            "border-top-right-radius:0px;\n"
//                                                            "border-bottom-left-radius:4px;\n"
//                                                            "border-bottom-right-radius:0px;\n"));
    }
    text_edit_page->show();
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
    connect(delete_the_widget, SIGNAL(triggered()), this, SLOT(closeSlot()));
    connect(t3, SIGNAL(triggered()), this, SLOT(show_note_page()));
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

void Edit_page::closeSlot()
{
    this->close();
}

void Edit_page::add_new_page()
{
    //    Edit_page *new_page = new Edit_page(this->pNotebook,NULL);
    //    this->pNotebook->m_editors.push_back(new_page);
    //    new_page->show();
}

void Edit_page::show_note_page()
{
    pNotebook->show();
}

void Edit_page::color_clicked()
{
    if(sink)
        light_show();
    else
        black_show();
}

void Edit_page::light_show()
{
//    this->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
//                                          "background:rgb(240, 240, 240);\n"
//                                          ""));
//    ui->widget_2->setStyleSheet(QString::fromUtf8("\n"
//                                                  "background:rgb(240, 240, 240);\n"
//                                                  ""));
//    ui->color_btn->setStyleSheet(QString::fromUtf8("image: url(:/image/1x/color.png);\n"
//                                                   "background:rgba(240, 240, 240,0.9);\n"
//                                                   ""));
//    ui->chang_btn->setStyleSheet(QString::fromUtf8(""));
//    ui->textEdit->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
}

void Edit_page::black_show()
{
//    this->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
//                                          "background:rgb(19,20,20);\n"
//                                          ""));
//    ui->widget_2->setStyleSheet(QString::fromUtf8("background:rgb(19,20,20);\n"));
//    ui->color_btn->setStyleSheet(QString::fromUtf8("image: url(:/image/1x/color.png);\n"
//                                                   "background:rgba(19,20,20,0.9);\n"
//                                                   ""));
//    ui->chang_btn->setStyleSheet(QString::fromUtf8(""));
//    ui->textEdit->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
}
