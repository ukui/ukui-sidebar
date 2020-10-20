#include "closeOrHide.h"
#include "ui_closeOrHide.h"
#include "QDebug"

extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);

close_or_hide::close_or_hide(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::close_or_hide)
{
    ui->setupUi(this);
    this->setProperty("blurRegion", QRegion(QRect(1, 1, 1, 1)));
    setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    ui->radioButton_2->setChecked(1);

    QPalette palette = ui->surebtn->palette();
    QColor ColorPlaceholderText(61,107,229,255);
    QBrush brush2;
    brush2.setColor(ColorPlaceholderText);
    palette.setColor(QPalette::Button,QColor(61,107,229,255));
    palette.setBrush(QPalette::ButtonText, QBrush(Qt::white));
    ui->surebtn->setPalette(palette);

    QPalette palette1 = ui->closebtn->palette();
    QColor ColorPlaceholderText1(255,255,255,0);
    QBrush brush;
    brush.setColor(ColorPlaceholderText1);
    palette.setBrush(QPalette::Button, brush);
    ui->closebtn->setPalette(palette1);

    ui->closebtn->setIcon(QIcon::fromTheme("window-close-symbolic"));
    ui->closebtn->setFlat(true);
    ui->closebtn->setVisible(true);
    ui->closebtn->setFocusPolicy(Qt::NoFocus);
    ui->closebtn->setProperty("useIconHighlightEffect", true);
    ui->closebtn->setProperty("iconHighlightEffectMode", true);
}

close_or_hide::~close_or_hide()
{
    delete ui;
}

void close_or_hide::on_closebtn_clicked()
{
    this->hide();
    close_flag = 0;
}

void close_or_hide::on_surebtn_clicked()
{
    if(ui->radioButton_2->isChecked()==true){
        this->hide();
         close_flag = 1;
    }else{
        this->hide();
        close_flag = 2;
    }
}

void close_or_hide::on_cancelbtn_clicked()
{
    this->hide();
}

void close_or_hide::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;

    QStyleOption opt;
    opt.init(this);
    painter.setBrush(opt.palette.color(QPalette::Base));

    painter.setPen(Qt::transparent);
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 0);
    rect.setHeight(rect.height() - 0);
    painter.drawRoundedRect(rect, 7, 7);
    {
        QPainterPath painterPath;
        painterPath.addRoundedRect(rect, 7, 7);
        painter.drawPath(painterPath);
    }

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    QPainterPath rectPath;
    rectPath.addRoundedRect(this->rect().adjusted(2, 2, -2, -2), 6, 6);

    // 画一个黑底
    QPixmap pixmap(this->rect().size());
    pixmap.fill(Qt::transparent);
    QPainter pixmapPainter(&pixmap);
    pixmapPainter.setRenderHint(QPainter::Antialiasing);
    pixmapPainter.setPen(Qt::transparent);
    pixmapPainter.setBrush(Qt::gray);
    pixmapPainter.drawPath(rectPath);
    pixmapPainter.end();

    // 模糊这个黑底
    QImage img = pixmap.toImage();
    qt_blurImage(img, 10, false, false);

    // 挖掉中心
    pixmap = QPixmap::fromImage(img);
    QPainter pixmapPainter2(&pixmap);
    pixmapPainter2.setRenderHint(QPainter::Antialiasing);
    pixmapPainter2.setCompositionMode(QPainter::CompositionMode_Clear);
    pixmapPainter2.setPen(Qt::transparent);
    pixmapPainter2.setBrush(QColor(78,78,78));
    pixmapPainter2.drawPath(rectPath);

    // 绘制阴影
    p.drawPixmap(this->rect(), pixmap, pixmap.rect());
    p.setOpacity(0.9);
    // 绘制一个背景
    p.save();
    p.fillPath(rectPath,palette().color(QPalette::Base));
    p.restore();
}
