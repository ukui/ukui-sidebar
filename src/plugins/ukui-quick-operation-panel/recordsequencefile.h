#ifndef RECORDSEQUENCEFILE_H
#define RECORDSEQUENCEFILE_H
#include <QMap>
#include <QFile>
#include <QVector>
#include <QMutex>
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
#define SCREENSHOTS_CLASS_NAME     "screenshot"
#define ALARM_NAME          "Alarm"
#define ALARM_ICON          ":/images/icon-alarm.svg"
#define ALARM_CLASS_NAME    "alarm"
#define NOTEBOOK_NAME       "NoteBook"
#define NOTEBOOK_ICON       ":/images/icon-notes.svg"
#define FEEDBACK_NAME       "Feedback"
#define FEEDBACK_ICON       ":/images/icon-alarm.svg"
#define WIFI_NAM            "Wifi"
#define WIFI_ICON           ":/image/wifi-normal.svg"


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
    bool initshortcutClassName();
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
    QVector<QMap<QString,QString>> m_shortcutShowVector;    //显示区内的快捷键  <[名字]，[图标1，图标2]>
    QVector<QMap<QString,QString>> m_shortcutHideVector;    //未添加到显示区的快捷键 <[名字]，[图标1，图标2]>
    QMap<QString,QString> m_shortcutClassName;  //快捷键类的类名，方便使用类名字符串获取 <[名字]，[类名字符串]>

    int m_hoverIndex;
    bool m_hoverStatus;

};

#endif // RECORDSEQUENCEFILE_H
