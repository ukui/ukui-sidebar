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
#include "padwidget.h"

padWidget::padWidget(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initGsettingValue();
    setPadButtonStatus();
    initLayout();
}

padWidget::~padWidget()
{

}

void padWidget::initMemberVariables()
{
    m_IconPathList << KYLIN_PAD_NORMAL_PATH << KYLIN_PAD_HOVER_PATH << KYLIN_PAD_PRESS_PATH;
    m_IconNameList << KYLIN_PAD_NORMAL_NAME << KYLIN_PAD_HOVER_NAME << KYLIN_PAD_PRESS_NAME;

    m_pWidgetButton         = new QWidget();
    m_pWidgetButton->setFixedSize(56, 56);
    m_pWidgetButton->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout     = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);

    m_pPadButton = new switchButton(m_IconPathList, m_IconNameList);
    m_pPadButton->setFixedSize(56, 56);
    m_pPadButton->setIconSize(QSize(32, 32));
    connect(m_pPadButton, &switchButton::clicked, this, &padWidget::PadButtonClickSlots);

    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");
    m_pPadButton->setStyle(m_pStyleNormal);

    m_pStyleOpen = new CustomStyle_SwitchOpenStatus("ukui-default");

    m_pPadLabel = new QLabel(QObject::tr("平板模式"));
//    m_pPadLabel->setFixedSize(80, 16);
    m_pPadLabel->setAlignment(Qt::AlignHCenter);

    m_pVboxLayout = new QVBoxLayout();
    m_pVboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxLayout->setSpacing(0);

    this->setFixedSize(56, 78);
    this->setContentsMargins(0, 0, 0, 0);
    return;
}

void padWidget::initGsettingValue()
{
    /* 链接time-shutdown的dgsetting接口 */
    if(QGSettings::isSchemaInstalled(KYLIN_PAD_GSETTING_VALUE))
        m_pTabletModeGsetting = new QGSettings(KYLIN_PAD_GSETTING_VALUE);
    if (m_pTabletModeGsetting != nullptr) {
        qDebug() << "当前的gsetting的key值" << m_pTabletModeGsetting->keys();
        m_bModelStatus = m_pTabletModeGsetting->get(KYLIN_PAD_MODLE).toBool();
    }
    return;
}

void padWidget::initLayout()
{
    m_pVboxButtonLayout->addWidget(m_pPadButton, 0, Qt::AlignCenter);
    m_pWidgetButton->setLayout(m_pVboxButtonLayout);
    m_pVboxLayout->addWidget(m_pWidgetButton, 0, Qt::AlignCenter);
    m_pVboxLayout->addItem(new QSpacerItem(15, 4));
    m_pVboxLayout->addWidget(m_pPadLabel);
    this->setLayout(m_pVboxLayout);
    return;
}

void padWidget::setPadButtonStatus()
{
    if (m_bModelStatus) {
        m_pPadButton->setStyle(m_pStyleOpen);
        m_pWidgetButton->update();
    } else {
        m_pPadButton->setStyle(m_pStyleNormal);
        m_pWidgetButton->update();
    }
    return;
}

void padWidget::PadButtonClickSlots()
{
    // 判断当前状态
    m_bModelStatus = m_pTabletModeGsetting->get(KYLIN_PAD_MODLE).toBool();
    if (!m_bModelStatus) {
        m_pPadButton->setStyle(m_pStyleOpen);
        m_pWidgetButton->update();
        m_bModelStatus = true;
    } else {
        m_pPadButton->setStyle(m_pStyleNormal);
        m_pWidgetButton->update();
        m_bModelStatus = false;
    }
    m_pTabletModeGsetting->set(KYLIN_PAD_MODLE, m_bModelStatus);
}
