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
#include "deleteMsg.h"
#include "ui_deleteMsg.h"
#include <X11/Xlib.h>
#include "xatom-helper.h"

extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);

delete_msg::delete_msg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_msg)
{
    ui->setupUi(this);

    // 添加窗管协议
    MotifWmHints hints;
    hints.flags = MWM_HINTS_FUNCTIONS|MWM_HINTS_DECORATIONS;
    hints.functions = MWM_FUNC_ALL;
    hints.decorations = MWM_DECOR_BORDER;
    XAtomHelper::getInstance()->setWindowMotifHint(this->winId(), hints);
//    this->setProperty("blurRegion", QRegion(QRect(1, 1, 1, 1)));
//    setAttribute(Qt::WA_TranslucentBackground);
//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    QPalette palette = ui->surebtn->palette();
    QColor ColorPlaceholderText(61,107,229,255);
    QBrush brush2;
    brush2.setColor(ColorPlaceholderText);
    palette.setColor(QPalette::Button,QColor(61,107,229,255));
    palette.setBrush(QPalette::ButtonText, QBrush(Qt::white));
    ui->surebtn->setPalette(palette);

    QPalette palette1 = ui->closebtn->palette();
    QColor ColorPlaceholderText1(255,255,255,0);
    QBrush brush;
    brush.setColor(ColorPlaceholderText1);
    palette.setBrush(QPalette::Button, brush);
    ui->closebtn->setPalette(palette1);

    ui->closebtn->setIcon(QIcon::fromTheme("window-close-symbolic"));
    ui->closebtn->setProperty("isWindowButton", 0x2);
    ui->closebtn->setProperty("useIconHighlightEffect", 0x8);
    //保存按钮边框是否凸起
    ui->closebtn->setFlat(true);
}

delete_msg::~delete_msg()
{
    delete ui;
}

void delete_msg::on_closebtn_clicked()
{
    close_sure = 0;
    this->close();
}

void delete_msg::on_surebtn_clicked()
{
    close_sure = 1;
    this->close();
}

void delete_msg::on_cancelbtn_clicked()
{
    close_sure = 0;
    this->close();
}

void delete_msg::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    QPainterPath rectPath;
    rectPath.addRect(this->rect());
    p.fillPath(rectPath,palette().color(QPalette::Base));
}

void delete_msg::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->dragPosition = event->globalPos() - frameGeometry().topLeft();
        this->mousePressed = true;
    }
    QWidget::mousePressEvent(event);
}

void delete_msg::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->mousePressed = false;
        this->setCursor(Qt::ArrowCursor);
    }

    QWidget::mouseReleaseEvent(event);
}

void delete_msg::mouseMoveEvent(QMouseEvent *event)
{
    if (this->mousePressed) {
        move(event->globalPos() - this->dragPosition);
        this->setCursor(Qt::ClosedHandCursor);
    }

    QWidget::mouseMoveEvent(event);
}
