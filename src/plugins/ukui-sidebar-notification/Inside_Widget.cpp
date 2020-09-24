#include "Inside_Widget.h"
#include <QDebug>

inside_widget::inside_widget(QWidget *parent) : QWidget(parent)
{

}

void inside_widget::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    QRect rect = this->rect();
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.setBrush(opt.palette.color(QPalette::Base));
    p.setOpacity(0.7);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(rect,0,0);
  //  this->update();
    QWidget::paintEvent(e);
}
