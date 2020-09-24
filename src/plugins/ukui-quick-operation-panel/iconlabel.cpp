#include "iconlabel.h"

IconLabel::IconLabel(QWidget *parent) : QLabel(parent)
{

}

void IconLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    emit LabelClicked();
}
