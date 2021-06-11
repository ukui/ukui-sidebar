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
#include "calculatorwidget.h"
#include <QDebug>

calculatorWidget::calculatorWidget(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initLayout();
}

calculatorWidget::~calculatorWidget()
{

}

void calculatorWidget::initMemberVariables()
{
    m_pWidgetButton         = new QWidget();
    m_pWidgetButton->setFixedSize(56, 56);
    m_pWidgetButton->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout     = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);

    m_pLabelFotmatText = new LabelFotmatText;

    m_pcalculatorButton = new ShortcutButton();
    m_pcalculatorButton->m_bStatusButton = false;
    m_pcalculatorButton->setFixedSize(56, 56);
    m_pcalculatorButton->setIcon(QIcon::fromTheme(KYLIN_CALCULATOR_NORMAL_NAME, QIcon(KYLIN_CALCULATOR_NORMAL_PATH)));
    m_pcalculatorButton->setIconSize(QSize(24, 24));
    connect(m_pcalculatorButton, &ShortcutButton::clicked, this, &calculatorWidget::calculatorButtonClickSlots);

    m_pDeleteButton = new QPushButton();
    m_pDeleteButton->setFixedSize(20, 20);
    m_pDeleteButton->setIcon(QIcon(KYLIN_DELETE_ICONPATH));
    m_pDeleteButton->setIconSize(QSize(12, 12));

    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");
    m_pcalculatorButton->setStyle(m_pStyleNormal);

    m_pcalculatorLabel = new QLabel();
    m_pcalculatorLabel->setFixedWidth(60);
    m_pcalculatorLabel->setText(m_pLabelFotmatText->SetFormatBody(QObject::tr("Calculator"), m_pcalculatorLabel));
    m_pcalculatorLabel->setAlignment(Qt::AlignHCenter);

    if (m_pLabelFotmatText->m_bTooltips) {
        this->setToolTip(QObject::tr("Calculator"));
    }

    m_pVboxLayout = new QVBoxLayout();
    m_pVboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxLayout->setSpacing(0);

    this->setFixedSize(63, 82);
    this->setContentsMargins(0, 0, 0, 0);
    return;
}

void calculatorWidget::initLayout()
{
    m_pVboxButtonLayout->addWidget(m_pcalculatorButton, 0, Qt::AlignCenter);
    m_pWidgetButton->setLayout(m_pVboxButtonLayout);
    m_pVboxLayout->addWidget(m_pWidgetButton, 0, Qt::AlignCenter);
    m_pVboxLayout->addItem(new QSpacerItem(15, 4));
    m_pVboxLayout->addWidget(m_pcalculatorLabel);
    this->setLayout(m_pVboxLayout);
    m_pDeleteButton->setParent(this);
    m_pDeleteButton->move(43, 0);
    m_pDeleteButton->setVisible(false);
    return;
}

void calculatorWidget::calculatorButtonClickSlots()
{
    qDebug()<<"计算器......";
    QProcess p(0);
    p.startDetached("mate-calculator");
    p.waitForStarted();
    return;
}
