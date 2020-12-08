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
#ifndef FILEITEMINIT_H
#define FILEITEMINIT_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>



class fileItemInit : public QWidget
{
    Q_OBJECT

public:

    QWidget* item_widget;
    QPushButton * deletebtn0;
    QLabel *  filename_label0;
    QLabel *  filesize_label0;


    explicit fileItemInit(QWidget *parent = nullptr);
    ~fileItemInit();

private:

};

#endif // fileItemInit_H
