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
#ifndef VERTICALSCROLL_24_H
#define VERTICALSCROLL_24_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QPainter>
#include <QStyleOption>

namespace Ui {

class VerticalScroll_24;

}
class Clock;
class VerticalScroll_24 : public QWidget

{
    Q_OBJECT

    Q_PROPERTY(int deviation READ readDeviation WRITE setDeviation )

public:

    explicit VerticalScroll_24(QWidget *parent = 0, Clock *clock = 0);

    ~VerticalScroll_24();
    //设置范围
    // set range
    void setRange(int min, int max);
    //获取当前值
    // Get current value
    int readValue();
    //当前选中的值
    //Currently selected value
    int m_currentValue;
    Clock *m_Pclock;

protected:
    //鼠标按压选择当前值
    // Press the mouse to select the current value
    void mousePressEvent(QMouseEvent *);
    //鼠标拖动，滚轮滚动
    //  Mouse drag, scroll wheel
    void mouseMoveEvent(QMouseEvent *);
    //鼠标释放，数值弹回正中间
    //  Release the mouse, and the value will bounce back to the middle
    void mouseReleaseEvent(QMouseEvent *);
    //鼠标滑轮滚动，数值滚动
    //  Mouse wheel scrolling, numerical scrolling
    void wheelEvent(QWheelEvent *);
    //绘制当前数值轮画面
    // Draw the current numerical wheel screen
    void paintEvent(QPaintEvent *);

    //描绘数字
    // Drawing numbers
    void paintNum(QPainter &painter, int num, int deviation);
    //使选中的数字回到屏幕中间
    //Bring the selected number back to the middle of the screen
    void homing();
    //鼠标移动偏移量，默认为0
    // Mouse movement offset, default is 0
    int readDeviation();
    //设置偏移量
    // Set offset
    void setDeviation(int n);

    void setupUi(QWidget *VerticalScroll_24);

    void retranslateUi(QWidget *VerticalScroll_24);

signals:

    void currentValueChanged(int value);

    void deviationChange(int deviation);



private:

    Ui::VerticalScroll_24 *ui;

private:
    int m_minRange;      //最小值  // minimum value
    int m_maxRange;      //最大值  // Maximum

    bool isDragging;     //鼠标是否按下 // Muse down
    int m_deviation;     //偏移量,记录鼠标按下后移动的垂直距离  // Offset, record the vertical distance after mouse is pressed
    int m_mouseSrcPos;
    int m_numSize;
    QPropertyAnimation *homingAni;
    const int interval;  //间隔大小 // Interval size
    const int devide;       //分隔数量 // Number of partitions
    void paintNum_24(QPainter &painter, int Height);
    void paintNum_12(QPainter &painter, int Height);
    QString change_NUM_to_str(int alarmHour);
};

#endif // VERTICALSCROLL_24_H
