#ifndef NODISTURBWIDGET_H
#define NODISTURBWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
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
#include <QLabel>
#include <QVBoxLayout>
#include "switchbutton.h"

#define KYLIN_NODISTURB_NORMAL_NAME     "kylin-nodisturb-normal"
#define KYLIN_NODISTURB_HOVER_NAME     "kylin-nodisturb-hover"
#define KYLIN_NODISTURB_PRESS_NAME     "kylin-nodisturb-pressed"


#define KYLIN_NODISTURB_NORMAL_PATH     ":/image/nodisturb-normal.svg"
#define KYLIN_NODISTURB_HOVER_PATH     ":/image/nodisturb-hover.svg"
#define KYLIN_NODISTURB_PRESS_PATH     ":/image/nodisturb-pressed.svg"

class nodisturbWidget : public QWidget
{
    Q_OBJECT
public:
    explicit nodisturbWidget(QWidget *parent = nullptr);
    ~nodisturbWidget();
    void initMemberVariables();
    void initLayout();
private:
    QWidget       *m_pWidgetButton;
    switchButton  *m_pnodisturbButton;
    QLabel        *m_pnodisturbLabel;

    QVBoxLayout   *m_pVboxButtonLayout;
    QVBoxLayout   *m_pVboxLayout;

    QStringList  m_IconPathList;
    QStringList  m_IconNameList;
};

#endif // NODISTURBWIDGET_H
