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
#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QProcess>
#include "switchbutton.h"

#define KYLIN_SETTING_NORMAL_NAME       "kylin-setting-normal"
#define KYLIN_SETTING_HOVER_NAME        "kylin-setting-hover"
#define KYLIN_SETTING_PRESS_NAME        "kylin-setting-pressed"

#define KYLIN_SETTING_NORMAL_PATH       ":/image/setting-normal.svg"
#define KYLIN_SETTING_HOVER_PATH        ":/image/setting-hover.svg"
#define KYLIN_SETTING_PRESS_PATH        ":/image/setting-pressed.svg"

class settingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit settingWidget(QWidget *parent = nullptr);
    ~settingWidget();
    void initMemberVariables();
    void initLayout();
private:
    QWidget      *m_pWidgetButton;
    switchButton *m_psettingButton;
    QLabel       *m_psettingLabel;

    QVBoxLayout  *m_pVboxButtonLayout;
    QVBoxLayout  *m_pVboxLayout;

    QStringList   m_IconPathList;
    QStringList   m_IconNameList;

private slots:
    void settingButtonClick();
};

#endif // SETTINGWIDGET_H
