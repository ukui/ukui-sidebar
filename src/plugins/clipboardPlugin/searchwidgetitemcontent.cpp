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


#include "searchwidgetitemcontent.h"
#include <QApplication>
#include <QStyle>
#include <QFile>
SearchWidgetItemContent::SearchWidgetItemContent(QWidget *parent)
{
    Q_UNUSED(parent);
    this->setObjectName("SearhWidget");
    m_pClearListWidgetButton = new QPushButton(tr("清除"));
    m_pClearListWidgetButton->setObjectName("CleanList");

    m_pClearTextButton = new QPushButton;
    m_pClearTextButton->setObjectName("ClearTextButton");
    m_pClearTextButton->setStyleSheet("QPushButton:pressed{border-image:url(:/image/button-close-hover-click-add-background-one.svg)}");
    m_pClearTextButton->setStyleSheet("QPushButton:hover{border-image:url(:/image/button-close-hover-click-add-background-one.svg)}");
    QIcon ClearTextEditIcon;
    ClearTextEditIcon.addFile(SEARCH_SVG_CLEAN);
    m_pClearTextButton->setIcon(ClearTextEditIcon);
    m_pClearTextButton->setCursor(Qt::ArrowCursor);

    m_pHBoxLayout = new QHBoxLayout;
    m_pLineEditArea = new QLineEdit;
    m_pLineEditArea->setObjectName("SearchLabel");
    QWidgetAction* action = new QWidgetAction(m_pLineEditArea);
    action->setDefaultWidget(m_pClearTextButton);
    m_pLineEditArea->addAction(action, QLineEdit::TrailingPosition);

    connect(m_pClearTextButton, &QPushButton::clicked, this, [=](){
          m_pLineEditArea->setText("");
    });
    m_pHBoxLayout->addWidget(m_pLineEditArea);
    m_pHBoxLayout->addWidget(m_pClearListWidgetButton);
    this->setLayout(m_pHBoxLayout);
}
