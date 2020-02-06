#ifndef TAKEINBOXTOOLBUTTON_H
#define TAKEINBOXTOOLBUTTON_H

#include <QToolButton>
#include <QWidget>

class TakeInBoxToolButton : public QToolButton
{
    Q_OBJECT
public:
    explicit TakeInBoxToolButton();
    void setEnterFlags(bool bFlags) {m_bEnterTakeInBox = bFlags;}

protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;

private:
    bool        m_bEnterTakeInBox;

signals:

public slots:
};

#endif // TAKEINBOXTOOLBUTTON_H
