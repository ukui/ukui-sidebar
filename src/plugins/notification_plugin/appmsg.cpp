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

AppMsg::AppMsg(NotificationPlugin *parent, QString strAppName, QString strIcon, bool bTakeInFlag)
{
    m_bTakeInFlag = bTakeInFlag;
    this->setFixedWidth(380);

    m_strAppName = strAppName;
    m_strIcon = strIcon;

    //App信息中的总的垂直布局器
    m_pMainVLaout = new QVBoxLayout();
    m_pMainVLaout->setContentsMargins(0,0,0,0);
    m_pMainVLaout->setSpacing(0);

    //图标和时间行的水平布局部件
    QWidget* pIconWidget = new QWidget;

    //图标和时间行的水平布局器
    QHBoxLayout* pIconHLayout = new QHBoxLayout();
    pIconHLayout->setContentsMargins(12,11,26,0);
    pIconHLayout->setSpacing(0);

    //设置通知消息中的Icon，使用QToolButton
    m_pIconToolButton = new QToolButton();
    m_pIconToolButton->setStyleSheet("QToolButton{border:none;border-style:none;padding:0px;background:transparent;}");
    m_pIconToolButton->setIconSize(QSize(22,24));
    m_pIconToolButton->setIcon(QPixmap(strIcon));

    //一个水平6分辨率的弹簧
    QSpacerItem* pH6Spacer = new QSpacerItem(3, 6, QSizePolicy::Fixed, QSizePolicy::Fixed);

    //设置应用名标签，采用省略模式
    m_pAppNameLabel = new QLabel();
    m_pAppNameLabel->setObjectName("AppName");
    QFontMetrics fontMetrics1(m_pAppNameLabel->font());
    QString formatAppName = fontMetrics1.elidedText(m_strAppName, Qt::ElideRight, m_pAppNameLabel->width());
    m_pAppNameLabel->setText(formatAppName);
    m_pAppNameLabel->setStyleSheet("background-color:transparent;");

    //设置通知消息中的弹簧，水平任意伸缩使主题和时间分开
    QSpacerItem* pHExpandingSpacer = new QSpacerItem(400, 10, QSizePolicy::Expanding, QSizePolicy::Fixed);

    //设置通知消息中的通知时间
    m_pTimeLabel = new QLabel();
    m_pTimeLabel->setObjectName("pushtime");
    m_pTimeLabel->setText("现在");
    m_pTimeLabel->setStyleSheet("background-color:transparent;");

    //设置通知消息中的折叠按钮
    m_pFoldButton = new QPushButton;
    m_pFoldButton->setObjectName("fold");
    m_pFoldButton->setText("折叠");
    m_pFoldButton->setVisible(false);
    connect(m_pFoldButton, SIGNAL(clicked()), this, SLOT(onFold()));

    pIconHLayout->addWidget(m_pIconToolButton, 0, Qt::AlignLeft|Qt::AlignBottom);
    pIconHLayout->addSpacerItem(pH6Spacer);
    pIconHLayout->addWidget(m_pAppNameLabel, 0, Qt::AlignLeft|Qt::AlignVCenter);
    pIconHLayout->addSpacerItem(pHExpandingSpacer);
    pIconHLayout->addWidget(m_pTimeLabel, 0, Qt::AlignRight);
    pIconHLayout->addWidget(m_pFoldButton, 0, Qt::AlignRight);
    pIconWidget->setLayout(pIconHLayout);


    //添加该应用的消息列表部件
    QWidget* pAppMsgListWidget = new QWidget;
    m_pAppMsgListVLaout = new QVBoxLayout();
    m_pAppMsgListVLaout->setContentsMargins(40, 0, 0, 0);
    m_pAppMsgListVLaout->setSpacing(0);
    m_pShowLeftItemLabel = new QLabel;
    m_pShowLeftItemLabel->setObjectName("ShowLeftItem");
    m_pShowLeftItemLabel->setVisible(false);

    m_pAppMsgListVLaout->addWidget(m_pShowLeftItemLabel, 0, Qt::AlignLeft);

    pAppMsgListWidget->setLayout(m_pAppMsgListVLaout);

    //收纳和删除框上面的Widget,多包含一条顶横线
    m_pButtonWidget = new QWidget;
    m_pButtonWidget->setFixedSize(380,39);
    m_pButtonWidget->setVisible(false);

    //收纳和删除框上面的垂直布局器
    QVBoxLayout* pVButtonLayout = new QVBoxLayout();
    pVButtonLayout->setContentsMargins(0,0,0,0);
    pVButtonLayout->setSpacing(0);

    QLabel* pHTopLabelLine = new QLabel;
    pHTopLabelLine->setFixedWidth(380);
    pHTopLabelLine->setFixedHeight(1);
    pHTopLabelLine->setStyleSheet("QLabel{border-style:none;border:1px solid rgba(255,255,255,0.08);}");
    pVButtonLayout->addWidget(pHTopLabelLine, 0);

    //收纳和删除框上面的Widget
    QWidget* pButtonWidget = new QWidget;
    pButtonWidget->setFixedSize(380,38);

    //收纳和删除框上面的水平布局器，只布局两个按钮和中间一条分割线
    QHBoxLayout* pHButtonLayout = new QHBoxLayout();
    pHButtonLayout->setContentsMargins(2,2,3,2);
    pHButtonLayout->setSpacing(0);

    //设置一个收纳按钮
    m_pTakeinButton = new QPushButton();
    m_pTakeinButton->setText("收纳");
    m_pTakeinButton->setObjectName("takein");
    connect(m_pTakeinButton, SIGNAL(clicked()), this, SLOT(onTakeinWholeApp()));
    connect(this, SIGNAL(Sig_SendTakein(QString, QString, QString, QString, QDateTime)), parent, SLOT(onTakeinMsg(QString, QString, QString, QString, QDateTime)));

    //设置一个中间的垂直分割线
    QLabel* pVLabelLine = new QLabel;
    pVLabelLine->setFixedWidth(1);
    pVLabelLine->setFixedHeight(30);
    pVLabelLine->setStyleSheet("QLabel{border-style:none;border:1px solid rgba(255,255,255,0.08);}");

    //设置通知消息中的删除消息按钮
    m_pDeleteButton = new QPushButton();
    m_pDeleteButton->setText("删除");
    m_pDeleteButton->setObjectName("delete");
    connect(m_pDeleteButton, SIGNAL(clicked()), this, SLOT(onDeleteAppMsg()));
    if(false == m_bTakeInFlag)
    {
        connect(this, SIGNAL(Sig_onDeleteAppMsg(AppMsg*)), parent, SLOT(onClearMsg(AppMsg*)));
    }
    else
    {
        connect(this, SIGNAL(Sig_onDeleteTakeInAppMsg(AppMsg*)), parent, SLOT(onClearTakeInMsg(AppMsg*)));
    }

    pHButtonLayout->addWidget(m_pTakeinButton, 0, Qt::AlignLeft);
    pHButtonLayout->addWidget(pVLabelLine, 0, Qt::AlignHCenter);
    pHButtonLayout->addWidget(m_pDeleteButton, 0, Qt::AlignRight);

    pButtonWidget->setLayout(pHButtonLayout);
    pVButtonLayout->addWidget(pButtonWidget, 0);
    m_pButtonWidget->setLayout(pVButtonLayout);


    QLabel* pHBottomLabelLine = new QLabel;
    pHBottomLabelLine->setFixedWidth(380);
    pHBottomLabelLine->setFixedHeight(1);
    pHBottomLabelLine->setStyleSheet("QLabel{border-style:none;border:1px solid rgba(255,255,255,0.08);}");

    m_pMainVLaout->addWidget(pIconWidget, 0);
    m_pMainVLaout->addWidget(pAppMsgListWidget);
    m_pMainVLaout->addWidget(m_pButtonWidget, 0);
    m_pMainVLaout->addWidget(pHBottomLabelLine, 0);
    setLayout(m_pMainVLaout);

    return;
}

AppMsg::~AppMsg()
{

}

//收纳单条消息至收纳盒，也需要new，因为收纳次序不定，所以根据时间插入位置, 来自上层NotificationPlugin的新增调用(新增收纳消息)
void AppMsg::addTakeinSingleMsg(QString strSummary, QDateTime dateTime, QString strBody)
{
    SingleMsg* pSingleMsg = new SingleMsg(this, strSummary, dateTime, strBody, true);

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

    m_listSingleMsg.insert(uIndex, pSingleMsg);
    m_pAppMsgListVLaout->insertWidget(uIndex, pSingleMsg);

    SingleMsg* pTopSingleMsg = m_listSingleMsg.at(0); //将该应用中最顶上的一条消息的时间赋给应用
    m_uNotifyTime = pTopSingleMsg->getPushTime();
    m_dateTime = pTopSingleMsg->getPushDateTime();

    return;
}

//新增单条消息至通知列表，崭新消息需要new，然后添加至列表最上面
void AppMsg::addSingleMsg(QString strSummary, QDateTime dateTime, QString strBody)
{
    m_dateTime = dateTime;
    m_uNotifyTime = dateTime.toTime_t();

    if(m_listSingleMsg.count() > 0) //只要新增加前已存在条数，则先将最顶部一条的顶边线和推送时间设置可见
    {
        SingleMsg* pFirstMsg = m_listSingleMsg.at(0);
        pFirstMsg->setTopLabelLineVisible(true);
        pFirstMsg->setTimeLabelVisible(true);
        pFirstMsg->setBodyLabelWordWrap(true);
    }

    SingleMsg* pSingleMsg = new SingleMsg(this, strSummary, dateTime, strBody);
    m_listSingleMsg.insert(0, pSingleMsg);
    m_pAppMsgListVLaout->insertWidget(0, pSingleMsg);

    int nShowLeftCount = m_listSingleMsg.count() - 1;
    QString strShowLeft = "还有" + QString::number(nShowLeftCount) + "则通知";
    QString strSetText;
    strSetText.append("<p style='line-height:24px'>").append(strShowLeft).append("</p>");
    m_pShowLeftItemLabel->setText(strSetText);

    //当剩余条数大于0，且剩余数显示标签和折叠按钮都不可见，则将剩余数显示标签设置可见，由于总条数大于1，将收纳和删除修改为全部收纳和全部删除
    if(nShowLeftCount > 0 && (false == m_pShowLeftItemLabel->isVisible()) && (false == m_pFoldButton->isVisible()))
    {
        m_pShowLeftItemLabel->setVisible(true);
        m_pTakeinButton->setText("全部收纳");
        m_pDeleteButton->setText("全部删除");
    }

    //如果剩余数显示标签可见，则索引从1开始，将所有SingleMsg设置不可见
    if(true == m_pShowLeftItemLabel->isVisible())
    {
        for(int i = 1; i < m_listSingleMsg.count(); i++)
        {
            SingleMsg* pTmpSingleMsg = m_listSingleMsg.at(i);
            pTmpSingleMsg->setVisible(false);
        }
    }

    //如果折叠按钮可见，则新增信息也展开消息
    if(true == m_pFoldButton->isVisible())
    {
        pSingleMsg->setBodyLabelWordWrap(true);
    }


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
        m_pTimeLabel->setText(strPushDate);
        return;
    }

    QDate lastDate = currentDate.addDays(-1);
    if(m_dateTime.date() == lastDate)
    {
        QString strPushDate = "昨天 ";
        strPushDate = strPushDate + m_dateTime.toString("hh:mm");
        m_pTimeLabel->setText(strPushDate);
        return;
    }

    QString strPushDate = m_dateTime.toString("yyyy/MM/dd");
    m_pTimeLabel->setText(strPushDate);
    return;

}

void AppMsg::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    if(false == m_bTakeInFlag)  //当不在收纳盒时，悬停在消息上才显示收纳和删除按钮
    {
        m_pButtonWidget->setVisible(true);
    }
    setStyleSheet("background-color:rgba(255,255,255,0.08);");

    return;
}

void AppMsg::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    if(false == m_bTakeInFlag)
    {
        m_pButtonWidget->setVisible(false);
    }

    setStyleSheet("background-color:rgba(26,26,26,0.95);");
    return;
}

//鼠标点击事件
void AppMsg::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        //点击展开所有列表
        SingleMsg* pFirstMsg = m_listSingleMsg.at(0);
        pFirstMsg->setTimeLabelVisible(true);
        pFirstMsg->setBodyLabelWordWrap(true);

        for(int i = 1; i < m_listSingleMsg.count(); i++)
        {
            SingleMsg* pTmpSingleMsg = m_listSingleMsg.at(i);
            pTmpSingleMsg->setVisible(true);
        }
        m_pShowLeftItemLabel->setVisible(false);
        m_pTimeLabel->setVisible(false);
        m_pFoldButton->setVisible(true);


//        if(false == m_strBody.isEmpty())
//        {
////            QFontMetrics fontMetrics(m_pBodyLabel->font());
////            int fontSize = fontMetrics.width(m_strBody);
////            int nRow = fontSize / 305;
////            int nRemaider = fontSize % 305;
////            if(nRemaider > 0)
////            {
////                nRow++;
////            }
////            m_pBodyLabel->setFixedHeight(6 + 24 * nRow);

//            m_pBodyLabel->setText(m_strBody);
//            m_pBodyLabel->setWordWrap(true);
////            m_pBodyLabel->adjustSize();
////            m_pBodyLabel->setAlignment(Qt::AlignTop);
//        }
    }
    return;
}

void AppMsg::onDeleteAppMsg()
{
    emit Sig_onDeleteAppMsg(this);
    return;
}

void AppMsg::onTakeinWholeApp()
{
    while(m_listSingleMsg.count() > 0)
    {
        SingleMsg* pSingleMsg = m_listSingleMsg.at(0);
        m_pAppMsgListVLaout->removeWidget(pSingleMsg);
        m_listSingleMsg.removeAt(0);
        emit Sig_SendTakein(m_strAppName, m_strIcon, pSingleMsg->getSummary(), pSingleMsg->getBody(), pSingleMsg->getPushDateTime());
    }

    emit Sig_onDeleteAppMsg(this);

    return;
}

//折叠消息列表
void AppMsg::onFold()
{
    SingleMsg* pFirstMsg = m_listSingleMsg.at(0);
    pFirstMsg->setTimeLabelVisible(false);
    pFirstMsg->setBodyLabelWordWrap(false);

    for(int i = 1; i < m_listSingleMsg.count(); i++)
    {
        SingleMsg* pTmpSingleMsg = m_listSingleMsg.at(i);
        pTmpSingleMsg->setVisible(false);
    }

    if(m_listSingleMsg.count() > 1)
    {
        m_pShowLeftItemLabel->setVisible(true);
    }
    m_pTimeLabel->setVisible(true);
    m_pFoldButton->setVisible(false);
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
    m_pAppMsgListVLaout->removeWidget(pSingleMsg);
    pSingleMsg->deleteLater();

    if(0 == m_listSingleMsg.count())
    {
        if(false == m_bTakeInFlag)
        {
            emit Sig_onDeleteAppMsg(this);
        }
        else
        {
            emit Sig_onDeleteTakeInAppMsg(this);
        }
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
    m_pAppMsgListVLaout->removeWidget(pSingleMsg);

    emit Sig_SendTakein(m_strAppName, m_strIcon, pSingleMsg->getSummary(), pSingleMsg->getBody(), pSingleMsg->getPushDateTime());
    pSingleMsg->deleteLater();

    if(0 == m_listSingleMsg.count())
    {
        emit Sig_onDeleteAppMsg(this);
    }
}
















