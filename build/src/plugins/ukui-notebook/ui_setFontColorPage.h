/********************************************************************************
** Form generated from reading UI file 'setFontColorPage.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETFONTCOLORPAGE_H
#define UI_SETFONTCOLORPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Set_font_color_page
{
public:
    QListWidget *listWidget;

    void setupUi(QWidget *Set_font_color_page)
    {
        if (Set_font_color_page->objectName().isEmpty())
            Set_font_color_page->setObjectName(QStringLiteral("Set_font_color_page"));
        Set_font_color_page->resize(30, 200);
        listWidget = new QListWidget(Set_font_color_page);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 30, 200));
        listWidget->setStyleSheet(QStringLiteral(""));

        retranslateUi(Set_font_color_page);

        QMetaObject::connectSlotsByName(Set_font_color_page);
    } // setupUi

    void retranslateUi(QWidget *Set_font_color_page)
    {
        Set_font_color_page->setWindowTitle(QApplication::translate("Set_font_color_page", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class Set_font_color_page: public Ui_Set_font_color_page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETFONTCOLORPAGE_H
