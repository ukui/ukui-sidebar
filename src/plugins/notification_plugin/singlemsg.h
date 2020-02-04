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

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QPushButton>
#include <QToolButton>
#include <QDateTime>


class NotificationPlugin;

class SingleMsg : public QWidget
{
    Q_OBJECT
public:
    SingleMsg(NotificationPlugin *parent, QString strAppName, QString strIcon, QString strSummary, QDateTime dateTime, QString strBody);
    ~SingleMsg();
    uint getNotifyAbsuluteTime() {return m_uNotifyTime;}

protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

private:
    QString         m_strAppName;                   //保存发送方的应用名
    uint            m_uNotifyTime;                  //保存推送时间的绝对时间
    QString         m_strBody;                      //保存正文字符串

    QLabel*         m_pAppNameLabel;
    QLabel*         m_pBodyLabel;                   //保存正文的Label
    QWidget*        m_pButtonWidget;                //保存底下收纳和删除按钮的Widget
    bool            m_bTakeInFlag;                  //转变为收纳消息吗，默认为false



signals:
    void            Sig_Send(SingleMsg *p);         //将本对象指针发送出去
    void            Sig_SendTakein(SingleMsg *p);

public slots:
    void            onClear();                      //清除消息
    void            onTakein();                     //处理收纳消息

};

#endif // SINGLEMSG_H
