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
#include "edit_page.h"
#include "ui_edit_page.h"
#include <QBitmap>
#include <QPalette>
#include "ui_select_color_page.h"
#include <QDebug>
#include "widget.h"
#include <QPainter>
#include "ui_text_editing.h"
#include <QTextList>
#include "set_font_size_page.h"
#include "ui_set_font_size_page.h"
#include "set_font_color_page.h"
#include "ui_set_font_color_page.h"
#include "cai_tou.h"


static int count =0;

Edit_page::Edit_page(Widget* page, QModelIndex index, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Edit_page),
    m_editColor(0,0,0),
    m_index(index)
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
    connect(ui->textEdit,&QTextEdit::textChanged,this,&Edit_page::textChangedSlot);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(color_clicked()));
    timer->setInterval(100);
    timer->start();
    set_color();

    caitou = new  cai_tou(this);
    caitou->move(0,0);
    ui->widget->hide();
    ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

Edit_page::~Edit_page()
{
    qDebug()<<"aa"<<count--;
    delete ui;
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
  connect(color_page->ui->wight_btn, SIGNAL(clicked()), this, SLOT(wight_btn_change()) );
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
    emit texthasChanged(m_index);
}

//chu ti
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
//sha chu xian
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


//shu zhi  suo jin
void Edit_page::showNUMList(bool index)
{

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

// zhi ti dax iao
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
    emit colorhasChanged(m_editColor);
    qDebug() << "emit colorhasChanged";
    caitou->color_widget = QColor(76,119,231);
    update();
}

void Edit_page::pink_btn_change()
{
    m_editColor = QColor(250,108,99);
    emit colorhasChanged(m_editColor);
    caitou->color_widget = QColor(250,108,99);
    update();
}

void Edit_page::dark_green_btn_change()
{

     m_editColor = QColor(15,161,90);
     emit colorhasChanged(m_editColor);
     caitou->color_widget =QColor(15,161,90); ;
     update();
}

void Edit_page::orang_btn_change()
{
     m_editColor = QColor(255,151,47);
     emit colorhasChanged(m_editColor);
     caitou->color_widget =QColor(255,151,47) ;
     update();
}

void Edit_page::Violet_btn_change()
{
     m_editColor = QColor(186,123,216);
     emit colorhasChanged(m_editColor);
     caitou->color_widget = QColor(186,123,216);
     update();
}

void Edit_page::Golden_btn_change()
{
     m_editColor = QColor(248,209,93);
     emit colorhasChanged(m_editColor);
     caitou->color_widget = QColor(248,209,93);
     update();
}

void Edit_page::light_blue_btn_change()
{
     m_editColor = QColor(42,162,217);
     emit colorhasChanged(m_editColor);
     caitou->color_widget = QColor(42,162,217);
     update();
}

void Edit_page::light_green_btn_change()
{
     m_editColor = QColor(110,207,67);
     emit colorhasChanged(m_editColor);
     caitou->color_widget = QColor(110,207,67);
     update();
}

void Edit_page::yellow_btn_change()
{
     m_editColor = QColor(250,243,175);
     emit colorhasChanged(m_editColor);
     caitou->color_widget = QColor(250,243,175);
     update();
}

void Edit_page::wight_btn_change()
{
    if(pNotebook->dack_wight_flag){
     m_editColor = QColor(236,238,242);
     caitou->color_widget = QColor(236,238,242);
    }else{
        m_editColor = QColor(0,0,0);
        caitou->color_widget = QColor(0,0,0);
    }

     emit colorhasChanged(m_editColor);
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
    color_page->show();
}

void Edit_page::on_chang_btn_clicked()
{
    QPointF position = this->pos();
    //QPointF position = parentWidget()->pos();
    text_edit_page->move(position.x(),position.y()+224);
    text_edit_page->show();
}

void Edit_page::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
    QMenu * menu = new QMenu(this);
    menu->resize(50,20);
    if(!pNotebook->dack_wight_flag)
    {
        menu->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
                                              "background:rgb(255,255,255);\n"
                                              ""));
    }else{

        menu->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
                                              "background:rgb(19,20,20);\n"
                                              ""));
    }

    QAction * delete_the_widget = new QAction(tr("Close"));
    delete_the_widget->setIcon(QIcon(":/image/1x/delete.png"));
    QAction * t3 = new QAction(tr("Open Notepad"));
    t3->setIcon(QIcon(":/image/1x/open_note-book.png"));
    connect(delete_the_widget, SIGNAL(triggered()), this, SLOT(clear_the_page()));
    connect(t3, SIGNAL(triggered()), this, SLOT(show_note_page()));
    menu->addAction(delete_the_widget);
    menu->addAction(t3);
    // QAction * t1 = new QAction(tr("新建"));
    //t1->setIcon(QIcon(":/image/1x/sourch.png"));
    //connect(t1, SIGNAL(triggered()), this, SLOT(add_new_page()));
    // menu->addAction(t1);
    menu->move(cursor().pos()); //让菜单显示的位置在鼠标的坐标上
    menu->show();
}

void Edit_page::clear_the_page()
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
    if(!pNotebook->dack_wight_flag == -1){
        return;
    }
        if(!pNotebook->dack_wight_flag)
        {
            light_show();
        }else{

            black_show();
        }

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
