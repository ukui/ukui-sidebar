#ifndef PIXMAPLABEL_H
#define PIXMAPLABEL_H
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QStyle>
#include <QStyleOption>

class pixmapLabel : public QLabel
{
    Q_OBJECT
public:
    pixmapLabel();
    QList<QPixmap> m_pixmapList;
    void setPixmapList(const QList<QPixmap> &list);
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PIXMAPLABEL_H
