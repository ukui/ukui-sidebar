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

    QString m_pweatherString;
    QGSettings *m_pWeatherGsetting;

private slots:
    void    getGsettingChageSlots(QString key);

Q_SIGNALS:

};

#endif // WEATHERWIDGET_H
