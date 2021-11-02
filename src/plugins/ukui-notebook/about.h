#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QPainter>
#include <QPainterPath>
#include <QDesktopServices>
#include <QUrl>

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = nullptr);
    ~About();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Ui::About *ui;

    void listenToGsettings();
};

#endif // ABOUT_H
