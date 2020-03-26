#ifndef SINGLEITEMWIDGET_H
#define SINGLEITEMWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include <QHBoxLayout>
#include "singleitemButton.h"
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

    singleitemButton *pushButtonDel;//自定义三态按钮

private slots:
    void clickDelBtn();

private:
    void SingleItem_init();
    void SingleItem_conn();
};

#endif // SINGLEITEMWIDGET_H
