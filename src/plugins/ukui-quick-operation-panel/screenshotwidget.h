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

#define KYLIN_SCREENSHOT_NORMAL_NAME    "kylin-screenshot-normal"
#define KYLIN_SCREENSHOT_HOVER_NAME     "kylin-screenshot-hover"
#define KYLIN_SCREENSHOT_PRESS_NAME     "kylin-screenshot-pressed"


#define KYLIN_SCREENSHOT_NORMAL_PATH    ":/image/screenshot-normal.svg"
#define KYLIN_SCREENSHOT_HOVER_PATH     ":/image/screenshot-hover.svg"
#define KYLIN_SCREENSHOT_PRESS_PATH     ":/image/screenshot-pressed.svg"

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
    switchButton   *m_pscreenshotButton;
    QLabel       *m_pscreenshotlabel;

    QVBoxLayout  *m_pVboxButtonLayout;
    QVBoxLayout  *m_pVboxLayout;

    QStringList   m_IconPathList;
    QStringList   m_IconNameList;
private slots:
    void         sreenShotButtonClickedSlots();
};

#endif // SCREENSHOTWIDGET_H
