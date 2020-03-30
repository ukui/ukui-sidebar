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
#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QObject>
#include <QStandardPaths>
#include "feedback.h"


static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString db_filepath;
    db_filepath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) +"/.config/ukui/.database_feedback.db";
    db.setDatabaseName(db_filepath);

    if(!db.open()) return false;

    QSqlQuery query;
    query.exec(QString(
                    "create table clock (Hour QString, Music QString,Filename Qstring)")); //提示：主键不能相同

    return true;
}

\
#endif // DATABASE_H
