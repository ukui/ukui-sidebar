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


#ifndef CLIPBOARDWIDGETENTRY_H
#define CLIPBOARDWIDGETENTRY_H
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QIcon>
#define  EDIT_SVG_PATH  ":/image/编辑.svg"
#define  COPY_SVG_PATH  ":/image/复制.svg"
#define  REMOVE_SVG_PATH  ":/image/删除.svg"
class ClipboardWidgetEntry : public QWidget
{
public:
    ClipboardWidgetEntry(QWidget *parent = nullptr);
    QPushButton *m_pPopButton;
    QPushButton *m_pEditButon;
    QPushButton *m_pRemoveButton;
    QLabel      *m_pCopyDataLabal;
    QHBoxLayout *m_pHLayout;
};

#endif // CLIPBOARDWIDGETENTRY_H
