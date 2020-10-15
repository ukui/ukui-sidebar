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
#include "editconfirmationarea.h"

EditConfirmationArea::EditConfirmationArea(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initLayout();
}

void EditConfirmationArea::initMemberVariables()
{
    m_pAddButton = new QPushButton();
    m_pAddButton->setIcon(QIcon::fromTheme("aaaa", QIcon(":/image/fold-normal.svg")));
    m_pAddButton->setText(QObject::tr("append"));
    m_pAddButton->setFixedSize(96, 32);

    m_pCompleteAreaButton = new QPushButton(QObject::tr("Complete"));
    m_pCompleteAreaButton->setFixedSize(96, 32);

    m_pHboxAreaLayout = new QHBoxLayout();
    m_pHboxAreaLayout->setContentsMargins(0, 0, 0, 0);
    m_pHboxAreaLayout->setSpacing(0);
    this->setContentsMargins(0, 0, 0, 0);
    return;
}

void EditConfirmationArea::initLayout()
{
    m_pHboxAreaLayout->addItem(new QSpacerItem(92, 10));
    m_pHboxAreaLayout->addWidget(m_pAddButton);
    m_pHboxAreaLayout->addItem(new QSpacerItem(16, 10));
    m_pHboxAreaLayout->addWidget(m_pCompleteAreaButton);
    m_pHboxAreaLayout->addItem(new QSpacerItem(92, 10));
    this->setLayout(m_pHboxAreaLayout);
}
