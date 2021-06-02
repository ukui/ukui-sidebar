/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <noteView.h>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout;
    QPushButton *newKynote;
    QLineEdit *SearchLine;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *trashButton;
    QPushButton *viewChangeButton;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_6;
    QToolButton *menuBtn;
    QPushButton *pushButton_Mini;
    QPushButton *pushButton_Exit;
    NoteView *listView;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(712, 590);
        Widget->setMinimumSize(QSize(704, 590));
        Widget->setMaximumSize(QSize(712, 590));
        Widget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 4, 4, 17);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(4, -1, 64, -1);
        newKynote = new QPushButton(Widget);
        newKynote->setObjectName(QString::fromUtf8("newKynote"));
        newKynote->setMinimumSize(QSize(90, 30));
        newKynote->setMaximumSize(QSize(90, 30));
        newKynote->setCursor(QCursor(Qt::PointingHandCursor));
        newKynote->setFocusPolicy(Qt::TabFocus);
        newKynote->setStyleSheet(QString::fromUtf8(""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/newNote_Regular.png"), QSize(), QIcon::Normal, QIcon::Off);
        newKynote->setIcon(icon);
        newKynote->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(newKynote);

        SearchLine = new QLineEdit(Widget);
        SearchLine->setObjectName(QString::fromUtf8("SearchLine"));
        SearchLine->setMinimumSize(QSize(320, 30));
        SearchLine->setMaximumSize(QSize(320, 30));
        SearchLine->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(SearchLine);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        horizontalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(8);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, -1, -1, -1);
        trashButton = new QPushButton(Widget);
        trashButton->setObjectName(QString::fromUtf8("trashButton"));
        trashButton->setMinimumSize(QSize(30, 30));
        trashButton->setMaximumSize(QSize(30, 30));
        trashButton->setCursor(QCursor(Qt::ArrowCursor));
        trashButton->setFocusPolicy(Qt::TabFocus);
        trashButton->setStyleSheet(QString::fromUtf8(""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/trashCan_Regular.png"), QSize(), QIcon::Normal, QIcon::Off);
        trashButton->setIcon(icon1);
        trashButton->setIconSize(QSize(14, 18));

        horizontalLayout_3->addWidget(trashButton);

        viewChangeButton = new QPushButton(Widget);
        viewChangeButton->setObjectName(QString::fromUtf8("viewChangeButton"));
        viewChangeButton->setMinimumSize(QSize(30, 30));
        viewChangeButton->setMaximumSize(QSize(30, 30));
        viewChangeButton->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_3->addWidget(viewChangeButton);

        frame = new QFrame(Widget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(1, 30));
        frame->setMaximumSize(QSize(1, 30));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(126, 126, 126);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        horizontalLayout_3->addWidget(frame);


        horizontalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(4);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(8, -1, -1, -1);
        menuBtn = new QToolButton(Widget);
        menuBtn->setObjectName(QString::fromUtf8("menuBtn"));
        menuBtn->setMinimumSize(QSize(30, 30));
        menuBtn->setMaximumSize(QSize(30, 30));

        horizontalLayout_6->addWidget(menuBtn);

        pushButton_Mini = new QPushButton(Widget);
        pushButton_Mini->setObjectName(QString::fromUtf8("pushButton_Mini"));
        pushButton_Mini->setMinimumSize(QSize(30, 30));
        pushButton_Mini->setMaximumSize(QSize(30, 30));
        pushButton_Mini->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_6->addWidget(pushButton_Mini);

        pushButton_Exit = new QPushButton(Widget);
        pushButton_Exit->setObjectName(QString::fromUtf8("pushButton_Exit"));
        pushButton_Exit->setMinimumSize(QSize(30, 30));
        pushButton_Exit->setMaximumSize(QSize(30, 30));
        pushButton_Exit->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_6->addWidget(pushButton_Exit);


        horizontalLayout_4->addLayout(horizontalLayout_6);


        verticalLayout->addLayout(horizontalLayout_4);

        listView = new NoteView(Widget);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(listView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(17, -1, 11, -1);
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("color: rgb(43,49,56);\n"
"color: rgb(126, 126, 126);"));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        newKynote->setText(QApplication::translate("Widget", "New", nullptr));
        trashButton->setText(QString());
        viewChangeButton->setText(QString());
        menuBtn->setText(QString());
        pushButton_Mini->setText(QString());
        pushButton_Exit->setText(QString());
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
