#ifndef ICONLABEL_H
#define ICONLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
class IconLabel : public QLabel
{
    Q_OBJECT
public:
    explicit IconLabel(QWidget *parent = nullptr);

protected:
    virtual void mouseReleaseEvent(QMouseEvent *ev);

Q_SIGNALS:
    void LabelClicked();


};

#endif // ICONLABEL_H
