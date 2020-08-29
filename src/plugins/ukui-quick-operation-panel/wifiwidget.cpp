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
#include "wifiwidget.h"

WifiWidget::WifiWidget(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initLayout();
    initComponent();
    initStatus();
}

WifiWidget::~WifiWidget()
{

}

void WifiWidget::initMemberVariables()
{
    m_IconPathList << KYLIN_WIFI_NORMAL_PATH << KYLIN_WIFI_HOVER_PATH << KYLIN_WIFI_PRESS_PATH;
    m_IconNameList << KYLIN_WIFI_NORMAL_NAME << KYLIN_WIFI_HOVER_NAME << KYLIN_WIFI_PRESS_NAME;




    m_pWifiIconLabel = new QLabel();
    m_pWifiIconLabel->setFixedSize(24, 24);
    m_pWifiIconLabel->setPixmap((QIcon::fromTheme( m_IconNameList.at(0), QIcon(m_IconPathList.at(0)))).pixmap(m_pWifiIconLabel->size()));

    m_pWifihNameLabel = new QLabel();
    m_pWifihNameLabel->setText("kylin");
    m_pWifihNameLabel->setFixedHeight(18);
    QPalette palette;
    palette.setBrush(QPalette::WindowText, Qt::black);
    m_pWifihNameLabel->setPalette(palette);
    this->update();



    m_pWifiButton    = new QPushButton();
    //connect(m_pWifiButton, &QPushButton::clicked, this, &WifiWidget::setButtonclickSlots);
    m_pWifiButton->setFixedSize(32, 32);
    m_pWifiButton->setIconSize(QSize(16, 16));
    QMatrix matrix;
    matrix.rotate(45);
   // m_pWifiButton->setIcon(QIcon(m_IconPathList.at(3)));

    m_pHboxButtonLayout   = new QHBoxLayout();
    m_pHboxButtonLayout->setContentsMargins(0, 0, 0, 0);
    m_pHboxButtonLayout->setSpacing(0);

    this->setFixedSize(148, 56);
    this->setContentsMargins(0, 0, 0, 0);
    return;
}

/* 初始化布局 */
void WifiWidget::initLayout()
{
        m_pHboxButtonLayout->addItem(new QSpacerItem(12, 4));
        m_pHboxButtonLayout->addWidget(m_pWifiIconLabel);
        m_pHboxButtonLayout->addItem(new QSpacerItem(8, 4));
        m_pHboxButtonLayout->addWidget(m_pWifihNameLabel);
        m_pHboxButtonLayout->addItem(new QSpacerItem(18, 4));
        m_pHboxButtonLayout->addWidget(m_pWifiButton);
        m_pHboxButtonLayout->addItem(new QSpacerItem(4, 1));
        this->setLayout(m_pHboxButtonLayout);
        return;
}

/* 初始化控件状态 */
void WifiWidget::initStatus()
{
    m_bWifiInitStatus = getwifiisEnable();
    if (getwifiisEnable()) {
        m_bWifiIsEnable = getInitStatus();
        if (m_bWifiIsEnable) {

            return;
        } else {
            qDebug() << "当前Wifi可用未打开";
            return;
        }
    } else {
        qDebug() << "当前Wifi不可用";
        return;
    }
}

/* 选中状态 */
void WifiWidget::OpenStatus()
{
    m_pWifiButton->setStyle(m_pStyleOpen);
    return;
}

/* 普通状态 */
void WifiWidget::NormalStatus()
{
    m_pWifiButton->setStyle(m_pStyleNormal);
    return;
}

/* 获取当前的wifi状态，打开或关闭 */
bool WifiWidget::getInitStatus()
{
    QDBusInterface interface( "org.freedesktop.NetworkManager",
                              "/org/freedesktop/NetworkManager",
                              "org.freedesktop.DBus.Properties",
                              QDBusConnection::systemBus());
    //获取当前wifi是否连接
    QDBusReply<QVariant> m_result = interface.call("Get", "org.freedesktop.NetworkManager", "WirelessEnabled");

    if (m_result.isValid()) {
        bool status = m_result.value().toBool();
        return status;
    } else {
        qDebug()<<"org.freedesktop.NetworkManager get invalid"<<endl;
        return false;
    }
    return false;
}

/* 初始化与网络连接的Dbus接口,当前Wifi是否有wifi模块可用 */
bool WifiWidget::getwifiisEnable()
{
    QDBusInterface m_interface( "org.freedesktop.NetworkManager",
                                "/org/freedesktop/NetworkManager",
                                "org.freedesktop.NetworkManager",
                                QDBusConnection::systemBus() );

    QDBusReply<QList<QDBusObjectPath>> obj_reply = m_interface.call("GetAllDevices");
    if (!obj_reply.isValid()) {
        qDebug()<<"execute dbus method 'GetAllDevices' is invalid in func getObjectPath()";
    }

    QList<QDBusObjectPath> obj_paths = obj_reply.value();

    foreach (QDBusObjectPath obj_path, obj_paths) {
        QDBusInterface interface( "org.freedesktop.NetworkManager",
                                  obj_path.path(),
                                  "org.freedesktop.DBus.Introspectable",
                                  QDBusConnection::systemBus() );

        QDBusReply<QString> reply = interface.call("Introspect");
        if (!reply.isValid()) {
            qDebug()<<"execute dbus method 'Introspect' is invalid in func getObjectPath()";
        }

        if (reply.value().indexOf("org.freedesktop.NetworkManager.Device.Wired") != -1) {
        } else if (reply.value().indexOf("org.freedesktop.NetworkManager.Device.Wireless") != -1) {
            return true;
        }
    }
    return false ;
}

/* 初始化gsetting值 */
void WifiWidget::initComponent()
{
    const QByteArray id(CONTROL_CENTER_WIFI);
    if (QGSettings::isSchemaInstalled(id)) {
        m_gsettings = new QGSettings(id);
        //  监听key的value是否发生了变化
        qDebug() << "初始化的switch开关" << m_bWifiIsEnable;
        connect(m_gsettings, &QGSettings::changed, this, [=] (const QString &key) {
            qDebug() << "status changed ------------>" << key << endl;
            if (key == "switchor") {
                bool judge = getSwitchStatus(key);    // 网络工具助手修改的gsetting值
                qDebug() << "当前Key值----->value === " << judge;
                initStatus();
            }
        });
    }
    return;
}

/* 获取当前网络工具助手修改gsetting值后的状态 */
bool WifiWidget::getSwitchStatus(QString key)
{
    if (!m_gsettings) {
        return true;
    }
    const QStringList list = m_gsettings->keys();
    if (!list.contains(key)) {
        return false;
    }
    bool res = m_gsettings->get(key).toBool();
    return res;
}

/* 设置当前的gsetting值 */
void WifiWidget::setwifiSwitch(bool signal)
{
    if (!m_gsettings) {
        return ;
    }
    const QStringList list = m_gsettings->keys();
    if (!list.contains("switch")) {
        return ;
    }
    m_gsettings->set("switch",signal);
    qDebug() << "当前Signal -->" << signal;
}

void WifiWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    switch (status) {
      case NORMAL: {
            if (m_bWifiInitStatus && m_bWifiIsEnable) {
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
            if (m_bWifiInitStatus && m_bWifiIsEnable) {
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
            if (m_bWifiInitStatus && m_bWifiIsEnable) {
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

/* 进入事件 */
void WifiWidget::enterEvent(QEvent *event)
{
    if(event == nullptr) {
        return;
    }

    status=HOVER;
    m_pWifiIconLabel->setPixmap((QIcon::fromTheme(m_IconNameList.at(1), QIcon(m_IconPathList.at(1)))).pixmap(m_pWifiIconLabel->size()));
}

void WifiWidget::leaveEvent(QEvent *event)
{
    if(event == nullptr) {
        return;
    }

    status=NORMAL;
    m_pWifiIconLabel->setPixmap((QIcon::fromTheme( m_IconNameList.at(0), QIcon(m_IconPathList.at(0)))).pixmap(m_pWifiIconLabel->size()));
}

void WifiWidget::mousePressEvent(QMouseEvent *event)
{
    if(event == nullptr) {
        return;
    }
    status=PRESS;
    WifiButtonClickSlot();
   m_pWifiIconLabel->setPixmap((QIcon::fromTheme( m_IconNameList.at(2), QIcon(m_IconPathList.at(2)))).pixmap(m_pWifiIconLabel->size()));
    QWidget::mousePressEvent(event);
}

void WifiWidget::mouseReleaseEvent(QMouseEvent *event)
{
//    bluetoothButtonClickSlots();
//    QWidget::mouseReleaseEvent(event);
}

/* wifi按钮槽函数 */
void WifiWidget::WifiButtonClickSlot()
{
    qDebug() << "是否进入这里";
    if (!m_bWifiInitStatus) {
        qDebug() << "没有wifi模块";
        // 为了发出没有Wifi提示信息，而改变getsetting值
        if (m_bWifiIsEnable) {
            m_bWifiIsEnable = false;
        } else {
            m_bWifiIsEnable = true;
        }
        setwifiSwitch(m_bWifiIsEnable);
        return;
    }
    if (m_bWifiIsEnable) {
        m_bWifiIsEnable = false;
    } else {
        m_bWifiIsEnable = true;
    }
    setwifiSwitch(m_bWifiIsEnable);
}
