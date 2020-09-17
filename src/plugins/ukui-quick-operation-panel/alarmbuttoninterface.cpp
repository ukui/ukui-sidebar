#include "alarmbuttoninterface.h"

alarmButtonInterface::alarmButtonInterface(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initLayout();
}

void alarmButtonInterface::initMemberVariables()
{
    m_pButtonWidget = new QWidget();
    m_pButtonWidget->setFixedSize(56, 56);

    m_pAlarmButton = new QPushButton();
    connect(m_pAlarmButton, &switchButton::clicked, this, &alarmButtonInterface::AlarmButtonClickSlots);
    m_pAlarmButton->setFixedSize(56, 56);
    m_pAlarmButton->setIcon(QIcon::fromTheme("icon-alarm", QIcon(KYLIN_AlARM_NORMAL_PATH)));
    m_pAlarmButton->setIconSize(QSize(16, 16));

    m_pDeleteButton = new QPushButton();
    m_pDeleteButton->setFixedSize(20, 20);
    m_pDeleteButton->setIcon(QIcon(KYLIN_DELETE_ICONPATH));
    m_pDeleteButton->setIconSize(QSize(12, 12));

    m_pAlarmLabel  = new QLabel();
    m_pAlarmLabel->setText(QObject::tr("Alarm"));
    m_pAlarmLabel->setAlignment(Qt::AlignHCenter);

    m_pVboxButtonLayout = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout->setSpacing(0);

    m_pVboxLayout       = new QVBoxLayout();
    m_pVboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxLayout->setSpacing(0);

    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");
    m_pAlarmButton->setStyle(m_pStyleNormal);

    this->setFixedSize(63, 78);
    this->setContentsMargins(0, 0, 0, 0);
}

void alarmButtonInterface::initLayout()
{
    m_pVboxButtonLayout->addWidget(m_pAlarmButton);
    m_pButtonWidget->setLayout(m_pVboxButtonLayout);

    m_pVboxLayout->addWidget(m_pButtonWidget, 0, Qt::AlignCenter);
    m_pVboxLayout->addItem(new QSpacerItem(5, 4));
    m_pVboxLayout->addWidget(m_pAlarmLabel);
    this->setLayout(m_pVboxLayout);
    m_pDeleteButton->setParent(this);
    m_pDeleteButton->move(43, 0);
    m_pDeleteButton->setVisible(false);
    return;
}

void alarmButtonInterface::AlarmButtonClickSlots()
{
    QProcess p(0);
    p.startDetached("ukui-clock");
    p.waitForStarted();
    return;
}
