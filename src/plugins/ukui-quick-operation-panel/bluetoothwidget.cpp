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
#include "bluetoothwidget.h"

bluetoothWidget::bluetoothWidget(QWidget *parent) : QWidget(parent)
{
    initBluetoothDbus();
    initMemberVariables();
    initLayout();
    initBluetoothStatus();
}

bluetoothWidget::~bluetoothWidget()
{

}

void bluetoothWidget::initMemberVariables()
{
    m_IconPathList << KYLIN_BLUETOOTH_NORMAL_PATH << KYLIN_BLUETOOTH_HOVER_PATH << KYLIN_BLUETOOTH_PRESS_PATH;
    m_IconNameList << KYLIN_BLUETOOTH_NORMAL_NAME << KYLIN_BLUETOOTH_HOVER_NAME << KYLIN_BLUETOOTH_PRESS_NAME;

    m_pWidgetButton         = new QWidget();
    m_pWidgetButton->setFixedSize(62, 62);
    m_pWidgetButton->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout     = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);

    m_pbluetoothButton = new switchButton(m_IconPathList, m_IconNameList);
    connect(m_pbluetoothButton, &switchButton::clicked, this, &bluetoothWidget::bluetoothButtonClickSlots);
    m_pbluetoothButton->setFixedSize(62, 62);
    m_pbluetoothButton->setIconSize(QSize(32, 32));

    m_pbluetoothLabel = new QLabel(QObject::tr("蓝牙"));
    m_pbluetoothLabel->setAlignment(Qt::AlignHCenter);

    m_pVboxLayout = new QVBoxLayout();
    m_pVboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxLayout->setSpacing(0);

    m_pStyleOpen   = new CustomStyle_SwitchOpenStatus("ukui-default");
    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");

    this->setFixedSize(80, 93);
    this->setContentsMargins(0, 0, 0, 0);
    return;
}

/* 初始化布局 */
void bluetoothWidget::initLayout()
{
    m_pVboxButtonLayout->addWidget(m_pbluetoothButton, 0, Qt::AlignCenter);
    m_pWidgetButton->setLayout(m_pVboxButtonLayout);
    m_pVboxLayout->addWidget(m_pWidgetButton, 0, Qt::AlignCenter);
    m_pVboxLayout->addItem(new QSpacerItem(15, 10));
    m_pVboxLayout->addWidget(m_pbluetoothLabel);
    this->setLayout(m_pVboxLayout);
    return;
}

/* 初始化dbus接口 */
bool bluetoothWidget::initBluetoothDbus()
{
    m_pServiceInterface = new QDBusInterface(KYLIN_BLUETOOTH_SERVER_NAME,
                                             KYLIN_BLUETOOTH_SERVER_PATH,
                                             KYLIN_BLUETOOTH_SERVER_INTERFACE,
                                             QDBusConnection::sessionBus());
    if (m_pServiceInterface->isValid() && m_pServiceInterface == nullptr) {
        qDebug() << "dbus接口初始化失败";
        return false;
    }
    connect(m_pServiceInterface, SIGNAL(BluetoothStatusChanged(bool)), this, SLOT(BluetoothStatusChangedSlots(bool)));
    return true;
}

/* 初始化第一次蓝牙状态 */
void bluetoothWidget::initBluetoothStatus()
{
    QDBusMessage msg = m_pServiceInterface->call("GetBluetoothStatus");
    m_bbluetoothStatus = msg.arguments().at(0).toBool();
    qDebug() << "第一次初始化状态" << m_bbluetoothStatus;
    setBluetoothStatus();
}

/* 根据按钮状态设置背景色 */
void bluetoothWidget::setBluetoothStatus()
{
    if (m_bbluetoothStatus) {
        m_pbluetoothButton->setStyle(m_pStyleOpen);
    } else {
        m_pbluetoothButton->setStyle(m_pStyleNormal);
    }
    return;
}

/* 监听dbus信号，当蓝牙状态改变时，将会触发此信号 */
void bluetoothWidget::BluetoothStatusChangedSlots(bool status)
{
    qDebug() << "当前蓝牙状态已改变";
    m_bbluetoothStatus = status;
    setBluetoothStatus();
    return;
}

/* 点击按钮槽函数 */
void bluetoothWidget::bluetoothButtonClickSlots()
{
    if (m_bbluetoothStatus) {
        m_pbluetoothButton->setStyle(m_pStyleNormal);
        m_bbluetoothStatus = false;
        m_pServiceInterface->call("SetBluetoothStatus", false);
    } else {
        m_pbluetoothButton->setStyle(m_pStyleOpen);
        m_bbluetoothStatus = true;
        m_pServiceInterface->call("SetBluetoothStatus", true);
    }
    return;
}
