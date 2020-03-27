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
#include <QFile>
EditorWidget::EditorWidget()
{
    installEventFilter(this);
    m_pMainQVBoxLayout = new QVBoxLayout();
    editBox();
    operationBox();

    m_pConfirmButton->setObjectName("ConfirmButton");
    m_pCancelButton->setObjectName("CancelButton");
    connect(m_pConfirmButton, &QPushButton::clicked, this, &EditorWidget::accept);
    connect(m_pCancelButton, &QPushButton::clicked, this, &EditorWidget::reject);
    m_pEditingArea->setObjectName("EditingArea");
    m_pEditBox->setObjectName("EditBox");
    m_pOperationBox->setObjectName("OperationBox");
    this->setObjectName("EditorWidget");
    m_pMainQVBoxLayout->addWidget(m_pEditBox);
    m_pMainQVBoxLayout->addWidget(m_pOperationBox);
    this->setWindowFlags(Qt::FramelessWindowHint);

    QScreen* pScreen = QGuiApplication::primaryScreen();
    QRect ScreenSize = pScreen->availableGeometry();
    int m_nScreenWidth = ScreenSize.width();        //屏幕分辨率的宽
    int m_nScreenHeight = ScreenSize.height();      //屏幕分辨率的高
    move(m_nScreenWidth/2-130, m_nScreenHeight/2-180);
    setLayout(m_pMainQVBoxLayout);
    setAttribute(Qt::WA_TranslucentBackground);
    QFile file(SIDEBAR_EDITAREA_QSS_PATH);
    if (file.open(QFile::ReadOnly)) {
        QString strQss = QLatin1String(file.readAll());
        QString strPaletteColor = strQss.mid(20, 7);
        this->setPalette(QPalette(QColor(strPaletteColor)));
        this->setStyleSheet(strQss);
        file.close();
    }
}

void EditorWidget::editBox()
{
    m_pEditingArea = new QTextEdit();
    m_pEditLaout = new QHBoxLayout;
    m_pEditLaout->addWidget(m_pEditingArea);
    m_pEditBox = new QGroupBox(tr("Edit"));
    m_pEditBox->setLayout(m_pEditLaout);
}

void EditorWidget::operationBox()
{
    m_pConfirmButton = new QPushButton(tr("Confirm"));
    m_pCancelButton  = new QPushButton(tr("Cancel"));
    m_pOperationLayout = new QHBoxLayout;

    m_pOperationLayout->addWidget(m_pCancelButton);
    m_pOperationLayout->addWidget(m_pConfirmButton);
    m_pOperationBox = new QGroupBox();
    m_pOperationBox->setLayout(m_pOperationLayout);
}

void EditorWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);

    p.setBrush(QBrush(QColor("#131314")));
    p.setOpacity(0.7);
    p.setPen(Qt::NoPen);

    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.drawRoundedRect(opt.rect,6,6);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
