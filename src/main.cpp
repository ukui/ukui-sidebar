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


#include "widget.h"
#include "pluginmanage.h"
#include "sidebar_app_log.h"
#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <QMessageLogContext>
#include <QCommandLineParser>
#include <QCommandLineOption>

int main(int argc, char *argv[])
{
    /* 如果系统中有实例在运行则退出 */
    int fd = open("/tmp/ukui-sidebar-lock", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0)
    {
        exit(1);
    }

    if (lockf(fd, F_TLOCK, 0))
    {
        syslog(LOG_ERR, "Can't lock single file, ukui-sidebar is already running!");
        qDebug()<<"Can't lock single file, ukui-sidebar is already running!";
        exit(0);
    }

    QApplication a(argc, argv);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QCommandLineParser parser;
    QCommandLineOption debugOption({"d", "debug"}, QObject::tr("Display debug information"));


    parser.addOptions({debugOption});
    parser.process(a);

    if(parser.isSet(debugOption))
        setLogLevel(QtDebugMsg);                                    /* 根据命令行设定日志等级 */
    else
        setLogLevel(QtWarningMsg);

    QString LogFilePath = QCoreApplication::applicationDirPath();   /* 获取文件运行的当前路径 */
    setLogPath(LogFilePath + LOG_FILE_NAME);                        /* 绑定打印日志文件路径 */
//    qInstallMessageHandler(customLogMessageHandler);                /* 安装日志打印功能 */


    qApp->setPalette(QPalette(QColor("#131314")));

    QApplication::setQuitOnLastWindowClosed(false);
    PluginManager::init();          /* 初始化插件管理器 */

    Widget w;

    QDBusConnection connection = QDBusConnection::sessionBus();
    if(!connection.registerService("com.ukui.panel.sidebar"))
    {
        qDebug() << "error:" << connection.lastError().message();
    }
    connection.registerObject("/getvalue/panel", &w, QDBusConnection::ExportAllSlots);

    return a.exec();
}
