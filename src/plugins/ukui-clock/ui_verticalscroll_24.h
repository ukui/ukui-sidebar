/*
* Copyright (C) 2020 Tianjin KYLIN Information Technology Co., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, see <http://www.gnu.org/licenses/&gt;.
*
*/
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
