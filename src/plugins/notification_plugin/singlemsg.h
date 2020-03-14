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
#include <QVBoxLayout>


class AppMsg;
class ButtonWidget;
class DiyPropertyAnimation;

class SingleMsg : public QWidget
{
    Q_OBJECT
public:
    SingleMsg(AppMsg* pParent, QString strIconPath, QString strAppName, QString strSummary, QDateTime dateTime, QString strBody, bool bTakeInFlag = false);
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

    uint        getPushTime() {return m_uNotifyTime;}
    QDateTime   getPushDateTime() {return m_dateTime;}
    QString     getIcon() {return m_strIconPath;}
    QString     getSummary() {return m_strSummary;}
    QString     getBody() {return m_strBody;}


protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    QVBoxLayout*    m_pAppVLaout;
    QWidget*        m_pSingleWidget;                //除去底部6px的空白之外的一个内框部件
    QWidget*        m_pAnimationBaseMapWidget;      //动画底图动态模拟大小替身部件
    QWidget*        m_pIconWidget;                  //在动画中暂定高38px
    QLabel*         m_pTimeLabel;                   //时间标签
    ButtonWidget*   m_pSingleTakeinButton;          //单条消息中的收纳按钮
    ButtonWidget*   m_pSingleDeleteButton;          //单条消息中的删除按钮
    QLabel*         m_pSummaryLabel;                //在动画中暂定高26px
    QLabel*         m_pBodyLabel;                   //正文标签,收缩时,在动画中暂定高24px
    QWidget*        m_pShowLeftWidget;              //显示该应用未展开部件
    QLabel*         m_pShowLeftItemLabel;           //显示该应用未展开条数



    QString         m_strIconPath;                  //图标路径
    QString         m_strSummary;                   //保存主题
    QString         m_strBody;                      //保存正文
    QDateTime       m_dateTime;                     //保存推送时间
    uint            m_uNotifyTime;                  //保存推送时间的绝对时间
    bool            m_bTakeInFlag;                  //收纳标志
    bool            m_bFold;                        //是否折叠
    bool            m_bMain;                        //是否为主窗口
    int             m_nShowLeftCount;               //为主窗口时,剩余显示条数
    bool            m_bTimeFormat;                  //time制式，0代表12小时制，1代表24小时制

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

public slots:
    void            onDele();                       //通知中心或者收纳盒中的删除
    void            onTakeIn();                     //通知中心消息收纳至收纳盒
    void            onRecover();                    //收纳盒消息恢复至通知中心

    void            updateUnfoldMove(int x1, int y1, int x2, int y2);       //更新展开的移动数据
    void            onUnfoldFinish();                                       //处理展开完成时的函数
    void            updateFoldMove(int x1, int y1, int x2, int y2);         //更新折叠的移动数据
    void            onFoldFinish();                                         //处理折叠完成时的函数
    void            updateDeleLeftMove(int x1, int y1, int x2, int y2);     //更新删除左移时的移动数据
    void            onDeleLeftMoveFinish();                                 //处理删除左移完成时的函数
    void            updateDeleUpperMove(int x1, int y1, int x2, int y2);    //更新删除上移时的移动数据
    void            onDeleUpperMoveFinish();                                //处理删除上移完成时的函数
    void            startAnimationDeleLeftMove();                           //开启删除左移动画

};

#endif // SINGLEMSG_H
