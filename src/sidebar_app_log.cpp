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

static int s_logLevel = QtDebugMsg;

void setLogPath(const QString & path)
{
    s_logPath = path;
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

void customLogMessageHandler(QtMsgType type, const QMessageLogContext& ctx, const QString& msg)
{
    Q_UNUSED(ctx);
    if (type < s_logLevel)
    {
        return;
    }

    QString logInfo;
    QString logTime = QDateTime::currentDateTime().toString("hh-mm-ss-MM-dd-yyyy");
    switch (type)
    {
    case QtDebugMsg:
        logInfo = QString("%1 [Debug] %2").arg(logTime, msg);
        break;

    case QtWarningMsg:
        logInfo = QString("%1 [Warning] %2").arg(logTime, msg);
        break;

    case QtCriticalMsg:
        logInfo = QString("%1 [Critical] %2").arg(logTime, msg);
        break;

    case QtFatalMsg:
        logInfo = QString("%1 [Fatal] %2").arg(logTime, msg);
        abort();
    case QtInfoMsg:
        logInfo = QString("%1 [Info] %2").arg(logTime, msg);
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
