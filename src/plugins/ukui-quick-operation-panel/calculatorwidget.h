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

#ifndef CALCULATORWIDGET_H
#define CALCULATORWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QProcess>
#include <QStyle>
#include "customstyle_switchNormalStatus.h"
#include "switchbutton.h"
#include "labelfotmattext.h"

#define KYLIN_CALCULATOR_NORMAL_PATH    ":/images/icon-calculator.svg"
#define KYLIN_CALCULATOR_SET_PATH       ":/images/icon-allsetting-s.svg"

#define KYLIN_CALCULATOR_NORMAL_NAME    "kylin-icon-calculator"
#define KYLIN_CALCULATOR_SET_NAME       "kylin-icon-allsetting-s"
#define KYLIN_DELETE_ICONPATH           ":/images/cancel-lock.png"

class calculatorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit calculatorWidget(QWidget *parent = nullptr);
    ~calculatorWidget();
    void initMemberVariables();
    void initLayout();
    QPushButton   *m_pDeleteButton;

private:
    QWidget       *m_pWidgetButton;
    QPushButton   *m_pcalculatorButton;
    QLabel        *m_pcalculatorLabel;
    QStyle        *m_pStyleNormal;

    LabelFotmatText *m_pLabelFotmatText;

    QVBoxLayout   *m_pVboxButtonLayout;
    QVBoxLayout   *m_pVboxLayout;

private slots:
    void calculatorButtonClickSlots();
};

#endif // CALCULATORWIDGET_H
