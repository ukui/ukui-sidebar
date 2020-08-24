#include "mywidget.h"
#include <QPainter>
#include<QDebug>

mywidget::mywidget(QWidget *parent) : QWidget(parent)
{

}

void mywidget::paintEvent(QPaintEvent *e)
{

    QPainter p(this);

    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.setBrush(QBrush(QColor(19, 19, 20, 1)));
    p.setPen(Qt::transparent);
    p.drawRoundedRect(rect,6,6);

}
