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
#ifndef DELETE_MSG_H
#define DELETE_MSG_H

#include <QDialog>
#include <QStyleOption>
#include <QPainter>
#include <QPainterPath>
namespace Ui {
class delete_msg;
}

class delete_msg : public QDialog
{
    Q_OBJECT

public:
    explicit delete_msg(QWidget *parent = nullptr);
    ~delete_msg();
    int close_sure;
    //绘制底部阴影
    // Draw bottom shadow
    void paintEvent(QPaintEvent *event)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
        painter.setBrush(QBrush(QColor(86, 86, 86)));
        painter.setPen(Qt::transparent);
        QRect rect = this->rect();
        rect.setWidth(rect.width() - 0);
        rect.setHeight(rect.height() - 0);
        painter.drawRoundedRect(rect, 7, 7);
        {
            QPainterPath painterPath;
            painterPath.addRoundedRect(rect, 7, 7);
            painter.drawPath(painterPath);
        }
        QWidget::paintEvent(event);
    }

private slots:
    void on_closebtn_clicked();

    void on_surebtn_clicked();

    void on_cancelbtn_clicked();

private:
    Ui::delete_msg *ui;
};

#endif // DELETE_MSG_H
