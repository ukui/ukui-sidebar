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

#include <QPainterPath>
#include <QDebug>

#include "noteHeadMenu.h"
#include "ui_noteHeadMenu.h"

static QPixmap drawSymbolicColoredPixmap (const QPixmap&, QPushButton *);

noteHeadMenu::noteHeadMenu(QWidget *parent) :
    QWidget(parent)
  , ui(new Ui::noteHeadMenu)
  , color_widget(15,161,90)

{
    ui->setupUi(this);
    setMinimumSize(250,34);
    btnInit();
}

noteHeadMenu::~noteHeadMenu()
{
    delete ui;
}

void noteHeadMenu::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    painter.setBrush(QBrush(color_widget));
    painter.setPen(Qt::transparent);
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 0);
    rect.setHeight(rect.height() - 0);
    painter.drawRoundedRect(rect, 7, 0);
    //也可用QPainterPath 绘制代替 painter.drawRoundedRect(rect, 15, 15);
    {
        QPainterPath painterPath;
        painterPath.addRoundedRect(rect, 7, 0);
        painter.drawPath(painterPath);
    }
    QWidget::paintEvent(event);
}

void noteHeadMenu::btnInit()
{
    ui->pushButtonExit->setIcon(drawSymbolicColoredPixmap(QIcon::fromTheme("window-close-symbolic").pixmap(16,16), ui->pushButtonExit));
    ui->pushButtonMenu->setIcon(drawSymbolicColoredPixmap(QIcon::fromTheme("open-menu-symbolic").pixmap(16,16), ui->pushButtonMenu));

    QString _Stylesheet = "QPushButton{background-color: rgba(0,0,0,0);}"
                  "QPushButton:hover{background-color: rgba(0,0,0,0.12);}"
                  "QPushButton:pressed{background-color: rgba(0,0,0,0.2);}";

    ui->pushButtonNew->setStyleSheet("QPushButton{border-image:url(:/image/1x/new-normal.png);}"
                                "QPushButton:hover{border-image:url(:/image/1x/new-hover.png);}"
                                "QPushButton:pressed{border-image:url(:/image/1x/new-click.png);}");

    ui->pushButtonExit->setStyleSheet(_Stylesheet);
    ui->pushButtonMenu->setStyleSheet(_Stylesheet);

    QPalette palette = ui->pushButtonExit->palette();
    palette.setColor(QPalette::Highlight, Qt::transparent); /* 取消按钮高亮 */
    ui->pushButtonExit->setPalette(palette);
    ui->pushButtonMenu->setPalette(palette);

    ui->pushButtonMenu->hide();
    ui->pushButtonNew->hide();
}

QPixmap drawSymbolicColoredPixmap(const QPixmap& source, QPushButton *btn)
{
    QColor baseColor = btn->palette().color(QPalette::Text).light(150);
    QImage img = source.toImage();

    qDebug() << "drawSymbolicColoredPixmap" << baseColor.red() << baseColor.green() <<baseColor.blue();
    for (int x = 0; x < img.width(); ++x) {
        for (int y = 0; y < img.height(); ++y) {
            auto color = img.pixelColor(x, y);
            color.setRed(255 - baseColor.red());
            color.setGreen(255 - baseColor.green());
            color.setBlue(255 - baseColor.blue());
            img.setPixelColor(x, y, color);
        }
    }

    return QPixmap::fromImage(img);
}
