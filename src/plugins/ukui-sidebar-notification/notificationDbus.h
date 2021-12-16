/*
* Copyright (C) 2019 Tianjin KYLIN Information Technology Co., Ltd.
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

#ifndef NOTIFICATIONDBUS_H
#define NOTIFICATIONDBUS_H

#include <QObject>
#include <QGSettings>
#include <QMap>
#include <QDateTime>

#define DBUS_INTERFACE "org.ukui.Sidebar.notification"

class NotificationPlugin;

class NotificationDbus : public QObject
{
    Q_OBJECT
    //申明该类有D-BUS服务接口
    Q_CLASSINFO("D-Bus Interface", "org.ukui.Sidebar.notification")

public:
    NotificationDbus(NotificationPlugin *parent);
    void getSettingsValue();
    void fromSettingsGetInfoToList();
    void appNotifySettingChangedSlot();
    QList<char*> listExistsPath();

signals:
    void Sig_Notify(QString appName, QString appIcon,
                    QString summary, QString body,
                    QString urlStr,  QString actions,
                    QDateTime dateTime, int nMaxNum, bool flag);
    void Sig_Takein(QString appName, QString appIcon,
                    QString summary, QString body,
                    QString urlStr,  QString actions,
                    QDateTime dateTime, int nMaxNum, bool flag);
    void Sig_CloseAppMsg(QString strAppName);
    void Sig_UpdateAppMaxNum(QString strAppName, int maxNum);
public slots:
    void sidebarNotification(const QString &appName,const QString &appIcon,
                             const QString &summary,const QString &body,
                             const QString &urlStr, const QString &actions); //创建一条侧边栏通知
    void proxyNotificationJump(const QString &urlStr); //代理通知中心的跳转动作

public:
    bool powerstatus = true;

private:
    NotificationPlugin*     m_parent;           //传一个插件对象指针，用来回传槽函数
    QGSettings*             m_pSettings;
    QMap<QString, int>      m_nAppMaxNum;
    QMap<QString, bool>     m_mapAppSwitch;
};

#endif // NOTIFICATIONDBUS_H
