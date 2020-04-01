#include "clock.h"
#include <QApplication>
#include "connection.h"
#include "debug.h"
#include "item_new.h"
#include "set_alarm_repeat_dialog.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Clock w;
    //setuppage w;
    w.show();
    
    return a.exec();
}
