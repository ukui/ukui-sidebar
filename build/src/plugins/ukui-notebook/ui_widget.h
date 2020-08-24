/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_3;
    QPushButton *newKynote;
    QLineEdit *SearchLine;
    QPushButton *trashButton;
    QPushButton *viewChangeButton;
    QPushButton *pushButton_Mini;
    QPushButton *pushButton_Exit;
    QFrame *frame;
    QPushButton *searchBtn;
    QToolButton *menuBtn;
    QListView *listView;
    QWidget *widget_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *sort_btn;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(704, 590);
        Widget->setMinimumSize(QSize(704, 590));
        Widget->setMaximumSize(QSize(704, 590));
        Widget->setStyleSheet(QStringLiteral(""));
        widget = new QWidget(Widget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 704, 590));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setMinimumSize(QSize(0, 40));
        newKynote = new QPushButton(widget_3);
        newKynote->setObjectName(QStringLiteral("newKynote"));
        newKynote->setGeometry(QRect(6, 5, 90, 32));
        newKynote->setMinimumSize(QSize(90, 32));
        newKynote->setMaximumSize(QSize(60, 25));
        newKynote->setCursor(QCursor(Qt::PointingHandCursor));
        newKynote->setFocusPolicy(Qt::TabFocus);
        newKynote->setStyleSheet(QStringLiteral(""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/newNote_Regular.png"), QSize(), QIcon::Normal, QIcon::Off);
        newKynote->setIcon(icon);
        newKynote->setIconSize(QSize(16, 16));
        SearchLine = new QLineEdit(widget_3);
        SearchLine->setObjectName(QStringLiteral("SearchLine"));
        SearchLine->setGeometry(QRect(116, 5, 320, 32));
        SearchLine->setMinimumSize(QSize(320, 32));
        SearchLine->setStyleSheet(QStringLiteral(""));
        trashButton = new QPushButton(widget_3);
        trashButton->setObjectName(QStringLiteral("trashButton"));
        trashButton->setGeometry(QRect(492, 5, 32, 32));
        trashButton->setMinimumSize(QSize(32, 32));
        trashButton->setMaximumSize(QSize(33, 32));
        trashButton->setCursor(QCursor(Qt::ArrowCursor));
        trashButton->setFocusPolicy(Qt::TabFocus);
        trashButton->setStyleSheet(QStringLiteral(""));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/trashCan_Regular.png"), QSize(), QIcon::Normal, QIcon::Off);
        trashButton->setIcon(icon1);
        trashButton->setIconSize(QSize(14, 18));
        viewChangeButton = new QPushButton(widget_3);
        viewChangeButton->setObjectName(QStringLiteral("viewChangeButton"));
        viewChangeButton->setGeometry(QRect(532, 5, 32, 32));
        viewChangeButton->setMinimumSize(QSize(32, 32));
        viewChangeButton->setMaximumSize(QSize(32, 32));
        viewChangeButton->setStyleSheet(QStringLiteral(""));
        pushButton_Mini = new QPushButton(widget_3);
        pushButton_Mini->setObjectName(QStringLiteral("pushButton_Mini"));
        pushButton_Mini->setGeometry(QRect(618, 5, 32, 32));
        pushButton_Mini->setMinimumSize(QSize(32, 32));
        pushButton_Mini->setMaximumSize(QSize(32, 32));
        pushButton_Mini->setStyleSheet(QStringLiteral(""));
        pushButton_Exit = new QPushButton(widget_3);
        pushButton_Exit->setObjectName(QStringLiteral("pushButton_Exit"));
        pushButton_Exit->setGeometry(QRect(650, 5, 32, 32));
        pushButton_Exit->setMinimumSize(QSize(32, 32));
        pushButton_Exit->setMaximumSize(QSize(32, 32));
        pushButton_Exit->setStyleSheet(QStringLiteral(""));
        frame = new QFrame(widget_3);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(575, 7, 1, 30));
        frame->setStyleSheet(QStringLiteral("background-color: rgb(126, 126, 126);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        searchBtn = new QPushButton(widget_3);
        searchBtn->setObjectName(QStringLiteral("searchBtn"));
        searchBtn->setGeometry(QRect(120, 5, 32, 32));
        searchBtn->setMinimumSize(QSize(32, 32));
        searchBtn->setMaximumSize(QSize(32, 32));
        menuBtn = new QToolButton(widget_3);
        menuBtn->setObjectName(QStringLiteral("menuBtn"));
        menuBtn->setGeometry(QRect(586, 5, 32, 32));
        menuBtn->setMinimumSize(QSize(32, 32));
        menuBtn->setMaximumSize(QSize(32, 32));

        verticalLayout->addWidget(widget_3);

        listView = new QListView(widget);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(listView);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMinimumSize(QSize(40, 40));
        horizontalLayoutWidget = new QWidget(widget_2);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 10, 160, 25));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QLatin1String("color: rgb(43,49,56);\n"
"color: rgb(126, 126, 126);"));

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        sort_btn = new QPushButton(widget_2);
        sort_btn->setObjectName(QStringLiteral("sort_btn"));
        sort_btn->setGeometry(QRect(640, 18, 35, 15));
        sort_btn->setMinimumSize(QSize(35, 15));
        sort_btn->setMaximumSize(QSize(35, 15));
        sort_btn->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(widget_2);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        newKynote->setText(QApplication::translate("Widget", "New", 0));
        trashButton->setText(QString());
        viewChangeButton->setText(QString());
        pushButton_Mini->setText(QString());
        pushButton_Exit->setText(QString());
        searchBtn->setText(QString());
        menuBtn->setText(QString());
        label->setText(QString());
        sort_btn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
