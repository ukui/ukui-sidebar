#ifndef DOTLINEDEMO_H
#define DOTLINEDEMO_H

#include <QWidget>
#include <QPainter>
#include <QWidget>



class DotLineDemo : public QWidget
{
    Q_OBJECT

public:
    explicit DotLineDemo(QWidget *parent = nullptr);
    ~DotLineDemo();

    QWidget * widget;

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
};

#endif // DOTLINEDEMO_H
