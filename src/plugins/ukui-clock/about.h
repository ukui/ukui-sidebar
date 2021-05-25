#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QPainter>
#include <QPainterPath>
#include <QDesktopServices>
#include <QUrl>
#include <QGSettings>
#include "constant_class.h"



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
    void  settingsStyle();                                                               //监听主题
    void  blackStyle();                                                                  //黑色主题
    void  whiteStyle();                                                                  //白色主题
    Ui::About *ui;
};

#endif // ABOUT_H
