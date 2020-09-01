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

#ifndef BLUETOOTHWIDGET_H
#define BLUETOOTHWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QtDBus>
#include <QStyleOption>
#include "switchbutton.h"
#include "swichButtonOpenStatus.h"
#include "customstyle_switchNormalStatus.h"

#define KYLIN_BLUETOOTH_NORMAL_NAME     "kylin-icon-bluetooth"
#define KYLIN_BLUETOOTH_OPEN_NAME      "kylin-icon-bluetooth-open"
#define KYLIN_BLUETOOTH_SET_NAME      "kylin-icon-bluetooth-s"

#define KYLIN_BLUETOOTH_NORMAL_PATH     ":/images/icon-bluetooth.svg"
#define KYLIN_BLUETOOTH_OPEN_PATH      ":/images/icon-bluetooth-open.svg"
#define KYLIN_BLUETOOTH_SET_PATH      ":/images/icon-bluetooth-s.svg"

#define KYLIN_BLUETOOTH_SERVER_NAME      "org.blueman.Applet"
#define KYLIN_BLUETOOTH_SERVER_PATH      "/org/blueman/applet"
#define KYLIN_BLUETOOTH_SERVER_INTERFACE "org.blueman.Applet"

class bluetoothWidget : public QWidget
{
    Q_OBJECT
public:
    explicit bluetoothWidget(QWidget *parent = nullptr);
    ~bluetoothWidget();
    void initMemberVariables();
    void initLayout();

    QColor getSystemPaleteColor();

    bool initBluetoothDbus();
    void initBluetoothStatus();

    void setBluetoothStatus();

private:
    QWidget         *m_pWidgetButton;
    QPushButton     *m_pbluetoothButton;
    QLabel          *m_pbluetoothLabel;

    QVBoxLayout     *m_pVboxButtonLayout;
    QVBoxLayout     *m_pVboxLayout;

    QStyle          *m_pStyleOpen;
    QStyle          *m_pStyleNormal;

    QDBusInterface*  m_pServiceInterface;
    bool             m_bbluetoothStatus;
private slots:
    void BluetoothStatusChangedSlots(bool status);
    void bluetoothButtonClickSlots();
};

#endif // BLUETOOTHWIDGET_H
