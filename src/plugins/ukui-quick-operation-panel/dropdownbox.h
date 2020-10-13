#ifndef DROPDOWNBOX_H
#define DROPDOWNBOX_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QPixmap>
#include <QScrollArea>
#include <QGSettings>
#include <QVariant>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDebug>
#include <QPainter>

#define KYLIN_ALARM_NORMAL_NAME_SET     "kylin-alarm-normal-s"
#define KYLIN_BLUETOOTH_SET_NAME        "kylin-icon-bluetooth-s"
#define KYLIN_CALCULATOR_SET_NAME       "kylin-icon-allsetting-s"
#define KYLIN_EYE_MODE_SET_NAME         "ukui-icon-hotspot-s"
#define KYLIN_HOTSPOT_SET_NAME          "kylin-icon-hotspot-s"
#define KYLIN_NODISTURB_SET_NAME        "kylin-icon-DND-s"
#define KYLIN_NOTEBOOK_SET_NAME         "kylin-icon-notes-s"
#define KYLIN_PAD_SET_NAME              "kylin-icon-tabletmode-s"
#define KYLIN_POWER_SAVING_SET_NAME     "kylin-icon-powersavingmode-s"
#define KYLIN_SCREENSHOT_SET_NAME       "kylin-icon-screenshot-s"
#define KYLIN_SETTING_SET_NAME          "kylin-icon-allsetting-s"
#define KYLIN_VPN_SET_PATH              "kylin-icon-VPN-s"
#define KYLIN_FEEDBACK_SET_PATH         "ukui-icon-feedback-s"

#define KYLIN_EYE_MODE_SET_PATH         ":/images/icon-eyeprotectionmode-s.svg"
#define KYLIN_AlARM_SET_PATH            ":/images/icon-alarm-s.svg"
#define KYLIN_HOTSPOT_SET_PATH          ":/image/icon-hotspot-s.svg"
#define KYLIN_BLUETOOTH_SET_PATH        ":/images/icon-bluetooth-s.svg"
#define KYLIN_CALCULATOR_SET_PATH       ":/images/icon-calculator-s.svg"
#define KYLIN_SCREENSHOT_SET_PATH       ":/images/icon-screenshot-s.svg"
#define KYLIN_NOTEBOOK_SET_PATH         ":/images/icon-notes-s.svg"
#define KYLIN_VPN_SET_PATH              ":/images/icon-VPN-s.svg"
#define KYLIN_NODISTURB_SET_PATH        ":/images/icon-DND-s.svg"
#define KYLIN_PC_SET_PATH               ":/images/icon-pcmode-s.svg"
#define KYLIN_SETTING_SET_PATH          ":/images/icon-allsetting-s.svg"
#define KYLIN_POWER_SAVING_SET_PATH     ":/images/icon-powersavingmode-s.svg"

#define SHORTCUT_BUTTON_GSETTING_PATH   "org.ukui.quick-operation.button.widget"

typedef struct ButtonInfoStruct
{
    QString iconName;
    QString iconPath;
    QString entryName;
}ButtonInfo;

class EntryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EntryWidget(QString iconName, QString iconPath, QString entryName, QString key, QWidget *parent = nullptr);
    void initMemberVariables();
    void initLayout();

public:
    QLabel      *m_pPixmapLabel;
    QLabel      *m_pTextLabel;
    QHBoxLayout *m_pHEntryLayout;
    QString     IconName;
    QString     IconPath;
    QString     EntryName;
    QString     gsettingKey;
    enum TaskWidgetStatus{NORMAL, HOVER, PRESS};
    TaskWidgetStatus status = NORMAL;

protected:
    void mousePressEvent(QMouseEvent *event);
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);
    void paintEvent(QPaintEvent *event);

Q_SIGNALS:
    void        WidgetClickSignal(QString gsettingKey);
};

class dropDownBox :public QWidget
{
    Q_OBJECT
public:
    explicit dropDownBox(QWidget *parent = nullptr);

public:
    QListWidget *m_pListWidget;
    QHBoxLayout *m_pHboxLayout;

    QGSettings  *m_pGsettingButtonData;

    QStringList m_listIconName;
    QStringList m_listIconPath;
    QStringList m_listEntryName;
    QStringList m_listGsettingKey;

    ButtonInfo  *m_pButtonInfoArray[13];
    QHash<QString, ButtonInfo*>  EntryData;

protected:
    void paintEvent(QPaintEvent *event);

private:
    void initMemberVariables();
    void initGsettingValue();
    void initListData();
    void initButtonInfoArrayData();
    void initListWidgetEntry();
    void initLayout();
    void insertButtonData(QString key, ButtonInfo *value);
    ButtonInfo* getButtonInfoData(QString key);

private slots:
    void resetDropDownWidget();
    void modifyButtonGsettingValue(QString key);
};

#endif // DROPDOWNBOX_H
