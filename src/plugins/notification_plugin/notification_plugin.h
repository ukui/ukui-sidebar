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


#ifndef NOTIFICATION_PLUGIN_H
#define NOTIFICATION_PLUGIN_H

#include "notification_interface.h"
#include "singlemsg.h"
#include <QtWidgets>

class ScrollAreaWidget;
class QSvgRenderer;
class TakeInBoxToolButton;

class NotificationPlugin : public QObject, public NotificationInterface
{
    Q_OBJECT
    //Q_INTERFACES宏用于告诉Qt该类实现的接口
    Q_INTERFACES(NotificationInterface)
    //Q_PLUGIN_METADATA宏用于描述插件元数据
    Q_PLUGIN_METADATA(IID NotificationInterface_iid FILE "notification_plugin.json")
    //申明该类有D-BUS服务接口
    Q_CLASSINFO("D-Bus Interface", "com.scorpio.test.value")

public:
    NotificationPlugin();
    virtual QWidget* centerWidget() override;    

public slots :
    uint Notify(QString strAppName, uint uId, QString strIconPath, QString strSummary, QString strBody, QStringList actions, QVariantMap hint, int nTimeout);

private:
    QWidget*                m_pMainWidget;
    QList<SingleMsg*>       m_listSingleMsg;                    //对于SingleMsg类对象用list表记录
    QList<SingleMsg*>       m_listSingleTakeInMsg;
    ScrollAreaWidget*       m_pQScrollAreaNotify;               //通知列表ScrollAreaWidget
    QVBoxLayout*            m_pScrollAreaNotifyVBoxLayout;
    ScrollAreaWidget*       m_pQScrollAreaTakeIn;               //收纳列表ScrollAreaWidget
    QVBoxLayout*            m_pScrollAreaTakeInVBoxLayout;
    QLabel*                 m_pMessageCenterLabel;
    QString                 m_strQss;
    bool                    m_bShowTakeIn;
    QLabel*                 m_pNotificationLabel;               //重要的通知和不重要的通知标签
    QSvgRenderer*           m_pSvgRender;
    TakeInBoxToolButton*    m_pTakeInBoxToolButton;
    QPixmap*                m_pPixmap;
    QLabel*                 m_pTakeInCoutLabel;                 //收纳盒计数统计Label

private slots:
    void onClearMsg(SingleMsg* pSingleMsg);                     //处理清除消息槽函数
    void onTakeinMsg(SingleMsg* pSingleMsg);
    void clearAllMessage();                                     //清除所有消息
    void showTakeInMessage();
    void callControlPanel();                                    //调用控制面板


};

#endif // NOTIFICATION_PLUGIN_H
