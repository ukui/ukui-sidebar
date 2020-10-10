#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QProcess>
#include "switchbutton.h"
#include "customstyle_switchNormalStatus.h"

#define KYLIN_ALARM_NORMAL_NAME         "kylin-alarm-normal"
#define KYLIN_ALARM_NORMAL_NAME_SET     "kylin-alarm-normal-s"
#define KYLIN_BLUETOOTH_HOVER_NAME      "kylin-alarm-hover"
#define KYLIN_BLUETOOTH_PRESS_NAME      "kylin-alarm-pressed"

#define KYLIN_AlARM_NORMAL_PATH         ":/images/icon-alarm.svg"
#define KYLIN_AlARM_SET_PATH            ":/images/images/icon-alarm-s.svg"
#define KYLIN_DELETE_ICONPATH           ":/images/cancel-lock.png"

class feedbackButtonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit feedbackButtonWidget(QWidget *parent = nullptr);
    QPushButton     *m_pDeleteButton;
private:
    void initMemberVariables();
    void initLayout();

private:
    QWidget         *m_pButtonWidget;
    QPushButton     *m_pFeedBackButton;
    QLabel          *m_pFeedBackLabel;

    QVBoxLayout     *m_pVboxButtonLayout;
    QVBoxLayout     *m_pVboxLayout;

    QStyle          *m_pStyleNormal;

private slots:
    void FeedbackButtonClickSlots();

Q_SIGNALS:

};
