#-------------------------------------------------
#
# Project created by QtCreator 2020-03-17T10:53:26
#
#-------------------------------------------------

include(./env.pri)
include($$PROJECT_COMPONENTSOURCE/closebutton.pri)

QT  +=  core gui printsupport sql concurrent network KWindowSystem dbus x11extras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ukui-notebook
TEMPLATE = app

LIBS  +=  -lpthread
LIBS  +=  -lX11 -lXrandr -lXinerama -lXi -lXcursor

PKGCONFIG += gsettings-qt

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

CONFIG += c++11 link_pkgconfig

INCLUDEPATH   +=  \
                 $$PROJECT_COMPONENTSOURCE \

TRANSLATIONS += \
        ../../../translations/ukui-notebook/ukui-notebook_zh_CN.ts
        ../../../translations/ukui-notebook/ukui-notebook_tr.ts

SOURCES += \
    about.cpp \
    utils/utils.cpp \
    utils/xatom-helper.cpp \
    adaptscreeninfo.cpp \
    customStyle.cpp \
    dbManager.cpp \
    editPage.cpp \
    emptyNotes.cpp \
    fontButton.cpp \
    headerbar.cpp \
    iconViewModeDelegate.cpp \
    listViewModeDelegate.cpp \
    main.cpp \
    myThrow.cpp \
    noteData.cpp \
    noteExitWindow.cpp \
    noteHead.cpp \
    noteHeadMenu.cpp \
    noteModel.cpp \
    noteView.cpp \
    paletteButton.cpp \
    paletteWidget.cpp \
    selectColorPage.cpp \
    setFontColorPage.cpp \
    setFontSizePage.cpp \
    singleApplication.cpp \
    singleitemButton.cpp \
    widget.cpp

HEADERS += \
    about.h \
    utils/utils.h \
    utils/xatom-helper.h \
    adaptscreeninfo.h \
    customStyle.h \
    dbManager.h \
    editPage.h \
    emptyNotes.h \
    fontButton.h \
    headerbar.h \
    iconViewModeDelegate.h \
    listViewModeDelegate.h \
    myThrow.h \
    noteData.h \
    noteExitWindow.h \
    noteHead.h \
    noteHeadMenu.h \
    noteModel.h \
    noteView.h \
    paletteButton.h \
    paletteWidget.h \
    selectColorPage.h \
    setFontColorPage.h \
    setFontSizePage.h \
    singleApplication.h \
    singleitemButton.h \
    widget.h

FORMS += \
    about.ui \
    editPage.ui \
    emptyNotes.ui \
    fontButton.ui \
    noteExitWindow.ui \
    noteHead.ui \
    noteHeadMenu.ui \
    paletteButton.ui \
    paletteWidget.ui \
    selectColorPage.ui \
    setFontColorPage.ui \
    setFontSizePage.ui \
    widget.ui

RESOURCES += \
    image.qrc

DISTFILES +=
unix {
    target.path = /usr/bin/
    INSTALLS += target

    translation.path = /usr/share/ukui-sidebar/ukui-notebook
    translation.files += ../../../translations/ukui-notebook/*.qm
    INSTALLS += translation
}

desktopfile.files = ukui-notebook.desktop
desktopfile.path = /usr/share/applications/

INSTALLS += desktopfile
