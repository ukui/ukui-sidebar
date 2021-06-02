/********************************************************************************
** Form generated from reading UI file 'setupPage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUPPAGE_H
#define UI_SETUPPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_setuppage
{
public:
    QWidget *widget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSlider *horizontalSlider;
    QPushButton *pushButton_6;
    QLabel *label;
    QPushButton *closeBtn;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *setuppage)
    {
        if (setuppage->objectName().isEmpty())
            setuppage->setObjectName(QString::fromUtf8("setuppage"));
        setuppage->resize(328, 450);
        setuppage->setStyleSheet(QString::fromUtf8(""));
        widget = new QWidget(setuppage);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 328, 450));
        widget->setStyleSheet(QString::fromUtf8(""));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(236, 200, 50, 24));
        pushButton->setStyleSheet(QString::fromUtf8("width:50px;\n"
"border-image: url(:/alarm_on.png);\n"
"height:24px;\n"
"background:linear-gradient(0deg,rgba(39,207,129,1) 0%,rgba(39,207,129,0.9) 100%);\n"
"border-radius:6px;\n"
"border:0px solid rgba();"));
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(236, 66, 50, 24));
        pushButton_2->setStyleSheet(QString::fromUtf8("width:50px;\n"
"border-image: url(:/alarm_off.png);\n"
"height:24px;\n"
"background:linear-gradient(0deg,rgba(39,207,129,1) 0%,rgba(39,207,129,0.9) 100%);\n"
"border-radius:6px;\n"
"border:0px solid rgba();"));
        horizontalSlider = new QSlider(widget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(100, 400, 197, 24));
        horizontalSlider->setStyleSheet(QString::fromUtf8(""));
        horizontalSlider->setOrientation(Qt::Horizontal);
        pushButton_6 = new QPushButton(widget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(10, 400, 70, 30));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 200, 68, 23));
        closeBtn = new QPushButton(widget);
        closeBtn->setObjectName(QString::fromUtf8("closeBtn"));
        closeBtn->setGeometry(QRect(284, 14, 30, 30));
        closeBtn->setMinimumSize(QSize(30, 30));
        closeBtn->setMaximumSize(QSize(30, 30));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 10, 81, 50));
        label_2->setStyleSheet(QString::fromUtf8("font:  \"Noto Sans Bengali\";\n"
"font-size:18px;"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 66, 68, 30));

        retranslateUi(setuppage);

        QMetaObject::connectSlotsByName(setuppage);
    } // setupUi

    void retranslateUi(QWidget *setuppage)
    {
        setuppage->setWindowTitle(QApplication::translate("setuppage", "Form", nullptr));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        pushButton_6->setText(QApplication::translate("setuppage", "volume", nullptr));
        label->setText(QApplication::translate("setuppage", "Boot up", nullptr));
        closeBtn->setText(QString());
        label_2->setText(QApplication::translate("setuppage", "setting", nullptr));
        label_3->setText(QApplication::translate("setuppage", "Mute", nullptr));
    } // retranslateUi

};

namespace Ui {
    class setuppage: public Ui_setuppage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUPPAGE_H
