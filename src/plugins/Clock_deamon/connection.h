#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStandardPaths>

static bool createConnection()
{

    QString url_filepath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) +"/.config/ukui/Clock_database.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(url_filepath);

    if(!db.open()) return false;

    QSqlQuery query;
    query.exec(QString(
      "create table clock (Hour int, Minute int, Music QString, onoroff int, NUM int, repeat Qstring, \
                           Monday int, Tuesday int, Wednesday int, Thursday int, Friday int, Saturday int ,Sunday int, \
                            Musictime QString, Name Qstring)"));
    return true;
}

#endif // CONNECTION_H
