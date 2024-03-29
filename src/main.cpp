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
#include "sidebarAppLog.h"
#include <ukui-log4qt.h>
#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <QGuiApplication>
#include <QMessageLogContext>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <X11/Xlib.h>
//#include <KWindowEffects>
#include "sidebarpluginswidgets.h"
#include "smallpluginsmanage.h"
#include "mostgrandwidget.h"
#include "qtsingleapplication.h"

int getScreenWidth() {
    Display *disp = XOpenDisplay(NULL);
    Screen *scrn = DefaultScreenOfDisplay(disp);
    if (NULL == scrn) {
        return 0;
    }
    int width = scrn->width;

    if (NULL != disp) {
        XCloseDisplay(disp);
    }
    return width;
}

int main(int argc, char *argv[])
{
   #if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
       QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
       QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    #endif
    initUkuiLog4qt("ukui-sidebar");
    /* 如果系统中有实例在运行则退出 */
    QString id = QString("ukui-sidebar-" + QLatin1String(getenv("DISPLAY")));
    QtSingleApplication a(id, argc, argv);
    if (a.isRunning()) {
        a.sendMessage(QApplication::arguments().length() > 1 ? QApplication::arguments().at(1) : a.applicationFilePath());
        qDebug() << QObject::tr("ukui-sidebar is already running!");
        return EXIT_SUCCESS;
    } else {
        QCommandLineParser parser;
        QCommandLineOption debugOption({"d", "debug"}, QObject::tr("Display debug information"));
        QCommandLineOption showSidebar({"s", "show"}, QObject::tr("show sidebar widget"));

        parser.addOptions({debugOption, showSidebar});
        parser.process(a);

        if (parser.isSet(debugOption)) {                                    /* 根据命令行设定日志等级 */
            setLogLevel(QtDebugMsg);
            setLogPath(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + LOG_FILE_NAME);  /* 绑定打印日志文件路径 */
            qInstallMessageHandler(customLogMessageHandler);
        } else {
            setLogLevel(QtWarningMsg);
        }

        QApplication::setQuitOnLastWindowClosed(false);
        SmallPluginsManage::SmallPluginsManageInit();                   /* 初始化侧边栏小插件管理容器 */
        PluginManager::init();                                          /* 初始化插件管理器 */
        mostGrandWidget::mostGrandWidgetInit();                         /* 初始化最里层Widget空白界面 */

        bool startOrNot = false;

        Widget *w = new Widget;
        w->setObjectName("SidebarWidget");
        w->setAttribute(Qt::WA_TranslucentBackground);
        mostGrandWidget::getInstancemostGrandWidget()->m_pmostGrandWidgetVLaout->addWidget(w);
        mostGrandWidget::getInstancemostGrandWidget()->LaoutSidebarWidget();
        mostGrandWidget::getInstancemostGrandWidget()->setMostGrandwidgetCoordinates(-500, 0);
        mostGrandWidget::getInstancemostGrandWidget()->setProperty("useSystemStyleBlur", true);
        mostGrandWidget::getInstancemostGrandWidget()->setVisible(true);

        QTimer *startTimer = new QTimer;
        startTimer->setSingleShot(true);

        QObject::connect(w,&Widget::startRun,[=](QSystemTrayIcon::ActivationReason reason){
            qDebug()<<"主动启动";
            startTimer->stop();
            w->startBackgroundFunction();
            QTimer *startTimer = new QTimer;
            startTimer->setSingleShot(true);
            QObject::connect(startTimer,&QTimer::timeout,[=](){
                    w->iconActivated(reason); //设定延时，防止消息界面未完全显示就展示
            });
            startTimer->start(1);
        });

        QObject::connect(startTimer,&QTimer::timeout,[=](){
            qDebug()<<"自发启动";
            w->startBackgroundFunction();
            w->oneShotBool=true;
        });
        startTimer->start(5000);

        QObject::connect(&a, SIGNAL(messageReceived(const QString&)),w, SLOT(bootOptionsFilter(const QString&)));
        return a.exec();
    }
}
