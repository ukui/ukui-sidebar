#include "recordsequencefile.h"
#include <QDir>
#include <QDebug>



#define TABLE_MODE_NAME     "Tablet Mode"
#define TABLE_MODE_ICON     ":/images/icon-PC-mode.svg"
#define NO_DISTURBING_NAME  "No disturbing"
#define NO_DISTURBING_ICON  ":/images/icon-DND.svg"
#define ENERGY_SAVING_NAME  "Energy-saving"
#define ENERGY_SAVING_ICON  ":/images/icon-powersavingmode.svg"
#define EYE_CARE_NAME       "Eye care"
#define EYE_CARE_ICON       ":/images/icon-eyeprotectionmode.svg"
#define BLUETOOTH_NAME      "Bluetooth"
#define BLUETOOTH_ICON      ":/image/bluetooth-normal.svg"
#define HOTSPOT_NAME        "Hotspot"
#define HOTSPOT_icon        ":/images/icon-hotspot.svg"
#define VPN_NAME            "VPN"
#define VPN_ICON            ":/images/icon-VPN.svg"
#define SETTING_NAME        "Setting"
#define SETTING_ICON        ":/images/icon-setting.svg"
#define CALCULATOR_NAME     "Calculator"
#define CALCULATOR_ICON     ":/images/icon-calculator.svg"
#define SCREENSHOTS_NAME    "Screenshots"
#define SCREENSHOTS_ICON    ":/images/icon-screenshot.svg"
#define ALARM_NAME          "Alarm"
#define ALARM_ICON          ":/images/icon-alarm.svg"
#define NOTEBOOK_NAME       "NoteBook"
#define NOTEBOOK_ICON       ":/images/icon-notes.svg"
#define FEEDBACK_NAME       "Feedback"
#define FEEDBACK_ICON       ":/images/icon-alarm.svg"
#define WIFI_NAM            "Wifi"
#define WIFI_ICON           ":/image/wifi-normal.svg"




RecordSequenceFile::RecordSequenceFile()
{
    recordShowPath = QDir::homePath() + "/.config/sidebarRecordShow";
    recordHidePath = QDir::homePath() + "/.config/sidebarRecordHide";
    initShortcutMap();
}

void RecordSequenceFile::initShortcutMap()
{
    //初始化shortcutShowMap和sidebarRecordShow文件
    if(QFile::exists(recordShowPath)){
        //解析sidebarRecordShow文件，输出到shortcutShowMap中
        if(readFile(recordShowPath,shortcutShowMap)){
            qDebug()<<"初始化shortcutShowMap read失败！";
            return;
        }
    }
    else{
        //初始化shortcutShowMap，输出sidebarRecordShow文件中
        shortcutShowMap.clear();
        shortcutShowMap.insert(TABLE_MODE_NAME,TABLE_MODE_ICON);
        shortcutShowMap.insert(NO_DISTURBING_NAME,NO_DISTURBING_ICON);
        shortcutShowMap.insert(ENERGY_SAVING_NAME,ENERGY_SAVING_ICON);
        shortcutShowMap.insert(EYE_CARE_NAME,EYE_CARE_ICON);
        shortcutShowMap.insert(BLUETOOTH_NAME,BLUETOOTH_ICON);
        shortcutShowMap.insert(HOTSPOT_NAME,HOTSPOT_icon);
        shortcutShowMap.insert(VPN_NAME,VPN_ICON);
        shortcutShowMap.insert(SETTING_NAME,SETTING_ICON);
        shortcutShowMap.insert(CALCULATOR_NAME,CALCULATOR_ICON);
        shortcutShowMap.insert(SCREENSHOTS_NAME,SCREENSHOTS_ICON);
        shortcutShowMap.insert(ALARM_NAME,ALARM_ICON);
        shortcutShowMap.insert(NOTEBOOK_NAME,NOTEBOOK_ICON);
        if(!writeFile(recordShowPath, shortcutShowMap)){
            qDebug()<<"初始化shortcutShowMap write失败！";
            return;
        }
    }


    //初始化shortcutHideMap和sidebarRecordHide文件
    if(QFile::exists(recordHidePath)){
        if(readFile(recordHidePath,shortcutHideMap)){
            qDebug()<<"shortcutHideMap read失败！";
            return;
        }
    }
    else{
        shortcutHideMap.clear();
        if(!writeFile(recordHidePath, shortcutHideMap)){
            qDebug()<<"初始化shortcutShowMap 失败！";
            return;
        }
    }

}

bool RecordSequenceFile::creatorRecordFile()
{

}

bool RecordSequenceFile::isExist()
{
    QString recoedPath = QDir::homePath() + "/.config/sidebarRecord";
    if(QFile::exists(recoedPath))
        return true;
    else
        return false;
}

bool RecordSequenceFile::readFile(QString filePath, QMap<QString,QString> map)
{
    QFile file(filePath);
    if(!file.open(QFile::ReadOnly| QFile::Text)){
        return false;
    }
    map.clear();
    QString fileDate = QString(file.readAll());
    QList<QString> fileList = fileDate.split(";");
    for(int i=0; i<=fileList.size(); i++){
        QStringList currList = fileList.at(i).split(",");
        map.insert(currList.at(0),currList.at(1));
    }
    return true;
}

/*存放格式如下:
Alarm,:/images/icon-alarm.svg;
NoteBook,:/images/icon-notes.svg;
*/
bool RecordSequenceFile::writeFile(QString filePath, QMap<QString,QString> map)
{
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text)){     //清空文件
        return false;
    }
    file.close();
    //文件写操作
    file.setFileName(filePath);
    if (file.open(QFile::WriteOnly | QFile::Text)){
        return false;
    }

    QMap<QString,QString>::iterator iter = map.begin();
    for(iter;iter!=map.end();iter++){
        QString str = iter.key() + "," + iter.value() + ";";
        file.write(str.toStdString().c_str(),str.size());
    }
    file.close();
    return true;
}






