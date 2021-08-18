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

#include "pixmaplabel.h"

pixmapLabel::pixmapLabel()
{

}

void pixmapLabel::setPixmapList(const QList<QPixmap> &list)
{
    m_pixmapList = list;
    update();
}

void pixmapLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::transparent);

    QStyle *style = QWidget::style();
    QStyleOption opt;
    opt.initFrom(this);
    int x = 4;
    int y = 4;
    //drawPixmaps
    if (m_pixmapList.size() == 1) {
        QPixmap pix = m_pixmapList[0];
        if (!isEnabled())
            pix = style->generatedIconPixmap(QIcon::Disabled, pix, &opt);
        QPixmap newPix = pix.scaled(16, 16, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        style->drawItemPixmap(&painter, QRect(QPoint(4, 4), newPix.size()), Qt::AlignCenter, newPix);
    } else {
        for (int i = 0 ; i < m_pixmapList.size(); ++i) {
            QPixmap pix = m_pixmapList[m_pixmapList.size() - i - 1];
            if (pix.size() == QSize(0, 0))
                continue;
            if (!isEnabled())
                pix = style->generatedIconPixmap(QIcon::Disabled, pix, &opt);
            QPixmap newPix = pix.scaled(16, 16, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            style->drawItemPixmap(&painter, QRect(QPoint(x, y), newPix.size()), Qt::AlignCenter, newPix);
            x += 2;
            y += 2;
        }
    }
    return;
}
