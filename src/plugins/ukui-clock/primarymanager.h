#ifndef PRIMARYMANAGER_H
#define PRIMARYMANAGER_H
#include <QString>
#include <QDebug>
#include <QScreen>
#include <QDBusInterface>
#include <QApplication>
#include "adaptscreeninfo.h"

#define DBUS_NAME       "org.ukui.SettingsDaemon"                       // dbus 服务名字
#define DBUS_PATH       "/org/ukui/SettingsDaemon/wayland"    // dbus 路径
#define DBUS_INTERFACE  "org.ukui.SettingsDaemon.wayland" // dbus 接口



class PrimaryManager:public QObject
{
    Q_OBJECT
public:
    PrimaryManager();

    void start();
    int getScreenGeometry(QString methodName);
    QString getScreenName(QString methodName);
    void  init();
    ~PrimaryManager();

    int getScreenWidth() const;

    int getScreenHeight() const;

    int getNScreen_x() const;

    int getNScreen_y() const;
    bool checkWayland();
public slots:
    void priScreenChanged(int x, int y, int width, int height);
private:
    QDBusInterface *mDbusXrandInter;
    int             m_screenWidth;                                 // 桌面宽度
    int             m_screenHeight;                                // 桌面高度
    int             m_screenNum;                                   // 屏幕数量
    int             m_nScreen_x;                                   // 主屏起始坐标X
    int             m_nScreen_y;                                   // 主屏起始坐标Y
    bool            m_on_wayland;                                   //是否是wayland
    QDesktopWidget * m_pDeskWgt;
    adaptScreenInfo * m_adaptScreenInfo = nullptr;
    void updateInfoByAdapt();

};

#endif // PRIMARYMANAGER_H
