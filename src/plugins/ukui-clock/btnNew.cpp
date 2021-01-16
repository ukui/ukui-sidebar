#include "btnNew.h"
#include <QVBoxLayout>
#include <QDebug>
#include "clock.h"
#include <QPainterPath>

Btn_new::Btn_new(int num, QString name, QWidget *parent) :
    QPushButton(parent),
    clock_num(num)
{
    QPixmap pixmap = QPixmap(":/go-bottom-symbolic.png");
    nameLabel = new QLabel(this);
    textLabel = new QLabel(this);
    IconLabel = new QLabel(this);
    noName = new QLabel(this);
    nameLabel->setFixedSize(71-num, 36);
    textLabel->setFixedSize(233+num, 36);
    IconLabel->setFixedSize(27, 36);
    noName->setFixedSize(9, 36);
    nameLabel->move(15, 5);
    textLabel->move(71-num, 5);
    noName->move(244, 0);
    IconLabel->move(309, 6);
    nameLabel->setText(name);
    textLabel->setText(name);
    IconLabel->setPixmap(pixmap);
    textLabel->setAlignment(Qt::AlignRight | Qt::AlignCenter);
    nameLabel->setStyleSheet("font-size:14px;");
    textLabel->setStyleSheet("font-size:14px;");
    this->resize(340,48);

    QPalette palette;
    palette.setColor(QPalette::ButtonText,QColor(148, 148, 148, 255));
    textLabel->setPalette(palette);

    IconLabel->setProperty("useIconHighlightEffect", true);
    IconLabel->setProperty("iconHighlightEffectMode", 1);
}

Btn_new::~Btn_new()
{

}

void Btn_new::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    QPainterPath rectPath;
    rectPath.addRoundedRect(this->rect(), 10, 10); // 左上右下

    QPainter painter(this);
    QStyleOption opt;
    opt.init(this);
    painter.setBrush(opt.palette.color(QPalette::Base));

    QColor mainColor;
    if(QColor(255,255,255) == opt.palette.color(QPalette::Base) || QColor(248,248,248) == opt.palette.color(QPalette::Base))
    {
        mainColor = QColor(255, 255, 255,107.1);
    }else{
        mainColor = QColor(255, 255, 255,40.8);
    }

    p.fillPath(rectPath,QBrush(mainColor));
}
