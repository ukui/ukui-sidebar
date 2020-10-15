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

#include "buttonwidget.h"
#include <QMouseEvent>
#include <QSvgRenderer>
#include <QPixmap>
#include <QPainter>
#include <QVBoxLayout>
#include <QSvgWidget>
#include <QDebug>

ButtonWidget::ButtonWidget()
{
    initMemberVariables();
    initGsettingValue();
    return;
}

void ButtonWidget::initMemberVariables()
{
    this->setFixedSize(24, 24);
    QVBoxLayout* pVBoxLayout = new QVBoxLayout;
    pVBoxLayout->setContentsMargins(0,0,0,0);
    pVBoxLayout->setSpacing(0);

    m_pDeleteButton = new QPushButton;
    m_pDeleteButton->setProperty("iconHighlightEffectMode", true);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Highlight, Qt::transparent);      /* 取消按钮高亮 */
    m_pDeleteButton->setPalette(palette);
    m_pDeleteButton->setFixedSize(24, 24);
    m_pDeleteButton->setFlat(true);
    m_pDeleteButton->setIcon(QIcon::fromTheme(UKUI_CLOSE_ICON));
    m_pDeleteButton->setIconSize(QSize(24, 24));
    pVBoxLayout->addWidget(m_pDeleteButton, 0, Qt::AlignHCenter | Qt::AlignVCenter);
    this->setLayout(pVBoxLayout);
}

void ButtonWidget::initGsettingValue()
{
    const QByteArray id(UKUI_QT_STYLE);
    if (QGSettings::isSchemaInstalled(id)) {
        m_pTabletModeGsetting = new QGSettings(id);
        connect(m_pTabletModeGsetting, &QGSettings::changed, [=](QString key) {
            if (UKUI_QT_STYLE_NAME_KEY == key) {
                QString styleName = m_pTabletModeGsetting->get(UKUI_QT_STYLE_NAME_KEY).toString();
                qDebug() << styleName;
                if (styleName == UKUI_QT_DARK_NAME) {
                    m_pDeleteButton->setProperty("useIconHighlightEffect", true);
                } else {
                    m_pDeleteButton->setProperty("useIconHighlightEffect", false);
                }
            }
        });
    return;
}
