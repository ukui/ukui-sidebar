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
#include "fileitemInit.h"
#include <QWidget>
#include "browseButton.h"

fileItemInit::fileItemInit(QWidget *parent) :
    QWidget(parent)
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("fileItemInit"));
    deletebtn0 = new browseButton(this);
    filename_label0 = new QLabel(this);
    filesize_label0 = new QLabel(this);
}

fileItemInit::~fileItemInit()
{
}
