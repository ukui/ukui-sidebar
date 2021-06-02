/********************************************************************************
** Form generated from reading UI file 'editPage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITPAGE_H
#define UI_EDITPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Edit_page
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *paletteBtn;
    QPushButton *formatBtn;

    void setupUi(QWidget *Edit_page)
    {
        if (Edit_page->objectName().isEmpty())
            Edit_page->setObjectName(QString::fromUtf8("Edit_page"));
        Edit_page->resize(250, 224);
        Edit_page->setMinimumSize(QSize(250, 224));
        Edit_page->setMaximumSize(QSize(250, 224));
        Edit_page->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(Edit_page);
        verticalLayout_2->setSpacing(4);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));

        verticalLayout_2->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(12, -1, 1, 10);
        textEdit = new QTextEdit(Edit_page);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        QFont font;
        font.setPointSize(14);
        textEdit->setFont(font);
        textEdit->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(textEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, 9, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        paletteBtn = new QPushButton(Edit_page);
        paletteBtn->setObjectName(QString::fromUtf8("paletteBtn"));
        paletteBtn->setMinimumSize(QSize(30, 30));
        paletteBtn->setMaximumSize(QSize(30, 30));
        paletteBtn->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(paletteBtn);

        formatBtn = new QPushButton(Edit_page);
        formatBtn->setObjectName(QString::fromUtf8("formatBtn"));
        formatBtn->setMinimumSize(QSize(30, 30));
        formatBtn->setMaximumSize(QSize(30, 30));
        formatBtn->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(formatBtn);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(Edit_page);

        QMetaObject::connectSlotsByName(Edit_page);
    } // setupUi

    void retranslateUi(QWidget *Edit_page)
    {
        Edit_page->setWindowTitle(QApplication::translate("Edit_page", "Form", nullptr));
        paletteBtn->setText(QString());
        formatBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Edit_page: public Ui_Edit_page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITPAGE_H
