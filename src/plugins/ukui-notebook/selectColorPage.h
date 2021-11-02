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

#ifndef SELECTCOLOR_H
#define SELECTCOLOR_H

#include <QWidget>

#include "paletteWidget.h"

#define SHADOW_WIDTH 1                  // 窗口阴影宽度;
#define TRIANGLE_WIDTH 15               // 小三角的宽度;
#define TRIANGLE_HEIGHT 10              // 小三角的高度;
#define BORDER_RADIUS 5                 // 窗口边角的弧度;

namespace Ui {
class SelectColor;
}
class Widget;
class SelectColor : public QWidget
{
    Q_OBJECT

public:
    explicit SelectColor(Widget* page, QWidget *parent = nullptr);
    ~SelectColor();

    Ui::SelectColor *ui;

public:
    Widget *pNotebook;
    PaletteWidget *paletteWidget;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    int m_startX = 180;             // 小三角起始位置;
    int m_triangleWidth = 10;       // 小三角的宽度;
    int m_triangleHeight= 5;        // 小三角高度;
    QTimer *timer;

private:
    void initSetup();
};

#endif // SELECTCOLOR_H
