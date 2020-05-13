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

static int count =0;

Edit_page::Edit_page(Widget* page, int noteId, QWidget *parent) :
    QWidget(parent)
  , ui(new Ui::Edit_page)
  , m_editColor(0,0,0)
  , m_noteId(noteId)
{
    qDebug()<<"aa"<<++count;
    ui->setupUi(this);
    //标题
    this->setWindowTitle(tr("ukui-memo"));
    //任务栏图标
    setWindowIcon(QIcon(":/image/kylin-notebook.svg"));

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

    QPointF position = this->pos();
    //m_noteHeadMenu->move(0,0);
    qDebug() << "m_noteHeadMenu" << position.x() << position.y();
    m_noteHead->move(0,0);
    m_noteHeadMenu->move(0,0);
    m_noteHead->show();
    m_noteHeadMenu->hide();
    ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(m_noteHeadMenu->ui->pushButtonExit,&QPushButton::clicked,this,&Edit_page::closeSlot);
    connect(ui->textEdit,&QTextEdit::textChanged,this,&Edit_page::textChangedSlot);
    connect(pNotebook->ui->sort_2_btn,SIGNAL(clicked()),this,SLOT(color_clicked()));
    color_clicked();
}

Edit_page::~Edit_page()
{
    qDebug()<<"aa"<<count--;
    delete ui;
}

void Edit_page::enterEvent(QEvent *)
{
    qDebug()<<"鼠标移入";

    m_noteHead->hide();
    m_noteHeadMenu->show();
}

void Edit_page::leaveEvent(QEvent *)
{
    qDebug()<<"鼠标移出";
    m_noteHeadMenu->hide();
    m_noteHead->show();
}

void Edit_page::set_select_color_page()
{
    color_page = new select_color_page(pNotebook);
    ui->textEdit->setFrameShape(QFrame::NoFrame);
    connect(color_page->ui->blue_btn, SIGNAL(clicked()), this, SLOT(blue_btn_change()) );
    connect(color_page->ui->pink_btn, SIGNAL(clicked()), this, SLOT(pink_btn_change()) );
    connect(color_page->ui->dark_green_btn, SIGNAL(clicked()), this, SLOT(dark_green_btn_change()) );
    connect(color_page->ui->orang_btn, SIGNAL(clicked()), this, SLOT(orang_btn_change()) );
    connect(color_page->ui->Violet_btn, SIGNAL(clicked()), this, SLOT(Violet_btn_change()) );
    connect(color_page->ui->Golden_btn, SIGNAL(clicked()), this, SLOT(Golden_btn_change()) );
    connect(color_page->ui->light_blue_btn, SIGNAL(clicked()), this, SLOT(light_blue_btn_change()) );
    connect(color_page->ui->light_green_btn, SIGNAL(clicked()), this, SLOT(light_green_btn_change()) );
    connect(color_page->ui->yellow_btn, SIGNAL(clicked()), this, SLOT(yellow_btn_change()) );
    connect(color_page->ui->white_btn, SIGNAL(clicked()), this, SLOT(white_btn_change()) );
}

void Edit_page::set_text_editing_page()
{
    text_edit_page = new Text_editing(pNotebook);

    connect(text_edit_page->set_size_page->ui->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(showSizeSpinBix()));
    connect(text_edit_page->set_color_fort_page->ui->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(showfortcolor()));

    connect(text_edit_page->ui->BoldBtn,SIGNAL(clicked()),this,SLOT(showBoldBtn()));
    connect(text_edit_page->ui->ItalicBtn,SIGNAL(clicked(bool)),this,SLOT(showItalicBtn()));
    connect(text_edit_page->ui->underlineBtn,SIGNAL(clicked(bool)),this,SLOT(showUnderlineBtn()));
    connect(text_edit_page->ui->StrikeOutResolvedBtn,SIGNAL(clicked(bool)),this,SLOT(showStrikeOutResolved()));
    connect(text_edit_page->ui->showListBtn,SIGNAL(clicked(bool)),this,SLOT(showList(bool)));
    connect(text_edit_page->ui->showNUMList,SIGNAL(clicked(bool)),this,SLOT(showNUMList(bool)));
    // connect(text_edit_page->ui->light_blue_btn,SIGNAL(activated(int)),this,SLOT(showSizeSpinBix(int)));

    //    connect(colorBtn,SIGNAL(clicked(bool)),this,SLOT(showColorBtn()));
}



void Edit_page::textChangedSlot()
{
    qDebug() << "emit textchange";
    emit texthasChanged(m_noteId, this->id);
}

//cu ti
void Edit_page::showBoldBtn()
{
    qDebug()<<"-------showBoldBtn------------";
    QTextCharFormat fmt;
    fmt.setFontWeight(text_edit_page->ui->BoldBtn->isCheckable() ? QFont::Bold : QFont::Normal);

    QTextCursor cursor = ui->textEdit->textCursor();
    if (!cursor.hasSelection()){
        cursor.select(QTextCursor::WordUnderCursor);
    }else{
        cursor.mergeCharFormat(fmt);
    }

    ui->textEdit->mergeCurrentCharFormat(fmt);
}
//xie ti
void Edit_page::showItalicBtn()
{
    qDebug()<<"-------showItalicBtn------------";
    QTextCharFormat fmt;
    fmt.setFontItalic(text_edit_page->ui->ItalicBtn->isCheckable() );// ? QFont::StyleItalic : QFont::Normal);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

//xia hua xian
void Edit_page::showUnderlineBtn()
{
    qDebug()<<"-------showUnderlineBtn------------";
    QTextCharFormat fmt;
    fmt.setFontUnderline(text_edit_page->ui->underlineBtn->isCheckable());// ? QFont::UnderlineResolved : QFont::Normal );
    ui->textEdit->mergeCurrentCharFormat(fmt);
}
//shan chu xian
void Edit_page::showStrikeOutResolved()
{
    qDebug()<<"-------showStrikeOutResolved------------";
    QTextCharFormat fmt;
    fmt.setFontStrikeOut(text_edit_page->ui->StrikeOutResolvedBtn->isCheckable());// ? QFont::StrikeOutResolved : QFont::Normal );
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

//fu hao  suo jin
void Edit_page::showList(bool index)
{
    Q_UNUSED(index);
    qDebug()<<"--------showList-----------";
    QTextCursor cursor = ui->textEdit->textCursor();

    QTextListFormat::Style style = QTextListFormat::ListDisc;

    style = QTextListFormat::ListDisc;

    cursor.beginEditBlock();    //设置缩进值

    QTextBlockFormat blockFmt = cursor.blockFormat();
    QTextListFormat listFmt;
    if(cursor.currentList())
    {
        listFmt = cursor.currentList()->format();
    }
    else
    {
        listFmt.setIndent(blockFmt.indent() + 1);
        blockFmt.setIndent(0);
        cursor.setBlockFormat(blockFmt);
    }
    listFmt.setStyle(style);
    cursor.createList(listFmt);

    cursor.endEditBlock();
}

//shu zi  suo jin
void Edit_page::showNUMList(bool index)
{
    Q_UNUSED(index);
    qDebug()<<"--------showList-----------";
    QTextCursor cursor = ui->textEdit->textCursor();

    QTextListFormat::Style style = QTextListFormat::ListDisc;

    style = QTextListFormat::ListDecimal;

    cursor.beginEditBlock();    //设置缩进值

    QTextBlockFormat blockFmt = cursor.blockFormat();
    QTextListFormat listFmt;
    if(cursor.currentList())
    {
        listFmt = cursor.currentList()->format();
    }
    else
    {
        listFmt.setIndent(blockFmt.indent() + 1);
        blockFmt.setIndent(0);
        cursor.setBlockFormat(blockFmt);
    }
    listFmt.setStyle(style);
    cursor.createList(listFmt);

    cursor.endEditBlock();
}

// zi ti da xiao
void Edit_page::showSizeSpinBix()
{
    qDebug()<<"--------------";
    int num = text_edit_page->set_size_page->ui->listWidget->currentRow();
    text_edit_page->ui->light_blue_btn->setText(QString::number(num+22));
    text_edit_page->set_size_page->close();

    QTextCharFormat fmt;
    fmt.setFontPointSize(num+10);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

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

void Edit_page::showfortcolor()
{
    qDebug()<<"--------------";
    int num = text_edit_page->set_color_fort_page->ui->listWidget->currentRow();
    text_edit_page->ui->blue_btn_2->setStyleSheet(color[num]+"border-radius:3px;");

    QTextCharFormat fmt;
    fmt.setForeground(color_num[num]);
    ui->textEdit->mergeCurrentCharFormat(fmt);

    text_edit_page->set_color_fort_page->close();
}

void Edit_page::blue_btn_change()
{
    m_editColor = QColor(76,119,231);
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
        m_editColor = QColor(236,238,242);
        m_noteHead->color_widget = QColor(236,238,242);
        m_noteHeadMenu->color_widget = QColor(236,238,242);
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
}

void Edit_page::on_color_btn_clicked()
{
    QPointF position = this->pos();
    //QPointF position = parentWidget()->pos();
    color_page->move(position.x(),position.y()+224);
    if(sink){
        qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
        color_page->ui->widget->setStyleSheet(QString::fromUtf8("background:rgb(240,240,240);\n"
                                                    "border-radius:4px;"));
        color_page->ui->white_btn->setStyleSheet(QString::fromUtf8("background:rgb(19,20,20);\n"
                                                       "border-radius:2px;"));
    }else{
        color_page->ui->widget->setStyleSheet(QString::fromUtf8("background:rgb(19,20,20);\n"
                                                    "border-radius:4px;"));
        color_page->ui->white_btn->setStyleSheet(QString::fromUtf8("background:rgba(236,238,242,1);\n"
                                                       "border-radius:2px;"));
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
        text_edit_page->ui->widget->setStyleSheet(QString::fromUtf8("background:rgb(240,240,240);\n""border-radius:4px;"));
        text_edit_page->ui->BoldBtn->setStyleSheet(QString::fromUtf8("background:rgba(240,240,240,0.9);"));
        text_edit_page->ui->ItalicBtn->setStyleSheet(QString::fromUtf8("background:rgb(240,240,240);"));
        text_edit_page->ui->underlineBtn->setStyleSheet(QString::fromUtf8("background:rgba(240,240,240,0.9);"));
        text_edit_page->ui->StrikeOutResolvedBtn->setStyleSheet(QString::fromUtf8("background:rgba(240,240,240,0.9);"));
        text_edit_page->ui->frame->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        text_edit_page->ui->showListBtn->setStyleSheet(QString::fromUtf8("background:rgba(240,240,240,0.9);"));
        text_edit_page->ui->showNUMList->setStyleSheet(QString::fromUtf8("background:rgba(240,240,240,0.9);"));
        //text_edit_page->ui->blue_btn_2->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 255, 180);\n"));
        text_edit_page->ui->blue_btn->setStyleSheet(QString::fromUtf8("background-color: rgb(167, 167, 167);\n"
                                                      "border-top-right-radius:4px;\n"
                                                      "border-top-left-radius:0px;\n"
                                                      "border-bottom-right-radius:4px;\n"
                                                      "border-bottom-left-radius:0px;"));
        text_edit_page->ui->light_blue_btn->setStyleSheet(QString::fromUtf8("\n"
                                                            "background-color: rgb(167, 167, 167);\n"
                                                            "color: rgba(145, 145, 145, 1);\n"
                                                            "border-top-left-radius:4px;\n"
                                                            "border-top-right-radius:0px;\n"
                                                            "border-bottom-left-radius:4px;\n"
                                                            "border-bottom-right-radius:0px;\n"));
    }else{
        //dark theme
        text_edit_page->ui->widget->setStyleSheet(QString::fromUtf8("background:rgb(19,20,20);\n""border-radius:4px;"));
        text_edit_page->ui->BoldBtn->setStyleSheet(QString::fromUtf8("background:rgba(19,20,20,0.9);"));
        text_edit_page->ui->ItalicBtn->setStyleSheet(QString::fromUtf8("background:rgb(19,20,20);"));
        text_edit_page->ui->underlineBtn->setStyleSheet(QString::fromUtf8("background:rgba(19,20,20,0.9);"));
        text_edit_page->ui->StrikeOutResolvedBtn->setStyleSheet(QString::fromUtf8("background:rgba(19,20,20,0.9);"));
        text_edit_page->ui->frame->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        text_edit_page->ui->showListBtn->setStyleSheet(QString::fromUtf8("background:rgba(19,20,20,0.9);"));
        text_edit_page->ui->showNUMList->setStyleSheet(QString::fromUtf8("background:rgba(19,20,20,0.9);"));
        //text_edit_page->ui->blue_btn_2->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 255, 180);\n"));
        text_edit_page->ui->blue_btn->setStyleSheet(QString::fromUtf8("background-color: rgb(67, 67, 67);\n"
                                                      "border-top-right-radius:4px;\n"
                                                      "border-top-left-radius:0px;\n"
                                                      "border-bottom-right-radius:4px;\n"
                                                      "border-bottom-left-radius:0px;"));
        text_edit_page->ui->light_blue_btn->setStyleSheet(QString::fromUtf8("\n"
                                                            "background-color: rgb(67, 67, 67);\n"
                                                            "color: rgba(145, 145, 145, 1);\n"
                                                            "border-top-left-radius:4px;\n"
                                                            "border-top-right-radius:0px;\n"
                                                            "border-bottom-left-radius:4px;\n"
                                                            "border-bottom-right-radius:0px;\n"));
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
    QAction * t1 = new QAction(tr("New"));
    t1->setIcon(QIcon(":/image/1x/sourch.png"));
    connect(t1, SIGNAL(triggered()), this, SLOT(add_new_page()));
    menu->addAction(t1);
    menu->move(cursor().pos()); //让菜单显示的位置在鼠标的坐标上
    menu->show();
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
    this->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
                                          "background:rgb(240, 240, 240);\n"
                                          ""));
    ui->widget_2->setStyleSheet(QString::fromUtf8("\n"
                                                  "background:rgb(240, 240, 240);\n"
                                                  ""));
    ui->color_btn->setStyleSheet(QString::fromUtf8("image: url(:/image/1x/color.png);\n"
                                                   "background:rgba(240, 240, 240,0.9);\n"
                                                   ""));
    ui->chang_btn->setStyleSheet(QString::fromUtf8(""));
    ui->textEdit->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
}

void Edit_page::black_show()
{
    this->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
                                          "background:rgb(19,20,20);\n"
                                          ""));
    ui->widget_2->setStyleSheet(QString::fromUtf8("background:rgb(19,20,20);\n"));
    ui->color_btn->setStyleSheet(QString::fromUtf8("image: url(:/image/1x/color.png);\n"
                                                   "background:rgba(19,20,20,0.9);\n"
                                                   ""));
    ui->chang_btn->setStyleSheet(QString::fromUtf8(""));
    ui->textEdit->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
}
