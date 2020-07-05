#include "btn_new.h"
#include <QVBoxLayout>
#include <QDebug>
#include "clock.h"
#include <QPainterPath>

Btn_new::Btn_new(int num, Clock *widget, QIcon icon, QString name, QWidget *parent) :
    QToolButton(parent),
    m_pclock(widget),
    clock_num(num)
{
    this->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QPixmap pixmap = icon.pixmap(QSize(16, 16));
    IconLabel = new QLabel();
    IconLabel->setFixedSize(16, 16);
    IconLabel->setPixmap(pixmap);
    IconLabel->setStyleSheet("background: rgba()");
    textLabel = new QLabel();
    textLabel->setText(name);
    textLabel->setStyleSheet("background: rgba()");
    QVBoxLayout *ToolButtonLaout = new QVBoxLayout();
    ToolButtonLaout->setContentsMargins(0, 0, 0, 0);
    ToolButtonLaout->addItem(new QSpacerItem(10, 11, QSizePolicy::Expanding));
    ToolButtonLaout->addWidget(IconLabel, 0, Qt::AlignCenter);
    ToolButtonLaout->addItem(new QSpacerItem(10, 6, QSizePolicy::Expanding));
    ToolButtonLaout->addWidget(textLabel, 0, Qt::AlignCenter);
    ToolButtonLaout->addSpacerItem(new QSpacerItem(10, 7));
    this->setLayout(ToolButtonLaout);
}

Btn_new::~Btn_new()
{

}

void Btn_new::mouseReleaseEvent(QMouseEvent *event)
{
    if(clock_num == 1){
        m_pclock->on_pushButton_clicked();
    }else if(clock_num == 2){
        m_pclock->on_pushButton_2_clicked();
    }else{
        m_pclock->on_pushButton_3_clicked();
    }
}


