#ifndef EYEPROTECTIONMODE_H
#define EYEPROTECTIONMODE_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGSettings>
#include <QVBoxLayout>
#include "swichButtonOpenStatus.h"
#include "customstyle_switchNormalStatus.h"
#include "switchbutton.h"

#define KYLIN_EYE_MODE_NORMAL_NAME   "ukui-icon-eyeprotectionmode"
#define KYLIN_EYE_MODE_SET_NAME      "ukui-icon-hotspot-s"
#define KYLIN_EYE_MODE_OPEN_NAME     "ukui-icon-eyeprotectionmode-open"

#define KYLIN_EYE_MODE_NORMAL_PATH   ":/images/icon-eyeprotectionmode.svg"
#define KYLIN_EYE_MODE_SET_PATH      ":/images/icon-hotspot-s.svg"
#define KYLIN_EYE_MODE_OPEN_PATH     ":/images/icon-eyeprotectionmode-open.svg"

class eyeProtectionMode : public QWidget
{
    Q_OBJECT
public:
    explicit eyeProtectionMode(QWidget *parent = nullptr);
    void   initMemberVariables();
    void   initGsettingValue();
    void   initLayout();
    void   setPadButtonStatus();
    QColor getSystemPaleteColor();
    void   setLabelTextColor();
private:
    QWidget       *m_pWidgetButton;
    QPushButton   *m_pEyeModeButton;
    QLabel        *m_pEyeModeLabel;

    QStyle        *m_pStyleOpen;
    QStyle        *m_pStyleNormal;

    QGSettings    *m_pTabletModeGsetting;
    QVBoxLayout   *m_pVboxButtonLayout;
    QVBoxLayout   *m_pVboxLayout;

    bool          m_bModelStatus;

Q_SIGNALS:

};

#endif // EYEPROTECTIONMODE_H
