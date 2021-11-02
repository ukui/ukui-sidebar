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
#ifndef SETUPPAGE_H
#define SETUPPAGE_H

#include <QWidget>
#include "setupPage.h"
#include "setAlarmRepeatDialog.h"
#include <QSqlTableModel>
#include <QHoverEvent>
#include <btnNew.h>
#include <setUpBtnNew.h>
#include <QGSettings/QGSettings>
#include "CustomButton.h"

namespace Ui {
class setuppage;
}

class setuppage : public QWidget
{
    Q_OBJECT

public:
    explicit setuppage( double , double, QWidget *parent = nullptr );
    ~setuppage();

    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
    void showPaint();
    void showPaint1();
    void showPaint2();

    Ui::setuppage *ui;
    set_alarm_repeat_Dialog * dialog_werk_day = nullptr;
    set_alarm_repeat_Dialog * Time_format = nullptr;
    set_alarm_repeat_Dialog * Pop_up_window = nullptr;
    set_alarm_repeat_Dialog * Reminder_off = nullptr;
    set_alarm_repeat_Dialog * Default_ringtone = nullptr;
    CustomButton * muteBtn;

    void showEvent(QShowEvent *event)

    {
    this->setAttribute(Qt::WA_Mapped);
    QWidget::showEvent(event);
    }

private slots:
    void Mute_starting();                                                                //静音开关回调
                                                                                         // Mute switch callback
    void werk_day_set();                                                                 //默认工作日日期设置回调
                                                                                         // Default workday date setting callback
    void Time_format_set();                                                              //时间格式设置回调
                                                                                         // Time format callback
    void Pop_up_window_set();                                                            //弹窗方式设置回调
                                                                                         // Pop up mode setting callback
    void Reminder_off_set();                                                             //提醒关闭回调
                                                                                         // Reminder close callback
    void Default_ringtone_set();                                                         //默认铃声设置回调
                                                                                         // Default ringtone setting callback
    void werk_day_listClickslot();                                                       //工作日选择单击回调
                                                                                         // Weekday select click callback
    void Time_format_listClickslot();                                                    //时间格式选择单击回调
                                                                                         // Time format selection click callback
    void Pop_up_window_listClickslot();                                                  //弹窗方式选择单击回调
                                                                                         // Pop up mode select click callback
    void Reminder_off_listClickslot();                                                   //提醒关闭选择单击回调
                                                                                         // Reminder off select click callback
    void Default_ringtone_listClickslot();                                               //默认铃声选择单击回调
                                                                                         // Default ring tone selection click callback
private:
    QSqlTableModel *model_setup;
    QPixmap repeat_on_Pixmap;
    QPixmap repeat_off_Pixmap;
    double pos_x;
    double pos_y;

    Btn_new *repeat_sel;
    setUpBtnNew *Time_sel;
    Btn_new *Pop_sel;
    setUpBtnNew *duration_sel;
    setUpBtnNew *ringtone_sel;

    QGSettings *style_settings;
};

#endif // SETUPPAGE_H
