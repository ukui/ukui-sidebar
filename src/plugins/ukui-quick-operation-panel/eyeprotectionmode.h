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
#ifndef EYEPROTECTIONMODE_H
#define EYEPROTECTIONMODE_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGSettings>
#include <QVBoxLayout>
#include <QDir>
#include <QSettings>
#include <QProcess>
#include <QStyleOption>
#include <QDebug>
#include "shortcutbutton.h"
#include "switchbutton.h"
#include "labelfotmattext.h"

#define KYLIN_EYE_MODE_NORMAL_NAME   "ukui-icon-eyeprotectionmode"
#define KYLIN_EYE_MODE_SET_NAME      "ukui-icon-eyeprotectionmode-s"
#define KYLIN_EYE_MODE_OPEN_NAME     "ukui-icon-eyeprotectionmode-open"

#define KYLIN_EYE_MODE_NORMAL_PATH   ":/images/icon-eyeprotectionmode.svg"
#define KYLIN_EYE_MODE_SET_PATH      ":/images/icon-hotspot-s.svg"
#define KYLIN_EYE_MODE_OPEN_PATH     ":/images/icon-eyeprotectionmode-open.svg"
#define KYLIN_DELETE_ICONPATH        ":/images/cancel-lock.png"

#define NIGHT_MODE_KEY        "nightmodestatus"
#define NIGHT_MODE_LIGHT      "light"
#define NIGHE_MODE_NIGHT      "night"
#define NIGHT_MODE_CONTROL    "org.ukui.control-center.panel.plugins"

#define UKUI_QT_STYLE          "org.ukui.style"
#define GTK_STYLE              "org.mate.interface"
#define UKUI_QT_STYLE_NAME     "style-name"
#define DEFAULT_QT_STYLE_NAME  "styleName"
#define GTK_STYLE_NAME         "gtk-theme"
#define DEFAULT_GTK_STYLE_NAME "gtkTheme"

#define UKUI_PANEL_SETTINGS "org.ukui.panel.settings"
#define UKUI_SHORTCUT_GSETTING_VALUEE "org.ukui.quick-operation.panel"
#define SHOW_NIGHTMODE       "shownightmode"

class eyeProtectionMode : public QWidget
{
    Q_OBJECT
public:
    explicit eyeProtectionMode(QWidget *parent = nullptr);
    void   initMemberVariables();
    void   initGsettingValue();
    void   initLayout();

    void   setEyeButtonStatus(const bool nightMode);
    void   setUkuiStyle(QString style);                         // 设置主题
    void   setupSettings();                                     // 设置kwin
    void   writeKwinSettings(bool change, QString theme);       // 设置与Kwin　窗口管理器　标题栏颜色
    QColor getSystemPaleteColor();
    void   setLabelTextColor();
    void   setPreStyleName();
    QPushButton   *m_pDeleteButton;

protected:
    void paintEvent(QPaintEvent *e);

private:
    QWidget        *m_pWidgetButton;
    ShortcutButton *m_pEyeModeButton;
    QLabel         *m_pEyeModeLabel;

    QStyle         *m_pStyleOpen;
    QStyle         *m_pStyleNormal;

    QString         m_pCureentTheme;

    LabelFotmatText *m_pLabelFotmatText;

    QSettings     *m_pqsettings;
    QSettings     *m_pKwinSettings;
    QGSettings    *m_pTabletModeGsetting = nullptr;
    QGSettings    *m_pqtstyleGsettings   = nullptr;
    QGSettings    *m_pgtkstyleGsettings  = nullptr;
    QGSettings    *m_pShortCutGsettings  = nullptr;
    QVBoxLayout   *m_pVboxButtonLayout   = nullptr;
    QVBoxLayout   *m_pVboxLayout         = nullptr;

    bool          m_bModelStatus;

private slots:
    void          EyeButtonClickSlots();

Q_SIGNALS:

};

#endif // EYEPROTECTIONMODE_H
