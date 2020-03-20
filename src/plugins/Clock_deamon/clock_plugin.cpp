#include "clock_plugin.h"
#include "clock.h"
#include "connection.h"
#include "debug.h"
#include "clock_interface.h"
#include "qdebug.h"


clock_plugin::clock_plugin()
{
    m_pClock = new Clock;

    //m_pClock_sidebarBTN->setFixedSize(400,60 );
    m_pClock->show();
}

void clock_plugin::onNotification() {
    qDebug()<< "onNotification==========================";
}

clock_plugin::~clock_plugin() {
    if( m_pClock)
    {
        delete m_pClock;
    }
    m_pClock = nullptr;

}

QWidget* clock_plugin::centerWidget()
{
    return  m_pClock;

}



