#ifndef VERTICALSCROLL_60_H
#define VERTICALSCROLL_60_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QPainter>

namespace Ui {

class VerticalScroll_60;

}

class VerticalScroll_60 : public QWidget

{

    Q_OBJECT

    Q_PROPERTY(int deviation READ readDeviation WRITE setDeviation )

public:

    explicit VerticalScroll_60(QWidget *parent = 0);

    ~VerticalScroll_60();
    //设置范围
    void setRange(int min, int max);
    //获取当前值
    int readValue();

    int m_currentValue;  //当前选中的值

    void setupUi(QWidget *VerticalScroll_60);

    void retranslateUi(QWidget *VerticalScroll_60);

protected:
    void mousePressEvent(QMouseEvent *);

    void mouseMoveEvent(QMouseEvent *);

    void mouseReleaseEvent(QMouseEvent *);

    void wheelEvent(QWheelEvent *);

    void paintEvent(QPaintEvent *);
    //描绘数字
    void paintNum(QPainter &painter, int num, int deviation);
    //使选中的数字回到屏幕中间
    void homing();
    //鼠标移动偏移量，默认为0
    int readDeviation();
    //设置偏移量
    void setDeviation(int n);


signals:

    void currentValueChanged(int value);

    void deviationChange(int deviation);



private:


    Ui::VerticalScroll_60 *ui;

private:
    int m_minRange;      //最小值
    int m_maxRange;      //最大值

    bool isDragging;        //鼠标是否按下
    int m_deviation;        //偏移量,记录鼠标按下后移动的垂直距离
    int m_mouseSrcPos;
    int m_numSize;
    QPropertyAnimation *homingAni;
    const int interval;  //间隔大小
    const int devide;       //分隔数量
};

#endif // VERTICALSCROLL_60_H
