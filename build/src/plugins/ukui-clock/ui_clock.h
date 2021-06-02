/********************************************************************************
** Form generated from reading UI file 'clock.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLOCK_H
#define UI_CLOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "countdownAnimation.h"

QT_BEGIN_NAMESPACE

class Ui_Clock
{
public:
    QAction *actionOn;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QStackedWidget *stackedWidget_4;
    QWidget *page_4;
    QLabel *label_8;
    QPushButton *min_5btn;
    QPushButton *min_10btn;
    QPushButton *min_20btn;
    QPushButton *min_30btn;
    QPushButton *min_60btn;
    Countdown_Animation *page_5;
    QLabel *label_9;
    QPushButton *count_push;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QLabel *label_11;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *count_stat;
    QWidget *page_2;
    QLabel *label_6;
    QPushButton *addAlarmBtn;
    QLabel *label_7;
    QListWidget *listWidget;
    QLabel *label_15;
    QLabel *noAlarmIcon;
    QLabel *noAlarm;
    QWidget *page_3;
    QPushButton *pushButton_Start;
    QLabel *label_5;
    QLabel *label_4;
    QPushButton *pushButton_timeselect;
    QPushButton *pushButton_ring;
    QListWidget *listWidget_2;
    QWidget *page_6;
    QWidget *set_page;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QLabel *label_12;
    QPushButton *set_alarm_cancelbtn;
    QPushButton *set_alarm_savebtn;
    QLabel *label_13;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_14;
    QLineEdit *lineEdit;
    QLabel *label_17;
    QPushButton *pushButton_5;
    QPushButton *pushButton_4;
    QStackedWidget *stackedWidget_3;
    QWidget *page_7;
    QToolButton *pushButton_12;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *Clock)
    {
        if (Clock->objectName().isEmpty())
            Clock->setObjectName(QString::fromUtf8("Clock"));
        Clock->resize(390, 580);
        Clock->setStyleSheet(QString::fromUtf8(""));
        actionOn = new QAction(Clock);
        actionOn->setObjectName(QString::fromUtf8("actionOn"));
        actionOn->setCheckable(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Images/Images/NO.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOn->setIcon(icon);
        stackedWidget = new QStackedWidget(Clock);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 115, 390, 466));
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        stackedWidget_4 = new QStackedWidget(page);
        stackedWidget_4->setObjectName(QString::fromUtf8("stackedWidget_4"));
        stackedWidget_4->setGeometry(QRect(0, 0, 454, 466));
        stackedWidget_4->setStyleSheet(QString::fromUtf8(""));
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        label_8 = new QLabel(page_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(129, 178, 195, 45));
        label_8->setStyleSheet(QString::fromUtf8("font: 36pt ;"));
        min_5btn = new QPushButton(page_4);
        min_5btn->setObjectName(QString::fromUtf8("min_5btn"));
        min_5btn->setGeometry(QRect(24, 414, 56, 36));
        min_5btn->setStyleSheet(QString::fromUtf8(""));
        min_10btn = new QPushButton(page_4);
        min_10btn->setObjectName(QString::fromUtf8("min_10btn"));
        min_10btn->setGeometry(QRect(111, 414, 56, 36));
        min_10btn->setStyleSheet(QString::fromUtf8(""));
        min_20btn = new QPushButton(page_4);
        min_20btn->setObjectName(QString::fromUtf8("min_20btn"));
        min_20btn->setGeometry(QRect(199, 414, 56, 36));
        min_20btn->setStyleSheet(QString::fromUtf8(""));
        min_30btn = new QPushButton(page_4);
        min_30btn->setObjectName(QString::fromUtf8("min_30btn"));
        min_30btn->setGeometry(QRect(287, 414, 56, 36));
        min_30btn->setStyleSheet(QString::fromUtf8(""));
        min_60btn = new QPushButton(page_4);
        min_60btn->setObjectName(QString::fromUtf8("min_60btn"));
        min_60btn->setGeometry(QRect(374, 414, 56, 36));
        min_60btn->setStyleSheet(QString::fromUtf8(""));
        stackedWidget_4->addWidget(page_4);
        page_5 = new Countdown_Animation();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        label_9 = new QLabel(page_5);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(97, 124, 195, 71));
        label_9->setStyleSheet(QString::fromUtf8("font-size:40px;"));
        count_push = new QPushButton(page_5);
        count_push->setObjectName(QString::fromUtf8("count_push"));
        count_push->setGeometry(QRect(210, 401, 72, 34));
        count_push->setStyleSheet(QString::fromUtf8(""));
        horizontalLayoutWidget = new QWidget(page_5);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 90, 391, 38));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(horizontalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 0));
        pushButton->setMaximumSize(QSize(26, 1111));

        horizontalLayout->addWidget(pushButton);

        label_11 = new QLabel(horizontalLayoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setStyleSheet(QString::fromUtf8("color: rgb(176, 176, 176);\n"
"font-size:16px;\n"
"\n"
"\n"
""));

        horizontalLayout->addWidget(label_11);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        count_stat = new QPushButton(page_5);
        count_stat->setObjectName(QString::fromUtf8("count_stat"));
        count_stat->setGeometry(QRect(108, 401, 72, 34));
        count_stat->setStyleSheet(QString::fromUtf8(""));
        stackedWidget_4->addWidget(page_5);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        label_6 = new QLabel(page_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(116, 0, 221, 61));
        label_6->setStyleSheet(QString::fromUtf8("font: 36pt ;\n"
""));
        addAlarmBtn = new QPushButton(page_2);
        addAlarmBtn->setObjectName(QString::fromUtf8("addAlarmBtn"));
        addAlarmBtn->setGeometry(QRect(159, 401, 72, 34));
        addAlarmBtn->setStyleSheet(QString::fromUtf8(""));
        label_7 = new QLabel(page_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(8, 67, 441, 31));
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"color: rgb(148, 148, 148);\n"
"font: 13pt ;\n"
"opacity:0.45;"));
        listWidget = new QListWidget(page_2);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(25, 0, 340, 354));
        listWidget->setStyleSheet(QString::fromUtf8(""));
        label_15 = new QLabel(page_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(80, 30, 31, 22));
        noAlarmIcon = new QLabel(page_2);
        noAlarmIcon->setObjectName(QString::fromUtf8("noAlarmIcon"));
        noAlarmIcon->setGeometry(QRect(115, 76, 149, 170));
        noAlarm = new QLabel(page_2);
        noAlarm->setObjectName(QString::fromUtf8("noAlarm"));
        noAlarm->setGeometry(QRect(125, 262, 140, 31));
        noAlarm->setStyleSheet(QString::fromUtf8("color: rgba(49, 66, 89, 0.6);\n"
"font-size:16px;"));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        pushButton_Start = new QPushButton(page_3);
        pushButton_Start->setObjectName(QString::fromUtf8("pushButton_Start"));
        pushButton_Start->setGeometry(QRect(210, 401, 72, 34));
        pushButton_Start->setStyleSheet(QString::fromUtf8(""));
        label_5 = new QLabel(page_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(90, 55, 210, 41));
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(176, 176, 176);\n"
"font: 19pt \n"
""));
        label_4 = new QLabel(page_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(90, 0, 210, 61));
        label_4->setStyleSheet(QString::fromUtf8("font: 30pt "));
        pushButton_timeselect = new QPushButton(page_3);
        pushButton_timeselect->setObjectName(QString::fromUtf8("pushButton_timeselect"));
        pushButton_timeselect->setGeometry(QRect(108, 401, 72, 34));
        pushButton_timeselect->setStyleSheet(QString::fromUtf8(""));
        pushButton_ring = new QPushButton(page_3);
        pushButton_ring->setObjectName(QString::fromUtf8("pushButton_ring"));
        pushButton_ring->setGeometry(QRect(108, 401, 72, 34));
        pushButton_ring->setStyleSheet(QString::fromUtf8(""));
        listWidget_2 = new QListWidget(page_3);
        listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));
        listWidget_2->setGeometry(QRect(25, 109, 340, 277));
        listWidget_2->setStyleSheet(QString::fromUtf8(""));
        stackedWidget->addWidget(page_3);
        pushButton_Start->raise();
        label_5->raise();
        label_4->raise();
        pushButton_ring->raise();
        listWidget_2->raise();
        pushButton_timeselect->raise();
        page_6 = new QWidget();
        page_6->setObjectName(QString::fromUtf8("page_6"));
        set_page = new QWidget(page_6);
        set_page->setObjectName(QString::fromUtf8("set_page"));
        set_page->setGeometry(QRect(0, 0, 390, 466));
        set_page->setMaximumSize(QSize(16777215, 16777215));
        set_page->setStyleSheet(QString::fromUtf8(""));
        pushButton_8 = new QPushButton(set_page);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(20, 360, 72, 34));
        pushButton_8->setStyleSheet(QString::fromUtf8(""));
        pushButton_9 = new QPushButton(set_page);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(210, 401, 72, 34));
        pushButton_9->setStyleSheet(QString::fromUtf8(""));
        label_12 = new QLabel(set_page);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(20, 30, 400, 25));
        label_12->setStyleSheet(QString::fromUtf8("width:173px;\n"
"height:18px;\n"
"font-size:18px;\n"
"font-weight:400;\n"
"color:rgba(148, 148, 148,1);\n"
"opacity:0.45;\n"
""));
        set_alarm_cancelbtn = new QPushButton(set_page);
        set_alarm_cancelbtn->setObjectName(QString::fromUtf8("set_alarm_cancelbtn"));
        set_alarm_cancelbtn->setGeometry(QRect(108, 401, 72, 34));
        set_alarm_cancelbtn->setStyleSheet(QString::fromUtf8(""));
        set_alarm_savebtn = new QPushButton(set_page);
        set_alarm_savebtn->setObjectName(QString::fromUtf8("set_alarm_savebtn"));
        set_alarm_savebtn->setGeometry(QRect(210, 401, 72, 34));
        set_alarm_savebtn->setStyleSheet(QString::fromUtf8(""));
        label_13 = new QLabel(set_page);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(123, 3, 200, 28));
        label_13->setStyleSheet(QString::fromUtf8("font:  13pt;\n"
""));
        widget = new QWidget(set_page);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(25, 185, 340, 48));
        widget->setStyleSheet(QString::fromUtf8("width:280px;\n"
"height:36px;\n"
"border-radius:4px;\n"
""));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_14 = new QLabel(widget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(label_14);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setStyleSheet(QString::fromUtf8("color:rgba(148, 148, 148,1);\n"
""));

        horizontalLayout_2->addWidget(lineEdit);

        label_17 = new QLabel(set_page);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(80, 76, 31, 22));
        stackedWidget->addWidget(page_6);
        pushButton_5 = new QPushButton(Clock);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(356, 4, 30, 30));
        pushButton_4 = new QPushButton(Clock);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(322, 4, 30, 30));
        stackedWidget_3 = new QStackedWidget(Clock);
        stackedWidget_3->setObjectName(QString::fromUtf8("stackedWidget_3"));
        stackedWidget_3->setGeometry(QRect(0, 37, 390, 300));
        stackedWidget_3->setStyleSheet(QString::fromUtf8(""));
        page_7 = new QWidget();
        page_7->setObjectName(QString::fromUtf8("page_7"));
        stackedWidget_3->addWidget(page_7);
        pushButton_12 = new QToolButton(Clock);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setGeometry(QRect(288, 4, 30, 30));
        label = new QLabel(Clock);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(36, 4, 41, 31));
        label_2 = new QLabel(Clock);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(8, 8, 24, 24));
        label_2->setStyleSheet(QString::fromUtf8("border-image: url(:/image/kylin-alarm-clock.png);"));
        stackedWidget_3->raise();
        stackedWidget->raise();
        pushButton_12->raise();
        pushButton_4->raise();
        pushButton_5->raise();
        label->raise();
        label_2->raise();

        retranslateUi(Clock);

        stackedWidget->setCurrentIndex(3);
        stackedWidget_4->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Clock);
    } // setupUi

    void retranslateUi(QWidget *Clock)
    {
        Clock->setWindowTitle(QApplication::translate("Clock", "Clock", nullptr));
        actionOn->setText(QApplication::translate("Clock", "On", nullptr));
        label_8->setText(QApplication::translate("Clock", "00:00:00", nullptr));
        min_5btn->setText(QApplication::translate("Clock", "5min", nullptr));
        min_10btn->setText(QApplication::translate("Clock", "15min", nullptr));
        min_20btn->setText(QApplication::translate("Clock", "25min", nullptr));
        min_30btn->setText(QApplication::translate("Clock", "30min", nullptr));
        min_60btn->setText(QApplication::translate("Clock", "60min", nullptr));
        label_9->setText(QApplication::translate("Clock", "00:00:00", nullptr));
        count_push->setText(QApplication::translate("Clock", "suspend", nullptr));
        pushButton->setText(QString());
        label_11->setText(QApplication::translate("Clock", "PM", nullptr));
        label_3->setText(QString());
        count_stat->setText(QApplication::translate("Clock", "start", nullptr));
        label_6->setText(QApplication::translate("Clock", "00:00:00", nullptr));
        addAlarmBtn->setText(QApplication::translate("Clock", "add", nullptr));
        label_7->setText(QApplication::translate("Clock", "Remaining time", nullptr));
        label_15->setText(QString());
        noAlarmIcon->setText(QString());
        noAlarm->setText(QApplication::translate("Clock", "no alarm", nullptr));
        pushButton_Start->setText(QApplication::translate("Clock", "start", nullptr));
        label_5->setText(QApplication::translate("Clock", "00:00:00", nullptr));
        label_4->setText(QApplication::translate("Clock", "00:00:00", nullptr));
        pushButton_timeselect->setText(QApplication::translate("Clock", "reset", nullptr));
        pushButton_ring->setText(QApplication::translate("Clock", "count", nullptr));
        pushButton_8->setText(QApplication::translate("Clock", "delete", nullptr));
        pushButton_9->setText(QApplication::translate("Clock", "Preservation", nullptr));
        label_12->setText(QApplication::translate("Clock", "12hour43minThe bell rings", nullptr));
        set_alarm_cancelbtn->setText(QApplication::translate("Clock", "cancel", nullptr));
        set_alarm_savebtn->setText(QApplication::translate("Clock", "Preservation", nullptr));
        label_13->setText(QApplication::translate("Clock", "New alarm", nullptr));
        label_14->setText(QApplication::translate("Clock", "  Name", nullptr));
        label_17->setText(QString());
        pushButton_5->setText(QString());
        pushButton_4->setText(QString());
        pushButton_12->setText(QString());
        label->setText(QApplication::translate("Clock", "Alarm", nullptr));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Clock: public Ui_Clock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLOCK_H
