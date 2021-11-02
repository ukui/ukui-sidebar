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
class Btn_new : public  QPushButton
{
    Q_OBJECT

public:
    explicit Btn_new(int num, QString name , QWidget *parent = nullptr);
    ~Btn_new();
    QLabel *nameLabel;
    QLabel *textLabel;
    QLabel *noName;
    QLabel *IconLabel;

    void paintEvent(QPaintEvent *event);
    void updateWidthForFontChange(int px);
private:
    Ui::Btn_new *ui;
    Clock * m_pclock;
    int clock_num;
    int pressflag;
protected:
};

#endif // BTN_NEW_H
