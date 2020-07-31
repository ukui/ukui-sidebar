#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include <QLCDNumber>
#include <QMediaPlayer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    //-------------------------
    void timestart();
    void settime_number(int h, int m, int s);
    //--------------------------



    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.fillRect(this->rect(), QColor(0, 0, 0, 0x20)); /* 设置透明颜色 */
    }
    //Qt::FramelessWindowHint会导致窗口不能被拖动。通过捕获鼠标移动事件从而实现窗口移动
    void mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton) {
            m_startPoint = frameGeometry().topLeft() - event->globalPos(); /* 捕获按下时坐标 */
        }
    }

    void mouseMoveEvent(QMouseEvent *event)
    {
        this->move(event->globalPos() + m_startPoint); /* 移动窗口 */
    }

private slots:
    void Count_down();//int Hour,int minute ,int second);

    void on_pushButton_Start_clicked();

    void on_pushButton_pause_clicked();

  // void on_pushButton_timeselect_2_clicked();

    void on_pushButton_ring_clicked();

private:
    QPoint m_startPoint;
    Ui::Widget *ui;
    QLCDNumber *numb, *numb2, *numb3;
    QTimer *timer;
    int hour=0, minute=0, second=0, pushflag=0 ;
    QMediaPlayer *player = new QMediaPlayer;
    QString ring;//铃声名字

};

#endif // WIDGET_H
