/********************************************************************************
** Form generated from reading UI file 'textEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTEDITWIDGET_H
#define UI_TEXTEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TextEditWidget
{
public:
    QPushButton *boldBtn;
    QPushButton *orderedBtn;
    QPushButton *strikeOutBtn;
    QPushButton *unorderedBtn;
    QPushButton *fontSizeBtn;
    QPushButton *styleBtn;
    QPushButton *underlineBtn;
    QPushButton *fontColorBtn;
    QFrame *frame;
    QPushButton *italicBtn;

    void setupUi(QWidget *TextEditWidget)
    {
        if (TextEditWidget->objectName().isEmpty())
            TextEditWidget->setObjectName(QString::fromUtf8("TextEditWidget"));
        TextEditWidget->resize(250, 35);
        boldBtn = new QPushButton(TextEditWidget);
        boldBtn->setObjectName(QString::fromUtf8("boldBtn"));
        boldBtn->setGeometry(QRect(5, 6, 24, 24));
        boldBtn->setMinimumSize(QSize(24, 24));
        boldBtn->setMaximumSize(QSize(24, 24));
        boldBtn->setStyleSheet(QString::fromUtf8(""));
        orderedBtn = new QPushButton(TextEditWidget);
        orderedBtn->setObjectName(QString::fromUtf8("orderedBtn"));
        orderedBtn->setGeometry(QRect(145, 6, 24, 24));
        orderedBtn->setMinimumSize(QSize(24, 24));
        orderedBtn->setMaximumSize(QSize(24, 24));
        orderedBtn->setFocusPolicy(Qt::ClickFocus);
        orderedBtn->setStyleSheet(QString::fromUtf8(""));
        orderedBtn->setCheckable(true);
        orderedBtn->setChecked(false);
        orderedBtn->setAutoExclusive(false);
        strikeOutBtn = new QPushButton(TextEditWidget);
        strikeOutBtn->setObjectName(QString::fromUtf8("strikeOutBtn"));
        strikeOutBtn->setGeometry(QRect(80, 6, 24, 24));
        strikeOutBtn->setMinimumSize(QSize(24, 24));
        strikeOutBtn->setMaximumSize(QSize(24, 24));
        strikeOutBtn->setStyleSheet(QString::fromUtf8(""));
        strikeOutBtn->setCheckable(true);
        unorderedBtn = new QPushButton(TextEditWidget);
        unorderedBtn->setObjectName(QString::fromUtf8("unorderedBtn"));
        unorderedBtn->setGeometry(QRect(120, 6, 24, 24));
        unorderedBtn->setMinimumSize(QSize(24, 24));
        unorderedBtn->setMaximumSize(QSize(24, 24));
        unorderedBtn->setFocusPolicy(Qt::ClickFocus);
        unorderedBtn->setStyleSheet(QString::fromUtf8(""));
        unorderedBtn->setCheckable(true);
        unorderedBtn->setAutoExclusive(false);
        fontSizeBtn = new QPushButton(TextEditWidget);
        fontSizeBtn->setObjectName(QString::fromUtf8("fontSizeBtn"));
        fontSizeBtn->setGeometry(QRect(183, 5, 30, 25));
        fontSizeBtn->setFocusPolicy(Qt::NoFocus);
        fontSizeBtn->setStyleSheet(QString::fromUtf8(""));
        styleBtn = new QPushButton(TextEditWidget);
        styleBtn->setObjectName(QString::fromUtf8("styleBtn"));
        styleBtn->setGeometry(QRect(215, 5, 30, 25));
        styleBtn->setMinimumSize(QSize(30, 25));
        styleBtn->setMaximumSize(QSize(30, 25));
        styleBtn->setStyleSheet(QString::fromUtf8(""));
        underlineBtn = new QPushButton(TextEditWidget);
        underlineBtn->setObjectName(QString::fromUtf8("underlineBtn"));
        underlineBtn->setGeometry(QRect(55, 6, 24, 24));
        underlineBtn->setMinimumSize(QSize(24, 24));
        underlineBtn->setMaximumSize(QSize(24, 24));
        underlineBtn->setStyleSheet(QString::fromUtf8(""));
        underlineBtn->setCheckable(true);
        fontColorBtn = new QPushButton(TextEditWidget);
        fontColorBtn->setObjectName(QString::fromUtf8("fontColorBtn"));
        fontColorBtn->setGeometry(QRect(222, 9, 17, 17));
        fontColorBtn->setMinimumSize(QSize(0, 0));
        fontColorBtn->setMaximumSize(QSize(17, 17));
        fontColorBtn->setStyleSheet(QString::fromUtf8(""));
        frame = new QFrame(TextEditWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(110, 8, 1, 20));
        frame->setMinimumSize(QSize(1, 20));
        frame->setMaximumSize(QSize(1, 20));
        frame->setStyleSheet(QString::fromUtf8(""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        italicBtn = new QPushButton(TextEditWidget);
        italicBtn->setObjectName(QString::fromUtf8("italicBtn"));
        italicBtn->setGeometry(QRect(30, 6, 24, 24));
        italicBtn->setMinimumSize(QSize(24, 24));
        italicBtn->setMaximumSize(QSize(24, 24));
        italicBtn->setStyleSheet(QString::fromUtf8(""));
        italicBtn->setCheckable(true);

        retranslateUi(TextEditWidget);

        QMetaObject::connectSlotsByName(TextEditWidget);
    } // setupUi

    void retranslateUi(QWidget *TextEditWidget)
    {
        TextEditWidget->setWindowTitle(QApplication::translate("TextEditWidget", "Form", nullptr));
        boldBtn->setText(QString());
        orderedBtn->setText(QString());
        strikeOutBtn->setText(QString());
        unorderedBtn->setText(QString());
        fontSizeBtn->setText(QApplication::translate("TextEditWidget", "14", nullptr));
        styleBtn->setText(QString());
        underlineBtn->setText(QString());
        fontColorBtn->setText(QString());
        italicBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TextEditWidget: public Ui_TextEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTEDITWIDGET_H
