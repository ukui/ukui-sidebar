/*
* Copyright (C) 2020 Tianjin KYLIN Information Technology Co., Ltd.
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

#include <QApplication>

#include "widget.h"
#include "singleApplication.h"
#include "utils/xatom-helper.h"
#include "utils/utils.h"
#include <X11/Xlib.h>
//#include <KWindowEffects>

//SDK统一格式日志
#ifdef KYDEBUG
#include <ukui-log4qt.h>
#endif

/*!
 * \brief myMessageOutput
 * 日志打印输出
 */
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // 加锁
    static QMutex mutex;
    mutex.lock();

    QByteArray localMsg = msg.toLocal8Bit();

    QString strMsg("");
    switch(type)
    {
    case QtDebugMsg:
        strMsg = QString("Debug    ");
        break;
    case QtWarningMsg:
        strMsg = QString("Warning    ");
        break;
    case QtCriticalMsg:
        strMsg = QString("Critical    ");
        break;
    case QtFatalMsg:
        strMsg = QString("Fatal    ");
        break;
    case QtInfoMsg:
        strMsg = QString("Info    ");
        break;
    }

    // 设置输出信息格式
    QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    //QString strMessage = QString("[Message]: %1 [File]: %2  [Line]: %3  [Function]: %4  [DateTime]: %5")
    //        .arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function).arg(strDateTime);
    QString strMessage = QString("[DateTime]: %1  [Message]: %2  [Line]: %3  [Function]: %4")
            .arg(strDateTime).arg(localMsg.constData()).arg(context.line).arg(context.function);

    // 输出信息至文件中（读写、追加形式）
    QString url_filepath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.config/kylin-note/output.log";
    QFile file(url_filepath);
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&file);
    stream << strMsg << strMessage << "\r\n";
    file.flush();
    file.close();

    // 解锁
    mutex.unlock();
}

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

/*!
 * \brief main
 */
int main(int argc, char *argv[])
{
    //自定义消息处理
    //qInstallMessageHandler(myMessageOutput);

    //SDK统一格式日志
    #ifdef KYDEBUG
       initUkuiLog4qt("ukui-notebook");
    #endif

    if (getScreenWidth() > 2560) {
        #if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
                QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
                QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
        #endif
    }

    SingleApplication a(argc, argv);

    a.setWindowIcon(QIcon::fromTheme("kylin-notebook"));
    a.setApplicationVersion ("1.0.0");

    QCommandLineParser parser;
    Utils::setCLIName(parser);
    /* 处理命令行参数。
       除了解析选项（如parse（））外，此函数还处理内置选项并处理错误。
       如果调用了addVersionOption，则内置选项为--version，如果调用了addHelpOption，则为--help --help-all。
       当调用这些选项之一时，或者当发生错误（例如，传递了未知选项）时，当前进程将使用exit（）函数停止。
    */
    parser.process(a);
    Widget w;
    //if (QApplication::arguments().length() > 1) {
    //    if (QApplication::arguments().at(1) == "--display" || QApplication::arguments().at(1) == "-m") {
    //        w.createNewNote();
    //    }
    //}

    if(!a.isRunning()){
        a.w = &w;
        w.setProperty("useSystemStyleBlur", true);
        // 添加窗管协议
        MotifWmHints hints;
        hints.flags = MWM_HINTS_FUNCTIONS|MWM_HINTS_DECORATIONS;
        hints.functions = MWM_FUNC_ALL;
        hints.decorations = MWM_DECOR_BORDER;
        XAtomHelper::getInstance()->setWindowMotifHint(w.winId(), hints);
        //w.setAttribute(Qt::WA_TranslucentBackground);
        //KWindowEffects::enableBlurBehind(w.winId(),true);

        QObject::connect(&a, SIGNAL(messageReceived(/*const QString&*/)), &w, SLOT(sltMessageReceived(/*const QString&*/)));

        return a.exec();
    }
    return 0;
}
