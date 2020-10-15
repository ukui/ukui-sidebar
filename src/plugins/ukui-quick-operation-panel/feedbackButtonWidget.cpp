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
#include "feedbackButtonWidget.h"

feedbackButtonWidget::feedbackButtonWidget(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initLayout();
}

void feedbackButtonWidget::initMemberVariables()
{
    m_pButtonWidget = new QWidget();
    m_pButtonWidget->setFixedSize(56, 56);

    m_pFeedBackButton = new QPushButton();
    connect(m_pFeedBackButton, &switchButton::clicked, this, &feedbackButtonWidget::FeedbackButtonClickSlots);
    m_pFeedBackButton->setFixedSize(56, 56);
    m_pFeedBackButton->setIcon(QIcon::fromTheme(KYLIN_FEEDBACK_NORMAL_NAME, QIcon(KYLIN_AlARM_NORMAL_PATH)));
    m_pFeedBackButton->setIconSize(QSize(24, 24));

    m_pDeleteButton = new QPushButton();
    m_pDeleteButton->setFixedSize(20, 20);
    m_pDeleteButton->setIcon(QIcon(KYLIN_DELETE_ICONPATH));
    m_pDeleteButton->setIconSize(QSize(12, 12));

    m_pLabelFotmatText = new LabelFotmatText;

    m_pFeedBackLabel  = new QLabel();
    m_pFeedBackLabel->setFixedWidth(60);
    m_pFeedBackLabel->setText(m_pLabelFotmatText->SetFormatBody(QObject::tr("Feedback"), m_pFeedBackLabel));
    m_pFeedBackLabel->setAlignment(Qt::AlignHCenter);

    m_pVboxButtonLayout = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout->setSpacing(0);

    m_pVboxLayout       = new QVBoxLayout();
    m_pVboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxLayout->setSpacing(0);

    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");
    m_pFeedBackButton->setStyle(m_pStyleNormal);

    this->setFixedSize(63, 82);
    this->setContentsMargins(0, 0, 0, 0);
}

void feedbackButtonWidget::initLayout()
{
    m_pVboxButtonLayout->addWidget(m_pFeedBackButton);
    m_pButtonWidget->setLayout(m_pVboxButtonLayout);

    m_pVboxLayout->addWidget(m_pButtonWidget, 0, Qt::AlignCenter);
    m_pVboxLayout->addItem(new QSpacerItem(5, 4));
    m_pVboxLayout->addWidget(m_pFeedBackLabel);
    this->setLayout(m_pVboxLayout);
    m_pDeleteButton->setParent(this);
    m_pDeleteButton->move(43, 0);
    m_pDeleteButton->setVisible(false);
    return;
}

void feedbackButtonWidget::FeedbackButtonClickSlots()
{
    QProcess p(0);
    p.startDetached("ukui-feedback");
    p.waitForStarted();
    return;
}
