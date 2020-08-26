#include "External_Widget.h"
#include <QDebug>

external_widget::external_widget()
{

}

void external_widget::paintEvent(QPaintEvent *e)
{


    QPainter p(this);

    QRect rect = this->rect();

    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.setBrush(QBrush(QColor(255,255,255)));

    p.setOpacity(0.7);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(rect,0,0);

    QWidget::paintEvent(e);

}
