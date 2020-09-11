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

#ifdef BUILD_TARGET
    m_pVolumeSlide       = new QSlider(Qt::Horizontal);
    m_pVolumeSlide->setFixedSize(120, 20);
#else
    m_pVolumeSlide       = new QSlider(Qt::Vertical);
    m_pVolumeSlide->setFixedSize(20, 120);
#endif

    connect(m_pVolumeSlide, &QSlider::valueChanged, this, &ScrollingAreaWidget::setVolumeSlideSlots);

    m_pHVolumeLayout     = new QGridLayout();
    m_pHVolumeLayout->setHorizontalSpacing(3);
    m_pHVolumeLayout->setVerticalSpacing(3);
    m_pHVolumeLayout->setContentsMargins(0, 0, 0, 0);
    m_pHVolumeLayout->setSpacing(0);

    m_pBrightNessWidget  = new QWidget();
    m_pBrightNessWidget->setContentsMargins(0, 0, 0, 0);
    m_pBrightIconLabel   = new QLabel();
    m_pBrightIconLabel->setFixedSize(24, 24);

#ifdef BUILD_TARGET
    m_pBrightSlide       = new QSlider(Qt::Horizontal);
    m_pBrightSlide->setFixedSize(120, 20);
#else
    m_pBrightSlide       = new QSlider(Qt::Vertical);
    m_pBrightSlide->setFixedSize(20, 120);
#endif

    connect(m_pBrightSlide, &QSlider::valueChanged, this, &ScrollingAreaWidget::setBrightSlideSlots);

    m_pBrightLayout      = new QGridLayout();
    m_pBrightLayout->setHorizontalSpacing(3);
    m_pBrightLayout->setVerticalSpacing(3);
    m_pBrightLayout->setContentsMargins(0, 0, 0, 0);
    m_pBrightLayout->setSpacing(0);
}

void ScrollingAreaWidget::initGsettingValue()
{
    /* 链接time-shutdown的dgsetting接口 */
    const QByteArray id(UKUI_VOLUME_BRIGHTNESS_GSETTING_ID);
    if(QGSettings::isSchemaInstalled(id)) {
        m_pVolumeLightSetting = new QGSettings(id);
    }
    if (m_pVolumeLightSetting != nullptr) {
        connect(m_pVolumeLightSetting, &QGSettings::changed, this, &ScrollingAreaWidget::setSliderValue);
        qDebug() << "当前的gsetting的key值" << m_pVolumeLightSetting->keys();
    }

    /* 链接time-shutdown的dgsetting接口 */
    const QByteArray id_2(KYLIN_POWER_MODE_GSETTING_VALUE);
    if(QGSettings::isSchemaInstalled(id_2)) {
        m_pBrightNessSetting = new QGSettings(id_2);
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
    m_pBrightIconLabel->setPixmap(QIcon::fromTheme("display-brightness-symbolic").pixmap(m_pBrightIconLabel->size()));

    /* 每一个需要在垂直布局与水平布局的切换的widget中，需要使用QGridLayout来布局 */
#ifdef BUILD_TARGET // 通用PC模式，使用的是水平布局，使用QGridLayout
    m_pHVolumeLayout->addWidget(m_pVolumeIconLabel, 0, 0, 1, 1);
    m_pHVolumeLayout->addWidget(m_pVolumeSlide, 0, 1, 1, 1);
    m_pVolumeWidget->setFixedHeight(24);
#else               // 通用PC模式，使用的是垂直布局
    m_pHVolumeLayout->addWidget(m_pVolumeSlide, 0, 0, 1, 1);
    m_pHVolumeLayout->addWidget(m_pVolumeIconLabel, 1, 0, 1, 1);
    m_pVolumeWidget->setFixedWidth(24);
#endif
    m_pVolumeWidget->setLayout(m_pHVolumeLayout);

#ifdef BUILD_TARGET
    m_pBrightLayout->addWidget(m_pBrightIconLabel, 0, 0, 1, 1);
    m_pBrightLayout->addWidget(m_pBrightSlide, 0, 1, 1, 1);
    m_pBrightNessWidget->setFixedHeight(24);
#else
    m_pBrightLayout->addWidget(m_pBrightSlide, 0, 0, 1, 1);
    m_pBrightLayout->addWidget(m_pBrightIconLabel, 1, 0, 1, 1);
    m_pBrightNessWidget->setFixedWidth(24);
#endif
    m_pBrightNessWidget->setLayout(m_pBrightLayout);

#ifdef BUILD_TARGET
    m_pHMainLayout->addItem(new QSpacerItem(10, 32));
    m_pHMainLayout->addWidget(m_pVolumeWidget);
    m_pHMainLayout->addItem(new QSpacerItem(10, 33));
    m_pHMainLayout->addWidget(m_pBrightNessWidget);
    m_pHMainLayout->addItem(new QSpacerItem(10, 36));
    this->setFixedSize(392, 56);
#else
    m_pHMainLayout->addItem(new QSpacerItem(10, 16));
    m_pHMainLayout->addWidget(m_pVolumeWidget);
    m_pHMainLayout->addItem(new QSpacerItem(10, 18));
    m_pHMainLayout->addWidget(m_pBrightNessWidget);
    m_pHMainLayout->addItem(new QSpacerItem(10, 18));
//    this->setFixedSize(200, 180);
#endif
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
