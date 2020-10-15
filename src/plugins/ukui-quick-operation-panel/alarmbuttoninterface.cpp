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
#include "alarmbuttoninterface.h"
#include <QDebug>
alarmButtonInterface::alarmButtonInterface(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initLayout();
}

void alarmButtonInterface::initMemberVariables()
{
    m_pButtonWidget = new QWidget();
    m_pButtonWidget->setFixedSize(56, 56);

    m_pAlarmButton = new ShortcutButton();
    m_pAlarmButton->m_bStatusButton = false;     // 切换主题，判断按钮是不是状态按钮；
    connect(m_pAlarmButton, &ShortcutButton::clicked, this, &alarmButtonInterface::AlarmButtonClickSlots);
    m_pAlarmButton->setFixedSize(56, 56);
    m_pAlarmButton->setIcon(QIcon::fromTheme(KYLIN_ALARM_NORMAL_NAME));
    m_pAlarmButton->setIconSize(QSize(24, 24));

    m_pDeleteButton = new QPushButton();
    m_pDeleteButton->setFixedSize(20, 20);
    m_pDeleteButton->setIcon(QIcon(KYLIN_DELETE_ICONPATH));
    m_pDeleteButton->setIconSize(QSize(12, 12));

    m_pLabelFotmatText = new LabelFotmatText;

    m_pAlarmLabel  = new QLabel();
    m_pAlarmLabel->setFixedWidth(60);
    m_pAlarmLabel->setText(m_pLabelFotmatText->SetFormatBody(QObject::tr("Alarm"), m_pAlarmLabel));
    m_pAlarmLabel->setAlignment(Qt::AlignHCenter);

    m_pVboxButtonLayout = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout->setSpacing(0);

    m_pVboxLayout       = new QVBoxLayout();
    m_pVboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxLayout->setSpacing(0);

    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");
    m_pAlarmButton->setStyle(m_pStyleNormal);

    this->setFixedSize(63, 82);
    this->setContentsMargins(0, 0, 0, 0);
}

void alarmButtonInterface::initLayout()
{
    m_pVboxButtonLayout->addWidget(m_pAlarmButton);
    m_pButtonWidget->setLayout(m_pVboxButtonLayout);

    m_pVboxLayout->addWidget(m_pButtonWidget, 0, Qt::AlignCenter);
    m_pVboxLayout->addItem(new QSpacerItem(5, 4, QSizePolicy::Fixed));
    m_pVboxLayout->addWidget(m_pAlarmLabel);
    this->setLayout(m_pVboxLayout);
    m_pDeleteButton->setParent(this);
    m_pDeleteButton->move(43, 0);
    m_pDeleteButton->setVisible(false);
    return;
}

void alarmButtonInterface::AlarmButtonClickSlots()
{
    QProcess p(0);
    p.startDetached("ukui-clock");
    p.waitForStarted();
    return;
}
