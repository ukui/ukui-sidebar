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

#ifndef SETFONTSIZE_H
#define SETFONTSIZE_H

#include <QWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>

namespace Ui {
class SetFontSize;
}

class fontButton;

class SetFontSize : public QWidget
{
    Q_OBJECT

public:
    explicit SetFontSize(QWidget *parent = nullptr);
    ~SetFontSize();

    Ui::SetFontSize *ui;

public:
    QListWidgetItem *list_aItem[40];
    fontButton *list_page[40];
    QLabel *label[40];

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void initSetup();
};

#endif // SETFONTSIZE_H
