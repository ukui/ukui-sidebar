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
#ifndef EDIT_PAGE_H
#define EDIT_PAGE_H

#include <QWidget>
#include <QPainter>
#include <QMenu>
#include <QPainter>
#include <QColor>
#include <QModelIndex>

#include "noteHead.h"
#include "noteHeadMenu.h"
#include "ui_noteHeadMenu.h"
#include "select_color_page.h"
#include "text_editing.h"

namespace Ui {
class Edit_page;
}
class Widget;

class Edit_page : public QWidget
{
    Q_OBJECT

public:
    Edit_page(Widget* p , int noteId, QWidget *parent = nullptr);
    ~Edit_page();
    Ui::Edit_page *ui;
    Widget* pNotebook;
    QColor m_editColor;
    noteHead *m_noteHead;
    noteHeadMenu *m_noteHeadMenu;
    QModelIndex m_index;
    int id;
    int m_noteId;


    void contextMenuEvent(QContextMenuEvent *event);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

private slots:
    void textChangedSlot();

    void on_color_btn_clicked();
    void blue_btn_change();
    void pink_btn_change();
    void dark_green_btn_change();
    void orang_btn_change();
    void Violet_btn_change();
    void Golden_btn_change();
    void light_blue_btn_change();
    void light_green_btn_change();
    void yellow_btn_change();
    void white_btn_change();
    void closeSlot();
    void add_new_page();
    void show_note_page();
    void color_clicked();
    void on_chang_btn_clicked();
    void showBoldBtn();
    void showItalicBtn();
    void showUnderlineBtn();
    void showStrikeOutResolved();
    //void showCurrentFormatChanged(const QTextCharFormat &);
    void showList(bool );
    void showNUMList(bool);
    void showSizeSpinBix();
    void showFontColorSlot();

private:
    void set_all_btn_attribute();
    void palette_ui();
    void set_select_color_page();
    void set_text_editing_page();
    void light_show();
    void black_show();
    void set_color();

    QPixmap pixmap1;
    QPixmap pixmap2;
    QPixmap pixmap3;
    select_color_page *color_page ;
    Text_editing *text_edit_page;
    QTimer *timer;
    QString color[11];
    QColor color_num[11];


signals:
    void texthasChanged(int noteId, int id);
    void colorhasChanged(const QColor &color,int);
};

#endif // EDIT_PAGE_H
