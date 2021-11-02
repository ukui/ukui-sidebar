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
#include <QMouseEvent>
#include <QPainterPath>
namespace Ui {
class delete_msg;
}
/**
 * @brief 删除消息弹框
 */
class delete_msg : public QDialog
{
    Q_OBJECT

public:
    explicit delete_msg(QWidget *parent = nullptr);
    ~delete_msg();
    int close_sure;
    //绘制底部阴影
    // Draw bottom shadow
    void paintEvent(QPaintEvent *event);
    Ui::delete_msg *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_closebtn_clicked();

    void on_surebtn_clicked();

    void on_cancelbtn_clicked();

private:
    QPoint dragPosition;                                            //拖动坐标
    bool mousePressed;                                              //鼠标是否按下
};

#endif // DELETE_MSG_H
