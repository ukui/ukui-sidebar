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


#include "searchwidgetitemcontent.h"
#include <QApplication>
#include <QStyle>
#include <QFile>

SearchWidgetItemContent::SearchWidgetItemContent(QWidget *parent)
{
    Q_UNUSED(parent);
    translator = new QTranslator;
    QLocale locale;
    //获取系统语言环境
    if ( locale.language() == QLocale::Chinese ) {
        qDebug() << "中文环境" ;
        translator->load(QString(":/translations/qt_zh_CN.qm"));  //选择翻译文件
        QApplication::installTranslator(translator);
    }

    this->setObjectName("SearhWidget");
    this->setContentsMargins(0,0,0,0);
    m_pClearListWidgetButton = new QPushButton(tr("Clear"));
    m_pClearListWidgetButton->setFixedSize(80, 34);
    m_pClearListWidgetButton->setStyle(new customstyle_search_pushbutton("ukui-default"));
    m_pClearListWidgetButton->setObjectName("CleanList");
    connect(m_pClearListWidgetButton, &QPushButton::clicked, this, [=](){
        emit globalClipboardSignal->ClipBoardWidgetEntryEditButtonSignal();
    });
    m_pClearTextButton = new QPushButton;
    m_pClearTextButton->setFixedSize(19, 21);
    m_pClearTextButton->setIconSize(QSize(9, 9));
    m_pClearTextButton->setObjectName("ClearTextButton");
    m_pClearTextButton->setStyleSheet("QPushButton:pressed{border-image:url(:/image/button-close-hover-click-add-background-one.svg)}");
    m_pClearTextButton->setStyleSheet("QPushButton:hover{border-image:url(:/image/button-close-hover-click-add-background-one.svg)}");

    QIcon ClearTextEditIcon;
    ClearTextEditIcon.addFile(SEARCH_SVG_CLEAN);
    m_pClearTextButton->setIcon(ClearTextEditIcon);
    m_pClearTextButton->setCursor(Qt::ArrowCursor);

    m_pHBoxLayout = new QHBoxLayout;
    m_pHBoxLayout->setContentsMargins(0,0,0,0);
    m_pLineEditArea = new QLineEdit;
    m_pLineEditArea->setAttribute(Qt::WA_Hover, true);
    m_pLineEditArea->setStyle(new CustomStyle("ukui-default"));
    m_pLineEditArea->setFixedSize(290, 30);
    m_pLineEditArea->setObjectName("SearchLabel");
//    m_pLineEditArea->setContentsMargins(0,0,0,0);
    m_pLineEditArea->setTextMargins(8, 0, 0, 0);
    m_pLineEditArea->setPlaceholderText(tr("search..."));

    connect(m_pLineEditArea, &QLineEdit::textChanged, this, &SearchWidgetItemContent::textChageSlots);
    /* Sets the font color of the placeholder */
    QBrush LineEditBrush;
    QPalette paletteLineEdit;
    QFont SearchLine;
    SearchLine = m_pLineEditArea->font();
    SearchLine.setPixelSize(14);
    SearchLine.setFamily("Noto Sans CJK SC");
    m_pLineEditArea->setFont(SearchLine);

    QColor ColorPlaceholderText(255,255,255,89);
    LineEditBrush = paletteLineEdit.placeholderText();
    LineEditBrush.setColor(ColorPlaceholderText);
    paletteLineEdit.setBrush(QPalette::PlaceholderText, LineEditBrush);
    m_pLineEditArea->setPalette(paletteLineEdit);

    QWidgetAction* action = new QWidgetAction(m_pLineEditArea);
    action->setDefaultWidget(m_pClearTextButton);

    m_pLineEditArea->addAction(action, QLineEdit::TrailingPosition);
    m_pClearTextButton->setVisible(false);
    connect(m_pClearTextButton, &QPushButton::clicked, this, [=](){
          m_pLineEditArea->setText("");
    });
    m_pHBoxLayout->addItem(new QSpacerItem(10,20));
    m_pHBoxLayout->addWidget(m_pLineEditArea);
    m_pHBoxLayout->addItem(new QSpacerItem(10,20));
    m_pHBoxLayout->addWidget(m_pClearListWidgetButton);
    m_pHBoxLayout->addItem(new QSpacerItem(10,20));
    m_pHBoxLayout->setSpacing(0);
    this->setLayout(m_pHBoxLayout);
}

void SearchWidgetItemContent::textChageSlots(const QString &text)
{
    if (text != "") {
        m_pClearTextButton->setVisible(true);
    } else {
        m_pClearTextButton->setVisible(false);
    }
}
