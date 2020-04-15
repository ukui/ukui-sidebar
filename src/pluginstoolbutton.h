#ifndef PLUGINSTOOLBUTTON_H
#define PLUGINSTOOLBUTTON_H

#include <QWidget>
#include <QToolButton>
class PluginsToolButton : public QToolButton
{
public:
    explicit PluginsToolButton(QWidget *parent = nullptr);
    enum SidebarButtonStatus{NORMAL, HOVER, PRESS};
    SidebarButtonStatus status;
protected:
    void enterEvent(QEvent *e);             //鼠标进入事件
    void leaveEvent(QEvent *e);             //鼠标离开事件
    void mousePressEvent(QMouseEvent *e);   //按钮点击事件
    void paintEvent(QPaintEvent *e);
};

#endif // PLUGINSTOOLBUTTON_H
