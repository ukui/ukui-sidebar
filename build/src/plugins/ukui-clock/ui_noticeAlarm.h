/********************************************************************************
** Form generated from reading UI file 'noticeAlarm.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTICEALARM_H
#define UI_NOTICEALARM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Natice_alarm
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QWidget *widget;
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *Natice_alarm)
    {
        if (Natice_alarm->objectName().isEmpty())
            Natice_alarm->setObjectName(QStringLiteral("Natice_alarm"));
        Natice_alarm->resize(486, 286);
        verticalLayout = new QVBoxLayout(Natice_alarm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        widget = new QWidget(Natice_alarm);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(454, 254));
        widget->setMaximumSize(QSize(454, 254));
        widget->setStyleSheet(QLatin1String("width:454px;\n"
"height:218px;\n"
"background:rgba(14,19,22,1);\n"
"opacity:0.95;\n"
"border-radius: 6px;\n"
""));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(424, 0, 30, 30));
        pushButton->setStyleSheet(QStringLiteral("border-image: url(:/image/1x/close_light.png);"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(177, 10, 100, 23));
        label->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 64, 454, 31));
        label_2->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font: 25 14pt  \"Noto Sans Devanagari Md\";"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(0, 94, 454, 51));
        label_3->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font: 28pt \"Noto Sans Coptic\";"));
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(97, 169, 100, 32));
        pushButton_2->setStyleSheet(QLatin1String("QPushButton{\n"
"font: 11pt ;\n"
"color: rgb(255, 255, 255);\n"
"background:rgba(46,46,46,1);\n"
"border-radius:4px;}\n"
"QPushButton:hover{background:rgba(143, 97, 47, 0.1)}"));
        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(257, 169, 100, 32));
        pushButton_3->setStyleSheet(QLatin1String("QPushButton{color: rgb(255, 255, 255);\n"
"background-color: rgba(39,207,129,0.9);\n"
" border-radius:4px;\n"
"font: 11pt ;}\n"
"QPushButton:hover{background-color: rgb(27, 143, 89);}\n"
""));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(0, 221, 454, 23));
        label_4->setMinimumSize(QSize(454, 0));
        label_4->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(widget);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        retranslateUi(Natice_alarm);

        QMetaObject::connectSlotsByName(Natice_alarm);
    } // setupUi

    void retranslateUi(QWidget *Natice_alarm)
    {
        Natice_alarm->setWindowTitle(QApplication::translate("Natice_alarm", "Form", 0));
        pushButton->setText(QString());
        label->setText(QApplication::translate("Natice_alarm", "Alarm clock", 0));
        label_2->setText(QApplication::translate("Natice_alarm", "\345\267\245\344\275\234\344\274\232\350\256\256", 0));
        label_3->setText(QApplication::translate("Natice_alarm", "10 : 45", 0));
        pushButton_2->setText(QApplication::translate("Natice_alarm", "Remind later", 0));
        pushButton_3->setText(QApplication::translate("Natice_alarm", "close", 0));
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Natice_alarm: public Ui_Natice_alarm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTICEALARM_H
