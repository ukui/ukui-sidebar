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
#include "submitFail.h"
#include "ukuiFeedback.h"
#include "browseButton.h"
#include <QPainterPath>

extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);

submit_fail::submit_fail(QWidget *parent) :
    QDialog(parent)
{
    UI_init();
    parentWnd = (feedback *)parent;
    setAttribute(Qt::WA_TranslucentBackground);
}

void submit_fail::UI_init()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("submit_fail"));
    setWindowTitle(tr("submit fail"));

    this->resize(350, 230);

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
    label->setText(tr("issue submitfail"));
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(111, 70, 168, 31));
    QFont font;
    font.setPixelSize(24);
    label->setFont(font);



    QPalette palette;
    QColor ColorPlaceholderText(255,255,255,0);
    QBrush brush;
    brush.setColor(ColorPlaceholderText);
    palette.setBrush(QPalette::Button, brush);
    palette.setBrush(QPalette::ButtonText, brush);

    fail_closeBtn = new QPushButton(this);
    fail_closeBtn->setGeometry(QRect(310, 15, 30, 30));
    fail_closeBtn->setIcon(QIcon::fromTheme("window-close-symbolic"));
    fail_closeBtn->setPalette(palette);
    fail_closeBtn->setProperty("useIconHighlightEffect", true);
    fail_closeBtn->setProperty("iconHighlightEffectMode", 1);




    connect(fail_closeBtn,SIGNAL(clicked()),this,SLOT(close_fail_window()));

    resendBtn = new QPushButton(this);
    resendBtn->setGeometry(QRect(130, 160, 60, 26));
    resendBtn->setText(tr("resend"));
    resendBtn->setFlat(false);
    resendBtn->hide();
    resendBtn->setStyleSheet(QString::fromUtf8("QPushButton{color: rgb(61, 107, 229);background-color:rgb(255,255,255)}"
                                               "QPushButton:hover {color: rgb(255,255,255);background-color:rgb(107,142,235)}"
                                               ""));
    connect(resendBtn,SIGNAL(clicked()),this,SLOT(resend_feedbackinfo()));

    pushButton_2 = new QPushButton(this);
    pushButton_2->setText(tr("Sure"));
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_2->setGeometry(QRect(249, 180, 80, 30));
    pushButton_2->setFlat(false);


    label_2 = new QLabel(this);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(71, 71, 30, 30));
    label_2->setPixmap(QPixmap(":/image/failed.png"));
    label_3 = new QLabel(this);
    label_3->setGeometry(QRect(71,111, 224, 19));


    connect(pushButton_2,SIGNAL(clicked()),this,SLOT(on_pushButton_2_clicked()));
}
void submit_fail::show_faillinfo(int error_code)
{
    switch (error_code) {
    case 1:
        label_3->setText(tr("The remote server refused the connection"));
        break;
    case 2:
        label_3->setText(tr("Server down"));
        break;
    case 3:
        label_3->setText(tr("Cannot find remote host name (invalid host name)"));
        break;
    case 4:
        label_3->setText(tr("Connection to remote server timed out"));
        break;
    case 99:
        label_3->setText(tr("net no connect"));
        break;
    case 403:
        label_3->setText(tr("Service Unavailable"));
        break;
    default:
        label_3->setText(tr("unknown mistake"));
        break;
    }
}
submit_fail::~submit_fail()
{
}

void submit_fail::on_pushButton_2_clicked()
{
    parentWnd->browseBtn->setEnabled(true);
    close();
}
void submit_fail::close_fail_window()
{
    this->hide();
}
void submit_fail::resend_feedbackinfo()
{
    close();
    parentWnd->resend_info_when_sendfail();

}
void submit_fail::paintEvent(QPaintEvent *e)
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
