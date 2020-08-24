/********************************************************************************
** Form generated from reading UI file 'editPage.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITPAGE_H
#define UI_EDITPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Edit_page
{
public:
    QWidget *widget_2;
    QPushButton *color_btn;
    QPushButton *chang_btn;
    QTextEdit *textEdit;

    void setupUi(QWidget *Edit_page)
    {
        if (Edit_page->objectName().isEmpty())
            Edit_page->setObjectName(QStringLiteral("Edit_page"));
        Edit_page->resize(250, 224);
        Edit_page->setStyleSheet(QStringLiteral(""));
        widget_2 = new QWidget(Edit_page);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(0, 8, 250, 216));
        widget_2->setStyleSheet(QStringLiteral(""));
        color_btn = new QPushButton(widget_2);
        color_btn->setObjectName(QStringLiteral("color_btn"));
        color_btn->setGeometry(QRect(170, 180, 30, 30));
        color_btn->setStyleSheet(QStringLiteral(""));
        chang_btn = new QPushButton(widget_2);
        chang_btn->setObjectName(QStringLiteral("chang_btn"));
        chang_btn->setGeometry(QRect(210, 180, 30, 30));
        chang_btn->setStyleSheet(QStringLiteral(""));
        textEdit = new QTextEdit(widget_2);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(12, 12, 225, 154));
        QFont font;
        font.setPointSize(14);
        textEdit->setFont(font);
        textEdit->setStyleSheet(QStringLiteral(""));

        retranslateUi(Edit_page);

        QMetaObject::connectSlotsByName(Edit_page);
    } // setupUi

    void retranslateUi(QWidget *Edit_page)
    {
        Edit_page->setWindowTitle(QApplication::translate("Edit_page", "Form", 0));
        color_btn->setText(QString());
        chang_btn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Edit_page: public Ui_Edit_page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITPAGE_H
