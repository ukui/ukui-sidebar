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
#ifndef COLOR_MINI_H
#define COLOR_MINI_H

#include <QWidget>

namespace Ui {
class color_mini;
}

class color_mini : public QWidget
{
    Q_OBJECT

public:
    explicit color_mini(QWidget *parent = nullptr);
    ~color_mini();
    Ui::color_mini *ui;

private:

};

#endif // COLOR_MINI_H
