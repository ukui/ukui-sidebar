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
#ifndef SET_FONT_COLOR_PAGE_H
#define SET_FONT_COLOR_PAGE_H

#include <QWidget>
#include <QListWidgetItem>
#include <QString>
#include "paletteButton.h"
#include "ui_paletteButton.h"

namespace Ui {
class Set_font_color_page;
}

class Set_font_color_page : public QWidget
{
    Q_OBJECT

public:
    explicit Set_font_color_page(QWidget *parent = nullptr);
    ~Set_font_color_page();

    void set_listwidget();

    Ui::Set_font_color_page *ui;
    QListWidgetItem *list_aItem[10];
    paletteButton *list_page[10];

    QString color[11];
    QString color1;

private:
    void set_color();

};

#endif // SET_FONT_COLOR_PAGE_H
