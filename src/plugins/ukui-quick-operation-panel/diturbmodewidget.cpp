#include "diturbmodewidget.h"

diturbModeWidget::diturbModeWidget(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initLayout();
}

void diturbModeWidget::initMemberVariables()
{
    m_IconPathList << KYLIN_BLUETOOTH_NORMAL_PATH << KYLIN_BLUETOOTH_HOVER_PATH << KYLIN_BLUETOOTH_PRESS_PATH;
    m_IconNameList << KYLIN_BLUETOOTH_NORMAL_NAME << KYLIN_BLUETOOTH_HOVER_NAME << KYLIN_BLUETOOTH_PRESS_NAME;
    m_pButtonWidget = new QWidget();
    m_pButtonWidget->setFixedSize(56, 56);

    m_pVPNButton = new switchButton(m_IconPathList, m_IconNameList);
//    connect(m_pDiturbModeButton, &switchButton::clicked, this, &alarmButtonInterface::AlarmButtonClickSlots);
    m_pVPNButton->setFixedSize(56, 56);
    m_pVPNButton->setIconSize(QSize(32, 32));

    m_pVPNLabel  = new QLabel();
    m_pVPNLabel->setText(QObject::tr("VPN"));
    m_pVPNLabel->setAlignment(Qt::AlignHCenter);

    m_pVboxButtonLayout = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout->setSpacing(0);

    m_pVboxLayout       = new QVBoxLayout();
    m_pVboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxLayout->setSpacing(0);

    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");
    m_pVPNButton->setStyle(m_pStyleNormal);

    this->setFixedSize(60, 78);
    this->setContentsMargins(0, 0, 0, 0);
}

void diturbModeWidget::initLayout()
{
    m_pVboxButtonLayout->addWidget(m_pVPNButton);
    m_pButtonWidget->setLayout(m_pVboxButtonLayout);

    m_pVboxLayout->addWidget(m_pButtonWidget, 0, Qt::AlignCenter);
    m_pVboxLayout->addItem(new QSpacerItem(5, 4));
    m_pVboxLayout->addWidget(m_pVPNLabel);
    this->setLayout(m_pVboxLayout);
}
