#ifndef ALARMBUTTONINTERFACE_H
#define ALARMBUTTONINTERFACE_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QProcess>
#include "switchbutton.h"
#include "customstyle_switchNormalStatus.h"

#define KYLIN_BLUETOOTH_NORMAL_NAME     "kylin-bluetooth-normal"
#define KYLIN_BLUETOOTH_HOVER_NAME      "kylin-bluetooth-hover"
#define KYLIN_BLUETOOTH_PRESS_NAME      "kylin-bluetooth-pressed"

#define KYLIN_BLUETOOTH_NORMAL_PATH     ":/image/bluetooth-normal.svg"
#define KYLIN_BLUETOOTH_HOVER_PATH      ":/image/bluetooth-hover.svg"
#define KYLIN_BLUETOOTH_PRESS_PATH      ":/image/bluetooth-pressed.svg"

class alarmButtonInterface : public QWidget
{
    Q_OBJECT
public:
    explicit alarmButtonInterface(QWidget *parent = nullptr);

private:
    void initMemberVariables();
    void initLayout();

private:
    QWidget         *m_pButtonWidget;
    switchButton    *m_pAlarmButton;
    QLabel          *m_pAlarmLabel;

    QVBoxLayout     *m_pVboxButtonLayout;
    QVBoxLayout     *m_pVboxLayout;

    QStyle          *m_pStyleNormal;

    QStringList      m_IconPathList;
    QStringList      m_IconNameList;

private slots:
    void AlarmButtonClickSlots();

Q_SIGNALS:

};

#endif // ALARMBUTTONINTERFACE_H
