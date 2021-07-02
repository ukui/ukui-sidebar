#-------------------------------------------------
#
# Project created by QtCreator 2019-11-16T14:05:00
#
#-------------------------------------------------

QT       += core gui dbus widgets network

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
        customstyleCleanPushbutton.cpp \
        qtsingleapplication.cpp \
        qtlocalpeer.cpp \
        qtlockedfile.cpp \
        xeventmonitor.cpp


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
        customstyleCleanPushbutton.h \
        qtsingleapplication.h \
        qtlocalpeer.h \
        qtlockedfile.h \
        xeventmonitor.h


INCLUDEPATH +=./plugin-interface ./plugin-sub-manager
TRANSLATIONS += ../translations/ukui-sidebar_bo.ts \
                ../translations/ukui-sidebar_tr.ts \
                ../translations/ukui-sidebar_zh_CN.ts

unix {
    translation.path = /usr/share/ukui-sidebar/
    translation.files += ../translations/*.qm
    INSTALLS += translation
}

QMAKE_CFLAGS += -D_FORTIFY_SOURCE=2 -O2

CONFIG += link_pkgconfig

PKGCONFIG +=gio-2.0 glib-2.0 gio-unix-2.0 xtst
LIBS += -lX11 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lukui-log4qt -lQt5Xdg

desktopfile.files = data/ukui-sidebar.desktop
desktopfile.path = /etc/xdg/autostart/

schemes.files += data/org.ukui.log4qt.ukui-sidebar.gschema.xml
schemes.path = /usr/share/glib-2.0/schemas/

schemes1.files += data/org.ukui.sidebar.gschema.xml
schemes1.path = /usr/share/glib-2.0/schemas/

# Default rules for deployment.
target.path = /usr/bin/
!isEmpty(target.path): INSTALLS += target

INSTALLS += desktopfile
INSTALLS += schemes
INSTALLS += schemes1

DISTFILES += \
    data/org.ukui.sidebar.gschema.xml \
    env.pri\

