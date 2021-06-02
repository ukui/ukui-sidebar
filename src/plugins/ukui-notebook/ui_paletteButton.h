/********************************************************************************
** Form generated from reading UI file 'paletteButton.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PALETTEBUTTON_H
#define UI_PALETTEBUTTON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_paletteButton
{
public:
    QLabel *label;

    void setupUi(QWidget *paletteButton)
    {
        if (paletteButton->objectName().isEmpty())
            paletteButton->setObjectName(QString::fromUtf8("paletteButton"));
        paletteButton->resize(27, 23);
        label = new QLabel(paletteButton);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(6, 6, 15, 15));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 21, 5);\n"
"border-radius:3px;"));

        retranslateUi(paletteButton);

        QMetaObject::connectSlotsByName(paletteButton);
    } // setupUi

    void retranslateUi(QWidget *paletteButton)
    {
        paletteButton->setWindowTitle(QApplication::translate("paletteButton", "Form", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class paletteButton: public Ui_paletteButton {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PALETTEBUTTON_H
