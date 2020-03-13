#include "realtimepropertyanimation.h"
#include <QVariant>
#include <QRect>

RealtimePropertyAnimation::RealtimePropertyAnimation(QObject *target, const QByteArray &propertyName, QObject *parent) : QPropertyAnimation(target, propertyName, parent)
{

}

void RealtimePropertyAnimation::updateCurrentValue(const QVariant &value)
{
    QRect rect = value.value<QRect>();
    int x1, y1, x2, y2;
    rect.getRect(&x1, &y1, &x2, &y2);

    emit Sig_currentRect(x1, y1, x2, y2);
    return;
}
