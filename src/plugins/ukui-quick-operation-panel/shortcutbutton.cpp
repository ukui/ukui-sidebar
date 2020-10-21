#include "shortcutbutton.h"
#include <QDebug>
ShortcutButton::ShortcutButton()
{
    initButtonStyle();
    initGsettingValue();
}

void ShortcutButton::initButtonStyle()
{
    m_pButtonNormalStatus = new customstyle_switchNormalStatus("ukui-default");
    m_pButtonOpenStatus   = new CustomStyle_SwitchOpenStatus("ukui-default");
    return;
}

void ShortcutButton::initGsettingValue()
{
    const QByteArray id(UKUI_QT_STYLE);
    if (QGSettings::isSchemaInstalled(id)) {
        m_pTabletModeGsetting = new QGSettings(id);
        connect(m_pTabletModeGsetting, &QGSettings::changed, [=](QString key) {
            if (UKUI_QT_STYLE_NAME_KEY == key) {
                if (m_bStatusButton) {
                    this->setStyle(m_pButtonOpenStatus);
                    qDebug() << "是否进入这么";
                } else {
                    this->setStyle(m_pButtonNormalStatus);
                }
            }
        });
    }
    return;
}
