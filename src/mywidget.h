#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class mywidget : public QWidget
{
    Q_OBJECT
public:
    explicit mywidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);                //重绘事件
signals:

public slots:
};

#endif // MYWIDGET_H
