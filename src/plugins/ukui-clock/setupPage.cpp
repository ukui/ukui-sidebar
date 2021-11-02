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
#include "setupPage.h"
#include "ui_setupPage.h"
#include "QSlider"
#include <QPixmap>
#include "setAlarmRepeatDialog.h"
#include <QDebug>
#include <QBitmap>
#include <QPainterPath>
#include "customStyle.h"

extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);

setuppage::setuppage( double position_x, double position_y, QWidget *parent  ) :
    QWidget(parent),
    pos_x(position_x),
    pos_y(position_y),
    ui(new Ui::setuppage)
{
//    setAttribute(Qt::WA_TranslucentBackground);
//    QPainterPath blurPath;
//    setProperty("useSystemStyleBlur", true);
//    setProperty("blurRegion", QRegion(blurPath.toFillPolygon().toPolygon()));//使用QPainterPath的api生成多边形Region

//    this->setProperty("blurRegion", QRegion(QRect(1, 1, 1, 1)));
    Qt::WindowFlags m_flags = windowFlags();
    this->setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);

    ui->setupUi(this);
    //工作日 废弃
    dialog_werk_day = new  set_alarm_repeat_Dialog(280,225,7,ui->widget);
    //时间格式
    Time_format = new  set_alarm_repeat_Dialog(288,138,3,ui->widget);
    //弹窗方式 废弃
    Pop_up_window = new  set_alarm_repeat_Dialog(280,75,2,ui->widget);
    //稍后提醒时间间隔
    Reminder_off = new  set_alarm_repeat_Dialog(288,190,5,ui->widget);
    //默认铃声
    Default_ringtone = new  set_alarm_repeat_Dialog(288,169,4,ui->widget);

    connect(dialog_werk_day->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(werk_day_listClickslot()));
    connect(Time_format->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(Time_format_listClickslot()));
    connect(Pop_up_window->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(Pop_up_window_listClickslot()));
    connect(Reminder_off->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(Reminder_off_listClickslot()));
    connect(Default_ringtone->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(Default_ringtone_listClickslot()));
    //工作日 废弃
    repeat_sel = new Btn_new(10, tr("  work"), this);
    //弹窗方式 废弃
    Pop_sel = new Btn_new(0, tr("  Pop-up"), this);
    //时间格式
    Time_sel = new setUpBtnNew(0, tr("  Time"), this);
    //稍后提醒时间间隔

    duration_sel = new setUpBtnNew(0, tr("  duration"), this);
    //默认铃声
    ringtone_sel = new setUpBtnNew(0, tr("  ringtone"), this);
    repeat_sel->move(45, 97);repeat_sel->hide();
    Pop_sel ->move(45, 197);Pop_sel->hide();

    Time_sel->move(30, 108);
    duration_sel->move(30, 163);
    ringtone_sel->move(30, 218);

    Time_sel->resize(268,40);
    duration_sel->resize(268,40);
    ringtone_sel->resize(268,40);

    //绑定下拉框
    connect(repeat_sel, SIGNAL(clicked()), this, SLOT(werk_day_set()) );
    connect(Time_sel, SIGNAL(clicked()), this, SLOT(Time_format_set()) );
    connect(Pop_sel, SIGNAL(clicked()), this, SLOT(Pop_up_window_set()) );
    connect(duration_sel, SIGNAL(clicked()), this, SLOT(Reminder_off_set()) );
    connect(ringtone_sel, SIGNAL(clicked()), this, SLOT(Default_ringtone_set()) );

    model_setup = new QSqlTableModel(this);
    model_setup->setTable("setup");
    model_setup->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_setup->select();
    model_setup->submitAll();

    repeat_on_Pixmap = QPixmap(":/image/object-select-symbolic.png");
    repeat_off_Pixmap = QPixmap("");

    QString werk_day;
    QString Time = model_setup->index(0, 15).data().toString();
    QString Pop_up = model_setup->index(0, 16).data().toString();
    QString Reminder = model_setup->index(0, 17).data().toString();
    QString Default = model_setup->index(0, 5).data().toString();

    int werk = 0;
    for (int i=0; i<7; i++) {
        if (model_setup->index(0, i+7).data().toInt()) {
            if(i == 0){
                werk_day = werk_day + tr("Mon");
            }else if(i == 1){
                werk_day = werk_day + tr("Tue");
            }else if(i == 2){
                werk_day = werk_day + tr("Wed");
            }else if(i == 3){
                werk_day = werk_day + tr("Thu");
            }else if(i == 4){
                werk_day = werk_day + tr("Fri");
            }else if(i == 5){
                werk_day = werk_day + tr("Sat");
            }else if(i == 6){
                werk_day = werk_day + tr("Sun");
            }
        }else{
            werk = 1;
        }
    }

    //可以比较 Time.compare(tr("Following system") 而不是两个都写
    if(Time.compare("Following system") == 0 || Time.compare("跟随系统") == 0){
        Time = tr("Following system");
    }else if(Time.compare("24 hour system") == 0 || Time.compare("24小时制") == 0){
        Time = tr("24 hour system");
    }else if(Time.compare("12 hour system") == 0 || Time.compare("12小时制") == 0){
        Time = tr("12 hour system");
    }
    if(Pop_up.compare("Notification") == 0 || Pop_up.compare("通知栏弹窗") == 0){
        Pop_up = tr("Notification");
    }else if(Pop_up.compare("Full screen") == 0 || Pop_up.compare("全屏弹窗") == 0){
        Pop_up = tr("Full screen");
    }
    if(Reminder.compare("Alert in 2 minutes") == 0 || Reminder.compare("2分钟后提醒") == 0){
        Reminder = tr("Alert in 2 minutes");
    }else if(Reminder.compare("Alert in 5 minutes") == 0 || Reminder.compare("5分钟后提醒") == 0){
        Reminder = tr("Alert in 5 minutes");
    }else if(Reminder.compare("Alert in 10 minutes") == 0 || Reminder.compare("10分钟后提醒") == 0){
        Reminder = tr("Alert in 10 minutes");
    }else if(Reminder.compare("Alert in 30 minutes") == 0 || Reminder.compare("30分钟后提醒") == 0){
        Reminder = tr("Alert in 30 minutes");
    }else if(Reminder.compare("Alert in 60 minutes") == 0 || Reminder.compare("60分钟后提醒") == 0){
        Reminder = tr("Alert in 60 minutes");
    }

    if(Default.compare("glass") == 0 || Default.compare("玻璃") == 0){
        Default = tr("glass");
    }else if(Default.compare("bark") == 0 || Default.compare("犬吠") == 0){
        Default = tr("bark");
    }else if(Default.compare("sonar") == 0 || Default.compare("声呐") == 0){
        Default = tr("sonar");
    }else if(Default.compare("drip") == 0 || Default.compare("雨滴") == 0){
        Default = tr("drip");
    }
    if(werk){
        repeat_sel->textLabel->setText(werk_day);
    }else {
        repeat_sel->textLabel->setText(werk_day);
    }
    Time_sel->textLabel->setText(Time);
    Pop_sel->textLabel->setText(Pop_up);
    duration_sel->textLabel->setText(Reminder);
    ringtone_sel->textLabel->setText(Default);

    dialog_werk_day->hide();
    Time_format->hide() ;
    Pop_up_window->hide() ;
    Reminder_off->hide() ;
    Default_ringtone->hide() ;

    QPalette palette1 = ui->pushButton_6->palette();
    QColor ColorPlaceholderText3(255,255,255,0);
    QBrush brush;
    brush.setColor(ColorPlaceholderText3);
    palette1.setBrush(QPalette::Button, brush);
    ui->pushButton_6->setPalette(palette1);
    ui->pushButton_6->setEnabled(false);
    //引入主体的事件过滤器
    ui->pushButton_6->installEventFilter(this);

    ui->closeBtn->setIcon(QIcon::fromTheme("window-close-symbolic"));
    ui->closeBtn->setProperty("isWindowButton", 0x2);
    ui->closeBtn->setProperty("useIconHighlightEffect", 0x8);
    ui->closeBtn->setFlat(true);
    connect(ui->closeBtn, &QPushButton::clicked, this, [=](){
        this->hide();
    });
    ui->label->hide();
    ui->pushButton->hide();

    muteBtn = new CustomButton(this,54,24,1);
    muteBtn->move(236,66);
    //    主题框架1.0.6-5kylin2

    //关闭按钮去掉聚焦状态
    ui->closeBtn->setFocusPolicy(Qt::NoFocus);

}

setuppage::~setuppage()
{
    delete  model_setup;
    delete  dialog_werk_day ;
    delete  Time_format ;
    delete  Pop_up_window ;
    delete  Reminder_off ;
    delete  Default_ringtone ;
    delete  ui;
}

void setuppage::Mute_starting()
{

}
//默认工作日日期设置回调
// Default workday date setting callback
void setuppage::werk_day_set()
{
    //手动构造一个鼠标移走的事件
    //Manually construct an event to move the mouse away
    repeat_sel->setAttribute(Qt::WA_UnderMouse, false);
    QHoverEvent hoverEvent(QEvent::HoverLeave, QPoint(40, 40), QPoint(0, 0));
    QCoreApplication::sendEvent(repeat_sel, &hoverEvent);

    dialog_werk_day->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    //dialog_werk_day->setAttribute(Qt::WA_TranslucentBackground);
    QPointF position = parentWidget()->pos();
    dialog_werk_day->move(position.x()+83,position.y()+250);
    dialog_werk_day->resize(280,225);
    dialog_werk_day->listWidget->setFixedSize(280,225);
    dialog_werk_day->widget[0]->alarmLabel0->setText(tr("Mon"));
    dialog_werk_day->widget[1]->alarmLabel0->setText(tr("Tue"));
    dialog_werk_day->widget[2]->alarmLabel0->setText(tr("Wed"));
    dialog_werk_day->widget[3]->alarmLabel0->setText(tr("Thu"));
    dialog_werk_day->widget[4]->alarmLabel0->setText(tr("Fri"));
    dialog_werk_day->widget[5]->alarmLabel0->setText(tr("Sat"));
    dialog_werk_day->widget[6]->alarmLabel0->setText(tr("Sun"));

    for (int i=0; i<7; i++) {
        if (model_setup->index(0, i+7).data().toInt()) {
            dialog_werk_day->widget[i]->alarmLabel1->setPixmap(repeat_on_Pixmap);
        } else {
            dialog_werk_day->widget[i]->alarmLabel1->setPixmap(repeat_off_Pixmap);
        }
    }
    dialog_werk_day->show();
}
//工作日选择单击回调
// Weekday select click callback
void setuppage::werk_day_listClickslot()
{
    model_setup->select();
    QString repeat_str;
    int num=dialog_werk_day->listWidget->currentRow();
    QString day[7] ;
    day[0] = tr("Mon");
    day[1] = tr("Tue");
    day[2] = tr("Wed");
    day[3] = tr("Thu");
    day[4] = tr("Fri");
    day[5] = tr("Sat");
    day[6] = tr("Sun");

    switch (num)
    {
    case 0:
        if (model_setup->index(0, 7).data().toInt() ){
            if(model_setup->index(0, 8).data().toInt()==0&&
                    model_setup->index(0, 9).data().toInt()==0&&
                    model_setup->index(0, 10).data().toInt()==0&&
                    model_setup->index(0, 11).data().toInt()==0&&
                    model_setup->index(0, 12).data().toInt()==0&&
                    model_setup->index(0, 13).data().toInt()==0){
            }else{
                model_setup->setData(model_setup->index(0, 7), 0);
                dialog_werk_day->widget[0]->alarmLabel1->setPixmap(repeat_off_Pixmap);
            }
        }else{
            model_setup->setData(model_setup->index(0, 7), 1);
            dialog_werk_day->widget[0]->alarmLabel1->setPixmap(repeat_on_Pixmap);
        }

        break;

    case 1:
        if (model_setup->index(0, 8).data().toInt() ){
            if(model_setup->index(0, 7).data().toInt()==0&&
                    model_setup->index(0, 9).data().toInt()==0&&
                    model_setup->index(0, 10).data().toInt()==0&&
                    model_setup->index(0, 11).data().toInt()==0&&
                    model_setup->index(0, 12).data().toInt()==0&&
                    model_setup->index(0, 13).data().toInt()==0 ){
            }else{
                model_setup->setData(model_setup->index(0, 8), 0);
                dialog_werk_day->widget[1]->alarmLabel1->setPixmap(repeat_off_Pixmap);
            }
        }else{
            model_setup->setData(model_setup->index(0, 8), 1);
            dialog_werk_day->widget[1]->alarmLabel1->setPixmap(repeat_on_Pixmap);
        }

        break;

    case 2:
        if (model_setup->index(0, 9).data().toInt() ){
            if(model_setup->index(0, 8).data().toInt()==0&&
                    model_setup->index(0, 7).data().toInt()==0&&
                    model_setup->index(0, 10).data().toInt()==0&&
                    model_setup->index(0, 11).data().toInt()==0&&
                    model_setup->index(0, 12).data().toInt()==0&&
                    model_setup->index(0, 13).data().toInt()==0 ){
            }else{
                model_setup->setData(model_setup->index(0, 9), 0);
                dialog_werk_day->widget[2]->alarmLabel1->setPixmap(repeat_off_Pixmap);
            }
        }else{
            model_setup->setData(model_setup->index(0, 9), 1);
            dialog_werk_day->widget[2]->alarmLabel1->setPixmap(repeat_on_Pixmap);
        }

        break;

    case 3:
        if (model_setup->index(0, 10).data().toInt() ){
            if(model_setup->index(0, 8).data().toInt()==0&&
                    model_setup->index(0, 9).data().toInt()==0&&
                    model_setup->index(0, 7).data().toInt()==0&&
                    model_setup->index(0, 11).data().toInt()==0&&
                    model_setup->index(0, 12).data().toInt()==0&&
                    model_setup->index(0, 13).data().toInt()==0 ){
            }else{
                model_setup->setData(model_setup->index(0, 10), 0);
                dialog_werk_day->widget[3]->alarmLabel1->setPixmap(repeat_off_Pixmap);
            }
        }else{
            model_setup->setData(model_setup->index(0, 10), 1);
            dialog_werk_day->widget[3]->alarmLabel1->setPixmap(repeat_on_Pixmap);
        }
        break;

    case 4:
        if (model_setup->index(0, 11).data().toInt()) {
            if(model_setup->index(0, 8).data().toInt()==0&&
                    model_setup->index(0, 9).data().toInt()==0&&
                    model_setup->index(0, 10).data().toInt()==0&&
                    model_setup->index(0, 7).data().toInt()==0&&
                    model_setup->index(0, 12).data().toInt()==0&&
                    model_setup->index(0, 13).data().toInt()==0 ){
            }else{
                model_setup->setData(model_setup->index(0, 11), 0);
                dialog_werk_day->widget[4]->alarmLabel1->setPixmap(repeat_off_Pixmap);
            }
        } else {
            model_setup->setData(model_setup->index(0, 11), 1);
            dialog_werk_day->widget[4]->alarmLabel1->setPixmap(repeat_on_Pixmap);
        }
        break;

    case 5:
        if (model_setup->index(0, 12).data().toInt() ) {
            if(model_setup->index(0, 8).data().toInt()==0&&
                    model_setup->index(0, 9).data().toInt()==0&&
                    model_setup->index(0, 10).data().toInt()==0&&
                    model_setup->index(0, 11).data().toInt()==0&&
                    model_setup->index(0, 7).data().toInt()==0&&
                    model_setup->index(0, 13).data().toInt()==0 ){
            }else{
                model_setup->setData(model_setup->index(0, 12), 0);
                dialog_werk_day->widget[5]->alarmLabel1->setPixmap(repeat_off_Pixmap);
            }
        } else {
            model_setup->setData(model_setup->index(0, 12), 1);
            dialog_werk_day->widget[5]->alarmLabel1->setPixmap(repeat_on_Pixmap);
        }
        break;

    case 6:
        if (model_setup->index(0, 13).data().toInt()) {
            if(model_setup->index(0, 8).data().toInt()==0&&
                    model_setup->index(0, 9).data().toInt()==0&&
                    model_setup->index(0, 10).data().toInt()==0&&
                    model_setup->index(0, 11).data().toInt()==0&&
                    model_setup->index(0, 12).data().toInt()==0&&
                    model_setup->index(0, 7).data().toInt()==0 ){
            }else{
                model_setup->setData(model_setup->index(0, 13), 0);
                dialog_werk_day->widget[6]->alarmLabel1->setPixmap(repeat_off_Pixmap);
            }
        } else {
            model_setup->setData(model_setup->index(0, 13), 1);
            dialog_werk_day->widget[6]->alarmLabel1->setPixmap(repeat_on_Pixmap);
        }
        break;

    default:
        break;
    }

    for (int i=0; i<7; i++) {
        if (model_setup->index(0, i+7).data().toInt()) {
            repeat_str=repeat_str+day[i];
        }
    }
    if (model_setup->index(0, 7).data().toInt()&&model_setup->index(0, 8).data().toInt()\
            &&model_setup->index(0, 9).data().toInt()&&model_setup->index(0, 10).data().toInt() \
            &&model_setup->index(0, 11).data().toInt()&&model_setup->index(0, 12).data().toInt() \
            &&model_setup->index(0, 13).data().toInt()) {
        repeat_str = tr("Every day");
    }
    repeat_sel->textLabel->setText(repeat_str);
    model_setup->setData(model_setup->index(0, 14), repeat_str);

    repeat_str="";
    model_setup->submitAll();
}

//时间格式设置回调
// Time format callback
void setuppage::Time_format_set()
{
    Time_sel->setAttribute(Qt::WA_UnderMouse, false);
    QHoverEvent hoverEvent(QEvent::HoverLeave, QPoint(40, 40), QPoint(0, 0));
    QCoreApplication::sendEvent(Time_sel, &hoverEvent);

    Time_format->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    //Time_format->setAttribute(Qt::WA_TranslucentBackground);
    QPointF position = parentWidget()->pos();
    Time_format->move(position.x()+51,position.y()+265);
    Time_format->resize(288,138);
    Time_format->listWidget->setFixedSize(268,130);
    Time_format->widget[0]->alarmLabel0->setText(tr("Following system"));
    Time_format->widget[1]->alarmLabel0->setText(tr("24 hour system"));
    Time_format->widget[2]->alarmLabel0->setText(tr("12 hour system"));

    Time_format->show();

}

//时间格式选择单击回调
// Time format selection click callback
void setuppage::Time_format_listClickslot()
{
    model_setup->select();

    int num=Time_format->listWidget->currentRow();

    switch (num) {
    case 0:
        model_setup->setData(model_setup->index(0, 2), 0);
        model_setup->setData(model_setup->index(0, 15), tr("Following system"));
        break;

    case 1:
        model_setup->setData(model_setup->index(0, 2), 1);
        model_setup->setData(model_setup->index(0, 15), tr("24 hour system"));
        break;

    case 2:
        model_setup->setData(model_setup->index(0, 2), 2);
        model_setup->setData(model_setup->index(0, 15), tr("12 hour system"));
        break;
    default:
        break;
    }

    Time_sel->textLabel->setText(model_setup->index(0, 15).data().toString());
    Time_format->hide();
    model_setup->submitAll();
}
//弹窗方式设置回调
// Pop up mode setting callback
void setuppage::Pop_up_window_set()
{
    Pop_sel->setAttribute(Qt::WA_UnderMouse, false);
    QHoverEvent hoverEvent(QEvent::HoverLeave, QPoint(40, 40), QPoint(0, 0));
    QCoreApplication::sendEvent(Pop_sel, &hoverEvent);

    Pop_up_window->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    //Pop_up_window->setAttribute(Qt::WA_TranslucentBackground);;
    QPointF position = parentWidget()->pos();
    Pop_up_window->move(position.x()+83,position.y()+242);
    Pop_up_window->resize(280,75);
    Pop_up_window->listWidget->setFixedSize(280,75);
    Pop_up_window->widget[0]->alarmLabel0->setText(tr("Notification"));
    Pop_up_window->widget[1]->alarmLabel0->setText(tr("Full screen"));
    Pop_up_window->show();
}

//弹窗方式选择单击回调
// Pop up mode select click callback
void setuppage::Pop_up_window_listClickslot()
{
    model_setup->select();
    int num=Pop_up_window->listWidget->currentRow();
    switch (num) {
    case 0:
        model_setup->setData(model_setup->index(0, 3), 0);
        break;

    case 1:
        model_setup->setData(model_setup->index(0, 3), 1);
        break;
    default:
        break;
    }
    if (!model_setup->index(0, 3).data().toInt()) {
        model_setup->setData(model_setup->index(0, 16), tr("Notification"));
    } else {
        model_setup->setData(model_setup->index(0, 16), tr("Full screen"));
    }
    Pop_sel->textLabel->setText(model_setup->index(0, 16).data().toString());
    Pop_up_window->hide();
    model_setup->submitAll();
}

//提醒关闭回调
// Reminder close callback
void setuppage::Reminder_off_set()
{
    duration_sel->setAttribute(Qt::WA_UnderMouse, false);
    QHoverEvent hoverEvent(QEvent::HoverLeave, QPoint(40, 40), QPoint(0, 0));
    QCoreApplication::sendEvent(duration_sel, &hoverEvent);

    Reminder_off->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    //Reminder_off->setAttribute(Qt::WA_TranslucentBackground);
    QPointF position = parentWidget()->pos();
    Reminder_off->move(position.x()+51,position.y()+320);
    Reminder_off->resize(288,190);
    Reminder_off->listWidget->setFixedSize(268,170);
    Reminder_off->widget[0]->alarmLabel0->setText(tr("Alert in 2 minutes"));
    Reminder_off->widget[1]->alarmLabel0->setText(tr("Alert in 5 minutes"));
    Reminder_off->widget[2]->alarmLabel0->setText(tr("Alert in 10 minutes"));
    Reminder_off->widget[3]->alarmLabel0->setText(tr("Alert in 30 minutes"));
    Reminder_off->widget[4]->alarmLabel0->setText(tr("Alert in 60 minutes"));
    Reminder_off->show();
}

//提醒关闭选择单击回调
// Reminder off select click callback
void setuppage::Reminder_off_listClickslot()
{
    model_setup->select();
    int num=Reminder_off->listWidget->currentRow();
    //配置稍后提醒时间间隔
    model_setup->setData(model_setup->index(0, 4), num);

    switch (num) {
    case 0:
        model_setup->setData(model_setup->index(0, 17), tr("Alert in 2 minutes"));
        break;
    case 1:
        model_setup->setData(model_setup->index(0, 17), tr("Alert in 5 minutes"));
        break;
    case 2:
        model_setup->setData(model_setup->index(0, 17), tr("Alert in 10 minutes"));
        break;
    case 3:
        model_setup->setData(model_setup->index(0, 17), tr("Alert in 30 minutes"));
        break;
    case 4:
        model_setup->setData(model_setup->index(0, 17), tr("Alert in 60 minutes"));
        break;
    default:
        break;
    }
    duration_sel->textLabel->setText(model_setup->index(0, 17).data().toString());
    model_setup->submitAll();
    Reminder_off->hide();
}
//默认铃声设置回调
// Default ringtone setting callback
void setuppage::Default_ringtone_set()
{
    ringtone_sel->setAttribute(Qt::WA_UnderMouse, false);
    QHoverEvent hoverEvent(QEvent::HoverLeave, QPoint(40, 40), QPoint(0, 0));
    QCoreApplication::sendEvent(ringtone_sel, &hoverEvent);

    Default_ringtone->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    //Default_ringtone->setAttribute(Qt::WA_TranslucentBackground);
    QPointF position = parentWidget()->pos();
    Default_ringtone->move(position.x()+51,position.y()+373);
    Default_ringtone->resize(288,169);
    Default_ringtone->listWidget->setFixedSize(268,149);
    Default_ringtone->widget[0]->alarmLabel0->setText(tr("glass"));
    Default_ringtone->widget[1]->alarmLabel0->setText(tr("bark"));
    Default_ringtone->widget[2]->alarmLabel0->setText(tr("sonar"));
    Default_ringtone->widget[3]->alarmLabel0->setText(tr("drip"));
    Default_ringtone->show();

}

//默认铃声选择单击回调
// Default ring tone selection click callback
void setuppage::Default_ringtone_listClickslot()
{
    model_setup->select();

    int num=Default_ringtone->listWidget->currentRow();

    switch (num)
    {
    case 0:
        model_setup->setData(model_setup->index(0, 5), tr("glass"));
        break;
    case 1:
        model_setup->setData(model_setup->index(0, 5), tr("bark"));
        break;
    case 2:
        model_setup->setData(model_setup->index(0, 5), tr("sonar"));
        break;
    case 3:
        model_setup->setData(model_setup->index(0, 5), tr("drip"));
        break;
    default:
        break;
    }
    qDebug()<<"xxxxxxx";
    ringtone_sel->textLabel->setText(model_setup->index(0, 5).data().toString());
    Default_ringtone->hide();
    model_setup->submitAll();
}


void setuppage::paintEvent(QPaintEvent *event)
{

    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    QPainterPath rectPath;
    rectPath.addRoundedRect(this->rect().adjusted(10, 10, -10, -10), 10, 10);
    // 画一个黑底
    QPixmap pixmap(this->rect().size());
    pixmap.fill(Qt::transparent);
    QPainter pixmapPainter(&pixmap);
    pixmapPainter.setRenderHint(QPainter::Antialiasing);
    pixmapPainter.setPen(Qt::transparent);
    pixmapPainter.setBrush(QColor(0,0,0,100));
    pixmapPainter.drawPath(rectPath);
    pixmapPainter.end();

    // 模糊这个黑底
    QImage img = pixmap.toImage();
    qt_blurImage(img, 10, false, false);

    // 挖掉中心
    pixmap = QPixmap::fromImage(img);
    QPainter pixmapPainter2(&pixmap);
    pixmapPainter2.setRenderHint(QPainter::Antialiasing);
    pixmapPainter2.setCompositionMode(QPainter::CompositionMode_Clear);
    pixmapPainter2.setPen(Qt::transparent);
    pixmapPainter2.setBrush(Qt::transparent);
    pixmapPainter2.drawPath(rectPath);

    // 绘制阴影
    p.drawPixmap(this->rect(), pixmap, pixmap.rect());

    QStyleOption opt;
    opt.init(this);
    QColor mainColor;
    if(QColor(255,255,255) == opt.palette.color(QPalette::Base) || QColor(248,248,248) == opt.palette.color(QPalette::Base))
    {
        mainColor = QColor(228, 235, 242,255);
    }else{
        mainColor = QColor(80, 85, 89,255);
    }


    // 绘制一个背景
    p.save();
    p.fillPath(rectPath,mainColor);
    p.restore();


}

/**
 * @brief 事件拦截器
 */
bool setuppage::eventFilter(QObject *watched, QEvent *event)
{
    //拦截按钮pushButton_6 的Paint QEvent
    if(watched == ui->pushButton_6 && event->type() == QEvent::Paint)
    {
        showPaint2();
    }

    return QWidget::eventFilter(watched,event);
}

//实现响应函数
void setuppage::showPaint()
{
}

//实现响应函数
void setuppage::showPaint1()
{

}
/**
 * @brief 颜色切换
 */
void setuppage::showPaint2()
{
    QPalette palette = ui->pushButton_6->palette();
    QColor ColorPlaceholderText(248,163,76,255);
    QBrush brush3;
    brush3.setColor(ColorPlaceholderText);
    QStyleOption opt;
    opt.init(this);

    if(QColor(255,255,255) == opt.palette.color(QPalette::Base) || QColor(248,248,248) == opt.palette.color(QPalette::Base))
    {
        palette.setBrush(QPalette::ButtonText, QBrush(QColor(0, 0, 0)));
    }else{
        palette.setBrush(QPalette::ButtonText, QBrush(QColor(255, 255, 255)));
    }

    ui->pushButton_6->setPalette(palette);
}
