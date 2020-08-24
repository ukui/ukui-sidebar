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


#include "clipboardwidgetentry.h"
#include "customstyleCleanPushbutton.h"
#include <QTimer>
#include <QStyleOption>
#include <QPainter>
#include <QPalette>
#include <QEvent>

ClipboardWidgetEntry::ClipboardWidgetEntry(QString dataFormat, QWidget *parent)
{
    Q_UNUSED(parent);
    m_dataFormat = dataFormat;
    status=NORMAL;
    this->setObjectName("WidgetEntry");
    this->setContentsMargins(0,0,0,0);

    /* 初始化三个按钮 */
    initPushbutton();
    /* 初始化Lable */
    initLable();

    if (dataFormat == ENTRYURL || dataFormat == ENTRYTEXT) {
        m_pCopyDataLabal->setFixedSize(386, 34);
    } else if (dataFormat == ENTRYIMAGE) {
        m_pCopyDataLabal->setFixedSize(110, 75);
    }

    m_pHLayout       = new QHBoxLayout();
    m_pHLayout->setContentsMargins(0,0,0,0);
    m_pHLayout->addItem(new QSpacerItem(10,20));

    if (dataFormat == ENTRYURL) {
        m_pCopyFileIcon = new pixmapLabel(); //用来放置文件的图标
        m_pCopyFileIcon->setContentsMargins(0, 0, 0, 0);
        m_pCopyFileIcon->setFixedSize(25, 25);
        m_pCopyDataLabal->setFixedSize(380, 34);
        m_pHLayout->addWidget(m_pCopyFileIcon);
    }

    m_pHLayout->addWidget(m_pCopyDataLabal);

    if (dataFormat == ENTRYIMAGE)
        m_pHLayout->addItem(new QSpacerItem(276, 34));

    m_pHLayout->addWidget(m_pPopButton);
    m_pHLayout->addWidget(m_pCancelLockButton);
    m_pCancelLockButton->setVisible(false);
    if (!(m_dataFormat == ENTRYURL
          || m_dataFormat == ENTRYIMAGE))
        m_pHLayout->addWidget(m_pEditButon);


    m_pHLayout->addWidget(m_pRemoveButton);
    m_pHLayout->addItem(new QSpacerItem(10,20));
    m_pHLayout->setSpacing(5);
    m_pPopButton->setVisible(false);
    m_pEditButon->setVisible(false);
    m_pRemoveButton->setVisible(false);
    this->setLayout(m_pHLayout);
}

void ClipboardWidgetEntry::initPushbutton()
{
    QIcon EditIcon;
    EditIcon.addFile(EDIT_SVG_PATH);
    QIcon PopIcon;
    PopIcon.addFile(LOCK_SVG_PATH);
    QIcon RemoveIcon;
    RemoveIcon.addFile(REMOVE_SVG_PATH);
    QIcon CancelIcon;
    CancelIcon.addFile(CANCEL_LOCK_PNG_PATH);
    m_pPopButton     = new QPushButton();
    m_pPopButton->setStyle(new customstyle_clean_pushbutton("ukui-default"));
    m_pPopButton->setToolTip(QObject::tr("Pop"));
    m_pPopButton->setFixedSize(34, 34);
    m_pPopButton->setIcon(PopIcon);
    m_pPopButton->setObjectName("PopButton");

    m_pEditButon     = new QPushButton();
    m_pEditButon->setStyle(new customstyle_clean_pushbutton("ukui-default"));
    connect(m_pEditButon, &QPushButton::clicked, globalClipboardSignal, &ClipboardSignal::ClipBoardWidgetEntryEditButtonSignal);
    m_pEditButon->setToolTip(QObject::tr("EditButton"));
    m_pEditButon->setFixedSize(34, 34);
    m_pEditButon->setIcon(EditIcon);
    m_pEditButon->setObjectName("EditButon");

    m_pRemoveButton  = new QPushButton();
    m_pRemoveButton->setStyle(new customstyle_clean_pushbutton("ukui-default"));
    m_pRemoveButton->setToolTip(QObject::tr("Remove"));
    m_pRemoveButton->setFixedSize(34, 34);
    m_pRemoveButton->setIcon(RemoveIcon);
    m_pRemoveButton->setObjectName("RemoveButton");

    m_pCancelLockButton = new QPushButton();
    m_pCancelLockButton->setStyle(new customstyle_clean_pushbutton("ukui-default"));
    m_pCancelLockButton->setToolTip(QObject::tr("Cancel the fixed"));
    m_pCancelLockButton->setFixedSize(34,34);
    m_pCancelLockButton->setIcon(CancelIcon);
    m_pCancelLockButton->setObjectName("cancel fixed the button");
    return;
}

void ClipboardWidgetEntry::initLable()
{
    m_pCopyDataLabal = new QLabel();
    QTimer::singleShot(1, m_pCopyDataLabal, [=](){
        QFont font = m_pCopyDataLabal->font();
//        font.setPixelSize(14);
//        font.setFamily("Noto Sans CJK SC");
        m_pCopyDataLabal->setFont(font);
    });
    m_pCopyDataLabal->setObjectName("EntryLable");
    if (m_dataFormat == ENTRYTEXT || m_dataFormat == ENTRYIMAGE) {
        m_pCopyDataLabal->setContentsMargins(3, 0, 0, 0);
    } else {
        m_pCopyDataLabal->setContentsMargins(0, 0, 0, 0);
    }
}

void ClipboardWidgetEntry::enterEvent(QEvent *e)
{
    if(e == nullptr) {
        return;
    }

    status=HOVER;
    repaint();

    m_pCopyDataLabal->setFixedSize(260, 34);
    if (m_dataFormat == ENTRYURL) {
        m_pCopyDataLabal->setFixedSize(278, 34);
    } else if (m_dataFormat == ENTRYIMAGE) {
        m_pCopyDataLabal->setFixedSize(110, 75);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
        emit previewShowImage(this);//发送预览信号
#endif
    } else {
        m_pCopyDataLabal->setFixedSize(260, 34);
        m_pEditButon->setVisible(true);
    }
    if (m_bWhetherFix) {
        m_pCancelLockButton->setVisible(true);
    } else {
        m_pPopButton->setVisible(true);
    }
    m_pRemoveButton->setVisible(true);
    m_ptext = this->m_pCopyDataLabal->text();
    QString format;
    if (m_dataFormat == ENTRYURL) {
        format = setMiddleFormatBody(m_ptext);
    } else {
        format = SetFormatBody(m_ptext);
    }
    m_pCopyDataLabal->setText(format);
    this->update();
}

void ClipboardWidgetEntry::leaveEvent(QEvent *e)
{
    if (e == nullptr)
        return;
    status=NORMAL;
    if (m_bWhetherFix) {
        m_pCancelLockButton->setVisible(false);
    } else {
        m_pPopButton->setVisible(false);
    }
    m_pEditButon->setVisible(false);
    m_pRemoveButton->setVisible(false);
    if (m_dataFormat == ENTRYURL || m_dataFormat == ENTRYTEXT) {
        m_pCopyDataLabal->setFixedSize(386, 34);
    } else if (m_dataFormat == ENTRYIMAGE) {
        m_pCopyDataLabal->setFixedSize(110, 75);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
        emit previewHideImage(this);//发送退出预览信号
#endif
        this->update();
    }
    if (m_ptext == "") {
        this->update();
        return;
    } else {
        this->m_pCopyDataLabal->setText(m_ptext);
    }
    this->update();
    return;
}

void ClipboardWidgetEntry::mousePressEvent(QMouseEvent *event)
{
    m_ptext = this->m_pCopyDataLabal->text();
    if (event->button() == Qt::LeftButton) {
        emit doubleClicksignals(this);
        return;
    }
    return;
}

void ClipboardWidgetEntry::mouseDoubleClickEvent(QMouseEvent *event)
{

}

QString ClipboardWidgetEntry::SetFormatBody(QString text)
{
    QFontMetrics fontMetrics(this->m_pCopyDataLabal->font());
    int LableWidth = this->m_pCopyDataLabal->width();
    int fontSize = fontMetrics.width(text);
    QString formatBody = text;
    if(fontSize > (LableWidth - 10)) {
        QStringList list = formatBody.split("\n");
        if (list.size() >= 2) {
            //当有几行时，只需要截取第一行就行，在第一行后面加...
            /* 判断第一行是否是空行 */
            formatBody = judgeBlankLine(list);
            formatBody = formatBody + "aa";
            int oneFontSize = fontMetrics.width(formatBody);
            if (oneFontSize > (LableWidth - 10)) {
                formatBody = fontMetrics.elidedText(formatBody, Qt::ElideRight, LableWidth - 10);
                return formatBody;
            } else {
                if (!substringSposition(formatBody, list)) {
                    int oneFontSize = fontMetrics.width(formatBody);
                    formatBody = fontMetrics.elidedText(formatBody, Qt::ElideRight, oneFontSize - 1);
                    return formatBody;
                }
            }
        } else {
            //说明只存在一行，在最后面加...就行
            formatBody = fontMetrics.elidedText(formatBody, Qt::ElideRight, LableWidth - 10);
            return formatBody;
        }
    } else {
        QStringList list = formatBody.split("\n");
        if (list.size() >= 2) {
            //取得当前的有字符串的子串
            formatBody = judgeBlankLine(list);
            formatBody = formatBody + "aa";
            if (!substringSposition(formatBody, list)) {
                int oneFontSize = fontMetrics.width(formatBody);
                formatBody = fontMetrics.elidedText(formatBody, Qt::ElideRight, oneFontSize - 1);
            }
        }
    }
    return formatBody;
}

QString ClipboardWidgetEntry::setMiddleFormatBody(QString text)
{
    QFontMetrics fontMetrics(m_pCopyDataLabal->font());
    int LableWidth = m_pCopyDataLabal->width();
    int fontSize = fontMetrics.width(text);
    QString formatBody = text;
    if (fontSize > (LableWidth - 20)) {
        formatBody = fontMetrics.elidedText(formatBody, Qt::ElideMiddle, LableWidth - 20);
        return formatBody;
    }
    return formatBody;
}

/* 去除掉空行，显示有字体的行 */
QString ClipboardWidgetEntry::judgeBlankLine(QStringList list)
{
    int tmp = list.count();
    for (int i = 0; i < tmp; i++) {
        QString dest = list.at(i);
        dest = dest.trimmed();
        if (dest.size() != 0)
           return list.at(i);
    }
    return list.at(0);
}

/* 判断当前子串位置，后面是否还有子串 */
bool ClipboardWidgetEntry::substringSposition(QString formatBody, QStringList list)
{
    int tmp = list.count();
    for (int i = 0; i < tmp; i++) {
        QString dest = list.at(i);
        if (dest == formatBody && i == tmp - 1)
            return true;
    }
    return false;
}

void ClipboardWidgetEntry::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    switch (status) {
      case NORMAL: {
              p.setBrush(QBrush(QColor(255, 255, 255, 0)));
              p.setPen(Qt::NoPen);
              break;
          }
      case HOVER: {
              QColor color(opt.palette.color(QPalette::WindowText));
              p.setBrush(QBrush(color));
              p.setOpacity(0.08);
              p.setPen(Qt::NoPen);
              break;
          }
      case PRESS: {
              break;
          }
    }
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.drawRoundedRect(opt.rect,0,0);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
