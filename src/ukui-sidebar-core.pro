#-------------------------------------------------
#
# Project created by QtCreator 2019-11-16T14:05:00
#
#-------------------------------------------------

QT       += core gui dbus widgets

TARGET = ukui-sidebar
TEMPLATE = app
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_MESSAGELOGCONTEXT

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


include(./plugin-signals/plugin-signals.pri)
include(./plugin-interface/plugin-interface.pri)

RESOURCES  += sidebar.qrc
SOURCES += \
        main.cpp \
        mostgrandwidget.cpp \
        realtimepropertyanimation.cpp \
        sidebarpluginswidgets.cpp \
        smallpluginsbutton.cpp \
        smallpluginsmanage.cpp \
        widget.cpp \
        pluginmanage.cpp \
        sidebar_app_log.cpp

INCLUDEPATH += ./plugin-interface

HEADERS += \
        mostgrandwidget.h \
        realtimepropertyanimation.h \
        sidebarpluginswidgets.h \
        smallpluginsbutton.h \
        smallpluginsmanage.h \
        widget.h \
        pluginmanage.h \
        sidebar_app_log.h


INCLUDEPATH +=./plugin-interface ./plugin-sub-manager
TRANSLATIONS += Sidebar_zh_CN.ts
CONFIG += link_pkgconfig

PKGCONFIG +=gio-2.0 glib-2.0 gio-unix-2.0
LIBS += -lgio-2.0 -lgobject-2.0 -lglib-2.0

desktopfile.files = data/ukui-sidebar.desktop
desktopfile.path = /etc/xdg/autostart/

# Default rules for deployment.
target.path = /usr/bin/
!isEmpty(target.path): INSTALLS += target

INSTALLS += desktopfile
