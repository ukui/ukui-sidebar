#include "eyeprotectionmode.h"

eyeProtectionMode::eyeProtectionMode(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initGsettingValue();
    initLayout();
}

void eyeProtectionMode::initMemberVariables()
{
    m_pWidgetButton         = new QWidget();
    m_pWidgetButton->setFixedSize(56, 56);
    m_pWidgetButton->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout     = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);

    m_pLabelFotmatText = new LabelFotmatText;

    m_pEyeModeButton = new QPushButton();
    m_pEyeModeButton->setFixedSize(56, 56);
    m_pEyeModeButton->setIcon(QIcon::fromTheme(KYLIN_EYE_MODE_NORMAL_NAME, QIcon(KYLIN_EYE_MODE_NORMAL_PATH)));
    m_pEyeModeButton->setIconSize(QSize(24, 24));
    connect(m_pEyeModeButton, &switchButton::clicked, this, &eyeProtectionMode::EyeButtonClickSlots);

    m_pDeleteButton = new QPushButton();
    m_pDeleteButton->setFixedSize(20, 20);
    m_pDeleteButton->setIcon(QIcon(KYLIN_DELETE_ICONPATH));
    m_pDeleteButton->setIconSize(QSize(12, 12));

    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");
    m_pEyeModeButton->setStyle(m_pStyleNormal);

    m_pStyleOpen = new CustomStyle_SwitchOpenStatus("ukui-default");

    m_pEyeModeLabel = new QLabel();
    m_pEyeModeLabel->setFixedWidth(64);
    m_pEyeModeLabel->setText(m_pLabelFotmatText->SetFormatBody(QObject::tr("Eye care mode"), m_pEyeModeLabel));
    m_pEyeModeLabel->setAlignment(Qt::AlignHCenter);

    if (m_pLabelFotmatText->m_bTooltips) {
        this->setToolTip(QObject::tr("Eye care mode"));
    }

    m_pVboxLayout = new QVBoxLayout();
    m_pVboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxLayout->setSpacing(0);

    this->setFixedSize(63, 78);
    this->setContentsMargins(0, 0, 0, 0);
    return;
}

void eyeProtectionMode::initGsettingValue()
{
    // redshift的配置文件
    QString filename = QDir::homePath() +"/.config/redshift.conf";
    m_pqsettings = new QSettings(filename, QSettings::IniFormat);

    // 夜间模式的初始化
    const QByteArray id(NIGHT_MODE_CONTROL);
    if(QGSettings::isSchemaInstalled(id)) {
        m_pTabletModeGsetting = new QGSettings(id);
        if (m_pTabletModeGsetting->keys().contains(NIGHT_MODE_KEY)) {
            m_bModelStatus = m_pTabletModeGsetting->get(NIGHT_MODE_KEY).toBool();
            setEyeButtonStatus(m_bModelStatus);
        }
        else
            qDebug()<<"nightmodestatus is not exit";

        connect(m_pTabletModeGsetting, &QGSettings::changed, this, [=](const QString &key) {
            if (key==NIGHT_MODE_KEY) {
                setEyeButtonStatus(m_pTabletModeGsetting->get(NIGHT_MODE_KEY).toBool());
            }
        });

        // 系统主题gsettings  qt+gtk
        const QByteArray styleid(UKUI_QT_STYLE);
        if (QGSettings::isSchemaInstalled(styleid))
            m_pqtstyleGsettings = new QGSettings(styleid);

        const QByteArray gtkstyleid(GTK_STYLE);
        if (QGSettings::isSchemaInstalled(gtkstyleid))
            m_pgtkstyleGsettings = new QGSettings(gtkstyleid);
    } else {
        m_pEyeModeButton->setIcon(QIcon::fromTheme(KYLIN_EYE_MODE_OPEN_NAME, QIcon(KYLIN_EYE_MODE_OPEN_PATH)));
    }

    // init kwin settings
    setupSettings();
}

void eyeProtectionMode::initLayout()
{
    m_pVboxButtonLayout->addWidget(m_pEyeModeButton, 0, Qt::AlignCenter);
    m_pWidgetButton->setLayout(m_pVboxButtonLayout);
    m_pVboxLayout->addWidget(m_pWidgetButton, 0, Qt::AlignCenter);
    m_pVboxLayout->addItem(new QSpacerItem(15, 4));
    m_pVboxLayout->addWidget(m_pEyeModeLabel);
    this->setLayout(m_pVboxLayout);
    m_pDeleteButton->setParent(this);
    m_pDeleteButton->move(43, 0);
    m_pDeleteButton->setVisible(false);
    return;
}

/*
 * 设置夜间模式
 * tr: set NightMode
*/
void eyeProtectionMode::setEyeButtonStatus(const bool nightMode){
    QProcess process;
    QString cmd;
    QString serverCmd;

    if (nightMode) {
        /* 控制面板不是常驻应用，装机成功后未启动控制面板设置夜间模式的情况下
         * /.config/redshift.conf　未设置
         * 需要任务栏设置初始化夜间模式的时间及色温
         * 其他情况下任务栏应读取控制面板设置的参数
　　　　　*/
        m_pqsettings->beginGroup("redshift");
        if (m_pqsettings->value("temp-day", "").toString().isEmpty()) {
            m_pqsettings->setValue("dawn-time", "17:54");
            m_pqsettings->setValue("dusk-time", "17:55");
            m_pqsettings->setValue("temp-day", "3500");
            m_pqsettings->setValue("temp-night", "3500");
        } else {
            m_pqsettings->setValue("temp-day", m_pqsettings->value("temp-day", "").toString());
            m_pqsettings->setValue("temp-night", m_pqsettings->value("temp-night", "").toString());
        }
        m_pqsettings->endGroup();
        m_pqsettings->sync();

        cmd = "restart";
        serverCmd = "enable";
        m_pEyeModeButton->setStyle(m_pStyleOpen);
        m_pEyeModeButton->setIcon(QIcon::fromTheme(KYLIN_EYE_MODE_OPEN_NAME, QIcon(KYLIN_EYE_MODE_OPEN_PATH)));
    } else {
        cmd = "stop";
        serverCmd = "disable";
        m_pEyeModeButton->setStyle(m_pStyleNormal);
        m_pEyeModeButton->setIcon(QIcon::fromTheme(KYLIN_EYE_MODE_NORMAL_NAME, QIcon(KYLIN_EYE_MODE_NORMAL_PATH)));
    }
    m_bModelStatus = nightMode;
    setLabelTextColor();
    this->update();
    process.startDetached("systemctl", QStringList() << "--user" << serverCmd << "redshift.service");
    process.startDetached("systemctl", QStringList() << "--user" << cmd << "redshift.service");
}

/*设置主题*/
void eyeProtectionMode::setUkuiStyle(QString style)
{
    if (QString::compare(style,"ukui-white")==0) {
        if (m_pqtstyleGsettings->keys().contains(DEFAULT_QT_STYLE_NAME) || m_pqtstyleGsettings->keys().contains(UKUI_QT_STYLE_NAME))
            m_pqtstyleGsettings->set(UKUI_QT_STYLE_NAME,"ukui-white");
        else
            qWarning()<<tr("don't contains the keys style-name");

        if (m_pgtkstyleGsettings->keys().contains(DEFAULT_GTK_STYLE_NAME) || m_pgtkstyleGsettings->keys().contains(GTK_STYLE_NAME))
            m_pgtkstyleGsettings->set(GTK_STYLE_NAME,"ukui-white");
        else
            qWarning()<<tr("don't contains the keys style-name");

    } else {
        if (m_pqtstyleGsettings->keys().contains(DEFAULT_QT_STYLE_NAME) || m_pqtstyleGsettings->keys().contains(UKUI_QT_STYLE_NAME))
            m_pqtstyleGsettings->set(UKUI_QT_STYLE_NAME,"ukui-black");
        else
            qWarning()<<tr("don't contains the keys style-name");
        if (m_pgtkstyleGsettings->keys().contains(DEFAULT_GTK_STYLE_NAME) || m_pgtkstyleGsettings->keys().contains(GTK_STYLE_NAME))
            m_pgtkstyleGsettings->set(GTK_STYLE_NAME,"ukui-black");
        else
            qWarning()<<tr("don't contains the keys style-name");

    }
}

/* Kwin初始化　*/
void eyeProtectionMode::setupSettings()
{
    QString filename = QDir::homePath() + "/.config/kdeglobals";
    m_pKwinSettings = new QSettings(filename, QSettings::IniFormat);
}

/*设置与Kwin　窗口管理器　标题栏颜色*/
void eyeProtectionMode::writeKwinSettings(bool change, QString theme)
{
    QString th;
    if ("ukui-white" == theme)
        th = "0";
    else
        th = "1";
    m_pKwinSettings->beginGroup("Theme");
    m_pKwinSettings->setValue("Style", th);
    m_pKwinSettings->endGroup();
    m_pKwinSettings->sync();
}

QColor eyeProtectionMode::getSystemPaleteColor()
{
    QStyleOption opt;
    opt.init(m_pEyeModeLabel);
    if (m_bModelStatus) {
        return opt.palette.color(QPalette::Highlight);
    } else {
        return opt.palette.color(QPalette::Text);
    }
}

void eyeProtectionMode::setLabelTextColor()
{
    QPalette palette;
    QColor color = getSystemPaleteColor();
    palette.setBrush(QPalette::WindowText, color);
    m_pEyeModeLabel->setPalette(palette);
    this->update();
}

void eyeProtectionMode::EyeButtonClickSlots()
{
    if (QGSettings::isSchemaInstalled(NIGHT_MODE_CONTROL)) {
        if (!m_bModelStatus) {
            if (m_pTabletModeGsetting->keys().contains(NIGHT_MODE_KEY)) {
                setEyeButtonStatus(true);
                setUkuiStyle("ukui-black");
                writeKwinSettings(true,"ukui-black");
                m_bModelStatus = true;
            }
        } else {
            if (m_pTabletModeGsetting->keys().contains(NIGHT_MODE_KEY)) {
                setEyeButtonStatus(false);
                setUkuiStyle("ukui-white");
                writeKwinSettings(true,"ukui-white");
                m_bModelStatus = false;
            }
        }
        m_pTabletModeGsetting->set(NIGHT_MODE_KEY, m_bModelStatus);
        this->update();
    }
}

void eyeProtectionMode::paintEvent(QPaintEvent *e)
{
    QPalette palette;
    QColor color = getSystemPaleteColor();
    palette.setBrush(QPalette::WindowText, color);
    m_pEyeModeLabel->setPalette(palette);
    QWidget::paintEvent(e);
}
