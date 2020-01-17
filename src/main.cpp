#include "register_client_to_gnome_session.h"

#include "widget.h"
#include "pluginmanage.h"
#include "sidebar_app_log.h"
#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>
#include <pwd.h>
#include <QMessageLogContext>
#include <QCommandLineParser>
#include <QCommandLineOption>

int main(int argc, char *argv[])
{
    register_client_to_gnome_session ();
    /* 如果系统中有实例在运行则退出 */
    int check_ret = checkProcessRunning(PROGRAM_NAME);
    if (check_ret != 0)
    {
        qDebug() << "此进程正在运行中";
        return check_ret;
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
    qInstallMessageHandler(customLogMessageHandler);                /* 安装日志打印功能 */

//    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
//        QMessageBox::critical(nullptr, QObject::tr("Systray"), QObject::tr("I couldn't detect any system tray " "on this system."));
//        return 1;
//    }

    //加载样式表
    QFile file(QSS_PATH);
    if (file.open(QFile::ReadOnly)) {
        QString strQss = QLatin1String(file.readAll());
        QString strPaletteColor = strQss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(strPaletteColor)));
        qApp->setStyleSheet(strQss);
        file.close();
    }

    QApplication::setQuitOnLastWindowClosed(false);
    PluginManager::init();          /* 初始化插件管理器 */

    Widget w;

    return a.exec();
}
