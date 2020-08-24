/********************************************************************************
** Form generated from reading UI file 'closeOrHide.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLOSEORHIDE_H
#define UI_CLOSEORHIDE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
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
            close_or_hide->setObjectName(QStringLiteral("close_or_hide"));
        close_or_hide->resize(322, 162);
        close_or_hide->setStyleSheet(QStringLiteral("background-color: rgb(130, 130, 130);"));
        widget = new QWidget(close_or_hide);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 320, 160));
        widget->setStyleSheet(QLatin1String("background-color: rgba(14,19,22,1);\n"
"border-radius: 6px;"));
        closebtn = new QPushButton(widget);
        closebtn->setObjectName(QStringLiteral("closebtn"));
        closebtn->setGeometry(QRect(290, 0, 30, 30));
        closebtn->setStyleSheet(QLatin1String("border-image: url(:/image/close_light.png);\n"
""));
        surebtn = new QPushButton(widget);
        surebtn->setObjectName(QStringLiteral("surebtn"));
        surebtn->setGeometry(QRect(98, 110, 71, 32));
        surebtn->setStyleSheet(QLatin1String("QPushButton{color: rgb(255, 255, 255);\n"
"background-color: rgba(39,207,129,0.9);\n"
" border-radius:4px;\n"
"font: 11pt ;}\n"
"QPushButton:hover{background-color: rgb(27, 143, 89);}\n"
""));
        cancelbtn = new QPushButton(widget);
        cancelbtn->setObjectName(QStringLiteral("cancelbtn"));
        cancelbtn->setGeometry(QRect(220, 110, 71, 32));
        cancelbtn->setStyleSheet(QLatin1String("QPushButton{\n"
"font: 11pt ;\n"
"color: rgb(255, 255, 255);\n"
"background:rgba(46,46,46,1);\n"
"border-radius:4px;}\n"
"QPushButton:hover{background:rgba(143, 97, 47, 0.1)}"));
        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 30, 51, 51));
        label_6->setStyleSheet(QStringLiteral("border-image: url(:/image/aptdaemon-error.png);"));
        radioButton = new QRadioButton(widget);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(120, 17, 161, 31));
        radioButton->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font: 25 14pt ;"));
        radioButton_2 = new QRadioButton(widget);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(120, 60, 161, 28));
        radioButton_2->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font: 25 14pt ;"));

        retranslateUi(close_or_hide);

        QMetaObject::connectSlotsByName(close_or_hide);
    } // setupUi

    void retranslateUi(QDialog *close_or_hide)
    {
        close_or_hide->setWindowTitle(QApplication::translate("close_or_hide", "Dialog", 0));
        closebtn->setText(QString());
        surebtn->setText(QApplication::translate("close_or_hide", "sure", 0));
        cancelbtn->setText(QApplication::translate("close_or_hide", "cancel", 0));
        label_6->setText(QString());
        radioButton->setText(QApplication::translate("close_or_hide", "backstage", 0));
        radioButton_2->setText(QApplication::translate("close_or_hide", " Exit program ", 0));
    } // retranslateUi

};

namespace Ui {
    class close_or_hide: public Ui_close_or_hide {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLOSEORHIDE_H
