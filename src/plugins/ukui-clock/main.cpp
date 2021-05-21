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
#include "clock.h"
#include "singleApplication.h"
#include <QApplication>
#include <QDesktopWidget>
#include <X11/Xlib.h>
#include "xatom-helper.h"

/*!
 * \brief myMessageOutput
 * 日志打印输出
 */
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // 加锁
    static QMutex mutex;
    mutex.lock();
//    qDebug()<<msg;
    QByteArray localMsg = msg.toLocal8Bit();

    QString strMsg("");
    switch (type) {
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
    QString strMessage = QString("[DateTime]: %1  [Message]: %2  [Line]: %3  [Function]: %4")
                         .arg(strDateTime).arg(localMsg.constData()).arg(context.line).arg(
        context.function);

    QString dirStr = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
                     + "/.config/kylin-clock/";
    QDir dir;
    if (!dir.exists(dirStr)) {
        dir.mkpath(dirStr);
    }
    // 输出信息至文件中（读写、追加形式）
    QString url_filepath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
                           + "/.config/kylin-clock/output.log";
    QFile file(url_filepath);

    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&file);
    stream << strMsg << strMessage << "\r\n";
    file.flush();
    file.close();

    // 解锁
    mutex.unlock();
}

int main(int argc, char *argv[])
{
    // 自定义消息处理
    qInstallMessageHandler(myMessageOutput);
    //适配分数缩放
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 12, 0))
        QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    #endif
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
        QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    #endif

    //构造单例 利用本地连接qlocalsocket作为判断的公共访问资源
    SingleApplication a(argc, argv);
    //支持主题框架图标
     a.setWindowIcon(QIcon::fromTheme("kylin-alarm-clock"));
    //此属性保存关闭最后一个窗口时应用程序是否隐式退出。默认值为true。
    a.setQuitOnLastWindowClosed(false);
    //如果没在运行
    if (!a.isRunning()) {
        Clock w;
        a.w = &w;

        // 添加窗管协议。显示的位置
        MotifWmHints hints;
        hints.flags = MWM_HINTS_FUNCTIONS|MWM_HINTS_DECORATIONS;
        hints.functions = MWM_FUNC_ALL;
        hints.decorations = MWM_DECOR_BORDER;
        XAtomHelper::getInstance()->setWindowMotifHint(w.winId(), hints);
        w.show();
        return a.exec();
    }
    return 0;
}
