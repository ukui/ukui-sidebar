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
    m_pWidgetButton         = new QWidget();
    m_pWidgetButton->setFixedSize(56, 56);
    m_pWidgetButton->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout     = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);

    m_pLabelFotmatText = new LabelFotmatText;

    m_pbluetoothButton = new ShortcutButton();
    connect(m_pbluetoothButton, &ShortcutButton::clicked, this, &bluetoothWidget::bluetoothButtonClickSlots);
    m_pbluetoothButton->setFixedSize(56, 56);
    m_pbluetoothButton->setIconSize(QSize(24, 24));

    m_pDeleteButton = new QPushButton();
    m_pDeleteButton->setFixedSize(20, 20);
    m_pDeleteButton->setIcon(QIcon(KYLIN_DELETE_ICONPATH));
    m_pDeleteButton->setIconSize(QSize(12, 12));

    m_pbluetoothLabel = new QLabel();
    m_pbluetoothLabel->setFixedWidth(60);
    m_pbluetoothLabel->setText(m_pLabelFotmatText->SetFormatBody(QObject::tr("Bluetooth"), m_pbluetoothLabel));
    m_pbluetoothLabel->setAlignment(Qt::AlignHCenter);

    if (m_pLabelFotmatText->m_bTooltips) {
        this->setToolTip(QObject::tr("Bluetooth"));
    }

    m_pVboxLayout = new QVBoxLayout();
    m_pVboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxLayout->setSpacing(0);

    m_pStyleOpen   = new CustomStyle_SwitchOpenStatus("ukui-default");
    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");

    this->setFixedSize(63, 82);
    this->setContentsMargins(0, 0, 0, 0);
    return;
}

/* 初始化布局 */
void bluetoothWidget::initLayout()
{
    m_pVboxButtonLayout->addWidget(m_pbluetoothButton, 0, Qt::AlignCenter);
    m_pWidgetButton->setLayout(m_pVboxButtonLayout);
    m_pVboxLayout->addWidget(m_pWidgetButton, 0, Qt::AlignCenter);
    m_pVboxLayout->addItem(new QSpacerItem(5, 4));
    m_pVboxLayout->addWidget(m_pbluetoothLabel);
    this->setLayout(m_pVboxLayout);
    m_pDeleteButton->setParent(this);
    m_pDeleteButton->move(43, 0);
    m_pDeleteButton->setVisible(false);
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
    m_pbluetoothButton->m_bStatusButton = m_bbluetoothStatus;
    setBluetoothStatus();
}

/* 根据按钮状态设置背景色 */
void bluetoothWidget::setBluetoothStatus()
{
    QPalette palette;
    QColor color = getSystemPaleteColor();
    if (m_bbluetoothStatus) {
        m_pbluetoothButton->setIcon(QIcon::fromTheme(KYLIN_BLUETOOTH_OPEN_NAME, QIcon(KYLIN_BLUETOOTH_OPEN_PATH)));
        m_pbluetoothButton->setStyle(m_pStyleOpen);
    } else {
        m_pbluetoothButton->setIcon(QIcon::fromTheme(KYLIN_BLUETOOTH_NORMAL_NAME, QIcon(KYLIN_BLUETOOTH_NORMAL_PATH)));
        m_pbluetoothButton->setStyle(m_pStyleNormal);
    }
    palette.setBrush(QPalette::WindowText, color);
    m_pbluetoothLabel->setPalette(palette);
    this->update();
    return;
}

QColor bluetoothWidget::getSystemPaleteColor()
{
    QStyleOption opt;
    opt.init(m_pbluetoothLabel);
    if (m_bbluetoothStatus) {
        return opt.palette.color(QPalette::Highlight);
    } else {
        return opt.palette.color(QPalette::Text);
    }
}

/* 监听dbus信号，当蓝牙状态改变时，将会触发此信号 */
void bluetoothWidget::BluetoothStatusChangedSlots(bool status)
{
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
