/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *titleIcon;
    QLabel *titlename;
    QSpacerItem *horizontalSpacer;
    QPushButton *closeBtn;
    QHBoxLayout *horizontalLayout_2;
    QLabel *appiconLabel;
    QVBoxLayout *verticalLayout_2;
    QLabel *appnameLabel;
    QLabel *versionLabel;
    QLabel *introduceLabel;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName(QString::fromUtf8("About"));
        About->resize(420, 334);
        verticalLayout = new QVBoxLayout(About);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 18, 18, 28);
        label = new QLabel(About);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(22, 18));
        label->setMaximumSize(QSize(22, 18));

        horizontalLayout->addWidget(label);

        titleIcon = new QLabel(About);
        titleIcon->setObjectName(QString::fromUtf8("titleIcon"));
        titleIcon->setMinimumSize(QSize(24, 24));
        titleIcon->setMaximumSize(QSize(24, 24));

        horizontalLayout->addWidget(titleIcon);

        titlename = new QLabel(About);
        titlename->setObjectName(QString::fromUtf8("titlename"));

        horizontalLayout->addWidget(titlename);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        closeBtn = new QPushButton(About);
        closeBtn->setObjectName(QString::fromUtf8("closeBtn"));
        closeBtn->setMinimumSize(QSize(30, 30));
        closeBtn->setMaximumSize(QSize(30, 30));

        horizontalLayout->addWidget(closeBtn);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        appiconLabel = new QLabel(About);
        appiconLabel->setObjectName(QString::fromUtf8("appiconLabel"));
        appiconLabel->setMinimumSize(QSize(96, 96));
        appiconLabel->setMaximumSize(QSize(96, 96));

        horizontalLayout_2->addWidget(appiconLabel);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(16);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 16, -1, -1);
        appnameLabel = new QLabel(About);
        appnameLabel->setObjectName(QString::fromUtf8("appnameLabel"));
        appnameLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(appnameLabel);

        versionLabel = new QLabel(About);
        versionLabel->setObjectName(QString::fromUtf8("versionLabel"));
        versionLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(versionLabel);

        introduceLabel = new QLabel(About);
        introduceLabel->setObjectName(QString::fromUtf8("introduceLabel"));
        introduceLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(introduceLabel);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        verticalLayout->addLayout(verticalLayout_2);

        verticalSpacer = new QSpacerItem(20, 12, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(About);

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QDialog *About)
    {
        About->setWindowTitle(QApplication::translate("About", "Dialog", nullptr));
        label->setText(QString());
        titleIcon->setText(QString());
        titlename->setText(QApplication::translate("About", "clock", nullptr));
        closeBtn->setText(QString());
        appiconLabel->setText(QString());
        appnameLabel->setText(QApplication::translate("About", "Kylin Clock", nullptr));
        versionLabel->setText(QString());
        introduceLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
