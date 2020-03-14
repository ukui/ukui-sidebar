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



#ifndef APPMSG_H
#define APPMSG_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QPushButton>
#include <QToolButton>
#include <QDateTime>


class NotificationPlugin;
class SingleMsg;


class AppMsg : public QWidget
{
    Q_OBJECT
public:
    AppMsg(NotificationPlugin *parent, QString strAppName, bool bTakeInFlag = false);
    uint    getAppPushTime() {return m_uNotifyTime;}
    QString getAppName() {return m_strAppName;}
    void    addSingleMsg(QString strIconPath, QString strSummary, QDateTime dateTime, QString strBody);
    void    updateAppPushTime();                        //更新应用最新的推送时间
    int     getSingleMsgCount();                        //获取应用消息数
    void    statisticLeftItem();                        //统计应用剩余显示条数
    void    setTopWithSecondItem();                     //当应用最顶条被删除后,将第二条置顶
    void    setAppFold();                               //当app展开时，将app设置折叠


private:
    QVBoxLayout*        m_pMainVLaout;                  //App信息中的总的垂直布局器
    QWidget*            m_pAppBaseMapWidget;            //多条消息时，底图部件包括底部6个px的空白
    QWidget*            m_pBaseMapWidget;               //多条消息时，底图部件不包括底部6个px的空白
    QList<SingleMsg*>   m_listSingleMsg;                //对于SingleMsg类对象用list表记录
    QString             m_strAppName;                   //保存发送方的应用名
    QDateTime           m_dateTime;                     //保存推送时间
    uint                m_uNotifyTime;                  //保存推送时间的绝对时间
    bool                m_bTakeInFlag;                  //转变为收纳消息吗，默认为false
    bool                m_bFold;                        //折叠标志



signals:
    void                Sig_onDeleteAppMsg(AppMsg* p);              //该对象属于通知应用,发出删除应用的信号
    void                Sig_onDeleteTakeInAppMsg(AppMsg* p);        //当该对象属于收纳应用时,发出删除收纳应用的信号
    void                Sig_countTakeInBitAndUpate();               //发个统计收纳数信号
    void                Sig_SendTakeInSingleMsg(QString strAppName, QString strIcon, QString strSummary, QString strBody, QDateTime dateTime);
    void                Sig_SendAddSingleMsg(QString strAppName, QString strIcon, QString strSummary, QString strBody, QDateTime dateTime, bool bNewNotificationFlag);


public slots:
    void                onDeleteAppMsg();                           //删除一个应用消息
    void                onTakeinWholeApp();                         //收纳整个应用消息
    void                onRecoverWholeApp();                        //恢复整个应用消息
    void                onDeleSingleMsg(SingleMsg* pSingleMsg);     //删除单条消息
    void                onTakeInSingleMsg(SingleMsg* pSingleMsg);   //收纳单条消息
    void                onRecoverSingleMsg(SingleMsg* pSingleMsg);  //恢复单条消息
    void                setAppFoldFlag(bool bFlag);                 //设置应用折叠标志
    void                onMainMsgEnter();                           //应用主消息进入
    void                onMainMsgLeave();                           //应用主消息离开
    void                onShowBaseMap();                            //显示应用底图
    void                onHideBaseMap();                            //隐藏底图部件

};

#endif // APPMSG_H
