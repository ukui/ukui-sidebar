#include "recordsequencefile.h"
#include <QDir>
#include <QDebug>




RecordSequenceFile *RecordSequenceFile::m_instance = 0;
QMutex RecordSequenceFile::m_mutex;

RecordSequenceFile::RecordSequenceFile()
{
    m_recordShowPath = QDir::homePath() + "/.config/sidebarRecordShow";
    m_recordHidePath = QDir::homePath() + "/.config/sidebarRecordHide";
    initshortcutClassName();
    initShortcutMap();
    m_hoverIndex = -1;
    m_hoverStatus = false;

    connect(this, SIGNAL(orderChange(QVector<QMap<QString,QString>>)),this,SLOT(saveOrder(QVector<QMap<QString,QString>>)));
}

bool RecordSequenceFile::initShortcutMap()
{
    //初始化shortcutShowVector和sidebarRecordShow文件
    if(QFile::exists(m_recordShowPath)){
        if(!readFile(m_recordShowPath,m_shortcutShowVector)){  //解析sidebarRecordShow文件，输出到shortcutShowMap中
            qDebug()<<"init m_shortcutShowVector read failed！";
            return false;
        }
    }
    else{
        //初始化shortcutShowVector，输出sidebarRecordShow文件中
        QMap<QString,QString> shortcutShowMap;
        shortcutShowMap.clear();
        shortcutShowMap.insert(TABLE_MODE_NAME,TABLE_MODE_ICON);
        m_shortcutShowVector.append(shortcutShowMap);
        shortcutShowMap.clear();
        shortcutShowMap.insert(NO_DISTURBING_NAME,NO_DISTURBING_ICON);
        m_shortcutShowVector.append(shortcutShowMap);
        shortcutShowMap.clear();
        shortcutShowMap.insert(ENERGY_SAVING_NAME,ENERGY_SAVING_ICON);
        m_shortcutShowVector.append(shortcutShowMap);
        shortcutShowMap.clear();
        shortcutShowMap.insert(EYE_CARE_NAME,EYE_CARE_ICON);
        m_shortcutShowVector.append(shortcutShowMap);
        shortcutShowMap.clear();
        shortcutShowMap.insert(BLUETOOTH_NAME,BLUETOOTH_ICON);
        m_shortcutShowVector.append(shortcutShowMap);
        shortcutShowMap.clear();
        shortcutShowMap.insert(HOTSPOT_NAME,HOTSPOT_icon);
        m_shortcutShowVector.append(shortcutShowMap);
        shortcutShowMap.clear();
        shortcutShowMap.insert(VPN_NAME,VPN_ICON);
        m_shortcutShowVector.append(shortcutShowMap);
        shortcutShowMap.clear();
        shortcutShowMap.insert(SETTING_NAME,SETTING_ICON);
        m_shortcutShowVector.append(shortcutShowMap);
        shortcutShowMap.clear();
        shortcutShowMap.insert(CALCULATOR_NAME,CALCULATOR_ICON);
        m_shortcutShowVector.append(shortcutShowMap);
        shortcutShowMap.clear();
        shortcutShowMap.insert(SCREENSHOTS_NAME,SCREENSHOTS_ICON);
        m_shortcutShowVector.append(shortcutShowMap);
        shortcutShowMap.clear();
        shortcutShowMap.insert(ALARM_NAME,ALARM_ICON);
        m_shortcutShowVector.append(shortcutShowMap);
        shortcutShowMap.clear();
        shortcutShowMap.insert(NOTEBOOK_NAME,NOTEBOOK_ICON);
        m_shortcutShowVector.append(shortcutShowMap);

        if(!writeFile(m_recordShowPath, m_shortcutShowVector)){
            qDebug()<<"init m_shortcutShowVector write failed！";
            return false;
        }
    }
}

bool RecordSequenceFile::initshortcutClassName()
{
//    shortcutShowMap.insert(TABLE_MODE_NAME,TABLE_MODE_ICON);
//    shortcutShowMap.insert(NO_DISTURBING_NAME,NO_DISTURBING_ICON);
//    shortcutShowMap.insert(ENERGY_SAVING_NAME,ENERGY_SAVING_ICON);
//    shortcutShowMap.insert(EYE_CARE_NAME,EYE_CARE_ICON);
//    shortcutShowMap.insert(BLUETOOTH_NAME,BLUETOOTH_ICON);
//    shortcutShowMap.insert(HOTSPOT_NAME,HOTSPOT_icon);
//    shortcutShowMap.insert(VPN_NAME,VPN_ICON);
//    shortcutShowMap.insert(SETTING_NAME,SETTING_ICON);
//    shortcutShowMap.insert(CALCULATOR_NAME,CALCULATOR_ICON);
    m_shortcutClassName.insert(SCREENSHOTS_NAME,SCREENSHOTS_CLASS_NAME);
    m_shortcutClassName.insert(ALARM_NAME,ALARM_CLASS_NAME);
//    shortcutShowMap.insert(NOTEBOOK_NAME,NOTEBOOK_ICON);
}


bool RecordSequenceFile::isExist()
{
}

bool RecordSequenceFile::readFile(QString filePath, QVector<QMap<QString,QString>> &vector)
{
        QFile file(filePath);
        if(!file.open(QFile::ReadOnly| QFile::Text)){
            qDebug()<<"read open false";
            return false;
        }
        QString fileDate = QString(file.readAll());
        QList<QString> fileList = fileDate.split(";");
        fileList.removeLast();
        vector.clear();
        for(int i=0; i<fileList.size(); i++){
            QStringList currList = fileList.at(i).split(",");
            QMap<QString,QString> map;
            map.insert(QString(currList.at(0)),QString(currList.at(1)));
            vector.append(map);
        }

        return true;
}

/*存放格式如下:
Alarm,:/images/icon-alarm.svg;
NoteBook,:/images/icon-notes.svg;
*/
bool RecordSequenceFile::writeFile(QString filePath, const QVector<QMap<QString,QString>> vector)
{
    qDebug()<<"---writeFile:"<<filePath;
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly | QFile::Text)){
        qDebug()<<"---write open false";
        return false;
    }

    for (int i = 0; i < vector.size(); ++i) {
        QString key = vector.at(i).begin().key();
        QString value = vector.at(i).begin().value();
        QString str = key + "," + value + ";";
        file.write(str.toUtf8());
    }
    file.close();
        return true;
}

QVector<QMap<QString, QString>> &RecordSequenceFile::getShortcutShowVector()
{
    return m_shortcutShowVector;
}

//次序改变时(增、删、改),更新存储文件内容
void RecordSequenceFile::saveOrder(QVector<QMap<QString,QString>> vector)
{
    m_shortcutShowVector = vector;
    if(!writeFile(m_recordShowPath, vector)){
        return;
    }
}






