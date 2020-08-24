/********************************************************************************
** Form generated from reading UI file 'paletteWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PALETTEWIDGET_H
#define UI_PALETTEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PaletteWidget
{
public:
    QPushButton *defaultBtn;
    QPushButton *orangeBtn;
    QPushButton *yellowBtn;
    QPushButton *violetBtn;
    QPushButton *lightBlueBtn;
    QPushButton *pinkBtn;
    QPushButton *darkGreenBtn;
    QPushButton *blueBtn;
    QPushButton *lightGreenBtn;
    QPushButton *goldenBtn;

    void setupUi(QWidget *PaletteWidget)
    {
        if (PaletteWidget->objectName().isEmpty())
            PaletteWidget->setObjectName(QStringLiteral("PaletteWidget"));
        PaletteWidget->resize(250, 35);
        PaletteWidget->setMinimumSize(QSize(250, 35));
        PaletteWidget->setMaximumSize(QSize(250, 35));
        defaultBtn = new QPushButton(PaletteWidget);
        defaultBtn->setObjectName(QStringLiteral("defaultBtn"));
        defaultBtn->setGeometry(QRect(230, 10, 15, 15));
        defaultBtn->setStyleSheet(QLatin1String("background:rgba(255,255,255,1);\n"
"border-radius:2px;"));
        orangeBtn = new QPushButton(PaletteWidget);
        orangeBtn->setObjectName(QStringLiteral("orangeBtn"));
        orangeBtn->setGeometry(QRect(80, 10, 15, 15));
        orangeBtn->setStyleSheet(QLatin1String("background:rgba(255,151,47,1);\n"
"border-radius:2px;"));
        yellowBtn = new QPushButton(PaletteWidget);
        yellowBtn->setObjectName(QStringLiteral("yellowBtn"));
        yellowBtn->setGeometry(QRect(205, 10, 15, 15));
        yellowBtn->setStyleSheet(QLatin1String("background:rgba(250,243,175,1);\n"
"border-radius:2px;"));
        violetBtn = new QPushButton(PaletteWidget);
        violetBtn->setObjectName(QStringLiteral("violetBtn"));
        violetBtn->setGeometry(QRect(105, 10, 15, 15));
        violetBtn->setStyleSheet(QLatin1String("background:rgba(186,123,216,1);\n"
"border-radius:2px;"));
        lightBlueBtn = new QPushButton(PaletteWidget);
        lightBlueBtn->setObjectName(QStringLiteral("lightBlueBtn"));
        lightBlueBtn->setGeometry(QRect(155, 10, 15, 15));
        lightBlueBtn->setStyleSheet(QLatin1String("background:rgba(42,162,217,1);\n"
"border-radius:2px;"));
        pinkBtn = new QPushButton(PaletteWidget);
        pinkBtn->setObjectName(QStringLiteral("pinkBtn"));
        pinkBtn->setGeometry(QRect(30, 10, 15, 15));
        pinkBtn->setStyleSheet(QLatin1String("background:rgba(250,108,99,1);\n"
"border-radius:2px;"));
        darkGreenBtn = new QPushButton(PaletteWidget);
        darkGreenBtn->setObjectName(QStringLiteral("darkGreenBtn"));
        darkGreenBtn->setGeometry(QRect(55, 10, 15, 15));
        darkGreenBtn->setStyleSheet(QLatin1String("background:rgba(15,161,90,1);\n"
"border-radius:2px;"));
        blueBtn = new QPushButton(PaletteWidget);
        blueBtn->setObjectName(QStringLiteral("blueBtn"));
        blueBtn->setGeometry(QRect(5, 10, 15, 15));
        blueBtn->setStyleSheet(QLatin1String("background:rgba(76,119,231,1);\n"
"border-radius:2px;"));
        lightGreenBtn = new QPushButton(PaletteWidget);
        lightGreenBtn->setObjectName(QStringLiteral("lightGreenBtn"));
        lightGreenBtn->setGeometry(QRect(180, 10, 15, 15));
        lightGreenBtn->setStyleSheet(QLatin1String("background:rgba(110,207,67,1);\n"
"border-radius:2px;"));
        goldenBtn = new QPushButton(PaletteWidget);
        goldenBtn->setObjectName(QStringLiteral("goldenBtn"));
        goldenBtn->setGeometry(QRect(130, 10, 15, 15));
        goldenBtn->setStyleSheet(QLatin1String("background:rgba(248,209,93,1);\n"
"border-radius:2px;"));

        retranslateUi(PaletteWidget);

        QMetaObject::connectSlotsByName(PaletteWidget);
    } // setupUi

    void retranslateUi(QWidget *PaletteWidget)
    {
        PaletteWidget->setWindowTitle(QApplication::translate("PaletteWidget", "Form", 0));
        defaultBtn->setText(QString());
        orangeBtn->setText(QString());
        yellowBtn->setText(QString());
        violetBtn->setText(QString());
        lightBlueBtn->setText(QString());
        pinkBtn->setText(QString());
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
