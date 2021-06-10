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
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QProcess>
#include <QGSettings>
#include "shortcutbutton.h"
#include "labelfotmattext.h"

#define KYLIN_FEEDBACK_NORMAL_NAME         "ukui-icon-feedback"
#define KYLIN_ALARM_NORMAL_NAME_SET        "ukui-icon-feedback-s"
#define KYLIN_BLUETOOTH_HOVER_NAME      "kylin-alarm-hover"
#define KYLIN_BLUETOOTH_PRESS_NAME      "kylin-alarm-pressed"

#define KYLIN_AlARM_NORMAL_PATH         ":/images/icon-alarm.svg"
#define KYLIN_AlARM_SET_PATH            ":/images/images/icon-alarm-s.svg"
#define KYLIN_DELETE_ICONPATH           ":/images/cancel-lock.png"

class feedbackButtonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit feedbackButtonWidget(QWidget *parent = nullptr);
    void FeedbackButtonClickSlots();
    QPushButton     *m_pDeleteButton;
private:
    void initMemberVariables();
    void initLayout();

private:
    QWidget         *m_pButtonWidget;
    ShortcutButton  *m_pFeedBackButton;
    LabelFotmatText *m_pLabelFotmatText;
    QLabel          *m_pFeedBackLabel;

    QVBoxLayout     *m_pVboxButtonLayout;
    QVBoxLayout     *m_pVboxLayout;

    QStyle          *m_pStyleNormal;

private slots:
//    void FeedbackButtonClickSlots();

Q_SIGNALS:

};
