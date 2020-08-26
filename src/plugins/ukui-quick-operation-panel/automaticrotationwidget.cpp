#include "automaticrotationwidget.h"

AutomaticRotationWidget::AutomaticRotationWidget(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initLayout();
}

void AutomaticRotationWidget::initMemberVariables()
{
    m_IconPathList << KYLIN_AUTOMATICROTATION_NORMAL_PATH << KYLIN_AUTOMATICROTATION_HOVER_PATH << KYLIN_AUTOMATICROTATION_PRESS_PATH;
    m_IconNameList << KYLIN_AUTOMATICROTATION_NORMAL_NAME << KYLIN_AUTOMATICROTATION_HOVER_NAME << KYLIN_AUTOMATICROTATION_PRESS_NAME;
    m_pWidgetButton = new QWidget();
    m_pWidgetButton->setFixedSize(56, 56);
    m_pWidgetButton->setContentsMargins(0, 0, 0, 0);
    m_pAutomaticRotationButton =  new switchButton(m_IconPathList, m_IconNameList);
    m_pAutomaticRotationButton->setFixedSize(56, 56);
    m_pAutomaticRotationButton->setIconSize(QSize(32, 32));

    m_pVboxButtonLayout = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout->setSpacing(0);

    m_pAutomaticRotationLabel = new QLabel();
    m_pAutomaticRotationLabel->setText(QObject::tr("Auto rotate"));
    m_pAutomaticRotationLabel->setAlignment(Qt::AlignHCenter);

    m_pStyleOpen   = new CustomStyle_SwitchOpenStatus("ukui-default");
    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");
    m_pAutomaticRotationButton->setStyle(m_pStyleOpen);
    m_pVboxLayout = new QVBoxLayout();
    m_pVboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxLayout->setSpacing(0);

    this->setFixedSize(60, 78);
    this->setContentsMargins(0, 0, 0, 0);
}

void AutomaticRotationWidget::initLayout()
{
    m_pVboxButtonLayout->addWidget(m_pAutomaticRotationButton, 0, Qt::AlignCenter);
    m_pWidgetButton->setLayout(m_pVboxButtonLayout);
    m_pVboxLayout->addWidget(m_pWidgetButton);
    m_pVboxLayout->addItem(new QSpacerItem(1, 4));
    m_pVboxLayout->addWidget(m_pAutomaticRotationLabel);
    this->setLayout(m_pVboxLayout);
}
