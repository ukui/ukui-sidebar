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

#include "paletteWidget.h"
#include "ui_paletteWidget.h"

extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);

PaletteWidget::PaletteWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaletteWidget)
{
    ui->setupUi(this);

    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.setRenderHint(QPainter::Antialiasing);
    p.drawRoundedRect(bmp.rect(),6,6);
    setMask(bmp);
    btnSetup();
}

PaletteWidget::~PaletteWidget()
{
    delete ui;
}

void PaletteWidget::btnSetup()
{
    ui->blueBtn->setStyleSheet("background:rgba(76,119,231,1);"
                               "border-radius:2px;");
    ui->redBtn->setStyleSheet("background:rgba(250,108,99,1);"
                               "border-radius:2px;");
    ui->darkGreenBtn->setStyleSheet("background:rgba(15,161,90,1);"
                               "border-radius:2px;");
    ui->orangeBtn->setStyleSheet("background:rgba(255,151,47,1);"
                               "border-radius:2px;");
    ui->purpleBtn->setStyleSheet("background:rgba(186,123,216,1);"
                               "border-radius:2px;");
    ui->goldenBtn->setStyleSheet("background:rgba(248,209,93,1);"
                               "border-radius:2px;");
    ui->lightBlueBtn->setStyleSheet("background:rgba(42,162,217,1);"
                               "border-radius:2px;");
    ui->lightGreenBtn->setStyleSheet("background:rgba(110,207,67,1);"
                               "border-radius:2px;");
    ui->yellowBtn->setStyleSheet("background:rgba(144,101,255,1);"
                               "border-radius:2px;");
    ui->pinkBtn->setStyleSheet("background:rgba(245,80,159,1);"
                               "border-radius:2px;");
}

void PaletteWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;

    QPainterPath rectPath;
    rectPath.addRoundedRect(this->rect().adjusted(1, 1, -1, -1), 6, 6);

    // 画一个黑底
    QPixmap pixmap(this->rect().size());
    pixmap.fill(Qt::transparent);
    QPainter pixmapPainter(&pixmap);
    pixmapPainter.setRenderHint(QPainter::Antialiasing);
    pixmapPainter.setPen(Qt::transparent);
    pixmapPainter.setBrush(Qt::black);
    pixmapPainter.drawPath(rectPath);
    pixmapPainter.end();

    // 模糊这个黑底
    QImage img = pixmap.toImage();
    qt_blurImage(img, 10, false, false);

    // 挖掉中心
    pixmap = QPixmap::fromImage(img);
    QPainter pixmapPainter2(&pixmap);
    pixmapPainter2.setRenderHint(QPainter::Antialiasing);
    pixmapPainter2.setCompositionMode(QPainter::CompositionMode_Clear);
    pixmapPainter2.setPen(Qt::transparent);
    pixmapPainter2.setBrush(Qt::transparent);
    pixmapPainter2.drawPath(rectPath);

    // 绘制阴影
    p.drawPixmap(this->rect(), pixmap, pixmap.rect());

    // 绘制一个背景
    p.save();
    p.fillPath(rectPath,palette().color(QPalette::Base));
    p.restore();
}
