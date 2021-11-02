#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

//#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QMouseEvent>
#include <QStyleOption>
#include <QPainter>
#include <QGSettings>
#include <QPushButton>
#include <QPropertyAnimation>
#include "constant_class.h"


/**
 * @brief 自定义滑动按钮
 */
class CustomButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CustomButton(QWidget *parent = nullptr, int width=50, int height=24, int status = 1);

private:
    QTimer timer;
    int m_width;
    int m_height;
    int dir;
    int position;
    int max;
    int min;
    int length;
    int Status;
    QString closeBcack;
    QString openBcack;
    QString closeBtn;
    QString openbtn;
    QPropertyAnimation *animation1;
    QPropertyAnimation *animation2;

public:
    void init(int status);
    void whiteStyle();
    void blackStyle();
    void settingsStyle();
    void colorUpdate();
    void openSlot();
    void closeSlot();
    void initOpen();
    void initClose();
    QLabel* myLabel;
};

#endif // CUSTOMBUTTON_H
