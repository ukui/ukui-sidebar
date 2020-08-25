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

#define KYLIN_HOTSPOT_NORMAL_NAME      "kylin-hotspot-normal"
#define KYLIN_HOTSPOT_HOVER_NAME       "kylin-hotspot-hover"
#define KYLIN_HOTSPOT_PRESS_NAME       "kylin-hotspot-pressed"

#define KYLIN_HOTSPOT_NORMAL_PATH      ":/image/hotspot-normal.svg"
#define KYLIN_HOTSPOT_HOVER_PATH       ":/image/hotspot-hover.svg"
#define KYLIN_HOTSPOT_PRESS_PATH       ":/image/hotspot-pressed.svg"

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
    switchButton  *m_photspotButton;
    QLabel        *m_photspotLabel;

    QVBoxLayout   *m_pVboxButtonLayout;
    QVBoxLayout   *m_pVboxLayout;

    QStringList  m_IconPathList;
    QStringList  m_IconNameList;
};

#endif // HOTSPOTWIDGET_H
