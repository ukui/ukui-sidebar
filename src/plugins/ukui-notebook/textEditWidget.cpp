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

#include "textEditWidget.h"
#include "ui_textEditWidget.h"

extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);

TextEditWidget::TextEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextEditWidget)
{
    ui->setupUi(this);
    btnInit();
}

TextEditWidget::~TextEditWidget()
{
    delete ui;
}

void TextEditWidget::paintEvent(QPaintEvent *event)
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
    p.setOpacity(0.9);
    // 绘制一个背景
    p.save();
    p.fillPath(rectPath,palette().color(QPalette::Base));
    p.restore();
}

void TextEditWidget::btnInit()
{
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.setRenderHint(QPainter::Antialiasing);
    p.drawRoundedRect(bmp.rect(),6,6);
    setMask(bmp);

    ui->boldBtn->setIcon(QPixmap(":/image/1x/bold.png"));
    ui->italicBtn->setIcon(QPixmap(":/image/1x/Italic.png"));
    ui->underlineBtn->setIcon(QPixmap(":/image/1x/under_line-new.png"));
    ui->strikeOutBtn->setIcon(QPixmap(":/image/1x/del_line.png"));
    ui->unorderedBtn->setIcon(QPixmap(":/image/1x/Symbol.png"));
    ui->orderedBtn->setIcon(QPixmap(":/image/1x/number.png"));

    //ui->underlineBtn->setIcon(QIcon::fromTheme("format-text-underline-symbolic"));
    //ui->boldBtn->setIcon(QIcon::fromTheme("format-text-bold-symbolic"));
    //ui->italicBtn->setIcon(QIcon::fromTheme("format-text-italic-symbolic"));

    //取消按钮默认灰色背景
    QPalette palette = ui->boldBtn->palette();
    QColor ColorPlaceholderText(255,255,255,0);
    QBrush brush;
    brush.setColor(ColorPlaceholderText);
    palette.setBrush(QPalette::Button, brush);
    palette.setBrush(QPalette::ButtonText, brush);
    ui->boldBtn->setPalette(palette);
    ui->italicBtn->setPalette(palette);
    ui->underlineBtn->setPalette(palette);
    ui->strikeOutBtn->setPalette(palette);
    ui->unorderedBtn->setPalette(palette);
    ui->orderedBtn->setPalette(palette);

    QPalette palette2 = ui->fontColorBtn->palette();
    palette2.setColor(QPalette::Highlight, Qt::transparent); /* 取消按钮高亮 */
    ui->fontColorBtn->setPalette(palette2);

    ui->boldBtn->setCheckable(true);
    ui->italicBtn->setCheckable(true);
    ui->underlineBtn->setCheckable(true);
    ui->strikeOutBtn->setCheckable(true);
    ui->unorderedBtn->setCheckable(true);
    ui->orderedBtn->setCheckable(true);
    ui->fontSizeBtn->setCheckable(false);

    ui->boldBtn->setProperty("useIconHighlightEffect", true);
    ui->boldBtn->setProperty("iconHighlightEffectMode", 1);
    ui->italicBtn->setProperty("useIconHighlightEffect", true);
    ui->italicBtn->setProperty("iconHighlightEffectMode", 1);
    ui->underlineBtn->setProperty("useIconHighlightEffect", true);
    ui->underlineBtn->setProperty("iconHighlightEffectMode", 1);
    ui->strikeOutBtn->setProperty("useIconHighlightEffect", true);
    ui->strikeOutBtn->setProperty("iconHighlightEffectMode", 1);
    ui->unorderedBtn->setProperty("useIconHighlightEffect", true);
    ui->unorderedBtn->setProperty("iconHighlightEffectMode", 1);
    ui->orderedBtn->setProperty("useIconHighlightEffect", true);
    ui->orderedBtn->setProperty("iconHighlightEffectMode", 1);
}
