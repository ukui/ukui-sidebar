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


#include "singlemsg.h"
#include "notification_plugin.h"

SingleMsg::SingleMsg(NotificationPlugin *parent, QString strAppName, QString strIcon, QString strSummary, QDateTime dateTime, QString strBody)
{
    m_bTakeInFlag = false;

    setObjectName("singlemsg");
    this->setFixedWidth(380);

    m_strAppName = strAppName;
    m_uNotifyTime = dateTime.toTime_t();

    //单条信息中的总的垂直布局器
    QVBoxLayout* pMainVLaout = new QVBoxLayout();
    pMainVLaout->setContentsMargins(0,0,0,0);
    pMainVLaout->setSpacing(0);

    //图标和时间行的水平布局部件
    QWidget* pIconWidget = new QWidget;

    //图标和时间行的水平布局器
    QHBoxLayout* pIconHLayout = new QHBoxLayout();
    pIconHLayout->setContentsMargins(12,0,26,0);
    pIconHLayout->setSpacing(0);

    //设置通知消息中的Icon，使用QToolButton
    QToolButton* pIconToolButton = new QToolButton();
    pIconToolButton->setStyleSheet("QToolButton{border:none;border-style:none;padding:0px;background:transparent;}");
    pIconToolButton->setIconSize(QSize(22,24));
    pIconToolButton->setIcon(QPixmap(strIcon));

    //一个水平6分辨率的弹簧
    QSpacerItem* pH6Spacer = new QSpacerItem(6, 6, QSizePolicy::Fixed, QSizePolicy::Fixed);

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
    QString strTransTime = dateTime.toString("hh:mm:ss");
    QLabel* pTimeLabel = new QLabel(strTransTime);
    pTimeLabel->setObjectName("pushtime");
    pTimeLabel->setStyleSheet("background-color:transparent;");

    pIconHLayout->addWidget(pIconToolButton, 0, Qt::AlignLeft|Qt::AlignBottom);
    pIconHLayout->addSpacerItem(pH6Spacer);
    pIconHLayout->addWidget(m_pAppNameLabel, 0, Qt::AlignLeft|Qt::AlignVCenter);
    pIconHLayout->addSpacerItem(pHExpandingSpacer);
    pIconHLayout->addWidget(pTimeLabel, 0, Qt::AlignRight);
    pIconWidget->setLayout(pIconHLayout);
    pMainVLaout->addWidget(pIconWidget, 0);


    //图标和时间行的水平布局部件
    QWidget* pSummaryWidget = new QWidget;
    //设置主题的水平布局器
    QHBoxLayout* pHSummaryLayout = new QHBoxLayout();
    pHSummaryLayout->setContentsMargins(43,0,0,0);
    pHSummaryLayout->setSpacing(0);
    //设置通知消息中的主题，采用省略模式
    QLabel* pSummaryLabel = new QLabel();
    pSummaryLabel->setObjectName("Summary");
    pSummaryLabel->setMaximumWidth(300);
    pSummaryLabel->setStyleSheet("background-color:transparent;");

    QFontMetrics fontMetrics(pSummaryLabel->font());
    QString formatSummary = fontMetrics.elidedText(strSummary, Qt::ElideRight, pSummaryLabel->width());
    pSummaryLabel->setText(formatSummary);
    pHSummaryLayout->addWidget(pSummaryLabel, 0, Qt::AlignLeft);
    pSummaryWidget->setLayout(pHSummaryLayout);
    pMainVLaout->addWidget(pSummaryWidget);

    //设置通知消息中的正文QLabel，行高18px,采用自动换行模式
    if(false == strBody.isEmpty())
    {
        m_strBody = strBody;
        //图标和时间行的水平布局部件
        QWidget* pBodyWidget = new QWidget;
        QHBoxLayout* pHBodyLayout = new QHBoxLayout();
        pHBodyLayout->setContentsMargins(43,0,0,0);
        m_pBodyLabel = new QLabel();
        m_pBodyLabel->setObjectName("body");
        m_pBodyLabel->setFixedWidth(305);
        m_pBodyLabel->setStyleSheet("background-color:transparent;");
        QFontMetrics fontMetrics(m_pBodyLabel->font());
        QString formatSummary = fontMetrics.elidedText(strBody, Qt::ElideRight, m_pBodyLabel->width() - 50);
        m_pBodyLabel->setText(formatSummary);
        pHBodyLayout->addWidget(m_pBodyLabel, 0, Qt::AlignLeft);
        pBodyWidget->setLayout(pHBodyLayout);
        pMainVLaout->addWidget(pBodyWidget);
    }

    //收纳和删除框上面的Widget,多包含一条顶横线
    m_pButtonWidget = new QWidget;
    qDebug()<<"SingleMsg::SingleMsg"<<m_pButtonWidget->parent();
    m_pButtonWidget->setFixedSize(380,39);
    m_pButtonWidget->setVisible(false);

    //收纳和删除框上面的垂直布局器
    QVBoxLayout* pVButtonLayout = new QVBoxLayout();
    pVButtonLayout->setContentsMargins(0,0,0,0);
    pVButtonLayout->setSpacing(0);

    QLabel* pHTopLabelLine = new QLabel;
    pHTopLabelLine->setFixedWidth(380);
    pHTopLabelLine->setFixedHeight(1);
    pHTopLabelLine->setStyleSheet("QLabel{border-style:none;border:1px solid #242424;}");
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
    connect(this, SIGNAL(Sig_SendTakein(SingleMsg*)), parent, SLOT(onTakeinMsg(SingleMsg*)));
    pHButtonLayout->addWidget(pTakeinButton, 0, Qt::AlignLeft);

    QLabel* pVLabelLine = new QLabel;
    pVLabelLine->setFixedWidth(1);
    pVLabelLine->setFixedHeight(30);
    pVLabelLine->setStyleSheet("QLabel{border-style:none;border:1px solid #242424;}");
    pHButtonLayout->addWidget(pVLabelLine, 0, Qt::AlignHCenter);

    //设置通知消息中的删除消息按钮
    QPushButton* pClearToolButton = new QPushButton();
    pClearToolButton->setText("删除");
    pClearToolButton->setObjectName("delete");
    connect(pClearToolButton, SIGNAL(clicked()), this, SLOT(onClear()));
    connect(this, SIGNAL(Sig_Send(SingleMsg*)), parent, SLOT(onClearMsg(SingleMsg*)));
    pHButtonLayout->addWidget(pClearToolButton, 0, Qt::AlignRight);

    pButtonWidget->setLayout(pHButtonLayout);
    pVButtonLayout->addWidget(pButtonWidget, 0);

    m_pButtonWidget->setLayout(pVButtonLayout);
    pMainVLaout->addWidget(m_pButtonWidget, 0);

    QLabel* pHBottomLabelLine = new QLabel;
    pHBottomLabelLine->setFixedWidth(380);
    pHBottomLabelLine->setFixedHeight(1);
    pHBottomLabelLine->setStyleSheet("QLabel{border-style:none;border:1px solid #242424;}");
    pMainVLaout->addWidget(pHBottomLabelLine, 0);

    setLayout(pMainVLaout);
    return;
}

SingleMsg::~SingleMsg()
{

}

void SingleMsg::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    if(false == m_bTakeInFlag)  //当不在收纳盒时，悬停在消息上才显示收纳和删除按钮
    {
        m_pButtonWidget->setVisible(true);
    }
    setStyleSheet("background-color:rgba(255,255,255,0.08);");

    return;
}

void SingleMsg::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    if(false == m_bTakeInFlag)
    {
        m_pButtonWidget->setVisible(false);
    }

    setStyleSheet("background-color:rgba(26,26,26,0.95);");
    if(false == m_strBody.isEmpty())
    {
        m_pBodyLabel->setWordWrap(false);
        QFontMetrics fontMetrics(m_pBodyLabel->font());
        QString formatSummary = fontMetrics.elidedText(m_strBody, Qt::ElideRight, m_pBodyLabel->width());
        m_pBodyLabel->setText(formatSummary);
    }
    return;
}

//鼠标点击事件
void SingleMsg::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        if(false == m_strBody.isEmpty())
        {
            m_pBodyLabel->setWordWrap(true);
            m_pBodyLabel->setText(m_strBody);
        }
    }
    return;
}

void SingleMsg::onClear()
{
    emit Sig_Send(this);
    return;
}

void SingleMsg::onTakein()
{
    m_bTakeInFlag = true;
    m_pButtonWidget->setVisible(false);
    emit Sig_SendTakein(this);
    return;
}
















