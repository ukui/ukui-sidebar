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

TextEditWidget::TextEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextEditWidget)
{
    ui->setupUi(this);

    iconInit();
}

TextEditWidget::~TextEditWidget()
{
    delete ui;
}

void TextEditWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);

    p.setBrush(opt.palette.color(QPalette::Base));
    p.setOpacity(0.9);
    p.setPen(Qt::NoPen);

    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.drawRoundedRect(opt.rect,6,6);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TextEditWidget::iconInit()
{
    QPixmap pixmap1=QPixmap(":/image/1x/bold.png");
    QPixmap pixmap2=QPixmap(":/image/1x/Italic.png");
    QPixmap pixmap3=QPixmap(":/image/1x/under_line-new.png");
    QPixmap pixmap4=QPixmap(":/image/1x/del_line.png");
    QPixmap pixmap5=QPixmap(":/image/1x/Symbol.png");
    QPixmap pixmap6=QPixmap(":/image/1x/number.png");

//    ui->blue_btn->setStyleSheet(QString::fromUtf8("border-top-right-radius:4px;\n"
//                                                  "border-top-left-radius:0px;\n"
//                                                  "border-bottom-right-radius:4px;\n"
//                                                  "border-bottom-left-radius:0px;"));
//    ui->light_blue_btn->setStyleSheet(QString::fromUtf8("color: rgba(145, 145, 145, 1);\n"
//                                                        "border-top-left-radius:4px;\n"
//                                                        "border-top-right-radius:0px;\n"
//                                                        "border-bottom-left-radius:4px;\n"
//                                                        "border-bottom-right-radius:0px;\n"));

//    ui->BoldBtn->setIcon(pixmap1);
//    ui->BoldBtn->setIconSize(QSize(36,36));
//    ui->ItalicBtn->setIcon(pixmap2);
//    ui->ItalicBtn->setIconSize(QSize(36,36));
    //ui->underlineBtn->setIcon(pixmap3);
    //ui->underlineBtn->setIconSize(QSize(36,36));
    ui->StrikeOutResolvedBtn->setIcon(pixmap4);
    ui->StrikeOutResolvedBtn->setIconSize(QSize(36,36));
    ui->showListBtn->setIcon(pixmap5);
    ui->showListBtn->setIconSize(QSize(16,16));
    ui->showNUMList->setIcon(pixmap6);
    ui->showNUMList->setIconSize(QSize(16,16));

    ui->underlineBtn->setIcon(QIcon::fromTheme("format-text-underline-symbolic"));
    ui->BoldBtn->setIcon(QIcon::fromTheme("format-text-bold-symbolic"));
    ui->ItalicBtn->setIcon(QIcon::fromTheme("format-text-italic-symbolic"));

    //取消按钮默认灰色背景
    QPalette palette = ui->BoldBtn->palette();
    QColor ColorPlaceholderText(255,255,255,0);
    QBrush brush;
    brush.setColor(ColorPlaceholderText);
    palette.setBrush(QPalette::Button, brush);
    palette.setBrush(QPalette::ButtonText, brush);
    ui->BoldBtn->setPalette(palette);
    ui->ItalicBtn->setPalette(palette);
    ui->underlineBtn->setPalette(palette);
    ui->StrikeOutResolvedBtn->setPalette(palette);
    ui->showListBtn->setPalette(palette);
    ui->showNUMList->setPalette(palette);

    QPalette palette2 = ui->blue_btn_2->palette();
    palette2.setColor(QPalette::Highlight, Qt::transparent); /* 取消按钮高亮 */
    ui->blue_btn_2->setPalette(palette2);

    ui->BoldBtn->setCheckable(true);
    ui->ItalicBtn->setCheckable(true);
    ui->underlineBtn->setCheckable(true);
    ui->StrikeOutResolvedBtn->setCheckable(true);
    ui->showListBtn->setCheckable(true);
    ui->showNUMList->setCheckable(true);
    ui->light_blue_btn->setCheckable(false);

    ui->BoldBtn->setProperty("useIconHighlightEffect", true);
    ui->BoldBtn->setProperty("iconHighlightEffectMode", 1);
    ui->ItalicBtn->setProperty("useIconHighlightEffect", true);
    ui->ItalicBtn->setProperty("iconHighlightEffectMode", 1);
    ui->underlineBtn->setProperty("useIconHighlightEffect", true);
    ui->underlineBtn->setProperty("iconHighlightEffectMode", 1);
}
