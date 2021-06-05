#ifndef SHORTCUTBASE_H
#define SHORTCUTBASE_H

#include <QObject>

class ShortcutInterface : public QObject
{
    Q_OBJECT
public:
    explicit ShortcutInterface(QObject *parent = nullptr);
    virtual bool action() const = 0;

};

#endif // SHORTCUTBASE_H
