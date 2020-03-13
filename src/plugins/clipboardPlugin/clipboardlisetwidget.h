#ifndef CLIPBOARDLISETWIDGET_H
#define CLIPBOARDLISETWIDGET_H
#include <QListWidget>
#include <QMouseEvent>
#include "clipboardsignal.h"
extern ClipboardSignal *globalClipboardSignal;
class ClipBoardLisetWidget :public QListWidget
{
public:
    ClipBoardLisetWidget();
protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // CLIPBOARDLISETWIDGET_H
