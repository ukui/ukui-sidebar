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
#ifndef PADWIDGET_H
#define PADWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QGSettings>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QStyleOption>
#include "swichButtonOpenStatus.h"
#include "customstyle_switchNormalStatus.h"
#include "switchbutton.h"

#define KYLIN_PC_NORMAL_NAME            "kylin-icon-PC-mode"
#define KYLIN_PC_SET_NAME               "kylin-icon-pcmode-s"

#define KYLIN_PAD_NORMAL_NAME            "kylin-icon-tablet-mode"
#define KYLIN_PAD_SET_NAME               "kylin-icon-tabletmode-s"

#define KYLIN_PC_NORMAL_PATH            ":/images/icon-PC-mode.svg"
#define KYLIN_PC_SET_PATH               ":/images/icon-pcmode-s.svg"

#define KYLIN_PAD_NORMAL_PATH           ":/images/icon-tablet-mode.svg"
#define KYLIN_PAD_SET_PATH              ":/images/icon-tabletmode-s.svg"

#define KYLIN_PAD_GSETTING_VALUE        "org.ukui.SettingsDaemon.plugins.tablet-mode"
#define KYLIN_PAD_MODLE                 "tablet-mode"

class padWidget : public QWidget
{
    Q_OBJECT
public:
    explicit padWidget(QWidget *parent = nullptr);
    ~padWidget();
    void   initMemberVariables();
    void   initGsettingValue();
    void   initLayout();
    void   setPadButtonStatus();
    QColor getSystemPaleteColor();
    void   setLabelTextColor();
private:
    QWidget       *m_pWidgetButton;
    QPushButton   *m_pPadButton;
    QLabel        *m_pPadLabel;

    QStyle        *m_pStyleOpen;
    QStyle        *m_pStyleNormal;

    QGSettings    *m_pTabletModeGsetting;
    QVBoxLayout   *m_pVboxButtonLayout;
    QVBoxLayout   *m_pVboxLayout;
    QStringList   m_IconPathList;
    QStringList   m_IconNameList;

    bool          m_bModelStatus;
private slots:
    void          PadButtonClickSlots();
};

#endif // PADWIDGET_H
