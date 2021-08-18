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

#include "notificationDbus.h"
#include "notificationPlugin.h"
#include <QDBusConnection>
#include <QDateTime>

/* qt会将glib里的signals成员识别为宏，所以取消该宏
 * 后面如果用到signals时，使用Q_SIGNALS代替即可
 **/
#ifdef signals
#undef signals
#endif

extern "C" {
#include <glib.h>
#include <gio/gio.h>
#include <dconf/dconf.h>
}
#define NOTICE_ORIGIN_SCHEMA "org.ukui.control-center.noticeorigin"
#define NOTICE_ORIGIN_PATH "/org/ukui/control-center/noticeorigin/"
#define SWITCH_KEY "messages"
#define MAXIMINE_KEY "maximize"
#define NAME_KEY "nameCn"

NotificationDbus::NotificationDbus(NotificationPlugin *parent)
{
    m_parent = parent;
    getSettingsValue();

    //注册dbus
    QDBusConnection::sessionBus().unregisterService("org.ukui.Sidebar");
    QDBusConnection::sessionBus().registerService("org.ukui.Sidebar");
    //注册对象路径，导出所有此对象的插槽
    //registerObject参数：路径，interface,对象，options
    QDBusConnection::sessionBus().registerObject("/org/ukui/Sidebar/notification",this,
                                                 QDBusConnection::ExportAllSlots|QDBusConnection::ExportAllSignals);

    //将消息添加到通知中心或收纳盒
    connect(this, SIGNAL(Sig_Notify(QString, QString, QString, QString, QString, QString, QDateTime, int, bool)),
            m_parent, SLOT(onAddSingleNotify(QString, QString, QString, QString, QString, QString, QDateTime, int, bool)));

    connect(this, SIGNAL(Sig_Takein(QString, QString, QString, QString, QString, QString, QDateTime, int, bool)),
            m_parent, SLOT(onTakeInSingleNotify(QString, QString, QString, QString, QString, QString, QDateTime, int, bool)));

    //配置实时关闭通知消息
    connect(this, SIGNAL(Sig_CloseAppMsg(QString)), m_parent, SLOT(onCloseAppMsg(QString)));
    //配置实时更新通知消息最大数
    connect(this, SIGNAL(Sig_UpdateAppMaxNum(QString, int)), m_parent, SLOT(onUpdateAppMaxNum(QString, int)));
}

//创建一条侧边栏通知
void NotificationDbus::sidebarNotification(const QString &appName, const QString &appIcon,
                                           const QString &summary, const QString &body,
                                           const QString &urlStr,  const QString &actions)
{
    qInfo()<<"--------------->"<<appName<<appIcon<<summary<<body<<urlStr<<actions;

    QMap<QString, int>::const_iterator iter = m_nAppMaxNum.find(appName);
    int nMaxNum = 20;
    if ((iter != m_nAppMaxNum.end()) && (iter.value() > 0)) { //找到
        nMaxNum = iter.value();
    }

    QDateTime dateTime(QDateTime::currentDateTime());
    QMap<QString, bool>::const_iterator iter1 = m_mapAppSwitch.find(appName);
    if (iter1 == m_mapAppSwitch.end()) {    //未找到
        emit Sig_Notify(appName, appIcon, summary, body, urlStr, actions, dateTime, nMaxNum, true);
    } else {
        emit Sig_Takein(appName, appIcon, summary, body, urlStr, actions, dateTime, nMaxNum, true);
    }
}

//获取路径并创建gsetting
void NotificationDbus::getSettingsValue()
{
    QList<char*> existsPath = listExistsPath();
    for (char* path : existsPath) {
        char* prepath = QString(NOTICE_ORIGIN_PATH).toLatin1().data();
        char* allpath = strcat(prepath, path);

        const QByteArray ba(NOTICE_ORIGIN_SCHEMA);
        const QByteArray bba(allpath);
        m_pSettings = new QGSettings(ba, bba, this);
        fromSettingsGetInfoToList();
        //监听setting的状态和最大数目改变
        connect(m_pSettings, SIGNAL(changed(const QString &)),this,SLOT(appNotifySettingChangedSlot()));
    }
}

void NotificationDbus::fromSettingsGetInfoToList()
{
    //存储settings,应用名和最大显示数目,以及true
    if (false == m_pSettings->keys().contains(NAME_KEY)) {
        return;
    }
    QString strAppName = m_pSettings->get(NAME_KEY).toString();

    if (m_pSettings->keys().contains(MAXIMINE_KEY)) {
        int maxNum = m_pSettings->get(MAXIMINE_KEY).toInt();
        m_nAppMaxNum.insert(strAppName, maxNum);
    }
    if (m_pSettings->keys().contains(SWITCH_KEY)) {
        powerstatus = m_pSettings->get(SWITCH_KEY).toBool();
        if (false == powerstatus) {
            m_mapAppSwitch.insert(strAppName, powerstatus);
        }
    }
}

void NotificationDbus::appNotifySettingChangedSlot()
{
    int maxNum = 0;
    QString strAppName = "";
    bool status = false;

    if (false == m_pSettings->keys().contains(NAME_KEY)) {
        return;
    }

    strAppName = m_pSettings->get(NAME_KEY).toString();
    if (m_pSettings->keys().contains(MAXIMINE_KEY)) {
        maxNum = m_pSettings->get(MAXIMINE_KEY).toInt();
        m_nAppMaxNum[strAppName] = maxNum;
        emit Sig_UpdateAppMaxNum(strAppName, maxNum);
    }

    if (m_pSettings->keys().contains(SWITCH_KEY)) {
        status = m_pSettings->get(SWITCH_KEY).toBool();
        powerstatus= m_pSettings->get(SWITCH_KEY).toBool();
        QMap<QString, bool>::const_iterator iter1 = m_mapAppSwitch.find(strAppName);
        if (iter1 == m_mapAppSwitch.end()) {    //没找到，没在黑名单
            if(false == status) {
                m_mapAppSwitch.insert(strAppName, status);
                emit Sig_CloseAppMsg(strAppName);              //对于没在黑名单的，新增黑名单关闭消息要求实时更新至通知列表
            }
        } else {
            if (true == status) {
                m_mapAppSwitch.remove(strAppName);
            }
        }
    }
}

//列出存在的路径
QList<char*> NotificationDbus::listExistsPath()
{
    char** childs;
    int len;

    DConfClient * client = dconf_client_new();
    childs = dconf_client_list(client, NOTICE_ORIGIN_PATH, &len);
    g_object_unref(client);

    QList<char*> vals;

    for (int i = 0; childs[i] != NULL; i++) {
        if (dconf_is_rel_dir(childs[i], NULL)) {
            char* val = g_strdup(childs[i]);
            vals.append(val);
        }
    }
    g_strfreev(childs);
    return vals;
}

