/********************************************************************************
** Form generated from reading UI file 'closeOrHide.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLOSEORHIDE_H
#define UI_CLOSEORHIDE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_close_or_hide
{
public:
    QWidget *widget;
    QPushButton *closebtn;
    QPushButton *surebtn;
    QPushButton *cancelbtn;
    QLabel *label_6;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;

    void setupUi(QDialog *close_or_hide)
    {
        if (close_or_hide->objectName().isEmpty())
            close_or_hide->setObjectName(QString::fromUtf8("close_or_hide"));
        close_or_hide->resize(322, 162);
        close_or_hide->setStyleSheet(QString::fromUtf8(""));
        widget = new QWidget(close_or_hide);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 320, 160));
        widget->setStyleSheet(QString::fromUtf8(""));
        closebtn = new QPushButton(widget);
        closebtn->setObjectName(QString::fromUtf8("closebtn"));
        closebtn->setGeometry(QRect(281, 10, 30, 30));
        closebtn->setStyleSheet(QString::fromUtf8(""));
        surebtn = new QPushButton(widget);
        surebtn->setObjectName(QString::fromUtf8("surebtn"));
        surebtn->setGeometry(QRect(98, 110, 71, 32));
        surebtn->setStyleSheet(QString::fromUtf8(""));
        cancelbtn = new QPushButton(widget);
        cancelbtn->setObjectName(QString::fromUtf8("cancelbtn"));
        cancelbtn->setGeometry(QRect(220, 110, 71, 32));
        cancelbtn->setStyleSheet(QString::fromUtf8(""));
        label_6 = new QLabel(widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 30, 51, 51));
        label_6->setStyleSheet(QString::fromUtf8("border-image: url(:/image/aptdaemon-error.png);"));
        radioButton = new QRadioButton(widget);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(120, 17, 161, 31));
        radioButton->setStyleSheet(QString::fromUtf8("font:  14pt ;"));
        radioButton_2 = new QRadioButton(widget);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(120, 60, 161, 28));
        radioButton_2->setStyleSheet(QString::fromUtf8("font: 14pt ;"));

        retranslateUi(close_or_hide);

        QMetaObject::connectSlotsByName(close_or_hide);
    } // setupUi

    void retranslateUi(QDialog *close_or_hide)
    {
        close_or_hide->setWindowTitle(QApplication::translate("close_or_hide", "Dialog", nullptr));
        closebtn->setText(QString());
        surebtn->setText(QApplication::translate("close_or_hide", "sure", nullptr));
        cancelbtn->setText(QApplication::translate("close_or_hide", "cancel", nullptr));
        label_6->setText(QString());
        radioButton->setText(QApplication::translate("close_or_hide", " backstage", nullptr));
        radioButton_2->setText(QApplication::translate("close_or_hide", " Exit program ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class close_or_hide: public Ui_close_or_hide {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLOSEORHIDE_H
