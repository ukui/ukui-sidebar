#-------------------------------------------------
#
# Project created by QtCreator 2020-01-08T10:30:22
#
#-------------------------------------------------

QT       += core gui sql
QT += widgets

TARGET = clipboardPlugin
TEMPLATE = lib
CONFIG += plugin

include(../../env.pri)

DEFINES += QT_DEPRECATED_WARNINGS

RESOURCES  += clipboardPlugin.qrc
SOURCES += \
    cleanpromptbox.cpp \
    clipBoardInternalSignal.cpp \
    customstyle.cpp \
    customstyleCleanPushbutton.cpp \
    customstylePushbutton2.cpp \
    customstyleSearchPushbutton.cpp \
    pixmaplabel.cpp \
    sidebarclipboardplugin.cpp \
    clipboardwidgetentry.cpp \
    editorwidget.cpp \
    searchwidgetitemcontent.cpp \
    clipboardlisetwidget.cpp \
    clipboarddb.cpp \
    previewimagewidget.cpp

INCLUDEPATH    += ../../plugin-interface ../../plugin-signals

HEADERS += \
    cleanpromptbox.h \
    clipBoardInternalSignal.h \
    customstyle.h \
    customstyleCleanPushbutton.h \
    customstylePushbutton2.h \
    customstyleSearchPushbutton.h \
    pixmaplabel.h \
    sidebarclipboardplugin.h \
    clipboardwidgetentry.h \
    clipboardsignal.h \
    editorwidget.h \
    searchwidgetitemcontent.h \
    ../../plugin-signals/sidebarclipboardsignal.h \
    clipboardlisetwidget.h \
    clipbaordstructoriginaldata.h \
    clipboarddb.h \
    previewimagewidget.h
DISTFILES += clipboardPlugin.json 

TRANSLATIONS += ../../../translations/ukui-sidebar-clipboard/ukui-sidebar-clipboard_zh_CN.ts \
                ../../../translations/ukui-sidebar-clipboard/ukui-sidebar-clipboard_bo.ts \
                ../../../translations/ukui-sidebar-clipboard/ukui-sidebar-clipboard_tr.ts

unix {
    target.path = $${PLUGIN_INSTALL_DIRS}
    INSTALLS += target
}
