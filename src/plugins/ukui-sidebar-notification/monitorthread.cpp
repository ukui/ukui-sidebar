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

#include "monitorthread.h"
#include "notificationPlugin.h"
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
#define NAME_KEY "name"

MonitorThread::MonitorThread(NotificationPlugin *parent)
{
    m_parent = parent;

    this->moveToThread(this);
}

void MonitorThread::extractData(QString strOutput)
{
    QString strOutputTmp = strOutput;

    //app名的获取
    int nIndex = strOutputTmp.indexOf("\"");
    if (-1 == nIndex) {
        return;
    }

    strOutputTmp = strOutputTmp.mid(nIndex + 1);
    nIndex = strOutputTmp.indexOf("\"");
    if (-1 == nIndex) {
        return;
    }
    QString strAppName = strOutputTmp.mid(0, nIndex);
    strOutputTmp = strOutputTmp.mid(nIndex + 1);
    //检查电源信息是否被禁用
    if ("电源管理" == strAppName) {
        if (!powerstatus) {
            qDebug()<<"电源通知已禁用";
            return;
        }
        qDebug()<<"电源通知未禁用";
    }
    if ("notify-send" == strAppName) {
        strAppName = "未知来源";
    }
    //图标路径的获取
    nIndex = strOutputTmp.indexOf("\"");
    if (-1 == nIndex) {
        return;
    }
    strOutputTmp = strOutputTmp.mid(nIndex + 1);
    nIndex = strOutputTmp.indexOf("\"");
    if (-1 == nIndex) {
        return;
    }
    QString strIcon = strOutputTmp.mid(0, nIndex);
    strOutputTmp = strOutputTmp.mid(nIndex + 1);

    if ("" == strIcon) {
        strIcon = "/usr/share/icons/ukui-icon-theme-default/24x24/mimetypes/application-x-desktop.png";
    }

    //主题的获取
    nIndex = strOutputTmp.indexOf("\"");
    if (-1 == nIndex) {
        return;
    }
    strOutputTmp = strOutputTmp.mid(nIndex + 1);
    nIndex = strOutputTmp.indexOf("\"");
    if (-1 == nIndex) {
        return;
    }
    QString strSummary = strOutputTmp.mid(0, nIndex);
    strOutputTmp = strOutputTmp.mid(nIndex + 1);

    //正文的获取
    nIndex = strOutputTmp.indexOf("\"");
    if (-1 == nIndex) {
        return;
    }
    strOutputTmp = strOutputTmp.mid(nIndex + 1);
    nIndex = strOutputTmp.indexOf("\"");
    if (-1 == nIndex) {
        return;
    }
    QString strBody = strOutputTmp.mid(0, nIndex);
    strOutputTmp = strOutputTmp.mid(nIndex + 1);

    QMap<QString, int>::const_iterator iter = m_nAppMaxNum.find(strAppName);
    int nMaxNum = 20;

    if ((iter != m_nAppMaxNum.end()) && (iter.value() > 0)) { //找到
        nMaxNum = iter.value();
    }

    QDateTime dateTime(QDateTime::currentDateTime());

    QMap<QString, bool>::const_iterator iter1 = m_mapAppSwitch.find(strAppName);
    if (iter1 == m_mapAppSwitch.end()) {    //未找到
        emit Sig_Notify(strAppName, strIcon, strSummary, strBody, dateTime, nMaxNum, true);
    } else {
        emit Sig_Takein(strAppName, strIcon, strSummary, strBody, dateTime, nMaxNum, true);
    }

    return;
}

//获取路径并创建gsetting
void MonitorThread::getSettingsValue()
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

void MonitorThread::fromSettingsGetInfoToList()
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
        qDebug()<<"初始电源通知状态:"<<powerstatus;
        if (false == powerstatus) {
            m_mapAppSwitch.insert(strAppName, powerstatus);
        }
    }
}

//列出存在的路径
QList<char*> MonitorThread::listExistsPath()
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

void MonitorThread::appNotifySettingChangedSlot()
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
        qDebug()<<"电源统计状态更改为："<<powerstatus;
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

void MonitorThread::readOutputData()
{
    QByteArray output = m_pProcess->readAllStandardOutput();

    if (false == m_bEnabled) {  //上面的内容必须读空再返回，不然就一直有缓存
        return;
    }

    QString str_output = output;

    if (str_output.isEmpty()) {
        return;
    }

    int nIndex = 0;
    do {
        nIndex = str_output.indexOf("member=Notify");
        if (-1 == nIndex) {
            break;
        }
        str_output = str_output.mid(nIndex + 13);
        extractData(str_output);

    } while (str_output.size() > 0);

    return;
}

void MonitorThread::switchEnable(bool bEnabled)
{
    if (m_bEnabled != bEnabled) {
        m_bEnabled = bEnabled;
    }
}

void MonitorThread::run()
{
    getSettingsValue();
    system("killall dbus-monitor");
    m_pProcess = new QProcess(this);
    m_pProcess->start("dbus-monitor interface=org.freedesktop.Notifications");

    QTimer* pTimer = new QTimer(this);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(readOutputData()));
    pTimer->start(1000);

    //将消息添加到通知中心或收纳盒
    connect(this, SIGNAL(Sig_Notify(QString, QString, QString, QString, QDateTime, int, bool)), m_parent, SLOT(onAddSingleNotify(QString, QString, QString, QString, QDateTime, int, bool)));

    connect(this, SIGNAL(Sig_Takein(QString, QString, QString, QString, QDateTime, int, bool)), m_parent, SLOT(onTakeInSingleNotify(QString, QString, QString, QString, QDateTime, int, bool)));

    //配置实时关闭通知消息
    connect(this, SIGNAL(Sig_CloseAppMsg(QString)), m_parent, SLOT(onCloseAppMsg(QString)));
    //配置实时更新通知消息最大数
    connect(this, SIGNAL(Sig_UpdateAppMaxNum(QString, int)), m_parent, SLOT(onUpdateAppMaxNum(QString, int)));

    exec();

}
