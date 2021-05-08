/********************************************************************************
** Form generated from reading UI file 'noticeAlarm.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTICEALARM_H
#define UI_NOTICEALARM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
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
    QLabel *titleIcon;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *Natice_alarm)
    {
        if (Natice_alarm->objectName().isEmpty())
            Natice_alarm->setObjectName(QString::fromUtf8("Natice_alarm"));
        Natice_alarm->resize(486, 286);
        verticalLayout = new QVBoxLayout(Natice_alarm);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        widget = new QWidget(Natice_alarm);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(454, 254));
        widget->setMaximumSize(QSize(454, 254));
        widget->setStyleSheet(QString::fromUtf8(""));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(414, 10, 30, 30));
        pushButton->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(44, 14, 100, 23));
        label->setStyleSheet(QString::fromUtf8(""));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 34, 454, 31));
        label_2->setStyleSheet(QString::fromUtf8("font:  14pt ;"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 64, 454, 51));
        label_3->setStyleSheet(QString::fromUtf8("font: 28pt;"));
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(97, 139, 100, 32));
        pushButton_2->setStyleSheet(QString::fromUtf8(""));
        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(257, 139, 100, 32));
        pushButton_3->setStyleSheet(QString::fromUtf8(""));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(0, 191, 454, 23));
        label_4->setMinimumSize(QSize(454, 0));
        label_4->setStyleSheet(QString::fromUtf8(""));
        titleIcon = new QLabel(widget);
        titleIcon->setObjectName(QString::fromUtf8("titleIcon"));
        titleIcon->setGeometry(QRect(14, 14, 24, 24));
        titleIcon->setMinimumSize(QSize(24, 24));
        titleIcon->setMaximumSize(QSize(24, 24));

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
        Natice_alarm->setWindowTitle(QApplication::translate("Natice_alarm", "Form", nullptr));
        pushButton->setText(QString());
        label->setText(QApplication::translate("Natice_alarm", "Alarm clock", nullptr));
        label_2->setText(QApplication::translate("Natice_alarm", "\345\267\245\344\275\234\344\274\232\350\256\256", nullptr));
        label_3->setText(QApplication::translate("Natice_alarm", "10 : 45", nullptr));
        pushButton_2->setText(QApplication::translate("Natice_alarm", "Remind later", nullptr));
        pushButton_3->setText(QApplication::translate("Natice_alarm", "close", nullptr));
        label_4->setText(QString());
        titleIcon->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Natice_alarm: public Ui_Natice_alarm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTICEALARM_H
