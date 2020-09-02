#include "eyeprotectionmode.h"

eyeProtectionMode::eyeProtectionMode(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initLayout();
}

void eyeProtectionMode::initMemberVariables()
{
    m_pWidgetButton         = new QWidget();
    m_pWidgetButton->setFixedSize(56, 56);
    m_pWidgetButton->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout     = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);

    m_pEyeModeButton = new QPushButton();
    m_pEyeModeButton->setFixedSize(56, 56);
    m_pEyeModeButton->setIcon(QIcon::fromTheme(KYLIN_EYE_MODE_NORMAL_NAME, QIcon(KYLIN_EYE_MODE_NORMAL_PATH)));
    m_pEyeModeButton->setIconSize(QSize(32, 32));
//    connect(m_pPadButton, &switchButton::clicked, this, &padWidget::PadButtonClickSlots);

    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");
    m_pEyeModeButton->setStyle(m_pStyleNormal);

    m_pStyleOpen = new CustomStyle_SwitchOpenStatus("ukui-default");

    m_pEyeModeLabel = new QLabel(QObject::tr("护眼模式"));
    m_pEyeModeLabel->setAlignment(Qt::AlignHCenter);

    m_pVboxLayout = new QVBoxLayout();
    m_pVboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxLayout->setSpacing(0);

    this->setFixedSize(56, 78);
    this->setContentsMargins(0, 0, 0, 0);
    return;
}

void eyeProtectionMode::initLayout()
{
    m_pVboxButtonLayout->addWidget(m_pEyeModeButton, 0, Qt::AlignCenter);
    m_pWidgetButton->setLayout(m_pVboxButtonLayout);
    m_pVboxLayout->addWidget(m_pWidgetButton, 0, Qt::AlignCenter);
    m_pVboxLayout->addItem(new QSpacerItem(15, 4));
    m_pVboxLayout->addWidget(m_pEyeModeLabel);
    this->setLayout(m_pVboxLayout);
    return;
}
