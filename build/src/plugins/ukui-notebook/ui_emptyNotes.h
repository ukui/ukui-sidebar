/********************************************************************************
** Form generated from reading UI file 'emptyNotes.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPTYNOTES_H
#define UI_EMPTYNOTES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_emptyNotes
{
public:
    QWidget *widget;
    QLabel *label;
    QCheckBox *checkBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *emptyNotes)
    {
        if (emptyNotes->objectName().isEmpty())
            emptyNotes->setObjectName(QString::fromUtf8("emptyNotes"));
        emptyNotes->resize(400, 218);
        widget = new QWidget(emptyNotes);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 400, 218));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(95, 62, 190, 22));
        label->setStyleSheet(QString::fromUtf8("font-size:20px;\n"
"\n"
"font-weight:400;\n"
"color:rgba(40,40,40,1);\n"
"line-height:34px;\n"
"opacity:0.97;\n"
""));
        checkBox = new QCheckBox(widget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(95, 110, 151, 28));
        checkBox->setStyleSheet(QString::fromUtf8("font-size:14px;\n"
"font-weight:400;\n"
"color:rgba(102,102,102,1);\n"
"line-height:40px;\n"
"opacity:0.91;"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(124, 166, 120, 34));
        pushButton->setStyleSheet(QString::fromUtf8("color:rgba(102,102,102,1);\n"
"line-height:24px;"));
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(260, 166, 120, 34));
        pushButton_2->setStyleSheet(QString::fromUtf8("color:rgba(102,102,102,1);\n"
"line-height:24px;"));

        retranslateUi(emptyNotes);

        QMetaObject::connectSlotsByName(emptyNotes);
    } // setupUi

    void retranslateUi(QDialog *emptyNotes)
    {
        emptyNotes->setWindowTitle(QApplication::translate("emptyNotes", "Dialog", nullptr));
        label->setText(QApplication::translate("emptyNotes", "\347\241\256\345\256\232\350\246\201\346\270\205\347\251\272\344\276\277\347\255\276\346\234\254\345\220\227?", nullptr));
        checkBox->setText(QApplication::translate("emptyNotes", "\344\270\215\345\206\215\350\257\242\351\227\256", nullptr));
        pushButton->setText(QApplication::translate("emptyNotes", "\345\217\226\346\266\210", nullptr));
        pushButton_2->setText(QApplication::translate("emptyNotes", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class emptyNotes: public Ui_emptyNotes {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPTYNOTES_H
