/********************************************************************************
** Form generated from reading UI file 'deleteMsg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELETEMSG_H
#define UI_DELETEMSG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
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
            delete_msg->setObjectName(QString::fromUtf8("delete_msg"));
        delete_msg->resize(322, 162);
        delete_msg->setStyleSheet(QString::fromUtf8(""));
        widget = new QWidget(delete_msg);
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
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(90, 30, 221, 51));
        label_5->setStyleSheet(QString::fromUtf8("font:  15pt;"));
        label_6 = new QLabel(widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 30, 51, 51));
        label_6->setStyleSheet(QString::fromUtf8("border-image: url(:/image/aptdaemon-error.png);"));

        retranslateUi(delete_msg);

        QMetaObject::connectSlotsByName(delete_msg);
    } // setupUi

    void retranslateUi(QDialog *delete_msg)
    {
        delete_msg->setWindowTitle(QApplication::translate("delete_msg", "Dialog", nullptr));
        closebtn->setText(QString());
        surebtn->setText(QApplication::translate("delete_msg", "sure", nullptr));
        cancelbtn->setText(QApplication::translate("delete_msg", "cancel", nullptr));
        label_5->setText(QApplication::translate("delete_msg", "are you sure ?", nullptr));
        label_6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class delete_msg: public Ui_delete_msg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELETEMSG_H
