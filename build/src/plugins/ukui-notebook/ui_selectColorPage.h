/********************************************************************************
** Form generated from reading UI file 'selectColorPage.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTCOLORPAGE_H
#define UI_SELECTCOLORPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_select_color_page
{
public:

    void setupUi(QWidget *select_color_page)
    {
        if (select_color_page->objectName().isEmpty())
            select_color_page->setObjectName(QStringLiteral("select_color_page"));
        select_color_page->resize(250, 40);

        retranslateUi(select_color_page);

        QMetaObject::connectSlotsByName(select_color_page);
    } // setupUi

    void retranslateUi(QWidget *select_color_page)
    {
        select_color_page->setWindowTitle(QApplication::translate("select_color_page", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class select_color_page: public Ui_select_color_page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTCOLORPAGE_H
