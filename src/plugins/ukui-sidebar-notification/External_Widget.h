#ifndef MY_WIDGET_H
#define MY_WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QGSettings>

#define UKUI_TRANSPARENCY_SETTING "org.ukui.control-center.personalise"
class external_widget:public QWidget
{
public:
    external_widget();
    QGSettings   *m_pTransparency;
    double        m_dTranSparency = 0.7;
    void  initGsettingTransparency();
    void paintEvent(QPaintEvent *e);                //重绘事件
};

#endif // MY_WIDGET_H
