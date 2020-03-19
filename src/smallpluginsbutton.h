#ifndef SMALLPLUGINSBUTTON_H
#define SMALLPLUGINSBUTTON_H
#include <QPushButton>

class SmallPluginsButton :public QPushButton
{
    Q_OBJECT
public:
    SmallPluginsButton();
    ~SmallPluginsButton();
    void SendSingal();
protected:
    void enterEvent(QEvent *e); //鼠标进入事件
    void leaveEvent(QEvent *e);//鼠标离开事件
signals:
    void enterButtonSignal();
};

#endif // SMALLPLUGINSBUTTON_H
