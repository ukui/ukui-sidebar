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


#ifndef SCROLLAREAWIDGET_H
#define SCROLLAREAWIDGET_H

#include <QScrollBar>
#include <QScrollArea>

class ScrollBarWidget : public QScrollBar
{
    Q_OBJECT
public:
    explicit ScrollBarWidget();

protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;

signals:

public slots:
};

class ScrollAreaWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit ScrollAreaWidget();

protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;

signals:

public slots:
};

#endif // SCROLLAREAWIDGET_H
