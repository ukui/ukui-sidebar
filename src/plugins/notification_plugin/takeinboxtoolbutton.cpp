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
#include <QDebug>

TakeInBoxToolButton::TakeInBoxToolButton()
{
    m_bEnterTakeInBox = false;
    m_bIsHover = false;
}

void TakeInBoxToolButton::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_bIsHover = true;
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

bool TakeInBoxToolButton::event(QEvent *event)
{
    Q_UNUSED(event);
//    qDebug() << "进入此处";
//    if(false == m_bEnterTakeInBox && false == m_bIsHover)
//    {
//        setIcon(QIcon(":/images/box-24.svg"));
//    }
//    else if (true == m_bEnterTakeInBox && false == m_bIsHover) {
//        setIcon(QIcon(":/images/exitbox-24.svg"));
//    }
//    else if (false == m_bEnterTakeInBox && true == m_bIsHover) {
//        setIcon(QIcon(":/images/box-24-hover.svg"));
//    }
//    else if (true == m_bEnterTakeInBox && true == m_bIsHover) {
//        setIcon(QIcon(":/images/exitbox-24-hover.svg"));
//    }

    return QToolButton::event(event);
}

void TakeInBoxToolButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_bIsHover = false;
    if(false == m_bEnterTakeInBox)
    {
        setIcon(QIcon(":/images/box-24.svg"));
    }
    else {
        setIcon(QIcon(":/images/exitbox-24.svg"));
    }

    return;
}
