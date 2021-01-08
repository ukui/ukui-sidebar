#ifndef SETUPBTNNEW_H
#define SETUPBTNNEW_H

#include <QWidget>
#include <QToolButton>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class Btn_new;
}
class Clock;
class setUpBtnNew : public  QPushButton
{
    Q_OBJECT

public:
    explicit setUpBtnNew(int num, QString name , QWidget *parent = nullptr);
    ~setUpBtnNew();
    QLabel *nameLabel;
    QLabel *textLabel;
    QLabel *noName;
    QLabel *IconLabel;

    void paintEvent(QPaintEvent *event);

private:
    Ui::Btn_new *ui;
    Clock * m_pclock;
    int clock_num;
    int pressflag;
protected:
};

#endif // SETUPBTNNEW_H
