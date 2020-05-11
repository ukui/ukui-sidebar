#include "feedback.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    feedback w;
    w.show();
    return a.exec();
}
