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

    bsrWidget1 = new BsrWidget;
 //   bsrWidget1->setFixedSize(60,200);


//    m_pVolumeSlide       = new QSlider(Qt::Vertical);
//    m_pVolumeSlide->setFixedSize(20,200);
    m_pVVolumeLayout     = new QVBoxLayout();
    m_pVVolumeLayout->setContentsMargins(0, 0, 0, 0);
    m_pVVolumeLayout->setSpacing(0);

    m_pBrightNessWidget  = new QWidget();
    m_pBrightNessWidget->setContentsMargins(0, 0, 0, 0);
    m_pBrightIconLabel   = new QLabel();
    m_pBrightIconLabel->setFixedSize(24, 24);

    bsrWidget2 = new BsrWidget;
   // bsrWidget2->setFixedSize(60,200);


//    m_pBrightSlide       = new QSlider(Qt::Vertical);
//    m_pBrightSlide->setFixedSize(20,200);
    m_pBrightLayout      = new QVBoxLayout();
    m_pBrightLayout->setContentsMargins(0, 0, 0, 0);
    m_pBrightLayout->setSpacing(0);
}

void ScrollingAreaWidget::initLayout()
{
    m_pVolumeIconLabel->setPixmap(QIcon::fromTheme("audio-volume-high-symbolic").pixmap(m_pVolumeIconLabel->size()));

    m_pVVolumeLayout->addWidget(bsrWidget1);
    m_pVVolumeLayout->addItem(new QSpacerItem(1, 5));
    m_pVVolumeLayout->addWidget(m_pVolumeIconLabel,0, Qt::AlignCenter);

    m_pVolumeWidget->setLayout(m_pVVolumeLayout);

    m_pBrightIconLabel->setPixmap(QIcon::fromTheme("display-brightness-symbolic").pixmap(m_pBrightIconLabel->size()));

    //m_pBrightLayout->addItem(new QSpacerItem(3, 1));
    m_pBrightLayout->addWidget(bsrWidget2);
    m_pBrightLayout->addWidget(m_pBrightIconLabel,0, Qt::AlignCenter);
    m_pBrightNessWidget->setLayout(m_pBrightLayout);

    m_pHMainLayout->addItem(new QSpacerItem(25, 10));
    m_pHMainLayout->addWidget(m_pVolumeWidget);

    m_pHMainLayout->addItem(new QSpacerItem(50, 10));
    m_pHMainLayout->addWidget(m_pBrightNessWidget);
    this->setLayout(m_pHMainLayout);
}
