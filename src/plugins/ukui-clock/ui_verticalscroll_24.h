
#ifndef UI_VERTICALSCROLL_24_H
#define UI_VERTICALSCROLL_24_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VerticalScroll_24
{
public:

    void setupUi(QWidget *VerticalScroll_24)
    {
        if (VerticalScroll_24->objectName().isEmpty())
            VerticalScroll_24->setObjectName(QString::fromUtf8("VerticalScroll_24"));
        VerticalScroll_24->resize(50, 200);

        retranslateUi(VerticalScroll_24);

        QMetaObject::connectSlotsByName(VerticalScroll_24);
    } // setupUi

    void retranslateUi(QWidget *VerticalScroll_24)
    {
        VerticalScroll_24->setWindowTitle(QApplication::translate("VerticalScroll_24", "VerticalScroll_24", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VerticalScroll_24: public Ui_VerticalScroll_24 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VERTICALSCROLL_24_H
