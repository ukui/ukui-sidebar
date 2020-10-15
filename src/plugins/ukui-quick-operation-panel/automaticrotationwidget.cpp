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
#include "automaticrotationwidget.h"

AutomaticRotationWidget::AutomaticRotationWidget(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initGsettingValue();
    setButtonStatus();
    initLayout();
}

void AutomaticRotationWidget::initMemberVariables()
{
    m_IconPathList << KYLIN_AUTOMATICROTATION_NORMAL_PATH << KYLIN_AUTOMATICROTATION_HOVER_PATH << KYLIN_AUTOMATICROTATION_PRESS_PATH;
    m_IconNameList << KYLIN_AUTOMATICROTATION_NORMAL_NAME << KYLIN_AUTOMATICROTATION_HOVER_NAME << KYLIN_AUTOMATICROTATION_PRESS_NAME;
    m_pWidgetButton = new QWidget();
    m_pWidgetButton->setFixedSize(56, 56);
    m_pWidgetButton->setContentsMargins(0, 0, 0, 0);
    m_pAutomaticRotationButton =  new switchButton(m_IconPathList, m_IconNameList);
    m_pAutomaticRotationButton->setFixedSize(56, 56);
    m_pAutomaticRotationButton->setIconSize(QSize(16, 16));
    connect(m_pAutomaticRotationButton, &switchButton::clicked, this, &AutomaticRotationWidget::m_pAutomaticRotationButtonClickSlots);

    m_pLabelFotmatText = new LabelFotmatText();

    m_pVboxButtonLayout = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout->setSpacing(0);

    m_pAutomaticRotationLabel = new QLabel();
    m_pAutomaticRotationLabel->setFixedWidth(60);
    m_pAutomaticRotationLabel->setText(m_pLabelFotmatText->SetFormatBody(QObject::tr("Auto rotate"), m_pAutomaticRotationLabel));
    m_pAutomaticRotationLabel->setAlignment(Qt::AlignHCenter);

    m_pStyleOpen   = new CustomStyle_SwitchOpenStatus("ukui-default");
    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");

    m_pVboxLayout = new QVBoxLayout();
    m_pVboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxLayout->setSpacing(0);

    this->setFixedSize(56, 82);
    this->setContentsMargins(0, 0, 0, 0);
}

void AutomaticRotationWidget::initLayout()
{
    m_pVboxButtonLayout->addWidget(m_pAutomaticRotationButton, 0, Qt::AlignCenter);
    m_pWidgetButton->setLayout(m_pVboxButtonLayout);
    m_pVboxLayout->addWidget(m_pWidgetButton);
    m_pVboxLayout->addItem(new QSpacerItem(1, 4));
    m_pVboxLayout->addWidget(m_pAutomaticRotationLabel);
    this->setLayout(m_pVboxLayout);
}

void AutomaticRotationWidget::initGsettingValue()
{
    /* 链接time-shutdown的dgsetting接口 */
    const QByteArray id(KYLIN_PAD_GSETTING_VALUE);
    if(QGSettings::isSchemaInstalled(id))
        m_pAutomaticRotationGsetting = new QGSettings(id);
    if (m_pAutomaticRotationGsetting != nullptr) {
        qDebug() << "当前的gsetting的key值" << m_pAutomaticRotationGsetting->keys();
        m_bAutomaticRotationStatus = m_pAutomaticRotationGsetting->get(KYLIN_AUTOMATICROTAION_STATUS).toBool();
    }
    return;
}

void AutomaticRotationWidget::setButtonStatus()
{
    m_bAutomaticRotationStatus = m_pAutomaticRotationGsetting->get(KYLIN_AUTOMATICROTAION_STATUS).toBool();
    if (m_bAutomaticRotationStatus) {
        m_pAutomaticRotationButton->setStyle(m_pStyleOpen);
    } else {
        m_pAutomaticRotationButton->setStyle(m_pStyleNormal);
    }
}

void AutomaticRotationWidget::m_pAutomaticRotationButtonClickSlots()
{
    m_bAutomaticRotationStatus = m_pAutomaticRotationGsetting->get(KYLIN_AUTOMATICROTAION_STATUS).toBool();
    if (!m_bAutomaticRotationStatus) {
        m_pAutomaticRotationButton->setStyle(m_pStyleOpen);
        m_pWidgetButton->update();
        m_bAutomaticRotationStatus = true;
    } else {
        m_pAutomaticRotationButton->setStyle(m_pStyleNormal);
        m_pWidgetButton->update();
        m_bAutomaticRotationStatus = false;
    }
    m_pAutomaticRotationGsetting->set(KYLIN_AUTOMATICROTAION_STATUS, m_bAutomaticRotationStatus);
    return;
}
