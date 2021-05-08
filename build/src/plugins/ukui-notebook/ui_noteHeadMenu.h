/********************************************************************************
** Form generated from reading UI file 'noteHeadMenu.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTEHEADMENU_H
#define UI_NOTEHEADMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_noteHeadMenu
{
public:
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonNew;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonMenu;
    QPushButton *pushButtonExit;

    void setupUi(QWidget *noteHeadMenu)
    {
        if (noteHeadMenu->objectName().isEmpty())
            noteHeadMenu->setObjectName(QString::fromUtf8("noteHeadMenu"));
        noteHeadMenu->resize(250, 36);
        horizontalLayout_2 = new QHBoxLayout(noteHeadMenu);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(10, 2, 5, 2);
        pushButtonNew = new QPushButton(noteHeadMenu);
        pushButtonNew->setObjectName(QString::fromUtf8("pushButtonNew"));
        pushButtonNew->setMinimumSize(QSize(20, 20));
        pushButtonNew->setMaximumSize(QSize(20, 20));
        pushButtonNew->setAutoDefault(false);

        horizontalLayout_2->addWidget(pushButtonNew);

        horizontalSpacer = new QSpacerItem(136, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(4);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonMenu = new QPushButton(noteHeadMenu);
        pushButtonMenu->setObjectName(QString::fromUtf8("pushButtonMenu"));
        pushButtonMenu->setMinimumSize(QSize(30, 30));
        pushButtonMenu->setMaximumSize(QSize(30, 30));
        pushButtonMenu->setAutoDefault(false);

        horizontalLayout->addWidget(pushButtonMenu);

        pushButtonExit = new QPushButton(noteHeadMenu);
        pushButtonExit->setObjectName(QString::fromUtf8("pushButtonExit"));
        pushButtonExit->setMinimumSize(QSize(30, 30));
        pushButtonExit->setMaximumSize(QSize(30, 30));
        pushButtonExit->setAutoDefault(false);

        horizontalLayout->addWidget(pushButtonExit);


        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(noteHeadMenu);

        QMetaObject::connectSlotsByName(noteHeadMenu);
    } // setupUi

    void retranslateUi(QWidget *noteHeadMenu)
    {
        noteHeadMenu->setWindowTitle(QApplication::translate("noteHeadMenu", "Form", nullptr));
        pushButtonNew->setText(QString());
        pushButtonMenu->setText(QString());
        pushButtonExit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class noteHeadMenu: public Ui_noteHeadMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTEHEADMENU_H
