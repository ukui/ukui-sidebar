include(../../env.pri)
QT       += core gui widgets dbus

TARGET = shortcutPanel

TEMPLATE = lib

CONFIG += plugin

CONFIG += c++11 link_pkgconfig

PKGCONFIG +=gio-2.0 glib-2.0 gio-unix-2.0
LIBS += -lX11 -lgio-2.0 -lgobject-2.0 -lglib-2.0

#DESTDIR = ../ukui-quick-operation-panel
RESOURCES  += shortcutPanelPlugin.qrc
PKGCONFIG  += gsettings-qt
#LIBS          +=  -L$$[QT_INSTALL_LIBS] -ldconf
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accountinformation.cpp \
    alarmbuttoninterface.cpp \
    automaticrotationwidget.cpp \
    customstyle_switchNormalStatus.cpp \
    VPNButtonwidget.cpp \
    dropdownbox.cpp \
    editconfirmationarea.cpp \
    eyeprotectionmode.cpp \
    iconlabel.cpp \
    labelfotmattext.cpp \
    notebookbuttonwidget.cpp \
    powersavingmode.cpp \
    scrollingareawidget.cpp \
    swichButtonOpenStatus.cpp \
    bluetoothwidget.cpp \
    calculatorwidget.cpp \
    hotspotwidget.cpp \
    mainwidget.cpp \
    nodisturbwidget.cpp \
    padwidget.cpp \
    pushbutton.cpp \
    screenshotwidget.cpp \
    settingwidget.cpp \
    shortcutpanelplugin.cpp \
    switchbutton.cpp \
    weatherwidget.cpp \
    wifiwidget.cpp \

HEADERS += \
    accountinformation.h \
    alarmbuttoninterface.h \
    automaticrotationwidget.h \
    customstyle_switchNormalStatus.h \
    VPNButtonwidget.h \
    dropdownbox.h \
    editconfirmationarea.h \
    eyeprotectionmode.h \
    iconlabel.h \
    labelfotmattext.h \
    notebookbuttonwidget.h \
    powersavingmode.h \
    scrollingareawidget.h \
    swichButtonOpenStatus.h \
    bluetoothwidget.h \
    calculatorwidget.h \
    data.h \
    hotspotwidget.h \
    mainwidget.h \
    nodisturbwidget.h \
    padwidget.h \
    pushbutton.h \
    screenshotwidget.h \
    settingwidget.h \
    shortcutpanelplugin.h \
    switchbutton.h \
    weatherwidget.h \
    wifiwidget.h \

INCLUDEPATH    += ../../plugin-interface

DISTFILES += shortcutPanelPlugin.json

TRANSLATIONS += ../../../translations/ukui-quick-operation-panel/ukui-quick-operation-panel_zh_CN.ts \
                ../../../translations/ukui-quick-operation-panel/ukui-quick-operation-panel_tr.ts

translation.path = /usr/share/ukui-sidebar/ukui-quick-operation-panel
translation.files += ../../../translations/ukui-quick-operation-panel/*.qm

schemes.files += data/org.ukui.quick.operation.panel.gschema.xml
schemes.files += data/org.ukui.quick.operation.button.gschema.xml
schemes.path = /usr/share/glib-2.0/schemas/

# Default rules for deployment.
unix {
    target.path = $${PLUGIN_INSTALL_DIRS}
    INSTALLS += target schemes translation
}
#!isEmpty(target.path): INSTALLS += target
