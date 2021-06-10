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
#ifndef NOTEBOOKBUTTONWIDGET_H
#define NOTEBOOKBUTTONWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QProcess>
#include "shortcutbutton.h"
#include "labelfotmattext.h"

#define KYLIN_BLUETOOTH_NORMAL_NAME     "ukui-icon-notes"
#define KYLIN_BLUETOOTH_SET_NAME        "ukui-icon-notes-s"

#define KYLIN_BLUETOOTH_NORMAL_PATH     ":/images/icon-notes.svg"
#define KYLIN_BLUETOOTH_SET_PATH        ":/images/icon-notes-s.svg"
#define KYLIN_DELETE_ICONPATH           ":/images/cancel-lock.png"

class notebookButtonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit notebookButtonWidget(QWidget *parent = nullptr);
    void NoteButtonClickSlots();
    QPushButton     *m_pDeleteButton;

private:
    void initMemberVariables();
    void initLayout();

private:
    QWidget         *m_pButtonWidget;
    ShortcutButton  *m_pNoteButton;
    QLabel          *m_pNoteLabel;

    LabelFotmatText *m_pLabelFotmatText;

    QVBoxLayout     *m_pVboxButtonLayout;
    QVBoxLayout     *m_pVboxLayout;

    QStyle          *m_pStyleNormal;

private slots:
//    void NoteButtonClickSlots();

Q_SIGNALS:

};

#endif // NOTEBOOKBUTTONWIDGET_H
