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
    m_pWidgetButton         = new QWidget();
    m_pWidgetButton->setFixedSize(56, 56);
    m_pWidgetButton->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout     = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);

    m_pPadButton = new QPushButton();
    m_pPadButton->setFixedSize(56, 56);
    m_pPadButton->setIconSize(QSize(24, 24));
    connect(m_pPadButton, &switchButton::clicked, this, &padWidget::PadButtonClickSlots);

    m_pDeleteButton = new QPushButton();
    m_pDeleteButton->setFixedSize(20, 20);
    m_pDeleteButton->setIcon(QIcon(KYLIN_DELETE_ICONPATH));
    m_pDeleteButton->setIconSize(QSize(12, 12));

    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");
    m_pPadButton->setStyle(m_pStyleNormal);

    m_pStyleOpen = new CustomStyle_SwitchOpenStatus("ukui-default");

    m_pPadLabel = new QLabel(QObject::tr("平板模式"));
    m_pPadLabel->setAlignment(Qt::AlignHCenter);

    m_pVboxLayout = new QVBoxLayout();
    m_pVboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxLayout->setSpacing(0);

    this->setFixedSize(63, 78);
    this->setContentsMargins(0, 0, 0, 0);
    return;
}

void padWidget::initGsettingValue()
{
    /* 链接time-shutdown的dgsetting接口 */
    const QByteArray id(KYLIN_PAD_GSETTING_VALUE);
    if(QGSettings::isSchemaInstalled(id))
        m_pTabletModeGsetting = new QGSettings(id);
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
    m_pDeleteButton->setParent(this);
    m_pDeleteButton->move(43, 0);
    m_pDeleteButton->setVisible(false);
    return;
}

void padWidget::setPadButtonStatus()
{
    if (m_bModelStatus) {
        m_pPadButton->setStyle(m_pStyleOpen);
        m_pPadButton->setIcon(QIcon::fromTheme(KYLIN_PAD_NORMAL_NAME, QIcon(KYLIN_PAD_NORMAL_PATH)));
        m_pWidgetButton->update();
    } else {
        m_pPadButton->setStyle(m_pStyleNormal);
        m_pPadButton->setIcon(QIcon::fromTheme(KYLIN_PC_NORMAL_NAME, QIcon(KYLIN_PC_NORMAL_PATH)));
        m_pWidgetButton->update();
    }
    setLabelTextColor();
    return;
}

QColor padWidget::getSystemPaleteColor()
{
    QStyleOption opt;
    opt.init(m_pPadLabel);
    if (m_bModelStatus) {
        return opt.palette.color(QPalette::Highlight);
    } else {
        return opt.palette.color(QPalette::Text);
    }
}

void padWidget::setLabelTextColor()
{
    QPalette palette;
    QColor color = getSystemPaleteColor();
    palette.setBrush(QPalette::WindowText, color);
    m_pPadLabel->setPalette(palette);
    this->update();
}

void padWidget::PadButtonClickSlots()
{
    // 判断当前状态
    m_bModelStatus = m_pTabletModeGsetting->get(KYLIN_PAD_MODLE).toBool();
    if (!m_bModelStatus) {
        m_pPadButton->setStyle(m_pStyleOpen);
        m_pPadButton->setIcon(QIcon::fromTheme(KYLIN_PAD_NORMAL_NAME, QIcon(KYLIN_PAD_NORMAL_PATH)));
        m_pWidgetButton->update();
        m_bModelStatus = true;
    } else {
        m_pPadButton->setStyle(m_pStyleNormal);
        m_pPadButton->setIcon(QIcon::fromTheme(KYLIN_PC_NORMAL_NAME, QIcon(KYLIN_PC_NORMAL_PATH)));
        m_pWidgetButton->update();
        m_bModelStatus = false;
    }
    setLabelTextColor();
    m_pTabletModeGsetting->set(KYLIN_PAD_MODLE, m_bModelStatus);
}
