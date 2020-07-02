#ifndef TEXTEDITWIDGET_H
#define TEXTEDITWIDGET_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>

namespace Ui {
class TextEditWidget;
}

class TextEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TextEditWidget(QWidget *parent = nullptr);
    ~TextEditWidget();

    Ui::TextEditWidget *ui;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void iconInit();
};

#endif // TEXTEDITWIDGET_H
