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


#include "appmsg.h"
#include "notification_plugin.h"
#include "singlemsg.h"

AppMsg::AppMsg(NotificationPlugin *parent, QString strAppName, bool bTakeInFlag)
{
    m_bFold = true;
    m_bTakeInFlag = bTakeInFlag;
    this->setFixedWidth(380);

    m_strAppName = strAppName;    

    //App信息中的总的垂直布局器
    m_pMainVLaout = new QVBoxLayout();
    m_pMainVLaout->setContentsMargins(0,0,0,0);
    m_pMainVLaout->setSpacing(0);

    this->setLayout(m_pMainVLaout);

    //发个信号通知插件删除该通知应用消息
    connect(this, SIGNAL(Sig_onDeleteAppMsg(AppMsg*)), parent, SLOT(onClearMsg(AppMsg*)));
    //发个信号通知插件删除该收纳应用消息
    connect(this, SIGNAL(Sig_onDeleteTakeInAppMsg(AppMsg*)), parent, SLOT(onClearTakeInMsg(AppMsg*)));

    //发个信号通知插件收纳单条应用消息
    connect(this, SIGNAL(Sig_SendTakeInSingleMsg(QString, QString, QString, QString, QDateTime)), parent, SLOT(onTakeInSingleMsg(QString, QString, QString, QString, QDateTime)));


    //发个统计收纳数更新信号
    connect(this, SIGNAL(Sig_countTakeInBitAndUpate()), parent, SLOT(countTakeInBitAndUpate()));

    return;
}

AppMsg::~AppMsg()
{

}

//收纳单条消息至收纳盒，也需要new，因为收纳次序不定，所以根据时间插入位置, 来自上层NotificationPlugin的新增调用(新增收纳消息)
void AppMsg::addTakeinSingleMsg(QString strIcon, QString strSummary, QDateTime dateTime, QString strBody)
{
    SingleMsg* pSingleMsg = new SingleMsg(this, strIcon, m_strAppName, strSummary, dateTime, strBody, true);

    int uIndex = m_listSingleMsg.count();
    for(int i = m_listSingleMsg.count() - 1; i >= 0; i--)
    {
        SingleMsg* pTmpSingleMsg = m_listSingleMsg.at(i);
        if(pSingleMsg->getPushTime() < pTmpSingleMsg->getPushTime())
        {
            break;
        }
        uIndex = i;
    }

    //当新收纳的消息将插入最顶部时,将已有列表最顶部的正文设置一行缩略显示
    if((0 == uIndex) && (m_listSingleMsg.count() > 0))
    {
        SingleMsg* pFirstMsg = m_listSingleMsg.at(0);
        pFirstMsg->setMainFlag(false);
        pFirstMsg->setShowLeftItemFlag(false);
        if(true == m_bFold) //只有已经折叠的才需要将现有的顶部设为缩略显示
        {
            pFirstMsg->setBodyLabelWordWrap(false);
        }
    }

    //如果插入第0条,并且已展开,则将新收纳消息设置自动换行,并且折叠标志设为false
    if((0 == uIndex) && (false == m_bFold))
    {
        pSingleMsg->setBodyLabelWordWrap(true);
        pSingleMsg->setFoldFlag(false);
    }
    //如果插入的不是第0条,则自己不能为主
    if(0 != uIndex)
    {
        pSingleMsg->setMainFlag(false);
    }

    m_listSingleMsg.insert(uIndex, pSingleMsg);
    m_pMainVLaout->insertWidget(uIndex, pSingleMsg);

    //只要是折叠状态则索引从1开始，将所有SingleMsg设置不可见
    if(true == m_bFold)
    {
        for(int i = 1; i < m_listSingleMsg.count(); i++)
        {
            SingleMsg* pTmpSingleMsg = m_listSingleMsg.at(i);
            pTmpSingleMsg->setVisible(false);
        }
    }

    SingleMsg* pTopSingleMsg = m_listSingleMsg.at(0); //将该应用中最顶上的一条消息的时间赋给应用
    m_uNotifyTime = pTopSingleMsg->getPushTime();
    m_dateTime = pTopSingleMsg->getPushDateTime();

    statisticLeftItem();
    return;
}

//统计应用剩余显示条数
void AppMsg::statisticLeftItem()
{
    if(m_listSingleMsg.count() < 1) //小于1时,表示列表为空,直接返回
    {
        return;
    }
    int nShowLeftCount = m_listSingleMsg.count() - 1;
    SingleMsg* pTopSingleMsg = m_listSingleMsg.at(0);
    pTopSingleMsg->setLeftItem(nShowLeftCount);
    return;
}

//新增单条消息至通知列表，崭新消息需要new，然后添加至列表最上面
void AppMsg::addSingleMsg(QString strIconPath, QString strSummary, QDateTime dateTime, QString strBody)
{
    m_dateTime = dateTime;
    m_uNotifyTime = dateTime.toTime_t();

    if(m_listSingleMsg.count() > 0) //只要新增加前已存在条数，则先将最顶部一条设置非主信息,并且剩余条数不可见
    {
        SingleMsg* pFirstMsg = m_listSingleMsg.at(0);
        pFirstMsg->setMainFlag(false);
        pFirstMsg->setShowLeftItemFlag(false);
        pFirstMsg->setBodyLabelWordWrap(false);
        pFirstMsg->setFoldFlag(true);
    }

    SingleMsg* pSingleMsg = new SingleMsg(this, strIconPath, m_strAppName, strSummary, dateTime, strBody);
    m_listSingleMsg.insert(0, pSingleMsg);
    m_pMainVLaout->insertWidget(0, pSingleMsg);
    pSingleMsg->setFoldFlag(m_bFold);

    //只要是折叠状态则索引从1开始，将所有SingleMsg设置不可见
    if(true == m_bFold)
    {
        for(int i = 1; i < m_listSingleMsg.count(); i++)
        {
            SingleMsg* pTmpSingleMsg = m_listSingleMsg.at(i);
            pTmpSingleMsg->setVisible(false);
        }
    }
    else
    {
        pSingleMsg->setBodyLabelWordWrap(true); //如果已展开，则新增信息也展开消息
    }

    //统计应用剩余显示条数
    statisticLeftItem();

    return;
}

void AppMsg::updateAppPushTime()
{
    for(int i = 0; i < m_listSingleMsg.count(); i++)
    {
        SingleMsg* pTmpSingleMsg = m_listSingleMsg.at(i);
        pTmpSingleMsg->updatePushTime();
    }

    QDateTime currentDateTime(QDateTime::currentDateTime());
    QDate currentDate(QDate::currentDate());
    if(currentDateTime.toTime_t() < (m_uNotifyTime + 60))
    {
        return;
    }

    if(m_dateTime.date() == currentDate)
    {
        QString strPushDate = m_dateTime.toString("hh:mm");
//        m_pTimeLabel->setText(strPushDate);
        return;
    }

    QDate lastDate = currentDate.addDays(-1);
    if(m_dateTime.date() == lastDate)
    {
        QString strPushDate = "昨天 ";
        strPushDate = strPushDate + m_dateTime.toString("hh:mm");
//        m_pTimeLabel->setText(strPushDate);
        return;
    }

    QString strPushDate = m_dateTime.toString("yyyy/MM/dd");
//    m_pTimeLabel->setText(strPushDate);
    return;
}

int AppMsg::getSingleMsgCount()
{
    return m_listSingleMsg.count();
}

void AppMsg::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    setStyleSheet("background-color:rgba(255,255,255,0.08);");

    return;
}

void AppMsg::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    setStyleSheet("background-color:rgba(26,26,26,0.95);");
    return;
}

//鼠标点击事件
void AppMsg::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
//        m_bFold = false;  //置为false,表示展开
//        //点击展开所有列表
//        SingleMsg* pFirstMsg = m_listSingleMsg.at(0);
//        if(false == pFirstMsg->getSingleDeleteButtonVisible())  //只有当单条删除按钮不可见时，才设置时间可见，此为鼠标悬停在第一条上时点击按钮出现
//        {
//            pFirstMsg->setTimeLabelVisible(true);
//        }
//        pFirstMsg->setBodyLabelWordWrap(true);
//        pFirstMsg->setLeaveShowNoTimeFlag(false);

//        for(int i = 1; i < m_listSingleMsg.count(); i++)
//        {
//            SingleMsg* pTmpSingleMsg = m_listSingleMsg.at(i);
//            pTmpSingleMsg->setVisible(true);
//        }
//        m_pShowLeftItemLabel->setVisible(false);
//        m_pTimeLabel->setVisible(false);

    }
    return;
}

void AppMsg::onDeleteAppMsg()
{   
    if(false == m_bTakeInFlag)  //是通知应用就通知插件删该通知应用
    {
        emit Sig_onDeleteAppMsg(this);
    }
    else                        //是收纳应用就通知插件删该收纳应用
    {
        emit Sig_onDeleteTakeInAppMsg(this);
    }
    return;
}

void AppMsg::onTakeinWholeApp()
{
    while(m_listSingleMsg.count() > 0)
    {
        SingleMsg* pSingleMsg = m_listSingleMsg.at(0);
        m_pMainVLaout->removeWidget(pSingleMsg);
        m_listSingleMsg.removeAt(0);
        emit Sig_SendTakeInSingleMsg(m_strAppName, pSingleMsg->getIcon(), pSingleMsg->getSummary(), pSingleMsg->getBody(), pSingleMsg->getPushDateTime());
    }

    emit Sig_onDeleteAppMsg(this);

    return;
}

void AppMsg::onDeleSingleMsg(SingleMsg* pSingleMsg)
{
    int nIndex = m_listSingleMsg.indexOf(pSingleMsg);
    if(-1 == nIndex)
    {
        qDebug()<<"AppMsg::onDeleSingleMsg 在通知链表中未找到pSingleMsg指针";
        return;
    }

    m_listSingleMsg.removeAt(nIndex);
    m_pMainVLaout->removeWidget(pSingleMsg);
    pSingleMsg->deleteLater();

    //当本次删除为应用首条时,且该应用不止一条,则需将新的首条设置为顶部消息状态
    if(0 == nIndex)
    {
        setTopWithSecondItem();
    }

    //统计剩余显示条数,看情况显示
    statisticLeftItem();

    //只有当该应用属于收纳应用对象时,每删除一条都要更新收纳计数
    if(true == m_bTakeInFlag)
    {
        emit Sig_countTakeInBitAndUpate();
    }

    //当删除一条消息后,如果应用列表为空
    if(0 == m_listSingleMsg.count())
    {
        if(false == m_bTakeInFlag)  //是通知应用就通知插件删该通知应用
        {
            emit Sig_onDeleteAppMsg(this);
        }
        else                        //是收纳应用就通知插件删该收纳应用
        {
            emit Sig_onDeleteTakeInAppMsg(this);
        }
    }

    return;
}

//当应用最顶条被删除后,将第二条置顶
void AppMsg::setTopWithSecondItem()
{
    if(m_listSingleMsg.count() > 0)
    {
        SingleMsg* pFirstMsg = m_listSingleMsg.at(0);
        pFirstMsg->setMainFlag(true);
        pFirstMsg->setFoldFlag(m_bFold);
        if(true == m_bFold)
        {
            pFirstMsg->setBodyLabelWordWrap(false);
        }
        else
        {
            pFirstMsg->setBodyLabelWordWrap(true);
        }
        pFirstMsg->setVisible(true);
    }
    return;
}

//来自SingleMsg下的事件,处理收纳事件
void AppMsg::onTakeInSingleMsg(SingleMsg* pSingleMsg)
{
    int nIndex = m_listSingleMsg.indexOf(pSingleMsg);
    if(-1 == nIndex)
    {
        qDebug()<<"AppMsg::onTakeInSingleMsg 在通知链表中未找到pSingleMsg指针";
        return;
    }

    m_listSingleMsg.removeAt(nIndex);
    m_pMainVLaout->removeWidget(pSingleMsg);

    emit Sig_SendTakeInSingleMsg(m_strAppName, pSingleMsg->getIcon(), pSingleMsg->getSummary(), pSingleMsg->getBody(), pSingleMsg->getPushDateTime());
    pSingleMsg->deleteLater();

    //当本次收纳为应用首条时,且该应用不止一条,考虑将新的首条设置为顶部消息状态
    if(0 == nIndex)
    {
        setTopWithSecondItem();
    }

    //统计剩余显示条数,看情况显示
    statisticLeftItem();

    if(0 == m_listSingleMsg.count())
    {
        emit Sig_onDeleteAppMsg(this);
    }
}

void AppMsg::setAppFoldFlag(bool bFlag)
{
    m_bFold = bFlag;

    if(false == m_bFold)    //false表示应用展开
    {
        //展开时,索引从第1条开始,消息全部可见
        for(int i = 1; i < m_listSingleMsg.count(); i++)
        {
            SingleMsg* pTmpSingleMsg = m_listSingleMsg.at(i);
            pTmpSingleMsg->setVisible(true);
        }
    }
    else
    {
        //折叠时,索引从第1条开始,消息全部不可见
        for(int i = 1; i < m_listSingleMsg.count(); i++)
        {
            SingleMsg* pTmpSingleMsg = m_listSingleMsg.at(i);
            pTmpSingleMsg->setVisible(false);
            pTmpSingleMsg->setFoldFlag(true);
            pTmpSingleMsg->setBodyLabelWordWrap(false);
        }
    }

}
















