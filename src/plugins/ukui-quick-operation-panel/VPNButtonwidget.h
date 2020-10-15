/*
* Copyright (C) 2020 Tianjin KYLIN Information Technology Co., Ltd.
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
#ifndef DITURBMODEWIDGET_H
#define DITURBMODEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QProcess>
#include "switchbutton.h"
#include "customstyle_switchNormalStatus.h"
#include "labelfotmattext.h"

#define KYLIN_VPN_NORMAL_NAME     "ukui-icon-VPN"
#define KYLIN_VPN_SET_NAME        "ukui-icon-VPN-s"
#define KYLIN_VPN_OPEN_NAME       "ukui-icon-VPN-open"

#define KYLIN_BLUETOOTH_NORMAL_PATH     ":/images/icon-VPN.svg"
#define KYLIN_VPN_SET_PATH              ":/images/icon-VPN-s.svg"
#define KULIN_VPN_OPEN_PATH             ":/images/icon-VPN-open.svg"
#define KYLIN_DELETE_ICONPATH           ":/images/cancel-lock.png"

class diturbModeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit diturbModeWidget(QWidget *parent = nullptr);
    QPushButton     *m_pDeleteButton;

private:
    void initMemberVariables();
    void initLayout();

private:
    QWidget         *m_pButtonWidget;
    QPushButton     *m_pVPNButton;

    QLabel          *m_pVPNLabel;
    LabelFotmatText *m_pLabelFotmatText;

    QVBoxLayout     *m_pVboxButtonLayout;
    QVBoxLayout     *m_pVboxLayout;

    QStyle          *m_pStyleNormal;

private slots:
    void VPNButtonClickSLots();

Q_SIGNALS:

};

#endif // DITURBMODEWIDGET_H
