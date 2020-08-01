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
#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStandardPaths>
//创建或打开数据库
//Create or open database
static bool createConnection()
{

    QString url_filepath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) +"/.config/Clock_database.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(url_filepath);

    if(!db.open()) return false;

    QSqlQuery query;
    query.exec(QString(
                   "create table clock (Hour int, Minute int, Music QString, onoroff int, NUM int, repeat Qstring,Monday int, Tuesday int, Wednesday int, Thursday int, Friday int, Saturday int , Sunday int, Musictime QString, Name Qstring)"));
               QSqlQuery query_setup;
            query_setup.exec(QString(
                                 "create table setup (selfstart int, Mutestart int, Timeformat int,Popupwindow int, Reminderoff int, Defaultringtone string, volume int, Monday int, Tuesday int, Wednesday int, Thursday int, Friday int, Saturday int ,Sunday int, repeat Qstring, Time Qstring, window Qstring, Reminder Qstring , volume2 int, count_music_str QString)"));
                      QSqlQuery query_stop;
            query_stop.exec(QString(
                                    "create table Stopwatch (num int, stopwatch_h int, stopwatch_m int, stopwatch_s int, stopwatch_jg_h int, stopwatch_jg_m int, stopwatch_jg_s int)"));

            return true;
}

#endif // CONNECTION_H
