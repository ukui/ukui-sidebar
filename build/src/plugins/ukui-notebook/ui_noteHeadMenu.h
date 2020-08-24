/********************************************************************************
** Form generated from reading UI file 'noteHeadMenu.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTEHEADMENU_H
#define UI_NOTEHEADMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_noteHeadMenu
{
public:
    QPushButton *pushButtonExit;
    QPushButton *pushButtonMenu;

    void setupUi(QWidget *noteHeadMenu)
    {
        if (noteHeadMenu->objectName().isEmpty())
            noteHeadMenu->setObjectName(QStringLiteral("noteHeadMenu"));
        noteHeadMenu->resize(250, 20);
        pushButtonExit = new QPushButton(noteHeadMenu);
        pushButtonExit->setObjectName(QStringLiteral("pushButtonExit"));
        pushButtonExit->setGeometry(QRect(220, 0, 20, 20));
        pushButtonMenu = new QPushButton(noteHeadMenu);
        pushButtonMenu->setObjectName(QStringLiteral("pushButtonMenu"));
        pushButtonMenu->setGeometry(QRect(190, 0, 20, 20));

        retranslateUi(noteHeadMenu);

        QMetaObject::connectSlotsByName(noteHeadMenu);
    } // setupUi

    void retranslateUi(QWidget *noteHeadMenu)
    {
        noteHeadMenu->setWindowTitle(QApplication::translate("noteHeadMenu", "Form", 0));
        pushButtonExit->setText(QString());
        pushButtonMenu->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class noteHeadMenu: public Ui_noteHeadMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTEHEADMENU_H
