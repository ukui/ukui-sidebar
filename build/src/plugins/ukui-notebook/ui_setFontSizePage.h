/********************************************************************************
** Form generated from reading UI file 'setFontSizePage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETFONTSIZEPAGE_H
#define UI_SETFONTSIZEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetFontSize
{
public:
    QListWidget *listWidget;

    void setupUi(QWidget *SetFontSize)
    {
        if (SetFontSize->objectName().isEmpty())
            SetFontSize->setObjectName(QString::fromUtf8("SetFontSize"));
        SetFontSize->resize(30, 200);
        listWidget = new QListWidget(SetFontSize);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 30, 200));
        listWidget->setStyleSheet(QString::fromUtf8("selection-background-color: rgb(85, 255, 127);\n"
""));

        retranslateUi(SetFontSize);

        QMetaObject::connectSlotsByName(SetFontSize);
    } // setupUi

    void retranslateUi(QWidget *SetFontSize)
    {
        SetFontSize->setWindowTitle(QApplication::translate("SetFontSize", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetFontSize: public Ui_SetFontSize {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETFONTSIZEPAGE_H
