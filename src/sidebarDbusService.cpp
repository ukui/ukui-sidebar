#include "sidebarDbusService.h"
#include <QDebug>

SidebarDbusService::SidebarDbusService(QWidget *parent)
{
    m_parent = parent;
}

int SidebarDbusService::getWidth()
{
    return m_sidebarWidth;
}
