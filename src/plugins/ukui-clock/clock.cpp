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
#include "clock.h"
#include "ui_clock.h"
#include <QPainter>
#include <math.h>
#include <QTimerEvent>
#include <QTime>
#include <QTimer>
#include <QDialog>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QMatrix>
#include <QFont>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QUrl>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QModelIndex>
#include <QSqlQuery>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QVBoxLayout>
#include <QDebug>
#include "debug.h"
#include <unistd.h>
#include <QTimer>
#include <QTime>
#include "connection.h"
#include <QMessageBox>
#include "itemNew.h"
#include "set_clock.h"
#include "stopwatchItem.h"
#include "noticeDialog.h"
#include <QBitmap>
#include <QProcess>
#include <QScreen>
#include "noticeAlarm.h"
#include "ui_noticeAlarm.h"
#include "deleteMsg.h"
#include "ui_deleteMsg.h"
#include <QScroller>
#include <QTranslator>
#include <QDesktopWidget>
#include "btnNew.h"
#include "closeOrHide.h"
#include "ui_setupPage.h"


extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);
const double PI=3.141592;

Clock::Clock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Clock)
{
    QTranslator *translator = new QTranslator;
    // Get system locale
    if (translator->load(QLocale(), QLatin1String("ukui-clock"), QLatin1String("_"), QLatin1String("/usr/share/ukui-sidebar/ukui-clock")))
        QApplication::installTranslator(translator);
    else
        qDebug() << "cannot load translator ukui-clock_" << QLocale::system().name() << ".qm!";

    ui->setupUi(this);
    createConnection();

    this->setWindowTitle(tr("Alarm"));
    this->setAttribute(Qt::WA_TranslucentBackground);
    mousePressed = 0;
    buttonImageInit();
    CountdownInit();
    stopwatchInit();
    clockInit();
    setupInit();
    this->setFixedSize(454,555);
    this->setWindowOpacity(0.97);
    /*实现鼠标左键滑动效果
    *Realize the sliding effect of left mouse button
    */
    ui->listWidget -> setFrameShape(QListWidget::NoFrame);
    ui->listWidget_2 -> setFrameShape(QListWidget::NoFrame);
    QScroller::grabGesture(ui->listWidget,QScroller::LeftMouseButtonGesture); /*设置鼠标左键拖动  Set left mouse drag*/
    QScroller::grabGesture(ui->listWidget_2,QScroller::LeftMouseButtonGesture); /*设置鼠标左键拖动  Set left mouse drag*/
    ui->listWidget -> setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);  /*设置像素级滑动    Set pixel level slide*/
    ui->listWidget_2 -> setVerticalScrollMode(QAbstractItemView::ScrollPerPixel); /*设置像素级滑动  Set pixel level slide*/

    ui->listWidget->setStyleSheet("QListWidget::item::selected{background-color:rgba(72,72,76,1);border-radius:4px;border:1px solid rgba(97,97,101,1);}\
                                  QListWidget::item::selected:active{background-color:rgba(72,72,76,1);border-radius:4px;border:1px solid rgba(97,97,101,1);}\
                                  QListWidget::item:hover{background-color:rgba(72,72,76,0.5);border-radius:4px;}");

    ui->listWidget_2->setStyleSheet("QListWidget::item::selected{background-color:rgba(72,72,76,1);border-radius:4px;border:1px solid rgba(97,97,101,1);}\
                                    QListWidget::item::selected:active{background-color:rgba(72,72,76,1);border-radius:4px;border:1px solid rgba(97,97,101,1);}\
                                    QListWidget::item:hover{background-color:rgba(72,72,76,0.5);border-radius:4px;}");

    m_pSreenInfo = new adaptScreenInfo();
    qDebug()<<m_pSreenInfo->m_screenWidth<<m_pSreenInfo->m_screenHeight;
    move((m_pSreenInfo->m_screenWidth - this->width() + m_pSreenInfo->m_nScreen_x )/2, (m_pSreenInfo->m_screenHeight - this->height())/2);

    pushcount = new QPushButton(ui->page_7);
    pushcount->setFixedSize(88,32);
    pushcount->setIconSize(QSize(16,16));
    pushcount->move(48,8);
    pushcount->setIcon(QIcon(":/icon-1.png"));
    pushcount->setText(tr("Count"));

    pushclock = new QPushButton(ui->page_7);
    pushclock->setFixedSize(88,32);
    pushclock->setIconSize(QSize(16,16));
    pushclock->move(182,8);
    pushclock->setIcon(QIcon(":/icon-4-16x16.png"));
    pushclock->setText(tr("Alarm"));

    pushstop = new QPushButton(ui->page_7);
    pushstop->setFixedSize(88,32);
    pushstop->setIconSize(QSize(16,16));
    pushstop->move(317,8);
    pushstop->setIcon(QIcon(":/icon-2.png"));
    pushstop->setText(tr("Watch"));

    pushcount->setProperty("useIconHighlightEffect", true);
    pushcount->setProperty("iconHighlightEffectMode", 1);
    pushclock->setProperty("useIconHighlightEffect", true);
    pushclock->setProperty("iconHighlightEffectMode", 1);
    pushstop->setProperty("useIconHighlightEffect", true);
    pushstop->setProperty("iconHighlightEffectMode", 1);

    pushclock->setCheckable(true);
    pushcount->setCheckable(true);
    pushstop->setCheckable(true);
    pushclock->setAutoExclusive(true);
    pushcount->setAutoExclusive(true);
    pushstop->setAutoExclusive(true);

    pushclock->setChecked(true);

    connect(pushcount, SIGNAL(clicked()), this, SLOT( CountdownPageSwitch ()));
    connect(pushclock, SIGNAL(clicked()), this, SLOT( AlarmPageSwitch ()));
    connect(pushstop, SIGNAL(clicked()), this, SLOT( StopwatchPageSwitch ()));

     AlarmPageSwitch ();/*初始显示闹钟界面
                               Initial display alarm interface*/

    close_or_hide_page = new close_or_hide(this);

    ui->set_page->hide();
    ui->set_page->installEventFilter(this);
    ui->widget->installEventFilter(this);
    shadow->installEventFilter(this);
    shadow1->installEventFilter(this);

    ui->lineEdit->setStyleSheet("QLineEdit{background-color:transparent}");

    QPalette palette2 = ui->count_stat->palette();
    QColor ColorPlaceholderText2(61,107,229,255);
    QBrush brush2;
    brush2.setColor(ColorPlaceholderText2);
    palette2.setColor(QPalette::Button,QColor(61,107,229,255));
    palette2.setBrush(QPalette::ButtonText, QBrush(Qt::white));
    ui->count_stat->setPalette(palette2);
    ui->addAlarmBtn->setPalette(palette2);
    ui->pushButton_Start->setPalette(palette2);
    ui->set_alarm_savebtn->setPalette(palette2);
    ui->pushButton_9->setPalette(palette2);

    QPalette palette = ui->count_push->palette();
    QColor ColorPlaceholderText(248,163,76,255);
    QBrush brush3;
    brush3.setColor(ColorPlaceholderText);
    palette.setColor(QPalette::Button,QColor(248,163,76,255));
    palette.setBrush(QPalette::ButtonText, QBrush(Qt::white));
    ui->count_push->setPalette(palette);

    QPalette palette1 = ui->pushButton->palette();
    QColor ColorPlaceholderText3(255,255,255,0);
    QBrush brush;
    brush.setColor(ColorPlaceholderText3);
    palette1.setBrush(QPalette::Button, brush);
    ui->pushButton->setPalette(palette1);

    ui->pushButton_12->setPalette(palette1);

    ui->pushButton->setProperty("useIconHighlightEffect", true);
    ui->pushButton->setProperty("iconHighlightEffectMode", 1);
    ui->horizontalLayout->setContentsMargins(0,0,0,0);

    count_stat->setEnabled(false);
}

Clock::~Clock()
{
    delete timer_set_page;
    delete timer_Surplus;
    delete timer;
    delete timer_2;
    delete countdown_timer;
    delete model;
    delete model_setup;
    delete setup_page;
    delete dialog_repeat;
    delete dialog_music;
    delete time_music;
    delete count_music_sellect;
    delete ui->page_5;
    delete ui;
}

void Clock::closeEvent(QCloseEvent *event)
{
        QPointF position = this->pos();
        close_or_hide_page->move(position.x()+67,position.y()+250);
        close_or_hide_page->exec();

        if(close_or_hide_page->close_flag==1){
            event->accept();
            exit(0);
        }else if(close_or_hide_page->close_flag==2){
            event->ignore();
            this->hide();
            close_or_hide_page->close_flag = 0;
        }else{
            event->ignore();
        }
}

/*
*闹钟按钮图片初始化
* Alarm button picture initialization
*/
void Clock::buttonImageInit()
{
    pixmap1 = QPixmap(":/icon-1.png");
    pixmap1 = ChangeImageColor(pixmap1, QColor(255,255,255), QColor(0,0,0));
    pixmap2 = QPixmap(":/icon-2.png");
    pixmap3 = QPixmap(":/icon-3.png");
    pixmap4 = QPixmap(":/icon-4-16x16.png");
    pixmap5 = QPixmap(":/window-close-symbolic.png");
    pixmap6 = QPixmap(":/window-minimize-symbolic.png");
    pixmap7 = QPixmap(":/open-menu-symbolic.png");
    pixmap8 = QPixmap(":/start_1.png");
    pixmap9 = QPixmap(":/start_2.png");
    pixmap10 = QPixmap(":/push_1.png");
    pixmap11 = QPixmap(":/push_2.png");
    bgPixmap = QPixmap(":/go-bottom-symbolic.png");
    repeat_on_Pixmap = QPixmap(":/object-select-symbolic.png");
    repeat_off_Pixmap = QPixmap("");
    delBtnPixmap = QPixmap(":/deleteBtn.png");
    on_pixmap = QPixmap(":/alarm_on.png");
    off_pixmap = QPixmap(":/alarm_off.png");
    clock_icon = QPixmap(":/kylin-alarm-clock.svg");
    this->setWindowIcon(QIcon::fromTheme("kylin-alarm-clock",QIcon(":/kylin-alarm-clock.svg")));

    ui->pushButton->setIcon(pixmap4);
    ui->pushButton->setFlat(true);
    ui->pushButton->setVisible(true);
    ui->pushButton->setFocusPolicy(Qt::NoFocus);

    ui->pushButton_4->setIcon(QIcon::fromTheme("window-minimize-symbolic"));
    ui->pushButton_5->setIcon(QIcon::fromTheme("window-close-symbolic"));
    ui->pushButton_12->setIcon(QIcon::fromTheme("open-menu-symbolic"));
    ui->pushButton_4->setFlat(true);
    ui->pushButton_5->setFlat(true);
    ui->pushButton_4->setVisible(true);
    ui->pushButton_5->setVisible(true);
    ui->pushButton_12->setVisible(true);
    ui->pushButton_4->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_5->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_12->setFocusPolicy(Qt::NoFocus);

    ui->pushButton_4->setProperty("isWindowButton", 0x1);
    ui->pushButton_5->setProperty("isWindowButton", 0x2);
    ui->pushButton_12->setProperty("isWindowButton", 0x1);

    ui->pushButton_4->setProperty("useIconHighlightEffect", 0x2);
    ui->pushButton_5->setProperty("useIconHighlightEffect", 0x8);
    ui->pushButton_12->setProperty("useIconHighlightEffect", 0x2);

    count_sel = new Btn_new(0, tr("  Remind"), ui->page_4);
    count_sel->move(89,358);
    count_sel_1 = new Btn_new(0, tr("  Remind"), ui->page_5);
    count_sel_1->move(89,358);

    repeat_sel = new Btn_new(10, tr("  repeat"), ui->set_page);
    repeat_sel->move(82,302);
    time_sel = new Btn_new(0, tr("  Remind"), ui->set_page);
    time_sel->move(82,352);
    ring_sel = new Btn_new(0, tr("  ring time"), ui->set_page);
    ring_sel->move(82,402);
}
/*
*倒计时页初始化
*Countdown page initialization
*/
void Clock::CountdownInit()
{
    /*初始化定时器
     Initialize timer*/
    countdown_timer = new QTimer();
    /*信号和槽
     Signals and slots*/
    connect(ui->count_stat, SIGNAL(clicked()), this, SLOT(startbtnCountdown()) );
    connect(countdown_timer, SIGNAL(timeout()), this, SLOT(statCountdown()));
    /*设置定时器每个多少毫秒发送一个timeout()信号
     Set the timer to send a timeout () signal every milliseconds*/
    countdown_timer->setInterval(1000);
    countdown_hour = 0;
    countdown_minute = 0;
    countdown_second = 9;
    countdown_pushflag = 0;
    countdown_isStarted = 0;
    countdown_isStarted_2 = 0;
    ui->page_5->RoundBar3->ring_max = 3600;
    /*初始化倒计时进度圈
     Initialize countdown progress circle*/
    ui->page_5->RoundBar3->setValue(3600);
    ui->count_stat->raise();
}

/*
*秒表页初始化
*Stopwatch page initialization
*/
void Clock::stopwatchInit()
{
    /*初始化定时器
     Initialize timer*/
    timer = new QTimer();
    /*信号和槽
     Signals and slots*/
    connect(timer, SIGNAL(timeout()), this, SLOT(CountDown()));
    /*设置定时器每个多少毫秒发送一个timeout()信号
     Set the timer to send a timeout () signal every milliseconds*/
    timer->setInterval(10);
    ui->label_4->setText("00:00.00");
    isStarted = 0;
    hour=0;
    minute=0;
    second=0;
    pushflag=0 ;
    /*时间间隔定时器
     Time interval timer*/
    timer_2 = new QTimer();
    connect(timer_2, SIGNAL(timeout()), this, SLOT(stopwatchJg()));
    timer_2->setInterval(10);
    stopwatch_hour = 0;
    stopwatch_minute = 0;
    stopwatch_second = 0;
    stopwatch_isStarted = 0;

    ui->label_4->move(122,136);
    ui->label_5->move(177,210);
    ui->listWidget_2->move(39,230);
    ui->pushButton_Start->raise();
    ui->pushButton_ring->raise();
    ui->pushButton_timeselect->raise();
    ui->pushButton_timeselect->setEnabled(false);
    ui->pushButton_ring->setEnabled(false);
}

/*
*闹钟页初始化
*Alarm page initialization
*/
void Clock::clockInit()
{
    ui->lineEdit->setAlignment(Qt::AlignRight);
    QTimer *timer_clock = new QTimer(this);
    connect(timer_clock, SIGNAL(timeout()), this, SLOT(timerUpdate()) );/*动态获取时间
                                                                         Dynamic acquisition time*/
    timer_clock->start(1000);
    connect( ui->addAlarmBtn, SIGNAL(clicked()), this, SLOT(setAlarmClock()) );/*添加闹钟
                                                                                  Add alarm*/
    ui->label_6->setAlignment(Qt::AlignHCenter);
    ui->label_7->setAlignment(Qt::AlignHCenter);
    ui->label_12->setAlignment(Qt::AlignHCenter);
    ui->label_4->setAlignment(Qt::AlignHCenter);
    ui->label_5->setAlignment(Qt::AlignHCenter);
    ui->label_9->setAlignment(Qt::AlignHCenter);
    ui->label_13->setAlignment(Qt::AlignHCenter);
    model = new QSqlTableModel(this);
    model->setTable("clock");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select(); /*选取整个表的所有行
                      Select all rows of the entire table*/
    model_setup = new QSqlTableModel(this);
    model_setup->setTable("setup");
    model_setup->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_setup->select();

    connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(listdoubleClickslot()));
    connect(ui->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(listClickslot()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(deleteAlarm()) );
    connect(ui->set_alarm_savebtn, SIGNAL(clicked()), this, SLOT(setAlarmSave()) );
    connect(ui->set_alarm_cancelbtn, SIGNAL(clicked()), this, SLOT(alarmCancelSave()) );
    connect(repeat_sel, SIGNAL(clicked()), this, SLOT(alarmRepeat()) );
    connect(time_sel, SIGNAL(clicked()), this, SLOT(selectAlarmMusic()) );
    connect(ring_sel, SIGNAL(clicked()), this, SLOT(timeMusic()) );
    connect(count_sel, SIGNAL(clicked()), this, SLOT(countdownMusicSellect()));
    connect(count_sel_1, SIGNAL(clicked()), this, SLOT(countdownMusicSellect()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(windowClosingClicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(windowMinimizingClicked()));

    /*单击时间提示计时器
     Click time reminder timer*/
    timer_Surplus = new QTimer();
    connect(timer_Surplus, SIGNAL(timeout()), this, SLOT(listClickslot()));
    timer_Surplus->setInterval(1000);
    /*闹钟设置界面时间提示计时器
     Alarm clock setting interface time prompt timer*/
    timer_set_page = new QTimer();
    connect(timer_set_page, SIGNAL(timeout()), this, SLOT(verticalscrollRingTime()));
    timer_set_page->setInterval(100);
    if(model_setup->index(0, 2).data().toInt() == 2){
        system_time_flag = 0;
    }
    updateAlarmClock();

    if(!model->rowCount())
        ui->label_7->setText("");

    /*设置关于页*/
    ui->pushButton_12->setPopupMode(QToolButton::InstantPopup);
    m_menu = new QMenu(ui->pushButton_12);
    m_menu->setProperty("fillIconSymbolicColor", true);
    m_menuAction = new QAction(m_menu);
    QAction *m_aboutAction = new QAction(m_menu);
    QAction *m_closeAction = new QAction(m_menu);

    m_menuAction->setText(tr("Set Up"));
    m_aboutAction->setText(tr("About"));
    m_closeAction->setText(tr("Close"));

    m_menu->addAction(m_menuAction);
    m_menu->addAction(m_aboutAction);
    m_menu->addAction(m_closeAction);

    ui->pushButton_12->setMenu(m_menu);

    connect(m_aboutAction, &QAction::triggered, this, [=](){
        About *dialog = new About();
        dialog->exec();
    });
    connect(m_menuAction, SIGNAL(triggered()), this, SLOT(setUpPage()));
    connect(m_closeAction, SIGNAL(triggered()), this, SLOT(windowClosingClicked()));
}
/*
* 默认初始设置
* Default initial settings
*/
void Clock::setupInit()
{
    countdownSetStartTime();/*倒计时初始化数字转盘
                               Countdown initialization digital turntable*/
    ui->label_8->hide();
    count_sel->textLabel->setText(model_setup->index(0, 19).data().toString());
    count_sel_1->textLabel->setText(model_setup->index(0, 19).data().toString());
    alarmSetStartTime();/*闹钟初始化数字转盘
                            Alarm initialization digital turntable*/
    modelSetupSet(); /*设置数据库初始化
                        Set database initialization*/
    textTimerupdate();
    ui->lineEdit->setMaxLength(8);/*限制闹钟名字长度为9个字符*/

    /*设置输入框无视空格*/
    QRegExp rx = QRegExp("[\40]*");
    QRegExpValidator* validator = new QRegExpValidator(rx);
    ui->lineEdit->setValidator(validator);

    QString Default = model_setup->index(0, 19).data().toString();
    if(Default == "glass" || "玻璃"){
        Default = tr("glass");
    }else if(Default == "bark" || "犬吠"){
        Default = tr("bark");
    }else if(Default == "sonar" || "声呐"){
        Default = tr("sonar");
    }else if(Default == "drip" || "雨滴"){
        Default = tr("drip");
    }
    count_sel->textLabel->setText(Default);
    count_sel_1->textLabel->setText(Default);
    for (int i = 0; i < 9; i++) {
        repeat_day[i] = 0;
    }
    dialog_repeat = new  set_alarm_repeat_Dialog(ui->set_page, 9);dialog_repeat->hide();
    dialog_music = new  set_alarm_repeat_Dialog(ui->set_page, 4);dialog_music->hide();
    time_music = new  set_alarm_repeat_Dialog(ui->set_page, 5);time_music->hide();
    count_music_sellect = new  set_alarm_repeat_Dialog(ui->page, 4);count_music_sellect->hide();
    connect(dialog_repeat->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(repeatListclickslot()));
    connect(dialog_music->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(musicListclickslot()));
    connect(time_music->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(timeMusicListclickslot()));
}

/*
 * 时间间隔执行
 * Interval calculation execution callback
 */
void Clock::stopwatchJg()
{
    if (stopwatch_hour < 10) {
        QString hours_str = QString::number(stopwatch_hour);
        stopwatch_jg_h = "0"+hours_str;
    } else {
        stopwatch_jg_h = QString::number(stopwatch_hour);
    }

    if (stopwatch_minute < 10) {
        QString minute_str = QString::number(stopwatch_minute);
        stopwatch_jg_m = "0"+minute_str;
    }else {
        stopwatch_jg_m = QString::number(stopwatch_minute);
    }

    if (stopwatch_second < 10) {
        QString second_str = QString::number(stopwatch_second);
        stopwatch_jg_s = "0"+second_str;
    } else {
        stopwatch_jg_s = QString::number(stopwatch_second);
    }

    ui->label_5->setText(stopwatch_jg_h+":"+stopwatch_jg_m+"."+stopwatch_jg_s);

    stopwatch_second++;
    if (stopwatch_second==100) {
        stopwatch_minute++; stopwatch_second=0;}
    if (stopwatch_minute==60) {
        stopwatch_hour++; stopwatch_minute=0;}
}

/*
 * 秒表执行
 * Stopwatch execution
 */
void Clock::CountDown()
{
    if (hour < 10) {
        QString hours_str = QString::number(hour);
        stopwatch_h = "0"+hours_str;
    } else {
        stopwatch_h = QString::number(hour);
    }

    if (minute < 10) {
        QString minute_str = QString::number(minute);
        stopwatch_m = "0"+minute_str;
    } else {
        stopwatch_m = QString::number(minute);
    }

    if (second < 10) {
        QString second_str = QString::number(second);
        stopwatch_s = "0"+second_str;
    } else {
        stopwatch_s = QString::number(second);
    }
    ui->label_4->setText(stopwatch_h+":"+stopwatch_m+"."+stopwatch_s);

    second++;
    if (second==100){
        minute++; second=0;
    }

    if (minute==60){
        hour++; minute=0;
    }

}
/*
 * 秒表开始暂停继续
 * Stopwatch start pause continue
 */
void Clock::onPushbuttonStartClicked()
{
    if (!isStarted) {
        ui->pushButton_timeselect->setEnabled(true);
        ui->pushButton_ring->setEnabled(true);
        ui->pushButton_timeselect->hide();
        ui->pushButton_Start->setText(tr("suspend"));

        QPalette palette = ui->pushButton_Start->palette();
        QColor ColorPlaceholderText(248,163,76,255);
        QBrush brush2;
        brush2.setColor(ColorPlaceholderText);
        palette.setColor(QPalette::Button,QColor(248,163,76,255));
        palette.setBrush(QPalette::ButtonText, QBrush(Qt::white));
        ui->pushButton_Start->setPalette(palette);

        if (stopwatch_isStarted == 0) {
            timer_2->start();
            stopwatch_isStarted = 1;
        }
        timer->start();
        isStarted=1;
        if (!stopwatch_Animation) {
            stopwatchStartAnimation();
            stopwatch_Animation = 1;
        }
    } else {
        timer->stop();
        /*查询间隔计时器是否启动
         Query whether the interval timer starts*/
        if (stopwatch_isStarted == 1) {
            timer_2->stop();
            stopwatch_isStarted = 0;
        }
        isStarted=0;
        ui->pushButton_timeselect->show();
        ui->pushButton_Start->setText(tr("Continue"));
    }
    return;
}

/*
 *倒计时标签动画移动
 *Countdown start animation move
 */
void Clock::stopwatchStartAnimation()
{
    animation1 = new QPropertyAnimation(ui->label_4, "geometry");
    animation1->setDuration(1000);
    animation1->setKeyValueAt(0, QRect(122, 136, 210, 61));
    animation1->setEndValue(QRect(122, 36, 210, 61));
    animation1->start();

    animation2 = new QPropertyAnimation(ui->label_5, "geometry");
    animation2->setDuration(1000);
    animation2->setKeyValueAt(0, QRect(177, 210, 100, 20));
    animation2->setEndValue(QRect(177, 110, 100, 20));
    animation2->start();

    animation3 = new QPropertyAnimation(ui->listWidget_2, "geometry");
    animation3->setDuration(1000);
    animation3->setKeyValueAt(0, QRect(39 ,230, 376, 287));
    animation3->setEndValue(QRect(39, 130, 376, 287));
    animation3->start();
}
/*
 * 倒计时开始动画移动
 * Countdown start animation move
 */
void Clock::stopwatchStopAnimation()
{
    animation1 = new QPropertyAnimation(ui->label_4, "geometry");
    animation1->setDuration(1000);
    animation1->setKeyValueAt(0, QRect(122, 36, 210, 61));
    animation1->setEndValue(QRect(122, 136, 210, 61));
    animation1->start();

    animation2 = new QPropertyAnimation(ui->label_5, "geometry");
    animation2->setDuration(1000);
    animation2->setKeyValueAt(0, QRect(177, 110, 100, 20));
    animation2->setEndValue(QRect(177, 210, 100, 20));
    animation2->start();

    animation3 = new QPropertyAnimation(ui->listWidget_2, "geometry");
    animation3->setDuration(1000);
    animation3->setKeyValueAt(0, QRect(39 ,130, 376, 251));
    animation3->setEndValue(QRect(39, 230, 376, 251));
    animation3->start();
}

/*
 * 计次
 * times count
 */
void Clock::onPushbuttonRingClicked()
{
    if (!isStarted) {
        return;
    }

    if (stopwatch_isStarted == 0) {
        timer_2->start();
        stopwatch_isStarted = 1;
    }
    if (stopwatch_item_flag < 100) {
        stopwatch_aItem[stopwatch_item_flag] =new QListWidgetItem;
        stopwatch_aItem[stopwatch_item_flag]->setSizeHint(QSize(376,56));
        stopwatch_aItem[stopwatch_item_flag]->setTextColor(QColor(255, 0, 0, 255));
        ui->listWidget_2->insertItem(0,stopwatch_aItem[stopwatch_item_flag]);

        ui->listWidget_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->listWidget_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        stopwatch_w[stopwatch_item_flag] = new stopwatch_item(ui->listWidget_2);

        stopwatch_w[stopwatch_item_flag]->stopwatch1->setText(tr("count")+QString::number(stopwatch_item_flag+1));
        stopwatch_w[stopwatch_item_flag]->stopwatch2->setText(tr("interval ")+stopwatch_jg_h+":"+stopwatch_jg_m+"."+stopwatch_jg_s);
        stopwatch_w[stopwatch_item_flag]->stopwatch3->setText(stopwatch_h+":"+stopwatch_m+"."+stopwatch_s);

        ui->listWidget_2->setItemWidget(stopwatch_aItem[stopwatch_item_flag],stopwatch_w[stopwatch_item_flag]);

        stopwatch_hour = 0;
        stopwatch_minute = 0;
        stopwatch_second = 0;

        stopwatch_item_flag++;
    }
}

/*
 *复位
 *reset
 */
void Clock::onPushbuttonTimeselectClicked()
{
    if (nullptr != timer) {
        if (isStarted)
            return;
        ui->pushButton_timeselect->setEnabled(false);
        ui->pushButton_ring->setEnabled(false);
        timer->stop();
        timer_2->stop();
        ui->label_4->setText("00:00.00");
        ui->label_5->setText("00:00.00");
        isStarted = 0;
        stopwatch_isStarted = 0;
        hour = 0; minute = 0;second = 0;
        stopwatch_hour = 0;
        stopwatch_minute = 0;
        stopwatch_second = 0;
        ui->pushButton_Start->setText(tr("start"));

        QPalette palette = ui->pushButton_Start->palette();
        QColor ColorPlaceholderText(61,107,229,255);
        QBrush brush2;
        brush2.setColor(ColorPlaceholderText);
        palette.setColor(QPalette::Button,QColor(61,107,229,255));
        palette.setBrush(QPalette::ButtonText, QBrush(Qt::white));
        ui->pushButton_Start->setPalette(palette);


        for (int i=0; i < stopwatch_item_flag; i++) {
            delete stopwatch_w[i];
            delete stopwatch_aItem[i];
        }
        stopwatch_item_flag = 0;
        if (stopwatch_Animation) {
            stopwatchStopAnimation();
            stopwatch_Animation = 0;
        }
    }
}

/*
 * 窗口关闭
 * window closing
 */
void Clock::windowClosingClicked()
{
    QPointF position = this->pos();
    close_or_hide_page->move(position.x()+67,position.y()+250);
    close_or_hide_page->exec();

    if(close_or_hide_page->close_flag==1){
        exit(0);
    }else if(close_or_hide_page->close_flag==2){
        this->hide();
        close_or_hide_page->close_flag = 0;
    }
}

/*
 *窗口最小化
 *window minimizing
 */
void Clock::windowMinimizingClicked()
{
    this->showNormal();
    this->showMinimized();
}

/*
 * 倒计时切换
 * Countdown switch
 */
void Clock:: CountdownPageSwitch ()
{
    ui->stackedWidget->setCurrentIndex(0);

    QPalette palette = pushcount->palette();
    QColor ColorPlaceholderText(61,107,229,255);
    QBrush brush2;
    brush2.setColor(ColorPlaceholderText);
    palette.setColor(QPalette::Button,QColor(61,107,229,255));
    pushcount->setPalette(palette);

    QPalette palette1 = pushclock->palette();
    QColor ColorPlaceholderText2(255,255,255,0);
    QBrush brush;
    brush.setColor(ColorPlaceholderText2);
    palette1.setBrush(QPalette::Button, brush);
    pushclock->setPalette(palette1);
    pushstop->setPalette(palette1);

}

/*
 * 闹钟窗口切换
 * Alarm window switchin
 */
void Clock:: AlarmPageSwitch ()
{
    ui->stackedWidget->setCurrentIndex(1);

    QPalette palette = pushclock->palette();
    QColor ColorPlaceholderText(61,107,229,255);
    QBrush brush2;
    brush2.setColor(ColorPlaceholderText);
    palette.setColor(QPalette::Button,QColor(61,107,229,255));
    pushclock->setPalette(palette);

    QPalette palette1 = pushcount->palette();
    QColor ColorPlaceholderText2(255,255,255,0);
    QBrush brush;
    brush.setColor(ColorPlaceholderText2);
    palette1.setBrush(QPalette::Button, brush);
    pushcount->setPalette(palette1);
    pushstop->setPalette(palette1);

}

/*
 * 秒表窗口切换
 * Stopwatch window switch
 */
void Clock:: StopwatchPageSwitch ()
{
    ui->stackedWidget->setCurrentIndex(2);

    QPalette palette = pushstop->palette();
    QColor ColorPlaceholderText(61,107,229,255);
    QBrush brush2;
    brush2.setColor(ColorPlaceholderText);
    palette.setColor(QPalette::Button,QColor(61,107,229,255));
    //palette.setBrush(QPalette::ButtonText, QBrush(Qt::white));
    pushstop->setPalette(palette);

    QPalette palette1 = pushclock->palette();
    QColor ColorPlaceholderText2(255,255,255,0);
    QBrush brush;
    brush.setColor(ColorPlaceholderText2);
    palette1.setBrush(QPalette::Button, brush);
    pushclock->setPalette(palette1);
    pushcount->setPalette(palette1);

}

/*
 * 闹钟上方电子表
 * Electronic watch above alarm clock
 */
void Clock::textTimerupdate()
{
    QProcess process;
    process.start("gsettings get org.ukui.control-center.panel.plugins hoursystem");
    process.waitForFinished();
    QByteArray output = process.readAllStandardOutput();
    QString str_output = output;
    int rowNum = model->rowCount();

    model_setup->select();
    QTime time = QTime::currentTime();
    int time_H = time.hour();
    int time_M = time.minute();
    int time_S = time.second();

    if(model_setup->index(0, 2).data().toInt() == 1){
        ui->label_6->setText(changeNumToStr(time_H)+":"+changeNumToStr(time_M)+":"+changeNumToStr(time_S));
        ui->label_15->setText("");
        if(system_time_flag == 0){
            system_time_flag = 1;
            for (int i = 0; i < rowNum; i++) {
                delete aItem[i];
                delete w1[i];
            }
            updateAlarmClock();
        } else {
            system_time_flag = 1;
        }
    } else if (model_setup->index(0, 2).data().toInt() == 2) {
        if (time_H >=12) {
            ui->label_6->setText(changeNumToStr(time_H - 12)+":"+changeNumToStr(time_M)+":"+changeNumToStr(time_S));
            ui->label_15->setText(tr("PM"));
        } else {
            ui->label_6->setText(changeNumToStr(time_H)+":"+changeNumToStr(time_M)+":"+changeNumToStr(time_S));
            ui->label_15->setText(tr("AM"));
        }

        if(time_H == 0)
            ui->label_6->setText(changeNumToStr(12)+":"+changeNumToStr(time_M)+":"+changeNumToStr(time_S));

        if(time_H == 12)
            ui->label_6->setText(changeNumToStr(time_H)+":"+changeNumToStr(time_M)+":"+changeNumToStr(time_S));


        if (system_time_flag == 1) {
            system_time_flag = 0;
            for(int i=0; i<rowNum; i++) {
                delete aItem[i];
                delete w1[i];
            }
            updateAlarmClock();
        } else {
            system_time_flag = 0;
        }
    } else {
        if (str_output.compare("'24'\n") == 0) {
            ui->label_6->setText(changeNumToStr(time_H)+":"+changeNumToStr(time_M)+":"+changeNumToStr(time_S));
            ui->label_15->setText("");
            if (system_time_flag == 0) {
                system_time_flag = 1;
                for(int i = 0; i < rowNum; i++) {
                    delete aItem[i];
                    delete w1[i];
                }
                updateAlarmClock();
            } else {
                system_time_flag = 1;
            }
        } else {
            if (time_H >= 12) {
                ui->label_6->setText(changeNumToStr(time_H - 12)+":"+changeNumToStr(time_M)+":"+changeNumToStr(time_S));
                ui->label_15->setText(tr("PM"));
            } else {
                ui->label_6->setText(changeNumToStr(time_H)+":"+changeNumToStr(time_M)+":"+changeNumToStr(time_S));
                ui->label_15->setText(tr("AM"));
            }

            if(time_H == 0)
                ui->label_6->setText(changeNumToStr(12)+":"+changeNumToStr(time_M)+":"+changeNumToStr(time_S));

            if(time_H == 12)
                ui->label_6->setText(changeNumToStr(time_H)+":"+changeNumToStr(time_M)+":"+changeNumToStr(time_S));

            if (system_time_flag == 1) {
                system_time_flag = 0;
                for (int i = 0; i < rowNum; i++) {
                    delete aItem[i];
                    delete w1[i];
                }
                updateAlarmClock();
            } else {
                system_time_flag = 0;
            }
        }
    }
}

/*
 * 动态监控闹钟与本地时间
 * Dynamic monitoring alarm clock and local time
 */
void Clock::timerUpdate()
{
    QTime time = QTime::currentTime();
    int timeH = time.hour();
    int timeM = time.minute();
    int timeS = time.second();

    model_setup->select();
    textTimerupdate();

    int rowNum = model->rowCount();
    for (int i = 0; i < rowNum; i++) {
        /*判断星期
         Judgment week*/
        QDateTime current_date_time = QDateTime::currentDateTime();

        if (current_date_time.toString("ddd").compare("周一")==0 &&  model->index(i, 6).data().toInt() == 0)
             continue;
         if (current_date_time.toString("ddd").compare("周二")==0 &&  model->index(i, 7).data().toInt() == 0)
             continue;
         if (current_date_time.toString("ddd").compare("周三")==0 &&  model->index(i, 8).data().toInt() == 0)
             continue;
         if (current_date_time.toString("ddd").compare("周四")==0 &&  model->index(i, 9).data().toInt() == 0)
             continue;
         if (current_date_time.toString("ddd").compare("周五")==0 &&  model->index(i, 10).data().toInt() == 0)
             continue;
         if (current_date_time.toString("ddd").compare("周六")==0 &&  model->index(i, 11).data().toInt() == 0)
             continue;
         if (current_date_time.toString("ddd").compare("周日")==0 &&  model->index(i, 12).data().toInt() == 0)
             continue;

        /*判断开关
         Judgment switch*/
        if ( model->index(i, 3).data().toInt() == 1)
            continue;
        if (timeH == model->index(i, 0).data().toInt()
                && timeM == model->index(i, 1).data().toInt()
                && timeS == 0) {
            double music_time = 30;
            if (model->index(i, 13).data().toString().compare(tr("2min"))==0) {
                music_time = 2*60;
            } else if (model->index(i, 13).data().toString().compare(tr("3min"))==0) {
                music_time = 3*60;
            } else if (model->index(i, 13).data().toString().compare(tr("4min"))==0) {
                music_time = 4*60;
            } else if (model->index(i, 13).data().toString().compare(tr("6min"))==0) {
                music_time = 6*60;
            } else {
                music_time = 60;
            }
            noticeDialogShow(music_time, i );
            if(model->index(i, 5).data().toString().compare(tr("No repetition"))==0)
                offAlarm(i);
        }
    }
    update();
}

/*
 * 通知弹窗
 * Notification Popup
 */
void Clock::noticeDialogShow(int close_time, int alarm_num)
{
    model_setup->select();
    int hour_now = model->index(alarm_num, 0).data().toInt();
    int min_now = model->index(alarm_num, 1).data().toInt();
    QScreen *screen=QGuiApplication::primaryScreen ();
    QRect mm=screen->availableGeometry() ;
    int screen_width = mm.width();
    int screen_height = mm.height();
    Natice_alarm  *dialog1 = new Natice_alarm(close_time,alarm_num);
    dialog1->ui->label_2->setText(model->index(alarm_num, 14).data().toString());
    if (system_time_flag) {
        dialog1->ui->label_3->setText(changeNumToStr(hour_now)+" : "+changeNumToStr(min_now));
    } else {
        if (hour_now >= 12) {
            if (hour_now == 12) {
                dialog1->ui->label_3->setText(tr("PM")+" "+changeNumToStr(hour_now)+" : "+changeNumToStr(min_now));
            } else {
                dialog1->ui->label_3->setText(tr("PM")+" "+changeNumToStr(hour_now-12)+" : "+changeNumToStr(min_now));
            }
        } else {
            if (hour_now == 0){
                dialog1->ui->label_3->setText(tr("AM")+" "+changeNumToStr(12)+" : "+changeNumToStr(min_now));
            } else {
                dialog1->ui->label_3->setText(tr("AM")+" "+changeNumToStr(hour_now)+" : "+changeNumToStr(min_now));
            }
        }
    }
    dialog1->ui->label_4->setText(QString::number(close_time)+tr(" Seconds to close"));
    if (model_setup->index(0, 3).data().toInt()) {
        dialog1->showFullScreen();
    } else {
        dialog1->move(screen_width-450,screen_height-300);
    }
    dialog1->show();
}

/*
 *重绘窗口，更新闹钟
 *Redraw window, update alarm clock
 */
void Clock::updateAlarmClock()
{
    int rowNum = model->rowCount();
    int hour_now;
    int min_now;

    for (int alarmNum = 0; alarmNum < rowNum; alarmNum++) {
        aItem[alarmNum] =new QListWidgetItem;
        aItem[alarmNum]->setSizeHint(QSize(376,58));
        aItem[alarmNum]->setTextColor(QColor(255, 0, 0, 255));
        ui->listWidget->addItem(aItem[alarmNum]);
        ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        w1[alarmNum] = new item_new(ui->listWidget);
        ui->listWidget->setItemWidget(aItem[alarmNum],w1[alarmNum]);

        hour_now = model->index(alarmNum, 0).data().toInt();
        min_now = model->index(alarmNum, 1).data().toInt();

        if (system_time_flag) {
            changeTimeNum(hour_now,min_now);//转换int为QString
                                              // Convert int to qstring
            w1[alarmNum]->alarmLabel0->setText(alarmHour_str+" : "+alarmMinute_str);
            w1[alarmNum]->alarmLabel1->hide();
        } else {
            if (hour_now >= 12) {
                w1[alarmNum]->alarmLabel1->setText(tr("PM"));
                if (hour_now == 12) {
                    w1[alarmNum]->alarmLabel0->setText(changeNumToStr(hour_now)+" : "+changeNumToStr(min_now));
                } else {
                    w1[alarmNum]->alarmLabel0->setText(changeNumToStr(hour_now-12)+" : "+changeNumToStr(min_now));
                }
            } else {
                w1[alarmNum]->alarmLabel1->setText(tr("AM"));
                if (hour_now == 0) {
                    w1[alarmNum]->alarmLabel0->setText(changeNumToStr(12)+" : "+changeNumToStr(min_now));
                } else {
                    w1[alarmNum]->alarmLabel0->setText(changeNumToStr(hour_now)+" : "+changeNumToStr(min_now));
                }
            }
        }
        /*闹钟开关
         Alarm switch*/
        if (model->index(alarmNum, 3).data().toInt() == 1) {
            w1[alarmNum]->alarm_on_off0->setStyleSheet("border-image: url(:/alarm_off.png); border-radius:7px;");
        } else {
            w1[alarmNum]->alarm_on_off0->setStyleSheet("border-image: url(:/alarm_on.png); border-radius:7px;");
        }
        w1[alarmNum]->alarmLabel_w0->setText(model->index(alarmNum, 14).data().toString());


        QString werk_str =  model->index(alarmNum, 5).data().toString();
        QString werk_day ;
        int werk = 0;
        for (int i=0; i<7; i++) {
            if (model->index(alarmNum, 6+i).data().toInt()) {
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
        if(werk){
            w1[alarmNum]->alarmLabel_s0->setText(werk_day);
        }else {
            if(werk_str == tr("Every day") || werk_str == "每天"){
                w1[alarmNum]->alarmLabel_s0->setText(tr("Every day"));
            }else if(werk_str == "Workingday" || werk_str == "工作日"){
                w1[alarmNum]->alarmLabel_s0->setText(tr("Workingday"));
            }else if(werk_str == "No repetition" || werk_str == "不重复"){
                w1[alarmNum]->alarmLabel_s0->setText(tr("No repetition"));
            }
        }
        connect( w1[alarmNum]->alarm_on_off0, SIGNAL(clicked()), this, SLOT(OnOffAlarm()) );
    }
}

/*
 * 修改时间单数 为两位数
 * Modify time singular to two digits
 */
void Clock::changeTimeNum(int alarmHour, int alarmMinute)
{
    if (alarmHour < 10) {
        QString hours_str = QString::number(alarmHour);
        alarmHour_str = "0"+hours_str;
    } else {
        alarmHour_str = QString::number(alarmHour);
    }
    if (alarmMinute < 10) {
        QString minute_str = QString::number(alarmMinute);
        alarmMinute_str = "0"+minute_str;
    } else {
        alarmMinute_str = QString::number(alarmMinute);
    }
}

void Clock::cancelAlarmClock()
{
    dialog->close();
}

/*
 * 停止音乐
 * Stop music
 */
void Clock::stopPlayMusic()
{
    player->stop();
}

/*
 * 选择音乐
 * Choose music
 */
void Clock::ChooseAlarmMusic()
{
    musicPath = QFileDialog::getOpenFileName(this, "选择铃声",
                                             "G:/歌曲", "*.mp3");
}
/*
 * 播放音乐
 * Play music
 */
void Clock::rePlayMusic()
{
    player->play();
}

/*
 * 增加item
 * Add item
 */
void Clock::aitemNew()
{
    int rowNum = model->rowCount();
    aItem[rowNum] =new QListWidgetItem;
    aItem[rowNum]->setSizeHint(QSize(376,56));
    aItem[rowNum]->setTextColor(QColor(255, 0, 0, 255));
    ui->listWidget->addItem(aItem[rowNum]);
    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    w1[rowNum] = new item_new(ui->listWidget);
    ui->listWidget->setItemWidget(aItem[rowNum],w1[rowNum]);
}

/*
 * 新建闹钟按钮回调
 * New alarm button callback
 */
void Clock::setAlarmClock()
{
    ui->set_page->show();
    ui->set_page->raise();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();
    ui->set_alarm_savebtn->show();
    ui->set_alarm_cancelbtn->show();
    timer_set_page->start();
    ui->label_13->setText(tr("New alarm"));
    repeat_new_or_edit_flag = 0;

    model_setup->select();/*调用默认设置
                           Call default settings*/
    repeat_str_model = tr("Workingday");
    repeat_sel->textLabel->setText(repeat_str_model+tr("(default)"));
    for (int i=0; i<7; i++) {
        repeat_day[i] = model_setup->index(0, i+7).data().toInt();
    }
    time_music_str_model = tr("2min");
    ring_sel->textLabel->setText(time_music_str_model+tr("(default)"));

    music_str_model = model_setup->index(0, 5).data().toString();
    if(music_str_model == "glass" || "玻璃"){
        music_str_model = tr("glass");
    }else if(music_str_model == "bark" || "犬吠"){
        music_str_model = tr("bark");
    }else if(music_str_model == "sonar" || "声呐"){
        music_str_model = tr("sonar");
    }else if(music_str_model == "drip" || "雨滴"){
        music_str_model = tr("drip");
    }

    time_sel->textLabel->setText(music_str_model+tr("(default)"));
    clock_name = tr("Alarm");
    ui->lineEdit->setText(clock_name);
}

/*
 * 闹钟新建界面保存回调
 * Alarm new interface save callback
 */
void Clock::setAlarmSave()
{
    ui->lineEdit->setText(ui->lineEdit->text().remove(QRegExp("\\s")));//去除所以空格
    if(ui->lineEdit->text().isEmpty()){
        delete_msg *deletemsg = new delete_msg();
        deletemsg->ui->label_5->setText(tr("Please set alarm name!"));
        QPointF position = this->pos();
        deletemsg->move(position.x()+67,position.y()+250);
        deletemsg->exec();
        return ;
    }
    int rowNum;
    rowNum = model->rowCount();

    qDebug() << rowNum << "闹钟数";
    if (rowNum < 20) {
        model->insertRow(rowNum);
        model->setData(model->index(rowNum, 0), timer_alarm_start24->m_currentValue);
        model->setData(model->index(rowNum, 1), timer_alarm_start60->m_currentValue);
        model->setData(model->index(rowNum, 2), music_str_model);
        model->setData(model->index(rowNum, 3), int(0));
        model->setData(model->index(rowNum, 4), int(model->index(rowNum-1, 4).data().toInt()+1));
        model->setData(model->index(rowNum, 5), repeat_str_model);
        model->setData(model->index(rowNum, 13), time_music_str_model);
        model->setData(model->index(rowNum, 14), ui->lineEdit->text());
        qDebug() << repeat_str;

        for (int i=0; i<7; i++) {
            model->setData(model->index(rowNum, i+6), repeat_day[i]);
        }

        model->submitAll();

        for (int i=0; i<rowNum; i++) {
            delete aItem[i];
            delete w1[i];
        }
        qDebug() << model->index(rowNum, 0).data().toString()
                 << model->index(rowNum, 1).data().toString()
                 << QFileInfo( model->index(rowNum, 2).data().toString() ).fileName();
        updateAlarmClock();
    } else {
        QMessageBox::warning(this, "警告", "闹钟数量已达上限！", QMessageBox::Yes);
    }
    ui->stackedWidget_3->raise();
    ui->set_page->hide();
    ui->stackedWidget->raise();//将页面放置最前方
                               // Put the page at the front
    ui->pushButton_4->raise();
    ui->pushButton_5->raise();
    ui->pushButton_12->raise();
    timer_set_page->stop();

    if (dialog_repeat)
        dialog_repeat->close();
    if (dialog_music)
        dialog_music->close();
    if (time_music)
        time_music->close();
}

/*
 * 闹钟新建与重编辑界面剩余时间显示
 * Alarm clock new and re edit interface remaining time real-time display callback
 */
void Clock::verticalscrollRingTime()
{
    int x_h, x_m ;

    QTime time = QTime::currentTime();
    int timeH = time.hour();
    int timeM = time.minute();

    int hour_time = timer_alarm_start24->m_currentValue;
    int minute_time= timer_alarm_start60->m_currentValue;

    if (hour_time > timeH) {
        x_h = hour_time - timeH;
    } else {
        x_h = hour_time + 24 - timeH;
    }

    if (minute_time > timeM) {
        x_m = minute_time - timeM;
    } else {
        x_m = minute_time + 60 - timeM;
        x_h --;
    }
    if (x_m == 60) {
        x_m = 0;
        x_h++;
    }
    if (x_h == 24) {
        x_h = 0;
    }
    ui->label_12->setText(QString::number(x_h)+tr("hour ")+QString::number(x_m)+tr(" min bell rings"));
}

/*
 *闹钟新建界面取消回调
 * Cancel callback in alarm new interface
 */
void Clock::alarmCancelSave()
{
    ui->stackedWidget_3->raise();
    ui->set_page->hide();
    ui->stackedWidget->raise();
    timer_set_page->stop();
    ui->pushButton_4->raise();
    ui->pushButton_5->raise();
    ui->pushButton_12->raise();
}

/*
 * 双击闹钟打开重编辑页面
 * Double click the alarm clock to open the re edit page
 */
void Clock::listdoubleClickslot()
{
    ui->set_page->show();
    ui->pushButton_8->show();
    ui->pushButton_9->show();
    ui->set_alarm_savebtn->hide();
    timer_alarm_start24->m_currentValue=model->index(ui->listWidget->currentRow(), 0).data().toInt();
    timer_alarm_start60->m_currentValue=model->index(ui->listWidget->currentRow(), 1).data().toInt();
    ui->set_page->raise();
    timer_set_page->start();
    ui->label_13->setText(tr("Edit alarm clock"));
    repeat_new_or_edit_flag = 1;

    int num = ui->listWidget->currentRow();

    qDebug() << num  <<model->index(num, 5).data().toString();
    qDebug() << num  <<model->index(num, 2).data().toString();
    QString werk_day ;
    int werk = 0;
    for (int i=0; i<7; i++) {
        if (model->index(num, 6+i).data().toInt()) {
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
    if(werk){
        repeat_sel->textLabel->setText(werk_day);
    }else {
        repeat_sel->textLabel->setText(tr("Every day"));
    }
    if(model->index(num, 5).data().toString() == tr("  work") || model->index(num, 5).data().toString() == tr("  工作日")){
        repeat_sel->textLabel->setText(tr("  work"));
    }
    if(model->index(num, 5).data().toString() == tr("No repetition") || model->index(num, 5).data().toString() == tr("不重复")){
        repeat_sel->textLabel->setText(tr("No repetition"));
    }
    repeat_str_model = model->index(num, 5).data().toString();



    music_str_model =  model->index(num, 2).data().toString();
    if(music_str_model == "glass" || "玻璃"){
        music_str_model = tr("glass");
    }else if(music_str_model == "bark" || "犬吠"){
        music_str_model = tr("bark");
    }else if(music_str_model == "sonar" || "声呐"){
        music_str_model = tr("sonar");
    }else if(music_str_model == "drip" || "雨滴"){
        music_str_model = tr("drip");
    }
    time_sel->textLabel->setText(music_str_model);


    time_music_str_model = model->index(num, 13).data().toString();

    if(time_music_str_model == "2min" || "2分钟"){
        time_music_str_model = tr("2min");
    }else if(time_music_str_model == "3min" || "3分钟"){
        time_music_str_model = tr("3min");
    }else if(time_music_str_model == "4min" || "4分钟"){
        time_music_str_model = tr("4min");
    }else if(time_music_str_model == "6min" || "6分钟"){
        time_music_str_model = tr("6min");
    }
    ring_sel->textLabel->setText(time_music_str_model);
    time_music_str_model = model->index(num, 13).data().toString();


    clock_name = model->index(num, 14).data().toString();
    ui->lineEdit->setText(clock_name);


    for (int i=0; i<7; i++) {
        if (model->index(num, 6+i).data().toInt()) {
            repeat_day[i] = 1;
        } else {
            repeat_day[i] = 0;
        }
    }
}

/*
 * 闹钟重编辑保存回调
 * Alarm re edit save callback
 */
void Clock::alarmReEditClicked()
{
    if(ui->lineEdit->text().isEmpty()){
        delete_msg *deletemsg = new delete_msg();
        deletemsg->ui->label_5->setText(tr("Please set alarm name!"));
        QPointF position = this->pos();
        deletemsg->move(position.x()+67,position.y()+250);
        deletemsg->exec();
        return ;
    }

    int rowNum = ui->listWidget->currentRow();

    qDebug() << rowNum << "要修改的闹钟号"<<music_str_model;

    model->setData(model->index(rowNum, 0), timer_alarm_start24->m_currentValue);
    model->setData(model->index(rowNum, 1), timer_alarm_start60->m_currentValue);
    model->setData(model->index(rowNum, 2), music_str_model);
    model->setData(model->index(rowNum, 5), repeat_str_model);
    model->setData(model->index(rowNum, 13), time_music_str_model);
    model->setData(model->index(rowNum, 14), ui->lineEdit->text());

    for (int i=0; i<7; i++) {
        if (repeat_day[i]) {
            model->setData(model->index(rowNum, i+6), 1);
        } else {
            model->setData(model->index(rowNum, i+6), 0);
        }
    }
    model->submitAll();
    int m = model->rowCount();
    /*每次updateAlarmClock()之前，删除全部闹钟相关控件
      Delete all alarm related controls before updatealrmclock()*/
    for (int i = 0; i < m; i++) {
        delete aItem[i];
        delete w1[i];
    }

    qDebug() << model->index(rowNum, 0).data().toString()
             << model->index(rowNum, 1).data().toString()
             << QFileInfo( model->index(rowNum, 2).data().toString() ).fileName();

    updateAlarmClock();

    ui->stackedWidget_3->raise();
    ui->set_page->hide();
    ui->stackedWidget->raise();/*将页面放置最前方
                                Put the page at the front*/
    ui->pushButton_4->raise();
    ui->pushButton_5->raise();
    ui->pushButton_12->raise();
    timer_set_page->stop();

    if (dialog_repeat)
        dialog_repeat->close();

    if (dialog_music)
        dialog_music->close();

    if(time_music)
        time_music->close();
}


/*
 * 单击闹钟显示铃声剩余时间
 *Click the alarm to display the remaining time
 */
void Clock::listClickslot()
{
    timer_Surplus->start();
    int x_h, x_m ;
    int num=ui->listWidget->currentRow();
    int day_next;
    if(num >= 0){
        day_next = getAlarmClockWillRingDays(num); /*获取下次响铃天数*/
    }

    QTime time = QTime::currentTime();
    int timeH = time.hour();
    int timeM = time.minute();
    int day_true;
    int hour_time = model->index(num, 0).data().toInt();
    int minute_time= model->index(num, 1).data().toInt();
    if(last_day_ring == 1 && hour_time>=timeH ){              /*如果天数是下一天响，判断当天是否*/
        if(hour_time == timeH && minute_time <= timeM ){
            ;
        }else{
            day_true = getAlarmClockWillRingDays_2(num);
            if(day_true){
                day_next=0;
            }
        }
    }else{
        if(hour_time>=timeH){
            if(hour_time == timeH && minute_time <= timeM){
                ;
            }else{
                if(getAlarmClockWillRingDays_2(num))
                {
                    day_next=0;
                }
            }
        }
    }

    if (hour_time == timeH && day_next == 7) {
        if (minute_time > timeM)
            day_next = 0;
    }

        x_h = hour_time + 24*day_next - timeH;

    if (minute_time > timeM) {
        x_m = minute_time - timeM;
    } else {
        x_m = minute_time + 60 - timeM;
        x_h --;
    }

    if (x_m == 60) {
        x_m = 0;
        x_h++;
    }
    if(x_h<0){
        x_h=x_h+24;
    }
    if (x_h >= 24) {
        day_next = x_h/24;

        x_h = x_h % 24;
        if(day_next >= 7){
            day_next = 0;
        }
    } else {
        day_next = 0;
    }

    if (num < 0) {
        ui->label_7->setText(tr("Remaining time"));
    } else {
        if (day_next) {
           ui->label_7->setText(QString::number(day_next)+tr(" days ")+QString::number(x_h)+tr(" hour ")+QString::number(x_m)+tr(" min bell rings"));
        } else {
           ui->label_7->setText(QString::number(x_h)+tr(" hour ")+QString::number(x_m)+tr(" min bell rings"));
        }
    }
    if (!(model->rowCount())) {
        ui->label_7->setText("");
    }
    if (model->index(num, 3).data().toInt()){
        ui->label_7->setText(tr("Remaining time"));
    }
}


/*
 * 计算下次闹钟响起天数间隔
 * Calculate the next alarm ring interval
 */
int Clock::getAlarmClockWillRingDays(int num)
{
    int ring_day[7];
    int today ;
    int interval = 1;
    for (int i = 0; i < 7; i++) {
        ring_day[i] = model->index(num, i+6).data().toInt();
    }
    /*判断星期
     Judgment week*/
    QDateTime current_date_time = QDateTime::currentDateTime();

    if(current_date_time.toString("ddd").compare("周一")==0 )
        today = 0;
    else if(current_date_time.toString("ddd").compare("周二")==0 )
        today = 1;
    else if(current_date_time.toString("ddd").compare("周三")==0 )
        today = 2;
    else if(current_date_time.toString("ddd").compare("周四")==0 )
        today = 3;
    else if(current_date_time.toString("ddd").compare("周五")==0 )
        today = 4;
    else if(current_date_time.toString("ddd").compare("周六")==0 )
        today = 5;
    else if(current_date_time.toString("ddd").compare("周日")==0 )
        today = 6;

    for (int i = today+1; i < 7; i++) {
        if (ring_day[i] == 1) {
            last_day_ring = 1;
            interval = i - today;
            return interval;
        }
    }
    for (int i = 0; i<today+1; i++) {
        if (ring_day[i] == 1) {
            last_day_ring = 0;
            interval = 7 - today + i;
            return interval;
        }
    }
}

int Clock::getAlarmClockWillRingDays_2(int num)
{
    int ring_day[7];
    int today ;
    for (int i = 0; i < 7; i++) {
        ring_day[i] = model->index(num, i+6).data().toInt();
    }
    /*判断星期
     Judgment week*/
    QDateTime current_date_time = QDateTime::currentDateTime();

    if(current_date_time.toString("ddd").compare("周一")==0 )
        today = 0;
    else if(current_date_time.toString("ddd").compare("周二")==0 )
        today = 1;
    else if(current_date_time.toString("ddd").compare("周三")==0 )
        today = 2;
    else if(current_date_time.toString("ddd").compare("周四")==0 )
        today = 3;
    else if(current_date_time.toString("ddd").compare("周五")==0 )
        today = 4;
    else if(current_date_time.toString("ddd").compare("周六")==0 )
        today = 5;
    else if(current_date_time.toString("ddd").compare("周日")==0 )
        today = 6;

        if (ring_day[today] == 1) {
            return 1;
        }else{
            return 0;
        }
}

/*
 * 闹钟重编辑页面删除闹钟回调
 * Alarm re edit page delete alarm callback
 */
void Clock::deleteAlarm()
{
    int num=ui->listWidget->currentRow();
    int rowNum = model->rowCount();
    model->removeRows(num, 1);
    qDebug() << "delete " <<num <<rowNum;

    delete_msg *deletemsg = new delete_msg();
    QPointF position = this->pos();
    deletemsg->move(position.x()+67,position.y()+250);
    deletemsg->exec();

    if (!(deletemsg->close_sure)) {
        model->revertAll();/*如果不删除, 则撤销
                             If not deleted, undo*/
        qDebug() << rowNum;
    } else {
        for (int i=0; i<rowNum; i++) {
            delete w1[i];
            delete aItem[i];
        }
        model->submitAll(); /*否则提交, 在数据库中删除该行
                             *Otherwise commit, delete the row in the database*/
        updateAlarmClock();
        rowNum = model->rowCount();
        qDebug() << rowNum;

        ui->stackedWidget_3->raise();
        ui->set_page->hide();
        ui->stackedWidget->raise();/*将页面放置最前方
                                     Put the page at the front*/
        ui->pushButton_4->raise();
        ui->pushButton_5->raise();
        ui->pushButton_12->raise();
    }
    timer_set_page->stop();
}

/*
 * 闹钟开关
 * Alarm switch
 */
void Clock::OnOffAlarm()
{
    int i=0 ;
    QPushButton *btn = qobject_cast<QPushButton*>(QObject::sender());
    while (btn != w1[i]->alarm_on_off0) {
        i++;
    }
    if (model->index(i, 3).data().toInt() == 0) {
        btn->setStyleSheet("border-image: url(:/alarm_off.png);border-radius:7px;");
        qDebug() << "off";

        model->setData(model->index(i, 3), int(1));
        model->submitAll();
    } else {
        btn->setStyleSheet("border-image: url(:/alarm_on.png);border-radius:7px;");
        qDebug() << "on";

        model->setData(model->index(i, 3), int(0));
        model->submitAll();
    }
}
/*
 * 不重复时单独关闭闹钟
 * Turn off the alarm separately if it is not repeated
 */
void Clock::offAlarm(int i)
{
    w1[i]->alarm_on_off0->setStyleSheet("border-image: url(:/alarm_off.png);border-radius:7px;");
    qDebug() << "on";

    model->setData(model->index(i, 3), int(1));
    model->submitAll();

    int rowNum = model->rowCount();
    for (int i = 0; i < rowNum; i++) {
        delete aItem[i];
        delete w1[i];
    }
    updateAlarmClock();
}

/*
 * 倒计时音乐选择
 * Countdown music selection
 */
void Clock::countdownMusicSellect()
{
        QPointF position = this->pos();
        count_music_sellect->move(position.x()+89,position.y()+481);
        count_music_sellect->resize(280,141);
        count_music_sellect->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
        count_music_sellect->setAttribute(Qt::WA_TranslucentBackground);
        count_music_sellect->listWidget->setFixedSize(280,141);
        count_music_sellect->widget[0]->alarmLabel0->setText(tr("glass"));
        count_music_sellect->widget[1]->alarmLabel0->setText(tr("bark"));
        count_music_sellect->widget[2]->alarmLabel0->setText(tr("sonar"));
        count_music_sellect->widget[3]->alarmLabel0->setText(tr("drip"));
        count_music_sellect->show();

        connect(count_music_sellect->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(countMusicListclickslot()));
}
/*
 * 倒计时音乐选择单机回调
 * Countdown music selection single callback
 */
void Clock::countMusicListclickslot()
{
    QString music;
    int num=count_music_sellect->listWidget->currentRow();
    switch (num) {
    case 0:
            music = tr("glass");
        break;
    case 1:
            music = tr("bark");
        break;
    case 2:
            music = tr("sonar");
        break;
    case 3:
            music = tr("drip");
        break;
    default:
        break;
    }

    model_setup->setData(model_setup->index(0, 19), music);
    count_sel->textLabel->setText(music);
    count_sel_1->textLabel->setText(music);
    count_music_sellect->close();
    model_setup->submitAll();
}

//倒计时执行
// Countdown execution
void Clock::statCountdown(){
    QString h; QString m; QString s;
    if (countdown_hour < 10){
        QString hours_str = QString::number(countdown_hour);
        h = "0"+hours_str;
    } else {
        h = QString::number(countdown_hour);
    }

    if (countdown_minute < 10) {
        QString minute_str = QString::number(countdown_minute);
        m = "0"+minute_str;
    } else {
        m = QString::number(countdown_minute);
    }

    if (countdown_second < 10) {
        QString second_str = QString::number(countdown_second);
        s = "0"+second_str;
    } else {
        s = QString::number(countdown_second);
    }
    ui->label_9->setText(h+":"+m+":"+s);

    if (countdown_hour==0 && countdown_minute==0 && countdown_second==1) {
        countdown_timer->stop();
        countdownNoticeDialogShow();
        startbtnCountdown();
    }

    countdown_second--;
    if (countdown_second==-1) {
        countdown_minute--;
        countdown_second=59;
    }
    if (countdown_minute==-1) {
        countdown_hour--;
        countdown_minute=59;
    }
}

/*
 * 倒计时通知弹窗
 * Countdown notification pop-up
 */
void Clock::countdownNoticeDialogShow()
{
    model_setup->select();
    QScreen *screen=QGuiApplication::primaryScreen ();
    QRect mm=screen->availableGeometry() ;
    int screen_width = mm.width();
    int screen_height = mm.height();
    model_setup->select();
    Natice_alarm *dialog1 = new Natice_alarm(360,-1);
    dialog1->ui->label_4->setText(tr("360 Seconds to close"));
    dialog1->ui->label_2->hide();
    dialog1->ui->label->setText(tr("Count down"));
    dialog1->ui->label_3->setText(tr("Time out"));
    if (model_setup->index(0, 3).data().toInt()) {
        dialog1->showFullScreen();
    } else {
        dialog1->move(screen_width-450,screen_height-300);
    }
    dialog1->show();
}

/*
 * 倒计时开始-结束
 * Countdown start end callback
 */
void Clock::startbtnCountdown(){
    if (!countdown_isStarted) {
        if (timer_ring99->m_currentValue==0 && timer_ring60->m_currentValue==0 && timer_ring60_2->m_currentValue==0) {
            return;
        }
        int ringmax = timer_ring99->m_currentValue*3600 + timer_ring60->m_currentValue*60 + timer_ring60_2->m_currentValue;
        ui->page_5->RoundBar3->time_max = ringmax;
        ui->count_stat->setStyleSheet("");
        countdown_isStarted=1;
        ui->count_stat->setText(tr("End"));
        ui->stackedWidget_4->setCurrentIndex(1);
        setcoutdownNumber(timer_ring99->m_currentValue, timer_ring60->m_currentValue, timer_ring60_2->m_currentValue);//获取转轮当前值
        countdown_timer->start();
        ui->page_5->timer->start();
    } else {
        ui->page_5->RoundBar3->ring_max = 3600;
        ui->page_5->RoundBar3->setValue(3600);/*初始化倒计时进度圈
                                               Initialize countdown progress circle*/
        countdown_timer->stop();
        ui->page_5->timer->stop();
        countdown_isStarted=0;
        countdown_isStarted_2=0;
        timer_ring99->m_currentValue = 0;
        timer_ring60->m_currentValue = 0;
        timer_ring60_2->m_currentValue = 0;
        ui->count_stat->setText(tr("start"));
        ui->label_9->setText("00:00:00");
        ui->label_8->setText("00:00:00");
        ui->stackedWidget_4->setCurrentIndex(0);
        ui->count_push->setText(tr("suspend"));

        QPalette palette = ui->count_push->palette();
        QColor ColorPlaceholderText(248,163,76,255);
        QBrush brush2;
        brush2.setColor(ColorPlaceholderText);
        palette.setColor(QPalette::Button,QColor(248,163,76,255));
        palette.setBrush(QPalette::ButtonText, QBrush(Qt::white));
        ui->count_push->setPalette(palette);
    }
    return;
}

/*
 * 设置倒计时初始时间
 * Set the initial countdown time
 */
void Clock::setcoutdownNumber(int h1, int m1, int s1){
    countdown_hour=h1; countdown_minute=m1 ; countdown_second=s1;
    QString h; QString m; QString s;

    if (countdown_hour < 10){
        QString hours_str = QString::number(countdown_hour);
        h = "0"+hours_str;
    } else {
        h = QString::number(countdown_hour);
    }

    if (countdown_minute < 10) {
        QString minute_str = QString::number(countdown_minute);
        m = "0"+minute_str;
    } else {
        m = QString::number(countdown_minute);
    }

    if (countdown_second < 10) {
        QString second_str = QString::number(countdown_second);
        s = "0"+second_str;
    } else {
        s = QString::number(countdown_second);
    }

    ui->label_9->setText(h+":"+m+":"+s);
    ui->label_8->setText(h+":"+m+":"+s);

    getCountdownOverTime();
}

/*
 * 倒计时5分钟
 * Countdown 5 minutes set callback
 */
void Clock::onMin_5btnClicked()
{
    timer_ring99->m_currentValue = 0;
    timer_ring60->m_currentValue = 5;
    timer_ring60_2->m_currentValue = 0;
    setcoutdownNumber(0, 5, 0);
}
/*
 * 倒计时15分钟
 * Countdown 10 minutes set callback
 */
void Clock::onMin_10btnClicked()
{
    timer_ring99->m_currentValue = 0;
    timer_ring60->m_currentValue = 15;
    timer_ring60_2->m_currentValue = 0;
    setcoutdownNumber(0, 15, 0);
}
/*
 * 倒计时25分钟
 * Countdown 20 minutes set callback
 */
void Clock::onMin_20btnClicked()
{
    timer_ring99->m_currentValue = 0;
    timer_ring60->m_currentValue = 25;
    timer_ring60_2->m_currentValue = 0;
    setcoutdownNumber(0, 25, 0);
}
/*
 * 倒计时30分钟
 * Countdown 30 minutes set callback
 */
void Clock::onMin_30btnClicked()
{
    timer_ring99->m_currentValue = 0;
    timer_ring60->m_currentValue = 30;
    timer_ring60_2->m_currentValue = 0;
    setcoutdownNumber(0, 30, 0);
}
/*
 * 倒计时60分钟
 * Countdown 60 minutes set callback
 */
void Clock::onMin_60btnClicked()
{
    timer_ring99->m_currentValue = 1;
    timer_ring60->m_currentValue = 0;
    timer_ring60_2->m_currentValue = 0;
    setcoutdownNumber(1,0, 0);
}
/*
 * 获取倒计时结束时间
 * Get countdown end time
 */
void Clock::getCountdownOverTime()
{
    int x_h, x_m ;
    QTime time = QTime::currentTime();
    int timeH = time.hour();
    int timeM = time.minute();

    x_h = countdown_hour + timeH;
    x_m = countdown_minute + timeM;

    if (x_m >= 60) {
        x_m = x_m - 60;
        x_h ++;
    }
   if (x_h >= 48) {
        x_h = x_h - 48;
        ui->label_11->setText(tr("after tomorrow")+changeNumToStr(x_h)+":"+changeNumToStr(x_m));
    } else if (x_h >= 24) {
        x_h = x_h - 24;
        ui->label_11->setText(tr("Tomorrow")+changeNumToStr(x_h)+":"+changeNumToStr(x_m));
    } else if (x_h >= 12) {
        x_h = x_h - 12;
        ui->label_11->setText(tr("PM")+changeNumToStr(x_h)+":"+changeNumToStr(x_m));
    } else {
        ui->label_11->setText(tr("AM")+changeNumToStr(x_h)+":"+changeNumToStr(x_m));
    }
}

/*
 * 单位变双位
 * Integer to character
 */
QString Clock::changeNumToStr(int alarmHour)
{
    QString str;
    if (alarmHour < 10) {
        QString hours_str = QString::number(alarmHour);
        str = "0"+hours_str;
    } else {
        str = QString::number(alarmHour);
    }
    return str;
}

/*
 * 倒计时-暂停继续
 * Countdown - pause resume callback
 */
void Clock::onCountPushClicked()
{
    if (countdown_isStarted_2){
        ui->count_push->setText(tr("suspend"));

        QPalette palette = ui->count_push->palette();
        QColor ColorPlaceholderText(248,163,76,255);
        QBrush brush2;
        brush2.setColor(ColorPlaceholderText);
        palette.setColor(QPalette::Button,QColor(248,163,76,255));
        palette.setBrush(QPalette::ButtonText, QBrush(Qt::white));
        ui->count_push->setPalette(palette);

        countdown_timer->start();
        ui->page_5->timer->start();
        countdown_isStarted_2=0;

        getCountdownOverTime();
    } else {
        ui->count_push->setText(tr("Continue"));

        QPalette palette = ui->count_push->palette();
        QColor ColorPlaceholderText(61,107,229,255);
        QBrush brush2;
        brush2.setColor(ColorPlaceholderText);
        palette.setColor(QPalette::Button,QColor(61,107,229,255));
        palette.setBrush(QPalette::ButtonText, QBrush(Qt::white));
        ui->count_push->setPalette(palette);

        countdown_timer->stop();
        ui->page_5->timer->stop();
        countdown_isStarted_2=1;
    }
    return;
}

/*
 * 倒计时初始数字转盘
 * Countdown initial digital dial
 */
void Clock::countdownSetStartTime()
{
    DotLineDemo *ring_widget = new DotLineDemo(ui->page_4);
    ring_widget->move(0,0);

    shadow1 = new QWidget(ring_widget);
    shadow1->move(97,162);
    shadow1->resize(253,40);

    timer_ring99 = new VerticalScroll_99(ring_widget);
    QLabel * h_in_m = new QLabel (ring_widget);
    timer_ring60 = new VerticalScroll_60(ring_widget);
    QLabel * m_in_s = new QLabel (ring_widget);
    timer_ring60_2 = new VerticalScroll_60(ring_widget);

    QLabel * hour_ring = new QLabel (ring_widget);
    QLabel * min_ring = new QLabel (ring_widget);
    QLabel * sec_ring = new QLabel (ring_widget);

    hour_ring->setAlignment(Qt::AlignHCenter);
    min_ring->setAlignment(Qt::AlignHCenter);
    sec_ring->setAlignment(Qt::AlignHCenter);

    hour_ring->resize(50,30);
    hour_ring->setText(tr("hour"));
    hour_ring->setStyleSheet("font: 13pt ;color: rgb(148, 148, 148);");
    min_ring->resize(50,30);
    min_ring->setText(tr("min"));
    min_ring->setStyleSheet("font: 13pt ;color: rgb(148, 148, 148);");
    sec_ring->resize(50,30);
    sec_ring->setText(tr("sec"));
    sec_ring->setStyleSheet("font: 13pt ;color: rgb(148, 148, 148);");

    h_in_m->resize(10,38);
    h_in_m->setText(":");
    h_in_m->setStyleSheet("font: 30pt 'Sans Serif';");
    m_in_s->resize(10,38);
    m_in_s->setText(":");
    m_in_s->setStyleSheet("font: 30pt 'Sans Serif';");

    timer_ring99->move(125, 80);
    hour_ring->move(129,75);
    h_in_m->move(185,157);
    timer_ring60->move(200, 80);
    min_ring->move(201,75);
    m_in_s->move(257,157);
    timer_ring60_2->move(272, 80);
    sec_ring->move(273,75);

    count_stat = new QPushButton(ring_widget);
    count_stat->resize(100,32);
    count_stat->move(177,259);
    count_stat->setText(tr("start"));
    connect(count_stat, SIGNAL(clicked()), this, SLOT(startbtnCountdown()) );

    QPalette palette2 = count_stat->palette();
    QColor ColorPlaceholderText2(233,233,233,255);
    QBrush brush2;
    brush2.setColor(ColorPlaceholderText2);
    palette2.setColor(QPalette::Button,QColor(233,233,233,255));
    //palette2.setBrush(QPalette::ButtonText, QBrush(Qt::white));
    count_stat->setPalette(palette2);

    QTimer *timer_count_start;
    timer_count_start = new QTimer();
    connect(timer_count_start, SIGNAL(timeout()), this, SLOT(countStatBtnGray()));
    timer_count_start->setInterval(100);
    timer_count_start->start();
}

/*
 * 倒计时页开始键致灰
 *  Start button of countdown page grays out
 */
void Clock::countStatBtnGray()
{
    if(timer_ring99->m_currentValue==0 && timer_ring60->m_currentValue==0 && timer_ring60_2->m_currentValue==0) {
        count_stat->setEnabled(false);
        QStyleOption opt;
        opt.init(this);
        if(QColor(255,255,255) == opt.palette.color(QPalette::Base) || QColor(248,248,248) == opt.palette.color(QPalette::Base))
        {
            QPalette palette2 = count_stat->palette();
            QColor ColorPlaceholderText2(233,233,233,255);
            QBrush brush2;
            brush2.setColor(ColorPlaceholderText2);
            palette2.setColor(QPalette::Button,QColor(233,233,233,255));
            palette2.setBrush(QPalette::ButtonText, QBrush(QColor(158,158,158,255)));
            count_stat->setPalette(palette2);
        }else{
            QPalette palette2 = count_stat->palette();
            QColor ColorPlaceholderText2(45,45,48,255);
            QBrush brush2;
            brush2.setColor(ColorPlaceholderText2);
            palette2.setColor(QPalette::Button,QColor(45,45,48,255));
            palette2.setBrush(QPalette::ButtonText, QBrush(QColor(58,58,58,255)));
            count_stat->setPalette(palette2);
        }
    }else{
        count_stat->setEnabled(true);
        QPalette palette2 = count_stat->palette();
        QColor ColorPlaceholderText2(61,107,229,255);
        QBrush brush2;
        brush2.setColor(ColorPlaceholderText2);
        palette2.setColor(QPalette::Button,QColor(61,107,229,255));
        palette2.setBrush(QPalette::ButtonText, QBrush(Qt::white));
        count_stat->setPalette(palette2);
    }
}

/*
 * 闹钟初始化数字转盘
 * Alarm clock initialization digital turntable drawing
 */
void Clock::alarmSetStartTime()
{
    shadow = new QWidget(ui->set_page);
    shadow->move(82,117);
    shadow->resize(280,40);

    timer_alarm_start24 = new VerticalScroll_24(ui->set_page, this);
    QLabel * h_in_m = new QLabel (ui->set_page);
    timer_alarm_start60 = new VerticalScroll_60(ui->set_page);

    timer_alarm_start24->resize(53,180);
    timer_alarm_start60->resize(53,180);

    QLabel * hour_ring = new QLabel (ui->set_page);
    QLabel * min_ring = new QLabel (ui->set_page);

    hour_ring->setAlignment(Qt::AlignHCenter);
    min_ring->setAlignment(Qt::AlignHCenter);

    h_in_m->resize(10,40);
    h_in_m->setText(":");
    h_in_m->setStyleSheet("font: 25pt;");

    hour_ring->resize(50,30);
    hour_ring->setText(tr("hour"));
    hour_ring->setStyleSheet("font: 13pt ;color: rgb(148, 148, 148);");
    min_ring->resize(50,30);
    min_ring->setText(tr("min"));
    min_ring->setStyleSheet("font: 13pt ;color: rgb(148, 148, 148);");

    timer_alarm_start24->move(139, 45);
    hour_ring->move(140,40);
    h_in_m->move(220,113);
    timer_alarm_start60->move(258, 45);
    min_ring->move(258,40);
}

/*
 * 闹钟初始化工作日选择界面绘制回调
 * Alarm clock initialization workday selection interface drawing callback
 */
void Clock::alarmRepeat()
{
    int num;
    if(repeat_new_or_edit_flag)
        num = ui->listWidget->currentRow();
    else {
        num= model->rowCount();
    }
        QPointF position = this->pos();//446
        dialog_repeat->move(position.x()+88,position.y()+378);
        dialog_repeat->resize(280,270);
        dialog_repeat->listWidget->setFixedSize(280,270);
        dialog_repeat->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
        dialog_repeat->setAttribute(Qt::WA_TranslucentBackground);
        dialog_repeat->widget[0]->alarmLabel0->setText(tr("No repetition"));
        dialog_repeat->widget[1]->alarmLabel0->setText(tr("Workingday"));
        dialog_repeat->widget[2]->alarmLabel0->setText(tr("Mon"));
        dialog_repeat->widget[3]->alarmLabel0->setText(tr("Tue"));
        dialog_repeat->widget[4]->alarmLabel0->setText(tr("Wed"));
        dialog_repeat->widget[5]->alarmLabel0->setText(tr("Thu"));
        dialog_repeat->widget[6]->alarmLabel0->setText(tr("Fri"));
        dialog_repeat->widget[7]->alarmLabel0->setText(tr("Sat"));
        dialog_repeat->widget[8]->alarmLabel0->setText(tr("Sun"));
        for (int i=0; i<7; i++) {
            if (repeat_day[i]) {
                dialog_repeat->widget[i+2]->alarmLabel1->setPixmap(repeat_on_Pixmap);
            } else {
                dialog_repeat->widget[i+2]->alarmLabel1->setPixmap(repeat_off_Pixmap);
            }
        }
        dialog_repeat->show();

}
/*
 * 重复选项单击回调
 * Repeat option click callback
 */
void Clock::repeatListclickslot()
{
    int num=dialog_repeat->listWidget->currentRow();
    QString day[7] ;
    day[0]= tr("Mon");
    day[1] = tr("Tue");
    day[2] = tr("Wed");
    day[3] = tr("Thu");
    day[4] = tr("Fri");
    day[5] = tr("Sat");
    day[6] = tr("Sun");

    switch (num)
    {
    case 0:
        repeat_sel->textLabel->setText(tr("No repetition"));
        repeat_str_model = tr("No repetition");
        for (int i=0; i<7; i++) {
            repeat_day[i] = 1;
            qDebug() << repeat_day[i];
            dialog_repeat->widget[i+2]->alarmLabel1->setPixmap(repeat_off_Pixmap);
        }

        dialog_repeat->close();
        return;
        break;
    case 1:
        repeat_sel->textLabel->setText(tr("Workingday"));
        repeat_str_model = tr("Workingday");
        for (int i=0; i<7; i++) {
            if(model_setup->index(0, i+7).data().toInt()) {
                repeat_day[i] = 1;
                qDebug() << repeat_day[i];
                dialog_repeat->widget[i+2]->alarmLabel1->setPixmap(repeat_on_Pixmap);
            } else {
                repeat_day[i] = 0;
                dialog_repeat->widget[i+2]->alarmLabel1->setPixmap(repeat_off_Pixmap);
            }
        }
        dialog_repeat->widget[7]->alarmLabel1->setPixmap(repeat_on_Pixmap);
        dialog_repeat->widget[8]->alarmLabel1->setPixmap(repeat_on_Pixmap);
        dialog_repeat->close();
        return;
        break;
    case 2:
        if (repeat_day[0] == 0 ) {
            repeat_day[0] = 1;
            dialog_repeat->widget[2]->alarmLabel1->setPixmap(repeat_on_Pixmap);
        } else {
            if(repeat_day[1]== 0 && repeat_day[2]== 0 && repeat_day[3]== 0 && repeat_day[4]== 0 && repeat_day[5]== 0 && repeat_day[6]== 0){
                 //防止全部勾选被取消
            }else{
            repeat_day[0] = 0;
            dialog_repeat->widget[2]->alarmLabel1->setPixmap(repeat_off_Pixmap);
            }
        }
        break;
    case 3:
        if(repeat_day[1] == 0 ) {
            repeat_day[1] = 1;
            dialog_repeat->widget[3]->alarmLabel1->setPixmap(repeat_on_Pixmap);
        } else {
            if(repeat_day[0]== 0 && repeat_day[2]== 0 && repeat_day[3]== 0 && repeat_day[4]== 0 && repeat_day[5]== 0 && repeat_day[6]== 0){

            }else{
            repeat_day[1] = 0;
            dialog_repeat->widget[3]->alarmLabel1->setPixmap(repeat_off_Pixmap);
            }
        }
        break;
    case 4:
        if (repeat_day[2] == 0 ) {
            repeat_day[2] = 1;
            dialog_repeat->widget[4]->alarmLabel1->setPixmap(repeat_on_Pixmap);
        } else {
            if(repeat_day[1]== 0 && repeat_day[0]== 0 && repeat_day[3]== 0 && repeat_day[4]== 0 && repeat_day[5]== 0 && repeat_day[6]== 0){

            }else{
            repeat_day[2] = 0;
            dialog_repeat->widget[4]->alarmLabel1->setPixmap(repeat_off_Pixmap);
            }
        }
        break;
    case 5:
        if (repeat_day[3] == 0 ) {
            repeat_day[3] = 1;
            dialog_repeat->widget[5]->alarmLabel1->setPixmap(repeat_on_Pixmap);
        } else {
            if(repeat_day[1]== 0 && repeat_day[2]== 0 && repeat_day[0]== 0 && repeat_day[4]== 0 && repeat_day[5]== 0 && repeat_day[6]== 0){

            }else{
            repeat_day[3] = 0;
            dialog_repeat->widget[5]->alarmLabel1->setPixmap(repeat_off_Pixmap);
            }
        }
        break;
    case 6:
        if (repeat_day[4] == 0 ) {
            repeat_day[4] = 1;
            dialog_repeat->widget[6]->alarmLabel1->setPixmap(repeat_on_Pixmap);
        } else {
            if(repeat_day[1]== 0 && repeat_day[2]== 0 && repeat_day[3]== 0 && repeat_day[0]== 0 && repeat_day[5]== 0 && repeat_day[6]== 0){

            }else{
            repeat_day[4] = 0;
            dialog_repeat->widget[6]->alarmLabel1->setPixmap(repeat_off_Pixmap);
            }
        }
        break;
    case 7:
        if (repeat_day[5] == 0 ) {
            repeat_day[5] = 1;
            dialog_repeat->widget[7]->alarmLabel1->setPixmap(repeat_on_Pixmap);
        } else {
            if(repeat_day[1]== 0 && repeat_day[2]== 0 && repeat_day[3]== 0 && repeat_day[4]== 0 && repeat_day[0]== 0 && repeat_day[6]== 0){

            }else{
            repeat_day[5] = 0;
            dialog_repeat->widget[7]->alarmLabel1->setPixmap(repeat_off_Pixmap);
            }
        }
        break;
    case 8:
        if (repeat_day[6] == 0 ) {
            repeat_day[6] = 1;
            dialog_repeat->widget[8]->alarmLabel1->setPixmap(repeat_on_Pixmap);
        } else {
            if(repeat_day[1]== 0 && repeat_day[2]== 0 && repeat_day[3]== 0 && repeat_day[4]== 0 && repeat_day[5]== 0 && repeat_day[0]== 0){

            }else{
            repeat_day[6] = 0;
            dialog_repeat->widget[8]->alarmLabel1->setPixmap(repeat_off_Pixmap);
            }
        }
        break;
    default:
        break;
    }
    for (int i=0; i<7; i++) {
        if (repeat_day[i]) {
            repeat_str=repeat_str+day[i];
        }
    }
    if(repeat_day[0]&&repeat_day[1]&&repeat_day[2]&&repeat_day[3]&&repeat_day[4]&&repeat_day[5]&&repeat_day[6])
        repeat_str = tr("Every day");
    repeat_sel->textLabel->setText(repeat_str);
    repeat_str_model = repeat_str;
    repeat_str="";
}

/*
 * 闹钟初始化音乐选择界面回调
 * Alarm clock initialization music selection interface callback
 */
void Clock::selectAlarmMusic()
{
    int num;
    if(repeat_new_or_edit_flag)
        num = ui->listWidget->currentRow();
    else
        num= model->rowCount();

    QPointF position = this->pos();
    dialog_music->move(position.x()+88,position.y()+428);
    dialog_music->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    dialog_music->setAttribute(Qt::WA_TranslucentBackground);
    dialog_music->resize(280,129);
    dialog_music->listWidget->setFixedSize(280,129);
    dialog_music->widget[0]->alarmLabel0->setText(tr("glass"));
    dialog_music->widget[1]->alarmLabel0->setText(tr("bark"));
    dialog_music->widget[2]->alarmLabel0->setText(tr("sonar"));
    dialog_music->widget[3]->alarmLabel0->setText(tr("drip"));

    if(model_setup->index(0, 5).data().toString().compare(tr("glass"))==0){
        dialog_music->widget[0]->alarmLabel0->setText(tr("glass(default)"));
    } else if (model_setup->index(0, 5).data().toString().compare(tr("bark"))==0) {
        dialog_music->widget[1]->alarmLabel0->setText(tr("bark(default)"));
    } else if (model_setup->index(0, 5).data().toString().compare(tr("sonar"))==0) {
        dialog_music->widget[2]->alarmLabel0->setText(tr("sonar(default)"));
    } else if (model_setup->index(0, 5).data().toString().compare(tr("drip"))==0) {
        dialog_music->widget[3]->alarmLabel0->setText(tr("drip(default)"));
    }

    dialog_music->show();
}

/*
 * 闹钟初始化单击选择音乐
 * Alarm initialization Click to select music
 */
void Clock::musicListclickslot()
{
    int num=dialog_music->listWidget->currentRow();

    switch (num)
    {
    case 0:
        music_str_model=tr("glass");
        break;
    case 1:
        music_str_model=tr("bark");
        break;
    case 2:
        music_str_model=tr("sonar");
        break;
    case 3:
        music_str_model=tr("drip");
        break;
    default:
        break;
    }
    time_sel->textLabel->setText(music_str_model);
    dialog_music->close();
}
/*
 * 闹钟初始化音乐时长选择界面回调
 * Alarm clock initialization music time selection interface callback
 */
void Clock::timeMusic()
{
    int num;
    if(repeat_new_or_edit_flag)
        num = ui->listWidget->currentRow();
    else
        num= model->rowCount();

    QPointF position = this->pos();
    time_music->move(position.x()+88,position.y()+478);
    time_music->listWidget->setFixedSize(280,162);
    time_music->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    time_music->setAttribute(Qt::WA_TranslucentBackground);
    time_music->resize(280,162);
    time_music->listWidget->move(0,0);
    time_music->widget[0]->alarmLabel0->setText(tr("1min"));
    time_music->widget[1]->alarmLabel0->setText(tr("2min"));
    time_music->widget[2]->alarmLabel0->setText(tr("3min"));
    time_music->widget[3]->alarmLabel0->setText(tr("4min"));
    time_music->widget[4]->alarmLabel0->setText(tr("6min"));
    time_music->show();
}
/*
 * 单击选择音乐时长回调
 * Click to select music duration callback
 */
void Clock::timeMusicListclickslot()
{
    int num=time_music->listWidget->currentRow();
    switch (num)
    {
    case 0:
        time_music_str_model=tr("1min");
        break;
    case 1:
        time_music_str_model=tr("2min");
        break;
    case 2:
        time_music_str_model=tr("3min");
        break;
    case 3:
        time_music_str_model=tr("4min");
        break;
    case 4:
        time_music_str_model=tr("6min");
        break;
    default:
        break;
    }
    ring_sel->textLabel->setText(time_music_str_model);

    time_music->close();
}

/*
 * Default setting database data initialization
 * 默认设置数据库数据初始化
 */
void Clock::modelSetupSet()
{
    int setup_rowNum;
    setup_rowNum = model_setup->rowCount();
    if (setup_rowNum < 1) {
        model_setup->insertRow(setup_rowNum);
        model_setup->setData(model_setup->index(setup_rowNum, 0), int(0));//自启动  Self starting
        model_setup->setData(model_setup->index(setup_rowNum, 1), int(0));//静音    Mute
        model_setup->setData(model_setup->index(setup_rowNum, 2), int(3));//时间格式 Time format
        model_setup->setData(model_setup->index(setup_rowNum, 3), int(0));//弹窗    Popup
        model_setup->setData(model_setup->index(setup_rowNum, 4), int(0));//提醒关闭 Reminder off
        model_setup->setData(model_setup->index(setup_rowNum, 5), tr("glass"));
        model_setup->setData(model_setup->index(setup_rowNum, 6), int(100));//音量  volume
        model_setup->setData(model_setup->index(setup_rowNum, 7), int(1));
        model_setup->setData(model_setup->index(setup_rowNum, 8), int(1));
        model_setup->setData(model_setup->index(setup_rowNum, 9), int(1));
        model_setup->setData(model_setup->index(setup_rowNum, 10), int(1));
        model_setup->setData(model_setup->index(setup_rowNum, 11), int(1));
        model_setup->setData(model_setup->index(setup_rowNum, 12), int(0));
        model_setup->setData(model_setup->index(setup_rowNum, 13), int(0));
        model_setup->setData(model_setup->index(setup_rowNum, 14), tr("Monday to Friday"));
        model_setup->setData(model_setup->index(setup_rowNum, 15), tr("24 hour system"));
        model_setup->setData(model_setup->index(setup_rowNum, 16), tr("Notification"));
        model_setup->setData(model_setup->index(setup_rowNum, 17), tr("Alert in 2 minutes"));
        model_setup->setData(model_setup->index(setup_rowNum, 19), tr("glass"));
    }
    model_setup->submitAll();
}

/*
 * 设置页面绘制回调
 * Set page draw callback
 */
void Clock::setUpPage()
{
    /*手动构造一个鼠标移走的事件
    Manually construct an event to move the mouse away*/
    repeat_sel->setAttribute(Qt::WA_UnderMouse, false);
    QHoverEvent hoverEvent(QEvent::HoverLeave, QPoint(40, 40), QPoint(0, 0));
    QCoreApplication::sendEvent(repeat_sel, &hoverEvent);

    QPointF position1 = QCursor::pos();
    if(!setup_page){
        setup_page = new setuppage(position1.x(), position1.y(),  this);
        connect(setup_page->ui->pushButton, SIGNAL(clicked()), this, SLOT(alarmClcokSelfStarting()) );
        connect(setup_page->ui->pushButton_2, SIGNAL(clicked()), this, SLOT(MuteStarting()) );
        connect(setup_page->ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(setVolumeValue(int)));
        grand = new QWidget(setup_page->ui->widget);
    }
    setup_page->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    setup_page->setFixedSize(380,450);

    QPointF position = this->pos();

    setup_page->move(position.x()+38,position.y()+27);
    setup_page->setWindowOpacity(0.98);

    /*属性记忆重绘制
     Attribute memory redrawing*/
    if (model_setup->index(0, 0).data().toInt()) {
        setup_page->ui->pushButton->setStyleSheet("border-image: url(:/alarm_on.png);");
    } else {
        setup_page->ui->pushButton->setStyleSheet("border-image: url(:/alarm_off.png);");
    }
    if (model_setup->index(0, 1).data().toInt()) {
        setup_page->ui->pushButton_2->setStyleSheet("border-image: url(:/alarm_on.png);\
                                                    border-radius:6px;\
                border:0px solid rgba();");
    } else {
        setup_page->ui->pushButton_2->setStyleSheet("border-image: url(:/alarm_off.png);\
                                                    border-radius:6px;\
                border:0px solid rgba();");
    }
    setup_page->ui->horizontalSlider->setValue(model_setup->index(0, 6).data().toInt());

    if (model_setup->index(0, 1).data().toInt()) {
        grand->resize(197,24);
        grand->move(128,406);
        grand->setStyleSheet("QWidget{background-color: rgba(14, 19, 22, 0);border:0px solid rgba();}");
        grand->show();
    } else {
        grand->hide();
    }
    setup_page->show();
}

/*
 * 开机自启动开关;
 * Power on self start switch callback
 */
void Clock::alarmClcokSelfStarting()
{
    if (model_setup->index(0, 0).data().toInt()) {
        setup_page->ui->pushButton->setStyleSheet("border-image: url(:/alarm_off.png);");
        model_setup->setData(model_setup->index(0, 0), 0);
    } else {
        setup_page->ui->pushButton->setStyleSheet("border-image: url(:/alarm_on.png);");
        model_setup->setData(model_setup->index(0, 0), 1);
    }
    model_setup->submitAll();
}

/*
 * 静音开关回调  静音不可调节音量
 * Mute switch callback
 */
void Clock::MuteStarting()
{
    if (model_setup->index(0, 1).data().toInt()) {
        setup_page->ui->pushButton_2->setStyleSheet("border-image: url(:/alarm_off.png);\
                                                    border-radius:6px;\
                                                    border:0px solid rgba();");
        model_setup->setData(model_setup->index(0, 1), 0);
        grand->hide();
        model_setup->setData(model_setup->index(0, 6),model_setup->index(0, 18).data().toInt());//滑动条记忆回复
                                                                                                // Slider memory recall
        setup_page->ui->horizontalSlider->setValue(model_setup->index(0, 6).data().toInt());
    } else {
        setup_page->ui->pushButton_2->setStyleSheet("border-image: url(:/alarm_on.png);\
                                                    border-radius:6px;\
                                                    border:0px solid rgba();");
        model_setup->setData(model_setup->index(0, 1), 1);

        model_setup->setData(model_setup->index(0, 18),model_setup->index(0, 6).data().toInt());//记忆滑动条
                                                                                                // Memory slider
        model_setup->setData(model_setup->index(0, 6),0 );
        setup_page->ui->horizontalSlider->setValue(0);

        grand->move(128,406);
        grand->setStyleSheet("QWidget{background-color: rgba(14, 19, 22, 0);border:0px solid rgba();}");
        grand->show();
    }
    model_setup->submitAll();
}

/*
 * 设置音量回调
 * Set volume callback
 */
void Clock::setVolumeValue(int value)
{
    qDebug()<< value ;
    model_setup->setData(model_setup->index(0, 6),value );
    model_setup->submitAll();
}

void Clock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    QPainterPath rectPath;
    rectPath.addRoundedRect(this->rect(), 6, 6); // 左上右下
    p.fillPath(rectPath,palette().color(QPalette::Base));
}

QPixmap Clock::ChangeImageColor(QPixmap sourcePixmap, QColor origColor, QColor destColor)
{
    QImage image = sourcePixmap.toImage();

    QRgb rgb = image.pixel(image.width()/2,image.height()/2);
    QVector<QRgb> rgbVector = image.colorTable();

    for (int i = 0; i < rgbVector.size(); ++i)
    {
        QRgb rgb2 = QColor(0,0,0).rgba();//替换的颜色可以是透明的，比如QColor(0,255,0，0)。
        image.setColor(i,rgb2);
    }
    return QPixmap::fromImage(image);
}

bool Clock::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->set_page && event->type() == QEvent::Paint)
    {
        showPaint(); //响应函数
    }
    if(watched == ui->widget && event->type() == QEvent::Paint)
    {
        showPaint1();
    }
    if(watched == shadow && event->type() == QEvent::Paint)
    {
        showPaint7();
    }
    if(watched == shadow1 && event->type() == QEvent::Paint)
    {
        showPaint8();
    }
    return QWidget::eventFilter(watched,event);
}

/*
 * 实现响应函数设置页
*/
void Clock::showPaint()
{
    QPainter painter(ui->set_page);
    painter.setPen(Qt::gray);
    painter.setBrush(Qt::green);
    QStyleOption opt;
    opt.init(this);
    painter.setBrush(opt.palette.color(QPalette::Base));
    painter.setPen(Qt::transparent);
    QRect rect = ui->set_page->rect();
    rect.setWidth(rect.width() - 0);
    rect.setHeight(rect.height() - 0);
    painter.drawRoundedRect(rect, 7, 7);
    {
        QPainterPath painterPath;
        painterPath.addRoundedRect(rect, 0, 0);
        painter.drawPath(painterPath);
    }
}

/*
 * 实现响应函数命令栏
*/
void Clock::showPaint1()
{
    QPainter painter(ui->widget);
    painter.setPen(Qt::gray);
    painter.setBrush(Qt::green);
    QStyleOption opt;
    opt.init(this);
    painter.setBrush(opt.palette.color(QPalette::Base));

    if(QColor(255,255,255) == opt.palette.color(QPalette::Base) || QColor(248,248,248) == opt.palette.color(QPalette::Base))
    {
        painter.setBrush(QColor(217, 217, 217));
    }else{
        painter.setBrush(QColor(48,48,51));
    }

    painter.setPen(Qt::transparent);
    QRect rect = ui->widget->rect();
    rect.setWidth(rect.width() - 0);
    rect.setHeight(rect.height() - 0);
    painter.drawRoundedRect(rect, 7, 7);
    {
        QPainterPath painterPath;
        painterPath.addRoundedRect(rect, 4, 4);
        painter.drawPath(painterPath);
    }
}

/*
 * 实现响应函数设置页
*/
void Clock::showPaint7()
{
    QPainter painter(shadow);
    painter.setPen(Qt::gray);
    painter.setBrush(Qt::green);
    QStyleOption opt;
    opt.init(this);
    painter.setBrush(opt.palette.color(QPalette::Base));

    if(QColor(255,255,255) == opt.palette.color(QPalette::Base) || QColor(248,248,248) == opt.palette.color(QPalette::Base))
    {
        painter.setBrush(QColor(217, 217, 217));
    }else{
        painter.setBrush(QColor(48,48,51));
    }

    painter.setPen(Qt::transparent);
    QRect rect = shadow->rect();
    rect.setWidth(rect.width() - 0);
    rect.setHeight(rect.height() - 0);
    painter.drawRoundedRect(rect, 7, 7);
    {
        QPainterPath painterPath;
        painterPath.addRoundedRect(rect, 4, 4);
        painter.drawPath(painterPath);
    }
}
/*
 * 实现响应函数设置页
*/
void Clock::showPaint8()
{
    QPainter painter(shadow1);
    painter.setPen(Qt::gray);
    painter.setBrush(Qt::green);
    QStyleOption opt;
    opt.init(this);
    painter.setBrush(opt.palette.color(QPalette::Base));

    if(QColor(255,255,255) == opt.palette.color(QPalette::Base) || QColor(248,248,248) == opt.palette.color(QPalette::Base))
    {
        painter.setBrush(QColor(233,233,233));
    }else{
        painter.setBrush(QColor(48,48,51));
    }

    painter.setPen(Qt::transparent);
    QRect rect = shadow1->rect();
    rect.setWidth(rect.width() - 0);
    rect.setHeight(rect.height() - 0);
    painter.drawRoundedRect(rect, 7, 7);
    {
        QPainterPath painterPath;
        painterPath.addRoundedRect(rect, 4, 4);
        painter.drawPath(painterPath);
    }
}

void Clock::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->dragPosition = event->globalPos() - frameGeometry().topLeft();
        this->mousePressed = true;
    }
    QWidget::mousePressEvent(event);
}

void Clock::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->mousePressed = false;
        this->setCursor(Qt::ArrowCursor);
    }

    QWidget::mouseReleaseEvent(event);
}

void Clock::mouseMoveEvent(QMouseEvent *event)
{
    if (this->mousePressed) {
        move(event->globalPos() - this->dragPosition);
        this->setCursor(Qt::ClosedHandCursor);
    }

    QWidget::mouseMoveEvent(event);
}
