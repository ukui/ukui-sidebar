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

#ifndef SINGLEMSG_H
#define SINGLEMSG_H

#include <QWidget>
#include <QLabel>
#include <QDateTime>
#include <QToolButton>

class AppMsg;

class SingleMsg : public QWidget
{
    Q_OBJECT
public:
    SingleMsg(AppMsg* pParent, QString strSummary, QDateTime dateTime, QString strBody, bool bTakeInFlag = false);
    void updatePushTime();
    void setTopLabelLineVisible(bool bFlag);
    void setTimeLabelVisible(bool bFlag);
    void setBodyLabelWordWrap(bool bFlag);
    void setLeaveShowNoTimeFlag(bool bFlag) {m_bLeaveShowNoTimeFlag = bFlag;}
    uint getPushTime() {return m_uNotifyTime;}
    QDateTime getPushDateTime() {return m_dateTime;}
    QString getSummary() {return m_strSummary;}
    QString getBody() {return m_strBody;}
    bool getSingleDeleteButtonVisible() {return m_pSingleDeleteButton->isVisible();}

protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;

private:    
    QDateTime       m_dateTime;                     //保存推送时间
    uint            m_uNotifyTime;                  //保存推送时间的绝对时间
    QLabel*         m_pTimeLabel;
    QToolButton*    m_pSingleTakeinButton;          //单条消息中的收纳按钮
    QToolButton*    m_pSingleDeleteButton;          //单条消息中的删除按钮
    QLabel*         m_pBodyLabel;
    QLabel*         m_pHTopLabelLine;               //消息顶部分割线
    QString         m_strSummary;                   //保存主题
    QString         m_strBody;                      //保存正文
    QString         m_strFormatBody;                //保存格式化后的正文
    bool            m_bTakeInFlag;                  //收纳标志
    bool            m_bLeaveShowNoTimeFlag;         //鼠标离开不显示时间标志，只有当上层应用折叠，且该条置顶时设为true

signals:
    void            Sig_onDele(SingleMsg* p);
    void            Sig_onTakeIn(SingleMsg* p);

public slots:
    void            onDele();
    void            onTakeIn();

};

#endif // SINGLEMSG_H
