#ifndef SIDEBARCLIPBOARDSIGNAL_H
#define SIDEBARCLIPBOARDSIGNAL_H
#include <QObject>
class SidebarClipBoardSignal : public QObject
{
    Q_OBJECT
public:
    explicit SidebarClipBoardSignal() {}

signals:
    void finishSignal();
    void removeSignal();
    void popSignal();
public slots:
};
#endif // SIDEBARCLIPBOARDSIGNAL_H
