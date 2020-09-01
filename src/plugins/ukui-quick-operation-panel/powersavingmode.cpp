#include "powersavingmode.h"

powerSavingMode::powerSavingMode(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initGsettingValue();
    initLayout();
}

void powerSavingMode::initMemberVariables()
{
    m_pWidgetButton         = new QWidget();
    m_pWidgetButton->setFixedSize(56, 56);
    m_pWidgetButton->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout     = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);

    m_pPowerModeButton = new QPushButton();
    m_pPowerModeButton->setFixedSize(56, 56);
    m_pPowerModeButton->setIconSize(QSize(32, 32));
//    connect(m_pPowerModeButton, &switchButton::clicked, this, &powerSavingMode::PadButtonClickSlots);

    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");
    m_pPowerModeButton->setStyle(m_pStyleNormal);

    m_pStyleOpen = new CustomStyle_SwitchOpenStatus("ukui-default");

    m_pPowerModeLabel = new QLabel(QObject::tr("平板模式"));
    m_pPowerModeLabel->setAlignment(Qt::AlignHCenter);

    m_pVboxLayout = new QVBoxLayout();
    m_pVboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxLayout->setSpacing(0);

    this->setFixedSize(56, 78);
    this->setContentsMargins(0, 0, 0, 0);
    return;
}

void powerSavingMode::initGsettingValue()
{
    /* 链接time-shutdown的dgsetting接口 */
    if (QGSettings::isSchemaInstalled(KYLIN_POWER_MODE_GSETTING_VALUE))
        m_pTabletModeGsetting = new QGSettings(KYLIN_POWER_MODE_GSETTING_VALUE);
    if (m_pTabletModeGsetting != nullptr) {
        qDebug() << "当前的gsetting的key值" << m_pTabletModeGsetting->keys();
    }
    return;
}

void powerSavingMode::initLayout()
{
    m_pVboxButtonLayout->addWidget(m_pPowerModeButton, 0, Qt::AlignCenter);
    m_pWidgetButton->setLayout(m_pVboxButtonLayout);
    m_pVboxLayout->addWidget(m_pWidgetButton, 0, Qt::AlignCenter);
    m_pVboxLayout->addItem(new QSpacerItem(15, 4));
    m_pVboxLayout->addWidget(m_pPowerModeLabel);
    this->setLayout(m_pVboxLayout);
    return;
}
