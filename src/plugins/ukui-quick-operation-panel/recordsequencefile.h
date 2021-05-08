#ifndef RECORDSEQUENCEFILE_H
#define RECORDSEQUENCEFILE_H
#include <QMap>
#include <QFile>

class RecordSequenceFile
{
public:
    RecordSequenceFile();
    void initShortcutMap();
    bool creatorRecordFile();
    bool isExist();
    bool readFile(QString filePath,QMap<QString,QString> map);
    bool writeFile(QString filePath,QMap<QString,QString> map);

private:
    QFile *file;
    QString recordShowPath;
    QString recordHidePath;
public:    
    QMap<QString,QString> shortcutShowMap;
    QMap<QString,QString> shortcutHideMap; //未添加到显示区的快捷键

};

#endif // RECORDSEQUENCEFILE_H
