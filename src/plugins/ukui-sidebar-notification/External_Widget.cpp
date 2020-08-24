#include "External_Widget.h"
#include <QDebug>

external_widget::external_widget()
{

    initGsettingTransparency();
}

void external_widget::initGsettingTransparency()
{
    if (QGSettings::isSchemaInstalled(UKUI_TRANSPARENCY_SETTING)) {
        m_pTransparency = new QGSettings(UKUI_TRANSPARENCY_SETTING);
        m_dTranSparency = m_pTransparency->get("transparency").toDouble();
        connect(m_pTransparency, &QGSettings::changed, this, [=](QString value) {
            m_dTranSparency = m_pTransparency->get("transparency").toDouble();;
        });
    }
}

void external_widget::paintEvent(QPaintEvent *e)
{


    QPainter p(this);

    QRect rect = this->rect();

    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.setBrush(QBrush(QColor(20,20,20)));
    p.setOpacity(m_dTranSparency);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(rect,0,0);

}
