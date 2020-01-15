#ifndef SCROLLAREAWIDGET_H
#define SCROLLAREAWIDGET_H

#include <QScrollBar>
#include <QScrollArea>

class ScrollBarWidget : public QScrollBar
{
    Q_OBJECT
public:
    explicit ScrollBarWidget();

protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;

signals:

public slots:
};

class ScrollAreaWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit ScrollAreaWidget();

protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;

signals:

public slots:
};

#endif // SCROLLAREAWIDGET_H
