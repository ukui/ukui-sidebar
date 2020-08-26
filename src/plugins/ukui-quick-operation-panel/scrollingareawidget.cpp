#include "scrollingareawidget.h"

ScrollingAreaWidget::ScrollingAreaWidget(QWidget *parent) : QWidget(parent)
{
    initMemberVariable();
    initLayout();
}

void ScrollingAreaWidget::initMemberVariable()
{
    m_pHMainLayout = new QHBoxLayout();
    m_pHMainLayout->setContentsMargins(0, 0, 0, 0);
    m_pHMainLayout->setSpacing(0);
    this->setContentsMargins(0, 0, 0, 0);

    m_pVolumeWidget      = new QWidget();
    m_pVolumeWidget->setContentsMargins(0, 0, 0, 0);
    m_pVolumeIconLabel   = new QLabel();
    m_pVolumeIconLabel->setFixedSize(24, 24);
    m_pVolumeSlide       = new QSlider(Qt::Horizontal);
    m_pVolumeSlide->setFixedSize(120, 20);
    m_pHVolumeLayout     = new QHBoxLayout();
    m_pHVolumeLayout->setContentsMargins(0, 0, 0, 0);
    m_pHVolumeLayout->setSpacing(0);

    m_pBrightNessWidget  = new QWidget();
    m_pBrightNessWidget->setContentsMargins(0, 0, 0, 0);
    m_pBrightIconLabel   = new QLabel();
    m_pBrightIconLabel->setFixedSize(24, 24);
    m_pBrightSlide       = new QSlider(Qt::Horizontal);
    m_pBrightSlide->setFixedSize(120, 20);
    m_pBrightLayout      = new QHBoxLayout();
    m_pBrightLayout->setContentsMargins(0, 0, 0, 0);
    m_pBrightLayout->setSpacing(0);
}

void ScrollingAreaWidget::initLayout()
{
    m_pVolumeIconLabel->setPixmap(QIcon::fromTheme("audio-volume-high-symbolic").pixmap(m_pVolumeIconLabel->size()));
    m_pHVolumeLayout->addWidget(m_pVolumeIconLabel);
    m_pHVolumeLayout->addItem(new QSpacerItem(3, 1));
    m_pHVolumeLayout->addWidget(m_pVolumeSlide);
    m_pVolumeWidget->setLayout(m_pHVolumeLayout);

    m_pBrightIconLabel->setPixmap(QIcon::fromTheme("display-brightness-symbolic").pixmap(m_pBrightIconLabel->size()));
    m_pBrightLayout->addWidget(m_pBrightIconLabel);
    m_pBrightLayout->addItem(new QSpacerItem(3, 1));
    m_pBrightLayout->addWidget(m_pBrightSlide);
    m_pBrightNessWidget->setLayout(m_pBrightLayout);

    m_pHMainLayout->addItem(new QSpacerItem(32, 10));
    m_pHMainLayout->addWidget(m_pVolumeWidget);

    m_pHMainLayout->addItem(new QSpacerItem(29, 10));
    m_pHMainLayout->addWidget(m_pBrightNessWidget);
    m_pHMainLayout->addItem(new QSpacerItem(33, 10));
    this->setLayout(m_pHMainLayout);
}
