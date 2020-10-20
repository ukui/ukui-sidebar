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
    nameLabel->setFixedSize(71, 36);
    textLabel->setFixedSize(171, 36);
    IconLabel->setFixedSize(27, 36);
    noName->setFixedSize(9, 36);
    nameLabel->move(0, 0);
    textLabel->move(71, 0);
    noName->move(244, 0);
    IconLabel->move(253, 0);
    nameLabel->setText(name);
    textLabel->setText(name);
    IconLabel->setPixmap(pixmap);
    textLabel->setAlignment(Qt::AlignRight | Qt::AlignCenter);

    this->resize(280,36);

    QPalette palette;
    palette.setColor(QPalette::ButtonText,QColor(148, 148, 148, 255));
    textLabel->setPalette(palette);
}

Btn_new::~Btn_new()
{

}
