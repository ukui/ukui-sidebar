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
#include <QtWidgets>

class AppMsg;
class SingleMsg;
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
    //Q_CLASSINFO("D-Bus Interface", "com.scorpio.test.value")

public:
    NotificationPlugin();
    virtual QWidget* centerWidget() override;    
    virtual void showNotification() override;
    virtual void hideNotification() override;
    AppMsg* getAppMsgAndIndexByName(QString strAppName, int& nIndex);
    AppMsg* getTakeinAppMsgAndIndexByName(QString strAppName, int& nIndex);

private:
    QWidget*                m_pMainWidget;
    QList<AppMsg*>          m_listAppMsg;                       //对于SingleMsg类对象用list表记录
    QList<AppMsg*>          m_listTakeInAppMsg;
    ScrollAreaWidget*       m_pQScrollAreaNotify;               //通知列表ScrollAreaWidget
    QVBoxLayout*            m_pScrollAreaNotifyVBoxLayout;
    ScrollAreaWidget*       m_pQScrollAreaTakeIn;               //收纳列表ScrollAreaWidget
    QVBoxLayout*            m_pScrollAreaTakeInVBoxLayout;
    QLabel*                 m_pMessageCenterLabel;
    QLabel*                 m_pTakeinMessageCenterLabel;
    bool                    m_bShowTakeIn;
    QLabel*                 m_pNotificationLabel;               //重要的通知和不重要的通知标签
    QSvgRenderer*           m_pSvgRender;
    TakeInBoxToolButton*    m_pTakeInBoxToolButton;
    QPixmap*                m_pPixmap;
    QLabel*                 m_pTakeInCoutLabel;                 //收纳盒计数统计Label

signals:
    void    Sig_onNewNotification();

private slots:
    uint onAddSingleNotify(QString strAppName, QString strIconPath, QString strSummary, QString strBody, QDateTime dateTime, bool bNewNotificationFlag);    //处理新增单条通知
    void onTakeInSingleNotify(QString strAppName, QString strIcon, QString strSummary, QString strBody, QDateTime dateTime);                                //处理收纳单条通知
    void onClearAllMessage();                                   //清除所有消息
    void onClearAppMsg(AppMsg* pAppMsg);                        //处理删除通知应用消息槽函数
    void onClearTakeInAppMsg(AppMsg* pAppMsg);                  //处理删除收纳应用的槽函数
    void onShowTakeInMessage();                                 //切换至收纳盒
    void onCallControlPanel();                                  //调用控制面板
    void onCountTakeInBitAndUpate();                            //统计收纳位数并更新至右上角提示

};

#endif // NOTIFICATION_PLUGIN_H
