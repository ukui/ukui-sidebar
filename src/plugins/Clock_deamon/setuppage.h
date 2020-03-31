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
