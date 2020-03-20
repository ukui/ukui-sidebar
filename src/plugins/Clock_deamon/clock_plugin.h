#ifndef CLOCK_PLUGIN_H
#define CLOCK_PLUGIN_H

#include "clock_interface.h"
#include <QPushButton>
#include <QMainWindow>
#include <clock.h>

class clock_plugin : public QObject, public ClockInterface
{

    Q_OBJECT
    //Q_INTERFACES宏用于告诉Qt该类实现的接口
    Q_INTERFACES(ClockInterface)
    //Q_PLUGIN_METADATA宏用于描述插件元数据
    Q_PLUGIN_METADATA(IID ClockInterface_iid FILE "Clock.json")
    //申明该类有D-BUS服务接口
    //Q_CLASSINFO("D-Bus Interface", "com.scorpio.test.value")


public:

    clock_plugin();
    ~clock_plugin();

    QWidget *m_pClock;
    QWidget*  centerWidget();
    void onNotification() ;
   // void UI_in_sidebar();

signals:
    void    Clock_ification();


};


#endif // CLOCK_PLUGIN_H
