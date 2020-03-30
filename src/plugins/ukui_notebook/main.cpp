#include "widget.h"
#include <QApplication>
#include "sql_create.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!createConnection()) return 1;

    Widget w;
    w.setAttribute(Qt::WA_TranslucentBackground);
    w.show();

    return a.exec();
}
