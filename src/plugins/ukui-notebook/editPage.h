/*
* Copyright (C) 2020 Tianjin KYLIN Information Technology Co., Ltd.
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

#ifndef EDIT_PAGE_H
#define EDIT_PAGE_H

#include <QWidget>
#include <QPainter>
#include <QMenu>
#include <QPainter>
#include <QColor>
#include <QModelIndex>
#include <QTextList>
#include <QPointer>

#include "noteHead.h"
#include "noteHeadMenu.h"
#include "ui_noteHeadMenu.h"
#include "selectColorPage.h"
#include "ui_selectColorPage.h"
#include "paletteWidget.h"
#include "ui_paletteWidget.h"
#include "setFontColorPage.h"
#include "ui_setFontColorPage.h"
#include "setFontSizePage.h"
#include "ui_setFontSizePage.h"

namespace Ui {
class Edit_page;
}
class Widget;

class Edit_page : public QWidget
{
    Q_OBJECT

public:
    Edit_page(Widget* p , int noteId, QWidget *parent = nullptr);
    ~Edit_page();
    Ui::Edit_page *ui;
    Widget* pNotebook;
    QColor m_editColor;
    noteHead *m_noteHead;
    noteHeadMenu *m_noteHeadMenu;
    QModelIndex m_index;
    SetFontSize *set_size_page = nullptr ;
    SetFontColor *set_color_fort_page = nullptr ;

    int id;
    int m_noteId;

    bool m_isFullscreen;
    //bool m_ignoreShowHideEvents;
    bool m_isTopHit;

    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    //bool eventFilter(QObject *obj, QEvent *event);

    Qt::WindowFlags m_flags;
    void setStayOnTopSlot(bool b);

private:
    void initSetup();                                                // 初始配置
    void slotsSetup();                                               // 配置槽函数
    void btnSetup();                                                 // 初始化按钮
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);// 字体设置
    void fontChanged(const QFont &f);                                // 当前光标下字体格式获取
    void fontColorChanged(const QColor &c);                          // 当前光标下字体颜色获取
    void initColor();
    void listenToGsettings();

private:
    SelectColor *color_page;
    QTimer *timer;
    QString color[11];
    QColor color_num[11];

    QPointer<QTextList> m_lastBlockList;

    QPoint dragPosition;                                             // 拖动坐标
    bool mousePressed;                                               // 鼠标是否按下
    bool defaultFontColorChanged;                                    // 黑白字体颜色

private slots:
    void cursorPositionChangedSlot();                                // 当前光标位置改变
    void currentCharFormatChangedSlot(const QTextCharFormat &format);// 当前字体格式改变
    void textChangedSlot();                                          // 当前便签页身份id
    void setBoldSlot();                                              // 加粗
    void setItalicSlot();                                            // 斜体
    void setUnderlineSlot();                                         // 下划线
    void setStrikeOutSlot();                                         // 删除线
    void setUnorderedListSlot(bool checked);                         // 无序列表
    void setOrderedListSlot(bool checked);                           // 有序列表
    void list(bool checked, QTextListFormat::Style style);
    void setFontSizeSlot();                                          // 设置字体大小
    void setFontColorSlot();                                         // 设置字体颜色
    // 调色按钮
    void blueBtnSlot();
    void redBtnSlot();
    void darkGreenBtnSlot();
    void orangeBtnSlot();
    void purpleBtnSlot();
    void goldenBtnSlot();
    void lightBlueBtnSlot();
    void lightGreenBtnSlot();
    void yellowBtnSlot();
    void defaultBtnSlot();
    void pinkBtnSlot();
    void showFullScreenSlot();
    void textRightMenu(QPoint);
    void textForNewEditpageSlot();

signals:
    void texthasChanged(int noteId, int id);
    void colorhasChanged(const QColor &color,int);
    void isEmptyNote(int noteId);
    void requestDel(int noteId);
    void textForNewEditpageSig();

};

#endif // EDIT_PAGE_H
