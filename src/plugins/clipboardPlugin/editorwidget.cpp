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


#include "editorwidget.h"

EditorWidget::EditorWidget()
{
    m_pMainQVBoxLayout = new QVBoxLayout();
    editBox();
    operationBox();
    this->setObjectName("EditorWidget");
    m_pConfirmButton->setObjectName("ConfirmButton");
    m_pCancelButton->setObjectName("CancelButton");
    m_pEditingArea->setObjectName("EditingArea");
    m_pEditBox->setObjectName("EditBox");
    m_pOperationBox->setObjectName("OperationBox");
    m_pMainQVBoxLayout->addWidget(m_pEditBox);
    m_pMainQVBoxLayout->addWidget(m_pOperationBox);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(400,338);

    QScreen* pScreen = QGuiApplication::primaryScreen();
    QRect ScreenSize = pScreen->availableGeometry();
    int m_nScreenWidth = ScreenSize.width();        //屏幕分辨率的宽
    int m_nScreenHeight = ScreenSize.height();      //屏幕分辨率的高
    move(m_nScreenWidth/2-130, m_nScreenHeight/2-180);
    setLayout(m_pMainQVBoxLayout);
}

//void EditorWidget::titleBox()
//{
//    m_ptileLable = new QLabel(tr("编辑"));
//    QFont ft;
//    ft.setPointSize(14);
//    m_ptileLable->setFont(ft);
//    m_ptileLayout = new QHBoxLayout;
//    m_ptileLayout->addWidget(m_ptileLable);
//    m_pTitleBox = new QGroupBox();
//    m_pTitleBox->setLayout(m_ptileLayout);
//}

void EditorWidget::editBox()
{
    m_pEditingArea = new QTextEdit();
    m_pEditingArea->setFixedSize(340, 200);
    m_pEditLaout = new QHBoxLayout;
    m_pEditLaout->addWidget(m_pEditingArea);
    m_pEditBox = new QGroupBox(tr("编辑内容"));
    m_pEditBox->setLayout(m_pEditLaout);
}

void EditorWidget::operationBox()
{
    m_pConfirmButton = new QPushButton("确认");
    m_pCancelButton  = new QPushButton("取消");
    m_pOperationLayout = new QHBoxLayout;

    m_pOperationLayout->addWidget(m_pCancelButton);
    m_pOperationLayout->addWidget(m_pConfirmButton);
    m_pOperationBox = new QGroupBox();
    m_pOperationBox->setLayout(m_pOperationLayout);
}
