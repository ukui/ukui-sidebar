/********************************************************************************
** Form generated from reading UI file 'deleteMsg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELETEMSG_H
#define UI_DELETEMSG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_delete_msg
{
public:
    QWidget *widget;
    QPushButton *closebtn;
    QPushButton *surebtn;
    QPushButton *cancelbtn;
    QLabel *label_5;
    QLabel *label_6;

    void setupUi(QDialog *delete_msg)
    {
        if (delete_msg->objectName().isEmpty())
            delete_msg->setObjectName(QStringLiteral("delete_msg"));
        delete_msg->resize(322, 162);
        delete_msg->setStyleSheet(QStringLiteral("background-color: rgb(130, 130, 130);"));
        widget = new QWidget(delete_msg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 320, 160));
        widget->setStyleSheet(QLatin1String("background-color: rgba(14,19,22,1);\n"
"border-radius: 6px;"));
        closebtn = new QPushButton(widget);
        closebtn->setObjectName(QStringLiteral("closebtn"));
        closebtn->setGeometry(QRect(290, 0, 30, 30));
        closebtn->setStyleSheet(QStringLiteral("border-image: url(:/image/close_light.png);"));
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
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(90, 30, 221, 51));
        label_5->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font: 25 15pt \"Noto Sans CJK SC\";"));
        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 30, 51, 51));
        label_6->setStyleSheet(QStringLiteral("border-image: url(:/image/aptdaemon-error.png);"));

        retranslateUi(delete_msg);

        QMetaObject::connectSlotsByName(delete_msg);
    } // setupUi

    void retranslateUi(QDialog *delete_msg)
    {
        delete_msg->setWindowTitle(QApplication::translate("delete_msg", "Dialog", 0));
        closebtn->setText(QString());
        surebtn->setText(QApplication::translate("delete_msg", "sure", 0));
        cancelbtn->setText(QApplication::translate("delete_msg", "cancel", 0));
        label_5->setText(QApplication::translate("delete_msg", "are you sure ?", 0));
        label_6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class delete_msg: public Ui_delete_msg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELETEMSG_H
