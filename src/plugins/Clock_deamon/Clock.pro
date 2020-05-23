#-------------------------------------------------
#
# Project created by QtCreator 2014-06-28T21:00:26
#
#-------------------------------------------------

QT       += core gui multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ukui-clock
TEMPLATE = app



SOURCES += \
    btn_new.cpp \
        clock.cpp \
    customstyle.cpp \
    delete_msg.cpp \
    item_new.cpp \
    main.cpp \
    notice_alarm.cpp \
    notice_dialog.cpp \
    setuppage.cpp \
    singleApplication.cpp \
    stopwatch_item.cpp \
    verticalscroll_24.cpp \
    verticalscroll_60.cpp \
    verticalscroll_99.cpp \
    clickablelabel.cpp \
    DotLineDemo.cpp \
    set_alarm_repeat_dialog.cpp \
    countdown_animation.cpp \
    QRoundProgressBar.cpp
TRANSLATIONS = Clock.ts

HEADERS  += clock.h \
    btn_new.h \
    connection.h \
    customstyle.h \
    debug.h \
    delete_msg.h \
    item_new.h \
    notice_alarm.h \
    notice_dialog.h \
    setuppage.h \
    singleApplication.h \
    stopwatch_item.h \
    verticalscroll_24.h \
    verticalscroll_60.h \
    verticalscroll_99.h \
    clickablelabel.h \
    DotLineDemo.h \
    set_alarm_repeat_dialog.h \
    countdown_animation.h \
    QRoundProgressBar.h


FORMS    += clock.ui \
    delete_msg.ui \
    notice_alarm.ui \
    setuppage.ui


RESOURCES += \
    images.qrc

RC_FILE = clock.rc

unix {
    target.path = /usr/bin/
    INSTALLS += target
}
desktopfile.files = clock.desktop
desktopfile.path = /usr/share/applications/

INSTALLS += desktopfile
