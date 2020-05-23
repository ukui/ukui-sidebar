#ifndef BTN_NEW_H
#define BTN_NEW_H

#include <QWidget>
#include <QToolButton>
#include <QLabel>

namespace Ui {
class Btn_new;
}
class Clock;
class Btn_new : public  QToolButton
{
    Q_OBJECT

public:
    explicit Btn_new(int num, Clock *widget, QIcon icon , QString name , QWidget *parent = nullptr);
    ~Btn_new();

private:
    Ui::Btn_new *ui;
    QLabel *IconLabel;
    QLabel *textLabel;
    Clock * m_pclock;
    int clock_num;
protected:
    void enterEvent(QEvent *event);//鼠标进入事件
    void mousePressEvent(QMouseEvent *event);//鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *event);//鼠标松开事件
    void leaveEvent(QEvent *event);//鼠标离开事件
};

#endif // BTN_NEW_H
