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
#include "notificationPlugin.h"
#include "singlemsg.h"
#include "monitorthread.h"
#include "customstylePushbutton2.h"
AppMsg::AppMsg(NotificationPlugin *parent, QString strAppName, bool bTakeInFlag)
{
    m_bFold = true;
    m_bTakeInFlag = bTakeInFlag;
    m_strAppName = strAppName;
    this->setFixedWidth(380);
    m_nMaxCount = 3;

    //-->
    //折叠按钮和删除按钮部分
    m_pFoldBtnWid = new QWidget(this);
    QHBoxLayout *m_pFoldBtnHLaout = new QHBoxLayout();
    m_pFoldBtnHLaout->setContentsMargins(0,0,0,0);
    m_foldBtn = new QPushButton(m_pFoldBtnWid);

    m_foldBtn->setStyleSheet("QPushButton{background:rgba(255,255,255,31); border:0px; border-radius:6px;}"
                             "QPushButton:hover{background:rgba(255,255,255,71); border:0px; border-radius:6px;}"
                             "QPushButton:pressed{background:rgba(255,255,255,41); border:0px; border-radius:6px;}");
    QPainter p(m_foldBtn);
    QRect rect = m_foldBtn->rect();
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.setBrush(QBrush(QColor(0, 0, 255, 255)));
    p.setPen(Qt::transparent);
    p.drawRoundedRect(rect,6,6);

    m_foldBtn->setObjectName("fold"); 
    m_foldBtn->setLayoutDirection(Qt::LeftToRight);
    m_foldBtn->setIcon(QIcon::fromTheme("kylin-fold-hover").pixmap(17,17));
    m_foldBtn->setText(QObject::tr(" fold"));
    m_foldBtn->setFixedSize(88,36);
    connect(m_foldBtn,&QPushButton::clicked,this,&AppMsg::onFoldAppWidget);

    m_delBtn = new QPushButton();
    m_delBtn->setStyleSheet("QPushButton{background:rgba(255,255,255,31); border:0px; border-radius:12px;}"
                             "QPushButton:hover{background:rgba(255,255,255,71); border:0px; border-radius:12px;}"
                             "QPushButton:pressed{background:rgba(255,255,255,41); border:0px; border-radius:12px;}");
    m_delBtn->setIcon(QIcon(":/images/hover.svg"));
    m_delBtn->setIcon(QIcon::fromTheme("edit-clear-symbolic").pixmap(12,12));
    m_delBtn->setFixedSize(24,24);
    connect(m_delBtn,&QPushButton::clicked,this,&AppMsg::onDelAppMsg);
    m_pFoldBtnHLaout->addWidget(m_foldBtn);
    m_pFoldBtnHLaout->addItem(new QSpacerItem(256, 10, QSizePolicy::Expanding));
    m_pFoldBtnHLaout->addWidget(m_delBtn);
    m_pFoldBtnHLaout->addItem(new QSpacerItem(6, 10, QSizePolicy::Fixed));

    QVBoxLayout *m_pFoldBtnVLaout = new QVBoxLayout();
    m_pFoldBtnVLaout->setContentsMargins(0,0,0,0);
    m_pFoldBtnVLaout->addLayout(m_pFoldBtnHLaout);
    m_pFoldBtnVLaout->addItem(new QSpacerItem(10, 6, QSizePolicy::Fixed));


    m_pFoldBtnWid->setContentsMargins(0,0,0,0);
    m_pFoldBtnWid->setLayout(m_pFoldBtnVLaout);
    m_pFoldBtnWid->setFixedSize(380,42);
    if(m_bFold || (m_listSingleMsg.count()<=1))
        m_pFoldBtnWid->setVisible(false);
    else
        m_pFoldBtnWid->setVisible(true);
    //--<

    //App信息中的总的垂直布局器
    m_pMainVLaout = new QVBoxLayout();
    m_pMainVLaout->setContentsMargins(0,0,0,0);
    m_pMainVLaout->setSpacing(6);

    //如果只有m_pMainVLaout一个管理所有消息列表，当应用消息动态展开时，0号消息会出现闪屏的情况
    //为了规避上述情况，m_pMainVLaout中只防止0号消息，1号消息起全部放置m_pIndexFromOneVLaout中
    m_pIndexFromOneVLaout = new QVBoxLayout();
    m_pIndexFromOneVLaout->setContentsMargins(0,0,0,0);
    m_pIndexFromOneVLaout->setSpacing(6);
    m_pMainVLaout->addLayout(m_pIndexFromOneVLaout);

    //当出现多条消息时，增加底图
    m_pAppBaseMapWidget = new QWidget;
    QVBoxLayout* pBaseMapVLaout = new QVBoxLayout();
    pBaseMapVLaout->setContentsMargins(0,0,0,0);
    pBaseMapVLaout->setSpacing(0);

    m_pBaseMapWidget = new QWidget;
    m_pBaseMapWidget->setObjectName("BaseMap");
    m_pBaseMapWidget->setFixedWidth(360);
    m_pBaseMapWidget->setFixedHeight(0);
    m_pAppBaseMapWidget->setAttribute(Qt::WA_TranslucentBackground);
    m_pAppBaseMapWidget->setLayout(pBaseMapVLaout);
    m_pMainVLaout->addWidget(m_pAppBaseMapWidget, 0 , Qt::AlignHCenter);
    m_pAppBaseMapWidget->setVisible(false);

    m_pMainWid = new QWidget(this);
    m_pMainWid->setContentsMargins(0,0,0,0);
    m_pMainWid->setLayout(m_pMainVLaout);

    m_pMainBaseVLaout = new QVBoxLayout();
    m_pMainBaseVLaout->setContentsMargins(0,0,0,0);
    //m_pMainBaseVLaout->addWidget(m_pFoldBtnWid);
    m_pMainBaseVLaout->addWidget(m_pMainWid);
    this->setLayout(m_pMainBaseVLaout);

    //发个信号通知插件删除该通知应用消息
    connect(this, SIGNAL(Sig_onDeleteAppMsg(AppMsg*)), parent, SLOT(onClearAppMsg(AppMsg*)));
    //发个信号通知插件删除该收纳应用消息
    connect(this, SIGNAL(Sig_onDeleteTakeInAppMsg(AppMsg*)), parent, SLOT(onClearTakeInAppMsg(AppMsg*)));

    //发个信号通知插件收纳单条应用消息
    connect(this, SIGNAL(Sig_SendTakeInSingleMsg(QString, QString, QString, QString, QString, QString, QDateTime,int, bool)),
            parent, SLOT(onTakeInSingleNotify(QString, QString, QString, QString, QString, QString, QDateTime,int, bool)));
    //发个信号通知插件恢复单条应用消息
    connect(this, SIGNAL(Sig_SendAddSingleMsg(QString, QString, QString, QString, QString, QString, QDateTime, int, bool)),
            parent, SLOT(onAddSingleNotify(QString, QString, QString, QString, QString, QString, QDateTime, int, bool)));

    //发个统计收纳数更新信号
    connect(this, SIGNAL(Sig_countTakeInBitAndUpate()), parent, SLOT(onCountTakeInBitAndUpate()));

    return;
}

void AppMsg::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QRect rect = this->rect();
    if(!m_pFoldBtnWid->isVisible()){
        rect.setWidth(rect.width() - 1);
        rect.setHeight(rect.height() - 1);
        p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
        p.setBrush(QBrush(QColor(255, 255, 255, 10)));
        p.setPen(Qt::transparent);
        p.drawRoundedRect(rect,6,6);
    }else{
        rect.setY(rect.y() + 50);
        rect.setWidth(rect.width() - 1);
        rect.setHeight(rect.height() - 1);
        p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
        p.setBrush(QBrush(QColor(255, 255, 255, 10)));
        p.setPen(Qt::transparent);
        p.drawRoundedRect(rect,6,6);
    }

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
    if ((true == m_bFold) && (nShowLeftCount > 0)) {
        m_pAppBaseMapWidget->setVisible(true);
    } else {
        m_pAppBaseMapWidget->setVisible(false);
    }

    SingleMsg* pTopSingleMsg = m_listSingleMsg.at(0);
    pTopSingleMsg->setLeftItem(nShowLeftCount);
    return;
}

//当显示的最大消息大于设置的消息数目时删除最早的消息
void AppMsg::deleteExceedingMsg()
{
    int nIndex = -1;
    while (m_listSingleMsg.count() > m_nMaxCount)
    {
        nIndex = m_listSingleMsg.count() - 1;
        if (-1 == nIndex)
        {
            return;
        }

        SingleMsg* pSingleMsg = m_listSingleMsg.at(nIndex);
        onDeleSingleMsg(pSingleMsg);
    }
}


//新增单条消息至通知列表，崭新消息需要new，然后添加至列表最上面
void AppMsg::addSingleMsg(QString strIconPath, QString strSummary, QDateTime dateTime, QString strBody, QString strUrl, QString strAction)
{
    SingleMsg* pSingleMsg = new SingleMsg(this, strIconPath, m_strAppName, strSummary, dateTime, strBody, strUrl, strAction, m_bTakeInFlag);

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
            pFirstMsg-> setBodyLabelWordWrap(false);
            pFirstMsg->setVisible(false);
            //将SingleMsg底部设置0px空隙,当其展开时，让他完全从0展开
            pFirstMsg->setSingleMsgContentsMargins(0, 0, 0, 0);
        }

        //如果新增的消息将插入最顶部，则将老的顶部消息，先从m_pMainVLaout移除，再插入m_pIndexFromOneVLaout顶部
        m_pMainVLaout->removeWidget(pFirstMsg);
        m_pIndexFromOneVLaout->insertWidget(0, pFirstMsg);
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
    if(0 != uIndex)
    {
        //假如新增消息不是插入最顶部，则直接插入m_pIndexFromOneVLaout中的uIndex - 1
        m_pIndexFromOneVLaout->insertWidget(uIndex - 1, pSingleMsg);
    }
    else
    {
        //假如新增的消息将插入最顶部，由于上面已把老的顶部消息插入m_pIndexFromOneVLaout的顶部，所以此时直接插入m_pMainVLaout顶部
        m_pMainVLaout->insertWidget(0, pSingleMsg);
    }

    //当单个应用的消息达到设置的最大数目时，删除最早的消息并统计数目
    deleteExceedingMsg();

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
        m_listSingleMsg.removeAt(0);
        m_pMainVLaout->removeWidget(pSingleMsg);
        if(m_listSingleMsg.count() > 0)
        {
            SingleMsg* pTopSingleMsg = m_listSingleMsg.at(0);
            m_pIndexFromOneVLaout->removeWidget(pTopSingleMsg);
            m_pMainVLaout->insertWidget(0, pTopSingleMsg);
        }

        emit Sig_SendTakeInSingleMsg(m_strAppName, pSingleMsg->getIcon(), pSingleMsg->getSummary(),
                                     pSingleMsg->getBody(), pSingleMsg->getUrl(), pSingleMsg->getAction(),
                                     pSingleMsg->getPushDateTime(), 20, false);
    }

    emit Sig_onDeleteAppMsg(this);

    return;
}

void AppMsg::onRecoverWholeApp()
{
    while(m_listSingleMsg.count() > 0)
    {
        SingleMsg* pSingleMsg = m_listSingleMsg.at(0);
        m_listSingleMsg.removeAt(0);
        m_pMainVLaout->removeWidget(pSingleMsg);
        if(m_listSingleMsg.count() > 0)
        {
            SingleMsg* pTopSingleMsg = m_listSingleMsg.at(0);
            m_pIndexFromOneVLaout->removeWidget(pTopSingleMsg);
            m_pMainVLaout->insertWidget(0, pTopSingleMsg);
        }

        emit Sig_SendAddSingleMsg(m_strAppName, pSingleMsg->getIcon(), pSingleMsg->getSummary(),
                                  pSingleMsg->getBody(), pSingleMsg->getUrl(), pSingleMsg->getAction(),
                                  pSingleMsg->getPushDateTime(), 20, false);
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
    if(0 == nIndex)
    {
        m_pMainVLaout->removeWidget(pSingleMsg);
        if(m_listSingleMsg.count() > 0)
        {
            SingleMsg* pTopSingleMsg = m_listSingleMsg.at(0);
            m_pIndexFromOneVLaout->removeWidget(pTopSingleMsg);
            m_pMainVLaout->insertWidget(0, pTopSingleMsg);
        }
    }
    else
    {
        m_pIndexFromOneVLaout->removeWidget(pSingleMsg);
    }
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
    if(0 == nIndex)
    {
        m_pMainVLaout->removeWidget(pSingleMsg);
        if(m_listSingleMsg.count() > 0)
        {
            SingleMsg* pTopSingleMsg = m_listSingleMsg.at(0);
            m_pIndexFromOneVLaout->removeWidget(pTopSingleMsg);
            m_pMainVLaout->insertWidget(0, pTopSingleMsg);
        }
    }
    else
    {
        m_pIndexFromOneVLaout->removeWidget(pSingleMsg);
    }

    emit Sig_SendTakeInSingleMsg(m_strAppName, pSingleMsg->getIcon(), pSingleMsg->getSummary(),
                                 pSingleMsg->getBody(),  pSingleMsg->getUrl(), pSingleMsg->getAction(),
                                 pSingleMsg->getPushDateTime(), 20, false);
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
    if(0 == nIndex)
    {
        m_pMainVLaout->removeWidget(pSingleMsg);
        if(m_listSingleMsg.count() > 0)
        {
            SingleMsg* pTopSingleMsg = m_listSingleMsg.at(0);
            m_pIndexFromOneVLaout->removeWidget(pTopSingleMsg);
            m_pMainVLaout->insertWidget(0, pTopSingleMsg);
        }
    }
    else
    {
        m_pIndexFromOneVLaout->removeWidget(pSingleMsg);
    }


    emit Sig_SendAddSingleMsg(m_strAppName, pSingleMsg->getIcon(), pSingleMsg->getSummary(),
                              pSingleMsg->getBody(),  pSingleMsg->getUrl(), pSingleMsg->getAction(),
                              pSingleMsg->getPushDateTime(), 20, false);
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

    if(m_listSingleMsg.count() <= 1)
    {
        return;
    }

    //false表示应用展开
    if(false == m_bFold)
    {
        //-->
        //折叠按钮显示动画：App消息窗口下移，折叠按钮窗口下移
        if(m_listSingleMsg.count()>1)
            m_pFoldBtnWid->setVisible(true);
        int widthFoldWid = m_pFoldBtnWid->width();
        int heightFoldWid = m_pFoldBtnWid->height();
        QPropertyAnimation* pAnimation2 = new QPropertyAnimation(this, "geometryFold");
        connect(pAnimation2, &QPropertyAnimation::valueChanged, this, [=](const QVariant &value){
            QRect Rect = value.value<QRect>();
            int x1, y1, x2, y2;
            Rect.getRect(&x1, &y1, &x2, &y2);
            m_pFoldBtnWid->setGeometry(x1, y1, x2, y2);
        });
        connect(pAnimation2, &QPropertyAnimation::finished, this,[=](){
            m_pMainBaseVLaout->insertWidget(0,m_pFoldBtnWid);
        });
        pAnimation2->setDuration(100);
        pAnimation2->setStartValue(QRect(0, 0-heightFoldWid, widthFoldWid, heightFoldWid));
        pAnimation2->setEndValue(QRect(0, 0, widthFoldWid, heightFoldWid));
        pAnimation2->start(QAbstractAnimation::DeleteWhenStopped);

        int widthAppWid = m_pMainWid->width();
        int heightAppWid = m_pMainWid->height();
        QPropertyAnimation* pAnimation1 = new QPropertyAnimation(this, "geometryMain");
        connect(pAnimation1, &QPropertyAnimation::valueChanged, this, [=](const QVariant &value){
            QRect Rect = value.value<QRect>();
            int x1, y1, x2, y2;
            Rect.getRect(&x1, &y1, &x2, &y2);
            m_pMainWid->setGeometry(x1, y1, x2, y2);
        });
        connect(pAnimation1, &QPropertyAnimation::finished, this,[=](){
            //多条消息展开动画：展开时,索引从第1条开始,消息全部可见
            SingleMsg* pFristSingleMsg = m_listSingleMsg.at(0);  //展开第一条消息的正文内容
            pFristSingleMsg->setBodyLabelWordWrap(true);
            pFristSingleMsg->m_bAppFold = false;
            for(int i = 1; i < m_listSingleMsg.count(); i++)
            {
                SingleMsg* pTmpSingleMsg = m_listSingleMsg.at(i);
                pTmpSingleMsg->setBodyLabelWordWrap(true);
                pTmpSingleMsg->setFoldFlag(false);
                pTmpSingleMsg->m_bAppFold = false;
                pTmpSingleMsg->startAnimationUnfold();
            }
        });
        pAnimation1->setDuration(100);
        pAnimation1->setStartValue(QRect(0, 0, widthAppWid, heightAppWid));
        pAnimation1->setEndValue(QRect(0, m_pFoldBtnWid->height(), widthAppWid, heightAppWid));
        pAnimation1->start(QAbstractAnimation::DeleteWhenStopped);
        //--<

    }
    else
    {
        //折叠时,索引从第1条开始,消息全部不可见
        for(int i = 1; i < m_listSingleMsg.count(); i++)
        {
            SingleMsg* pTmpSingleMsg = m_listSingleMsg.at(i);
            pTmpSingleMsg->startAnimationFold();
        }
        m_pMainBaseVLaout->removeWidget(m_pFoldBtnWid);
        m_pFoldBtnWid->setVisible(false);
    }

}

//折叠整个应用的消息
void AppMsg::onFoldAppWidget()
{
    //折叠按钮显示动画：App消息窗口上移，折叠按钮窗口上移
    m_bFold = true;

    int widthFoldWid = m_pFoldBtnWid->width();
    int heightFoldWid = m_pFoldBtnWid->height();
    QPropertyAnimation* pAnimation2 = new QPropertyAnimation(this, "btnWidFold");
    connect(pAnimation2, &QPropertyAnimation::valueChanged, this, [=](const QVariant &value){
        QRect Rect = value.value<QRect>();
        int x1, y1, x2, y2;
        Rect.getRect(&x1, &y1, &x2, &y2);
        m_pFoldBtnWid->setGeometry(x1, y1, x2, y2);
    });
    connect(pAnimation2, &QPropertyAnimation::finished, this,[=](){
        m_pFoldBtnWid->setVisible(false);
        m_pMainBaseVLaout->removeWidget(m_pFoldBtnWid);
        emit Sig_foldAnimationFinish();
    });
    pAnimation2->setDuration(100);
    pAnimation2->setStartValue(QRect(0, 0, widthFoldWid, heightFoldWid));
    pAnimation2->setEndValue(QRect(0, 0-heightFoldWid, widthFoldWid, heightFoldWid));
    pAnimation2->start(QAbstractAnimation::DeleteWhenStopped);

    int widthAppWid = m_pMainWid->width();
    int heightAppWid = m_pMainWid->height();
    QPropertyAnimation* pAnimation1 = new QPropertyAnimation(this, "appMainFold");
    connect(pAnimation1, &QPropertyAnimation::valueChanged, this, [=](const QVariant &value){
        QRect Rect = value.value<QRect>();
        int x1, y1, x2, y2;
        Rect.getRect(&x1, &y1, &x2, &y2);
        m_pMainWid->setGeometry(x1, y1, x2, y2);
    });
    connect(pAnimation1, &QPropertyAnimation::finished, this,[=](){
        //折叠时,索引从第1条开始,消息全部不可见
        SingleMsg* pFristSingleMsg = m_listSingleMsg.at(0);  //折叠第一条消息的正文内容
        pFristSingleMsg->setBodyLabelWordWrap(false);
        pFristSingleMsg->m_bAppFold = true;
        pFristSingleMsg->setFoldFlag(true);
        for(int i = 1; i < m_listSingleMsg.count(); i++)
        {
            SingleMsg* pTmpSingleMsg = m_listSingleMsg.at(i);
            pTmpSingleMsg->setBodyLabelWordWrap(false);
            pTmpSingleMsg->m_bAppFold = true;
            pTmpSingleMsg->setFoldFlag(true);
            pTmpSingleMsg->startAnimationFold();
        }
        m_pMainBaseVLaout->removeWidget(m_pFoldBtnWid);
        m_pFoldBtnWid->setVisible(false);
    });
    pAnimation1->setDuration(100);
    pAnimation1->setStartValue(QRect(0, m_pFoldBtnWid->height(), widthAppWid, heightAppWid));
    pAnimation1->setEndValue(QRect(0, 0, widthAppWid, heightAppWid));
    pAnimation1->start(QAbstractAnimation::DeleteWhenStopped);
    //--<
}

void AppMsg::onDelAppMsg()
{
    //删除整个应用消息动画：先折叠，再左移动画，最后上移动画
    SingleMsg* pFristSingleMsg = m_listSingleMsg.at(0);
    connect(this,&AppMsg::Sig_foldAnimationFinish,this,[=](){
        QTimer *timer = new QTimer();
        timer->setSingleShot(true);                //设置一个单次定时器,只为延迟200毫秒,等待折叠动画完成
        connect(timer, &QTimer::timeout, this, [=](){
            pFristSingleMsg->onDele();   //开启左移动画，上移动画
        });
        timer->start(200);
    });
    onFoldAppWidget();
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
    m_pFoldBtnWid->setVisible(false);  //单条消息不显示折叠按钮
}

//应用主消息进入
void AppMsg::onMainMsgEnter()
{
    //m_pBaseMapWidget->setStyleSheet("QWidget{background:rgba(255,255,255,0.1);border-top-left-radius:0px;border-top-right-radius:0px;border-bottom-left-radius:6px;border-bottom-right-radius:6px;}");
}

//应用主消息离开
void AppMsg::onMainMsgLeave()
{
    //m_pBaseMapWidget->setStyleSheet("QWidget{background:rgba(255,255,255,0.04);border-top-left-radius:0px;border-top-right-radius:0px;border-bottom-left-radius:6px;border-bottom-right-radius:6px;}");
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

