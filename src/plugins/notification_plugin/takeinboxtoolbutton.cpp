#include "takeinboxtoolbutton.h"
#include <QToolTip>
#include <QHelpEvent>

TakeInBoxToolButton::TakeInBoxToolButton()
{
    m_bEnterTakeInBox = false;
}

void TakeInBoxToolButton::enterEvent(QEvent *event)
{
    QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
    if(false == m_bEnterTakeInBox)
    {
        QToolTip::showText(QPoint(helpEvent->pos().x(), (helpEvent->pos().y() + 30)), "进入收纳盒");
//        QToolTip::showText(helpEvent->globalPos(), "进入收纳盒");
    }
    else
    {
        QToolTip::showText(QPoint(helpEvent->pos().x(), (helpEvent->pos().y() + 30)), "退出收纳盒");
//        QToolTip::showText(helpEvent->globalPos(), "退出收纳盒");
    }
    return;
}

void TakeInBoxToolButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    QToolTip::hideText();
    return;
}
