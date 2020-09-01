#include "VPNButtonwidget.h"

diturbModeWidget::diturbModeWidget(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initLayout();
}

void diturbModeWidget::initMemberVariables()
{
    m_pButtonWidget = new QWidget();
    m_pButtonWidget->setFixedSize(56, 56);

    m_pVPNButton = new QPushButton();
    m_pVPNButton->setIcon(QIcon::fromTheme(KYLIN_VPN_NORMAL_NAME, QIcon(KYLIN_BLUETOOTH_NORMAL_PATH)));
    connect(m_pVPNButton, &switchButton::clicked, this, &diturbModeWidget::VPNButtonClickSLots);
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

    this->setFixedSize(56, 78);
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

void diturbModeWidget::VPNButtonClickSLots()
{
    QProcess p(0);
    p.startDetached("ukui-control-center -v");
    p.waitForStarted();
    return;
}
