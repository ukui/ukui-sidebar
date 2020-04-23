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
#include "submit_success.h"
#include "feedback.h"
#include "browse_button.h"

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
    this->resize(430, 260);
    setWindowTitle(tr("提交成功 "));
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口 半透明 显示阴影
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint); //设置窗口无边框

    //--------设置圆角
    QBitmap bmp(this->size());

    bmp.fill();

    QPainter p(&bmp);

    p.setPen(Qt::NoPen);

    p.setBrush(Qt::black);

    p.setRenderHint(QPainter::Antialiasing);

    p.drawRoundedRect(bmp.rect(),6,6);

    setMask(bmp);
    //----- ------------------------

    label = new QLabel(this);
    label->setText(tr("问题提交成功"));
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(130, 85, 291, 60));
    label->setStyleSheet(QString::fromUtf8("font: 30px;\n"
                                           "color: rgb(68, 68, 68);"));



    succ_closeBtn = new closeBtn_hover(this);
    succ_closeBtn->setGeometry(QRect(386, 14, 30, 30));
    succ_closeBtn->setStyleSheet("background-color: rgb(255,255,255);border-image:url(:/image/close_default.png);border-radius:4px;");
    connect(succ_closeBtn,SIGNAL(clicked()),this,SLOT(succ_close_window()));

    pushButton = new QPushButton(this);
    pushButton->setText(tr("继续反馈问题"));
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setGeometry(QRect(110, 165, 131, 26));
    pushButton->setFlat(false);
    pushButton->setStyleSheet(QString::fromUtf8("QPushButton{color: rgb(61, 107, 229);background-color:rgb(255,255,255)}"
                                                  "QPushButton:hover {color: rgb(255,255,255);background-color:rgb(107,142,235)}"
                                                  ""));
    pushButton_2 = new QPushButton(this);
    pushButton_2->setText(tr("退出"));
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_2->setGeometry(QRect(270, 165, 81, 26));
    pushButton_2->setFlat(false);
    pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton{color: rgb(61, 107, 229);background-color:rgb(255,255,255)}"
                                                  "QPushButton:hover {color: rgb(255,255,255);background-color:rgb(107,142,235)}"
                                                  ""));
    label_2 = new QLabel(this);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(70, 94, 50, 50));
    label_2->setStyleSheet(QString::fromUtf8("background-image: url(://success.png);"));

    connect(pushButton,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
    connect(pushButton_2,SIGNAL(clicked()),this,SLOT(on_pushButton_2_clicked()));
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

    // 随便绘制一个背景
    p.save();
    p.fillPath(rectPath, QColor(255, 255, 255));
    p.restore();
}
