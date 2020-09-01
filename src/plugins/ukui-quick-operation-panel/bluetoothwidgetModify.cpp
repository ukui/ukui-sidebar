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
#include "bluetoothwidgetModify.h"

ModifybluetoothWidget::ModifybluetoothWidget(QWidget *parent) : QWidget(parent)
{
    initBluetoothDbus();
    initMemberVariables();
    initLayout();
    initBluetoothStatus();
}

ModifybluetoothWidget::~ModifybluetoothWidget()
{

}

void ModifybluetoothWidget::initMemberVariables()
{
    m_IconPathList << KYLIN_BLUETOOTH_NORMAL_PATH << KYLIN_BLUETOOTH_HOVER_PATH << KYLIN_BLUETOOTH_PRESS_PATH;
    m_IconNameList << KYLIN_BLUETOOTH_NORMAL_NAME << KYLIN_BLUETOOTH_HOVER_NAME << KYLIN_BLUETOOTH_PRESS_NAME;

    m_pbluetoothIconLabel = new QLabel();
    m_pbluetoothIconLabel->setFixedSize(24, 24);
    m_pbluetoothIconLabel->setPixmap((QIcon::fromTheme( m_IconNameList.at(0), QIcon(m_IconPathList.at(0)))).pixmap(m_pbluetoothIconLabel->size()));


    m_pbluetoothNameLabel = new QLabel();
    m_pbluetoothNameLabel->setText("kylin");
    m_pbluetoothNameLabel->setFixedHeight(18);
    QPalette palette;
    palette.setBrush(QPalette::WindowText, Qt::black);
    m_pbluetoothNameLabel->setPalette(palette);
    this->update();


    m_pbluetoothButton    = new QPushButton();
    connect(m_pbluetoothButton, &QPushButton::clicked, this, &ModifybluetoothWidget::setButtonclickSlots);
    m_pbluetoothButton->setFixedSize(32, 32);
    m_pbluetoothButton->setIconSize(QSize(16, 16));

    m_pHboxButtonLayout   = new QHBoxLayout();
    m_pHboxButtonLayout->setContentsMargins(0, 0, 0, 0);
    m_pHboxButtonLayout->setSpacing(0);

    this->setFixedSize(148, 56);
    this->setContentsMargins(0, 0, 0, 0);
    return;
}

/* 初始化布局 */
void ModifybluetoothWidget::initLayout()
{
    m_pHboxButtonLayout->addItem(new QSpacerItem(12, 4));
    m_pHboxButtonLayout->addWidget(m_pbluetoothIconLabel);
    m_pHboxButtonLayout->addItem(new QSpacerItem(8, 4));
    m_pHboxButtonLayout->addWidget(m_pbluetoothNameLabel);
    m_pHboxButtonLayout->addItem(new QSpacerItem(18, 4));
    m_pHboxButtonLayout->addWidget(m_pbluetoothButton);
    m_pHboxButtonLayout->addItem(new QSpacerItem(4, 1));
    this->setLayout(m_pHboxButtonLayout);
    return;
}

/* 初始化dbus接口 */
bool ModifybluetoothWidget::initBluetoothDbus()
{
//    m_pServiceInterface = new QDBusInterface(KYLIN_BLUETOOTH_SERVER_NAME,
//                                             KYLIN_BLUETOOTH_SERVER_PATH,
//                                             KYLIN_BLUETOOTH_SERVER_INTERFACE,
//                                             QDBusConnection::sessionBus());
//    if (m_pServiceInterface->isValid() && m_pServiceInterface == nullptr) {
//        qDebug() << "dbus接口初始化失败";
//        return false;
//    }
//    connect(m_pServiceInterface, SIGNAL(BluetoothStatusChanged(bool)), this, SLOT(BluetoothStatusChangedSlots(bool)));
//    return true;
}

/* 初始化第一次蓝牙状态 */
void ModifybluetoothWidget::initBluetoothStatus()
{
//    QDBusMessage msg = m_pServiceInterface->call("GetBluetoothStatus");
//    m_bbluetoothStatus = msg.arguments().at(0).toBool();
//    qDebug() << "第一次初始化状态" << m_bbluetoothStatus;
    setBluetoothStatus();
}

/* 根据按钮状态设置背景色 */
void ModifybluetoothWidget::setBluetoothStatus()
{
//    if (m_bbluetoothStatus) {
//        m_pbluetoothButton->setStyle(m_pStyleOpen);
//    } else {
//        m_pbluetoothButton->setStyle(m_pStyleNormal);
//    }
    return;
}

/* 进入事件 */
void ModifybluetoothWidget::enterEvent(QEvent *event)
{
    if(event == nullptr) {
        return;
    }

    status=HOVER;
    m_pbluetoothIconLabel->setPixmap((QIcon::fromTheme(m_IconNameList.at(1), QIcon(m_IconPathList.at(1)))).pixmap(m_pbluetoothIconLabel->size()));
}

void ModifybluetoothWidget::leaveEvent(QEvent *event)
{
    if(event == nullptr) {
        return;
    }

    status=NORMAL;
    m_pbluetoothIconLabel->setPixmap((QIcon::fromTheme( m_IconNameList.at(0), QIcon(m_IconPathList.at(0)))).pixmap(m_pbluetoothIconLabel->size()));
}

void ModifybluetoothWidget::mousePressEvent(QMouseEvent *event)
{
    if(event == nullptr) {
        return;
    }
    status=PRESS;
    m_pbluetoothIconLabel->setPixmap((QIcon::fromTheme( m_IconNameList.at(2), QIcon(m_IconPathList.at(2)))).pixmap(m_pbluetoothIconLabel->size()));
    QWidget::mousePressEvent(event);
}

void ModifybluetoothWidget::mouseReleaseEvent(QMouseEvent *event)
{
    bluetoothButtonClickSlots();
    QWidget::mouseReleaseEvent(event);
}

void ModifybluetoothWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    switch (status) {
      case NORMAL: {
            if (m_bbluetoothStatus) {
              QColor color(61,107,229);
              p.setBrush(QBrush(color));
            } else {
              QColor color(246, 246, 246);
              p.setBrush(QBrush(color));
            }
            p.setOpacity(1);
            p.setPen(Qt::NoPen);
            break;
      }
      case HOVER: {
            if (m_bbluetoothStatus) {
              QColor color(107,142,235);
              p.setBrush(QBrush(color));
            } else {
              QColor color(246, 246, 246);
              p.setBrush(QBrush(color));
            }
            p.setOpacity(1);
            p.setPen(Qt::NoPen);
            break;
      }
      case PRESS: {
            if (m_bbluetoothStatus) {
              QColor color(50,87,202);
              p.setBrush(QBrush(color));
            } else {
              QColor color(246, 246, 246);
              p.setBrush(QBrush(color));
            }
            p.setOpacity(1);
            p.setPen(Qt::NoPen);
            break;
      }
    }
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.drawRoundedRect(opt.rect,28,28);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    this->update();
    QWidget::paintEvent(event);
}

/* 监听dbus信号，当蓝牙状态改变时，将会触发此信号 */
void ModifybluetoothWidget::BluetoothStatusChangedSlots(bool status)
{
    qDebug() << "当前蓝牙状态已改变";
    m_bbluetoothStatus = status;
    setBluetoothStatus();
    return;
}

/* 点击按钮槽函数 */
void ModifybluetoothWidget::bluetoothButtonClickSlots()
{
    if (m_bbluetoothStatus) {
        m_bbluetoothStatus = false;
        m_pServiceInterface->call("SetBluetoothStatus", false);
    } else {
        m_bbluetoothStatus = true;
        m_pServiceInterface->call("SetBluetoothStatus", true);
    }
    return;
}

void ModifybluetoothWidget::setButtonclickSlots()
{
    QProcess p(0);
    p.startDetached("ukui-control-center -n");
    p.waitForStarted();
    return;
}
