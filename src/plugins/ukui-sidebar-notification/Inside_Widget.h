#ifndef M_PMSG_H
#define M_PMSG_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
class inside_widget : public QWidget
{
    Q_OBJECT
public:
    explicit inside_widget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *e);

signals:

public slots:
};

#endif // M_PMSG_H
