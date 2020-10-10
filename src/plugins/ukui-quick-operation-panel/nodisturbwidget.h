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

#ifndef NODISTURBWIDGET_H
#define NODISTURBWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGSettings>
#include <QByteArray>
#include <QDebug>
#include <QStyleOption>

#include "switchbutton.h"
#include "swichButtonOpenStatus.h"
#include "customstyle_switchNormalStatus.h"
#include "labelfotmattext.h"

#define KYLIN_NODISTURB_NORMAL_NAME     "kylin-icon-DND"
#define KYLIN_NODISTURB_SET_NAME        "kylin-icon-DND-s"
#define KYLIN_NODISTURB_OPEN_NAME       "kylin-icon-DND-open"


#define KYLIN_NODISTURB_NORMAL_PATH     ":/images/icon-DND.svg"
#define KYLIN_NODISTURB_SET_PATH        ":/images/icon-DND-s.svg"
#define KYLIN_NODISTURB_OPEN_PATH       ":/images/icon-DND-open.svg"
#define KYLIN_DELETE_ICONPATH           ":/images/cancel-lock.png"

#define UKUI_VOLUME_BRIGHTNESS_GSETTING_ID          "org.ukui.quick-operation.panel"
#define KYLIN_DISTURB_GSETTING_VALUE_STATUS         "disturbmodestatus"
#define KYLIN_DISTURB_GSETTING_VALUE_SOUNDOFF       "disturbmodesoundoff"
#define KULIN_DISTURB_GSETTING_VALUE_NOTIFYCLOSE    "disturbmodenotifyclose"

class nodisturbWidget : public QWidget
{
    Q_OBJECT
public:
    explicit nodisturbWidget(QWidget *parent = nullptr);
    ~nodisturbWidget();
    void initMemberVariables();
    void initGsettingValue();
    void initLayout();

    QColor getSystemPaleteColor();
    void   setLabelTextColor();
    void   setEyeButtonStatus();
    QPushButton   *m_pDeleteButton;
    void   paintEvent(QPaintEvent *e);

private:
    QWidget       *m_pWidgetButton;
    QPushButton   *m_pnodisturbButton;
    QLabel        *m_pnodisturbLabel;

    LabelFotmatText *m_pLabelFotmatText;

    QStyle        *m_pStyleNormal;
    QStyle        *m_pStyleOpen;

    QGSettings    *m_pTabletModeGsetting = nullptr;
    QVBoxLayout   *m_pVboxButtonLayout;
    QVBoxLayout   *m_pVboxLayout;
    bool           m_bModelStatus;

private slots:
    void setNodisturbButtonSlots();
};

#endif // NODISTURBWIDGET_H
