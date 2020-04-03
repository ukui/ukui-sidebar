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
#ifndef CLEANPROMPTBOX_H
#define CLEANPROMPTBOX_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>
#include <QFile>
#include <QRadioButton>
#include "clipboardsignal.h"
#include "clipBoardInternalSignal.h"
#define  CLEAN_PNG_PATH  ":/image/user-trash.png"
#define  SIDEBAR_HINT_QSS_PATH  ":/qss/HintBoxWidget.css"
extern ClipboardSignal *globalClipboardSignal;
class CleanPromptBox : public QDialog
{
public:
    CleanPromptBox();
    QWidget     *m_pHintInformationWidget;
    QWidget     *m_pCheckBoxWidget;
    QWidget     *m_pButtonWidget;

    QPushButton *m_pConfirmButton;
    QPushButton *m_pCancelButton;
    QPushButton *m_pIconButton;
    QLabel      *m_pHintInformation;
    QLabel      *m_PIconLabel;

    QCheckBox   *m_pCheckBoxNoHint;

    QVBoxLayout  *m_pHintWidgetVLaout;
    QHBoxLayout  *m_pIconLableHLaout;
    QHBoxLayout  *m_pButtonHLaout;
    QHBoxLayout  *m_pChechBoxHLaout;

    void creatorHintInfomationWidget();
    void creatorCheckBoxWidget();
    void creatorButtonWidget();
    void creatorCleanPromptBoxWidget();
protected:
    void paintEvent(QPaintEvent *);
private slots:
    void ConfirmButtonSlots();
};

#endif // CLEANPROMPTBOX_H
