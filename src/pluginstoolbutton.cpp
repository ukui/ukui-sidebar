#include "pluginstoolbutton.h"
#include <QStyleOption>
#include <QPainter>
PluginsToolButton::PluginsToolButton(QWidget *parent)
{
    status = NORMAL;
}

void PluginsToolButton::enterEvent(QEvent *e)
{
    status = HOVER;
}

void PluginsToolButton::leaveEvent(QEvent *e)
{
    status = NORMAL;
}

void PluginsToolButton::mousePressEvent(QMouseEvent *e)
{
    status = PRESS;
}

void PluginsToolButton::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    switch (status) {
      case NORMAL: {
              p.setBrush(QBrush(QColor(opt.palette.color(QPalette::WindowText))));
              p.setOpacity(0.12);
              p.setPen(Qt::NoPen);
              break;
          }
      case HOVER: {
              p.setBrush(QBrush(QColor(opt.palette.color(QPalette::WindowText))));
              p.setOpacity(0.2);
              p.setPen(Qt::NoPen);
              break;
          }
      case PRESS: {
              p.setBrush(QBrush(QColor(opt.palette.color(QPalette::WindowText))));
              p.setOpacity(0.08);
              p.setPen(Qt::NoPen);
              break;
          }
      }
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.drawRoundedRect(opt.rect,4,4);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
