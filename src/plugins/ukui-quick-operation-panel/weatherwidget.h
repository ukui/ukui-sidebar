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
#ifndef WEATHERWIDGET_H
#define WEATHERWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QFont>
#include <QIcon>
#include <QGSettings>
#include <QDebug>
#include <QProcess>
#include "picturetowhite.h"

#define UKUI_WEATHER_GSETTING_ID  "org.china-weather-data.settings"
#define UKUI_WEATHER_GSETTING_KEY "weather"

class weatherWidget : public QWidget
{
    Q_OBJECT
public:
    explicit weatherWidget(QWidget *parent = nullptr);
    void initMemberVariables();
    void initLabelData();
    void setLabelData(QStringList WeatherInfoList);
    void initGSettingValue();
    void initLayout();

private:
    QLabel  *m_pWeatherIconLabel;
    QLabel  *m_pAreaLabel;
    QLabel  *m_pWeatherNumLabel;
    QHBoxLayout *m_pMainHLayout;

    PictureToWhite *m_pPictureToWhite;

    QString m_pweatherString;
    QGSettings *m_pWeatherGsetting = nullptr;

protected:
    void mousePressEvent(QMouseEvent *event);

private slots:
    void    getGsettingChageSlots(QString key);

Q_SIGNALS:

};

#endif // WEATHERWIDGET_H
