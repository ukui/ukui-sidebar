/*
* Copyright (C) 2019 Tianjin KYLIN Information Technology Co., Ltd.
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

#ifndef NOTIFICATION_INTERFACE_H
#define NOTIFICATION_INTERFACE_H

#include <QWidget>

//定义接口
class NotificationInterface
{
public:
    virtual ~NotificationInterface() {}

    //返回一个Widget设置到centerwidget中进行显示
    virtual QWidget* centerWidget() = 0;
    //当侧边栏展开时给通知中心一个通知
    virtual void showNotification() = 0;
    //当侧边栏隐藏时给通知中心一个通知
    virtual void hideNotification() = 0;
//    virtual void Notify(QString strAppName, QString strIconPath, QString strSummary, QString strTime, QString strBody) = 0;
};

//声明接口
#define NotificationInterface_iid "org.qt-project.Qt.QGenericPluginFactoryInterface"
Q_DECLARE_INTERFACE(NotificationInterface, NotificationInterface_iid)

#endif // NOTIFICATION_INTERFACE_H
