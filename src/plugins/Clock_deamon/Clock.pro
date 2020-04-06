#-------------------------------------------------
#
# Project created by QtCreator 2014-06-28T21:00:26
#
#-------------------------------------------------

QT       += core gui multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Clock_deamon
TEMPLATE = lib
CONFIG += plugin


SOURCES += clock.cpp \
    item_new.cpp \
    clock_plugin.cpp \
    stopwatch_item.cpp


HEADERS  += clock.h \
    connection.h \
    debug.h \
    item_new.h \
    clock_plugin.h \
    stopwatch_item.h

TRANSLATIONS = Clock.ts

DESTDIR = ../sidebarSmallPlugins

INCLUDEPATH    += ../../plugin-interface

DISTFILES += Clock.json


FORMS    += clock.ui \
    item_new.ui \
    stopwatch_item.ui


RESOURCES += \
    images.qrc

RC_FILE = clock.rc

unix {
    target.path = /usr/lib/ukui-sidebar/sidebarSmallPlugins
    INSTALLS += target
}
