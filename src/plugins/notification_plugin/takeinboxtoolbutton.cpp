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
#include <QHelpEvent>

TakeInBoxToolButton::TakeInBoxToolButton()
{
    m_bEnterTakeInBox = false;
}

void TakeInBoxToolButton::enterEvent(QEvent *event)
{
    QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
    if(false == m_bEnterTakeInBox)
    {
        QToolTip::showText(QPoint(helpEvent->pos().x(), (helpEvent->pos().y() + 30)), "进入收纳盒");
//        QToolTip::showText(helpEvent->globalPos(), "进入收纳盒");
    }
    else
    {
        QToolTip::showText(QPoint(helpEvent->pos().x(), (helpEvent->pos().y() + 30)), "退出收纳盒");
//        QToolTip::showText(helpEvent->globalPos(), "退出收纳盒");
    }
    return;
}

void TakeInBoxToolButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    QToolTip::hideText();
    return;
}
