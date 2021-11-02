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

#ifndef NOTEHEADMENU_H
#define NOTEHEADMENU_H

#include <QWidget>
#include <QPainter>
#include <QAction>
#include <QMenu>

namespace Ui {
class noteHeadMenu;
}

class noteHeadMenu : public QWidget
{
    Q_OBJECT

public:
    explicit noteHeadMenu(QWidget *parent = nullptr);
    ~noteHeadMenu();

    Ui::noteHeadMenu *ui;

public:
    QColor color_widget;
    QAction *m_menuActionDel;
    QAction *m_topAction;

signals:
    void requestTopMost();

protected:
    void paintEvent(QPaintEvent *event);
//    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    void btnInit();
    void slotsInit();

signals:
    void requestNewNote();
    void requestShowNote();
//    void requestFullscreen();
};

#endif // NOTEHEADMENU_H
