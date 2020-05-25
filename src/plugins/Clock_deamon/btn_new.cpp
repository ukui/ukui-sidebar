#include "btn_new.h"
#include <QVBoxLayout>
#include <QDebug>
#include "clock.h"

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
    IconLabel->setStyleSheet("background: rgba(39,207,129,0.9)");
    textLabel = new QLabel();
    textLabel->setText(name);
    textLabel->setStyleSheet("background: rgba(39,207,129,0.9)");
    QVBoxLayout *ToolButtonLaout = new QVBoxLayout();
    ToolButtonLaout->setContentsMargins(0, 0, 0, 0);
    ToolButtonLaout->addItem(new QSpacerItem(10, 11, QSizePolicy::Expanding));
    ToolButtonLaout->addWidget(IconLabel, 0, Qt::AlignCenter);
    ToolButtonLaout->addItem(new QSpacerItem(10, 6, QSizePolicy::Expanding));
    ToolButtonLaout->addWidget(textLabel, 0, Qt::AlignCenter);
    ToolButtonLaout->addSpacerItem(new QSpacerItem(10, 7));
    this->setLayout(ToolButtonLaout);
    this->setStyleSheet("background: rgba(39,207,129,0); border-radius:4px;");
    IconLabel->hide();
    textLabel->hide();
}

Btn_new::~Btn_new()
{

}

void Btn_new::enterEvent(QEvent *event)
{
    this->setStyleSheet("background: rgba(39,207,129,1);border-radius:4px;");
    textLabel->setStyleSheet("background: rgba(39,207,129,1)");
    IconLabel->setStyleSheet("background: rgba(39,207,129,1)");
    IconLabel->show();
    textLabel->show();
}

void Btn_new::mousePressEvent(QMouseEvent *event)
{
    this->setStyleSheet("background:rgba(27, 143, 89,1) ;border-radius:4px;");
    textLabel->setStyleSheet("background: rgba(27, 143, 89,1)");
    IconLabel->setStyleSheet("background: rgba(27, 143, 89,1)");
}

void Btn_new::mouseReleaseEvent(QMouseEvent *event)
{
    this->setStyleSheet("background: rgba(39,207,129,1) ;border-radius:4px;");
    textLabel->setStyleSheet("background: rgba(39,207,129,1)");
    IconLabel->setStyleSheet("background: rgba(39,207,129,1)");
    if(clock_num == 1){
        m_pclock->on_pushButton_clicked();
    }else if(clock_num == 2){
        m_pclock->on_pushButton_2_clicked();
    }else{
        m_pclock->on_pushButton_3_clicked();
    }

}

void Btn_new::leaveEvent(QEvent *event)
{
    this->setStyleSheet("background: rgba(39,207,129,0) ;border-radius:4px;");
    IconLabel->hide();
    textLabel->hide();
}
