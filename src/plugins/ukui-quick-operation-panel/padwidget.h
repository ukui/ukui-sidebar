#ifndef PADWIDGET_H
#define PADWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
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
#include <QLabel>
#include <QVBoxLayout>
#include "switchbutton.h"

#define KYLIN_PAD_NORMAL_NAME           "kylin-pad-normal"
#define KYLIN_PAD_HOVER_NAME            "kylin-pad-hover"
#define KYLIN_PAD_PRESS_NAME            "kylin-pad-pressed"

#define KYLIN_PAD_NORMAL_PATH           ":/image/pad-normal.svg"
#define KYLIN_PAD_HOVER_PATH            ":/image/pad-hover.svg"
#define KYLIN_PAD_PRESS_PATH            ":/image/pad-pressed.svg"

class padWidget : public QWidget
{
    Q_OBJECT
public:
    explicit padWidget(QWidget *parent = nullptr);
    ~padWidget();
    void initMemberVariables();
    void initLayout();

private:
    QWidget       *m_pWidgetButton;
    switchButton  *m_pPadButton;
    QLabel        *m_pPadLabel;

    QVBoxLayout   *m_pVboxButtonLayout;
    QVBoxLayout   *m_pVboxLayout;

    QStringList  m_IconPathList;
    QStringList  m_IconNameList;
};

#endif // PADWIDGET_H
