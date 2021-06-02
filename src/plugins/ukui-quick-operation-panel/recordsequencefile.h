#ifndef RECORDSEQUENCEFILE_H
#define RECORDSEQUENCEFILE_H
#include <QMap>
#include <QFile>
#include <QVector>
#include <QMutex>
#include <QDebug>

class RecordSequenceFile : public QObject
{
    Q_OBJECT
private:
    static RecordSequenceFile *m_instance;
    static QMutex m_mutex;        //实例互斥锁。
    RecordSequenceFile();

public:
    static RecordSequenceFile* getInstance(){
        if(!m_instance){
            QMutexLocker locker(&m_mutex);//加互斥锁。
            if(!m_instance){
                RecordSequenceFile *instance = new RecordSequenceFile();
                m_instance = instance;
            }
        }
        return m_instance;
    }
    bool initShortcutMap();
    bool isExist();
    bool readFile(QString filePath,QVector<QMap<QString,QString>> &vector);
    bool writeFile(QString filePath,const QVector<QMap<QString,QString>> vector);
    QVector<QMap<QString,QString>>& getShortcutShowVector();

Q_SIGNALS:
    void orderChange(QVector<QMap<QString,QString>> vector);
public Q_SLOTS:
    void saveOrder(QVector<QMap<QString,QString>> vector);


private:
    QFile *m_file;
    QString m_recordShowPath;
    QString m_recordHidePath;
public:    
    QVector<QMap<QString,QString>> m_shortcutShowVector;
    QVector<QMap<QString,QString>> m_shortcutHideVector; //未添加到显示区的快捷键

};

#endif // RECORDSEQUENCEFILE_H
