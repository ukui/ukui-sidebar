#ifndef AITEM_H
#define AITEM_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFrame>

class aItem :public QWidget
{
public:
    aItem();

private:
    QPushButton *deleteAlarmBtn0;
    QLabel *alarmLabel0;
    QLabel *alarmLabel_w0;
    QLabel *alarmLabel_s0;

    QPushButton *alarm_on_off0;
    QPushButton *alarm_changed0;
    QPushButton *alarm_edit0;

    QFrame *alarm_line0;
};

#endif // AITEM_H
