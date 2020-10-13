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
#ifndef VERTICALSCROLL_60_H
#define VERTICALSCROLL_60_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QPainter>
#include <QStyleOption>


namespace Ui {

class VerticalScroll_60;

}

class VerticalScroll_60 : public QWidget

{

    Q_OBJECT

    Q_PROPERTY(int deviation READ readDeviation WRITE setDeviation )

public:

    explicit VerticalScroll_60(QWidget *parent = 0);

    ~VerticalScroll_60();
    //设置范围
    // set range
    void setRange(int min, int max);
    //获取当前值
    // Get current value
    int readValue();
    //当前选中的值
    //Currently selected value
    int m_currentValue;

    void setupUi(QWidget *VerticalScroll_60);

    void retranslateUi(QWidget *VerticalScroll_60);

protected:
    void mousePressEvent(QMouseEvent *);

    void mouseMoveEvent(QMouseEvent *);

    void mouseReleaseEvent(QMouseEvent *);

    void wheelEvent(QWheelEvent *);

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


signals:

    void currentValueChanged(int value);

    void deviationChange(int deviation);



private:


    Ui::VerticalScroll_60 *ui;

private:
    int m_minRange;      //最小值 // minimum value
    int m_maxRange;      //最大值 // Maximum

    bool isDragging;        //鼠标是否按下 // Muse down
    int m_deviation;        //偏移量,记录鼠标按下后移动的垂直距离  // Offset, record the vertical distance after mouse is pressed
    int m_mouseSrcPos;
    int m_numSize;
    QPropertyAnimation *homingAni;
    const int interval;  //间隔大小 // Interval size
    const int devide;       //分隔数量 // Number of partitions
    QString change_NUM_to_str(int alarmHour);
};

#endif // VERTICALSCROLL_60_H
