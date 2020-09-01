#ifndef BSRWIDGET_H
#define BSRWIDGET_H


#include <QWidget>
#include <QSlider>


struct State
{
    bool p;

};


class SliderButton : public QSlider
{
    Q_OBJECT
public:
    explicit SliderButton(QWidget *parent = 0);


};

class BsrWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BsrWidget(QWidget *parent = 0);


private slots:
    void changeValueP(int);


private:
    SliderButton *sliderP;
    State state;
};

#endif // BSRWIDGET_H
