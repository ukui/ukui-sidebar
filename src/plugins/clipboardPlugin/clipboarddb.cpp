#include "clipboarddb.h"

clipboardDb::clipboardDb(QObject *parent)
{
    Q_UNUSED(parent);
    QString url_filepath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) +"/.config/Clipboard.db";
    if (!connectClipboardDb(url_filepath)) {  //链接数据库
        qWarning() << "创建数据库失败";
        return;
    }
    creatClipboardDbTable(url_filepath); //创建表格
}

/* 链接数据库 */
bool clipboardDb::connectClipboardDb(QString DbName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", DbName);
    db.setDatabaseName(DbName);
    if (!db.open()) {
        qDebug() << "打开数据失败,返回false";
        return false;
    }
    return true;
}

/* 创建数据 */
bool clipboardDb::creatClipboardDbTable(QString DbName)
{
    QSqlQuery query(QSqlDatabase::database(DbName));
    QString creatorSqlState = "CREATE TABLE Clipboard_table ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "content TEXT UNIQUE NOT NULL,"
                              "format TEXT NOT NULL,"
                              "Sequence INTEGER NOT NULL"
                              ");";

    query.exec(creatorSqlState);
    qDebug()<<"-------------------------------------creatorSqlState";
    return true;
}

/* 增 */
void clipboardDb::insertSqlClipbarodDb(QString content, QString format, int Sequence)
{
    QString url_filepath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) +"/.config/Clipboard.db";
    QSqlQuery query(QSqlDatabase::database(url_filepath));
    QString insertSql = QStringLiteral("INSERT INTO Clipboard_table (content, format, Sequence) VALUES ('%1','%2',%3)").arg(content).arg(format).arg(Sequence);
    if (!query.exec(insertSql)) {
        qDebug() << "数据插入错误";
    }
    query.finish();
    return;
}

/* 删 */
void clipboardDb::deleteSqlClipboardDb(QString content)
{
    QString url_filepath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) +"/.config/Clipboard.db";
    QSqlQuery query(QSqlDatabase::database(url_filepath));
    QString deleteSql = QStringLiteral("DELETE FROM Clipboard_table WHERE content='%1'").arg(content);
    if (!query.exec(deleteSql)) {
        qDebug() << "删除操作失败";
        return;
    }
    query.finish();
    return;
}

/* 改 */
void clipboardDb::updateSqlClipboardDb(QString content, QString format, int Sequence, QString oldcontent)
{
    QString url_filepath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) +"/.config/Clipboard.db";
    QSqlQuery query(QSqlDatabase::database(url_filepath));
    QString updateSql = QStringLiteral("UPDATE Clipboard_table SET content='%1',format='%2',Sequence=%3 WHERE content='%4'")
            .arg(content)
            .arg(format)
            .arg(Sequence)
            .arg(oldcontent);
    if(!query.exec(updateSql)) {
        qDebug() << "更新操作失败";
        return;
    }
    query.finish();
    return;
}

/* 查Id */
int clipboardDb::SelectSqlClipbaordDbId()
{
    QString url_filepath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) +"/.config/Clipboard.db";
    QSqlQuery query(QSqlDatabase::database(url_filepath));
    QString SelectSql = QStringLiteral("SELECT MAX(ID) from Clipboard_table");
    if (!query.exec(SelectSql)) {
        qWarning() << "查询操作失败";
        return -1;
    }
    int seq;
    while (query.next()) {
       seq = query.value(0).toDouble();
    }
    return seq;
}
