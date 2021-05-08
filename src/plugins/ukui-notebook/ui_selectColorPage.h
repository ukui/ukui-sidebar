/********************************************************************************
** Form generated from reading UI file 'selectColorPage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTCOLORPAGE_H
#define UI_SELECTCOLORPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectColor
{
public:

    void setupUi(QWidget *SelectColor)
    {
        if (SelectColor->objectName().isEmpty())
            SelectColor->setObjectName(QString::fromUtf8("SelectColor"));
        SelectColor->resize(250, 40);

        retranslateUi(SelectColor);

        QMetaObject::connectSlotsByName(SelectColor);
    } // setupUi

    void retranslateUi(QWidget *SelectColor)
    {
        SelectColor->setWindowTitle(QApplication::translate("SelectColor", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectColor: public Ui_SelectColor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTCOLORPAGE_H
