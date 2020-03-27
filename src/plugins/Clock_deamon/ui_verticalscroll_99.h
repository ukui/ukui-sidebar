
#ifndef UI_VERTICALSCROLL_99_H
#define UI_VERTICALSCROLL_99_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VerticalScroll_99
{
public:

    void setupUi(QWidget *VerticalScroll_99)
    {
        if (VerticalScroll_99->objectName().isEmpty())
            VerticalScroll_99->setObjectName(QString::fromUtf8("VerticalScroll_99"));
        VerticalScroll_99->resize(50, 200);

        retranslateUi(VerticalScroll_99);

        QMetaObject::connectSlotsByName(VerticalScroll_99);
    } // setupUi

    void retranslateUi(QWidget *VerticalScroll_99)
    {
        VerticalScroll_99->setWindowTitle(QApplication::translate("VerticalScroll_99", "VerticalScroll_99", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VerticalScroll_99: public Ui_VerticalScroll_99 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VERTICALSCROLL_99_H
