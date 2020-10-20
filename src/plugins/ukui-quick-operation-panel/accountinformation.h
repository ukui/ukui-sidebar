/*
* Copyright (C) 2020 Tianjin KYLIN Information Technology Co., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, see <http://www.gnu.org/licenses/&gt;.
*
*/
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
    void AccountSlots(QString property, QMap<QString, QVariant> propertyMap, QStringList propertyList);

Q_SIGNALS:

};

#endif // ACCOUNTINFORMATION_H
