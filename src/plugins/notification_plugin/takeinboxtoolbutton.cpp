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

    //设置边框, 边框色, 背景色, 字体色, 字号
    setStyleSheet("QToolTip{border:1px solid rgba(255, 255, 255, 0.2); background-color: #1A1A1A; color:#FFFFFF; padding:4px; border-radius:6px; font-size:12px;}");

    if(false == m_bEnterTakeInBox)
    {
        this->setToolTip(QString::fromLocal8Bit("进入收纳盒"));
    }
    else
    {
        this->setToolTip(QString::fromLocal8Bit("退出收纳盒"));
    }
    return;
}

void TakeInBoxToolButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    return;
}
