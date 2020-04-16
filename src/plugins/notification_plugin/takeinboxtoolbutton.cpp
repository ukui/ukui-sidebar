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

#include "takeinboxtoolbutton.h"
#include <QToolTip>

TakeInBoxToolButton::TakeInBoxToolButton()
{
    m_bEnterTakeInBox = false;
}

void TakeInBoxToolButton::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    setIconSize(QSize(24,24));
    //设置边框, 边框色, 背景色, 字体色, 字号
    if(false == m_bEnterTakeInBox)
    {
        setIcon(QIcon(":/images/box-24-hover.svg"));
        this->setToolTip((tr("Enter unimportant news")));
    }
    else
    {
        setIcon(QIcon(":/images/exitbox-24-hover.svg"));
        this->setToolTip((tr("Quit unimportant news")));
    }
    return;
}

void TakeInBoxToolButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    if(false == m_bEnterTakeInBox)
    {
        setIcon(QIcon(":/images/box-24.svg"));
    }
    else {
        setIcon(QIcon(":/images/exitbox-24.svg"));
    }

    return;
}
