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
#include "sidebarpluginswidgets.h"
#include "smallpluginsmanage.h"
#include "mostgrandwidget.h"
int main(int argc, char *argv[])
{
    /* 如果系统中有实例在运行则退出 */
    QStringList strlistHomePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
    QString strLockPath = strlistHomePath.at(0) + "/.config/ukui-sidebar";

    int fd = open(strLockPath.toUtf8().data(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
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
    {
        setLogLevel(QtDebugMsg);                                    /* 根据命令行设定日志等级 */
    }
    else
    {
        setLogLevel(QtWarningMsg);
    }

    QString LogFilePath = QCoreApplication::applicationDirPath();   /* 获取文件运行的当前路径 */
    setLogPath(LogFilePath + LOG_FILE_NAME);                        /* 绑定打印日志文件路径 */

    QApplication::setQuitOnLastWindowClosed(false);
    SmallPluginsManage::SmallPluginsManageInit();                   /* 初始化侧边栏小插件管理容器 */
    PluginManager::init();                                          /* 初始化插件管理器 */
    mostGrandWidget::mostGrandWidgetInit();                         /* 初始化最里层Widget空白界面 */


    Widget *w = new Widget;
    w->setObjectName("SidebarWidget");
    w->setAttribute(Qt::WA_TranslucentBackground);
    mostGrandWidget::getInstancemostGrandWidget()->m_pmostGrandWidgetVLaout->addWidget(w);

    mostGrandWidget::getInstancemostGrandWidget()->LaoutSidebarWidget();
    mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetCoordinates(-500, 0);
    mostGrandWidget::getInstancemostGrandWidget()->setVisible(true);
    return a.exec();
}
