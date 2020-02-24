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
    QIcon EditIcon;
    EditIcon.addFile(EDIT_SVG_PATH);
    QIcon PopIcon;
    PopIcon.addFile(COPY_SVG_PATH);
    QIcon RemoveIcon;
    RemoveIcon.addFile(REMOVE_SVG_PATH);
    m_pPopButton     = new QPushButton();
    m_pPopButton->setFixedSize(34, 34);
    m_pPopButton->setIcon(PopIcon);
    m_pPopButton->setObjectName("PopButton");
    m_pEditButon     = new QPushButton();
    m_pEditButon->setFixedSize(34, 34);
    m_pEditButon->setIcon(EditIcon);
    m_pEditButon->setObjectName("EditButon");
    m_pRemoveButton  = new QPushButton();
    m_pRemoveButton->setFixedSize(34, 34);
    m_pRemoveButton->setIcon(RemoveIcon);
    m_pRemoveButton->setObjectName("RemoveButton");
    m_pCopyDataLabal = new QLabel();
//    m_pCopyDataLabal->fontMetrics().elidedText(strText, Qt::ElideRight, 20, Qt::TextShowMnemonic);
//    m_pCopyDataLabal->setFixedSize(200, 34);
    m_pCopyDataLabal->setObjectName("EntryQLineEdit");
    m_pHLayout       = new QHBoxLayout();
    m_pHLayout->addWidget(m_pCopyDataLabal);
    m_pHLayout->addWidget(m_pPopButton);
    m_pHLayout->addWidget(m_pEditButon);
    m_pHLayout->addWidget(m_pRemoveButton);
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
    m_pCopyDataLabal->setStyleSheet("QWidget#WidgetEntry>QLabel{width:200px;height:34px;margin-right: 0px;} ");
    qDebug()<<tr("鼠标进入主界面事件");
}

void ClipboardWidgetEntry::leaveEvent(QEvent *e)
{
    if(e == nullptr) {
        return;
    }
    m_pPopButton->setVisible(false);
    m_pEditButon->setVisible(false);
    m_pRemoveButton->setVisible(false);
    m_pCopyDataLabal->setStyleSheet("QWidget#WidgetEntry>QLabel{width:200px;height:34px;margin-right: 120px}");
    qDebug()<<tr("鼠标离开主界面事件");
}
