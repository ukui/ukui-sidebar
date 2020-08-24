/********************************************************************************
** Form generated from reading UI file 'noteExitWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTEEXITWINDOW_H
#define UI_NOTEEXITWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_noteExitWindow
{
public:
    QWidget *widget;
    QLabel *label;
    QCheckBox *checkBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *noteExitWindow)
    {
        if (noteExitWindow->objectName().isEmpty())
            noteExitWindow->setObjectName(QStringLiteral("noteExitWindow"));
        noteExitWindow->resize(400, 218);
        QFont font;
        font.setPointSize(11);
        noteExitWindow->setFont(font);
        widget = new QWidget(noteExitWindow);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 400, 218));
        widget->setFont(font);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 62, 321, 22));
        label->setMinimumSize(QSize(321, 22));
        label->setMaximumSize(QSize(321, 22));
        QFont font1;
        font1.setFamily(QStringLiteral("Noto Sans CJK SC"));
        font1.setBold(false);
        font1.setWeight(50);
        label->setFont(font1);
        label->setStyleSheet(QLatin1String("font-size:20px;\n"
"font-weight:400;\n"
"opacity:0.97;\n"
"line-height:34px;"));
        checkBox = new QCheckBox(widget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(40, 110, 321, 28));
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        font2.setKerning(true);
        checkBox->setFont(font2);
        checkBox->setStyleSheet(QLatin1String("font-size:14px;\n"
"font-weight:400;\n"
"line-height:40px;\n"
"opacity:0.91;"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(124, 166, 120, 34));
        pushButton->setStyleSheet(QStringLiteral("line-height:24px;"));
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(260, 166, 120, 34));
        pushButton_2->setStyleSheet(QStringLiteral("line-height:24px;"));

        retranslateUi(noteExitWindow);

        QMetaObject::connectSlotsByName(noteExitWindow);
    } // setupUi

    void retranslateUi(QDialog *noteExitWindow)
    {
        noteExitWindow->setWindowTitle(QApplication::translate("noteExitWindow", "Dialog", 0));
        label->setText(QApplication::translate("noteExitWindow", "Are you sure to exit the note book?", 0));
        checkBox->setText(QApplication::translate("noteExitWindow", "Close the desktop note page at the same time", 0));
        pushButton->setText(QApplication::translate("noteExitWindow", "No", 0));
        pushButton_2->setText(QApplication::translate("noteExitWindow", "Yes", 0));
    } // retranslateUi

};

namespace Ui {
    class noteExitWindow: public Ui_noteExitWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTEEXITWINDOW_H
