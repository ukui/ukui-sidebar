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

#ifndef TAKEINBOXTOOLBUTTON_H
#define TAKEINBOXTOOLBUTTON_H

#include <QToolButton>
#include <QWidget>

class TakeInBoxToolButton : public QToolButton
{
    Q_OBJECT
public:
    explicit        TakeInBoxToolButton();
    void            setEnterFlags(bool bFlags) {m_bEnterTakeInBox = bFlags;}

protected:
    virtual void    enterEvent(QEvent *event) override;
    virtual void    leaveEvent(QEvent *event) override;

private:
    bool            m_bEnterTakeInBox;

};

#endif // TAKEINBOXTOOLBUTTON_H
