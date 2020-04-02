#include "setuppage.h"
#include "ui_setuppage.h"
#include "QSlider"
#include <QPixmap>
#include "set_alarm_repeat_dialog.h"
#include <QDebug>

setuppage::setuppage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setuppage)
{
    ui->setupUi(this);
    this->setWindowOpacity(0.9);

    ui->pushButton->hide();
    ui->label->hide();

    QPixmap bgPixmap = QPixmap(":/go-bottom-symbolic.png");
    ui->pushButton_10->setIcon(bgPixmap);
    ui->pushButton_11->setIcon(bgPixmap);
    ui->pushButton_12->setIcon(bgPixmap);
    ui->pushButton_13->setIcon(bgPixmap);
    ui->pushButton_14->setIcon(bgPixmap);


    connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(werk_day_set()) );
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(werk_day_set()) );
    connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(Time_format_set()) );
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(Time_format_set()) );
    connect(ui->pushButton_12, SIGNAL(clicked()), this, SLOT(Pop_up_window_set()) );
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(Pop_up_window_set()) );
    connect(ui->pushButton_13, SIGNAL(clicked()), this, SLOT(Reminder_off_set()) );
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(Reminder_off_set()) );
    connect(ui->pushButton_14, SIGNAL(clicked()), this, SLOT(Default_ringtone_set()) );
    connect(ui->pushButton_15, SIGNAL(clicked()), this, SLOT(Default_ringtone_set()) );

    model_setup = new QSqlTableModel(this);
    model_setup->setTable("setup");
    model_setup->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_setup->select();

    repeat_on_Pixmap = QPixmap(":/object-select-symbolic.png");
    repeat_off_Pixmap = QPixmap("");

    ui->pushButton_6->setText(model_setup->index(0, 14).data().toString());
    ui->pushButton_7->setText(model_setup->index(0, 15).data().toString());
    ui->pushButton_8->setText(model_setup->index(0, 16).data().toString());
    ui->pushButton_9->setText(model_setup->index(0, 17).data().toString());
    ui->pushButton_15->setText(model_setup->index(0, 5).data().toString());
}

setuppage::~setuppage()
{
    delete ui;
}

void setuppage::Mute_starting()
{

}
//默认工作日日期设置回调
void setuppage::werk_day_set()
{
     if(dialog_werk_day)
     {
         dialog_werk_day->close();
         dialog_werk_day = nullptr;
     }
     else {
         dialog_werk_day = new  set_alarm_repeat_Dialog(ui->widget, 7);
         dialog_werk_day->setWindowFlags(Qt::FramelessWindowHint);
         dialog_werk_day->move(45,133);

         dialog_werk_day->widget[0]->alarmLabel0->setText(tr("周一"));
         dialog_werk_day->widget[1]->alarmLabel0->setText(tr("周二"));
         dialog_werk_day->widget[2]->alarmLabel0->setText(tr("周三"));
         dialog_werk_day->widget[3]->alarmLabel0->setText(tr("周四"));
         dialog_werk_day->widget[4]->alarmLabel0->setText(tr("周五"));
         dialog_werk_day->widget[5]->alarmLabel0->setText(tr("周六"));
         dialog_werk_day->widget[6]->alarmLabel0->setText(tr("周日"));
         dialog_werk_day->show();
         for (int i=0; i<7; i++) {
             if(model_setup->index(0, i+7).data().toInt())
             {
                 dialog_werk_day->widget[i]->alarmLabel1->setIcon(repeat_on_Pixmap);
             }else{
                 dialog_werk_day->widget[i]->alarmLabel1->setIcon(repeat_off_Pixmap);
             }
         }

         connect(dialog_werk_day->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(werk_day_listClickslot()));
     }
}
//工作日选择单击回调
void setuppage::werk_day_listClickslot()
{
    QString repeat_str;
    int num=dialog_werk_day->listWidget->currentRow();
    QString day[7] ;
    day[0]= tr("周一");
    day[1] = tr("周二");
    day[2] = tr("周三");
    day[3] = tr("周四");
    day[4] = tr("周五");
    day[5] = tr("周六");
    day[6] = tr("周日");

    switch (num)
    {
    case 0:
        if(model_setup->index(0, 7).data().toInt() )
        {
            model_setup->setData(model_setup->index(0, 7), 0);
            dialog_werk_day->widget[0]->alarmLabel1->setIcon(repeat_off_Pixmap);
        }else {
            model_setup->setData(model_setup->index(0, 7), 1);
            dialog_werk_day->widget[0]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }
        break;

    case 1:
        if(model_setup->index(0, 8).data().toInt() )
        {
            model_setup->setData(model_setup->index(0, 8), 0);
            dialog_werk_day->widget[1]->alarmLabel1->setIcon(repeat_off_Pixmap);
        }else {
            model_setup->setData(model_setup->index(0, 8), 1);
            dialog_werk_day->widget[1]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }
        break;

    case 2:
        if(model_setup->index(0, 9).data().toInt() )
        {
            model_setup->setData(model_setup->index(0, 9), 0);
            dialog_werk_day->widget[2]->alarmLabel1->setIcon(repeat_off_Pixmap);
        }else {
            model_setup->setData(model_setup->index(0, 9), 1);
            dialog_werk_day->widget[2]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }
        break;

    case 3:
        if(model_setup->index(0, 10).data().toInt() )
        {
            model_setup->setData(model_setup->index(0, 10), 0);
            dialog_werk_day->widget[3]->alarmLabel1->setIcon(repeat_off_Pixmap);
        }else {
            model_setup->setData(model_setup->index(0, 10), 1);
            dialog_werk_day->widget[3]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }
        break;

    case 4:
        if(model_setup->index(0, 11).data().toInt() )
        {
            model_setup->setData(model_setup->index(0, 11), 0);
            dialog_werk_day->widget[4]->alarmLabel1->setIcon(repeat_off_Pixmap);
        }else {
            model_setup->setData(model_setup->index(0, 11), 1);
            dialog_werk_day->widget[4]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }
        break;

    case 5:
        if(model_setup->index(0, 12).data().toInt() )
        {
            model_setup->setData(model_setup->index(0, 12), 0);
            dialog_werk_day->widget[5]->alarmLabel1->setIcon(repeat_off_Pixmap);
        }else {
            model_setup->setData(model_setup->index(0, 12), 1);
            dialog_werk_day->widget[5]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }
        break;

    case 6:
        if(model_setup->index(0, 13).data().toInt() )
        {
            model_setup->setData(model_setup->index(0, 13), 0);
            dialog_werk_day->widget[6]->alarmLabel1->setIcon(repeat_off_Pixmap);
        }else {
            model_setup->setData(model_setup->index(0, 13), 1);
            dialog_werk_day->widget[6]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }
        break;

    default:
        break;
    }

    for (int i=0; i<7; i++) {
        if(model_setup->index(0, i+7).data().toInt())
        {
            repeat_str=repeat_str+day[i];
        }
    }
    ui->pushButton_6->setText(repeat_str);
    model_setup->setData(model_setup->index(0, 14), repeat_str);

    repeat_str="";
    model_setup->submitAll();
}

//时间格式设置回调
void setuppage::Time_format_set()
{
    if(dialog_werk_day)
    {
        dialog_werk_day->close();
        dialog_werk_day = nullptr;
    }
    else {
        dialog_werk_day = new  set_alarm_repeat_Dialog(ui->widget, 2);
        dialog_werk_day->setWindowFlags(Qt::FramelessWindowHint);
        dialog_werk_day->move(45,183);
        dialog_werk_day->resize(280, 75);
        dialog_werk_day->widget[0]->alarmLabel0->setText(tr("24小时制(23:59:59)"));
        dialog_werk_day->widget[0]->alarmLabel0->setFixedSize(200,17);
        dialog_werk_day->widget[1]->alarmLabel0->setText(tr("12小时制(上午10:59:59)"));
        dialog_werk_day->widget[1]->alarmLabel0->setFixedSize(200,17);

        dialog_werk_day->show();
        connect(dialog_werk_day->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(Time_format_listClickslot()));
    }
}

//时间格式选择单击回调
void setuppage::Time_format_listClickslot()
{
    int num=dialog_werk_day->listWidget->currentRow();

    switch (num)
    {
    case 0:
            model_setup->setData(model_setup->index(0, 2), 0);
        break;

    case 1:
            model_setup->setData(model_setup->index(0, 2), 1);
        break;
    default:
        break;
    }
    if(!model_setup->index(0, 2).data().toInt())
    {
        model_setup->setData(model_setup->index(0, 15), tr("24小时制(23:59:59)"));
    }else{
        model_setup->setData(model_setup->index(0, 15), tr("12小时制(上午10:59:59)"));
    }

    ui->pushButton_7->setText(model_setup->index(0, 15).data().toString());
    dialog_werk_day->close();
    dialog_werk_day = nullptr;
    model_setup->submitAll();
}


void setuppage::Pop_up_window_set()
{
    if(dialog_werk_day)
    {
        dialog_werk_day->close();
        dialog_werk_day = nullptr;
    }
    else {
        dialog_werk_day = new  set_alarm_repeat_Dialog(ui->widget, 2);
        dialog_werk_day->setWindowFlags(Qt::FramelessWindowHint);
        dialog_werk_day->move(45,233);
        dialog_werk_day->resize(280, 75);
        dialog_werk_day->widget[0]->alarmLabel0->setText(tr("通知栏弹窗"));
        dialog_werk_day->widget[1]->alarmLabel0->setText(tr("全屏弹窗"));
        dialog_werk_day->show();
        connect(dialog_werk_day->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(Pop_up_window_listClickslot()));
    }

}

//弹窗方式选择单击回调
void setuppage::Pop_up_window_listClickslot()
{
    int num=dialog_werk_day->listWidget->currentRow();
    switch (num)
    {
    case 0:
            model_setup->setData(model_setup->index(0, 3), 0);
        break;

    case 1:
            model_setup->setData(model_setup->index(0, 3), 1);
        break;
    default:
        break;
    }
    if(!model_setup->index(0, 3).data().toInt())
    {
        model_setup->setData(model_setup->index(0, 16), tr("通知栏弹窗"));
    }else{
        model_setup->setData(model_setup->index(0, 16), tr("全屏弹窗"));
    }
    ui->pushButton_8->setText(model_setup->index(0, 16).data().toString());
    dialog_werk_day->close();
    dialog_werk_day = nullptr;
    model_setup->submitAll();
}


void setuppage::Reminder_off_set()
{
    if(dialog_werk_day)
    {
        dialog_werk_day->close();
        dialog_werk_day = nullptr;
    }
    else {
        dialog_werk_day = new  set_alarm_repeat_Dialog(ui->widget, 5);
        dialog_werk_day->setWindowFlags(Qt::FramelessWindowHint);
        dialog_werk_day->move(45,283);
        dialog_werk_day->resize(280, 175);
        dialog_werk_day->widget[0]->alarmLabel0->setFixedSize(200,17);
        dialog_werk_day->widget[1]->alarmLabel0->setFixedSize(200,17);
        dialog_werk_day->widget[2]->alarmLabel0->setFixedSize(200,17);
        dialog_werk_day->widget[3]->alarmLabel0->setFixedSize(200,17);
        dialog_werk_day->widget[4]->alarmLabel0->setFixedSize(200,17);
        dialog_werk_day->widget[0]->alarmLabel0->setText(tr("1分钟后自动关闭"));
        dialog_werk_day->widget[1]->alarmLabel0->setText(tr("2分钟后自动关闭"));
        dialog_werk_day->widget[2]->alarmLabel0->setText(tr("3分钟后自动关闭"));
        dialog_werk_day->widget[3]->alarmLabel0->setText(tr("4分钟后自动关闭"));
        dialog_werk_day->widget[4]->alarmLabel0->setText(tr("6分钟后自动关闭"));
        dialog_werk_day->show();
        connect(dialog_werk_day->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(Reminder_off_listClickslot()));
    }
}

//提醒关闭选择单击回调
void setuppage::Reminder_off_listClickslot()
{
    int num=dialog_werk_day->listWidget->currentRow();
    model_setup->setData(model_setup->index(0, 4), num);

    switch (num)
    {
    case 0:
            model_setup->setData(model_setup->index(0, 17), tr("1分钟后自动关闭"));
        break;

    case 1:
            model_setup->setData(model_setup->index(0, 17), tr("2分钟后自动关闭"));
        break;

    case 2:
            model_setup->setData(model_setup->index(0, 17), tr("3分钟后自动关闭"));
        break;

    case 3:
            model_setup->setData(model_setup->index(0, 17), tr("4分钟后自动关闭"));
        break;

    case 4:
            model_setup->setData(model_setup->index(0, 17), tr("6分钟后自动关闭"));
        break;
    default:
        break;
    }

    ui->pushButton_9->setText(model_setup->index(0, 17).data().toString());
    dialog_werk_day->close();
    dialog_werk_day = nullptr;
    model_setup->submitAll();
}

void setuppage::Default_ringtone_set()
{
    if(dialog_werk_day)
    {
        dialog_werk_day->close();
        dialog_werk_day = nullptr;
    }
    else {
        dialog_werk_day = new  set_alarm_repeat_Dialog(ui->widget, 4);
        dialog_werk_day->setWindowFlags(Qt::FramelessWindowHint);
        dialog_werk_day->move(45,343);
        dialog_werk_day->resize(280,100);
        dialog_werk_day->listWidget->setFixedSize(280,100);
        dialog_werk_day->widget[0]->alarmLabel0->setText(tr("玻璃"));
        dialog_werk_day->widget[1]->alarmLabel0->setText(tr("犬吠"));
        dialog_werk_day->widget[2]->alarmLabel0->setText(tr("声呐"));
        dialog_werk_day->widget[3]->alarmLabel0->setText(tr("雨滴"));
        dialog_werk_day->show();
        connect(dialog_werk_day->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(Default_ringtone_listClickslot()));
    }
}

//默认铃声选择单击回调
void setuppage::Default_ringtone_listClickslot()
{
    int num=dialog_werk_day->listWidget->currentRow();

    switch (num)
    {
    case 0:
            model_setup->setData(model_setup->index(0, 5), tr("玻璃"));
        break;

    case 1:
            model_setup->setData(model_setup->index(0, 5), tr("犬吠"));
        break;

    case 2:
            model_setup->setData(model_setup->index(0, 5), tr("声呐"));
        break;

    case 3:
            model_setup->setData(model_setup->index(0, 5), tr("雨滴"));
        break;

    default:
        break;
    }

    ui->pushButton_15->setText(model_setup->index(0, 5).data().toString());
    dialog_werk_day->close();
    dialog_werk_day = nullptr;
    model_setup->submitAll();
}

