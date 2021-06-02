/********************************************************************************
** Form generated from reading UI file 'setFontColorPage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETFONTCOLORPAGE_H
#define UI_SETFONTCOLORPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetFontColor
{
public:
    QListWidget *listWidget;

    void setupUi(QWidget *SetFontColor)
    {
        if (SetFontColor->objectName().isEmpty())
            SetFontColor->setObjectName(QString::fromUtf8("SetFontColor"));
        SetFontColor->resize(30, 200);
        listWidget = new QListWidget(SetFontColor);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 30, 200));
        listWidget->setStyleSheet(QString::fromUtf8(""));

        retranslateUi(SetFontColor);

        QMetaObject::connectSlotsByName(SetFontColor);
    } // setupUi

    void retranslateUi(QWidget *SetFontColor)
    {
        SetFontColor->setWindowTitle(QApplication::translate("SetFontColor", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetFontColor: public Ui_SetFontColor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETFONTCOLORPAGE_H
