/*
* Copyright (C) 2019 Tianjin KYLIN Information Technology Co., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, see <http://www.gnu.org/licenses/&gt;.
*
*/
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
