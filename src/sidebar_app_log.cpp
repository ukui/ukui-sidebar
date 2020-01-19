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


#include "sidebar_app_log.h"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
static int s_logLevel = QtDebugMsg;

void setLogPath(const QString & path)
{
    s_logPath = path;
    qDebug() << "path ::::" << s_logPath;
}

void setLogLevel(int level)
{
    s_logLevel = level;
}

bool static ensureDirExist(const QString &dirPath)
{
    QDir dir(dirPath);
    if (dir.exists())
    {
        return true;
    }

    return dir.mkpath(dirPath);
}

void customLogMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    Q_UNUSED(context);
    if (type < s_logLevel)
    {
        return;
    }

    QString logInfo;
    QString logTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
    switch (type)
    {
    case QtDebugMsg:
        logInfo = QString("%1 [Debug] %2 %3 %4 %5").arg(logTime, context.file, QString::number(context.line), context.function, msg);
        break;

    case QtWarningMsg:
        logInfo = QString("%1 [Warning] %2 %3 %4 %5").arg(logTime, context.file, QString::number(context.line), context.function, msg);
        break;

    case QtCriticalMsg:
        logInfo = QString("%1 [Critical] %2 %3 %4 %5").arg(logTime, context.file, QString::number(context.line), context.function, msg);
        break;

    case QtFatalMsg:
        logInfo = QString("%1 [Fatal] %2 %3 %4 %5").arg(logTime, context.file, QString::number(context.line), context.function, msg);
        abort();
    case QtInfoMsg:
        logInfo = QString("%1 [Info] %2 %3 %4 %5").arg(logTime, context.file, QString::number(context.line), context.function, msg);
        break;
    }

    s_logMutex.lock();
    QFile outFile(s_logPath);
    QFileInfo fileInfo(outFile);
    if (!ensureDirExist(fileInfo.absoluteDir().absolutePath()))
        return;

    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        return;

    QTextStream ts(&outFile);
    ts << logInfo.toUtf8() << endl;
    outFile.close();
    s_logMutex.unlock();
}
