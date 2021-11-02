#ifndef SIDEBARDBUSSERVICE_H
#define SIDEBARDBUSSERVICE_H

#include <QObject>
#include <QRect>
#include <QWidget>

class SidebarDbusService: public QObject
{
    Q_OBJECT
    //申明该类有D-BUS服务接口
    Q_CLASSINFO("D-Bus Interface", "org.ukui.Sidebar")
public:
    SidebarDbusService(QWidget *parent = nullptr);
    int m_sidebarWidth;                                    // 侧边栏宽度
    bool sidebarState;                                      //展开中/展开完成-true；

private:
    QWidget *m_parent;
public slots:
    int getWidth(); //获取侧边栏当前位置
signals:
    void animationAction(const uint time, const int distance);
};

#endif // SIDEBARDBUSSERVICE_H
