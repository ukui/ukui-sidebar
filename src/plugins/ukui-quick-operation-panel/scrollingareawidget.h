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
#ifndef SCROLLINGAREAWIDGET_H
#define SCROLLINGAREAWIDGET_H

#include <QObject>
#include <QWidget>
#include <QSlider>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QDebug>
#include <QGSettings>
#include "picturetowhite.h"

#define UKUI_VOLUME_BRIGHTNESS_GSETTING_ID "org.ukui.quick-operation.panel"
#define UKUI_VOLUME_KEY "volumesize"

#define KYLIN_POWER_MODE_GSETTING_VALUE        "org.ukui.power-manager"
#define UKUI_BRIGHTNESS_KEY "brightness-ac"

class ScrollingAreaWidget : public QWidget
{
    Q_OBJECT
public:
    ScrollingAreaWidget(QWidget *parent = nullptr);

private:
    void initMemberVariable();
    void initGsettingValue();
    void initSlideStatus();
    void initLayout();
    void setVolumeStatusIcon(int value);
    void setLightStatusIcon();

private:
    QHBoxLayout *m_pHMainLayout;

    QWidget     *m_pVolumeWidget;
    QLabel      *m_pVolumeIconLabel;
    QSlider     *m_pVolumeSlide;
    QHBoxLayout *m_pHVolumeLayout;

    QWidget     *m_pBrightNessWidget;
    QLabel      *m_pBrightIconLabel;
    QSlider     *m_pBrightSlide;
    QHBoxLayout *m_pBrightLayout;

    QGSettings  *m_pVolumeLightSetting = nullptr;
    QGSettings  *m_pBrightNessSetting  = nullptr;

    PictureToWhite *m_pPictureToWhite;

private slots:
    void setSliderValue(QString key);
    void setVolumeSlideSlots(int value);
    void setBrightSlideSlots(int value);
};

#endif // SCROLLINGAREAWIDGET_H
