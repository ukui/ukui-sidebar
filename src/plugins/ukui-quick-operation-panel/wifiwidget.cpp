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
    m_pWidgetButton         = new QWidget();
    m_pWidgetButton->setFixedSize(62, 62);
    m_pWidgetButton->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout     = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);

    m_pWifiButton = new switchButton(m_IconPathList, m_IconNameList);
    connect(m_pWifiButton, &switchButton::clicked, this, &WifiWidget::WifiButtonClickSlot);
    m_pWifiButton->setFixedSize(62, 62);
    m_pWifiButton->setIconSize(QSize(32, 32));

    m_pWifiLabel = new QLabel(QObject::tr("Wifi"));
    m_pWifiLabel->setAlignment(Qt::AlignHCenter);
    m_pWifiLabel->setAlignment(Qt::AlignHCenter);

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
void WifiWidget::initLayout()
{
    m_pVboxButtonLayout->addWidget(m_pWifiButton, 0, Qt::AlignCenter);
    m_pWidgetButton->setLayout(m_pVboxButtonLayout);
    m_pVboxLayout->addWidget(m_pWidgetButton, 0, Qt::AlignCenter);
    m_pVboxLayout->setSpacing(15);
    m_pVboxLayout->addWidget(m_pWifiLabel, 0, Qt::AlignCenter);
    this->setLayout(m_pVboxLayout);
    return;
}

/* 初始化控件状态 */
void WifiWidget::initStatus()
{
    m_bWifiInitStatus = getwifiisEnable();
    if (getwifiisEnable()) {
        m_bWifiIsEnable = getInitStatus();
        if (m_bWifiIsEnable) {
            qDebug() << "当前Wifi可用且已打开";
            OpenStatus();
            return;
        } else {
            qDebug() << "当前Wifi可用未打开";
            NormalStatus();
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
        NormalStatus();
        m_bWifiIsEnable = false;
    } else {
        OpenStatus();
        m_bWifiIsEnable = true;
    }
    setwifiSwitch(m_bWifiIsEnable);
}
