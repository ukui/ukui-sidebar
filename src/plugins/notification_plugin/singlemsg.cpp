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
#include "appmsg.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QSvgRenderer>
#include <QPixmap>
#include <QPainter>


SingleMsg::SingleMsg(AppMsg* pParent, QString strIconPath, QString strAppName, QString strSummary, QDateTime dateTime, QString strBody, bool bTakeInFlag)
{
    m_bMain = true;     //默认是主窗口
    m_bFold = true;     //默认折叠状态
    m_strIconPath = strIconPath;
    m_strSummary = strSummary;
    m_strBody = strBody;
    m_dateTime = dateTime;
    m_uNotifyTime = dateTime.toTime_t();
    m_bTakeInFlag = bTakeInFlag;

    connect(this, SIGNAL(Sig_setAppFoldFlag(bool)), pParent, SLOT(setAppFoldFlag(bool)));
    connect(this, SIGNAL(Sig_onDeleSingleMsg(SingleMsg*)), pParent, SLOT(onDeleSingleMsg(SingleMsg*)));
    connect(this, SIGNAL(Sig_onDeleteAppMsg()), pParent, SLOT(onDeleteAppMsg()));
    connect(this, SIGNAL(Sig_onTakeInSingleMsg(SingleMsg*)), pParent, SLOT(onTakeInSingleMsg(SingleMsg*)));
    connect(this, SIGNAL(Sig_onTakeinWholeApp()), pParent, SLOT(onTakeinWholeApp()));
    connect(this, SIGNAL(Sig_onRecoverSingleMsg(SingleMsg*)), pParent, SLOT(onRecoverSingleMsg(SingleMsg*)));
    connect(this, SIGNAL(Sig_onRecoverWholeApp()), pParent, SLOT(onRecoverWholeApp()));



    //为了设置AppMsg的样式,在里面套了一个QWidget
    QVBoxLayout* pAppVLaout = new QVBoxLayout();
    pAppVLaout->setContentsMargins(0,0,0,6);
    pAppVLaout->setSpacing(0);
    QWidget* pAppWidget = new QWidget;
    pAppWidget->setObjectName("AppMsg");

    //单条消息总体垂直布局器
    QVBoxLayout* pMainVLaout = new QVBoxLayout;
    pMainVLaout->setContentsMargins(0, 0, 0, 0);
    pMainVLaout->setSpacing(0);


    //图标和时间行的水平布局部件
    QWidget* pIconWidget = new QWidget;

    //图标和时间行的水平布局器
    QHBoxLayout* pIconHLayout = new QHBoxLayout();
    pIconHLayout->setContentsMargins(12,11,26,0);
    pIconHLayout->setSpacing(0);

    //设置通知消息中的Icon，使用QToolButton
    QToolButton* pIconToolButton = new QToolButton();
    pIconToolButton->setStyleSheet("QToolButton{border:none;border-style:none;padding:0px;background:transparent;}");
    pIconToolButton->setIconSize(QSize(24,24));
    pIconToolButton->setIcon(QPixmap(strIconPath));

    //一个水平6分辨率的弹簧
    QSpacerItem* pH6Spacer = new QSpacerItem(3, 6, QSizePolicy::Fixed, QSizePolicy::Fixed);

    //设置应用名标签，采用省略模式
    QLabel* pAppNameLabel = new QLabel();
    pAppNameLabel->setObjectName("AppName");
    QFontMetrics fontMetrics1(pAppNameLabel->font());
    QString formatAppName = fontMetrics1.elidedText(strAppName, Qt::ElideRight, pAppNameLabel->width());
    pAppNameLabel->setText(formatAppName);
    pAppNameLabel->setStyleSheet("background-color:transparent;");

    //设置通知消息中的弹簧，水平任意伸缩使主题和时间分开
    QSpacerItem* pHExpandSpacer = new QSpacerItem(400, 10, QSizePolicy::Expanding, QSizePolicy::Fixed);

    //设置通知消息中的通知时间
    m_pTimeLabel = new QLabel();
    m_pTimeLabel->setObjectName("pushtime");
    m_pTimeLabel->setText("现在");
    m_pTimeLabel->setStyleSheet("background-color:transparent;");

    //单独收纳按钮
    m_pSingleTakeinButton = new QToolButton();
    m_pSingleTakeinButton->setObjectName("SingleMsgToolButton");
    m_pSingleTakeinButton->setVisible(false);

    QSvgRenderer* m_pTakeinSvgRender = new QSvgRenderer(pIconWidget);

    if(false == m_bTakeInFlag)
    {
        m_pTakeinSvgRender->load(QString(":/images/box.svg"));          //当该条消息不属于收纳消息时，QToolButton添加svg收纳盒图片
        connect(m_pSingleTakeinButton, SIGNAL(clicked()), this, SLOT(onTakeIn()));
    }
    else
    {
        m_pTakeinSvgRender->load(QString(":/images/exitbox.svg"));      //当该条消息属于收纳消息时，QToolButton添加svg出收纳盒图片
        connect(m_pSingleTakeinButton, SIGNAL(clicked()), this, SLOT(onRecover()));
    }
    QPixmap* m_pTakeinPixmap = new QPixmap(13, 13);
    m_pTakeinPixmap->fill(Qt::transparent);
    QPainter takeinPainter(m_pTakeinPixmap);
    m_pTakeinSvgRender->render(&takeinPainter);
    m_pSingleTakeinButton->setIcon(QIcon(*m_pTakeinPixmap));

    //单独删除按钮
    m_pSingleDeleteButton = new QToolButton();
    m_pSingleDeleteButton->setObjectName("SingleMsgToolButton");

    //QToolButton添加svg图片
    QSvgRenderer* m_pDeleteSvgRender = new QSvgRenderer(pIconWidget);
    m_pDeleteSvgRender->load(QString(":/images/hover.svg"));
    QPixmap* m_pDeletePixmap = new QPixmap(12, 12);
    m_pDeletePixmap->fill(Qt::transparent);
    QPainter painter(m_pDeletePixmap);
    m_pDeleteSvgRender->render(&painter);
    m_pSingleDeleteButton->setIcon(QIcon(*m_pDeletePixmap));

    connect(m_pSingleDeleteButton, SIGNAL(clicked()), this, SLOT(onDele()));
    m_pSingleDeleteButton->setVisible(false);

    pIconHLayout->addWidget(pIconToolButton, 0, Qt::AlignLeft);
    pIconHLayout->addSpacerItem(pH6Spacer);
    pIconHLayout->addWidget(pAppNameLabel, 0, Qt::AlignLeft|Qt::AlignVCenter);
    pIconHLayout->addSpacerItem(pHExpandSpacer);
    pIconHLayout->addWidget(m_pTimeLabel, 0, Qt::AlignRight);
    pIconHLayout->addWidget(m_pSingleTakeinButton, 0, Qt::AlignRight);
    pIconHLayout->addWidget(m_pSingleDeleteButton, 0, Qt::AlignRight);

    pIconWidget->setLayout(pIconHLayout);
    pMainVLaout->addWidget(pIconWidget, 0);



    //内容部件,将主题正文以及剩余条数显示装入内容部件
    QWidget* pContextWidget = new QWidget;
    pContextWidget->setStyleSheet("background-color:transparent;");
    //内容部件的垂直布局器
    QVBoxLayout* pVContextLayout = new QVBoxLayout();
    pVContextLayout->setContentsMargins(40,0,26,0);
    pVContextLayout->setSpacing(0);
    //设置通知消息中的主题，采用省略模式
    QLabel* pSummaryLabel = new QLabel();
    pSummaryLabel->setObjectName("Summary");
    pSummaryLabel->setMaximumWidth(250);
    pSummaryLabel->setStyleSheet("background-color:transparent;");

    QString formatSummary;
    formatSummary.append("<p style='line-height:26px'>").append(strSummary).append("</p>");
    QFontMetrics fontMetrics(pSummaryLabel->font());
    int nFontSize = fontMetrics.width(formatSummary);
    QString strformatSummary = formatSummary;
    if(nFontSize > (pSummaryLabel->width() + 70))
    {
        strformatSummary = fontMetrics.elidedText(formatSummary, Qt::ElideRight, pSummaryLabel->width() + 50);
    }

    pSummaryLabel->setText(strformatSummary);
    pVContextLayout->addWidget(pSummaryLabel, 0, Qt::AlignLeft);

    //设置通知消息中的正文QLabel，行高24px,采用自动换行模式
    if(false == strBody.isEmpty())   //当正文消息不为空
    {
        m_pBodyLabel = new QLabel();
        m_pBodyLabel->setObjectName("body");
        m_pBodyLabel->setFixedWidth(315);
//        m_pBodyLabel->setStyleSheet("padding:0px;height:24px;font-size:14px;background-color:transparent;");
        m_pBodyLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Maximum);
        m_pBodyLabel->setWordWrap(false);
//        m_pBodyLabel->setText(m_strBody);

        QFontMetrics fontMetrics(m_pBodyLabel->font());
        int fontSize = fontMetrics.width(m_strBody);
        QString formatBody = m_strBody;
        if(fontSize > (m_pBodyLabel->width() - 45))
        {
            formatBody = fontMetrics.elidedText(m_strBody, Qt::ElideRight, m_pBodyLabel->width() - 40);
        }
        m_pBodyLabel->setText(formatBody);

        pVContextLayout->addWidget(m_pBodyLabel, 0, Qt::AlignLeft);
    }

    //显示该应用未展开部件
    m_pShowLeftWidget = new QWidget;
    m_pShowLeftWidget->setVisible(false);
    QVBoxLayout* pVShowLeftLayout = new QVBoxLayout();
    pVShowLeftLayout->setContentsMargins(0,6,0,14);

    m_pShowLeftItemLabel = new QLabel;
    m_pShowLeftItemLabel->setObjectName("ShowLeftItem");
    pVShowLeftLayout->addWidget(m_pShowLeftItemLabel, 0, Qt::AlignLeft);
    m_pShowLeftWidget->setLayout(pVShowLeftLayout);
    pVContextLayout->addWidget(m_pShowLeftWidget, 0, Qt::AlignLeft);

    pContextWidget->setLayout(pVContextLayout);
    pMainVLaout->addWidget(pContextWidget);

    pAppWidget->setLayout(pMainVLaout);
    pAppVLaout->addWidget(pAppWidget);
    this->setLayout(pAppVLaout);

    return;
}

void SingleMsg::updatePushTime()
{
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

void SingleMsg::setBodyLabelWordWrap(bool bFlag)
{
    if(true == m_strBody.isEmpty())
    {
        return;
    }

    m_pBodyLabel->setWordWrap(bFlag);

    QFontMetrics fontMetrics(m_pBodyLabel->font());
    int fontSize = fontMetrics.width(m_strBody);
    QString formatBody = m_strBody;

    if(true == bFlag)
    {
        //如果展开,就超过四行末尾显示省略号
        if(fontSize > (m_pBodyLabel->width() * 4 - 30))
        {
            formatBody = fontMetrics.elidedText(m_strBody, Qt::ElideRight, m_pBodyLabel->width() * 4 - 20);
        }
    }
    else
    {
        //如果不展开,就超过一行末尾显示省略号
        if(fontSize > (m_pBodyLabel->width() - 45))
        {
            formatBody = fontMetrics.elidedText(m_strBody, Qt::ElideRight, m_pBodyLabel->width());
        }
    }
    m_pBodyLabel->setText(formatBody);

    return;
}

//将应用的总的剩余条数设置剩余标签显示内容,根据具体情况显示,该函数只有顶部消息才执行
void SingleMsg::setLeftItem(int nShowLeftCount)
{
    m_nShowLeftCount = nShowLeftCount;
    QString strShowLeft = "还有" + QString::number(nShowLeftCount) + "则通知";
    m_pShowLeftItemLabel->setText(strShowLeft);

    //当剩余条数大于0, 且是折叠状态则显示剩余标签
    if((true == m_bFold) && (m_nShowLeftCount > 0))
    {
        m_pShowLeftWidget->setVisible(true);
    }
    else
    {
        m_pShowLeftWidget->setVisible(false);
    }
}

void SingleMsg::setShowLeftItemFlag(bool bFlag)
{
    m_pShowLeftWidget->setVisible(bFlag);
}

void SingleMsg::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    setStyleSheet("background-color:rgba(255,255,255,0.2);");
    m_pSingleTakeinButton->setVisible(true);
    m_pSingleDeleteButton->setVisible(true);
    m_pTimeLabel->setVisible(false);

    return;
}

void SingleMsg::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    setStyleSheet("background-color:rgba(255,255,255,0.12);");
    m_pSingleTakeinButton->setVisible(false);
    m_pSingleDeleteButton->setVisible(false);
    m_pTimeLabel->setVisible(true);

    return;
}

//鼠标点击事件
void SingleMsg::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        if(true == m_bFold)
        {
            m_bFold = false;  //置为false,表示展开
            setBodyLabelWordWrap(true);
        }
        else
        {
            m_bFold = true;  //置为true,表示折叠
            setBodyLabelWordWrap(false);
        }
        //当消息为主窗口时,发送折叠信息给App
        if(true == m_bMain)
        {
            emit Sig_setAppFoldFlag(m_bFold);

            //当剩余条数大于0, 且是折叠状态则显示剩余标签
            if((true == m_bFold) && (m_nShowLeftCount > 0))
            {
                m_pShowLeftWidget->setVisible(true);
            }
            else
            {
                m_pShowLeftWidget->setVisible(false);
            }
        }
    }
    return;
}

//通知中心或者收纳盒中的删除
void SingleMsg::onDele()
{
    if(true == m_bMain && true == m_bFold)
    {
        emit Sig_onDeleteAppMsg();
    }
    else
    {
        emit Sig_onDeleSingleMsg(this);
    }
    return;
}

//通知中心消息收纳至收纳盒
void SingleMsg::onTakeIn()
{
    if(true == m_bMain && true == m_bFold)
    {
        emit Sig_onTakeinWholeApp();
    }
    else
    {
        emit Sig_onTakeInSingleMsg(this);
    }

    return;
}

//收纳盒消息恢复至通知中心
void SingleMsg::onRecover()
{
    if(true == m_bMain && true == m_bFold)
    {
        emit Sig_onRecoverWholeApp();
    }
    else
    {
        emit Sig_onRecoverSingleMsg(this);
    }

    return;
}





