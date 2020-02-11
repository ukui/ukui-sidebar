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

#ifndef MONITORTHREAD_H
#define MONITORTHREAD_H

#include <QThread>
class NotificationPlugin;
class QProcess;
class QTimer;

class MonitorThread : public QThread
{
    Q_OBJECT
public:
    MonitorThread(NotificationPlugin *parent);
    ~MonitorThread();
    void run();//线程入口函数（工作线程的主函数）
    void extractData(QString strOutput);

private:
    NotificationPlugin* m_parent;
    QProcess*           m_pProcess;
    QTimer*             m_pTimer;

signals:
    void Sig_Notify(QString, QString, QString, QString);

public slots:
    void readOutputData();
};

#endif // MONITORTHREAD_H
