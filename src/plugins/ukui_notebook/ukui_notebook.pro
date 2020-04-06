#-------------------------------------------------
#
# Project created by QtCreator 2020-03-17T10:53:26
#
#-------------------------------------------------

QT       += core gui printsupport sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ukui_notebook
TEMPLATE = lib
CONFIG += plugin

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


DESTDIR = ../sidebarSmallPlugins

INCLUDEPATH    += ../../plugin-interface

DISTFILES += notebook.json \
    ukui_notebook_zh_CN.ts

CONFIG += c++11

TRANSLATIONS += \
        ukui_notebook_zh_CN.ts

SOURCES += \
        widget.cpp \
    singleitemwidget.cpp \
    ukui_notebook.cpp \
    notebook_plugin.cpp

HEADERS += \
        widget.h \
    singleitemwidget.h \
    ukui_notebook.h \
    sql_create.h \
    notebook_plugin.h

FORMS += \
        widget.ui \
    singleitemwidget.ui \
    ukui_notebook.ui

RESOURCES += \
    ukui_notebook.qrc

unix {
    target.path = /usr/lib/ukui-sidebar/sidebarSmallPlugins
    INSTALLS += target
}
