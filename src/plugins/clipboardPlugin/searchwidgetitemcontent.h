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


#ifndef SEARCHWIDGETITEMCONTENT_H
#define SEARCHWIDGETITEMCONTENT_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QAction>
#include <QWidgetAction>
#include "clipboardwidgetentry.h"
#define  SIDEBAR_SEARCH_QSS_PATH  ":/qss/sideBarSearchArea.css"
class SearchWidgetItemContent:public QWidget
{
    Q_OBJECT
public:
    SearchWidgetItemContent(QWidget *parent = nullptr);
    QPushButton *m_pClearTextButton;
    QPushButton *m_pClearListWidgetButton;
    QLineEdit   *m_pLineEditArea;
    QHBoxLayout *m_pHBoxLayout;

private slots:
    void textChageSlots(const QString &text);
};

#endif // SEARCHWIDGETITEMCONTENT_H
