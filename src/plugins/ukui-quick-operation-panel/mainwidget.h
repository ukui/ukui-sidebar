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
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QObject>
#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QMenu>
#include <QAction>

#define KYLIN_EDIT_MENU_ICON_PATH ":/images/icon-edit.svg"
#define KYLIN_EDIT_MENU_ICON_NAME "document-edit-symbolic"

#define KYLIN_SET_MENU_ICON_PATH  ":/images/icon-setting.svg"
#define KYLIN_SET_MENU_ICON_NAME  "document-properties-symbolic"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    MainWidget();

private:
    void createAction();

protected:
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QAction *SetAction;
    QAction *EditAction;

private slots:

Q_SIGNALS:
    void EditOptionSignal();
    void hideDropdownBox();
};

#endif // MAINWIDGET_H
