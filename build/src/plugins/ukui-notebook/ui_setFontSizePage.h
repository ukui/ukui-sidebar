/********************************************************************************
** Form generated from reading UI file 'setFontSizePage.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETFONTSIZEPAGE_H
#define UI_SETFONTSIZEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Set_font_size_page
{
public:
    QListWidget *listWidget;

    void setupUi(QWidget *Set_font_size_page)
    {
        if (Set_font_size_page->objectName().isEmpty())
            Set_font_size_page->setObjectName(QStringLiteral("Set_font_size_page"));
        Set_font_size_page->resize(30, 200);
        listWidget = new QListWidget(Set_font_size_page);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 30, 200));
        listWidget->setStyleSheet(QLatin1String("selection-background-color: rgb(85, 255, 127);\n"
""));

        retranslateUi(Set_font_size_page);

        QMetaObject::connectSlotsByName(Set_font_size_page);
    } // setupUi

    void retranslateUi(QWidget *Set_font_size_page)
    {
        Set_font_size_page->setWindowTitle(QApplication::translate("Set_font_size_page", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class Set_font_size_page: public Ui_Set_font_size_page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETFONTSIZEPAGE_H
