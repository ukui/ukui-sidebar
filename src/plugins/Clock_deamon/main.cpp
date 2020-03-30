#include "clock.h"
#include <QApplication>
#include "connection.h"
#include "debug.h"
#include "item_new.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Clock w;
    w.show();

    return a.exec();
}
