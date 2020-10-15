#ifndef SHORTCUTBUTTON_H
#define SHORTCUTBUTTON_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QGSettings>
#include <QVariant>
#include "swichButtonOpenStatus.h"
#include "customstyle_switchNormalStatus.h"

#define UKUI_QT_STYLE          "org.ukui.style"
#define UKUI_QT_STYLE_NAME_KEY "styleName"

class ShortcutButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ShortcutButton();
    void initButtonStyle();
    void initGsettingValue();

public:
    QGSettings      *m_pTabletModeGsetting;
    bool             m_bStatusButton;
    CustomStyle_SwitchOpenStatus      *m_pButtonOpenStatus;
    customstyle_switchNormalStatus    *m_pButtonNormalStatus;
};

#endif // SHORTCUTBUTTON_H
