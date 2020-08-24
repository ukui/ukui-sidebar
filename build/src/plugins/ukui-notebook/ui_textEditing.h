/********************************************************************************
** Form generated from reading UI file 'textEditing.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTEDITING_H
#define UI_TEXTEDITING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Text_editing
{
public:

    void setupUi(QWidget *Text_editing)
    {
        if (Text_editing->objectName().isEmpty())
            Text_editing->setObjectName(QStringLiteral("Text_editing"));
        Text_editing->resize(250, 40);

        retranslateUi(Text_editing);

        QMetaObject::connectSlotsByName(Text_editing);
    } // setupUi

    void retranslateUi(QWidget *Text_editing)
    {
        Text_editing->setWindowTitle(QApplication::translate("Text_editing", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class Text_editing: public Ui_Text_editing {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTEDITING_H
