#include "clipboardlisetwidget.h"
#include "sidebarclipboardplugin.h"

#include <QMouseEvent>

#include <QDebug>
ClipBoardLisetWidget::ClipBoardLisetWidget()
{
    installEventFilter(this);
}

void ClipBoardLisetWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton) {
        auto pos = event->pos();
        if (!this->indexAt(pos).isValid())
            //发送信号
            emit globalClipboardSignal->ClipboardHideSignal();
    }
}
