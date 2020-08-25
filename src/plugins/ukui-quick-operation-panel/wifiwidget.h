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
#ifndef WIFIWIDGET_H
#define WIFIWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDebug>
#include <QGSettings>
#include <QStyle>
#include "switchbutton.h"
#include "swichButtonOpenStatus.h"
#include "customstyle_switchNormalStatus.h"

#define CONTROL_CENTER_WIFI "org.ukui.control-center.wifi.switch"

#define KYLIN_WIFI_NORMAL_NAME          "kylin-wifi-normal"
#define KYLIN_WIFI_HOVER_NAME           "kylin-wifi-normal"
#define KYLIN_WIFI_PRESS_NAME           "kylin-wifi-normal"

#define KYLIN_WIFI_NORMAL_PATH          ":/image/wifi-normal.svg"
#define KYLIN_WIFI_HOVER_PATH           ":/image/wifi-hover.svg"
#define KYLIN_WIFI_PRESS_PATH           ":/image/wifi-pressed.svg"

class WifiWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WifiWidget(QWidget *parent= nullptr);
    ~WifiWidget();
    void initMemberVariables();
    void initLayout();
    void initStatus();
    void OpenStatus();
    void NormalStatus();

    bool getInitStatus();
    bool getwifiisEnable();

    void initComponent();
    bool getSwitchStatus(QString key);

    void setwifiSwitch(bool signal);

private:
    QWidget      *m_pWidgetButton;
    switchButton *m_pWifiButton;
    QLabel       *m_pWifiLabel;

    QStyle       *m_pStyleOpen;
    QStyle       *m_pStyleNormal;

    QVBoxLayout  *m_pVboxButtonLayout;
    QVBoxLayout  *m_pVboxLayout;

    QGSettings   *m_gsettings = nullptr;

    QStringList   m_IconPathList;
    QStringList   m_IconNameList;

    bool          m_bWifiIsEnable;
    bool          m_bWifiInitStatus;
private slots:
    void          WifiButtonClickSlot();
};

#endif // WIFIWIDGET_H
