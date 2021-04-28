#include "closeOrHide.h"
#include "ui_closeOrHide.h"
#include "QDebug"
#include <X11/Xlib.h>
#include "xatom-helper.h"

extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);

close_or_hide::close_or_hide(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::close_or_hide)
{
    ui->setupUi(this);
//    this->setProperty("blurRegion", QRegion(QRect(1, 1, 1, 1)));
//    setAttribute(Qt::WA_TranslucentBackground);
//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    ui->radioButton_2->setChecked(1);

    // 添加窗管协议
    MotifWmHints hints;
    hints.flags = MWM_HINTS_FUNCTIONS|MWM_HINTS_DECORATIONS;
    hints.functions = MWM_FUNC_ALL;
    hints.decorations = MWM_DECOR_BORDER;
    XAtomHelper::getInstance()->setWindowMotifHint(this->winId(), hints);

    ui->label->setText(tr("Please select the state after closing:"));

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
    ui->closebtn->setProperty("isWindowButton", 0x2);
    ui->closebtn->setProperty("useIconHighlightEffect", 0x8);
    ui->closebtn->setFlat(true);
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
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    QPainterPath rectPath;
    rectPath.addRect(this->rect());
    p.fillPath(rectPath,palette().color(QPalette::Base));
}

void close_or_hide::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->dragPosition = event->globalPos() - frameGeometry().topLeft();
        this->mousePressed = true;
    }
    QWidget::mousePressEvent(event);
}

void close_or_hide::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->mousePressed = false;
        this->setCursor(Qt::ArrowCursor);
    }

    QWidget::mouseReleaseEvent(event);
}

void close_or_hide::mouseMoveEvent(QMouseEvent *event)
{
    if (this->mousePressed) {
        move(event->globalPos() - this->dragPosition);
        this->setCursor(Qt::ClosedHandCursor);
    }

    QWidget::mouseMoveEvent(event);
}
