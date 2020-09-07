#include "scrollingareawidget.h"

ScrollingAreaWidget::ScrollingAreaWidget(QWidget *parent) : QWidget(parent)
{
    initMemberVariable();
    initGsettingValue();
    initSlideStatus();
    initLayout();
}

void ScrollingAreaWidget::initMemberVariable()
{
    m_pHMainLayout = new QHBoxLayout();
    m_pHMainLayout->setContentsMargins(0, 16, 0, 16);
    m_pHMainLayout->setSpacing(0);
    this->setContentsMargins(0, 0, 0, 0);

    m_pVolumeWidget      = new QWidget();
    m_pVolumeWidget->setContentsMargins(0, 0, 0, 0);
    m_pVolumeIconLabel   = new QLabel();
    m_pVolumeIconLabel->setFixedSize(24, 24);
    m_pVolumeSlide       = new QSlider(Qt::Horizontal);
    m_pVolumeSlide->setFixedSize(120, 20);
    connect(m_pVolumeSlide, &QSlider::valueChanged, this, &ScrollingAreaWidget::setVolumeSlideSlots);

    m_pHVolumeLayout     = new QHBoxLayout();
    m_pHVolumeLayout->setContentsMargins(0, 0, 0, 0);
    m_pHVolumeLayout->setSpacing(0);

    m_pBrightNessWidget  = new QWidget();
    m_pBrightNessWidget->setContentsMargins(0, 0, 0, 0);
    m_pBrightIconLabel   = new QLabel();
    m_pBrightIconLabel->setFixedSize(24, 24);
    m_pBrightSlide       = new QSlider(Qt::Horizontal);
    m_pBrightSlide->setFixedSize(120, 20);
    connect(m_pBrightSlide, &QSlider::valueChanged, this, &ScrollingAreaWidget::setBrightSlideSlots);

    m_pBrightLayout      = new QHBoxLayout();
    m_pBrightLayout->setContentsMargins(0, 0, 0, 0);
    m_pBrightLayout->setSpacing(0);
}

void ScrollingAreaWidget::initGsettingValue()
{
    /* 链接time-shutdown的dgsetting接口 */
    if(QGSettings::isSchemaInstalled(UKUI_VOLUME_BRIGHTNESS_GSETTING_ID)) {
        m_pVolumeLightSetting = new QGSettings(UKUI_VOLUME_BRIGHTNESS_GSETTING_ID);
    }
    if (m_pVolumeLightSetting != nullptr) {
        connect(m_pVolumeLightSetting, &QGSettings::changed, this, &ScrollingAreaWidget::setSliderValue);
        qDebug() << "当前的gsetting的key值" << m_pVolumeLightSetting->keys();
    }

    /* 链接time-shutdown的dgsetting接口 */
    if(QGSettings::isSchemaInstalled(KYLIN_POWER_MODE_GSETTING_VALUE)) {
        m_pBrightNessSetting = new QGSettings(KYLIN_POWER_MODE_GSETTING_VALUE);
    }
    if (m_pBrightNessSetting != nullptr) {
        connect(m_pBrightNessSetting, &QGSettings::changed, this, &ScrollingAreaWidget::setSliderValue);
        qDebug() << "当前的gsetting的key值" << m_pVolumeLightSetting->keys();
    }

    return;
}

void ScrollingAreaWidget::initSlideStatus()
{
    int value = m_pVolumeLightSetting->get(UKUI_VOLUME_KEY).toInt();
    m_pVolumeSlide->setValue(value);

    value = m_pBrightNessSetting->get(UKUI_BRIGHTNESS_KEY).toInt();
    m_pBrightSlide->setValue(value);
    return;
}

void ScrollingAreaWidget::initLayout()
{
    m_pVolumeIconLabel->setPixmap(QIcon::fromTheme("audio-volume-high-symbolic").pixmap(m_pVolumeIconLabel->size()));
    m_pHVolumeLayout->addWidget(m_pVolumeIconLabel);
    m_pHVolumeLayout->addItem(new QSpacerItem(3, 1));
    m_pHVolumeLayout->addWidget(m_pVolumeSlide);
    m_pVolumeWidget->setLayout(m_pHVolumeLayout);
    m_pVolumeWidget->setFixedHeight(24);

    m_pBrightIconLabel->setPixmap(QIcon::fromTheme("display-brightness-symbolic").pixmap(m_pBrightIconLabel->size()));
    m_pBrightLayout->addWidget(m_pBrightIconLabel);
    m_pBrightLayout->addItem(new QSpacerItem(3, 1));
    m_pBrightLayout->addWidget(m_pBrightSlide);
    m_pBrightNessWidget->setLayout(m_pBrightLayout);
    m_pBrightNessWidget->setFixedHeight(24);

    m_pHMainLayout->addItem(new QSpacerItem(32, 10));
    m_pHMainLayout->addWidget(m_pVolumeWidget);

    m_pHMainLayout->addItem(new QSpacerItem(29, 10));
    m_pHMainLayout->addWidget(m_pBrightNessWidget);
    m_pHMainLayout->addItem(new QSpacerItem(33, 10));
    this->setLayout(m_pHMainLayout);
}

/* 当对应的组件修改了gsetting，需修改对应滚动条的值 */
void ScrollingAreaWidget::setSliderValue(QString key)
{
    int value;
    if (key == UKUI_VOLUME_KEY) {
        value = m_pVolumeLightSetting->get(UKUI_VOLUME_KEY).toInt();
        m_pVolumeSlide->setValue(value);
    } else if (key == UKUI_BRIGHTNESS_KEY) {
        value = m_pBrightNessSetting->get(UKUI_BRIGHTNESS_KEY).toInt();
        m_pBrightSlide->setValue(value);
    }
    return;
}

/* 改变音量滚动条时，修改gsetting值，通知音量组件修改，同步 */
void ScrollingAreaWidget::setVolumeSlideSlots(int value)
{
    qDebug() << "123123131音量滚动条时" << value;
    m_pVolumeLightSetting->set(UKUI_VOLUME_KEY, value);
    return;
}

/* 改变亮度滚动条时，修改gsetting值，通知修改亮度，同步 */
void ScrollingAreaWidget::setBrightSlideSlots(int value)
{
    qDebug() << "123123131亮度滚动条时";
    m_pBrightNessSetting->set(UKUI_BRIGHTNESS_KEY, value);
    return;
}
