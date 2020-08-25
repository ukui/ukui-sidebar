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
#include "switchbutton.h"

#define KYLIN_CALCULATOR_NORMAL_PATH    ":/image/calculator-normal.svg"
#define KYLIN_CALCULATOR_HOVER_PATH     ":/image/calculator-hover.svg"
#define KYLIN_CALCULATOR_PRESS_PATH     ":/image/calculator-pressed.svg"

#define KYLIN_CALCULATOR_NORMAL_NAME    "kylin-calculator-normal"
#define KYLIN_CALCULATOR_HOVER_NAME     "kylin-calculator-hover"
#define KYLIN_CALCULATOR_PRESS_NAME     "kylin-calculator-pressed"

class calculatorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit calculatorWidget(QWidget *parent = nullptr);
    ~calculatorWidget();
    void initMemberVariables();
    void initLayout();
private:
    QWidget       *m_pWidgetButton;
    switchButton  *m_pcalculatorButton;
    QLabel        *m_pcalculatorLabel;

    QVBoxLayout   *m_pVboxButtonLayout;
    QVBoxLayout   *m_pVboxLayout;

    QStringList  m_IconPathList;
    QStringList  m_IconNameList;
private slots:
    void calculatorButtonClickSlots();
};

#endif // CALCULATORWIDGET_H
