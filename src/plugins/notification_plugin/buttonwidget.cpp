#include "buttonwidget.h"
#include "singlemsg.h"
#include <QMouseEvent>
#include <QSvgRenderer>
#include <QPixmap>
#include <QPainter>
#include <QVBoxLayout>
#include <QSvgWidget>
#include <QDebug>

ButtonWidget::ButtonWidget(QString strIcon, QString strHoverIcon)
{
    m_strIcon = strIcon;
    m_strHoverIcon = strHoverIcon;

    this->setFixedWidth(24);
    this->setFixedHeight(24);
    this->setStyleSheet("border:none;border-style:none;padding:0px;background:transparent;width:24px;height:24px;");

    QVBoxLayout* pVBoxLayout = new QVBoxLayout;
    pVBoxLayout->setContentsMargins(0,0,0,0);
    pVBoxLayout->setSpacing(0);

    m_ToolButton = new QLabel;
    m_pTakeinSvgRender = new QSvgRenderer(m_ToolButton);
    m_pTakeinSvgRender->load(m_strIcon);
    m_pTakeinPixmap = new QPixmap(13, 13);
    m_pTakeinPixmap80percent = new QPixmap(11, 11);
    m_pTakeinPixmap->fill(Qt::transparent);
    QPainter takeinPainter(m_pTakeinPixmap);
    m_pTakeinSvgRender->render(&takeinPainter);
    m_ToolButton->setPixmap(*m_pTakeinPixmap);

    pVBoxLayout->addWidget(m_ToolButton, 0, Qt::AlignHCenter | Qt::AlignVCenter);
    this->setLayout(pVBoxLayout);

    return;
}

void ButtonWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_pTakeinSvgRender->load(m_strHoverIcon);
    m_pTakeinPixmap->fill(Qt::transparent);
    QPainter takeinPainter(m_pTakeinPixmap);
    m_pTakeinSvgRender->render(&takeinPainter);
    m_ToolButton->setPixmap(*m_pTakeinPixmap);

    return;
}

void ButtonWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_pTakeinSvgRender->load(m_strIcon);
    m_pTakeinPixmap->fill(Qt::transparent);
    QPainter takeinPainter(m_pTakeinPixmap);
    m_pTakeinSvgRender->render(&takeinPainter);
    m_ToolButton->setPixmap(*m_pTakeinPixmap);

    return;
}

//鼠标点击事件
void ButtonWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        m_pTakeinSvgRender->load(m_strIcon);
        m_pTakeinPixmap80percent->fill(Qt::transparent);
        QPainter takeinPainter(m_pTakeinPixmap80percent);
        m_pTakeinSvgRender->render(&takeinPainter);
        m_ToolButton->setPixmap(*m_pTakeinPixmap80percent);
    }

    return;
}

void ButtonWidget::mouseReleaseEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    qDebug()<<"ButtonWidget::mouseReleaseEvent" <<x << y;

    //假如在QRect(0, 0, 24, 24));这个区域里，就发出信号
    if (x >= 0 && x <= 24 && y >= 0 && y<=24)
    {
        emit Sig_clicked();
    }

    return;
}
