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


#include "clipboardwidgetentry.h"

ClipboardWidgetEntry::ClipboardWidgetEntry(QWidget *parent)
{
    Q_UNUSED(parent);
    this->setObjectName("WidgetEntry");
    this->setContentsMargins(0,0,0,0);
    QIcon EditIcon;
    EditIcon.addFile(EDIT_SVG_PATH);
    QIcon PopIcon;
    PopIcon.addFile(COPY_SVG_PATH);
    QIcon RemoveIcon;
    RemoveIcon.addFile(REMOVE_SVG_PATH);
    m_pPopButton     = new QPushButton();
//    m_pPopButton->setToolTip(tr("Pop"));
    m_pPopButton->setFixedSize(34, 34);
    m_pPopButton->setIcon(PopIcon);
    m_pPopButton->setObjectName("PopButton");
    m_pEditButon     = new QPushButton();
//    m_pEditButon->setToolTip(tr("EditButton"));
    m_pEditButon->setFixedSize(34, 34);
    m_pEditButon->setIcon(EditIcon);
    m_pEditButon->setObjectName("EditButon");
    m_pRemoveButton  = new QPushButton();
//    m_pRemoveButton->setToolTip(tr("Remove"));
    m_pRemoveButton->setFixedSize(34, 34);
    m_pRemoveButton->setIcon(RemoveIcon);
    m_pRemoveButton->setObjectName("RemoveButton");
    m_pCopyDataLabal = new QLabel();
    m_pCopyDataLabal->setObjectName("EntryLable");
    m_pCopyDataLabal->setFixedSize(260, 34);
    m_pHLayout       = new QHBoxLayout();
    m_pHLayout->setContentsMargins(0,0,0,0);
    m_pHLayout->addItem(new QSpacerItem(10,20));
    m_pHLayout->addWidget(m_pCopyDataLabal);
    m_pHLayout->addItem(new QSpacerItem(118, 20));
    m_pHLayout->addWidget(m_pPopButton);
    m_pHLayout->addWidget(m_pEditButon);
    m_pHLayout->addWidget(m_pRemoveButton);
    m_pHLayout->addItem(new QSpacerItem(10,20));
    m_pHLayout->setSpacing(5);
    m_pPopButton->setVisible(false);
    m_pEditButon->setVisible(false);
    m_pRemoveButton->setVisible(false);
    this->setLayout(m_pHLayout);
}

void ClipboardWidgetEntry::enterEvent(QEvent *e)
{
    if(e == nullptr) {
        return;
    }
    m_pPopButton->setVisible(true);
    m_pEditButon->setVisible(true);
    m_pRemoveButton->setVisible(true);
}

void ClipboardWidgetEntry::leaveEvent(QEvent *e)
{
    if(e == nullptr) {
        return;
    }
    m_pPopButton->setVisible(false);
    m_pEditButon->setVisible(false);
    m_pRemoveButton->setVisible(false);
}
