#include "singleitemButton.h"

singleitemButton::singleitemButton()
{
    installEventFilter(this);
    QIcon pushdelIcon;
    this->setFixedSize(34,34);
    this->setIconSize(QSize(16,16));
    pushdelIcon.addFile(":/new/prefix1/SVG/delete-b.svg");
    this->setIcon(pushdelIcon);

}

singleitemButton::~singleitemButton()
{

}

void singleitemButton::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    QIcon pushdelIcon;
    this->setFixedSize(34,34);
    this->setIconSize(QSize(16,16));
    pushdelIcon.addFile(":/new/prefix1/SVG/delete-b-hover.svg");
    this->setIcon(pushdelIcon);
}

void singleitemButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    QIcon pushdelIcon;
    this->setFixedSize(34,34);
    this->setIconSize(QSize(16,16));
    pushdelIcon.addFile(":/new/prefix1/SVG/delete-b-click.svg");
    this->setIcon(pushdelIcon);
}

void singleitemButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    QIcon pushdelIcon;
    this->setFixedSize(34,34);
    this->setIconSize(QSize(16,16));
    pushdelIcon.addFile(":/new/prefix1/SVG/delete-b-hover.svg");
    this->setIcon(pushdelIcon);
}

void singleitemButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    QIcon pushdelIcon;
    this->setFixedSize(34,34);
    this->setIconSize(QSize(16,16));
    pushdelIcon.addFile(":/new/prefix1/SVG/delete-b.svg");
    this->setIcon(pushdelIcon);
}

bool singleitemButton::eventFilter(QObject *obj, QEvent *e)
{
    //qDebug() << e->type();
    if(obj == this)
    {
        if(e->type() == QEvent::MouseButtonPress)
        {
            emit buttonclick();
            return true;
        }
    }
}


