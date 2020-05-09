#ifndef CLIPBAORDSTRUCTORIGINALDATA_H
#define CLIPBAORDSTRUCTORIGINALDATA_H
#include <QMimeData>
#include "clipboardwidgetentry.h"
enum DataType {
    Unknown,
    Text,
    Image,
    File
};
typedef struct  clipboardOriginalDataHash {
    ClipboardWidgetEntry* WidgetEntry;
    const QMimeData* MimeData;
    QPixmap          *p_pixmap;
    QString          text;
    QString          Clipbaordformat;
    QList<QUrl>      urls;
    int              Sequence;
//    int              DataFlag = 0;  //数据标记，判断该数据类型为Pixmap还是Text DataFlag = 1 --> 文本, DataFlag = 2 --> 图片
} OriginalDataHashValue;
#endif // CLIPBAORDSTRUCTORIGINALDATA_H
