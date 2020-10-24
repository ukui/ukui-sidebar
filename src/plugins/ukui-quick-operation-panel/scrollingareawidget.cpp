/*
* Copyright (C) 2020 Tianjin KYLIN Information Technology Co., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, see <http://www.gnu.org/licenses/&gt;.
*
*/
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

    m_pPictureToWhite = new PictureToWhite();

    m_pVolumeWidget      = new QWidget();
    m_pVolumeWidget->setContentsMargins(0, 0, 0, 0);
    m_pVolumeIconLabel   = new QLabel();
    m_pVolumeIconLabel->setProperty("useIconHighlightEffect", true);
    m_pVolumeIconLabel->setProperty("iconHighlightEffectMode", true);
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
    setVolumeStatusIcon(value);

    value = m_pBrightNessSetting->get(UKUI_BRIGHTNESS_KEY).toInt();
    m_pBrightSlide->setValue(value);
    setLightStatusIcon(value);
    return;
}

void ScrollingAreaWidget::initLayout()
{
    m_pVolumeIconLabel->setPixmap(QIcon::fromTheme("ukui-icon-sound-middle").pixmap(m_pVolumeIconLabel->size()));
    m_pHVolumeLayout->addWidget(m_pVolumeIconLabel);
    m_pHVolumeLayout->addItem(new QSpacerItem(3, 1));
    m_pHVolumeLayout->addWidget(m_pVolumeSlide);
    m_pVolumeWidget->setLayout(m_pHVolumeLayout);
    m_pVolumeWidget->setFixedHeight(24);

    m_pBrightIconLabel->setPixmap(QIcon::fromTheme("ukui-icon-light-0").pixmap(m_pBrightIconLabel->size()));
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
        qDebug() << "当前音量值" << value;
        m_pVolumeSlide->setValue(value);
        setVolumeStatusIcon(value);
    } else if (key == UKUI_BRIGHTNESS_KEY) {
        value = m_pBrightNessSetting->get(UKUI_BRIGHTNESS_KEY).toInt();
        m_pBrightSlide->setValue(value);
        setLightStatusIcon(value);
    }
    return;
}

/* 根据声音大小值设置状态图标 */
void ScrollingAreaWidget::setVolumeStatusIcon(int value)
{
    if (value == 0)
        m_pVolumeIconLabel->setPixmap(QIcon::fromTheme("ukui-icon-sound-low").pixmap(m_pVolumeIconLabel->size()));
    else if (value > 0 && value <= 35)
        m_pVolumeIconLabel->setPixmap(QIcon::fromTheme("ukui-icon-sound-low").pixmap(m_pVolumeIconLabel->size()));
    else if (value >= 36 && value <= 65)
        m_pVolumeIconLabel->setPixmap(QIcon::fromTheme("ukui-icon-sound-middle").pixmap(m_pVolumeIconLabel->size()));
    else
       m_pVolumeIconLabel->setPixmap(QIcon::fromTheme("ukui-icon-sound-high").pixmap(m_pVolumeIconLabel->size()));
    m_pVolumeIconLabel->update();
}

/* 根据亮度值设置状态图标 */
void ScrollingAreaWidget::setLightStatusIcon(int value)
{
    if (value == 0)
        m_pBrightIconLabel->setPixmap(QIcon::fromTheme("ukui-icon-light-0").pixmap(m_pBrightIconLabel->size()));
    else if (value > 0 && value <= 25)
        m_pBrightIconLabel->setPixmap(QIcon::fromTheme("ukui-icon-light-25").pixmap(m_pBrightIconLabel->size()));
    else if (value >25 && value <= 50)
        m_pBrightIconLabel->setPixmap(QIcon::fromTheme("ukui-icon-light-50").pixmap(m_pBrightIconLabel->size()));
    else if (value > 50 && value <= 75)
        m_pBrightIconLabel->setPixmap(QIcon::fromTheme("ukui-icon-light-75").pixmap(m_pBrightIconLabel->size()));
    else if (value > 75)
        m_pBrightIconLabel->setPixmap(QIcon::fromTheme("ukui-icon-light-100").pixmap(m_pBrightIconLabel->size()));
    m_pBrightIconLabel->update();
}

/* 改变音量滚动条时，修改gsetting值，通知音量组件修改，同步 */
void ScrollingAreaWidget::setVolumeSlideSlots(int value)
{
    if (nullptr != m_pVolumeLightSetting) {
        m_pVolumeLightSetting->set(UKUI_VOLUME_KEY, value);
    }
    setVolumeStatusIcon(value);
    return;
}

/* 改变亮度滚动条时，修改gsetting值，通知修改亮度，同步 */
void ScrollingAreaWidget::setBrightSlideSlots(int value)
{
    if (nullptr != m_pBrightNessSetting) {
        m_pBrightNessSetting->set(UKUI_BRIGHTNESS_KEY, value);
    }
    setLightStatusIcon(value);
    return;
}
