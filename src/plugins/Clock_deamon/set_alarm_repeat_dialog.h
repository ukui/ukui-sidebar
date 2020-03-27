#ifndef SET_ALARM_REPEAT_DIALOG_H
#define SET_ALARM_REPEAT_DIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include <QLabel>

namespace Ui {
class set_alarm_repeat_Dialog;
}

class set_alarm_repeat_widget;


class set_alarm_repeat_Dialog : public QWidget
{
    Q_OBJECT

public:
    explicit set_alarm_repeat_Dialog(QWidget *parent = nullptr , int rowNum = 0);
    ~set_alarm_repeat_Dialog();

    set_alarm_repeat_widget *widget[20];
    QListWidgetItem *aItem[20];
    int rowNum_all ;
    QListWidget *listWidget;

private:
  //  Ui::set_alarm_repeat_Dialog *ui;
    void setupUi(QWidget *set_alarm_repeat_Dialog);
    void retranslateUi(QWidget *set_alarm_repeat_Dialog);

    void set_aItem(int rowNum);

};



class set_alarm_repeat_widget : public QWidget
{
    Q_OBJECT

public:
    explicit set_alarm_repeat_widget(QWidget *parent = nullptr);
    ~set_alarm_repeat_widget();

    QLabel *alarmLabel0;
    QPushButton *alarmLabel1;

private:

};

#endif // SET_ALARM_REPEAT_DIALOG_H
