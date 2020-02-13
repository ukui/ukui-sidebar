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

AppMsg::AppMsg(NotificationPlugin *parent, QString strAppName, QString strIcon)
{
    m_bTakeInFlag = false;
    this->setFixedWidth(380);

    m_strAppName = strAppName;

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

    pIconHLayout->addWidget(m_pIconToolButton, 0, Qt::AlignLeft|Qt::AlignBottom);
    pIconHLayout->addSpacerItem(pH6Spacer);
    pIconHLayout->addWidget(m_pAppNameLabel, 0, Qt::AlignLeft|Qt::AlignVCenter);
    pIconHLayout->addSpacerItem(pHExpandingSpacer);
    pIconHLayout->addWidget(m_pTimeLabel, 0, Qt::AlignRight);
    pIconWidget->setLayout(pIconHLayout);
    m_pMainVLaout->addWidget(pIconWidget, 0);

    //添加该应用的消息列表部件
    QWidget* pAppMsgListWidget = new QWidget;
    m_pAppMsgListVLaout = new QVBoxLayout();
    m_pAppMsgListVLaout->setContentsMargins(40, 0, 0, 0);
    m_pAppMsgListVLaout->setSpacing(0);
    pAppMsgListWidget->setLayout(m_pAppMsgListVLaout);
    m_pMainVLaout->addWidget(pAppMsgListWidget);


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
    QPushButton* pTakeinButton = new QPushButton();
    pTakeinButton->setText("收纳");
    pTakeinButton->setObjectName("takein");
    connect(pTakeinButton, SIGNAL(clicked()), this, SLOT(onTakein()));
    connect(this, SIGNAL(Sig_SendTakein(AppMsg*)), parent, SLOT(onTakeinMsg(AppMsg*)));
    pHButtonLayout->addWidget(pTakeinButton, 0, Qt::AlignLeft);

    QLabel* pVLabelLine = new QLabel;
    pVLabelLine->setFixedWidth(1);
    pVLabelLine->setFixedHeight(30);
    pVLabelLine->setStyleSheet("QLabel{border-style:none;border:1px solid rgba(255,255,255,0.08);}");
    pHButtonLayout->addWidget(pVLabelLine, 0, Qt::AlignHCenter);

    //设置通知消息中的删除消息按钮
    QPushButton* pClearToolButton = new QPushButton();
    pClearToolButton->setText("删除");
    pClearToolButton->setObjectName("delete");
    connect(pClearToolButton, SIGNAL(clicked()), this, SLOT(onClear()));
    connect(this, SIGNAL(Sig_Send(AppMsg*)), parent, SLOT(onClearMsg(AppMsg*)));
    pHButtonLayout->addWidget(pClearToolButton, 0, Qt::AlignRight);

    pButtonWidget->setLayout(pHButtonLayout);
    pVButtonLayout->addWidget(pButtonWidget, 0);

    m_pButtonWidget->setLayout(pVButtonLayout);
    m_pMainVLaout->addWidget(m_pButtonWidget, 0);

    QLabel* pHBottomLabelLine = new QLabel;
    pHBottomLabelLine->setFixedWidth(380);
    pHBottomLabelLine->setFixedHeight(1);
    pHBottomLabelLine->setStyleSheet("QLabel{border-style:none;border:1px solid rgba(255,255,255,0.08);}");
    m_pMainVLaout->addWidget(pHBottomLabelLine, 0);

    setLayout(m_pMainVLaout);
    return;
}

AppMsg::~AppMsg()
{

}

void AppMsg::addSingleMsg(QString strSummary, QDateTime dateTime, QString strBody)
{
    m_dateTime = dateTime;
    m_uNotifyTime = dateTime.toTime_t();

    SingleMsg* pSingleMsg = new SingleMsg(strSummary, dateTime, strBody);
    m_listSingleMsg.insert(0, pSingleMsg);
    m_pAppMsgListVLaout->insertWidget(0, pSingleMsg);  //索引0总是图标和appname那一行的部件，最后总是收纳和删除按钮部件

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
    m_pIconToolButton->setStyleSheet("QToolButton{border:1px dashed rgba(255,0,0,255);padding:0px;background:transparent;}");

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
    m_pIconToolButton->setStyleSheet("QToolButton{border:none;border-style:none;padding:0px;background:transparent;}");
//    if(false == m_strBody.isEmpty())
//    {
//        m_pBodyLabel->setWordWrap(false);
//        QFontMetrics fontMetrics(m_pBodyLabel->font());
//        int fontSize = fontMetrics.width(m_strBody);
//        QString formatSummary = m_strBody;
//        if(fontSize > (m_pBodyLabel->width() - 5))
//        {
//            formatSummary = fontMetrics.elidedText(m_strBody, Qt::ElideRight, m_pBodyLabel->width() + 195);
//        }

//        m_pBodyLabel->setText(formatSummary);
//    }
    return;
}

//鼠标点击事件
void AppMsg::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        m_pIconToolButton->setStyleSheet("QToolButton{border:none;border-style:none;padding:0px;background:transparent;}");
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

void AppMsg::onClear()
{
    emit Sig_Send(this);
    return;
}

void AppMsg::onTakein()
{
    m_bTakeInFlag = true;
    m_pButtonWidget->setVisible(false);
    emit Sig_SendTakein(this);
    return;
}
















