#include "feedbackButtonWidget.h"

feedbackButtonWidget::feedbackButtonWidget(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initLayout();
}

void feedbackButtonWidget::initMemberVariables()
{
    m_pButtonWidget = new QWidget();
    m_pButtonWidget->setFixedSize(56, 56);

    m_pFeedBackButton = new QPushButton();
    connect(m_pFeedBackButton, &switchButton::clicked, this, &feedbackButtonWidget::FeedbackButtonClickSlots);
    m_pFeedBackButton->setFixedSize(56, 56);
    m_pFeedBackButton->setIcon(QIcon::fromTheme("icon-alarm", QIcon(KYLIN_AlARM_NORMAL_PATH)));
    m_pFeedBackButton->setIconSize(QSize(24, 24));

    m_pDeleteButton = new QPushButton();
    m_pDeleteButton->setFixedSize(20, 20);
    m_pDeleteButton->setIcon(QIcon(KYLIN_DELETE_ICONPATH));
    m_pDeleteButton->setIconSize(QSize(12, 12));

    m_pFeedBackLabel  = new QLabel();
    m_pFeedBackLabel->setText(QObject::tr("Feedback"));
    m_pFeedBackLabel->setAlignment(Qt::AlignHCenter);

    m_pVboxButtonLayout = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout->setSpacing(0);

    m_pVboxLayout       = new QVBoxLayout();
    m_pVboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxLayout->setSpacing(0);

    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");
    m_pFeedBackButton->setStyle(m_pStyleNormal);

    this->setFixedSize(63, 78);
    this->setContentsMargins(0, 0, 0, 0);
}

void feedbackButtonWidget::initLayout()
{
    m_pVboxButtonLayout->addWidget(m_pFeedBackButton);
    m_pButtonWidget->setLayout(m_pVboxButtonLayout);

    m_pVboxLayout->addWidget(m_pButtonWidget, 0, Qt::AlignCenter);
    m_pVboxLayout->addItem(new QSpacerItem(5, 4));
    m_pVboxLayout->addWidget(m_pFeedBackLabel);
    this->setLayout(m_pVboxLayout);
    m_pDeleteButton->setParent(this);
    m_pDeleteButton->move(43, 0);
    m_pDeleteButton->setVisible(false);
    return;
}

void feedbackButtonWidget::FeedbackButtonClickSlots()
{
    QProcess p(0);
    p.startDetached("ukui-feedback");
    p.waitForStarted();
    return;
}
