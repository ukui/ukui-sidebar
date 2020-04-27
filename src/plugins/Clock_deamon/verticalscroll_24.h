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
    void setRange(int min, int max);
    //获取当前值
    int readValue();
    int m_currentValue;  //当前选中的值
    Clock *m_Pclock;

protected:
    void mousePressEvent(QMouseEvent *);

    void mouseMoveEvent(QMouseEvent *);

    void mouseReleaseEvent(QMouseEvent *);

    void wheelEvent(QWheelEvent *);

    void paintEvent(QPaintEvent *);
    //描绘数字
    void paintNum(QPainter &painter, int num, int deviation);
    //使选中的数字回到屏幕中间
    void homing();
    //鼠标移动偏移量，默认为0
    int readDeviation();
    //设置偏移量
    void setDeviation(int n);

    void setupUi(QWidget *VerticalScroll_24);

    void retranslateUi(QWidget *VerticalScroll_24);

signals:

    void currentValueChanged(int value);

    void deviationChange(int deviation);



private:

    Ui::VerticalScroll_24 *ui;

private:
    int m_minRange;      //最小值
    int m_maxRange;      //最大值

    bool isDragging;        //鼠标是否按下
    int m_deviation;        //偏移量,记录鼠标按下后移动的垂直距离
    int m_mouseSrcPos;
    int m_numSize;
    QPropertyAnimation *homingAni;
    const int interval;  //间隔大小
    const int devide;       //分隔数量
    void paintNum_24(QPainter &painter, int Height);
    void paintNum_12(QPainter &painter, int Height);
    QString change_NUM_to_str(int alarmHour);
};

#endif // VERTICALSCROLL_24_H
