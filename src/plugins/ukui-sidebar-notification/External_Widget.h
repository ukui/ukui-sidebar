#ifndef MY_WIDGET_H
#define MY_WIDGET_H

#include <QWidget>
#include <QPainter>
class external_widget:public QWidget
{
public:
    external_widget();
    void paintEvent(QPaintEvent *e);                //重绘事件
};

#endif // MY_WIDGET_H
