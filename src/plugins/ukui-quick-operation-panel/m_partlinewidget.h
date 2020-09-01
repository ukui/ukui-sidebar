#ifndef M_PARTLINEWIDGET_H
#define M_PARTLINEWIDGET_H

#include <QWidget>
#include <QPainter>

class m_PartLineWidget : public QWidget
{
    Q_OBJECT
public:
    explicit m_PartLineWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);


};

#endif // M_PARTLINEWIDGET_H
