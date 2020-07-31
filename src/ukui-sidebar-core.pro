#-------------------------------------------------
#
# Project created by QtCreator 2019-11-16T14:05:00
#
#-------------------------------------------------

QT       += core gui dbus widgets KWindowSystem

TARGET = ukui-sidebar
TEMPLATE = app
CONFIG += c++11 link_pkgconfig
PKGCONFIG += gsettings-qt

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_MESSAGELOGCONTEXT

include(./plugin-signals/plugin-signals.pri)
include(./plugin-interface/plugin-interface.pri)
include(env.pri)

DEFINES += PLUGIN_INSTALL_DIRS='\\"$${PLUGIN_INSTALL_DIRS}\\"'

RESOURCES  += sidebar.qrc
SOURCES += \
        main.cpp \
        mostgrandwidget.cpp \
        pluginstoolbutton.cpp \
        sidebarpluginswidgets.cpp \
        smallpluginsbutton.cpp \
        smallpluginsmanage.cpp \
        widget.cpp \
        pluginmanage.cpp \
        sidebarAppLog.cpp \
        customstyle.cpp \
        customstyleCleanPushbutton.cpp

INCLUDEPATH += ./plugin-interface

HEADERS += \
        mostgrandwidget.h \
        pluginstoolbutton.h \
        sidebarpluginswidgets.h \
        smallpluginsbutton.h \
        smallpluginsmanage.h \
        widget.h \
        pluginmanage.h \
        sidebarAppLog.h \
        customstyle.h \
        customstyleCleanPushbutton.h

INCLUDEPATH +=./plugin-interface ./plugin-sub-manager
TRANSLATIONS += ukui-sidebar_bo.ts \
                ukui-sidebar_tr.ts \
                ukui-sidebar_zh_CN.ts
CONFIG += link_pkgconfig

PKGCONFIG +=gio-2.0 glib-2.0 gio-unix-2.0
LIBS += -lX11 -lgio-2.0 -lgobject-2.0 -lglib-2.0

desktopfile.files = data/ukui-sidebar.desktop
desktopfile.path = /etc/xdg/autostart/

# Default rules for deployment.
target.path = /usr/bin/
!isEmpty(target.path): INSTALLS += target

INSTALLS += desktopfile

DISTFILES += \
    env.pri
