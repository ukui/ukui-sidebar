/********************************************************************************
** Form generated from reading UI file 'textEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTEDITWIDGET_H
#define UI_TEXTEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TextEditWidget
{
public:
    QPushButton *BoldBtn;
    QPushButton *showNUMList;
    QPushButton *StrikeOutResolvedBtn;
    QPushButton *showListBtn;
    QPushButton *light_blue_btn;
    QPushButton *blue_btn;
    QPushButton *underlineBtn;
    QPushButton *blue_btn_2;
    QFrame *frame;
    QPushButton *ItalicBtn;

    void setupUi(QWidget *TextEditWidget)
    {
        if (TextEditWidget->objectName().isEmpty())
            TextEditWidget->setObjectName(QStringLiteral("TextEditWidget"));
        TextEditWidget->resize(250, 35);
        BoldBtn = new QPushButton(TextEditWidget);
        BoldBtn->setObjectName(QStringLiteral("BoldBtn"));
        BoldBtn->setGeometry(QRect(5, 6, 24, 24));
        BoldBtn->setMinimumSize(QSize(24, 24));
        BoldBtn->setMaximumSize(QSize(24, 24));
        BoldBtn->setStyleSheet(QStringLiteral(""));
        showNUMList = new QPushButton(TextEditWidget);
        showNUMList->setObjectName(QStringLiteral("showNUMList"));
        showNUMList->setGeometry(QRect(145, 6, 24, 24));
        showNUMList->setMinimumSize(QSize(24, 24));
        showNUMList->setMaximumSize(QSize(24, 24));
        showNUMList->setFocusPolicy(Qt::ClickFocus);
        showNUMList->setStyleSheet(QStringLiteral(""));
        showNUMList->setCheckable(true);
        showNUMList->setChecked(false);
        showNUMList->setAutoExclusive(false);
        StrikeOutResolvedBtn = new QPushButton(TextEditWidget);
        StrikeOutResolvedBtn->setObjectName(QStringLiteral("StrikeOutResolvedBtn"));
        StrikeOutResolvedBtn->setGeometry(QRect(80, 6, 24, 24));
        StrikeOutResolvedBtn->setMinimumSize(QSize(24, 24));
        StrikeOutResolvedBtn->setMaximumSize(QSize(24, 24));
        StrikeOutResolvedBtn->setStyleSheet(QStringLiteral(""));
        StrikeOutResolvedBtn->setCheckable(true);
        showListBtn = new QPushButton(TextEditWidget);
        showListBtn->setObjectName(QStringLiteral("showListBtn"));
        showListBtn->setGeometry(QRect(120, 6, 24, 24));
        showListBtn->setMinimumSize(QSize(24, 24));
        showListBtn->setMaximumSize(QSize(24, 24));
        showListBtn->setFocusPolicy(Qt::ClickFocus);
        showListBtn->setStyleSheet(QStringLiteral(""));
        showListBtn->setCheckable(true);
        showListBtn->setAutoExclusive(false);
        light_blue_btn = new QPushButton(TextEditWidget);
        light_blue_btn->setObjectName(QStringLiteral("light_blue_btn"));
        light_blue_btn->setGeometry(QRect(183, 5, 30, 25));
        light_blue_btn->setStyleSheet(QStringLiteral(""));
        blue_btn = new QPushButton(TextEditWidget);
        blue_btn->setObjectName(QStringLiteral("blue_btn"));
        blue_btn->setGeometry(QRect(215, 5, 30, 25));
        blue_btn->setMinimumSize(QSize(30, 25));
        blue_btn->setMaximumSize(QSize(30, 25));
        blue_btn->setStyleSheet(QStringLiteral(""));
        underlineBtn = new QPushButton(TextEditWidget);
        underlineBtn->setObjectName(QStringLiteral("underlineBtn"));
        underlineBtn->setGeometry(QRect(55, 6, 24, 24));
        underlineBtn->setMinimumSize(QSize(24, 24));
        underlineBtn->setMaximumSize(QSize(24, 24));
        underlineBtn->setStyleSheet(QStringLiteral(""));
        underlineBtn->setCheckable(true);
        blue_btn_2 = new QPushButton(TextEditWidget);
        blue_btn_2->setObjectName(QStringLiteral("blue_btn_2"));
        blue_btn_2->setGeometry(QRect(222, 9, 17, 17));
        blue_btn_2->setMinimumSize(QSize(0, 0));
        blue_btn_2->setMaximumSize(QSize(17, 17));
        blue_btn_2->setStyleSheet(QLatin1String("background-color: rgb(245, 255, 180);\n"
""));
        frame = new QFrame(TextEditWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(110, 8, 1, 20));
        frame->setMinimumSize(QSize(1, 20));
        frame->setMaximumSize(QSize(1, 20));
        frame->setStyleSheet(QStringLiteral(""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        ItalicBtn = new QPushButton(TextEditWidget);
        ItalicBtn->setObjectName(QStringLiteral("ItalicBtn"));
        ItalicBtn->setGeometry(QRect(30, 6, 24, 24));
        ItalicBtn->setMinimumSize(QSize(24, 24));
        ItalicBtn->setMaximumSize(QSize(24, 24));
        ItalicBtn->setStyleSheet(QStringLiteral(""));
        ItalicBtn->setCheckable(true);

        retranslateUi(TextEditWidget);

        QMetaObject::connectSlotsByName(TextEditWidget);
    } // setupUi

    void retranslateUi(QWidget *TextEditWidget)
    {
        TextEditWidget->setWindowTitle(QApplication::translate("TextEditWidget", "Form", 0));
        BoldBtn->setText(QString());
        showNUMList->setText(QString());
        StrikeOutResolvedBtn->setText(QString());
        showListBtn->setText(QString());
        light_blue_btn->setText(QApplication::translate("TextEditWidget", "14", 0));
        blue_btn->setText(QString());
        underlineBtn->setText(QString());
        blue_btn_2->setText(QString());
        ItalicBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TextEditWidget: public Ui_TextEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTEDITWIDGET_H
