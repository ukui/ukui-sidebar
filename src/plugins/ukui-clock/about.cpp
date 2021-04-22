#include "about.h"
#include "ui_about.h"
#include <X11/Xlib.h>
#include "xatom-helper.h"

extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    // 添加窗管协议
    MotifWmHints hints;
    hints.flags = MWM_HINTS_FUNCTIONS|MWM_HINTS_DECORATIONS;
    hints.functions = MWM_FUNC_ALL;
    hints.decorations = MWM_DECOR_BORDER;
    XAtomHelper::getInstance()->setWindowMotifHint(this->winId(), hints);

    setWindowTitle(tr("About"));
    //setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    //setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);

    this->setWindowIcon(QIcon::fromTheme("kylin-alarm-clock",QIcon(":/image/kylin-alarm-clock.svg")));
    ui->titleIcon->setPixmap(QIcon::fromTheme("kylin-alarm-clock").pixmap(24,24));

    ui->closeBtn->setIcon(QIcon::fromTheme("window-close-symbolic"));
    ui->closeBtn->setProperty("isWindowButton", 0x2);
    ui->closeBtn->setProperty("useIconHighlightEffect", 0x8);
    ui->closeBtn->setFlat(true);
    connect(ui->closeBtn, &QPushButton::clicked, this, [=](){
        this->close();
    });
    ui->appnameLabel->setStyleSheet("QLabel{font-size: 18px; color: palette(windowText);}"
                                    "QLabel{font-family: NotoSansCJKsc-Medium, NotoSansCJKsc;}");
    ui->versionLabel->setText(tr("Version: ")+"2021.2.0");
    settingsStyle();
    ui->appiconLabel->setPixmap(QIcon::fromTheme("kylin-alarm-clock").pixmap(96,96));
    connect(ui->introduceLabel, &QLabel::linkActivated, this, [=](const QString url){
         QDesktopServices::openUrl(QUrl(url));
     });
    ui->introduceLabel->setContextMenuPolicy(Qt::NoContextMenu);
}

About::~About()
{
    delete ui;
}

/*
*监听主题
*/
void About::settingsStyle()
{
    const QByteArray style_id(ORG_UKUI_STYLE);
    QStringList stylelist;
    QGSettings *style_settings = new QGSettings(style_id);

    stylelist<<STYLE_NAME_KEY_DARK<<STYLE_NAME_KEY_BLACK; //<<STYLE_NAME_KEY_DEFAULT;
    if(QGSettings::isSchemaInstalled(style_id)){
        style_settings = new QGSettings(style_id);
        if(stylelist.contains(style_settings->get(STYLE_NAME).toString())){
            blackStyle();
        }else{
            whiteStyle();
        }
    }

    connect(style_settings, &QGSettings::changed, this, [=] (const QString &key){
        if(key==STYLE_NAME){
            if(stylelist.contains(style_settings->get(STYLE_NAME).toString())){
                blackStyle();
            }else{
                whiteStyle();
            }
        }
    });
}

void About::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    QPainterPath rectPath;
    rectPath.addRect(this->rect());
    p.fillPath(rectPath,palette().color(QPalette::Base));
}

//黑色主题
void About::blackStyle()
{
    ui->introduceLabel->setText(tr("Service & Support: ") +
                                "<a href=\"mailto://support@kylinos.cn\""
                                "style=\"color:white\">"
                                "support@kylinos.cn</a>");
}
//白色主题
void About::whiteStyle()
{
    ui->introduceLabel->setText(tr("Service & Support: ") +
                                "<a href=\"mailto://support@kylinos.cn\""
                                "style=\"color:black\">"
                                "support@kylinos.cn</a>");
}
