/********************************************************************************
** Form generated from reading UI file 'noteExitWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTEEXITWINDOW_H
#define UI_NOTEEXITWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_noteExitWindow
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QCheckBox *checkBox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *noteExitWindow)
    {
        if (noteExitWindow->objectName().isEmpty())
            noteExitWindow->setObjectName(QString::fromUtf8("noteExitWindow"));
        noteExitWindow->resize(412, 230);
        noteExitWindow->setMinimumSize(QSize(412, 230));
        noteExitWindow->setMaximumSize(QSize(412, 230));
        QFont font;
        font.setPointSize(11);
        noteExitWindow->setFont(font);
        verticalLayout_2 = new QVBoxLayout(noteExitWindow);
        verticalLayout_2->setSpacing(40);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(61, 68, 0, 24);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(31);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(noteExitWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(321, 22));
        label->setMaximumSize(QSize(321, 22));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Noto Sans CJK SC"));
        font1.setBold(false);
        font1.setWeight(50);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("font-size:20px;\n"
"font-weight:400;\n"
"opacity:0.97;\n"
"line-height:34px;"));

        verticalLayout->addWidget(label);

        checkBox = new QCheckBox(noteExitWindow);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        font2.setKerning(true);
        checkBox->setFont(font2);
        checkBox->setStyleSheet(QString::fromUtf8("font-size:14px;\n"
"font-weight:400;\n"
"line-height:40px;\n"
"opacity:0.91;"));

        verticalLayout->addWidget(checkBox);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(16);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, 26, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(noteExitWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(120, 34));
        pushButton->setMaximumSize(QSize(120, 34));
        pushButton->setStyleSheet(QString::fromUtf8("line-height:24px;"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(noteExitWindow);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(120, 34));
        pushButton_2->setMaximumSize(QSize(120, 34));
        pushButton_2->setStyleSheet(QString::fromUtf8("line-height:24px;"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(noteExitWindow);

        QMetaObject::connectSlotsByName(noteExitWindow);
    } // setupUi

    void retranslateUi(QDialog *noteExitWindow)
    {
        noteExitWindow->setWindowTitle(QApplication::translate("noteExitWindow", "Dialog", nullptr));
        label->setText(QApplication::translate("noteExitWindow", "Are you sure to exit the note book?", nullptr));
        checkBox->setText(QApplication::translate("noteExitWindow", "Close the desktop note page at the same time", nullptr));
        pushButton->setText(QApplication::translate("noteExitWindow", "No", nullptr));
        pushButton_2->setText(QApplication::translate("noteExitWindow", "Yes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class noteExitWindow: public Ui_noteExitWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTEEXITWINDOW_H
