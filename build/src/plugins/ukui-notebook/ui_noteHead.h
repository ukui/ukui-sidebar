/********************************************************************************
** Form generated from reading UI file 'noteHead.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTEHEAD_H
#define UI_NOTEHEAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_noteHead
{
public:

    void setupUi(QWidget *noteHead)
    {
        if (noteHead->objectName().isEmpty())
            noteHead->setObjectName(QString::fromUtf8("noteHead"));
        noteHead->resize(250, 16);

        retranslateUi(noteHead);

        QMetaObject::connectSlotsByName(noteHead);
    } // setupUi

    void retranslateUi(QWidget *noteHead)
    {
        noteHead->setWindowTitle(QApplication::translate("noteHead", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class noteHead: public Ui_noteHead {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTEHEAD_H
