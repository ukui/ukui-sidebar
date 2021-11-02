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

#ifndef SETFONTCOLOR_H
#define SETFONTCOLORE_H

#include <QWidget>
#include <QListWidgetItem>
#include <QString>
#include <QStyleOption>
#include <QPainter>
#include <QGSettings>
#include <QDebug>

#include "paletteButton.h"
#include "ui_paletteButton.h"

/**
 * ukui style
 */
#define THEME_QT_SCHEMA     "org.ukui.style"
#define MODE_QT_KEY         "style-name"

namespace Ui {
class SetFontColor;
}

class SetFontColor : public QWidget
{
    Q_OBJECT

public:
    explicit SetFontColor(QWidget *parent = nullptr);
    ~SetFontColor();

    Ui::SetFontColor *ui;

public:
    QListWidgetItem *list_aItem[10];
    paletteButton *list_page[10];

    QString color[11];
    QString color1;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void initSetup();
    void setColor();
};

#endif // SETFONTCOLORE_H
