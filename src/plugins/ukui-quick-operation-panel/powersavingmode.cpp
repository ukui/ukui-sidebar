#include "powersavingmode.h"

powerSavingMode::powerSavingMode(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initGsettingValue();
    initButtonStatus();
    initLayout();
}

void powerSavingMode::initMemberVariables()
{
    m_pWidgetButton         = new QWidget();
    m_pWidgetButton->setFixedSize(56, 56);
    m_pWidgetButton->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout     = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);

    m_pLabelFotmatText = new LabelFotmatText;

    m_pPowerModeButton = new QPushButton();
    m_pPowerModeButton->setFixedSize(56, 56);
    m_pPowerModeButton->setIconSize(QSize(24, 24));
    connect(m_pPowerModeButton, &switchButton::clicked, this, &powerSavingMode::PowerSavingButtonClickSlots);

    m_pDeleteButton = new QPushButton();
    m_pDeleteButton->setFixedSize(20, 20);
    m_pDeleteButton->setIcon(QIcon(KYLIN_DELETE_ICONPATH));
    m_pDeleteButton->setIconSize(QSize(12, 12));

    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");
    m_pPowerModeButton->setStyle(m_pStyleNormal);

    m_pStyleOpen = new CustomStyle_SwitchOpenStatus("ukui-default");

    m_pPowerModeLabel = new QLabel();
    m_pPowerModeLabel->setFixedWidth(64);
    m_pPowerModeLabel->setText(m_pLabelFotmatText->SetFormatBody(QObject::tr("Energy-saving mode"), m_pPowerModeLabel));
    m_pPowerModeLabel->setAlignment(Qt::AlignHCenter);

    if (m_pLabelFotmatText->m_bTooltips) {
        this->setToolTip(QObject::tr("Energy-saving mode"));
    }

    m_pVboxLayout = new QVBoxLayout();
    m_pVboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxLayout->setSpacing(0);

    this->setFixedSize(63, 78);
    this->setContentsMargins(0, 0, 0, 0);
    return;
}

void powerSavingMode::initGsettingValue()
{
    /* 链接电源节能模式gsetting连接 */
    const QByteArray id(KYLIN_POWER_MODE_GSETTING_VALUE);
    if (QGSettings::isSchemaInstalled(id))
        m_pSavingModeGsetting = new QGSettings(id);

    /* 用于记录当前节能模式开关状态 */
    const QByteArray id_2(UKUI_VOLUME_BRIGHTNESS_GSETTING_ID);
    if (QGSettings::isSchemaInstalled(id_2))
        m_pSavingModeButtonStatusGsetting = new QGSettings(id_2);
    return;
}

void powerSavingMode::initButtonStatus()
{
    m_bModelStatus = m_pSavingModeButtonStatusGsetting->get(UKUI_ENERGY_SAVING_MODE_KEY).toBool();
    if (m_bModelStatus) {
        m_pPowerModeButton->setStyle(m_pStyleOpen);
        m_pPowerModeButton->setIcon(QIcon::fromTheme(KYLIN_POWER_SAVING_OPEN_NAME, QIcon(KYLIN_POWER_SAVING_OPEN_PATH)));
    } else {
        m_pPowerModeButton->setStyle(m_pStyleNormal);
        m_pPowerModeButton->setIcon(QIcon::fromTheme(KYLIN_POWER_SAVING_NORMAL_NAME, QIcon(KYLIN_POWER_SAVING_NORMAL_PATH)));
    }
    m_pPowerModeButton->update();
    setLabelTextColor();
}

void powerSavingMode::initLayout()
{
    m_pVboxButtonLayout->addWidget(m_pPowerModeButton, 0, Qt::AlignCenter);
    m_pWidgetButton->setLayout(m_pVboxButtonLayout);
    m_pVboxLayout->addWidget(m_pWidgetButton, 0, Qt::AlignCenter);
    m_pVboxLayout->addItem(new QSpacerItem(15, 4));
    m_pVboxLayout->addWidget(m_pPowerModeLabel);
    this->setLayout(m_pVboxLayout);
    m_pDeleteButton->setParent(this);
    m_pDeleteButton->move(43, 0);
    m_pDeleteButton->setVisible(false);
    return;
}

QColor powerSavingMode::getSystemPaleteColor()
{
    QStyleOption opt;
    opt.init(m_pPowerModeLabel);
    if (m_bModelStatus) {
        return opt.palette.color(QPalette::Highlight);
    } else {
        return opt.palette.color(QPalette::Text);
    }
}

void powerSavingMode::setLabelTextColor()
{
    QPalette palette;
    QColor color = getSystemPaleteColor();
    palette.setBrush(QPalette::WindowText, color);
    m_pPowerModeLabel->setPalette(palette);
    this->update();
}

void powerSavingMode::PowerSavingButtonClickSlots()
{
    m_bModelStatus = m_pSavingModeButtonStatusGsetting->get(UKUI_ENERGY_SAVING_MODE_KEY).toBool();
    if (!m_bModelStatus) {
        m_pPowerModeButton->setStyle(m_pStyleOpen);
        m_pPowerModeButton->setIcon(QIcon::fromTheme(KYLIN_POWER_SAVING_OPEN_NAME, QIcon(KYLIN_POWER_SAVING_OPEN_PATH)));
        m_pSavingModeGsetting->set(KYLIN_POWER_SREEN_BRIGHTNESS_AC_KEY, 20);
        m_pSavingModeGsetting->set(KYLIN_POWER_SLEEP_DISPLAY_AC_KEY, 60);
        m_pSavingModeGsetting->set(KYLIN_POWER_SLEEP_BATTERY_KEY, 60);
        m_bModelStatus = true;
    } else {
        m_pPowerModeButton->setStyle(m_pStyleNormal);
        m_pPowerModeButton->setIcon(QIcon::fromTheme(KYLIN_POWER_SAVING_NORMAL_NAME, QIcon(KYLIN_POWER_SAVING_NORMAL_PATH)));
        m_pSavingModeGsetting->set(KYLIN_POWER_SREEN_BRIGHTNESS_AC_KEY, 66);
        m_pSavingModeGsetting->set(KYLIN_POWER_SLEEP_DISPLAY_AC_KEY, 600);
        m_pSavingModeGsetting->set(KYLIN_POWER_SLEEP_BATTERY_KEY, 600);
        m_bModelStatus = false;
    }
    m_pSavingModeButtonStatusGsetting->set(UKUI_ENERGY_SAVING_MODE_KEY, m_bModelStatus);
    m_pPowerModeButton->update();
    setLabelTextColor();
}
