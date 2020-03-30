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
#include "notification_plugin.h"


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
    if(-1 == nIndex)
    {
        return;
    }
    strOutputTmp = strOutputTmp.mid(nIndex + 1);
    nIndex = strOutputTmp.indexOf("\"");
    if(-1 == nIndex)
    {
        return;
    }
    QString strAppName = strOutputTmp.mid(0, nIndex);
    strOutputTmp = strOutputTmp.mid(nIndex + 1);
    if("notify-send" == strAppName)
    {
        strAppName = "未知来源";
    }

    //图标路径的获取
    nIndex = strOutputTmp.indexOf("\"");
    if(-1 == nIndex)
    {
        return;
    }
    strOutputTmp = strOutputTmp.mid(nIndex + 1);
    nIndex = strOutputTmp.indexOf("\"");
    if(-1 == nIndex)
    {
        return;
    }
    QString strIcon = strOutputTmp.mid(0, nIndex);
    strOutputTmp = strOutputTmp.mid(nIndex + 1);

    if("" == strIcon)
    {
        strIcon = "/usr/share/icons/ukui-icon-theme/24x24/mimetypes/application-x-desktop.png";
    }

    //主题的获取
    nIndex = strOutputTmp.indexOf("\"");
    if(-1 == nIndex)
    {
        return;
    }
    strOutputTmp = strOutputTmp.mid(nIndex + 1);
    nIndex = strOutputTmp.indexOf("\"");
    if(-1 == nIndex)
    {
        return;
    }
    QString strSummary = strOutputTmp.mid(0, nIndex);
    strOutputTmp = strOutputTmp.mid(nIndex + 1);

    //正文的获取
    nIndex = strOutputTmp.indexOf("\"");
    if(-1 == nIndex)
    {
        return;
    }
    strOutputTmp = strOutputTmp.mid(nIndex + 1);
    nIndex = strOutputTmp.indexOf("\"");
    if(-1 == nIndex)
    {
        return;
    }
    QString strBody = strOutputTmp.mid(0, nIndex);
    strOutputTmp = strOutputTmp.mid(nIndex + 1);

    QDateTime dateTime(QDateTime::currentDateTime());
    emit Sig_Notify(strAppName, strIcon, strSummary, strBody, dateTime, true);
    return;
}


void MonitorThread::readOutputData()
{
    QByteArray output = m_pProcess->readAllStandardOutput();
    QString str_output = output;
    if(str_output.isEmpty())
    {
        return;
    }
    //qDebug()<<str_output;

    int nIndex = 0;
    do{
        nIndex = str_output.indexOf("member=Notify");
        if(-1 == nIndex)
        {
            break;
        }
        str_output = str_output.mid(nIndex + 13);
        extractData(str_output);

    }while(str_output.size() > 0);

    return;
}

void MonitorThread::run()
{
    system("killall dbus-monitor");
    m_pProcess = new QProcess();
    m_pProcess->start("dbus-monitor interface=org.freedesktop.Notifications");

    QTimer* pTimer = new QTimer();
    connect(pTimer, SIGNAL(timeout()), this, SLOT(readOutputData()));
    pTimer->start(1000);

    connect(this, SIGNAL(Sig_Notify(QString, QString, QString, QString, QDateTime, bool)), m_parent, SLOT(onAddSingleNotify(QString, QString, QString, QString, QDateTime, bool)));
    exec();

}
