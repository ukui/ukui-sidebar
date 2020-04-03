#ifndef CLIPBOARDINTERNALSIGNAL_H
#define CLIPBOARDINTERNALSIGNAL_H
#include <QObject>
class ClipBoardInternalSignal : public QObject
{
    Q_OBJECT
public:
    explicit ClipBoardInternalSignal() {}
    static void initInternalSignal();
    static ClipBoardInternalSignal* getGlobalInternalSignal();

signals:
    void CheckBoxSelectedSignal();
public slots:
};
#endif // CLIPBOARDINTERNALSIGNAL_H
