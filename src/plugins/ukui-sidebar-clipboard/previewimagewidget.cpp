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

#include "previewimagewidget.h"

previewImageWidget::previewImageWidget(QPixmap *pixmap, QWidget *parent)
{
    Q_UNUSED(parent);
    m_pLabel = new QLabel();
    m_pLabel->setFixedSize(260, 130);
    int width  = m_pLabel->width();
    int height = m_pLabel->height();
    QPixmap fitpixmap = (*pixmap).scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    m_pLabel->setPixmap(fitpixmap);
    m_pVlaout = new QVBoxLayout();
    this->setContentsMargins(0, 0, 0, 0);
    m_pVlaout->setContentsMargins(0, 0, 0, 0);
    m_pVlaout->addWidget(m_pLabel);
    this->setLayout(m_pVlaout);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
}
