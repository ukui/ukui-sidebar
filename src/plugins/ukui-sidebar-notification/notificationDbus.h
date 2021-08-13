#ifndef NOTIFICATIONDBUS_H
#define NOTIFICATIONDBUS_H

#include <QObject>
#include <QGSettings>
#include <QMap>
#include <QDateTime>

#define DBUS_INTERFACE "org.ukui.Sidebar.notification"

class NotificationPlugin;

class NotificationDbus : public QObject
{
    Q_OBJECT
    //申明该类有D-BUS服务接口
    Q_CLASSINFO("D-Bus Interface", "org.ukui.Sidebar.notification")

public:
    NotificationDbus(NotificationPlugin *parent);
    void getSettingsValue();
    void fromSettingsGetInfoToList();
    void appNotifySettingChangedSlot();
    QList<char*> listExistsPath();

signals:
    void Sig_Notify(QString appName, QString appIcon,
                    QString summary, QString body,
                    QString urlStr,  QString actions,
                    QDateTime dateTime, int nMaxNum, bool flag);
    void Sig_Takein(QString appName, QString appIcon,
                    QString summary, QString body,
                    QString urlStr,  QString actions,
                    QDateTime dateTime, int nMaxNum, bool flag);
    void Sig_CloseAppMsg(QString strAppName);
    void Sig_UpdateAppMaxNum(QString strAppName, int maxNum);
public slots:
    void sidebarNotification(const QString &appName,const QString &appIcon,
                             const QString &summary,const QString &body,
                             const QString &urlStr, const QString &actions); //创建一条侧边栏通知

public:
    bool powerstatus = true;

private:
    NotificationPlugin*     m_parent;           //传一个插件对象指针，用来回传槽函数
    QGSettings*             m_pSettings;
    QMap<QString, int>      m_nAppMaxNum;
    QMap<QString, bool>     m_mapAppSwitch;
};

#endif // NOTIFICATIONDBUS_H
