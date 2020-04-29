#ifndef DELETE_MSG_H
#define DELETE_MSG_H

#include <QDialog>
#include <QStyleOption>
#include <QPainter>
namespace Ui {
class delete_msg;
}

class delete_msg : public QDialog
{
    Q_OBJECT

public:
    explicit delete_msg(QWidget *parent = nullptr);
    ~delete_msg();
    int close_sure;

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

private slots:
    void on_closebtn_clicked();

    void on_surebtn_clicked();

    void on_cancelbtn_clicked();

private:
    Ui::delete_msg *ui;
};

#endif // DELETE_MSG_H
