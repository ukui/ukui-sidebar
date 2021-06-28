#ifndef TINYCOUNTDOWN_H
#define TINYCOUNTDOWN_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include "constant_class.h"
#include <xcb/xcb.h>
#include <QTime>
#include <QTimer>
#include <QStyleOption>
#include <QGSettings>
#include "xatom-helper.h"
namespace Ui {
class tinyCountdown;
}

class tinyCountdown : public QWidget
{
    Q_OBJECT

public:
    explicit tinyCountdown(QWidget *parent = nullptr);
    ~tinyCountdown();
    void updateTimeInfo(QString str);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

 /*
    void focusOutEvent ( QFocusEvent * event ) override;
    void focusInEvent ( QFocusEvent * event ) override;
*/

    void closeEvent(QCloseEvent *event) override;

    void clearData();
protected:
     //绘制背景
     // Draw background
    void paintEvent(QPaintEvent *);

signals:
    void mainWindowClick();

public slots:
        void set_dialog_close();
        void showTop();
private slots:
    void showMainWindow();


private:
    Ui::tinyCountdown *ui;
    bool mousePressed;
    QPoint dragPosition;                                            //拖动坐标
    void closeStyle();
    void settingsStyle();
    void whiteStyle();
    void blackStyle();
    void switchStyle();
};

#endif // TINYCOUNTDOWN_H
