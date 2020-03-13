#ifndef REALTIMEPROPERTYANIMATION_H
#define REALTIMEPROPERTYANIMATION_H

#include <QPropertyAnimation>

class RealtimePropertyAnimation : public QPropertyAnimation
{
    Q_OBJECT
public:
    explicit RealtimePropertyAnimation(QObject *target, const QByteArray &propertyName, QObject *parent = nullptr);

protected:
    virtual void updateCurrentValue(const QVariant &value) override;

signals:
    void Sig_currentRect(int, int, int, int);

};


#endif // REALTIMEPROPERTYANIMATION_H
