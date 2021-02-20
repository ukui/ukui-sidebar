#include "about.h"
#include "ui_about.h"
#include "utils/xatom-helper.h"

extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    setWindowTitle(tr("About"));
    //setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    //setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);

    // 添加窗管协议
    MotifWmHints hints;
    hints.flags = MWM_HINTS_FUNCTIONS|MWM_HINTS_DECORATIONS;
    hints.functions = MWM_FUNC_ALL;
    hints.decorations = MWM_DECOR_BORDER;
    XAtomHelper::getInstance()->setWindowMotifHint(this->winId(), hints);

    ui->iconLabel->setPixmap(QIcon::fromTheme("kylin-notebook").pixmap(24,24));
    ui->titleLabel->setText(tr("Kylin Memo"));
    ui->closeBtn->setIcon(QIcon::fromTheme("window-close-symbolic"));
    ui->closeBtn->setProperty("isWindowButton", 0x2);
    ui->closeBtn->setProperty("useIconHighlightEffect", 0x8);
    ui->closeBtn->setFlat(true);
    connect(ui->closeBtn, &QPushButton::clicked, this, [=](){
        this->close();
    });
    ui->appnameLabel->setStyleSheet("QLabel{font-size: 18px; color: palette(windowText);}"
                                    "QLabel{font-family: NotoSansCJKsc-Medium, NotoSansCJKsc;}");
    ui->versionLabel->setText(tr("Version: 2020.1.0"));
    ui->teamLabel->setText(tr("Service & Support: ") +
                           "<a href=\"mailto://support@kylinos.cn\""
                           "style=\"color: palette(buttonText)\">"
                           "support@kylinos.cn</a>");
    ui->appiconLabel->setPixmap(QIcon::fromTheme("kylin-notebook").pixmap(96,96));
    ui->appnameLabel->setText(tr("Kylin Memo"));
    ui->introduceLabel->setText(tr("Kylin Memo is a self-developed sidebar application plug-in, "
                                   "which provides a rich interface, convenient operation and stable functions, "
                                   "aiming at a friendly user experience."));
    ui->introduceLabel->setAlignment(Qt::AlignJustify);
    ui->introduceLabel->setWordWrap(true);
    connect(ui->teamLabel, &QLabel::linkActivated, this, [=](const QString url){
        QDesktopServices::openUrl(QUrl(url));
    });
    ui->teamLabel->setContextMenuPolicy(Qt::NoContextMenu);
}

About::~About()
{
    delete ui;
}

void About::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    QPainterPath rectPath;
    rectPath.addRect(this->rect());
    p.fillPath(rectPath,palette().color(QPalette::Base));
}
