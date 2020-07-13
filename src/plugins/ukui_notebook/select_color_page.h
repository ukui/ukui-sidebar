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

#ifndef SELECT_COLOR_PAGE_H
#define SELECT_COLOR_PAGE_H

#include <QWidget>

#include "paletteWidget.h"

#define SHADOW_WIDTH 1                  // 窗口阴影宽度;
#define TRIANGLE_WIDTH 15               // 小三角的宽度;
#define TRIANGLE_HEIGHT 10              // 小三角的高度;
#define BORDER_RADIUS 5                 // 窗口边角的弧度;

namespace Ui {
class select_color_page;
}
class Widget;
class select_color_page : public QWidget
{
    Q_OBJECT

public:
    explicit select_color_page(Widget* page , QWidget *parent = nullptr);
    ~select_color_page();
    void paintEvent(QPaintEvent *e);
    Ui::select_color_page *ui;
    Widget *pNotebook;
    PaletteWidget *paletteWidget;
private slots:
    void color_clicked();

private:
    void black_show();
    void light_show();
    // 小三角起始位置;
    int m_startX = 180;
    // 小三角的宽度;
    int m_triangleWidth = 10;
    // 小三角高度;
    int m_triangleHeight= 5;
    QTimer *timer;
};

#endif // SELECT_COLOR_PAGE_H
