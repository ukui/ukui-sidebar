#ifndef SET_CLOCK_H
#define SET_CLOCK_H

#include <QWidget>

namespace Ui {
class set_clock;
}

class set_clock : public QWidget
{
    Q_OBJECT

public:
    explicit set_clock(QWidget *parent = nullptr);
    ~set_clock();

private:
    Ui::set_clock *ui;
};

#endif // SET_CLOCK_H
