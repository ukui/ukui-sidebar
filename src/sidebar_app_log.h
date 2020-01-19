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


#include <QMutex>
#include <QString>

#define LOG_FILE_NAME QString("/SidebarLog/") + QDateTime::currentDateTime().toString("yyyy-MM-dd") + QString(".log")


static QMutex s_logMutex;
static QString s_logPath;

void setLogPath(const QString &path);
void setLogLevel(int level);
void customLogMessageHandler(QtMsgType type, const QMessageLogContext& ctx, const QString& msg);
