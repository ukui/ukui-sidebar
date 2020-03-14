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
    m_strAppName = strAppName;
    this->setFixedWidth(380);
    this->adjustSize();

    //App信息中的总的垂直布局器
    m_pMainVLaout = new QVBoxLayout();
    m_pMainVLaout->setContentsMargins(0,0,0,0);
    m_pMainVLaout->setSpacing(0);

    //当出现多条消息时，增加底图
    m_pAppBaseMapWidget = new QWidget;
    QVBoxLayout* pBaseMapVLaout = new QVBoxLayout();
    pBaseMapVLaout->setContentsMargins(0,0,0,6);
    pBaseMapVLaout->setSpacing(0);

    m_pBaseMapWidget = new QWidget;
    m_pBaseMapWidget->setObjectName("BaseMap");
    m_pBaseMapWidget->setFixedWidth(360);
    m_pBaseMapWidget->setFixedHeight(6);
    m_pBaseMapWidget->setStyleSheet("QWidget{background:rgba(255,255,255,0.04);border-top-left-radius:0px;border-top-right-radius:0px;border-bottom-left-radius:6px;border-bottom-right-radius:6px;}");
    pBaseMapVLaout->addWidget(m_pBaseMapWidget, 0 , Qt::AlignHCenter);

    m_pAppBaseMapWidget->setLayout(pBaseMapVLaout);
    m_pMainVLaout->addWidget(m_pAppBaseMapWidget, 0 , Qt::AlignHCenter);
    m_pAppBaseMapWidget->setVisible(false);

    this->setLayout(m_pMainVLaout);

    //发个信号通知插件删除该通知应用消息
    connect(this, SIGNAL(Sig_onDeleteAppMsg(AppMsg*)), parent, SLOT(onClearAppMsg(AppMsg*)));
    //发个信号通知插件删除该收纳应用消息
    connect(this, SIGNAL(Sig_onDeleteTakeInAppMsg(AppMsg*)), parent, SLOT(onClearTakeInAppMsg(AppMsg*)));

    //发个信号通知插件收纳单条应用消息
    connect(this, SIGNAL(Sig_SendTakeInSingleMsg(QString, QString, QString, QString, QDateTime)), parent, SLOT(onTakeInSingleNotify(QString, QString, QString, QString, QDateTime)));
    //发个信号通知插件恢复单条应用消息
    connect(this, SIGNAL(Sig_SendAddSingleMsg(QString, QString, QString, QString, QDateTime, bool)), parent, SLOT(onAddSingleNotify(QString, QString, QString, QString, QDateTime, bool)));

    //发个统计收纳数更新信号
    connect(this, SIGNAL(Sig_countTakeInBitAndUpate()), parent, SLOT(onCountTakeInBitAndUpate()));

    return;
}

//统计应用剩余显示条数
void AppMsg::statisticLeftItem()
{
    //小于1时,表示列表为空,直接返回
    if(m_listSingleMsg.count() < 1)
    {
        return;
    }

    int nShowLeftCount = m_listSingleMsg.count() - 1;
    //当应用处于折叠状态，且剩余条数大于0时,应用底图部件显示
    if((true == m_bFold) && (nShowLeftCount > 0))
    {
        m_pAppBaseMapWidget->setVisible(true);
    }
    else
    {
        m_pAppBaseMapWidget->setVisible(false);
    }

    SingleMsg* pTopSingleMsg = m_listSingleMsg.at(0);
    pTopSingleMsg->setLeftItem(nShowLeftCount);
    return;
}

//新增单条消息至通知列表，崭新消息需要new，然后添加至列表最上面
void AppMsg::addSingleMsg(QString strIconPath, QString strSummary, QDateTime dateTime, QString strBody)
{
    SingleMsg* pSingleMsg = new SingleMsg(this, strIconPath, m_strAppName, strSummary, dateTime, strBody, m_bTakeInFlag);

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

    //当新增的消息将插入最顶部时,将已有列表最顶部的老主消息正文设置一行缩略显示
    if((0 == uIndex) && (m_listSingleMsg.count() > 0))
    {
        SingleMsg* pFirstMsg = m_listSingleMsg.at(0);
        pFirstMsg->setMainFlag(false);
        pFirstMsg->setShowLeftItemFlag(false);
        //只有已经折叠的才需要将现有的正文设置为缩略显示
        if(true == m_bFold)
        {
            pFirstMsg->setBodyLabelWordWrap(false);
            pFirstMsg->setVisible(false);
            //将SingleMsg底部设置0px空隙,当其展开时，让他完全从0展开
            pFirstMsg->setSingleMsgContentsMargins(0, 0, 0, 0);
        }
    }

    //如果插入第0条,并且已展开,则将新增消息设置自动换行,并且折叠标志设为false
    if((0 == uIndex) && (false == m_bFold))
    {
        pSingleMsg->setBodyLabelWordWrap(true);
        pSingleMsg->setFoldFlag(m_bFold);
    }

    //如果插入的不是第0条,则自己不能为主
    if(0 != uIndex)
    {
        pSingleMsg->setMainFlag(false);
        //并且已经折叠的自己不可见
        if(true == m_bFold)
        {
            pSingleMsg->setVisible(false);
        }
    }

    m_listSingleMsg.insert(uIndex, pSingleMsg);
    m_pMainVLaout->insertWidget(uIndex, pSingleMsg);

    //将该应用中最顶上的一条消息的时间赋给应用
    SingleMsg* pTopSingleMsg = m_listSingleMsg.at(0);
    m_uNotifyTime = pTopSingleMsg->getPushTime();
    m_dateTime = pTopSingleMsg->getPushDateTime();

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

    return;
}

int AppMsg::getSingleMsgCount()
{
    return m_listSingleMsg.count();
}

void AppMsg::onDeleteAppMsg()
{
    if(false == m_bTakeInFlag)
    {
        emit Sig_onDeleteAppMsg(this);              //是通知应用就通知插件删该通知应用
    }
    else
    {
        emit Sig_onDeleteTakeInAppMsg(this);        //是收纳应用就通知插件删该收纳应用
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

void AppMsg::onRecoverWholeApp()
{
    while(m_listSingleMsg.count() > 0)
    {
        SingleMsg* pSingleMsg = m_listSingleMsg.at(0);
        m_pMainVLaout->removeWidget(pSingleMsg);
        m_listSingleMsg.removeAt(0);
        emit Sig_SendAddSingleMsg(m_strAppName, pSingleMsg->getIcon(), pSingleMsg->getSummary(), pSingleMsg->getBody(), pSingleMsg->getPushDateTime(), false);
    }

    emit Sig_onDeleteTakeInAppMsg(this);

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

    //当删除一条消息后,如果应用列表为空
    if(0 == m_listSingleMsg.count())
    {
        if(false == m_bTakeInFlag)
        {
            emit Sig_onDeleteAppMsg(this);              //是通知应用就通知插件删该通知应用
        }
        else
        {
            emit Sig_onDeleteTakeInAppMsg(this);        //是收纳应用就通知插件删该收纳应用
        }
    }

    //只有当该应用属于收纳应用对象时,每删除一条都要更新收纳计数
    if(true == m_bTakeInFlag)
    {
        emit Sig_countTakeInBitAndUpate();
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

        //都是在删除单挑、收纳单挑和恢复单挑的情况下调用的setTopWithSecondItem，此时App应该都是展开状态
        pFirstMsg->setBodyLabelWordWrap(true);
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

//来自SingleMsg下的事件,处理恢复事件
void AppMsg::onRecoverSingleMsg(SingleMsg* pSingleMsg)
{
    int nIndex = m_listSingleMsg.indexOf(pSingleMsg);
    if(-1 == nIndex)
    {
        qDebug()<<"AppMsg::onTakeInSingleMsg 在通知链表中未找到pSingleMsg指针";
        return;
    }

    m_listSingleMsg.removeAt(nIndex);
    m_pMainVLaout->removeWidget(pSingleMsg);

    emit Sig_SendAddSingleMsg(m_strAppName, pSingleMsg->getIcon(), pSingleMsg->getSummary(), pSingleMsg->getBody(), pSingleMsg->getPushDateTime(), false);
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
        emit Sig_onDeleteTakeInAppMsg(this);
    }

    //只有当该应用属于收纳应用对象时,每恢复一条都要更新收纳计数
    if(true == m_bTakeInFlag)
    {
        emit Sig_countTakeInBitAndUpate();
    }
}

void AppMsg::setAppFoldFlag(bool bFlag)
{
    m_bFold = bFlag;

    //当应用处于展开状态，或者总条数小于等于1时,应用底图部件隐藏
    if((false == m_bFold) || (m_listSingleMsg.count() <= 1))
    {
        m_pAppBaseMapWidget->setVisible(false);
    }

    //false表示应用展开
    if(false == m_bFold)
    {
        //展开时,索引从第1条开始,消息全部可见
        for(int i = 1; i < m_listSingleMsg.count(); i++)
        {
            SingleMsg* pTmpSingleMsg = m_listSingleMsg.at(i);
            pTmpSingleMsg->startAnimationUnfold();
        }
    }
    else
    {
        //折叠时,索引从第1条开始,消息全部不可见
        for(int i = 1; i < m_listSingleMsg.count(); i++)
        {
            SingleMsg* pTmpSingleMsg = m_listSingleMsg.at(i);
            pTmpSingleMsg->startAnimationFold();
        }
    }

}

//当app展开时，将app设置折叠
void AppMsg::setAppFold()
{
    if(false == m_bFold)
    {
        //假如应用展开，则将应用主消息设置折叠
        SingleMsg* pFirstSingleMsg = m_listSingleMsg.at(0);
        pFirstSingleMsg->mainMsgSetFold();
    }
}

//应用主消息进入
void AppMsg::onMainMsgEnter()
{
    m_pBaseMapWidget->setStyleSheet("QWidget{background:rgba(255,255,255,0.1);border-top-left-radius:0px;border-top-right-radius:0px;border-bottom-left-radius:6px;border-bottom-right-radius:6px;}");
}

//应用主消息离开
void AppMsg::onMainMsgLeave()
{
    m_pBaseMapWidget->setStyleSheet("QWidget{background:rgba(255,255,255,0.04);border-top-left-radius:0px;border-top-right-radius:0px;border-bottom-left-radius:6px;border-bottom-right-radius:6px;}");
}

void AppMsg::onShowBaseMap()
{
    //当应用处于折叠状态，且总条数大于1时,应用底图部件显示
    if((true == m_bFold) && (m_listSingleMsg.count() > 1))
    {
        SingleMsg* pTmpSingleMsg = m_listSingleMsg.at(0);
        pTmpSingleMsg->setSingleMsgContentsMargins(0, 0, 0, 0);     //假如折叠，剩余条目显示将可见，则SingleMsg的内容均无空隙
        pTmpSingleMsg->setShowLeftItemFlag(true);
        m_pAppBaseMapWidget->setVisible(true);
    }
}

//隐藏底图部件
void AppMsg::onHideBaseMap()
{
    m_pAppBaseMapWidget->setVisible(false);
}















