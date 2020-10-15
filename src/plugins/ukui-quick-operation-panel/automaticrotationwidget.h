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
#ifndef AUTOMATICROTATION_H
#define AUTOMATICROTATION_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QGSettings>
#include <QDebug>
#include "switchbutton.h"
#include "swichButtonOpenStatus.h"
#include "customstyle_switchNormalStatus.h"
#include "labelfotmattext.h"

#define KYLIN_PAD_GSETTING_VALUE        "org.ukui.SettingsDaemon.plugins.tablet-mode"
#define KYLIN_AUTOMATICROTAION_STATUS   "auto-rotation"

#define KYLIN_AUTOMATICROTATION_NORMAL_NAME     "kylin-bluetooth-normal"
#define KYLIN_AUTOMATICROTATION_HOVER_NAME      "kylin-bluetooth-hover"
#define KYLIN_AUTOMATICROTATION_PRESS_NAME      "kylin-bluetooth-pressed"

#define KYLIN_AUTOMATICROTATION_NORMAL_PATH     ":/image/bluetooth-normal.svg"
#define KYLIN_AUTOMATICROTATION_HOVER_PATH      ":/image/bluetooth-hover.svg"
#define KYLIN_AUTOMATICROTATION_PRESS_PATH      ":/image/bluetooth-pressed.svg"

class AutomaticRotationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AutomaticRotationWidget(QWidget *parent = nullptr);

private:
    void initMemberVariables();
    void initLayout();
    void initGsettingValue();
    void setButtonStatus();

private:
    QWidget         *m_pWidgetButton;
    switchButton    *m_pAutomaticRotationButton;
    QLabel          *m_pAutomaticRotationLabel;

    LabelFotmatText *m_pLabelFotmatText;

    QVBoxLayout     *m_pVboxButtonLayout;
    QVBoxLayout     *m_pVboxLayout;

    QStyle          *m_pStyleOpen;
    QStyle          *m_pStyleNormal;

    QGSettings      *m_pAutomaticRotationGsetting = nullptr;

    QStringList      m_IconPathList;
    QStringList      m_IconNameList;

    bool             m_bAutomaticRotationStatus;

private slots:
    void             m_pAutomaticRotationButtonClickSlots();
Q_SIGNALS:

};

#endif // AUTOMATICROTATION_H
