#ifndef M_PMSG_H
#define M_PMSG_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QGSettings>
#define UKUI_TRANSPARENCY_SETTING "org.ukui.control-center.personalise"

class inside_widget : public QWidget
{
    Q_OBJECT
public:
    explicit inside_widget(QWidget *parent = nullptr);
    QGSettings *m_pTransparency;
    double tranSparency = 0.7;

protected:
    void paintEvent(QPaintEvent *e);

signals:

public slots:
};

#endif // M_PMSG_H
