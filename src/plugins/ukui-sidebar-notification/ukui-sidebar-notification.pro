#-------------------------------------------------
#
# Project created by QtCreator 2020-01-08T16:23:49
#
#-------------------------------------------------

QT       += core gui widgets svg dbus

TARGET = notification_plugin
TEMPLATE = lib
CONFIG += plugin \
          link_pkgconfig

include(../../env.pri)

PKGCONFIG += gsettings-qt \
             glib-2.0
LIBS          +=  -L$$[QT_INSTALL_LIBS] -ldconf

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    notificationDbus.cpp \
    notificationPlugin.cpp \
    appmsg.cpp \
    scrollareawidget.cpp \
    takeinboxtoolbutton.cpp \
    monitorthread.cpp \
    singlemsg.cpp \
    buttonwidget.cpp \
    customstylePushbutton2.cpp \
    picturetowhite.cpp \

INCLUDEPATH    += ../../plugin-interface \
                 /usr/include/dconf
HEADERS += \
    notificationDbus.h \
    notificationPlugin.h \
    appmsg.h \
    scrollareawidget.h \
    takeinboxtoolbutton.h \
    monitorthread.h \
    singlemsg.h \
    buttonwidget.h \
    customstylePushbutton2.h \
    picturetowhite.h \

DISTFILES += notificationPlugin.json

unix {
    target.path = $${PLUGIN_INSTALL_DIRS}
    INSTALLS += target

    translation.path = /usr/share/ukui-sidebar/ukui-sidebar-notification
    translation.files += ../../../translations/ukui-sidebar-notification/*.qm
    INSTALLS += translation
}

TRANSLATIONS += ../../../translations/ukui-sidebar-notification/ukui-sidebar-notification_zh_CN.ts \
                ../../../translations/ukui-sidebar-notification/ukui-sidebar-notification_tr.ts

RESOURCES += \
    notificationPlugin.qrc
