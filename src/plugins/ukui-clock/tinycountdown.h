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
#ifndef TINYCOUNTDOWN_H
#define TINYCOUNTDOWN_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include "constant_class.h"
#include <xcb/xcb.h>
#include <QTime>
#include <QTimer>
#include <QStyleOption>
#include <QGSettings>
#include <QPainterPath>
#include "xatom-helper.h"
namespace Ui {
class tinyCountdown;
}

class tinyCountdown : public QWidget
{
    Q_OBJECT

public:
    explicit tinyCountdown(QWidget *parent = nullptr);
    ~tinyCountdown();
    void updateTimeInfo(QString str);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

 /*
    void focusOutEvent ( QFocusEvent * event ) override;
    void focusInEvent ( QFocusEvent * event ) override;
*/

    void closeEvent(QCloseEvent *event) override;

    void clearData();
protected:
     //绘制背景
     // Draw background
    void paintEvent(QPaintEvent *);

signals:
    void mainWindowClick();

public slots:
        void set_dialog_close();
        void showTop();
private slots:
    void showMainWindow();


private:
    Ui::tinyCountdown *ui;
    bool mousePressed;
    QPoint dragPosition;                                            //拖动坐标
    void closeStyle();
    void settingsStyle();
    void whiteStyle();
    void blackStyle();
    void switchStyle();
};

#endif // TINYCOUNTDOWN_H
