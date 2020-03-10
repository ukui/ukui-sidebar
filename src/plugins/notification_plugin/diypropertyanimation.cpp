#include "diypropertyanimation.h"
#include <QVariant>
#include <QRect>

DiyPropertyAnimation::DiyPropertyAnimation(QObject *target, const QByteArray &propertyName, QObject *parent) : QPropertyAnimation(target, propertyName, parent)
{

}

void DiyPropertyAnimation::updateCurrentValue(const QVariant &value)
{
    QRect rect = value.value<QRect>();
    int x1, y1, x2, y2;
    rect.getRect(&x1, &y1, &x2, &y2);

    emit Sig_currentRect(x1, y1, x2, y2);
    return;
}
