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

    QGSettings  *m_pVolumeLightSetting;
    QGSettings  *m_pBrightNessSetting;

private slots:
    void setSliderValue(QString key);
    void setVolumeSlideSlots(int value);
    void setBrightSlideSlots(int value);
};

#endif // SCROLLINGAREAWIDGET_H
