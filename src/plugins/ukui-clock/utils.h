#ifndef UTILS_H
#define UTILS_H
#include <QObject>
#include <QGuiApplication>
#include <QScreen>
#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>
#include <QRect>

class Utils
{
public:
    Utils();
    void centerToScreen(QWidget* widget);
};

#endif // UTILS_H
