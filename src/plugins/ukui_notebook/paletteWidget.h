#ifndef PALETTEWIDGET_H
#define PALETTEWIDGET_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>

namespace Ui {
class PaletteWidget;
}

class PaletteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PaletteWidget(QWidget *parent = nullptr);
    ~PaletteWidget();

    Ui::PaletteWidget *ui;

protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif // PALETTEWIDGET_H
