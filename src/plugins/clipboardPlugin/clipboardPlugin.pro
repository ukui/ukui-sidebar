#-------------------------------------------------
#
# Project created by QtCreator 2020-01-08T10:30:22
#
#-------------------------------------------------

QT       += core gui
QT += widgets

TARGET = clipboardPlugin
TEMPLATE = lib
CONFIG += plugin

DESTDIR = ../sidebar_clipboardPlugin_plugins

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES  += clipboardPlugin.qrc
SOURCES += \
        sidebarclipboardplugin.cpp \
    clipboardwidgetentry.cpp \
    editorwidget.cpp \
    searchwidgetitemcontent.cpp \
    clipboardlisetwidget.cpp

INCLUDEPATH    += ../../plugin-interface ../../plugin-signals

HEADERS += \
        sidebarclipboardplugin.h \
    clipboardwidgetentry.h \
    clipboardsignal.h \
    editorwidget.h \
    searchwidgetitemcontent.h \
    ../../plugin-signals/sidebarclipboardsignal.h \
    clipboardlisetwidget.h
DISTFILES += clipboardPlugin.json 

TRANSLATIONS += test_zh_CN.ts

unix {
    target.path = /usr/lib/ukui-sidebar/sidebar_clipboardPlugin_plugins
    INSTALLS += target
}
