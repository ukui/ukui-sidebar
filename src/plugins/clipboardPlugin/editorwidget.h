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


#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QWidget>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QGroupBox>
#include <QLabel>
#include <QFont>
#include <QGuiApplication>
#include <QScreen>
#include <QRect>
#include <QDebug>
#include <QStyleOption>
#include <QPainter>
#include <QDialog>
#define  SIDEBAR_EDITAREA_QSS_PATH  ":/qss/sideBarEditArea.css"
class EditorWidget : public QDialog
{
    Q_OBJECT
public:
    explicit EditorWidget();
    QPushButton  *m_pConfirmButton;
    QPushButton  *m_pCancelButton;
    QTextEdit    *m_pEditingArea;
    QLabel       *m_ptileLable;
    QGroupBox    *m_pTitleBox;
    QGroupBox    *m_pEditBox;
    QGroupBox    *m_pOperationBox;
    QVBoxLayout  *m_pMainQVBoxLayout;                                     //主界面垂直布局器
    QHBoxLayout  *m_ptileLayout;
    QHBoxLayout  *m_pEditLaout;
    QHBoxLayout  *m_pOperationLayout;

    void titleBox();
    void editBox();
    void operationBox();

protected:
    void paintEvent(QPaintEvent *);
};

#endif // EDITORWIDGET_H
