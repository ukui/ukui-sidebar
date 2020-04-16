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
#include "customstyle_clean_pushbutton.h"
#include <QTimer>
#include <QStyleOption>
#include <QPainter>
#include <QPalette>
#include <QEvent>
ClipboardWidgetEntry::ClipboardWidgetEntry(QWidget *parent)
{
    Q_UNUSED(parent);
    status=NORMAL;
    this->setObjectName("WidgetEntry");
    this->setContentsMargins(0,0,0,0);
    QIcon EditIcon;
    EditIcon.addFile(EDIT_SVG_PATH);
    QIcon PopIcon;
    PopIcon.addFile(COPY_SVG_PATH);
    QIcon RemoveIcon;
    RemoveIcon.addFile(REMOVE_SVG_PATH);
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

    m_pCopyDataLabal = new QLabel();
    QTimer::singleShot(1, m_pCopyDataLabal, [=](){
        QFont font = m_pCopyDataLabal->font();
        font.setPixelSize(14);
        font.setFamily("Noto Sans CJK SC");
        m_pCopyDataLabal->setFont(font);
    });
    m_pCopyDataLabal->setObjectName("EntryLable");
    m_pCopyDataLabal->setContentsMargins(3, 0, 0, 0);
    m_pCopyDataLabal->setFixedSize(386, 34);

    m_pHLayout       = new QHBoxLayout();
    m_pHLayout->setContentsMargins(0,0,0,0);
    m_pHLayout->addItem(new QSpacerItem(10,20));
    m_pHLayout->addWidget(m_pCopyDataLabal);
    m_pHLayout->addWidget(m_pPopButton);
    m_pHLayout->addWidget(m_pEditButon);
    m_pHLayout->addWidget(m_pRemoveButton);
    m_pHLayout->addItem(new QSpacerItem(10,20));
    m_pHLayout->setSpacing(5);
    m_pPopButton->setVisible(false);
    m_pEditButon->setVisible(false);
    m_pRemoveButton->setVisible(false);
    this->setLayout(m_pHLayout);
}

void ClipboardWidgetEntry::enterEvent(QEvent *e)
{
    if(e == nullptr) {
        return;
    }

    status=HOVER;
    repaint();

    m_pCopyDataLabal->setFixedSize(260, 34);
    m_pPopButton->setVisible(true);
    m_pEditButon->setVisible(true);
    m_pRemoveButton->setVisible(true);
    m_ptext = this->m_pCopyDataLabal->text();
    QString format = SetFormatBody(m_ptext);
    m_pCopyDataLabal->setText(format);
}

void ClipboardWidgetEntry::leaveEvent(QEvent *e)
{
    if(e == nullptr) {
        return;
    }
    status=NORMAL;
    m_pPopButton->setVisible(false);
    m_pEditButon->setVisible(false);
    m_pRemoveButton->setVisible(false);
    m_pCopyDataLabal->setFixedSize(386, 34);
    this->m_pCopyDataLabal->setText(m_ptext);
}

QString ClipboardWidgetEntry::SetFormatBody(QString text)
{
    QFontMetrics fontMetrics(this->m_pCopyDataLabal->font());
    int LableWidth = this->m_pCopyDataLabal->width();
    int fontSize = fontMetrics.width(text);
    QString formatBody = text;
//    qDebug() << "Lable象数点大小为" << LableWidth << "&&从编辑框返回的数据，象数点大小为-->" << fontSize;
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
//                    qDebug () << "oneFontSize = fontMetrics.width(formatBody);" << oneFontSize;
                    formatBody = fontMetrics.elidedText(formatBody, Qt::ElideRight, oneFontSize - 1);
                    return formatBody;
                }
            }
        } else {
            //说明只存在一行，在最后面加...就行
//            qDebug() << "fontSize > (LableWidth - 10)" << LableWidth << "&&jiantieban---->" << fontSize;
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
//                qDebug () << "当前子串的大小" << oneFontSize << formatBody;
                formatBody = fontMetrics.elidedText(formatBody, Qt::ElideRight, oneFontSize - 1);
            }
        }
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
        if (dest.size() != 0) {
           return list.at(i);
        }
    }
    return list.at(0);
}

/* 判断当前子串位置，后面是否还有子串 */
bool ClipboardWidgetEntry::substringSposition(QString formatBody, QStringList list)
{
    int tmp = list.count();
    for (int i = 0; i < tmp; i++) {
        QString dest = list.at(i);
        if (dest == formatBody && i == tmp - 1) {
            qDebug() << "后面没有字串，返回true";
            return true;
        }
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
