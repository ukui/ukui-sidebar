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
#include <QVBoxLayout>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusError>
#include <QDBusReply>
#include <QApplication>
#include <QScreen>
#include "picturetowhite.h"
#define CONTROL_CENTER_TIME_FORMAT_GSETTING "org.ukui.control-center.panel.plugins"
#define CONTROL_TINE_FORMAT_GSETTING_VALUE "hoursystem"
#define TIME_FORMAT "12"
class AppMsg;
class ButtonWidget;

class SingleMsg : public QWidget
{
    Q_OBJECT
public:
    SingleMsg(AppMsg* pParent, QString strIconPath, QString strAppName, QString strSummary, QDateTime dateTime, QString strBody, QString strUrl, QString strAction, bool bTakeInFlag = false);
    void initTimeFormatGsetting();
    void updatePushTime();
    void setBodyLabelWordWrap(bool bFlag);
    void setLeftItem(int nShowLeftCount);
    void setMainFlag(bool bFlag) {m_bMain = bFlag;}
    void setFoldFlag(bool bFlag) {m_bFold = bFlag;}
    void setShowLeftItemFlag(bool bFlag);
    void setSingleMsgContentsMargins(int left, int top, int right, int bottom);
    void mainMsgSetFold();
    void startAnimationUnfold();                        //开启展开动画
    void startAnimationFold();                          //开启折叠动画
    void startAnimationDeleUpperMove();                 //开启删除上移动画
    void listenTimeZone();                              //监听时区变化dbus
    void initGsettingValue();                           //初始化监听主题
    void jumpAction();                                  //执行跳转动作

    QDBusInterface *m_datetimeInterface;

    uint        getPushTime() {return m_uNotifyTime;}
    QDateTime   getPushDateTime() {return m_dateTime;}
    QString     getIcon() {return m_strIconPath;}
    QString     getSummary() {return m_strSummary;}
    QString     getBody() {return m_strBody;}
    QString     getUrl() {return m_strUrl;}
    QString     getAction() {return m_strAction;}


    enum TaskWidgetStatus{NORMAL, HOVER, PRESS};
    TaskWidgetStatus status;

    bool m_bAppFold;                        //消息所属应用是否折叠

protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *e);                //重绘事件


private:
    QVBoxLayout*    m_pAppVLaout;
    QHBoxLayout*    m_pIconHLayout;
    QWidget*        m_pSingleWidget;                //除去底部6px的空白之外的一个内框部件
    QWidget*        m_pAnimationBaseMapWidget;      //动画底图动态模拟大小替身部件
    QWidget*        m_pIconWidget;                  //在动画中暂定高38px

    QWidget*        m_pTimeLabelWidget;
    QWidget*        m_pStorageDeleteButtonWidget;

    QLabel*         m_pTimeLabel;                   //时间标签
    ButtonWidget*   m_pSingleTakeinButton;          //单条消息中的收纳按钮
    ButtonWidget*   m_pSingleDeleteButton;          //单条消息中的删除按钮
    QLabel*         m_pSummaryLabel;                //在动画中暂定高26px
    QLabel*         m_pBodyLabel;                   //正文标签,收缩时,在动画中暂定高24px
    QWidget*        m_pShowLeftWidget;              //显示该应用未展开部件
    QLabel*         m_pShowLeftItemLabel;           //显示该应用未展开条数
    QTimer*         m_pSetDeleDelayTimer;
    QTimer*         m_pSetJumpDelayTimer;
    QWidget*        m_pContextWidget;
    QGSettings     *m_pStyleGsetting;               //监听主题的gsetting



    QString         m_strIconPath;                  //图标路径
    QString         m_strSummary;                   //保存主题
    QString         m_strBody;                      //保存正文
    QString         m_strUrl;                       //跳转链接
    QString         m_strAction;                    //跳转动作
    QDateTime       m_dateTime;                     //保存推送时间
    uint            m_uNotifyTime;                  //保存推送时间的绝对时间
    uint            m_uTimeDifference;              //保存当前时间与推送时间的时间差
    bool            m_bTakeInFlag;                  //收纳标志
    bool            m_bFold;                        //本条消息是否折叠
    bool            m_bMain;                        //是否为主窗口
    int             m_nShowLeftCount;               //为主窗口时,剩余显示条数
    bool            m_bTimeFormat;                  //time制式，0代表12小时制，1代表24小时制
    QGSettings      *stylesettings;
    AppMsg          *m_pParent;                     //父类指针
    bool            jumpFlag;                       //跳转标志

signals:
    void            Sig_onDeleSingleMsg(SingleMsg* p);
    void            Sig_onTakeInSingleMsg(SingleMsg* p);
    void            Sig_onRecoverSingleMsg(SingleMsg* p);
    void            Sig_onDeleteAppMsg();
    void            Sig_onTakeinWholeApp();
    void            Sig_onRecoverWholeApp();
    void            Sig_setAppFoldFlag(bool bFoldFlag);
    void            Sig_onMainEnter();              //应用主消息鼠标进入信号，发送至App,让分层底图变色
    void            Sig_onMainLeave();              //应用主消息鼠标离开信号，发送至App,让分层底图背景变回来
    void            Sig_notifyAppShowBaseMap();     //当动画折叠后，通知主app考虑显示底图
    void            Sig_notifyAppHideBaseMap();     //通知隐藏应用的底图部件
    void            Sig_jumpAction();  //执行跳转动作信号

public slots:
    void            onDele();                       //通知中心或者收纳盒中的删除
    void            onTakeIn();                     //通知中心消息收纳至收纳盒
    void            onRecover();                    //收纳盒消息恢复至通知中心

    void            updateUnfoldMove(const QVariant &value);        //更新展开的移动数据
    void            onUnfoldFinish();                               //处理展开完成时的函数
    void            updateFoldMove(const QVariant &value);          //更新折叠的移动数据
    void            onFoldFinish();                                 //处理折叠完成时的函数
    void            updateDeleLeftMove(const QVariant &value);      //更新删除左移时的移动数据
    void            onDeleLeftMoveFinish();                         //处理删除左移完成时的函数
    void            updateDeleUpperMove(const QVariant &value);     //更新删除上移时的移动数据
    void            onDeleUpperMoveFinish();                        //处理删除上移完成时的函数
    void            startAnimationDeleLeftMove();                   //开启删除左移动画
    void            listenTimeZoneSlots();                          //监听时区变化函数
    void            slotChangeFonts(const QString &key);            //系统字体变化时，优化显示显示格式
};

#endif // SINGLEMSG_H
