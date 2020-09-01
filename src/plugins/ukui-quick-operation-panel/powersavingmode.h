#ifndef POWERSAVINGMODE_H
#define POWERSAVINGMODE_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGSettings>
#include <QVBoxLayout>
#include <QDebug>
#include "swichButtonOpenStatus.h"
#include "customstyle_switchNormalStatus.h"
#include "switchbutton.h"

#define KYLIN_POWER_MODE_GSETTING_VALUE        "org.ukui.power-manager"
#define KYLIN_POWER_SREEN_BRIGHTNESS_MODLE     "brightness-ac"

class powerSavingMode : public QWidget
{
    Q_OBJECT
public:
    explicit powerSavingMode(QWidget *parent = nullptr);

private:
    void   initMemberVariables();
    void   initGsettingValue();
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

    QGSettings    *m_pTabletModeGsetting;
    QVBoxLayout   *m_pVboxButtonLayout;
    QVBoxLayout   *m_pVboxLayout;

    bool          m_bModelStatus;
signals:

};

#endif // POWERSAVINGMODE_H
