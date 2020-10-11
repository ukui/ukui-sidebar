#include "btnNew.h"
#include <QVBoxLayout>
#include <QDebug>
#include "clock.h"
#include <QPainterPath>

Btn_new::Btn_new(int num, Clock *widget, QIcon icon, QString name, QWidget *parent) :
    QToolButton(parent),
    m_pclock(widget),
    clock_num(num)
{
    //this->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    QPixmap pixmap = icon.pixmap(QSize(16, 16));
    IconLabel = new QPushButton();
    IconLabel->setFixedSize(24, 24);
    IconLabel->setIcon(pixmap);
    textLabel = new QLabel();
    textLabel->setText(name);
    QHBoxLayout *ToolButtonLaout = new QHBoxLayout();
    ToolButtonLaout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    ToolButtonLaout->addWidget(IconLabel, 0, Qt::AlignCenter);
    ToolButtonLaout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));
    ToolButtonLaout->addWidget(textLabel, 0, Qt::AlignCenter);
    ToolButtonLaout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    ToolButtonLaout->setContentsMargins(0,0,0,0);
    this->setLayout(ToolButtonLaout);

    IconLabel->setProperty("useIconHighlightEffect", true);
    IconLabel->setProperty("iconHighlightEffectMode", 1);


    QPalette palette = IconLabel->palette();
    QColor ColorPlaceholderText(61,107,229,255);
    QBrush brush2;
    brush2.setColor(ColorPlaceholderText);
    palette.setColor(QPalette::Button,QColor(61,107,229,255));
    palette.setBrush(QPalette::ButtonText, QBrush(Qt::white));
    IconLabel->setPalette(palette);


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
