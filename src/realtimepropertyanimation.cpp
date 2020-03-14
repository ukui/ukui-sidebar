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

#include "realtimepropertyanimation.h"
#include <QVariant>
#include <QRect>

RealtimePropertyAnimation::RealtimePropertyAnimation(QObject *target, const QByteArray &propertyName, QObject *parent) : QPropertyAnimation(target, propertyName, parent)
{

}

void RealtimePropertyAnimation::updateCurrentValue(const QVariant &value)
{
    QRect rect = value.value<QRect>();
    int x1, y1, x2, y2;
    rect.getRect(&x1, &y1, &x2, &y2);

    emit Sig_currentRect(x1, y1, x2, y2);
    return;
}
