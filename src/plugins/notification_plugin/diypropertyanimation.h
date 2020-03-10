#ifndef DIYPROPERTYANIMATION_H
#define DIYPROPERTYANIMATION_H

#include <QPropertyAnimation>

class DiyPropertyAnimation : public QPropertyAnimation
{
    Q_OBJECT
public:
    explicit DiyPropertyAnimation(QObject *target, const QByteArray &propertyName, QObject *parent = nullptr);

protected:
    virtual void updateCurrentValue(const QVariant &value) override;

signals:
    void Sig_currentRect(int, int, int, int);

};

#endif // DIYPROPERTYANIMATION_H
