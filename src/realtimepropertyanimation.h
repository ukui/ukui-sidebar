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

#ifndef REALTIMEPROPERTYANIMATION_H
#define REALTIMEPROPERTYANIMATION_H

#include <QPropertyAnimation>

class RealtimePropertyAnimation : public QPropertyAnimation
{
    Q_OBJECT
public:
    explicit RealtimePropertyAnimation(QObject *target, const QByteArray &propertyName, QObject *parent = nullptr);

protected:
    virtual void updateCurrentValue(const QVariant &value) override;

signals:
    void Sig_currentRect(int, int, int, int);

};


#endif // REALTIMEPROPERTYANIMATION_H
