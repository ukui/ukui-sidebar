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
#include <QLine>
#include <QGroupBox>
#define  EDIT_SVG_PATH  ":/image/editor.svg"
#define  COPY_SVG_PATH  ":/image/copy.svg"
#define  REMOVE_SVG_PATH  ":/image/delete.svg"
#define  SEARCH_SVG_CLEAN ":/image/button-close-hover-click-two.svg"
#define  SEARCH_SVG_CLEAN_BACK ":/image/button-close-hover-click-add-background-one.svg"
class ClipboardWidgetEntry : public QWidget
{
public:
    ClipboardWidgetEntry(QWidget *parent = nullptr);
    void WidgetEntry();
    void WidgetEntryLine();
    QPushButton *m_pPopButton;
    QPushButton *m_pEditButon;
    QPushButton *m_pRemoveButton;
    QLabel      *m_pCopyDataLabal;
    QLabel      *m_pHBottomLabelLine;
    QHBoxLayout *m_pHLayout;
    QHBoxLayout *m_pHorizontalLineLayout;
    QLine       *m_pLine;
    QGroupBox   *m_pMainWidgetEntryBox;
    QGroupBox   *m_pEntryLineBox;
    QVBoxLayout *m_pMainLayout;
};

#endif // CLIPBOARDWIDGETENTRY_H
