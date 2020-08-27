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

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QtDBus>
#include <QStyleOption>
#include <QPainter>
#include <QIcon>
#include "switchbutton.h"
#include "swichButtonOpenStatus.h"
#include "customstyle_switchNormalStatus.h"

#define KYLIN_BLUETOOTH_NORMAL_NAME     "kylin-bluetooth-normal"
#define KYLIN_BLUETOOTH_HOVER_NAME      "kylin-bluetooth-hover"
#define KYLIN_BLUETOOTH_PRESS_NAME      "kylin-bluetooth-pressed"

#define KYLIN_BLUETOOTH_NORMAL_PATH     ":/image/bluetooth-normal.svg"
#define KYLIN_BLUETOOTH_HOVER_PATH      ":/image/bluetooth-hover.svg"
#define KYLIN_BLUETOOTH_PRESS_PATH      ":/image/bluetooth-pressed.svg"

#define KYLIN_BLUETOOTH_SERVER_NAME      "org.blueman.Applet"
#define KYLIN_BLUETOOTH_SERVER_PATH      "/org/blueman/applet"
#define KYLIN_BLUETOOTH_SERVER_INTERFACE "org.blueman.Applet"

class ModifybluetoothWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ModifybluetoothWidget(QWidget *parent = nullptr);
    ~ModifybluetoothWidget();

    void initMemberVariables();
    void initLayout();

    bool initBluetoothDbus();
    void initBluetoothStatus();

    void setBluetoothStatus();

    enum TaskWidgetStatus{NORMAL, HOVER, PRESS};
    TaskWidgetStatus status = NORMAL;

private:
    QLabel          *m_pbluetoothIconLabel;
    QLabel          *m_pbluetoothNameLabel;
    QPushButton     *m_pbluetoothButton;
    QHBoxLayout     *m_pHboxButtonLayout;

    QStyle          *m_pStyleOpen;
//    QStyle          *m_pStyleNormal;

    QStringList      m_IconPathList;
    QStringList      m_IconNameList;
    QDBusInterface*  m_pServiceInterface;
    bool             m_bbluetoothStatus;

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private slots:
    void BluetoothStatusChangedSlots(bool status);
    void bluetoothButtonClickSlots();
    void setButtonclickSlots();
};
