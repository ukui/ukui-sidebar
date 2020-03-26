#ifndef SINGLEITEMBUTTON_H
#define SINGLEITEMBUTTON_H

#include <QPushButton>
#include <QWidget>
#include <QDebug>
#include <QEvent>
class singleitemButton : public QPushButton
{
    Q_OBJECT
public:
    singleitemButton();
    ~singleitemButton();

signals:
    void buttonclick();
protected:
    void enterEvent(QEvent *event);//鼠标进入事件
    void mousePressEvent(QMouseEvent *event);//鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *event);//鼠标松开事件
    void leaveEvent(QEvent *event);//鼠标离开事件
    bool eventFilter(QObject *, QEvent *);//事件过滤器

};

#endif // SINGLEITEMBUTTON_H
