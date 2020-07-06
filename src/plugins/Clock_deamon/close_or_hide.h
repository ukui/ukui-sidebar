#ifndef CLOSE_OR_HIDE_H
#define CLOSE_OR_HIDE_H

#include <QDialog>
#include <QStyleOption>
#include <QPainter>
#include <QPainterPath>
namespace Ui {
class close_or_hide;
}
class Clock;
class close_or_hide : public QDialog
{
    Q_OBJECT

public:
    explicit close_or_hide(QWidget *parent = nullptr);
    ~close_or_hide();

    //绘制底部阴影
    // Draw bottom shadow
    void paintEvent(QPaintEvent *event)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
        painter.setBrush(QBrush(QColor(86, 86, 86)));
        painter.setPen(Qt::transparent);
        QRect rect = this->rect();
        rect.setWidth(rect.width() - 0);
        rect.setHeight(rect.height() - 0);
        painter.drawRoundedRect(rect, 7, 7);
        {
            QPainterPath painterPath;
            painterPath.addRoundedRect(rect, 7, 7);
            painter.drawPath(painterPath);
        }
        QWidget::paintEvent(event);
    }
    int close_flag;
private slots:
    void on_closebtn_clicked();

    void on_surebtn_clicked();

    void on_cancelbtn_clicked();

private:
    Ui::close_or_hide *ui;
};

#endif // CLOSE_OR_HIDE_H
