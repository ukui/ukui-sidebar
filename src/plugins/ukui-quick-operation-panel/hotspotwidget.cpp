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
#include "hotspotwidget.h"

hotspotWidget::hotspotWidget(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initLayout();
//    this->setStyleSheet("QWidget{border: 1px solid rgba(255,255,0,1);}");
}

hotspotWidget::~hotspotWidget()
{

}

void hotspotWidget::initMemberVariables()
{
    m_pWidgetButton         = new QWidget();
    m_pWidgetButton->setFixedSize(56, 56);
    m_pWidgetButton->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout     = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);

    m_photspotButton = new QPushButton();
    m_photspotButton->setIcon(QIcon::fromTheme(KYLIN_HOTSPOT_NORMAL_NAME, QIcon(KYLIN_HOTSPOT_NORMAL_PATH)));
    m_photspotButton->setFixedSize(56, 56);
    m_photspotButton->setIconSize(QSize(24, 24));
    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");
    m_photspotButton->setStyle(m_pStyleNormal);

    m_pDeleteButton = new QPushButton();
    m_pDeleteButton->setFixedSize(20, 20);
    m_pDeleteButton->setIcon(QIcon(KYLIN_DELETE_ICONPATH));
    m_pDeleteButton->setIconSize(QSize(12, 12));

    m_photspotLabel = new QLabel(QObject::tr("热点"));
    m_photspotLabel->setAlignment(Qt::AlignHCenter);

    m_pVboxLayout = new QVBoxLayout();
    m_pVboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxLayout->setSpacing(0);

    this->setFixedSize(63, 78);
    this->setContentsMargins(0, 0, 0, 0);
    return;
}

void hotspotWidget::initLayout()
{
    m_pVboxButtonLayout->addWidget(m_photspotButton, 0, Qt::AlignCenter);
    m_pWidgetButton->setLayout(m_pVboxButtonLayout);
    m_pVboxLayout->addWidget(m_pWidgetButton, 0, Qt::AlignCenter);
    m_pVboxLayout->addItem(new QSpacerItem(15, 4));
    m_pVboxLayout->addWidget(m_photspotLabel);
    this->setLayout(m_pVboxLayout);
    m_pDeleteButton->setParent(this);
    m_pDeleteButton->move(43, 0);
    m_pDeleteButton->setVisible(false);
    return;
}
