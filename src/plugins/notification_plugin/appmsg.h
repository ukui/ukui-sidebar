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
    AppMsg(NotificationPlugin *parent, QString strAppName, QString strIcon, bool bTakeInFlag = false);
    ~AppMsg();
    uint getNotifyAbsuluteTime() {return m_uNotifyTime;}
    QString getAppName() {return m_strAppName;}
    void addSingleMsg(QString strSummary, QDateTime dateTime, QString strBody);
    void TakeinSingleMsg(QString strSummary, QDateTime dateTime, QString strBody);
    void updateAppPushTime();   //更新应用最新的推送时间

protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

private:
    QVBoxLayout*        m_pMainVLaout;                  //App信息中的总的垂直布局器
    QToolButton*        m_pIconToolButton;              //消息图标
    QLabel*             m_pAppNameLabel;                //保存应用名的Label
    QLabel*             m_pTimeLabel;                   //保存推送时间的Label
    QPushButton*        m_pFoldButton;                  //应用消息折叠按钮
    QVBoxLayout*        m_pAppMsgListVLaout;            //保存添加该应用的消息列表布局器    
    QLabel*             m_pShowLeftItemLabel;           //显示该应用未展开条数
    QWidget*            m_pButtonWidget;                //保存底下收纳和删除按钮的Widget
    QPushButton*        m_pTakeinButton;                //收纳按钮
    QPushButton*        m_pDeleteButton;                //删除按钮


    QList<SingleMsg*>   m_listSingleMsg;                //对于SingleMsg类对象用list表记录
    QString             m_strAppName;                   //保存发送方的应用名
    QString             m_strIcon;                      //保存发送方的图标路径
    QDateTime           m_dateTime;                     //保存推送时间
    uint                m_uNotifyTime;                  //保存推送时间的绝对时间
    bool                m_bTakeInFlag;                  //转变为收纳消息吗，默认为false



signals:
    void                Sig_onDeleteAppMsg(AppMsg* p);            //将本对象指针发送出去
    void                Sig_SendTakein(QString strAppName, QString strIcon, QString strSummary, QString strBody, QDateTime dateTime);

public slots:
    void                onDeleteAppMsg();                      //清除一个应用消息
    void                onTakein();                     //收纳一个应用消息
    void                onFold();                       //处理折叠
    void                onDeleSingleMsg(SingleMsg* pSingleMsg);
    void                onTakeInSingleMsg(SingleMsg* pSingleMsg);

};

#endif // APPMSG_H
