#include "clock.h"
#include <QApplication>
#include "connection.h"
#include "debug.h"
#include "item_new.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   // if(!createConnection()) return 1;

    //qInstallMessageHandler(outputMessage);

    Clock w;

    w.show();
    
    return a.exec();
}
