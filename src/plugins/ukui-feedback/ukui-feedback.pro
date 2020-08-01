QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = ukui-feedback
TEMPLATE = app

LIBS    +=  -lX11

QT += core gui  network

DEFINES += QT_DEPRECATED_WARNINGS

TRANSLATIONS += ../../../translations/ukui-feedback/ukui-feedback_en.ts

SOURCES += \
    browseButton.cpp \
    closebtnHover.cpp \
    customStyle.cpp \
    fileitemInit.cpp \
    hidebtnHover.cpp \
    main.cpp \
    singleApplication.cpp \
    submitFail.cpp \
    submitSuccess.cpp \
    systeminfoButton.cpp \
    ukuiFeedback.cpp

HEADERS += \
    browseButton.h \
    closebtnHover.h \
    customStyle.h \
    fileitemInit.h \
    hidebtnHover.h \
    singleApplication.h \
    submitFail.h \
    submitSuccess.h \
    systeminfoButton.h \
    ukuiFeedback.h

RESOURCES += \
    ukuiFeedback.qrc

DISTFILES +=

unix {
    target.path = /usr/bin/
    INSTALLS += target
}

desktopfile.files = ukui-feedback.desktop
desktopfile.path = /usr/share/applications/

INSTALLS += desktopfile
