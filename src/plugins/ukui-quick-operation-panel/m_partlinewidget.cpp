#include "m_partlinewidget.h"

m_PartLineWidget::m_PartLineWidget(QWidget *parent) : QWidget(parent)
{

}

void m_PartLineWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    QRect rect = this->rect();

    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.setBrush(QBrush(QColor(20,20,20)));

    p.setOpacity(0.1);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(rect,0,0);

    QWidget::paintEvent(event);
}
