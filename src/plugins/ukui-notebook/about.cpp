#include "about.h"
#include "ui_about.h"
#include "utils/xatom-helper.h"

#include <QGSettings>

#define UKUI_STYLE_SCHEMA          "org.ukui.style"
#define STYLE_NAME                 "styleName"
#define STYLE_NAME_KEY_DARK        "ukui-dark"
#define STYLE_NAME_KEY_DEFAULT     "ukui-default"
#define STYLE_NAME_KEY_BLACK       "ukui-black"
#define STYLE_NAME_KEY_LIGHT       "ukui-light"
#define STYLE_NAME_KEY_WHITE       "ukui-white"

#define SYSTEM_FONT_EKY            "system-font-size"
#define SYSTEM_NAME_KEY            "system-font"
#define STYLE_ICON                "icon-theme-name"
#define STYLE_ICON_NAME           "iconThemeName"

extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    setWindowTitle(tr("About"));
    // setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    // setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);

    // 添加窗管协议
    MotifWmHints hints;
    hints.flags = MWM_HINTS_FUNCTIONS|MWM_HINTS_DECORATIONS;
    hints.functions = MWM_FUNC_ALL;
    hints.decorations = MWM_DECOR_BORDER;
    XAtomHelper::getInstance()->setWindowMotifHint(this->winId(), hints);

    ui->iconLabel->setPixmap(QIcon::fromTheme("kylin-notebook").pixmap(24, 24));
    ui->titleLabel->setText(tr("Notes"));
    ui->closeBtn->setIcon(QIcon::fromTheme("window-close-symbolic"));
    ui->closeBtn->setProperty("isWindowButton", 0x2);
    ui->closeBtn->setProperty("useIconHighlightEffect", 0x8);
    ui->closeBtn->setFlat(true);

    connect(ui->closeBtn, &QPushButton::clicked, this, [=](){
        this->close();
    });

    ui->versionLabel->setText(tr("Version: 2020.1.0"));
// ui->teamLabel->setText(tr("Service & Support: ") +
// "<a href=\"mailto://support@kylinos.cn\""
// "style=\"color: palette(buttonText)\">"
// "support@kylinos.cn</a>");
    ui->appiconLabel->setPixmap(QIcon::fromTheme("kylin-notebook").pixmap(96, 96));
    ui->appnameLabel->setText(tr("Notes"));
    ui->introduceLabel->setText(tr("Notes is a self-developed sidebar application plug-in, "
                                   "which provides a rich interface, convenient operation and stable functions, "
                                   "aiming at a friendly user experience."));
    ui->introduceLabel->setAlignment(Qt::AlignJustify);
    ui->introduceLabel->setWordWrap(true);
    connect(ui->teamLabel, &QLabel::linkActivated, this, [=](const QString url){
        QDesktopServices::openUrl(QUrl(url));
    });
    ui->teamLabel->setContextMenuPolicy(Qt::NoContextMenu);

    listenToGsettings();
}

About::~About()
{
    delete ui;
}

void About::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    QPainterPath rectPath;
    rectPath.addRect(this->rect());
    p.fillPath(rectPath, palette().color(QPalette::Base));
}

void About::listenToGsettings()
{
    const QByteArray styleID(UKUI_STYLE_SCHEMA);
    QStringList stylelist;

    if (QGSettings::isSchemaInstalled(styleID)) {
        QGSettings *styleUKUI = new QGSettings(styleID, QByteArray(), this);

        stylelist << STYLE_NAME_KEY_DARK << STYLE_NAME_KEY_BLACK; // <<STYLE_NAME_KEY_DEFAULT;

        if (stylelist.contains(styleUKUI->get(STYLE_NAME).toString())) {
            ui->teamLabel->setText(tr("Service & Support: ")
                                   +"<a href=\"mailto://support@kylinos.cn\""
                                    "style=\"color:white\">"
                                    "support@kylinos.cn</a>");
        } else {
            ui->teamLabel->setText(tr("Service & Support: ")
                                   +"<a href=\"mailto://support@kylinos.cn\""
                                    "style=\"color:black\">"
                                    "support@kylinos.cn</a>");
        }

        connect(styleUKUI, &QGSettings::changed, this, [=](const QString &key){
            if (key == STYLE_NAME) {
                if (stylelist.contains(styleUKUI->get(STYLE_NAME).toString())) {
                    ui->teamLabel->setText(tr("Service & Support: ")
                                           +"<a href=\"mailto://support@kylinos.cn\""
                                            "style=\"color:white\">"
                                            "support@kylinos.cn</a>");
                } else {
                    ui->teamLabel->setText(tr("Service & Support: ")
                                           +"<a href=\"mailto://support@kylinos.cn\""
                                            "style=\"color:black\">"
                                            "support@kylinos.cn</a>");
                }
            }
            if(key==STYLE_ICON_NAME || key==STYLE_ICON){
                        //主题框架不能更新 titleIcon
                        ui->iconLabel->setPixmap(QIcon::fromTheme("kylin-notebook").pixmap(24,24));
                        ui->appiconLabel->setPixmap(QIcon::fromTheme("kylin-notebook").pixmap(96,96));
                    }
        });

        if (styleUKUI->get(SYSTEM_FONT_EKY).toInt()) {
            const int size = styleUKUI->get(SYSTEM_FONT_EKY).toInt();
            QFont dateFont;
            dateFont.setPointSize(size * 1.3);
            ui->appnameLabel->setFont(dateFont);
        }

        connect(styleUKUI, &QGSettings::changed, this, [=](const QString &key){
            if (key == "systemFontSize") {
                const int size = styleUKUI->get(SYSTEM_FONT_EKY).toInt();
                QFont dateFont;
                dateFont.setPointSize(size * 1.3);
                ui->appnameLabel->setFont(dateFont);
            }
        });
    }
}
