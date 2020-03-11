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

    //为了设置SingleMsg的6px圆角的样式,在里面套了一个QWidget
    m_pAppVLaout = new QVBoxLayout();
    m_pAppVLaout->setContentsMargins(0,0,0,6);
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

    //图标和时间行的水平布局器
    QHBoxLayout* pIconHLayout = new QHBoxLayout();
    pIconHLayout->setContentsMargins(12,11,26,0);
    pIconHLayout->setSpacing(0);

    //设置通知消息中的Icon，使用QToolButton
    QToolButton* pIconToolButton = new QToolButton();
    pIconToolButton->setStyleSheet("QToolButton{border:none;border-style:none;padding:0px;background:transparent;}");
    pIconToolButton->setIconSize(QSize(24,24));
    pIconToolButton->setIcon(QPixmap(strIconPath));

    //一个水平3分辨率的弹簧
//    QSpacerItem* pH6Spacer = new QSpacerItem(3, 6, QSizePolicy::Fixed, QSizePolicy::Fixed);

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
//    pIconHLayout->addSpacerItem(pH6Spacer);
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
    if(false == m_strBody.isEmpty())   //当正文消息不为空
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
        if(true == m_bTimeFormat)   //24小时制
        {
            strPushDate = m_dateTime.toString("hh:mm");
        }
        else                        //12小时制
        {
            strPushDate = m_dateTime.toString("AP h:mm");
        }
        m_pTimeLabel->setText(strPushDate);
        return;
    }

    if(1 == (currentDateTime.date().toJulianDay() - m_dateTime.date().toJulianDay()))
    {
        strPushDate = "昨天 ";
        if(true == m_bTimeFormat)   //24小时制
        {
            strPushDate = strPushDate + m_dateTime.toString("hh:mm");
        }
        else                        //12小时制
        {
            strPushDate = strPushDate + m_dateTime.toString("AP h:mm");
        }
        m_pTimeLabel->setText(strPushDate);

        return;
    }

    //一周以内
    if((currentDateTime.date().toJulianDay() - m_dateTime.date().toJulianDay()) < 7)
    {
        if(true == m_bTimeFormat)   //24小时制
        {
            strPushDate = m_dateTime.toString("ddd hh:mm");
        }
        else                        //12小时制
        {
            strPushDate =  m_dateTime.toString("ddd AP h:mm");
        }
        m_pTimeLabel->setText(strPushDate);
    }
    else  //一周以外
    {
        strPushDate = m_dateTime.toString("yyyy/MM/dd");
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
//        if(fontSize > (m_pBodyLabel->width() * 4 + 181))
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
    setStyleSheet("background-color:rgba(255,255,255,0.2);");
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
    setStyleSheet("background-color:rgba(255,255,255,0.12);");
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
            //当剩余条数大于0, 且是折叠状态则显示剩余标签
            if((true == m_bFold) && (m_nShowLeftCount > 0))
            {
                emit Sig_onMainEnter();
            }
            else
            {
                emit Sig_onMainLeave();     //点击后也让app的分层底图恢复原色
                m_pAppVLaout->setContentsMargins(0,0,0,6); //假如展开，剩余条目显示不可见，则SingleMsg的内容空白恢复正常，即底部多出6个px的空隙
                m_pShowLeftItemLabel->setVisible(false);
            }
            emit Sig_setAppFoldFlag(m_bFold);
        }
    }
    return;
}

void SingleMsg::resizeEvent(QResizeEvent *event)
{
    qDebug()<<"SingleMsg::resizeEvent"<<m_bMain <<this->width() <<this->height();

}

void SingleMsg::mainMsgSetFold()
{
    //当消息为主窗口时,由主消息设置折叠
    if(true == m_bMain)
    {
        m_bFold = true;  //置为true,表示折叠
        setBodyLabelWordWrap(false);
        //当剩余条数大于0, 且是折叠状态则显示剩余标签
        if(m_nShowLeftCount > 0)
        {
            m_pAppVLaout->setContentsMargins(0,0,0,0); //假如折叠，剩余条目显示将可见，则SingleMsg的内容均无空隙
            m_pShowLeftItemLabel->setVisible(true);
        }
        emit Sig_setAppFoldFlag(true);
    }
}

//多消息展开
void SingleMsg::setAnimationUnfoldStatus(bool bFlag)
{
    int height = m_pSingleWidget->height();
    m_bAnimationFlag = bFlag;
    m_pAppVLaout->removeWidget(m_pSingleWidget);
    m_pAnimationBaseMapWidget->setFixedSize(10, 0);
    m_pAppVLaout->addWidget(m_pAnimationBaseMapWidget, 0, Qt::AlignHCenter);
    this->setVisible(true);
    return;
}

//多消息折叠
void SingleMsg::setAnimationFoldStatus(bool bFlag)
{
    m_bAnimationFlag = bFlag;
    m_pSingleWidget->repaint();
    int nHeight = m_pSingleWidget->height();
    if(true == m_strBody.isEmpty())
    {
        nHeight = 90;
    }
    else
    {
        nHeight = 114;
    }

    m_pAnimationBaseMapWidget->setFixedSize(10, nHeight);
    m_pAppVLaout->removeWidget(m_pSingleWidget);
    m_pAppVLaout->addWidget(m_pAnimationBaseMapWidget, 0, Qt::AlignHCenter);
//    this->setVisible(true);
    return;
}

void SingleMsg::startAnimation()
{
    int width = this->width();
    int height = this->height();
    if(true == m_strBody.isEmpty())
    {
        height = 90 - 6;            //在删除里面总部件之前已保存消息总体折叠时的高度，现已减去底部6px的空白区域，得出动画框体偏移距离
    }
    else
    {
        height = 114 - 6;
    }

    //设置show动画
    DiyPropertyAnimation* pAnimation = new DiyPropertyAnimation(m_pSingleWidget, "geometry");
    pAnimation->setDuration(1000);
    connect(pAnimation, SIGNAL(Sig_currentRect(int, int, int, int)), this, SLOT(updateCurrentRect(int, int, int, int)));
    connect(pAnimation, SIGNAL(finished()), this, SLOT(onAnimationFinish()));

    pAnimation->setStartValue(QRect(0, 0, width, height));
    pAnimation->setEndValue(QRect(0, height, width, height));
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

//开启删除动画之前，设置的一些准备状态
void SingleMsg::setAnimationDeleStatus(bool bFlag)
{
    int nHeight;
    if(true == m_strBody.isEmpty())
    {
        nHeight = 90 - 6;
    }
    else
    {
        nHeight = 114 - 6;
    }

    m_pAppVLaout->removeWidget(m_pSingleWidget);
    m_pAnimationBaseMapWidget->setFixedSize(this->width(), nHeight);
    m_pAppVLaout->addWidget(m_pAnimationBaseMapWidget, 0, Qt::AlignHCenter);
}

//开启删除左移动画
void SingleMsg::startAnimationDeleLeftMove()
{
    int width = this->width();
    int height;
    if(true == m_strBody.isEmpty())
    {
        height = 90;
    }
    else
    {
        height = 114;
    }

    height = height - 6;   //在删除里面总部件之前已保存消息总体折叠时的高度，现已减去底部6px的空白区域，得出动画框体偏移距离

    //设置show动画
    DiyPropertyAnimation* pAnimation = new DiyPropertyAnimation(m_pSingleWidget, "geometry");
    pAnimation->setDuration(3000);
    connect(pAnimation, SIGNAL(Sig_currentRect(int, int, int, int)), this, SLOT(updateDeleLeftMove(int, int, int, int)));
    connect(pAnimation, SIGNAL(finished()), this, SLOT(onAnimationDeleLeftMoveFinish()));

    pAnimation->setStartValue(QRect(0, 0, width, height));
    pAnimation->setEndValue(QRect(0 - width, 0, width, height));
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);

}

//开启删除上移动画
void SingleMsg::startAnimationDeleUpperMove()
{
    int width = m_pAnimationBaseMapWidget->width() + 6;
    int height = m_pAnimationBaseMapWidget->height() + 6;

    //设置show动画
    DiyPropertyAnimation* pAnimation = new DiyPropertyAnimation(m_pAnimationBaseMapWidget, "geometry");
    pAnimation->setDuration(2000);
    connect(pAnimation, SIGNAL(Sig_currentRect(int, int, int, int)), this, SLOT(updateDeleUpperMove(int, int, int, int)));
    connect(pAnimation, SIGNAL(finished()), this, SLOT(onAnimationDeleUpperMoveFinish()));

    pAnimation->setStartValue(QRect(0, 0, width, height));
    pAnimation->setEndValue(QRect(0, 0 - height, width, height));
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
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
        setAnimationDeleStatus(false);
        startAnimationDeleLeftMove();
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

void SingleMsg::updateCurrentRect(int x1, int y1, int x2, int y2)
{
    qDebug()<<"SingleMsg::updateCurrentRect "<<y1;
    int nHeight;
    if(true == m_strBody.isEmpty())
    {
        nHeight = 90 - 6;
    }
    else
    {
        nHeight = 114 - 6;
    }

    if(false == m_bAnimationFlag)
    {
        m_pSingleWidget->setGeometry(0, (y1 - nHeight), this->width(), nHeight);
        m_pAnimationBaseMapWidget->setFixedSize(10, y1);
    }
    else
    {
        m_pSingleWidget->setGeometry(0, (0 - y1), this->width(), nHeight);
        m_pAnimationBaseMapWidget->setFixedSize(10, (nHeight - y1));
    }

//    this->resize(x2, y1 + 6);
    return;
}

void SingleMsg::onAnimationFinish()
{
    if(false == m_bAnimationFlag)
    {
        m_pAppVLaout->removeWidget(m_pAnimationBaseMapWidget);
        m_pAppVLaout->addWidget(m_pSingleWidget);
    }
    else
    {
        this->setVisible(false);
        m_pAppVLaout->removeWidget(m_pAnimationBaseMapWidget);
        m_pAppVLaout->addWidget(m_pSingleWidget);
        emit Sig_notifyAppShowBaseMap();
    }
}

void SingleMsg::updateDeleLeftMove(int x1, int y1, int x2, int y2)
{
    qDebug()<<"SingleMsg::updateDeleLeftMove "<<x1;
    int nWidth = this->width();
    int nHeight = this->height();
    if(true == m_strBody.isEmpty())
    {
        nHeight = 90 - 6;
    }
    else
    {
        nHeight = 114 - 6;
    }

    m_pSingleWidget->setGeometry(x1, 0, nWidth, nHeight);

}

void SingleMsg::onAnimationDeleLeftMoveFinish()
{
    startAnimationDeleUpperMove();
}

void SingleMsg::updateDeleUpperMove(int x1, int y1, int x2, int y2)
{
    qDebug()<<"SingleMsg::updateDeleUpperMove "<<x2 <<y1;
    if((y2 - 6 + y1) >= 0) //y2-6表示填充控件的高度，y1为负数，首先将填充控件的高度不断减少直至0
    {
        m_pAnimationBaseMapWidget->setFixedSize(x2, (y2 - 6 + y1));
    }
    else  //当填充控件减至0以后，就需要减少底部6个px的空白
    {
        m_pAppVLaout->setContentsMargins(0,0,0,(y2 + y1));
    }

}

void SingleMsg::onAnimationDeleUpperMoveFinish()
{
    emit Sig_onDeleSingleMsg(this);
}



