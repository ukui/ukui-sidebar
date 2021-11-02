#include "primarymanager.h"




PrimaryManager::PrimaryManager()
{
    this->m_on_wayland = checkWayland();
    if(m_on_wayland){
        //支持 wayland
        mDbusXrandInter = new QDBusInterface(DBUS_NAME,
                                             DBUS_PATH,
                                             DBUS_INTERFACE,
                                             QDBusConnection::sessionBus());
        this->m_nScreen_x = getScreenGeometry("x");
        this->m_nScreen_y = getScreenGeometry("y");
        this->m_screenWidth = getScreenGeometry("width");
        this->m_screenHeight = getScreenGeometry("height");
        qDebug("初始化, geometry is  x=%d, y=%d, width=%d, height=%d", m_nScreen_x, m_nScreen_y, m_screenWidth, m_screenHeight);
        /*监听dbus变化  更改主屏幕时，会进行信号发送 */
        connect(mDbusXrandInter, SIGNAL(screenPrimaryChanged(int,int,int,int)),
                this, SLOT(priScreenChanged(int,int,int,int)));
    }else{
        //不支持 wayland
        m_pDeskWgt = QApplication::desktop();
        m_adaptScreenInfo = new adaptScreenInfo();
        updateInfoByAdapt();
        //当改变屏幕分辨率时 重新计算 主屏坐标 屏幕宽高
        connect(QApplication::primaryScreen(), &QScreen::geometryChanged, this, &PrimaryManager::updateInfoByAdapt);
        //主屏发生变化槽函数 重新计算 主屏坐标 屏幕宽高
        connect(m_pDeskWgt, &QDesktopWidget::primaryScreenChanged, this, &PrimaryManager::updateInfoByAdapt);
        //屏幕数量改变时 重新计算 主屏坐标 屏幕宽高
        connect(m_pDeskWgt, &QDesktopWidget::screenCountChanged, this, &PrimaryManager::updateInfoByAdapt);
    }

}
/**
 * @brief 主屏幕变化监听函数
 */
void PrimaryManager::priScreenChanged(int x, int y, int width, int height)
{
    QString priName;
    priName = getScreenName ("priScreenName");
    this->m_nScreen_x=x;
    this->m_nScreen_y=y;
    this->m_screenWidth=width;
    this->m_screenHeight=height;
    qDebug("primary screen  changed, geometry is  x=%d, y=%d, width=%d, height=%d", x, y, width, height);
}
/**
 * @brief 根据adaptScreenInfo更新数据
 */
void PrimaryManager::updateInfoByAdapt()
{
    this->m_nScreen_x = m_adaptScreenInfo->m_nScreen_x;
    this->m_nScreen_y = m_adaptScreenInfo->m_nScreen_y;
    this->m_screenWidth = m_adaptScreenInfo->m_screenWidth;
    this->m_screenHeight = m_adaptScreenInfo->m_screenHeight;
}
/**
 * @brief 启动获取主屏幕坐标 x/y/width/height；  以及基于Kscreen获取的主屏幕名字
 */
void PrimaryManager::start()
{
    int priX, priY, priWid, priHei;
       QString priName;
       priX = getScreenGeometry("x");
       priY = getScreenGeometry("y");
       priWid = getScreenGeometry("width");
       priHei = getScreenGeometry("height");
       priName = getScreenName ("priScreenName");

       qDebug("Start: Primary screen geometry is x=%d, y=%d, width=%d, height=%d,",
              priX, priY, priWid, priHei);
       qDebug()<<"Primary screen name = " << priName;
}
/**
 * @brief 根据dbus 提供method 获取X/Y/width/height 参数
 */
int PrimaryManager::getScreenGeometry(QString methodName)
{
    int res = 0;
        QDBusMessage message = QDBusMessage::createMethodCall(DBUS_NAME,
                                   DBUS_PATH,
                                   DBUS_INTERFACE,
                                   methodName);
        QDBusMessage response = QDBusConnection::sessionBus().call(message);
        if (response.type() == QDBusMessage::ReplyMessage)
        {
            if(response.arguments().isEmpty() == false) {
                int value = response.arguments().takeFirst().toInt();
                res = value;
                qDebug() << value;
            }
        } else {
            qDebug()<<methodName<<"called failed";
        }
        return res;
}
/**
 * @brief 根据 dbus 提供method 获取基于kscreen获得的屏幕名字
 */
QString PrimaryManager::getScreenName(QString methodName)
{
    QString res = 0;
    QDBusMessage message = QDBusMessage::createMethodCall(DBUS_NAME,
                               DBUS_PATH,
                               DBUS_INTERFACE,
                               methodName);
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    if (response.type() == QDBusMessage::ReplyMessage)
    {
        if(response.arguments().isEmpty() == false) {
            QString value = response.arguments().takeFirst().toString();
            res = value;
            qDebug() << value;
        }
    } else {
        qDebug()<<methodName<<"called failed";
    }
    return res;
}
/**
 * @brief 如果应用必须要用QScreen 可进行参数判断，代码如下：
 */
void PrimaryManager::init()
{
    int dX, dY, dWidth, dHeight;
        QScreen *mPriScreen;

        dX = getScreenGeometry("x");
        dY = getScreenGeometry("y");
        dWidth = getScreenGeometry("width");
        dHeight = getScreenGeometry("height");
        //根据真实值判断哪一个是主屏
        for (auto screen : QApplication::screens()){
            if (screen->geometry().x() == dX && screen->geometry().y() == dY) {
                 mPriScreen = screen;
            }
        }
}

PrimaryManager::~PrimaryManager()
{
    delete mDbusXrandInter;
    delete m_adaptScreenInfo;
}

int PrimaryManager::getScreenWidth() const
{
    return m_screenWidth;
}

int PrimaryManager::getScreenHeight() const
{
    return m_screenHeight;
}

int PrimaryManager::getNScreen_x() const
{
    return m_nScreen_x;
}

int PrimaryManager::getNScreen_y() const
{
    return m_nScreen_y;
}
/**
 * @brief 根据环境变量判断是否支持wayland
 */
bool PrimaryManager::checkWayland()
{
    QByteArray byte = qgetenv("DESKTOP_SESSION");
    QString info =QString::fromLocal8Bit(byte);
    if("ukui-wayland"==info){
        return true;
    }else{
        return false;
    }
}
