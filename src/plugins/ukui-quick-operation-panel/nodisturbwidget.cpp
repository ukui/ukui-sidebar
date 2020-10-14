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
#include "nodisturbwidget.h"

nodisturbWidget::nodisturbWidget(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initGsettingValue();
    setEyeButtonStatus();
    initLayout();
}

nodisturbWidget::~nodisturbWidget()
{

}

void nodisturbWidget::initMemberVariables()
{
    m_pWidgetButton         = new QWidget();
    m_pWidgetButton->setFixedSize(56, 56);
    m_pWidgetButton->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout     = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);

    m_pLabelFotmatText = new LabelFotmatText;

    m_pnodisturbButton = new QPushButton();
    connect(m_pnodisturbButton, &QPushButton::clicked, this, &nodisturbWidget::setNodisturbButtonSlots);
    m_pnodisturbButton->setFixedSize(56, 56);
    m_pnodisturbButton->setIcon(QIcon::fromTheme(KYLIN_NODISTURB_NORMAL_NAME, QIcon(KYLIN_NODISTURB_NORMAL_PATH)));
    m_pnodisturbButton->setIconSize(QSize(24, 24));
    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");
    m_pnodisturbButton->setStyle(m_pStyleNormal);

    m_pDeleteButton = new QPushButton();
    m_pDeleteButton->setFixedSize(20, 20);
    m_pDeleteButton->setIcon(QIcon(KYLIN_DELETE_ICONPATH));
    m_pDeleteButton->setIconSize(QSize(12, 12));

    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");
    m_pnodisturbButton->setStyle(m_pStyleNormal);

    m_pStyleOpen = new CustomStyle_SwitchOpenStatus("ukui-default");

    m_pnodisturbLabel = new QLabel();
    m_pnodisturbLabel->setFixedWidth(60);
    m_pnodisturbLabel->setText(m_pLabelFotmatText->SetFormatBody(QObject::tr("No disturbing"), m_pnodisturbLabel));
    m_pnodisturbLabel->setAlignment(Qt::AlignHCenter);

    if (m_pLabelFotmatText->m_bTooltips) {
        this->setToolTip(QObject::tr("No disturbing"));
    }
    m_pVboxLayout = new QVBoxLayout();
    m_pVboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxLayout->setSpacing(0);

    this->setFixedSize(63, 82);
    this->setContentsMargins(0, 0, 0, 0);
    return;
}

void nodisturbWidget::initGsettingValue()
{
    const QByteArray id(UKUI_VOLUME_BRIGHTNESS_GSETTING_ID);
    if(QGSettings::isSchemaInstalled(id))
        m_pTabletModeGsetting = new QGSettings(id);
    if (m_pTabletModeGsetting != nullptr && m_pTabletModeGsetting->keys().contains(KYLIN_DISTURB_GSETTING_VALUE_STATUS))
        m_bModelStatus = m_pTabletModeGsetting->get(KYLIN_DISTURB_GSETTING_VALUE_STATUS).toBool();
    return;
}

void nodisturbWidget::initLayout()
{
    m_pVboxButtonLayout->addWidget(m_pnodisturbButton, 0, Qt::AlignCenter);
    m_pWidgetButton->setLayout(m_pVboxButtonLayout);
    m_pVboxLayout->addWidget(m_pWidgetButton, 0, Qt::AlignCenter);
    m_pVboxLayout->addItem(new QSpacerItem(15, 4));
    m_pVboxLayout->addWidget(m_pnodisturbLabel);
    this->setLayout(m_pVboxLayout);
    m_pDeleteButton->setParent(this);
    m_pDeleteButton->move(43, 0);
    m_pDeleteButton->setVisible(false);
    return;
}

QColor nodisturbWidget::getSystemPaleteColor()
{
    QStyleOption opt;
    opt.init(m_pnodisturbLabel);
    if (m_bModelStatus) {
        return opt.palette.color(QPalette::Highlight);
    } else {
        return opt.palette.color(m_pnodisturbLabel->palette().Text);
    }
}

void nodisturbWidget::setLabelTextColor()
{
    QPalette palette;
    QColor color = getSystemPaleteColor();
    palette.setBrush(QPalette::WindowText, color);
    m_pnodisturbLabel->setPalette(palette);
    this->update();
    return;
}

void nodisturbWidget::setEyeButtonStatus()
{
    if (m_bModelStatus) {
        m_pnodisturbButton->setStyle(m_pStyleOpen);
        m_pnodisturbButton->setIcon(QIcon::fromTheme(KYLIN_NODISTURB_OPEN_NAME, QIcon(KYLIN_NODISTURB_OPEN_PATH)));
    } else {
        m_pnodisturbButton->setStyle(m_pStyleNormal);
        m_pnodisturbButton->setIcon(QIcon::fromTheme(KYLIN_NODISTURB_NORMAL_NAME, QIcon(KYLIN_NODISTURB_NORMAL_PATH)));
    }
    setLabelTextColor();
    return;
}

void nodisturbWidget::setNodisturbButtonSlots()
{
    if (!m_bModelStatus) {
        m_pnodisturbButton->setStyle(m_pStyleOpen);
        m_pnodisturbButton->setIcon(QIcon::fromTheme(KYLIN_NODISTURB_OPEN_NAME, QIcon(KYLIN_NODISTURB_OPEN_PATH)));
        m_bModelStatus = true;
    } else {
        m_pnodisturbButton->setStyle(m_pStyleNormal);
        m_pnodisturbButton->setIcon(QIcon::fromTheme(KYLIN_NODISTURB_NORMAL_NAME, QIcon(KYLIN_NODISTURB_NORMAL_PATH)));
        m_bModelStatus = false;
    }
    if (m_pTabletModeGsetting->keys().contains(KYLIN_DISTURB_GSETTING_VALUE_STATUS) && \
            m_pTabletModeGsetting->keys().contains(KYLIN_DISTURB_GSETTING_VALUE_SOUNDOFF) && \
            m_pTabletModeGsetting->keys().contains(KULIN_DISTURB_GSETTING_VALUE_NOTIFYCLOSE)) {
        m_pTabletModeGsetting->set(KYLIN_DISTURB_GSETTING_VALUE_STATUS, m_bModelStatus);
        m_pTabletModeGsetting->set(KYLIN_DISTURB_GSETTING_VALUE_SOUNDOFF, m_bModelStatus);
        m_pTabletModeGsetting->set(KULIN_DISTURB_GSETTING_VALUE_NOTIFYCLOSE, m_bModelStatus);
    }
    setLabelTextColor();
    return;
}

void nodisturbWidget::paintEvent(QPaintEvent *e)
{
    QPalette palette;
    QColor color = getSystemPaleteColor();
    palette.setBrush(QPalette::WindowText, color);
    m_pnodisturbLabel->setPalette(palette);
    QWidget::paintEvent(e);
}
