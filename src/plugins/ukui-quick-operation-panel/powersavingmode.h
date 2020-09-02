#ifndef POWERSAVINGMODE_H
#define POWERSAVINGMODE_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGSettings>
#include <QVBoxLayout>
#include <QDebug>
#include <QStyleOption>
#include "swichButtonOpenStatus.h"
#include "customstyle_switchNormalStatus.h"
#include "switchbutton.h"

#define KYLIN_POWER_SAVING_NORMAL_NAME   "ukui-icon-powersavingmode-normal"
#define KYLIN_POWER_SAVING_SET_NAME      "ukui-icon-powersavingmode-s"
#define KYLIN_POWER_SAVING_OPEN_NAME     "ukui-icon-powersavingmode-open"

#define KYLIN_POWER_SAVING_NORMAL_PATH   ":/images/icon-powersavingmode.svg"
#define KYLIN_POWER_SAVING_SET_PATH      ":/images/icon-powersavingmode-s.svg"
#define KYLIN_POWER_SAVING_OPEN_PATH     ":/images/icon-powersavingmode-open.svg"

#define KYLIN_POWER_MODE_GSETTING_VALUE        "org.ukui.power-manager"
#define KYLIN_POWER_SREEN_BRIGHTNESS_AC_KEY    "brightness-ac"
#define KYLIN_POWER_SLEEP_DISPLAY_AC_KEY       "sleep-display-ac"
#define KYLIN_POWER_SLEEP_BATTERY_KEY          "sleep-display-battery"

#define UKUI_VOLUME_BRIGHTNESS_GSETTING_ID     "org.ukui.quick-operation.panel"
#define UKUI_ENERGY_SAVING_MODE_KEY            "energysavingmode"

class powerSavingMode : public QWidget
{
    Q_OBJECT
public:
    explicit powerSavingMode(QWidget *parent = nullptr);

private:
    void   initMemberVariables();
    void   initGsettingValue();
    void   initButtonStatus();
    void   initLayout();
    void   setPowerModeButtonStatus();
    QColor getSystemPaleteColor();
    void   setLabelTextColor();

private:
    QWidget       *m_pWidgetButton;
    QPushButton   *m_pPowerModeButton;
    QLabel        *m_pPowerModeLabel;

    QStyle        *m_pStyleOpen;
    QStyle        *m_pStyleNormal;

    QGSettings    *m_pSavingModeGsetting;
    QGSettings    *m_pSavingModeButtonStatusGsetting;
    QVBoxLayout   *m_pVboxButtonLayout;
    QVBoxLayout   *m_pVboxLayout;

    bool          m_bModelStatus;

private slots:
    void PowerSavingButtonClickSlots();

Q_SIGNALS:

};

#endif // POWERSAVINGMODE_H
