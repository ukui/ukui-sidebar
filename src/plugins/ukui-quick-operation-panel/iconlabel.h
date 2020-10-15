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
#ifndef ICONLABEL_H
#define ICONLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
class IconLabel : public QLabel
{
    Q_OBJECT
public:
    explicit IconLabel(QWidget *parent = nullptr);

protected:
    virtual void mouseReleaseEvent(QMouseEvent *ev);

Q_SIGNALS:
    void LabelClicked();


};

#endif // ICONLABEL_H
