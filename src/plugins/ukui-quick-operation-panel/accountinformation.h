#ifndef ACCOUNTINFORMATION_H
#define ACCOUNTINFORMATION_H



#include <QFont>
#include <QDBusInterface>
#include <QDBusReply>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QProcess>
#include <QPainter>
#include <QApplication>
#include "iconlabel.h"

#define DEFAULTFACE "/usr/share/ukui/faces/default.png"

#define KYLIN_SHUT_DOWN_ICON_PATH ":/images/icon-shutdown.svg"
#define KYLIN_SHUT_DOWN_ICON_NAME ":/ukui-icon-shutdown"

/* qt会将glib里的signals成员识别为宏，所以取消该宏
 * 后面如果用到signals时，使用Q_SIGNALS代替即可
 **/
#ifdef signals
#undef signals
#endif

extern "C" {
#include <glib.h>
#include <gio/gio.h>
}

typedef struct _UserInfomation {
    QString objpath;
    QString username;
    QString iconfile;
    QString passwd;
    int accounttype;
    int passwdtype;
    bool current;
    bool logined;
    bool autologin;
    bool noPwdLogin;
    qint64 uid;
}UserInfomation;

class AccountInformation : public QWidget
{
    Q_OBJECT
public:
    explicit AccountInformation(QWidget *parent = nullptr);

private:
    void initMemberVariable();
    void initLayout();
    void registeredAccountsDbus();
    QStringList getUserObjectPath();
    UserInfomation GetUserInformation(QString objpath);

    void setAllControlsLabelInfo();
    QPixmap PixmapToRound(const QPixmap &src, int radius);
private:
    IconLabel    *m_pHeadPortraitIconLabel;
    QLabel       *m_pNameLabel;
    QLabel       *m_pIdentityLabel;
    QPushButton  *m_pShutDownButton;
    QHBoxLayout  *m_pMainLayout;
    QVBoxLayout  *m_pVLabelLayout;
    QWidget      *m_pInfoWidget;
    QDBusInterface * m_pSystemUserIface;



private slots:
    void openShutdownWidgetSlots();
    void openContorlCenterWidgetSlots();

Q_SIGNALS:

};

#endif // ACCOUNTINFORMATION_H
