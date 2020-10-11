#ifndef BTN_NEW_H
#define BTN_NEW_H

#include <QWidget>
#include <QToolButton>
#include <QLabel>
#include <QPushButton>

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
    QPushButton *IconLabel;
    QLabel *textLabel;
    Clock * m_pclock;
    int clock_num;
    int pressflag;
protected:
    void mouseReleaseEvent(QMouseEvent *event);//鼠标松开事件
};

#endif // BTN_NEW_H
