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
#include "buttonwidget.h"
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QSvgRenderer>
#include <QPixmap>
#include <QPainter>
#include "diypropertyanimation.h"
#include <QDebug>
#include <QTimer>

SingleMsg::SingleMsg(AppMsg* pParent, QString strIconPath, QString strAppName, QString strSummary, QDateTime dateTime, QString strBody, bool bTakeInFlag)
{
    m_bMain = true;                 //默认是主窗口
    m_bFold = true;                 //默认折叠状态
    m_strIconPath = strIconPath;
    m_strSummary = strSummary;
    m_strBody = strBody;

    m_dateTime = dateTime;
    m_uNotifyTime = dateTime.toTime_t();
    m_bTakeInFlag = bTakeInFlag;
    m_bTimeFormat = true;

    this->adjustSize();

    connect(this, SIGNAL(Sig_setAppFoldFlag(bool)), pParent, SLOT(setAppFoldFlag(bool)));
    connect(this, SIGNAL(Sig_onDeleSingleMsg(SingleMsg*)), pParent, SLOT(onDeleSingleMsg(SingleMsg*)));
    connect(this, SIGNAL(Sig_onDeleteAppMsg()), pParent, SLOT(onDeleteAppMsg()));
    connect(this, SIGNAL(Sig_onTakeInSingleMsg(SingleMsg*)), pParent, SLOT(onTakeInSingleMsg(SingleMsg*)));
    connect(this, SIGNAL(Sig_onTakeinWholeApp()), pParent, SLOT(onTakeinWholeApp()));
    connect(this, SIGNAL(Sig_onRecoverSingleMsg(SingleMsg*)), pParent, SLOT(onRecoverSingleMsg(SingleMsg*)));
    connect(this, SIGNAL(Sig_onRecoverWholeApp()), pParent, SLOT(onRecoverWholeApp()));
    connect(this, SIGNAL(Sig_onMainEnter()), pParent, SLOT(onMainMsgEnter()));
    connect(this, SIGNAL(Sig_onMainLeave()), pParent, SLOT(onMainMsgLeave()));
    connect(this, SIGNAL(Sig_notifyAppShowBaseMap()), pParent, SLOT(onShowBaseMap()));
    connect(this, SIGNAL(Sig_notifyAppHideBaseMap()), pParent, SLOT(onHideBaseMap()));

    //为了设置SingleMsg的6px圆角的样式,在里面套了一个QWidget
    m_pAppVLaout = new QVBoxLayout();
    m_pAppVLaout->setContentsMargins(0,0,0,0);
    m_pAppVLaout->setSpacing(0);
    m_pSingleWidget = new QWidget(this);
    m_pSingleWidget->setObjectName("SingleNotification");

    m_pAnimationBaseMapWidget = new QWidget(this);
    m_pAnimationBaseMapWidget->setStyleSheet("background:transparent;");

    //单条消息总体垂直布局器
    QVBoxLayout* pMainVLaout = new QVBoxLayout;
    pMainVLaout->setContentsMargins(0, 0, 0, 0);
    pMainVLaout->setSpacing(0);

    //图标和时间行的水平布局部件
    m_pIconWidget = new QWidget;
    m_pIconWidget->setStyleSheet("background:transparent;");

    //图标和时间行的水平布局器
    QHBoxLayout* pIconHLayout = new QHBoxLayout();
    pIconHLayout->setContentsMargins(12,11,26,0);
    pIconHLayout->setSpacing(0);

    //设置通知消息中的Icon，使用QToolButton
    QToolButton* pIconToolButton = new QToolButton();
    pIconToolButton->setStyleSheet("QToolButton{border:none;border-style:none;padding:0px;background:transparent;}");
    pIconToolButton->setIconSize(QSize(24,24));
    pIconToolButton->setIcon(QPixmap(strIconPath));

    //设置应用名标签，采用省略模式
    QLabel* pAppNameLabel = new QLabel();
    pAppNameLabel->setObjectName("AppName");
    pAppNameLabel->setFixedWidth(84);
    QFont font14;
    font14.setPixelSize(14);
    pAppNameLabel->setFont(font14);
    QFontMetrics fontMetrics1(pAppNameLabel->font());

    QString formatAppName = fontMetrics1.elidedText(strAppName, Qt::ElideRight, pAppNameLabel->width());
    pAppNameLabel->setText(formatAppName);


    //设置通知消息中的弹簧，水平任意伸缩使主题和时间分开
    QSpacerItem* pHExpandSpacer = new QSpacerItem(400, 10, QSizePolicy::Expanding, QSizePolicy::Fixed);

    //设置通知消息中的通知时间
    m_pTimeLabel = new QLabel();
    m_pTimeLabel->setObjectName("pushtime");
    m_pTimeLabel->setText("现在");
    m_pTimeLabel->setStyleSheet("background-color:transparent;");

    //单独收纳按钮
    if(false == m_bTakeInFlag)
    {
        QString strIcon = ":/images/box-16-translucent.svg";
        QString strHoverIcon = ":/images/box-16.svg";
        QString strPressIcon = ":/images/box-14-translucent.svg";
        m_pSingleTakeinButton = new ButtonWidget(strIcon, strHoverIcon, strPressIcon);
        connect(m_pSingleTakeinButton, SIGNAL(Sig_clicked()), this, SLOT(onTakeIn()));
    }
    else
    {
        QString strIcon = ":/images/exitbox-16-translucent.svg";
        QString strHoverIcon = ":/images/exitbox-16.svg";
        QString strPressIcon = ":/images/exitbox-14-translucent.svg";
        m_pSingleTakeinButton = new ButtonWidget(strIcon, strHoverIcon, strPressIcon);
        connect(m_pSingleTakeinButton, SIGNAL(Sig_clicked()), this, SLOT(onRecover()));
    }
    m_pSingleTakeinButton->setVisible(false);

    //单独删除按钮
    QString strIcon = ":/images/hover-translucent.svg";
    QString strHoverIcon = ":/images/hover.svg";
    m_pSingleDeleteButton = new ButtonWidget(strIcon, strHoverIcon, strIcon);
    connect(m_pSingleDeleteButton, SIGNAL(Sig_clicked()), this, SLOT(onDele()));
    m_pSingleDeleteButton->setVisible(false);

    pIconHLayout->addWidget(pIconToolButton, 0, Qt::AlignLeft);
    pIconHLayout->addWidget(pAppNameLabel, 0, Qt::AlignLeft|Qt::AlignVCenter);
    pIconHLayout->addSpacerItem(pHExpandSpacer);
    pIconHLayout->addWidget(m_pTimeLabel, 0, Qt::AlignRight);
    pIconHLayout->addWidget(m_pSingleTakeinButton, 0, Qt::AlignRight);
    pIconHLayout->addWidget(m_pSingleDeleteButton, 0, Qt::AlignRight);

    m_pIconWidget->setLayout(pIconHLayout);
    pMainVLaout->addWidget(m_pIconWidget, 0);


    //内容部件,将主题正文以及剩余条数显示装入内容部件
    QWidget* pContextWidget = new QWidget;
    pContextWidget->setStyleSheet("background-color:transparent;");
    //内容部件的垂直布局器
    QVBoxLayout* pVContextLayout = new QVBoxLayout();
    pVContextLayout->setContentsMargins(40,0,26,0);
    pVContextLayout->setSpacing(0);
    //设置通知消息中的主题，采用省略模式
    m_pSummaryLabel = new QLabel();
    m_pSummaryLabel->setFixedWidth(314);
    m_pSummaryLabel->setStyleSheet("color:rgba(255,255,255,0.97);font-weight:400;font-size:16px;background-color:transparent;line-height:26px;padding:0px;");
    QFont font16;
    font16.setPixelSize(16);
    m_pSummaryLabel->setFont(font16);

    QString formatSummary;
    formatSummary.append("<p style='line-height:26px'>").append(m_strSummary).append("</p>");
    QFontMetrics fontMetrics(m_pSummaryLabel->font());
    int nFontSize = fontMetrics.width(formatSummary);
    QString strformatSummary = formatSummary;
    if(nFontSize > (m_pSummaryLabel->width() + 239))
    {
        strformatSummary = fontMetrics.elidedText(formatSummary, Qt::ElideRight, m_pSummaryLabel->width() + 210);
    }

    m_pSummaryLabel->setText(strformatSummary);
    pVContextLayout->addWidget(m_pSummaryLabel, 0, Qt::AlignLeft);

    //设置通知消息中的正文QLabel，行高24px,采用自动换行模式
    if(false == m_strBody.isEmpty())
    {
        QString strLineHeight24Body;
        strLineHeight24Body.append("<p style='line-height:24px'>").append(m_strBody).append("</p>");
        m_pBodyLabel = new QLabel();
        m_pBodyLabel->setFixedWidth(315);
        m_pBodyLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        m_pBodyLabel->adjustSize();
        m_pBodyLabel->setStyleSheet("color:rgba(255,255,255,0.57);font-weight:400;font-size:14px;background-color:transparent;line-height:24px;padding:0px;");

        QFontMetrics fontMetrics(m_pBodyLabel->font());
        int fontSize = fontMetrics.width(strLineHeight24Body);
        QString formatBody = strLineHeight24Body;

        m_pBodyLabel->setWordWrap(false);
        if(fontSize > (m_pBodyLabel->width() + 209))
        {
            formatBody = fontMetrics.elidedText(strLineHeight24Body, Qt::ElideRight, m_pBodyLabel->width() + 180);
        }
        m_pBodyLabel->setText(formatBody);
        pVContextLayout->addWidget(m_pBodyLabel, 0, Qt::AlignLeft);
    }

    //显示该应用未展开部件
    m_pShowLeftWidget = new QWidget;
    QVBoxLayout* pVShowLeftLayout = new QVBoxLayout();
    pVShowLeftLayout->setContentsMargins(0,6,0,14);

    m_pShowLeftItemLabel = new QLabel;
    m_pShowLeftItemLabel->setObjectName("ShowLeftItem");
    m_pShowLeftItemLabel->setVisible(false);
    pVShowLeftLayout->addWidget(m_pShowLeftItemLabel, 0, Qt::AlignLeft);
    m_pShowLeftWidget->setLayout(pVShowLeftLayout);
    pVContextLayout->addWidget(m_pShowLeftWidget, 0, Qt::AlignLeft);

    pContextWidget->setLayout(pVContextLayout);
    pMainVLaout->addWidget(pContextWidget);

    m_pSingleWidget->setLayout(pMainVLaout);
    m_pAppVLaout->addWidget(m_pSingleWidget);
    this->setLayout(m_pAppVLaout);

    setStyleSheet("background-color:rgba(255,255,255,0.12);");
    return;
}

void SingleMsg::updatePushTime()
{
    QDateTime currentDateTime(QDateTime::currentDateTime());

    if(currentDateTime.toTime_t() < (m_uNotifyTime + 60))
    {
        return;
    }

    QString strPushDate;
    if(m_dateTime.date() == currentDateTime.date())
    {
        if(true == m_bTimeFormat)
        {
            strPushDate = m_dateTime.toString("hh:mm");                     //24小时制
        }
        else
        {
            strPushDate = m_dateTime.toString("AP h:mm");                   //12小时制
        }
        m_pTimeLabel->setText(strPushDate);
        return;
    }

    if(1 == (currentDateTime.date().toJulianDay() - m_dateTime.date().toJulianDay()))
    {
        strPushDate = "昨天 ";
        if(true == m_bTimeFormat)
        {
            strPushDate = strPushDate + m_dateTime.toString("hh:mm");       //24小时制
        }
        else
        {
            strPushDate = strPushDate + m_dateTime.toString("AP h:mm");     //12小时制
        }
        m_pTimeLabel->setText(strPushDate);

        return;
    }

    //一周以内
    if((currentDateTime.date().toJulianDay() - m_dateTime.date().toJulianDay()) < 7)
    {
        if(true == m_bTimeFormat)
        {
            strPushDate = m_dateTime.toString("ddd hh:mm");                 //24小时制
        }
        else
        {
            strPushDate =  m_dateTime.toString("ddd AP h:mm");              //12小时制
        }
        m_pTimeLabel->setText(strPushDate);
    }
    else
    {
        strPushDate = m_dateTime.toString("yyyy/MM/dd");                    //一周以外
        m_pTimeLabel->setText(strPushDate);
    }

    return;

}

void SingleMsg::setBodyLabelWordWrap(bool bFlag)
{
    if(true == m_strBody.isEmpty())
    {
        return;
    }

    m_pBodyLabel->setWordWrap(bFlag);
    QFont font14;
    font14.setPixelSize(14);
    m_pBodyLabel->setFont(font14);
    QFontMetrics fontMetrics(m_pBodyLabel->font());
    QString strLineHeight24Body;
    strLineHeight24Body.append("<p style='line-height:24px'>").append(m_strBody).append("</p>");
    int fontSize = fontMetrics.width(strLineHeight24Body);
    QString formatBody = strLineHeight24Body;

    if(true == bFlag)
    {
        //如果展开,就超过四行末尾显示省略号
        //if(fontSize > (m_pBodyLabel->width() * 4 + 181))
        {
            formatBody = fontMetrics.elidedText(strLineHeight24Body, Qt::ElideRight, m_pBodyLabel->width() * 4 + 152);
        }
    }
    else
    {
        //如果不展开,就超过一行末尾显示省略号
        if(fontSize > (m_pBodyLabel->width() + 209))
        {
            formatBody = fontMetrics.elidedText(strLineHeight24Body, Qt::ElideRight, m_pBodyLabel->width() + 180);
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
        m_pAppVLaout->setContentsMargins(0,0,0,0); //假如折叠，剩余条目显示将可见，则SingleMsg的内容均无空隙
        m_pShowLeftItemLabel->setVisible(true);
    }
    else
    {
        m_pAppVLaout->setContentsMargins(0,0,0,6); //假如展开，剩余条目显示不可见，则SingleMsg的内容空白恢复正常，即底部多出6个px的空隙
        m_pShowLeftItemLabel->setVisible(false);
    }
}

void SingleMsg::setShowLeftItemFlag(bool bFlag)
{
    m_pShowLeftItemLabel->setVisible(bFlag);
}

void SingleMsg::setSingleMsgContentsMargins(int left, int top, int right, int bottom)
{
    m_pAppVLaout->setContentsMargins(left, top, right, bottom);
}

void SingleMsg::enterEvent(QEvent *event)
{
    Q_UNUSED(event);

    if((true == m_bMain) && (false == m_bFold) && (m_nShowLeftCount > 0))
    {
        setStyleSheet("background-color:rgba(255,255,255,0.28);");
    }
    else
    {
        setStyleSheet("background-color:rgba(255,255,255,0.2);");
    }

    m_pSingleTakeinButton->setVisible(true);
    m_pSingleDeleteButton->setVisible(true);
    m_pTimeLabel->setVisible(false);

    if((true == m_bMain) && (true == m_bFold) && (m_nShowLeftCount > 0))
    {
        emit Sig_onMainEnter();
    }

    return;
}

void SingleMsg::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);

    if((true == m_bMain) && (false == m_bFold) && (m_nShowLeftCount > 0))
    {
        setStyleSheet("background-color:rgba(255,255,255,0.2);");
    }
    else
    {
        setStyleSheet("background-color:rgba(255,255,255,0.12);");
    }
    m_pSingleTakeinButton->setVisible(false);
    m_pSingleDeleteButton->setVisible(false);
    m_pTimeLabel->setVisible(true);

    if((true == m_bMain) && (true == m_bFold) && (m_nShowLeftCount > 0))
    {
        emit Sig_onMainLeave();
    }

    return;
}

//鼠标点击事件
void SingleMsg::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        if(true == m_bFold)
        {
            m_bFold = false;                                //置为false,表示展开
            setBodyLabelWordWrap(true);
        }
        else
        {
            m_bFold = true;                                 //置为true,表示折叠
            setBodyLabelWordWrap(false);
        }

        if((true == m_bMain) && (false == m_bFold) && (m_nShowLeftCount > 0))
        {
            setStyleSheet("background-color:rgba(255,255,255,0.28);");
        }
        else
        {
            setStyleSheet("background-color:rgba(255,255,255,0.2);");
        }

        //当消息为主窗口时,发送折叠信息给App
        if(true == m_bMain)
        {
            //当剩余条数大于0, 且是折叠状态则显示剩余标签
            if((true == m_bFold) && (m_nShowLeftCount > 0))
            {
                emit Sig_onMainEnter();
            }
            else
            {
                emit Sig_onMainLeave();                     //点击后也让app的分层底图恢复原色
                m_pAppVLaout->setContentsMargins(0,0,0,6);  //假如展开，剩余条目显示不可见，则SingleMsg的内容空白恢复正常，即底部多出6个px的空隙
                m_pShowLeftItemLabel->setVisible(false);
            }
            emit Sig_setAppFoldFlag(m_bFold);
        }
    }
    return;
}

void SingleMsg::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
}

void SingleMsg::mainMsgSetFold()
{
    //当消息为主窗口时,由主消息设置折叠
    if(true == m_bMain)
    {
        //置为true,表示折叠
        m_bFold = true;
        setBodyLabelWordWrap(false);

        //当剩余条数大于0, 且是折叠状态则显示剩余标签
        if(m_nShowLeftCount > 0)
        {
            m_pAppVLaout->setContentsMargins(0,0,0,0);      //假如折叠，剩余条目显示将可见，则SingleMsg的内容均无空隙
            m_pShowLeftItemLabel->setVisible(true);
        }
        emit Sig_setAppFoldFlag(true);
    }
}

//开启多消息展开时动画
void SingleMsg::startAnimationUnfold()
{
    int width = this->width();
    int height = this->height();
    qDebug()<<"SingleMsg::startAnimationUnfold"<<this <<width <<height;

    m_pAppVLaout->removeWidget(m_pSingleWidget);
    m_pAnimationBaseMapWidget->setFixedSize(width, 0);
    m_pAnimationBaseMapWidget->setVisible(true);
    m_pAppVLaout->addWidget(m_pAnimationBaseMapWidget, 0, Qt::AlignHCenter);
    this->setVisible(true);

    if(true == m_strBody.isEmpty())
    {
        height = 90;
    }
    else
    {
        height = 114;
    }

    //设置show动画
    DiyPropertyAnimation* pAnimation = new DiyPropertyAnimation(m_pSingleWidget, "geometry");
    pAnimation->setDuration(300);
    connect(pAnimation, SIGNAL(Sig_currentRect(int, int, int, int)), this, SLOT(updateUnfoldMove(int, int, int, int)));
    connect(pAnimation, SIGNAL(finished()), this, SLOT(onUnfoldFinish()));

    pAnimation->setStartValue(QRect(0, 0, width, height));
    pAnimation->setEndValue(QRect(0, height, width, height));
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

//开启多消息折叠时动画
void SingleMsg::startAnimationFold()
{
    int width = this->width();
    int height = this->height();
    qDebug()<<"SingleMsg::startAnimationFold"<<this <<width <<height;

    m_pAnimationBaseMapWidget->setFixedSize(380, (height - 6));
    m_pAnimationBaseMapWidget->setVisible(true);
    m_pAppVLaout->removeWidget(m_pSingleWidget);
    m_pAppVLaout->addWidget(m_pAnimationBaseMapWidget, 0, Qt::AlignHCenter);

    //设置show动画
    DiyPropertyAnimation* pAnimation = new DiyPropertyAnimation(m_pSingleWidget, "geometry");
    pAnimation->setDuration(300);
    connect(pAnimation, SIGNAL(Sig_currentRect(int, int, int, int)), this, SLOT(updateFoldMove(int, int, int, int)));
    connect(pAnimation, SIGNAL(finished()), this, SLOT(onFoldFinish()));

    pAnimation->setStartValue(QRect(0, 0, width, height));
    pAnimation->setEndValue(QRect(0, height, width, height));
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

//开启删除左移动画
void SingleMsg::startAnimationDeleLeftMove()
{
    int nWidth = this->width();
    int nHeight = this->height();
    QDateTime currentDateTime(QDateTime::currentDateTime());
    QString strCurrentTime = currentDateTime.toString("hh:mm:ss.zzz");
    qDebug()<<strCurrentTime <<"SingleMsg::setAnimationDeleStatus"<<this <<nWidth <<nHeight;

    nHeight = nHeight - 6;                  //减去底部6px的空白区域，得出动画框体偏移高度

    m_pAppVLaout->removeWidget(m_pSingleWidget);
    m_pAnimationBaseMapWidget->setFixedSize(nWidth, nHeight);
    m_pAnimationBaseMapWidget->setVisible(true);
    m_pAppVLaout->addWidget(m_pAnimationBaseMapWidget, 0, Qt::AlignHCenter);

    //设置show动画
    DiyPropertyAnimation* pAnimation = new DiyPropertyAnimation(m_pSingleWidget, "geometry");
    pAnimation->setDuration(150);
    connect(pAnimation, SIGNAL(Sig_currentRect(int, int, int, int)), this, SLOT(updateDeleLeftMove(int, int, int, int)));
    connect(pAnimation, SIGNAL(finished()), this, SLOT(onDeleLeftMoveFinish()));

    pAnimation->setStartValue(QRect(0, 0, nWidth, nHeight));
    pAnimation->setEndValue(QRect(0 - nWidth, 0, nWidth, nHeight));
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);

}

//开启删除上移动画
void SingleMsg::startAnimationDeleUpperMove()
{
    int width = this->width();
    int height = this->height();
    QDateTime currentDateTime(QDateTime::currentDateTime());
    QString strCurrentTime = currentDateTime.toString("hh:mm:ss.zzz");
    qDebug()<<strCurrentTime <<"SingleMsg::startAnimationDeleUpperMove"<<this <<width <<height;

    //设置show动画
    DiyPropertyAnimation* pAnimation = new DiyPropertyAnimation(m_pAnimationBaseMapWidget, "geometry");
    pAnimation->setDuration(150);
    connect(pAnimation, SIGNAL(Sig_currentRect(int, int, int, int)), this, SLOT(updateDeleUpperMove(int, int, int, int)));
    connect(pAnimation, SIGNAL(finished()), this, SLOT(onDeleUpperMoveFinish()));

    pAnimation->setStartValue(QRect(0, 0, width, height));
    pAnimation->setEndValue(QRect(0, 0 - height, width, height));
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

//通知中心或者收纳盒中的删除
void SingleMsg::onDele()
{
    if((true == m_bMain) && (true == m_bFold) && (m_nShowLeftCount > 0))
    {
        m_pAppVLaout->setContentsMargins(0,0,0,6);
        emit Sig_notifyAppHideBaseMap();                    //通知隐藏应用的底图部件，但保留显示底部6px的空白
    }

    QTimer* pSetDeleDelayTimer = new QTimer(this);
    pSetDeleDelayTimer->setSingleShot(true);                //设置一个单次定时器,只为延迟2毫秒执行删除
    connect(pSetDeleDelayTimer, SIGNAL(timeout()), this, SLOT(startAnimationDeleLeftMove()));
    pSetDeleDelayTimer->start(2);

    return;
}

//通知中心消息收纳至收纳盒
void SingleMsg::onTakeIn()
{
    if((true == m_bMain) && (true == m_bFold) && (m_nShowLeftCount > 0))
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
    if((true == m_bMain) && (true == m_bFold) && (m_nShowLeftCount > 0))
    {
        emit Sig_onRecoverWholeApp();
    }
    else
    {
        emit Sig_onRecoverSingleMsg(this);
    }

    return;
}

//更新展开的移动数据
void SingleMsg::updateUnfoldMove(int x1, int y1, int x2, int y2)
{
    Q_UNUSED(x1);

    //首先将填充控件的高度不断增加直至6
    if(y1 <= 6)
    {
        m_pAppVLaout->setContentsMargins(0, 0, 0, y1);
    }
    else
    {
        m_pAppVLaout->setContentsMargins(0, 0, 0, 6);               //当填充控件增加直至6以后
        m_pSingleWidget->setGeometry(0, (y1 - y2), x2, (y2 - 6));   //(y2 - 6)即为m_pSingleWidget的本来高度
        m_pAnimationBaseMapWidget->setFixedSize(x2, (y1 - 6));
    }

    return;
}

//更新折叠的移动数据
void SingleMsg::updateFoldMove(int x1, int y1, int x2, int y2)
{
    Q_UNUSED(x1);
    //m_pSingleWidget的本来高度
    int nHeight = y2 - 6;

    //首先将m_pSingleWidget慢慢消失
    if(y1 <= nHeight)
    {
        m_pSingleWidget->setGeometry(0, (0 - y1), x2, nHeight);
        m_pAnimationBaseMapWidget->setFixedSize(x2, (nHeight - y1));
    }
    else
    {
        m_pSingleWidget->setGeometry(0, (0 - nHeight), x2, nHeight);    //当m_pSingleWidget消失后，开始将底部6个px的空白消失
        m_pAnimationBaseMapWidget->setFixedSize(x2, 0);
        m_pAppVLaout->setContentsMargins(0, 0, 0, (6 - (y1 - nHeight)));
    }

    return;
}

//处理展开完成时的函数
void SingleMsg::onUnfoldFinish()
{
    m_pAppVLaout->removeWidget(m_pAnimationBaseMapWidget);
    m_pAnimationBaseMapWidget->setVisible(false);
    m_pAppVLaout->addWidget(m_pSingleWidget);
}

//处理折叠完成时的函数
void SingleMsg::onFoldFinish()
{
    this->setVisible(false);
    m_pAppVLaout->removeWidget(m_pAnimationBaseMapWidget);
    m_pAnimationBaseMapWidget->setVisible(false);
    m_pAppVLaout->addWidget(m_pSingleWidget);

    setFoldFlag(true);
    setBodyLabelWordWrap(false);

    emit Sig_notifyAppShowBaseMap();
}

//更新删除左移时的移动数据
void SingleMsg::updateDeleLeftMove(int x1, int y1, int x2, int y2)
{
    Q_UNUSED(y1);
    m_pSingleWidget->setGeometry(x1, 0, x2, y2);

}

//处理删除左移完成时的函数
void SingleMsg::onDeleLeftMoveFinish()
{
    startAnimationDeleUpperMove();
}

//更新删除上移时的移动数据
void SingleMsg::updateDeleUpperMove(int x1, int y1, int x2, int y2)
{
    Q_UNUSED(x1);

    //y2-6表示填充控件的高度，y1为负数，首先将填充控件的高度不断减少直至0
    if((y2 - 6 + y1) >= 0)
    {
        m_pAnimationBaseMapWidget->setFixedSize(x2, (y2 - 6 + y1));
    }
    else
    {
        m_pAnimationBaseMapWidget->setVisible(false);           //当填充控件减至0以后，就需要减少底部6个px的空白
        m_pAppVLaout->setContentsMargins(0,0,0,(y2 + y1));
    }

}

//处理删除上移完成时的函数
void SingleMsg::onDeleUpperMoveFinish()
{
    if((true == m_bMain) && (true == m_bFold) && (m_nShowLeftCount > 0))
    {
        emit Sig_onDeleteAppMsg();
    }
    else
    {
        emit Sig_onDeleSingleMsg(this);
    }

}



