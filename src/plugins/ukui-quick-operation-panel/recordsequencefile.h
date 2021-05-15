#ifndef RECORDSEQUENCEFILE_H
#define RECORDSEQUENCEFILE_H
#include <QMap>
#include <QFile>
#include <QVector>

class RecordSequenceFile
{
public:
    RecordSequenceFile();
    void initShortcutMap();
    bool creatorRecordFile();
    bool isExist();
    bool readFile(QString filePath,QVector<QMap<QString,QString>> vector);
    bool writeFile(QString filePath,QVector<QMap<QString,QString>> vector);

private:
    QFile *file;
    QString recordShowPath;
    QString recordHidePath;
public:    
    QVector<QMap<QString,QString>> shortcutShowVector;
    QVector<QMap<QString,QString>> shortcutHideVector; //未添加到显示区的快捷键

};

#endif // RECORDSEQUENCEFILE_H
