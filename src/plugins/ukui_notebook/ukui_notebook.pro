#-------------------------------------------------
#
# Project created by QtCreator 2020-03-17T10:53:26
#
#-------------------------------------------------

QT       += core gui printsupport sql concurrent gui

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

CONFIG += c++11

DESTDIR = ../sidebarSmallPlugins

INCLUDEPATH    += ../../plugin-interface

DISTFILES += notebook.json

TRANSLATIONS += \
        ukui_notebook_zh_CN.ts

SOURCES += \
    cai_tou.cpp \
    color_mini.cpp \
    dbmanager.cpp \
    edit_page.cpp \
    empty_notepad.cpp \
    form.cpp \
    mythrow.cpp \
    notebook_plugin.cpp \
    notedata.cpp \
    notemodel.cpp \
    noteview.cpp \
    notewidgetdelegate.cpp \
    pop_up_exit.cpp \
    select_color_page.cpp \
    set_font_color_page.cpp \
    set_font_size_page.cpp \
    singleitemButton.cpp \
    text_editing.cpp \
    widget.cpp

HEADERS += \
    cai_tou.h \
    color_mini.h \
    dbmanager.h \
    edit_page.h \
    empty_notepad.h \
    form.h \
    mythrow.h \
    notebook_plugin.h \
    notedata.h \
    notemodel.h \
    noteview.h \
    notewidgetdelegate.h \
    pop_up_exit.h \
    select_color_page.h \
    set_font_color_page.h \
    set_font_size_page.h \
    singleitemButton.h \
    text_editing.h \
    widget.h

FORMS += \
    cai_tou.ui \
    color_mini.ui \
    edit_page.ui \
    empty_notepad.ui \
    form.ui \
    pop_up_exit.ui \
    select_color_page.ui \
    set_font_color_page.ui \
    set_font_size_page.ui \
    text_editing.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

DISTFILES +=
unix {
    target.path = /usr/lib/ukui-sidebar/sidebarSmallPlugins
    INSTALLS += target
}
