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
#include <QHBoxLayout>
#include <QVBoxLayout>

SingleMsg::SingleMsg(QString strSummary, QDateTime dateTime, QString strBody)
{
    m_dateTime = dateTime;
    m_uNotifyTime = dateTime.toTime_t();

    //单条消息总体垂直布局器
    QVBoxLayout* pMainVLaout = new QVBoxLayout;
    pMainVLaout->setContentsMargins(0, 0, 0, 0);
    pMainVLaout->setSpacing(0);

    //主题部件
    QWidget* pSummaryWidget = new QWidget;
    //设置主题的水平布局器
    QHBoxLayout* pHSummaryLayout = new QHBoxLayout();
    pHSummaryLayout->setContentsMargins(0,0,26,0);
    pHSummaryLayout->setSpacing(0);
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
    pHSummaryLayout->addWidget(pSummaryLabel, 0, Qt::AlignLeft);

    //设置通知消息中的弹簧，水平任意伸缩使主题和时间分开
    QSpacerItem* pHExpandingSpacer = new QSpacerItem(100, 1, QSizePolicy::Expanding, QSizePolicy::Fixed);
    pHSummaryLayout->addSpacerItem(pHExpandingSpacer);

    //设置通知消息中的通知时间
    m_pTimeLabel = new QLabel();
    m_pTimeLabel->setObjectName("pushtime");
    m_pTimeLabel->setText("现在");
    m_pTimeLabel->setStyleSheet("background-color:transparent;");
    pHSummaryLayout->addWidget(m_pTimeLabel, 0, Qt::AlignRight);

    pSummaryWidget->setLayout(pHSummaryLayout);
    pMainVLaout->addWidget(pSummaryWidget);

    //设置通知消息中的正文QLabel，行高24px,采用自动换行模式
    if(false == strBody.isEmpty())
    {
        m_strBody.append("<p style='line-height:24px'>").append(strBody).append("</p>");
//        m_strBody = strBody;

        m_pBodyLabel = new QLabel();
        m_pBodyLabel->setObjectName("body");
        m_pBodyLabel->setFixedWidth(305);
        m_pBodyLabel->setStyleSheet("padding:0px;background-color:transparent;");
        QFontMetrics fontMetrics(m_pBodyLabel->font());
        int fontSize = fontMetrics.width(m_strBody);
        QString formatBody = m_strBody;
        if(fontSize > (m_pBodyLabel->width() - 5))
        {
            formatBody = fontMetrics.elidedText(m_strBody, Qt::ElideRight, m_pBodyLabel->width() + 130);
        }

        m_pBodyLabel->setText(formatBody);

        pMainVLaout->addWidget(m_pBodyLabel, 0, Qt::AlignLeft);
    }

    QLabel* pHBottomLabelLine = new QLabel;
    pHBottomLabelLine->setFixedWidth(340);
    pHBottomLabelLine->setFixedHeight(1);
    pHBottomLabelLine->setStyleSheet("QLabel{border-style:none;border:1px solid rgba(255,255,255,0.08);}");
    pMainVLaout->addWidget(pHBottomLabelLine, 0);
    this->setLayout(pMainVLaout);

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


