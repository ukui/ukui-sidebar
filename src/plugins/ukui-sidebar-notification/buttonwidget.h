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

#ifndef BUTTONWIDGET_H
#define BUTTONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QIcon>
#include <QPixmap>
#include <QPushButton>
#include <QGSettings>
#include "picturetowhite.h"
#define UKUI_QT_STYLE          "org.ukui.style"
#define UKUI_QT_STYLE_NAME_KEY "styleName"
#define UKUI_QT_DARK_NAME      "ukui-dark"
#define UKUI_CLOSE_ICON        "window-close-symbolic"

class ButtonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonWidget();
    ~ButtonWidget();
    void initMemberVariables();
    void initGsettingValue();
    QPushButton*    m_pDeleteButton;

private:
    QPixmap*        m_pTakeinPixmap;                //收纳默认或悬停时的像素
    QPixmap*        m_pTakeinPressPixmap;           //收纳点击时的像素
    QGSettings      *m_pTabletModeGsetting;
    bool            m_bTakeInFlag;
    PictureToWhite  *m_pPictureToWhite;
signals:
    void            Sig_clicked();

public slots:
    void ChangedSlots(QString key);
};

#endif // BUTTONWIDGET_H
