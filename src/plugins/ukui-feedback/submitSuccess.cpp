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
#include "submitSuccess.h"
#include "ukuiFeedback.h"
#include "browseButton.h"
#include <QPainterPath>
extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);
submit_success::submit_success(QWidget *parent) :
    QDialog(parent)
{
    parentWnd = (feedback *)parent;
    UI_init();
}
void submit_success::UI_init()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("submit_success"));
    this->resize(350, 230);
    setWindowTitle(tr("Submitted success "));
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.setRenderHint(QPainter::Antialiasing);
    p.drawRoundedRect(bmp.rect(),6,6);
    setMask(bmp);
    //----- ------------------------

    QLabel *logoLabel = new QLabel(this);
    logoLabel->setPixmap(QPixmap("://image/24x24/kylin-feedback.png"));
    logoLabel->setGeometry(QRect(8,8,24,24));

    QLabel *titleLabel = new QLabel(this);
    titleLabel->setText(tr("feedback"));
    titleLabel->setGeometry(QRect(40,11,56,19));
    titleLabel->setStyleSheet(QString::fromUtf8("font: 14px;\n"));

    label = new QLabel(this);
    label->setText(tr("submitted success"));
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(111, 70, 168, 31));
    label->setStyleSheet(QString::fromUtf8("font: 24px;\n"));

    QPalette palette;
    QColor ColorPlaceholderText(255,255,255,0);
    QBrush brush;
    brush.setColor(ColorPlaceholderText);
    palette.setBrush(QPalette::Button, brush);
    palette.setBrush(QPalette::ButtonText, brush);

    succ_closeBtn = new QPushButton(this);
    succ_closeBtn->setGeometry(QRect(310, 15, 30, 30));
    succ_closeBtn->setIcon(QIcon::fromTheme("window-close-symbolic"));
    succ_closeBtn->setPalette(palette);
    succ_closeBtn->setProperty("useIconHighlightEffect", true);
    succ_closeBtn->setProperty("iconHighlightEffectMode", 1);
    connect(succ_closeBtn,SIGNAL(clicked()),this,SLOT(succ_close_window()));

    pushButton = new QPushButton(this);
    pushButton->setText(tr("Continue"));
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setGeometry(QRect(110, 165, 131, 26));
    pushButton->setFlat(false);
    pushButton->hide();

    pushButton_2 = new QPushButton(this);
    pushButton_2->setText(tr("Sure"));
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_2->setGeometry(QRect(249, 180, 80, 30));

    label_2 = new QLabel(this);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(71, 71, 30, 30));
    label_2->setPixmap(QPixmap(":/image/success.png"));
    connect(pushButton_2,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
    qDebug()<<"submit_success::UI_init()";
    this->show();
}
submit_success::~submit_success()
{

}

void submit_success::on_pushButton_2_clicked()
{
    this->close();
    parentWnd->window_close();
}

void submit_success::on_pushButton_clicked()
{
    parentWnd ->feedback_info_init();
    close();
}
void submit_success::succ_close_window()
{
    this->close();
}
void submit_success::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    QPainterPath rectPath;
    rectPath.addRoundedRect(this->rect().adjusted(10, 10, -10, -10), 5, 5);

    QPixmap pixmap(this->rect().size());
    pixmap.fill(Qt::transparent);
    QPainter pixmapPainter(&pixmap);
    pixmapPainter.setRenderHint(QPainter::Antialiasing);
    pixmapPainter.setPen(Qt::transparent);
    pixmapPainter.setBrush(Qt::black);
    pixmapPainter.drawPath(rectPath);
    pixmapPainter.end();

    QImage img = pixmap.toImage();
    qt_blurImage(img, 10, false, false);

    pixmap = QPixmap::fromImage(img);
    QPainter pixmapPainter2(&pixmap);
    pixmapPainter2.setRenderHint(QPainter::Antialiasing);
    pixmapPainter2.setCompositionMode(QPainter::CompositionMode_Clear);
    pixmapPainter2.setPen(Qt::transparent);
    pixmapPainter2.setBrush(Qt::transparent);
    pixmapPainter2.drawPath(rectPath);

    p.drawPixmap(this->rect(), pixmap, pixmap.rect());

    QStyleOption *option = new QStyleOption();
    p.save();
    p.fillPath(rectPath, option->palette.color(QPalette::Base));
    p.restore();
}
