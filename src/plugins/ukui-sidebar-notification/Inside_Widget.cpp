#include "Inside_Widget.h"
#include <QDebug>

inside_widget::inside_widget(QWidget *parent) : QWidget(parent)
{
    if (QGSettings::isSchemaInstalled(UKUI_TRANSPARENCY_SETTING)) {
        m_pTransparency = new QGSettings(UKUI_TRANSPARENCY_SETTING);
        tranSparency = m_pTransparency->get("transparency").toDouble();
        connect(m_pTransparency, &QGSettings::changed, this, [=](QString key) {
            if (key == "transparency") {
                tranSparency = m_pTransparency->get("transparency").toDouble();
            }
        });
    }
}

void inside_widget::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    QRect rect = this->rect();
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.setBrush(opt.palette.color(QPalette::Base));
    p.setOpacity(tranSparency);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(rect,0,0);
  //  this->update();
    QWidget::paintEvent(e);
}
