#-------------------------------------------------
#
# Project created by QtCreator 2020-03-17T10:53:26
#
#-------------------------------------------------

QT       += core gui printsupport sql concurrent gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ukui-notebook
TEMPLATE = app

LIBS    +=  -lX11

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

TRANSLATIONS += \
        ukui_notebook_zh_CN.ts
        notebook_tr.ts

SOURCES += \
    customStyle.cpp \
    dbmanager.cpp \
    edit_page.cpp \
    emptyNotes.cpp \
    fontButton.cpp \
    headerbar.cpp \
    iconviewmodedelegate.cpp \
    listViewModeDelegate.cpp \
    main.cpp \
    mythrow.cpp \
    noteExitWindow.cpp \
    noteHead.cpp \
    noteHeadMenu.cpp \
    notedata.cpp \
    notemodel.cpp \
    noteview.cpp \
    paletteButton.cpp \
    paletteWidget.cpp \
    select_color_page.cpp \
    set_font_color_page.cpp \
    set_font_size_page.cpp \
    singleApplication.cpp \
    singleitemButton.cpp \
    textEditWidget.cpp \
    text_editing.cpp \
    widget.cpp

HEADERS += \
    customStyle.h \
    dbmanager.h \
    edit_page.h \
    emptyNotes.h \
    fontButton.h \
    headerbar.h \
    iconviewmodedelegate.h \
    listViewModeDelegate.h \
    mythrow.h \
    noteExitWindow.h \
    noteHead.h \
    noteHeadMenu.h \
    notedata.h \
    notemodel.h \
    noteview.h \
    paletteButton.h \
    paletteWidget.h \
    select_color_page.h \
    set_font_color_page.h \
    set_font_size_page.h \
    singleApplication.h \
    singleitemButton.h \
    textEditWidget.h \
    text_editing.h \
    widget.h

FORMS += \
    edit_page.ui \
    emptyNotes.ui \
    fontButton.ui \
    noteExitWindow.ui \
    noteHead.ui \
    noteHeadMenu.ui \
    paletteButton.ui \
    paletteWidget.ui \
    select_color_page.ui \
    set_font_color_page.ui \
    set_font_size_page.ui \
    textEditWidget.ui \
    text_editing.ui \
    widget.ui

RESOURCES += \
    image.qrc

DISTFILES +=
unix {
    target.path = /usr/bin/
    INSTALLS += target
}

desktopfile.files = ukui_notebook.desktop
desktopfile.path = /usr/share/applications/

INSTALLS += desktopfile
