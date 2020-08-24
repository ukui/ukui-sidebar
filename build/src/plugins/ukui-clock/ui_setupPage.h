/********************************************************************************
** Form generated from reading UI file 'setupPage.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUPPAGE_H
#define UI_SETUPPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_setuppage
{
public:
    QWidget *widget;
    QLabel *label;
    QPushButton *pushButton;
    QWidget *widget_2;
    QLabel *label_18;
    QPushButton *pushButton_10;
    QPushButton *pushButton_6;
    QWidget *widget_3;
    QLabel *label_19;
    QPushButton *pushButton_11;
    QPushButton *pushButton_7;
    QWidget *widget_4;
    QLabel *label_20;
    QPushButton *pushButton_12;
    QPushButton *pushButton_8;
    QWidget *widget_5;
    QLabel *label_21;
    QPushButton *pushButton_13;
    QPushButton *pushButton_9;
    QWidget *widget_6;
    QLabel *label_22;
    QPushButton *pushButton_14;
    QPushButton *pushButton_15;
    QLabel *label_2;
    QPushButton *pushButton_2;
    QLabel *label_3;
    QSlider *horizontalSlider;
    QLabel *label_4;

    void setupUi(QWidget *setuppage)
    {
        if (setuppage->objectName().isEmpty())
            setuppage->setObjectName(QStringLiteral("setuppage"));
        setuppage->resize(380, 450);
        setuppage->setStyleSheet(QLatin1String("\n"
"border-radius:4px;\n"
""));
        widget = new QWidget(setuppage);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 380, 450));
        widget->setStyleSheet(QLatin1String("background-color: rgba(35,35,37, 1);\n"
"border:1px solid rgba(47,47,51,1);\n"
"border-radius:4px;\n"
"\n"
""));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(53, 58, 63, 22));
        label->setStyleSheet(QLatin1String("width:56px;\n"
"height:14px;\n"
"font-size:14px;\n"
"border:0px solid rgba();\n"
"font-weight:400;\n"
"color:rgba(255,255,255,1)"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(275, 53, 50, 24));
        pushButton->setStyleSheet(QLatin1String("width:50px;\n"
"border-image: url(:/alarm_on.png);\n"
"height:24px;\n"
"background:linear-gradient(0deg,rgba(39,207,129,1) 0%,rgba(39,207,129,0.9) 100%);\n"
"border-radius:6px;\n"
"border:0px solid rgba();"));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(45, 97, 280, 36));
        widget_2->setStyleSheet(QLatin1String("width:280px;\n"
"height:36px;\n"
"background:rgba(48,48,51,1);\n"
"border-radius:4px;\n"
"border:0px solid rgba();"));
        label_18 = new QLabel(widget_2);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(0, 0, 61, 31));
        label_18->setStyleSheet(QLatin1String("width:39px;\n"
"height:14px;\n"
"font-size:14px;\n"
"\n"
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
"font-family:Source Han Sans CN;\n"
"font-weight:400;\n"
"color:rgba(148, 148, 148,1);\n"
"opacity:0.35;\n"
"text-align: right"));
        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setGeometry(QRect(45, 147, 280, 36));
        widget_3->setStyleSheet(QLatin1String("width:280px;\n"
"height:36px;\n"
"background:rgba(48,48,51,1);\n"
"border-radius:4px;\n"
"border:0px solid rgba();"));
        label_19 = new QLabel(widget_3);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(0, 0, 71, 31));
        label_19->setStyleSheet(QLatin1String("width:39px;\n"
"height:14px;\n"
"font-size:14px;\n"
"\n"
"font-weight:400;\n"
"color:rgba(255,255,255,1);\n"
""));
        pushButton_11 = new QPushButton(widget_3);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));
        pushButton_11->setGeometry(QRect(244, 0, 36, 36));
        pushButton_7 = new QPushButton(widget_3);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(70, 0, 171, 36));
        pushButton_7->setStyleSheet(QLatin1String("width:67px;\n"
"height:14px;\n"
"font-size:14px;\n"
"font-family:Source Han Sans CN;\n"
"font-weight:400;\n"
"color:rgba(148, 148, 148,1);\n"
"opacity:0.35;\n"
"text-align: right"));
        widget_4 = new QWidget(widget);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setGeometry(QRect(45, 197, 280, 36));
        widget_4->setStyleSheet(QLatin1String("width:280px;\n"
"height:36px;\n"
"background:rgba(48,48,51,1);\n"
"border-radius:4px;\n"
"border:0px solid rgba();"));
        label_20 = new QLabel(widget_4);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(0, 0, 62, 31));
        label_20->setStyleSheet(QLatin1String("width:39px;\n"
"height:14px;\n"
"font-size:14px;\n"
"\n"
"font-weight:400;\n"
"color:rgba(255,255,255,1);\n"
""));
        pushButton_12 = new QPushButton(widget_4);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));
        pushButton_12->setGeometry(QRect(244, 0, 36, 36));
        pushButton_8 = new QPushButton(widget_4);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(70, 0, 171, 36));
        pushButton_8->setStyleSheet(QLatin1String("width:67px;\n"
"height:14px;\n"
"font-size:14px;\n"
"font-family:Source Han Sans CN;\n"
"font-weight:400;\n"
"color:rgba(148, 148, 148,1);\n"
"opacity:0.35;\n"
"text-align: right"));
        widget_5 = new QWidget(widget);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setGeometry(QRect(45, 247, 280, 36));
        widget_5->setStyleSheet(QLatin1String("width:280px;\n"
"height:36px;\n"
"background:rgba(48,48,51,1);\n"
"border-radius:4px;\n"
"border:0px solid rgba();"));
        label_21 = new QLabel(widget_5);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(0, 0, 61, 31));
        label_21->setStyleSheet(QLatin1String("width:39px;\n"
"height:14px;\n"
"font-size:14px;\n"
"\n"
"font-weight:400;\n"
"color:rgba(255,255,255,1);\n"
""));
        pushButton_13 = new QPushButton(widget_5);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));
        pushButton_13->setGeometry(QRect(244, 0, 36, 36));
        pushButton_9 = new QPushButton(widget_5);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setGeometry(QRect(70, 0, 171, 36));
        pushButton_9->setStyleSheet(QLatin1String("width:67px;\n"
"height:14px;\n"
"font-size:14px;\n"
"font-family:Source Han Sans CN;\n"
"font-weight:400;\n"
"color:rgba(148, 148, 148,1);\n"
"opacity:0.35;\n"
"text-align: right"));
        widget_6 = new QWidget(widget);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setGeometry(QRect(45, 297, 280, 36));
        widget_6->setStyleSheet(QLatin1String("width:280px;\n"
"height:36px;\n"
"background:rgba(48,48,51,1);\n"
"border-radius:4px;\n"
"border:0px solid rgba();"));
        label_22 = new QLabel(widget_6);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(0, 0, 71, 31));
        label_22->setStyleSheet(QLatin1String("width:39px;\n"
"height:14px;\n"
"font-size:14px;\n"
"\n"
"font-weight:400;\n"
"color:rgba(255,255,255,1);\n"
""));
        pushButton_14 = new QPushButton(widget_6);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));
        pushButton_14->setGeometry(QRect(244, 0, 36, 36));
        pushButton_15 = new QPushButton(widget_6);
        pushButton_15->setObjectName(QStringLiteral("pushButton_15"));
        pushButton_15->setGeometry(QRect(70, 0, 171, 36));
        pushButton_15->setStyleSheet(QLatin1String("width:67px;\n"
"height:14px;\n"
"font-size:14px;\n"
"font-family:Source Han Sans CN;\n"
"font-weight:400;\n"
"color:rgba(148, 148, 148,1);\n"
"opacity:0.35;\n"
"text-align: right"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(45, 358, 51, 20));
        label_2->setStyleSheet(QLatin1String("width:28px;\n"
"height:14px;\n"
"font-size:14px;\n"
"border:0px solid rgba();\n"
"font-weight:400;\n"
"color:rgba(255,255,255,1)"));
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(275, 353, 50, 24));
        pushButton_2->setStyleSheet(QLatin1String("width:50px;\n"
"border-image: url(:/alarm_off.png);\n"
"height:24px;\n"
"background:linear-gradient(0deg,rgba(39,207,129,1) 0%,rgba(39,207,129,0.9) 100%);\n"
"border-radius:6px;\n"
"border:0px solid rgba();"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(53, 408, 63, 22));
        label_3->setStyleSheet(QLatin1String("font-size:14px;\n"
"border:0px solid rgba();\n"
"font-weight:300;\n"
"color:rgba(255,255,255,1)"));
        horizontalSlider = new QSlider(widget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(128, 406, 197, 24));
        horizontalSlider->setStyleSheet(QLatin1String("background-color: rgb();\n"
"border-left-color: rgb(85, 255, 0);\n"
"border-bottom-color: rgb(85, 170, 0);\n"
"border-radius:50%;\n"
"border:0px solid rgba();\n"
"\n"
"\n"
""));
        horizontalSlider->setOrientation(Qt::Horizontal);
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(40, 25, 300, 50));
        label_4->setStyleSheet(QLatin1String("font: 57 22pt \"Noto Sans Devanagari Md\";\n"
"color: rgba(39,207,129,0.9);\n"
"border:0px solid rgba();"));

        retranslateUi(setuppage);

        QMetaObject::connectSlotsByName(setuppage);
    } // setupUi

    void retranslateUi(QWidget *setuppage)
    {
        setuppage->setWindowTitle(QApplication::translate("setuppage", "Form", 0));
        label->setText(QApplication::translate("setuppage", "Boot up", 0));
        pushButton->setText(QString());
        label_18->setText(QApplication::translate("setuppage", "  work", 0));
        pushButton_10->setText(QString());
        pushButton_6->setText(QString());
        label_19->setText(QApplication::translate("setuppage", "  Time", 0));
        pushButton_11->setText(QString());
        pushButton_7->setText(QString());
        label_20->setText(QApplication::translate("setuppage", "  Pop-up", 0));
        pushButton_12->setText(QString());
        pushButton_8->setText(QString());
        label_21->setText(QApplication::translate("setuppage", "  duration", 0));
        pushButton_13->setText(QString());
        pushButton_9->setText(QString());
        label_22->setText(QApplication::translate("setuppage", "  ringtone", 0));
        pushButton_14->setText(QString());
        pushButton_15->setText(QString());
        label_2->setText(QApplication::translate("setuppage", "  Mute", 0));
        pushButton_2->setText(QString());
        label_3->setText(QApplication::translate("setuppage", "volume", 0));
        label_4->setText(QApplication::translate("setuppage", "setting", 0));
    } // retranslateUi

};

namespace Ui {
    class setuppage: public Ui_setuppage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUPPAGE_H
