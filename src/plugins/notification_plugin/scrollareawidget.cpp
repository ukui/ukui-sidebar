#include "scrollareawidget.h"
#include <QDebug>


ScrollBarWidget::ScrollBarWidget()
{
    setStyleSheet("QScrollBar:vertical{width: 5;}");
//    setFixedHeight(100);
    return;
}

void ScrollBarWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    setStyleSheet("QScrollBar:vertical{width: 10;}");
    return;
}

void ScrollBarWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    setStyleSheet("QScrollBar:vertical{width: 5;}");
    return;
}

ScrollAreaWidget::ScrollAreaWidget()
{
    setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    setWidgetResizable(true);
    ScrollBarWidget *pScrollbar = new ScrollBarWidget;
    setVerticalScrollBar(pScrollbar);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //隐藏横向滚动条
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //隐藏纵向滚动条
}

void ScrollAreaWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); //隐藏纵向滚动条
    return;
}

void ScrollAreaWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //隐藏纵向滚动条
    return;
}
