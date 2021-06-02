/********************************************************************************
** Form generated from reading UI file 'paletteWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PALETTEWIDGET_H
#define UI_PALETTEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PaletteWidget
{
public:
    QPushButton *pinkBtn;
    QPushButton *orangeBtn;
    QPushButton *yellowBtn;
    QPushButton *purpleBtn;
    QPushButton *lightBlueBtn;
    QPushButton *redBtn;
    QPushButton *darkGreenBtn;
    QPushButton *blueBtn;
    QPushButton *lightGreenBtn;
    QPushButton *goldenBtn;

    void setupUi(QWidget *PaletteWidget)
    {
        if (PaletteWidget->objectName().isEmpty())
            PaletteWidget->setObjectName(QString::fromUtf8("PaletteWidget"));
        PaletteWidget->resize(250, 35);
        PaletteWidget->setMinimumSize(QSize(250, 35));
        PaletteWidget->setMaximumSize(QSize(250, 35));
        pinkBtn = new QPushButton(PaletteWidget);
        pinkBtn->setObjectName(QString::fromUtf8("pinkBtn"));
        pinkBtn->setGeometry(QRect(230, 10, 15, 15));
        pinkBtn->setStyleSheet(QString::fromUtf8(""));
        orangeBtn = new QPushButton(PaletteWidget);
        orangeBtn->setObjectName(QString::fromUtf8("orangeBtn"));
        orangeBtn->setGeometry(QRect(80, 10, 15, 15));
        orangeBtn->setStyleSheet(QString::fromUtf8(""));
        yellowBtn = new QPushButton(PaletteWidget);
        yellowBtn->setObjectName(QString::fromUtf8("yellowBtn"));
        yellowBtn->setGeometry(QRect(205, 10, 15, 15));
        yellowBtn->setStyleSheet(QString::fromUtf8(""));
        purpleBtn = new QPushButton(PaletteWidget);
        purpleBtn->setObjectName(QString::fromUtf8("purpleBtn"));
        purpleBtn->setGeometry(QRect(105, 10, 15, 15));
        purpleBtn->setStyleSheet(QString::fromUtf8(""));
        lightBlueBtn = new QPushButton(PaletteWidget);
        lightBlueBtn->setObjectName(QString::fromUtf8("lightBlueBtn"));
        lightBlueBtn->setGeometry(QRect(155, 10, 15, 15));
        lightBlueBtn->setStyleSheet(QString::fromUtf8(""));
        redBtn = new QPushButton(PaletteWidget);
        redBtn->setObjectName(QString::fromUtf8("redBtn"));
        redBtn->setGeometry(QRect(30, 10, 15, 15));
        redBtn->setStyleSheet(QString::fromUtf8(""));
        darkGreenBtn = new QPushButton(PaletteWidget);
        darkGreenBtn->setObjectName(QString::fromUtf8("darkGreenBtn"));
        darkGreenBtn->setGeometry(QRect(55, 10, 15, 15));
        darkGreenBtn->setStyleSheet(QString::fromUtf8(""));
        blueBtn = new QPushButton(PaletteWidget);
        blueBtn->setObjectName(QString::fromUtf8("blueBtn"));
        blueBtn->setGeometry(QRect(5, 10, 15, 15));
        blueBtn->setStyleSheet(QString::fromUtf8(""));
        lightGreenBtn = new QPushButton(PaletteWidget);
        lightGreenBtn->setObjectName(QString::fromUtf8("lightGreenBtn"));
        lightGreenBtn->setGeometry(QRect(180, 10, 15, 15));
        lightGreenBtn->setStyleSheet(QString::fromUtf8(""));
        goldenBtn = new QPushButton(PaletteWidget);
        goldenBtn->setObjectName(QString::fromUtf8("goldenBtn"));
        goldenBtn->setGeometry(QRect(130, 10, 15, 15));
        goldenBtn->setStyleSheet(QString::fromUtf8(""));

        retranslateUi(PaletteWidget);

        QMetaObject::connectSlotsByName(PaletteWidget);
    } // setupUi

    void retranslateUi(QWidget *PaletteWidget)
    {
        PaletteWidget->setWindowTitle(QApplication::translate("PaletteWidget", "Form", nullptr));
        pinkBtn->setText(QString());
        orangeBtn->setText(QString());
        yellowBtn->setText(QString());
        purpleBtn->setText(QString());
        lightBlueBtn->setText(QString());
        redBtn->setText(QString());
        darkGreenBtn->setText(QString());
        blueBtn->setText(QString());
        lightGreenBtn->setText(QString());
        goldenBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PaletteWidget: public Ui_PaletteWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PALETTEWIDGET_H
