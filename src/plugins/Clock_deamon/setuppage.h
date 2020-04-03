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
#include "ui_setuppage.h"
#include "set_alarm_repeat_dialog.h"
#include <QSqlTableModel>
namespace Ui {
class setuppage;
}

class setuppage : public QWidget
{
    Q_OBJECT

public:
    explicit setuppage(QWidget *parent = nullptr);
    ~setuppage();

    Ui::setuppage *ui;
    set_alarm_repeat_Dialog * dialog_werk_day = nullptr;


private slots:
    void Mute_starting();                                                                //静音开关回调

    void werk_day_set();                                                                 //默认工作日日期设置回调

    void Time_format_set();                                                              //时间格式设置回调

    void Pop_up_window_set();                                                            //弹窗方式设置回调

    void Reminder_off_set();                                                             //提醒关闭回调

    void Default_ringtone_set();                                                         //默认铃声设置回调

    void werk_day_listClickslot();                                                       //工作日选择单击回调

    void Time_format_listClickslot();                                                    //时间格式选择单击回调

    void Pop_up_window_listClickslot();                                                  //弹窗方式选择单击回调

    void Reminder_off_listClickslot();                                                   //提醒关闭选择单击回调

    void Default_ringtone_listClickslot();                                               //默认铃声选择单击回调

private:
    QSqlTableModel *model_setup;
    QPixmap repeat_on_Pixmap;
    QPixmap repeat_off_Pixmap;

};

#endif // SETUPPAGE_H
