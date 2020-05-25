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
#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H

#include <QObject>
#include <QApplication>
#include <QtNetwork/QLocalServer>
#include "clock.h"

class SingleApplication : public QApplication {
    Q_OBJECT
public:
    SingleApplication(int &argc, char **argv);

    bool isRunning();              //是否已经有实例在运行
                                   //  Whether an instance is already running
    Clock *w;                      // Widget指针
                                   // Widget pointer

private slots:
    // 有新连接时触发
    // Triggered when there is a new connection
    void _newLocalConnection();

private:
    // 初始化本地连接
    // Initialize local connection
    void _initLocalConnection();
    // 创建服务端
    // Create server
    void _newLocalServer();
    // 激活窗口
    // Activate window
    void _activateWindow();

    bool _isRunning;                // 是否已經有实例在运行
                                    // Whether an instance is already running
    QLocalServer *_localServer;     // 本地socket Server
                                    // Local socket server
    QString _serverName;            // 服务名称
                                    // Service name
};


#endif // SINGLEAPPLICATION_H
