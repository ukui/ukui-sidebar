/********************************************************************************
** Form generated from reading UI file 'clock.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLOCK_H
#define UI_CLOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include <clickableLabel.h>
#include "countdownAnimation.h"

QT_BEGIN_NAMESPACE

class Ui_Clock
{
public:
    QAction *actionOn;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *count_stat;
    QStackedWidget *stackedWidget_4;
    QWidget *page_4;
    QLabel *label_8;
    QPushButton *min_5btn;
    QPushButton *min_10btn;
    QPushButton *min_20btn;
    QPushButton *min_30btn;
    QPushButton *min_60btn;
    QFrame *line;
    Countdown_Animation *page_5;
    QLabel *label_9;
    QPushButton *count_push;
    QFrame *line_3;
    QWidget *widget_5;
    QLabel *label_23;
    QPushButton *pushButton_19;
    QPushButton *pushButton_20;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_10;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer_2;
    QWidget *page_2;
    QLabel *label_6;
    QPushButton *addAlarmBtn;
    QLabel *label_7;
    QListWidget *listWidget;
    QFrame *line_4;
    QLabel *label_15;
    QWidget *page_3;
    QPushButton *pushButton_Start;
    QLabel *label_5;
    QLabel *label_4;
    QPushButton *pushButton_timeselect;
    QPushButton *pushButton_ring;
    QListWidget *listWidget_2;
    QFrame *line_5;
    QPushButton *pushButton_5;
    QPushButton *pushButton_4;
    QStackedWidget *stackedWidget_3;
    QWidget *page_7;
    QPushButton *pushButton_3;
    ClickableLabel *label;
    ClickableLabel *label_2;
    ClickableLabel *label_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QFrame *line_2;
    QWidget *set_page;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QLabel *label_12;
    QPushButton *set_alarm_cancelbtn;
    QPushButton *set_alarm_savebtn;
    QLabel *label_13;
    QWidget *widget;
    QLabel *label_14;
    QLineEdit *lineEdit;
    QWidget *widget_2;
    QLabel *label_18;
    QPushButton *pushButton_10;
    QPushButton *pushButton_6;
    QWidget *widget_3;
    QLabel *label_19;
    QPushButton *pushButton_7;
    QPushButton *pushButton_11;
    QWidget *widget_4;
    QLabel *label_22;
    QPushButton *pushButton_16;
    QPushButton *pushButton_17;
    QLabel *label_17;
    QPushButton *pushButton_12;

    void setupUi(QWidget *Clock)
    {
        if (Clock->objectName().isEmpty())
            Clock->setObjectName(QStringLiteral("Clock"));
        Clock->resize(454, 660);
        Clock->setStyleSheet(QLatin1String("background-color: rgba(14,19,22,1);\n"
"\n"
"color: rgb(255, 255, 255);\n"
""));
        actionOn = new QAction(Clock);
        actionOn->setObjectName(QStringLiteral("actionOn"));
        actionOn->setCheckable(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Images/Images/NO.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOn->setIcon(icon);
        stackedWidget = new QStackedWidget(Clock);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 110, 454, 541));
        stackedWidget->setStyleSheet(QStringLiteral("border-radius:7px;"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        count_stat = new QPushButton(page);
        count_stat->setObjectName(QStringLiteral("count_stat"));
        count_stat->setGeometry(QRect(178, 476, 100, 32));
        count_stat->setStyleSheet(QLatin1String("QPushButton{color: rgb(255, 255, 255);\n"
"background-color: rgba(39,207,129,0.9);\n"
" border-radius:4px;\n"
"font: 11pt ;}\n"
"QPushButton:hover{background-color: rgb(27, 143, 89);}\n"
"\n"
""));
        stackedWidget_4 = new QStackedWidget(page);
        stackedWidget_4->setObjectName(QStringLiteral("stackedWidget_4"));
        stackedWidget_4->setGeometry(QRect(0, 0, 454, 461));
        stackedWidget_4->setStyleSheet(QStringLiteral(""));
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        label_8 = new QLabel(page_4);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(129, 178, 195, 45));
        label_8->setStyleSheet(QStringLiteral("font: 36pt ;"));
        min_5btn = new QPushButton(page_4);
        min_5btn->setObjectName(QStringLiteral("min_5btn"));
        min_5btn->setGeometry(QRect(24, 404, 56, 36));
        min_5btn->setStyleSheet(QLatin1String("QPushButton{\n"
"width:56px;\n"
"font: 11pt ;\n"
"height:36px;\n"
"background:rgba(46,46,46,1);\n"
"border-radius:4px;}\n"
"QPushButton:hover{background:rgba(143, 97, 47, 0.1)}\n"
""));
        min_10btn = new QPushButton(page_4);
        min_10btn->setObjectName(QStringLiteral("min_10btn"));
        min_10btn->setGeometry(QRect(111, 404, 56, 36));
        min_10btn->setStyleSheet(QLatin1String("QPushButton{\n"
"width:56px;\n"
"font: 11pt ;\n"
"height:36px;\n"
"background:rgba(46,46,46,1);\n"
"border-radius:4px;}\n"
"QPushButton:hover{background:rgba(143, 97, 47, 0.1)}"));
        min_20btn = new QPushButton(page_4);
        min_20btn->setObjectName(QStringLiteral("min_20btn"));
        min_20btn->setGeometry(QRect(199, 404, 56, 36));
        min_20btn->setStyleSheet(QLatin1String("QPushButton{\n"
"width:56px;\n"
"font: 11pt ;\n"
"height:36px;\n"
"background:rgba(46,46,46,1);\n"
"border-radius:4px;}\n"
"QPushButton:hover{background:rgba(143, 97, 47, 0.1)}"));
        min_30btn = new QPushButton(page_4);
        min_30btn->setObjectName(QStringLiteral("min_30btn"));
        min_30btn->setGeometry(QRect(287, 404, 56, 36));
        min_30btn->setStyleSheet(QLatin1String("QPushButton{\n"
"width:56px;\n"
"font: 11pt ;\n"
"height:36px;\n"
"background:rgba(46,46,46,1);\n"
"border-radius:4px;}\n"
"QPushButton:hover{background:rgba(143, 97, 47, 0.1)}"));
        min_60btn = new QPushButton(page_4);
        min_60btn->setObjectName(QStringLiteral("min_60btn"));
        min_60btn->setGeometry(QRect(374, 404, 56, 36));
        min_60btn->setStyleSheet(QLatin1String("QPushButton{\n"
"width:56px;\n"
"font: 11pt ;\n"
"height:36px;\n"
"background:rgba(46,46,46,1);\n"
"border-radius:4px;}\n"
"QPushButton:hover{background:rgba(143, 97, 47, 0.1)}"));
        line = new QFrame(page_4);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 0, 545, 1));
        line->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgba(255, 255, 255,0.04);"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        stackedWidget_4->addWidget(page_4);
        page_5 = new Countdown_Animation();
        page_5->setObjectName(QStringLiteral("page_5"));
        label_9 = new QLabel(page_5);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(129, 178, 195, 45));
        label_9->setStyleSheet(QStringLiteral("font: 36pt ;"));
        count_push = new QPushButton(page_5);
        count_push->setObjectName(QStringLiteral("count_push"));
        count_push->setGeometry(QRect(193, 259, 68, 68));
        count_push->setStyleSheet(QLatin1String("QPushButton{color: rgb(255, 255, 255);\n"
" background-color: rgba(231,159,78,0.9);\n"
" border-radius:34px;}\n"
" QPushButton:hover{background:rgba(143, 97, 47, 0.6)}"));
        line_3 = new QFrame(page_5);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(0, 0, 545, 1));
        line_3->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgba(255, 255, 255,0.04);"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        widget_5 = new QWidget(page_5);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setGeometry(QRect(87, 405, 280, 36));
        widget_5->setStyleSheet(QLatin1String("width:280px;\n"
"height:36px;\n"
"background:rgba(48,48,51,1);\n"
"border-radius:4px;\n"
""));
        label_23 = new QLabel(widget_5);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(0, 0, 61, 31));
        label_23->setStyleSheet(QLatin1String("width:39px;\n"
"height:14px;\n"
"font-size:14px;\n"
"font-weight:400;\n"
"color:rgba(255,255,255,1);\n"
""));
        pushButton_19 = new QPushButton(widget_5);
        pushButton_19->setObjectName(QStringLiteral("pushButton_19"));
        pushButton_19->setGeometry(QRect(244, 0, 36, 36));
        pushButton_20 = new QPushButton(widget_5);
        pushButton_20->setObjectName(QStringLiteral("pushButton_20"));
        pushButton_20->setGeometry(QRect(70, 0, 171, 36));
        pushButton_20->setStyleSheet(QLatin1String("width:67px;\n"
"height:14px;\n"
"font-size:14px;\n"
"font-weight:400;\n"
"color:rgba(148, 148, 148,1);\n"
"opacity:0.35;\n"
"text-align: right"));
        horizontalLayoutWidget = new QWidget(page_5);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(100, 130, 241, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_10 = new QLabel(horizontalLayoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setMinimumSize(QSize(20, 20));
        label_10->setMaximumSize(QSize(20, 20));
        label_10->setStyleSheet(QStringLiteral("border-image: url(:/icon-4-16x16.png);"));

        horizontalLayout->addWidget(label_10);

        label_11 = new QLabel(horizontalLayoutWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setStyleSheet(QLatin1String("width:70px;\n"
"height:14px;\n"
"font-size:14px;\n"
"font-family:Source Han Sans CN;\n"
"font-weight:400;\n"
"color:rgba(255,255,255,1);\n"
"opacity:0.45;\n"
""));

        horizontalLayout->addWidget(label_11);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        stackedWidget_4->addWidget(page_5);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        label_6 = new QLabel(page_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(116, 19, 221, 61));
        label_6->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font: 36pt ;\n"
""));
        addAlarmBtn = new QPushButton(page_2);
        addAlarmBtn->setObjectName(QStringLiteral("addAlarmBtn"));
        addAlarmBtn->setGeometry(QRect(177, 476, 100, 32));
        addAlarmBtn->setStyleSheet(QLatin1String("QPushButton{width:100px;\n"
" height:32px;\n"
"background: rgba(39,207,129,0.9) ;\n"
"border-radius:4px;font: 12pt;}\n"
"\n"
"QPushButton:hover{background-color: rgb(27, 143, 89);}\n"
""));
        label_7 = new QLabel(page_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(8, 93, 441, 25));
        label_7->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"color: rgb(148, 148, 148);\n"
"font: 13pt ;\n"
"opacity:0.45;"));
        listWidget = new QListWidget(page_2);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(39, 130, 376, 294));
        listWidget->setStyleSheet(QLatin1String("selection-background-color:rgba(72,72,76,1);\n"
"border-radius:0px 0px 6px 6px;\n"
""));
        line_4 = new QFrame(page_2);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(0, 0, 545, 1));
        line_4->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgba(255, 255, 255,0.04);"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        label_15 = new QLabel(page_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(80, 50, 31, 22));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        pushButton_Start = new QPushButton(page_3);
        pushButton_Start->setObjectName(QStringLiteral("pushButton_Start"));
        pushButton_Start->setGeometry(QRect(292, 476, 100, 32));
        pushButton_Start->setStyleSheet(QLatin1String("QPushButton{\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgba(39,207,129,0.9);\n"
"border-radius:4px;\n"
"}\n"
"QPushButton:hover{background-color: rgb(27, 143, 89);}\n"
""));
        label_5 = new QLabel(page_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(177, 110, 100, 20));
        label_5->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"color: rgb(148, 148, 148);\n"
"font: 12pt \"Sans Serif\";"));
        label_4 = new QLabel(page_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(122, 36, 210, 61));
        label_4->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"\n"
"font: 36pt ;"));
        pushButton_timeselect = new QPushButton(page_3);
        pushButton_timeselect->setObjectName(QStringLiteral("pushButton_timeselect"));
        pushButton_timeselect->setGeometry(QRect(62, 476, 100, 32));
        pushButton_timeselect->setStyleSheet(QLatin1String("background:rgba(28,28,30,1);\n"
"border:1px solid rgba(52,52,56,1);\n"
"border-radius:4px;\n"
"color: rgb(65, 65, 65);"));
        pushButton_ring = new QPushButton(page_3);
        pushButton_ring->setObjectName(QStringLiteral("pushButton_ring"));
        pushButton_ring->setGeometry(QRect(62, 476, 100, 32));
        pushButton_ring->setStyleSheet(QLatin1String("background:rgba(28,28,30,1);\n"
"border:1px solid rgba(52,52,56,1);\n"
"border-radius:4px;\n"
"color: rgb(65, 65, 65);\n"
""));
        listWidget_2 = new QListWidget(page_3);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));
        listWidget_2->setGeometry(QRect(39, 130, 376, 311));
        listWidget_2->setStyleSheet(QLatin1String("selection-background-color:rgba(72,72,76,1);\n"
"border-radius:0px 0px 6px 6px;\n"
"\n"
"\n"
"QListWidget::item::selected:active{background-color:rgba(72,72,76,1);border-radius:4px;border:1px solid rgba(97,97,101,1);}\n"
"QListWidget::item:hover{background-color:rgba(72,72,76,0.5);border-radius:4px;}"));
        line_5 = new QFrame(page_3);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(0, 0, 545, 1));
        line_5->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgba(255, 255, 255,0.04);"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        stackedWidget->addWidget(page_3);
        pushButton_Start->raise();
        label_5->raise();
        label_4->raise();
        pushButton_ring->raise();
        listWidget_2->raise();
        line_5->raise();
        pushButton_timeselect->raise();
        pushButton_5 = new QPushButton(Clock);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(420, 4, 30, 30));
        pushButton_4 = new QPushButton(Clock);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(386, 4, 30, 30));
        stackedWidget_3 = new QStackedWidget(Clock);
        stackedWidget_3->setObjectName(QStringLiteral("stackedWidget_3"));
        stackedWidget_3->setGeometry(QRect(0, 30, 454, 633));
        stackedWidget_3->setStyleSheet(QLatin1String("border-radius:7px;\n"
""));
        page_7 = new QWidget();
        page_7->setObjectName(QStringLiteral("page_7"));
        pushButton_3 = new QPushButton(page_7);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(332, 8, 60, 32));
        label = new ClickableLabel(page_7);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(48, 40, 90, 32));
        label->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font: 10pt ;"));
        label_2 = new ClickableLabel(page_7);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(187, 40, 80, 32));
        label_2->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font: 10pt ;"));
        label_3 = new ClickableLabel(page_7);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(322, 40, 80, 32));
        label_3->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font: 10pt ;"));
        pushButton = new QPushButton(page_7);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(63, 8, 60, 32));
        pushButton_2 = new QPushButton(page_7);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(197, 8, 60, 32));
        line_2 = new QFrame(page_7);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(0, 80, 660, 1));
        line_2->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgba(255, 255, 255,0.04);"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        stackedWidget_3->addWidget(page_7);
        set_page = new QWidget(Clock);
        set_page->setObjectName(QStringLiteral("set_page"));
        set_page->setGeometry(QRect(0, 30, 454, 633));
        set_page->setStyleSheet(QStringLiteral("border-radius:7px;"));
        pushButton_8 = new QPushButton(set_page);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(62, 557, 100, 32));
        pushButton_8->setStyleSheet(QLatin1String("QPushButton{\n"
"background:rgba(44,44,46,1);\n"
"border:1px solid rgba(68,68,71,1);\n"
"border-radius:4px;}\n"
"QPushButton:hover{background:rgba(143, 97, 47, 0.1)}"));
        pushButton_9 = new QPushButton(set_page);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setGeometry(QRect(292, 557, 100, 32));
        pushButton_9->setStyleSheet(QLatin1String("QPushButton{\n"
"background: rgb(37, 200, 124);\n"
"border-radius:4px;}\n"
"QPushButton:hover{background-color: rgb(27, 143, 89);}"));
        label_12 = new QLabel(set_page);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(127, 284, 200, 25));
        label_12->setStyleSheet(QLatin1String("width:173px;\n"
"height:18px;\n"
"font-size:18px;\n"
"font-weight:400;\n"
"color:rgba(148, 148, 148,1);\n"
"opacity:0.45;\n"
""));
        set_alarm_cancelbtn = new QPushButton(set_page);
        set_alarm_cancelbtn->setObjectName(QStringLiteral("set_alarm_cancelbtn"));
        set_alarm_cancelbtn->setGeometry(QRect(62, 557, 100, 32));
        set_alarm_cancelbtn->setStyleSheet(QLatin1String("QPushButton{\n"
"width:100px;\n"
"height:32px;\n"
"background:rgba(44,44,46,1);\n"
"border:1px solid rgba(68,68,71,1);\n"
"border-radius:4px;}\n"
"QPushButton:hover{background:rgba(143, 97, 47, 0.1)}"));
        set_alarm_savebtn = new QPushButton(set_page);
        set_alarm_savebtn->setObjectName(QStringLiteral("set_alarm_savebtn"));
        set_alarm_savebtn->setGeometry(QRect(292, 557, 100, 32));
        set_alarm_savebtn->setStyleSheet(QLatin1String("QPushButton{\n"
"background: rgb(37, 200, 124);\n"
"border-radius:4px;}\n"
"QPushButton:hover{background-color: rgb(27, 143, 89);}"));
        label_13 = new QLabel(set_page);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(189, 33, 74, 18));
        label_13->setStyleSheet(QLatin1String("width:74px;\n"
"height:18px;\n"
"font-size:18px;\n"
"font-weight:400;\n"
"color:rgba(255,255,255,1);\n"
""));
        widget = new QWidget(set_page);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(87, 328, 280, 36));
        widget->setStyleSheet(QLatin1String("width:280px;\n"
"height:36px;\n"
"background:rgba(48,48,51,1);\n"
"border-radius:4px;\n"
""));
        label_14 = new QLabel(widget);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(0, 0, 61, 31));
        label_14->setStyleSheet(QLatin1String("width:39px;\n"
"height:14px;\n"
"font-size:14px;\n"
"font-weight:400;\n"
"color:rgba(255,255,255,1);\n"
""));
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(52, 0, 191, 32));
        lineEdit->setStyleSheet(QStringLiteral("color:rgba(148, 148, 148,1);"));
        widget_2 = new QWidget(set_page);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(87, 378, 280, 36));
        widget_2->setStyleSheet(QLatin1String("width:280px;\n"
"height:36px;\n"
"background:rgba(48,48,51,1);\n"
"border-radius:4px;\n"
""));
        label_18 = new QLabel(widget_2);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(0, 0, 61, 31));
        label_18->setStyleSheet(QLatin1String("width:39px;\n"
"height:14px;\n"
"font-size:14px;\n"
"font-weight:400;\n"
"color:rgba(255,255,255,1);\n"
""));
        pushButton_10 = new QPushButton(widget_2);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        pushButton_10->setGeometry(QRect(244, 0, 36, 36));
        pushButton_6 = new QPushButton(widget_2);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(50, 0, 191, 36));
        pushButton_6->setStyleSheet(QLatin1String("width:67px;\n"
"height:14px;\n"
"font-size:14px;\n"
"font-weight:400;\n"
"color:rgba(148, 148, 148,1);\n"
"opacity:0.35;\n"
"text-align: right"));
        widget_3 = new QWidget(set_page);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setGeometry(QRect(87, 428, 280, 36));
        widget_3->setStyleSheet(QLatin1String("width:280px;\n"
"height:36px;\n"
"background:rgba(48,48,51,1);\n"
"border-radius:4px;\n"
""));
        label_19 = new QLabel(widget_3);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(0, 0, 71, 31));
        label_19->setStyleSheet(QLatin1String("width:39px;\n"
"height:14px;\n"
"font-size:14px;\n"
"font-weight:400;\n"
"color:rgba(255,255,255,1);\n"
""));
        pushButton_7 = new QPushButton(widget_3);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(244, 0, 36, 36));
        pushButton_11 = new QPushButton(widget_3);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));
        pushButton_11->setGeometry(QRect(70, 0, 171, 36));
        pushButton_11->setStyleSheet(QLatin1String("width:67px;\n"
"height:14px;\n"
"font-size:14px;\n"
"font-weight:400;\n"
"color:rgba(148, 148, 148,1);\n"
"opacity:0.35;\n"
"text-align: right"));
        widget_4 = new QWidget(set_page);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setGeometry(QRect(87, 478, 280, 36));
        widget_4->setStyleSheet(QLatin1String("width:280px;\n"
"height:36px;\n"
"background:rgba(48,48,51,1);\n"
"border-radius:4px;\n"
""));
        label_22 = new QLabel(widget_4);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(0, 0, 71, 31));
        label_22->setStyleSheet(QLatin1String("width:39px;\n"
"height:14px;\n"
"font-size:14px;\n"
"font-weight:400;\n"
"color:rgba(255,255,255,1);\n"
""));
        pushButton_16 = new QPushButton(widget_4);
        pushButton_16->setObjectName(QStringLiteral("pushButton_16"));
        pushButton_16->setGeometry(QRect(244, 0, 36, 36));
        pushButton_17 = new QPushButton(widget_4);
        pushButton_17->setObjectName(QStringLiteral("pushButton_17"));
        pushButton_17->setGeometry(QRect(70, 0, 171, 36));
        pushButton_17->setStyleSheet(QLatin1String("width:67px;\n"
"height:14px;\n"
"font-size:14px;\n"
"font-weight:400;\n"
"color:rgba(148, 148, 148,1);\n"
"opacity:0.35;\n"
"text-align: right"));
        label_17 = new QLabel(set_page);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(90, 200, 31, 22));
        pushButton_12 = new QPushButton(Clock);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));
        pushButton_12->setGeometry(QRect(352, 4, 30, 30));
        set_page->raise();
        stackedWidget_3->raise();
        stackedWidget->raise();
        pushButton_12->raise();
        pushButton_4->raise();
        pushButton_5->raise();

        retranslateUi(Clock);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Clock);
    } // setupUi

    void retranslateUi(QWidget *Clock)
    {
        Clock->setWindowTitle(QApplication::translate("Clock", "Clock", 0));
        actionOn->setText(QApplication::translate("Clock", "On", 0));
        count_stat->setText(QApplication::translate("Clock", "start", 0));
        label_8->setText(QApplication::translate("Clock", "00:00:00", 0));
        min_5btn->setText(QApplication::translate("Clock", "5min", 0));
        min_10btn->setText(QApplication::translate("Clock", "15min", 0));
        min_20btn->setText(QApplication::translate("Clock", "25min", 0));
        min_30btn->setText(QApplication::translate("Clock", "30min", 0));
        min_60btn->setText(QApplication::translate("Clock", "60min", 0));
        label_9->setText(QApplication::translate("Clock", "00:00:00", 0));
        count_push->setText(QApplication::translate("Clock", "suspend", 0));
        label_23->setText(QApplication::translate("Clock", "  Remind", 0));
        pushButton_19->setText(QString());
        pushButton_20->setText(QString());
        label_10->setText(QString());
        label_11->setText(QApplication::translate("Clock", "PM", 0));
        label_6->setText(QApplication::translate("Clock", "00:00:00", 0));
        addAlarmBtn->setText(QApplication::translate("Clock", "add alarm", 0));
        label_7->setText(QApplication::translate("Clock", "Remaining time", 0));
        label_15->setText(QString());
        pushButton_Start->setText(QApplication::translate("Clock", "start", 0));
        label_5->setText(QApplication::translate("Clock", "00:00:00", 0));
        label_4->setText(QApplication::translate("Clock", "00:00:00", 0));
        pushButton_timeselect->setText(QApplication::translate("Clock", "reset", 0));
        pushButton_ring->setText(QApplication::translate("Clock", "count", 0));
        pushButton_5->setText(QString());
        pushButton_4->setText(QString());
        pushButton_3->setText(QString());
        label->setText(QApplication::translate("Clock", "Count down", 0));
        label_2->setText(QApplication::translate("Clock", "Alarm", 0));
        label_3->setText(QApplication::translate("Clock", "Stopwatch", 0));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        pushButton_8->setText(QApplication::translate("Clock", "deletealarm", 0));
        pushButton_9->setText(QApplication::translate("Clock", "Preservation", 0));
        label_12->setText(QApplication::translate("Clock", "12hour43minThe bell rings", 0));
        set_alarm_cancelbtn->setText(QApplication::translate("Clock", "cancel", 0));
        set_alarm_savebtn->setText(QApplication::translate("Clock", "Preservation", 0));
        label_13->setText(QApplication::translate("Clock", "New alarm", 0));
        label_14->setText(QApplication::translate("Clock", "  Name", 0));
        label_18->setText(QApplication::translate("Clock", "  repeat", 0));
        pushButton_10->setText(QString());
        pushButton_6->setText(QString());
        label_19->setText(QApplication::translate("Clock", "  Remind", 0));
        pushButton_7->setText(QString());
        pushButton_11->setText(QString());
        label_22->setText(QApplication::translate("Clock", "  ring time", 0));
        pushButton_16->setText(QString());
        pushButton_17->setText(QString());
        label_17->setText(QString());
        pushButton_12->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Clock: public Ui_Clock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLOCK_H
