/********************************************************************************
** Form generated from reading UI file 'fontButton.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FONTBUTTON_H
#define UI_FONTBUTTON_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fontButton
{
public:
    QLabel *label;

    void setupUi(QWidget *fontButton)
    {
        if (fontButton->objectName().isEmpty())
            fontButton->setObjectName(QStringLiteral("fontButton"));
        fontButton->resize(30, 23);
        fontButton->setStyleSheet(QStringLiteral(""));
        label = new QLabel(fontButton);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 27, 23));

        retranslateUi(fontButton);

        QMetaObject::connectSlotsByName(fontButton);
    } // setupUi

    void retranslateUi(QWidget *fontButton)
    {
        fontButton->setWindowTitle(QApplication::translate("fontButton", "Form", 0));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class fontButton: public Ui_fontButton {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FONTBUTTON_H
