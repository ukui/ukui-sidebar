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
#ifndef HOTSPOTWIDGET_H
#define HOTSPOTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "switchbutton.h"
#include "customstyle_switchNormalStatus.h"

#define KYLIN_HOTSPOT_NORMAL_NAME      "kylin-icon-hotspot"
#define KYLIN_HOTSPOT_SET_NAME       "kylin-icon-hotspot-s"
#define KYLIN_HOTSPOT_OPEN_NAME       "kylin-icon-hotspot-open"

#define KYLIN_HOTSPOT_NORMAL_PATH      ":/images/icon-hotspot.svg"
#define KYLIN_HOTSPOT_SET_PATH         ":/image/icon-hotspot-s.svg"
#define KYLIN_HOTSPOT_OPEN_PATH        ":/images/icon-hotspot-open.svg"
#define KYLIN_DELETE_ICONPATH          ":/images/cancel-lock.png"

class hotspotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit hotspotWidget(QWidget *parent = nullptr);
    ~hotspotWidget();
    void initMemberVariables();
    void initLayout();
private:
    QWidget       *m_pWidgetButton;
    QPushButton   *m_photspotButton;
    QPushButton   *m_pDeleteButton;
    QLabel        *m_photspotLabel;

    QStyle        *m_pStyleNormal;

    QVBoxLayout   *m_pVboxButtonLayout;
    QVBoxLayout   *m_pVboxLayout;
};

#endif // HOTSPOTWIDGET_H
