#include "smallpluginsbutton.h"
#include <QDebug>

SmallPluginsButton::SmallPluginsButton()
{
    connect(this, &SmallPluginsButton::clicked, this, &SmallPluginsButton::enterButtonSignal);
}

SmallPluginsButton::~SmallPluginsButton()
{

}

void SmallPluginsButton::enterEvent(QEvent *e)
{
    Q_UNUSED(e);
//    emit enterButtonSignal();
}

void SmallPluginsButton::leaveEvent(QEvent *e)
{
    Q_UNUSED(e);
}

void SmallPluginsButton::SendSingal()
{
    emit enterButtonSignal();
}


