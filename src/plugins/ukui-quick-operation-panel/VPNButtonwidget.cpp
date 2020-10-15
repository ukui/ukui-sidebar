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
#include "VPNButtonwidget.h"

diturbModeWidget::diturbModeWidget(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initLayout();
}

void diturbModeWidget::initMemberVariables()
{
    m_pButtonWidget = new QWidget();
    m_pButtonWidget->setFixedSize(56, 56);

    m_pVPNButton = new ShortcutButton();
    m_pVPNButton->m_bStatusButton = false;
    m_pVPNButton->setIcon(QIcon::fromTheme(KYLIN_VPN_NORMAL_NAME, QIcon(KYLIN_BLUETOOTH_NORMAL_PATH)));
    connect(m_pVPNButton, &ShortcutButton::clicked, this, &diturbModeWidget::VPNButtonClickSLots);
    m_pVPNButton->setFixedSize(56, 56);
    m_pVPNButton->setIconSize(QSize(24, 24));

    m_pDeleteButton = new QPushButton();
    m_pDeleteButton->setFixedSize(20, 20);
    m_pDeleteButton->setIcon(QIcon(KYLIN_DELETE_ICONPATH));
    m_pDeleteButton->setIconSize(QSize(12, 12));

    m_pLabelFotmatText = new LabelFotmatText;

    m_pVPNLabel  = new QLabel();
    m_pVPNLabel->setFixedWidth(60);
    m_pVPNLabel->setText(m_pLabelFotmatText->SetFormatBody(QObject::tr("VPN"), m_pVPNLabel));
    m_pVPNLabel->setAlignment(Qt::AlignHCenter);

    m_pVboxButtonLayout = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout->setSpacing(0);

    m_pVboxLayout       = new QVBoxLayout();
    m_pVboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxLayout->setSpacing(0);

    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");
    m_pVPNButton->setStyle(m_pStyleNormal);

    this->setFixedSize(63, 82);
    this->setContentsMargins(0, 0, 0, 0);
}

void diturbModeWidget::initLayout()
{
    m_pVboxButtonLayout->addWidget(m_pVPNButton);
    m_pButtonWidget->setLayout(m_pVboxButtonLayout);

    m_pVboxLayout->addWidget(m_pButtonWidget, 0, Qt::AlignCenter);
    m_pVboxLayout->addItem(new QSpacerItem(5, 4));
    m_pVboxLayout->addWidget(m_pVPNLabel);
    this->setLayout(m_pVboxLayout);
    m_pDeleteButton->setParent(this);
    m_pDeleteButton->move(43, 0);
    m_pDeleteButton->setVisible(false);
}

void diturbModeWidget::VPNButtonClickSLots()
{
    QProcess p(0);
    p.startDetached("ukui-control-center -v");
    p.waitForStarted();
    return;
}
