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

#include "swichButtonOpenStatus.h"
#include "customstyle_switchNormalStatus.h"
#include "switchbutton.h"

#define KYLIN_EYE_MODE_NORMAL_NAME   "ukui-icon-eyeprotectionmode"
#define KYLIN_EYE_MODE_SET_NAME      "ukui-icon-hotspot-s"
#define KYLIN_EYE_MODE_OPEN_NAME     "ukui-icon-eyeprotectionmode-open"

#define KYLIN_EYE_MODE_NORMAL_PATH   ":/images/icon-eyeprotectionmode.svg"
#define KYLIN_EYE_MODE_SET_PATH      ":/images/icon-hotspot-s.svg"
#define KYLIN_EYE_MODE_OPEN_PATH     ":/images/icon-eyeprotectionmode-open.svg"

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

private:
    QWidget       *m_pWidgetButton;
    QPushButton   *m_pEyeModeButton;
    QLabel        *m_pEyeModeLabel;

    QStyle        *m_pStyleOpen;
    QStyle        *m_pStyleNormal;

    QSettings     *m_pqsettings;
    QSettings     *m_pKwinSettings;
    QGSettings    *m_pTabletModeGsetting = nullptr;
    QGSettings    *m_pqtstyleGsettings   = nullptr;
    QGSettings    *m_pgtkstyleGsettings  = nullptr;
    QVBoxLayout   *m_pVboxButtonLayout   = nullptr;
    QVBoxLayout   *m_pVboxLayout         = nullptr;

    bool          m_bModelStatus;

private slots:
    void          EyeButtonClickSlots();

Q_SIGNALS:

};

#endif // EYEPROTECTIONMODE_H
