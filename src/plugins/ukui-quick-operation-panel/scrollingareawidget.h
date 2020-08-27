#ifndef SCROLLINGAREAWIDGET_H
#define SCROLLINGAREAWIDGET_H

#include <QObject>
#include <QWidget>
#include <QSlider>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QDebug>

class ScrollingAreaWidget : public QWidget
{
    Q_OBJECT
public:
    ScrollingAreaWidget(QWidget *parent = nullptr);

private:
    void initMemberVariable();
    void initLayout();

private:
    QHBoxLayout *m_pHMainLayout;

    QWidget     *m_pVolumeWidget;
    QLabel      *m_pVolumeIconLabel;
    QSlider     *m_pVolumeSlide;
    QVBoxLayout *m_pVVolumeLayout;

    QWidget     *m_pBrightNessWidget;
    QLabel      *m_pBrightIconLabel;
    QSlider     *m_pBrightSlide;
    QVBoxLayout *m_pBrightLayout;
};

#endif // SCROLLINGAREAWIDGET_H
