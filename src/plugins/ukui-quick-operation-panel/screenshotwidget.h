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
#ifndef SCREENSHOTWIDGET_H
#define SCREENSHOTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QProcess>
#include "switchbutton.h"
#include "customstyle_switchNormalStatus.h"

#define KYLIN_SCREENSHOT_NORMAL_NAME    "kylin-icon-screenshot"
#define KYLIN_SCREENSHOT_SET_NAME       "kylin-icon-screenshot-s"

#define KYLIN_SCREENSHOT_NORMAL_PATH    ":/images/icon-screenshot.svg"
#define KYLIN_SCREENSHOT_SET_PATH       ":/images/icon-screenshot-s.svg"
#define KYLIN_DELETE_ICONPATH           ":/images/cancel-lock.png"

class screenshotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit screenshotWidget(QWidget *parent = nullptr);
    ~screenshotWidget();
    void initMemberVariables();
    void initLayout();

private:
    QWidget      *m_pWidgetButton;
    QPushButton  *m_pscreenshotButton;
    QPushButton  *m_pDeleteButton;
    QLabel       *m_pscreenshotlabel;

    QStyle       *m_pStyleNormal;

    QVBoxLayout  *m_pVboxButtonLayout;
    QVBoxLayout  *m_pVboxLayout;
private slots:
    void         sreenShotButtonClickedSlots();
};

#endif // SCREENSHOTWIDGET_H
