#ifndef ITEM_NEW_H
#define ITEM_NEW_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFrame>

namespace Ui {
class item_new;
}

class item_new : public QWidget
{
    Q_OBJECT

public:
    explicit item_new(QWidget *parent = nullptr);
    ~item_new();

//private:

    void setupUi(QWidget *item_new);
    void retranslateUi(QWidget *item_new);
    Ui::item_new *ui;

    QPushButton *deleteAlarmBtn0;
    QLabel *alarmLabel0;
    QLabel *alarmLabel_w0;
    QLabel *alarmLabel_s0;

    QPushButton *alarm_on_off0;
    QPushButton *alarm_changed0;
    QPushButton *alarm_edit0;

    QFrame *alarm_line0;

};

#endif // ITEM_NEW_H
