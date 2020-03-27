#include "DotLineDemo.h"

DotLineDemo::DotLineDemo(QWidget *parent):
     QWidget(parent)
{
    this->resize(454, 403);
}

DotLineDemo::~DotLineDemo()
{

}


void DotLineDemo::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    // 反走样
    painter.setRenderHint(QPainter::Antialiasing, true);

    //color: rgb(148, 148, 148);   Qt::gray
    painter.setPen(QPen(QColor(60, 60, 60), 4, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(QPointF(226, 215), 170, 170);
}
