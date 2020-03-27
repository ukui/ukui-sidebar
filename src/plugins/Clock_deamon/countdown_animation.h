#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include <QRoundProgressBar.h>

namespace Ui {
class Countdown_Animation;
}

class Countdown_Animation : public QWidget
{
    Q_OBJECT
public:

     Countdown_Animation( QWidget *parent = 0, int value_max = 0);
    ~Countdown_Animation();

    QRoundProgressBar *RoundBar3;

    void setupUi(QWidget *TestWidget);

    void retranslateUi(QWidget *TestWidget);

    QTimer *timer;

    int value_max=100;

private:
    void connectToSlider(class QRoundProgressBar* bar);

    void con();



    Ui::Countdown_Animation *ui;
};

#endif // TESTWIDGET_H
