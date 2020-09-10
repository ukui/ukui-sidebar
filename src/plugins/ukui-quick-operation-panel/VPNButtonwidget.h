#ifndef DITURBMODEWIDGET_H
#define DITURBMODEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QProcess>
#include "switchbutton.h"
#include "customstyle_switchNormalStatus.h"

#define KYLIN_VPN_NORMAL_NAME     "kylin-icon-VPN"
#define KYLIN_VPN_SET_NAME        "kylin-icon-VPN-s"
#define KYLIN_VPN_OPEN_NAME       "Kylin-icon-VPN-open.svg"

#define KYLIN_BLUETOOTH_NORMAL_PATH     ":/images/icon-VPN.svg"
#define KYLIN_BLUETOOTH_SET_PATH        ":/images/icon-VPN-s.svg"
#define KULIN_VPN_OPEN_PATH             ":/images/icon-VPN-open.svg"
#define KYLIN_DELETE_ICONPATH           ":/images/cancel-lock.png"

class diturbModeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit diturbModeWidget(QWidget *parent = nullptr);
    QPushButton     *m_pDeleteButton;

private:
    void initMemberVariables();
    void initLayout();

private:
    QWidget         *m_pButtonWidget;
    QPushButton     *m_pVPNButton;

    QLabel          *m_pVPNLabel;

    QVBoxLayout     *m_pVboxButtonLayout;
    QVBoxLayout     *m_pVboxLayout;

    QStyle          *m_pStyleNormal;

private slots:
    void VPNButtonClickSLots();

Q_SIGNALS:

};

#endif // DITURBMODEWIDGET_H
