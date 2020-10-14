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
#include "labelfotmattext.h"
#define KYLIN_ALARM_NORMAL_NAME         "ukui-icon-alarm"
#define KYLIN_ALARM_NORMAL_NAME_SET     "ukui-icon-alarm-s"
#define KYLIN_BLUETOOTH_HOVER_NAME      "kylin-alarm-hover"
#define KYLIN_BLUETOOTH_PRESS_NAME      "kylin-alarm-pressed"

#define KYLIN_AlARM_NORMAL_PATH         ":/images/icon-alarm.svg"
#define KYLIN_AlARM_SET_PATH            ":/images/images/icon-alarm-s.svg"
#define KYLIN_DELETE_ICONPATH           ":/images/cancel-lock.png"

class alarmButtonInterface : public QWidget
{
    Q_OBJECT
public:
    explicit alarmButtonInterface(QWidget *parent = nullptr);
    QPushButton     *m_pDeleteButton;
private:
    void initMemberVariables();
    void initLayout();

private:
    QWidget         *m_pButtonWidget;
    QPushButton     *m_pAlarmButton;
    QLabel          *m_pAlarmLabel;

    LabelFotmatText *m_pLabelFotmatText;

    QVBoxLayout     *m_pVboxButtonLayout;
    QVBoxLayout     *m_pVboxLayout;

    QStyle          *m_pStyleNormal;

private slots:
    void AlarmButtonClickSlots();

Q_SIGNALS:

};

#endif // ALARMBUTTONINTERFACE_H
