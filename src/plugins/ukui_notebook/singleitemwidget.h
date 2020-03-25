#ifndef SINGLEITEMWIDGET_H
#define SINGLEITEMWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
namespace Ui {
class SingleItemWidget;
}

class SingleItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SingleItemWidget(QWidget *parent = nullptr);
    ~SingleItemWidget();
signals:
    void childDelEvent();

public:
    Ui::SingleItemWidget *ui;

private slots:
    void clickDelBtn();

private:
    void SingleItem_init();
    void SingleItem_conn();
//    void paintEvent(QPaintEvent *);
};

#endif // SINGLEITEMWIDGET_H
