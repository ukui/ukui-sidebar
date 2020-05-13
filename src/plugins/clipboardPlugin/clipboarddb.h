#ifndef CLIPBOARDDB_H
#define CLIPBOARDDB_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QStandardPaths>
class clipboardDb : public QObject
{
public:
    clipboardDb(QObject *parent = nullptr);
    bool connectClipboardDb(QString DbName);
    bool creatClipboardDbTable(QString DbName);
    void insertSqlClipbarodDb(QString content, QString format, int Sequence);
    void deleteSqlClipboardDb(QString content);
    void updateSqlClipboardDb(QString content, QString format, int Sequence, QString oldcontent);
    int SelectSqlClipbaordDbId();
};

#endif // CLIPBOARDDB_H
