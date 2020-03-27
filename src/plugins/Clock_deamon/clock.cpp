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
#include <QDebug>
#include <QTimer>
#include <QTime>
#include "connection.h"
#include <QMessageBox>
#include "item_new.h"
#include "set_clock.h"
#include "stopwatch_item.h"

const double PI=3.141592;

Clock::Clock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Clock)
{
    ui->setupUi(this);

    createConnection();
    this->setWindowTitle(tr("闹钟"));
    setWindowFlags(Qt::FramelessWindowHint);   /* 开启窗口无边框 */
    //setAttribute(Qt::WA_TranslucentBackground);/* 开启窗口透明层 */
   // this->hide();

    ui->set_page->setStyleSheet("QWidget{background-color: rgba(14, 19, 22, 0.9);}");

    pixmap1 = QPixmap(":/icon-1.png");
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



    ui->pushButton->setIcon(pixmap1);
    ui->pushButton_2->setIcon(pixmap4);
    ui->pushButton_3->setIcon(pixmap2);

    ui->pushButton_4->setIcon(pixmap6);
    ui->pushButton_4->setFlat(true);
    ui->pushButton_4->setVisible(true);
    ui->pushButton_4->setFocusPolicy(Qt::NoFocus);

    ui->pushButton_5->setIcon(pixmap5);
    ui->pushButton_5->setFlat(true);
    ui->pushButton_5->setVisible(true);
    ui->pushButton_5->setFocusPolicy(Qt::NoFocus);
    //---------------倒计时-------------------------------------------------------------------------

    //初始化定时器
    countdown_timer = new QTimer();
    //信号和槽
    connect(ui->count_stat, SIGNAL(clicked()), this, SLOT(startbtn_countdown()) );
    connect(countdown_timer, SIGNAL(timeout()), this, SLOT(stat_countdown()));
    //设置定时器每个多少毫秒发送一个timeout()信号
    countdown_timer->setInterval(1000);
    ui->count_push->setStyleSheet("border-image: url(:/push_1.png);");
    countdown_hour = 0;
    countdown_minute = 0;
    countdown_second = 9;
    countdown_pushflag = 0;
    countdown_isStarted = 0;

    //------------秒表-----------------------------------------------------------------------------------
    //  ui->pushButton_Start->setIcon(pixmap8);
    ui->pushButton_Start->setFlat(true);
    ui->pushButton_Start->setVisible(true);
    ui->pushButton_Start->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_Start->setStyleSheet("border-image: url(:/start_1.png);");

    //初始化定时器
    timer = new QTimer();
    //信号和槽
    connect(timer, SIGNAL(timeout()), this, SLOT(Count_down()));
    //设置定时器每个多少毫秒发送一个timeout()信号
    timer->setInterval(10);

    ui->label_4->setText("00:00.00");
    isStarted = 0;
    hour=0;
    minute=0;
    second=0;
    pushflag=0 ;
    on_pushButton_2_clicked();//初始显示闹钟界面

    //时间间隔定时器
    timer_2 = new QTimer();
    connect(timer_2, SIGNAL(timeout()), this, SLOT(stopwatch_jg()));
    timer_2->setInterval(10);
    stopwatch_hour = 0;
    stopwatch_minute = 0;
    stopwatch_second = 0;
    stopwatch_isStarted = 0;

    //----------------------闹钟---------------------------------
    //ui->label_20->setStyleSheet("background:rgb();");
    ui->pushButton_10->setIcon(bgPixmap);
    ui->pushButton_7->setIcon(bgPixmap);
    ui->pushButton_16->setIcon(bgPixmap);
    QTimer *timer_clock = new QTimer(this);
    connect(timer_clock, SIGNAL(timeout()), this, SLOT(timerUpdate()) );//动态获取时间
    QTime time = QTime::currentTime();
    ui->label_6->setText(time.toString("hh")+":"+time.toString("mm")+":"+time.toString("ss"));
    timer_clock->start(1000);

    connect( ui->addAlarmBtn, SIGNAL(clicked()), this, SLOT(set_Alarm_Clock()) );//添加闹钟


    player_alarm = new QMediaPlayer(this);
    mediaList = new QMediaPlaylist(this);

    model = new QSqlTableModel(this);
    model->setTable("clock");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select(); //选取整个表的所有行


    connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(listdoubleClickslot()));
    connect(ui->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(listClickslot()));

    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(deleteAlarm()) );
    connect(ui->set_alarm_savebtn, SIGNAL(clicked()), this, SLOT(set_alarm_save()) );
    connect(ui->set_alarm_cancelbtn, SIGNAL(clicked()), this, SLOT(alarm_Cancel_save()) );
    connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(alarm_repeat()) );
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(alarm_repeat()) );
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(select_Music()) );
    connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(select_Music()) );
    connect(ui->pushButton_16, SIGNAL(clicked()), this, SLOT(time_Music()) );
    connect(ui->pushButton_17, SIGNAL(clicked()), this, SLOT(time_Music()) );
    connect(ui->pushButton_18, SIGNAL(clicked()), this, SLOT(clack_rename()) );

    //单击时间提示计时器
    timer_21111 = new QTimer();
    connect(timer_21111, SIGNAL(timeout()), this, SLOT(listClickslot()));
    timer_21111->setInterval(1000);

    //闹钟设置界面时间提示计时器
    timer_set_page = new QTimer();
    connect(timer_set_page, SIGNAL(timeout()), this, SLOT(verticalscroll_ring_time()));
    timer_set_page->setInterval(100);

    updateAlarmClock();
//-----------------------------------------------------------------------------------------------------------------
    countdown_set_start_time();//倒计时初始化数字转盘
    ui->label_8->hide();

    connect(ui->label, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()) );//扩大页面切换反映区
    connect(ui->label_2, SIGNAL(clicked()), this, SLOT(on_pushButton_2_clicked()) );
    connect(ui->label_3, SIGNAL(clicked()), this, SLOT(on_pushButton_3_clicked()) );


    alarm_set_start_time();//闹钟初始化数字转盘

    for (int i=0; i<9; i++) {
        repeat_day[i] = 0;
        qDebug() << repeat_day[i];
    }
}

Clock::~Clock()
{
    delete ui;
}


QPointF Clock::rotateAngle(int angle, int len)
{
    int x, y;

    x = 150+len*sin(angle*PI/180);
    y = 150-len*cos(angle*PI/180);

    return QPointF(x, y);
}

//绘制时钟界面
void Clock::paintEvent1(QPaintEvent *)
{
    QTime time = QTime::currentTime();
    int timeH = time.hour();
    int timeM = time.minute();
    int timeS = time.second();

    QDateTime dateTime = QDateTime::currentDateTime();
    // cTimeLabe->setText(dateTime.toString("yyyy-MM-dd hh:mm:ss ddd"));

    QPainter painter(ui->page_4);
    QPen pen;

    //painter.drawPixmap(this->rect(), bgPixmap);
    //绘制钟面
    pen.setWidth(1);
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    for(int i=0; i<60; i++)
    {
        painter.drawLine(rotateAngle(6*i, 100), rotateAngle(6*i, 95));
    }
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawEllipse(QPoint(150, 150), 100, 100);
    pen.setWidth(3);
    painter.setPen(pen);
    for(int i=0; i<12; i++)
    {
        painter.drawLine(rotateAngle(30*i, 100), rotateAngle(30*i, 90));
    }

    //绘制指针
    pen.setWidth(2);
    pen.setColor(Qt::black);//pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawLine(QPointF(150, 150), rotateAngle(6*timeS, 80));
    pen.setWidth(6);
    pen.setColor(Qt::black);//pen.setColor(Qt::blue);
    painter.setPen(pen);
    painter.drawLine(QPointF(150, 150), rotateAngle(6*timeM, 60));
    pen.setWidth(8);
    pen.setColor(Qt::black);//pen.setColor(Qt::green);
    painter.setPen(pen);
    painter.drawLine(QPointF(150, 150), rotateAngle(0.5*(timeH*60+timeM), 40));
}

//时间间隔执行
void Clock::stopwatch_jg()
{
    if(stopwatch_hour < 10){
        QString hours_str = QString::number(stopwatch_hour);
        stopwatch_jg_h = "0"+hours_str;
    }else {
        stopwatch_jg_h = QString::number(stopwatch_hour);
    }

    if(stopwatch_minute < 10){
        QString minute_str = QString::number(stopwatch_minute);
        stopwatch_jg_m = "0"+minute_str;
    }else {
        stopwatch_jg_m = QString::number(stopwatch_minute);
    }

    if(stopwatch_second < 10){
        QString second_str = QString::number(stopwatch_second);
        stopwatch_jg_s = "0"+second_str;
    }else {
        stopwatch_jg_s = QString::number(stopwatch_second);
    }

    ui->label_5->setText(stopwatch_jg_h+":"+stopwatch_jg_m+"."+stopwatch_jg_s);

    stopwatch_second++;
    if(stopwatch_second==100){
        stopwatch_minute++; stopwatch_second=0;}
    if(stopwatch_minute==60){
        stopwatch_hour++; stopwatch_minute=0;}
}

//秒表执行
void Clock::Count_down()
{
    if(hour < 10){
        QString hours_str = QString::number(hour);
        stopwatch_h = "0"+hours_str;
    }else {
        stopwatch_h = QString::number(hour);
    }

    if(minute < 10){
        QString minute_str = QString::number(minute);
        stopwatch_m = "0"+minute_str;
    }else {
        stopwatch_m = QString::number(minute);
    }

    if(second < 10){
        QString second_str = QString::number(second);
        stopwatch_s = "0"+second_str;
    }else {
        stopwatch_s = QString::number(second);
    }

    ui->label_4->setText(stopwatch_h+":"+stopwatch_m+"."+stopwatch_s);

    second++;
    if(second==100){
        minute++; second=0;}
    if(minute==60){
        hour++; minute=0;}

}

void Clock::on_pushButton_Start_clicked()
{
    if (!isStarted){
        ui->pushButton_Start->setStyleSheet("border-image: url(:/push_1.png);");
        if(stopwatch_isStarted == 0)
        {
            timer_2->start();
            stopwatch_isStarted = 1;
        }
        timer->start();
        isStarted=1;
    } else {
        timer->stop();
        if(stopwatch_isStarted == 1)//查询间隔计时器是否启动
        {
            timer_2->stop();
            stopwatch_isStarted = 0;
        }
        isStarted=0;
        ui->pushButton_Start->setStyleSheet("border-image: url(:/continu.png);");
    }
    return;
}

//计次
void Clock::on_pushButton_ring_clicked()
{
    if(!isStarted)
    {
        return;
    }

    if(stopwatch_isStarted == 0)
    {
        timer_2->start();
        stopwatch_isStarted = 1;
    }
    stopwatch_aItem[stopwatch_item_flag] =new QListWidgetItem;
    stopwatch_aItem[stopwatch_item_flag]->setSizeHint(QSize(376,56));
    stopwatch_aItem[stopwatch_item_flag]->setTextColor(QColor(255, 0, 0, 255));
    ui->listWidget_2->addItem(stopwatch_aItem[stopwatch_item_flag]);
    ui->listWidget_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    stopwatch_w[stopwatch_item_flag] = new stopwatch_item(ui->listWidget_2);

    stopwatch_w[stopwatch_item_flag]->stopwatch1->setText("计次"+QString::number(stopwatch_item_flag));
    stopwatch_w[stopwatch_item_flag]->stopwatch2->setText(stopwatch_jg_h+":"+stopwatch_jg_m+"."+stopwatch_jg_s);
    stopwatch_w[stopwatch_item_flag]->stopwatch3->setText(stopwatch_h+":"+stopwatch_m+"."+stopwatch_s);

    ui->listWidget_2->setItemWidget(stopwatch_aItem[stopwatch_item_flag],stopwatch_w[stopwatch_item_flag]);

    stopwatch_hour = 0;
    stopwatch_minute = 0;
    stopwatch_second = 0;

    qDebug()<< stopwatch_item_flag;

    stopwatch_item_flag++;
}


//复位
void Clock::on_pushButton_timeselect_clicked()
{
    if(nullptr != timer){
        timer->stop();
        timer_2->stop();
        ui->label_4->setText("00:00.00");
        ui->label_5->setText("00:00.00");
        isStarted = 0;
        stopwatch_isStarted = 0;
        ui->pushButton_Start->setStyleSheet("border-image: url(:/start_1.png);");

        for (int i=0; i < stopwatch_item_flag; i++) {
            delete stopwatch_w[i];
            delete stopwatch_aItem[i];
        }
        stopwatch_item_flag = 0;
    }
}

//窗口关闭
void Clock::on_pushButton_5_clicked()
{
    this->close();
}

//窗口最小化
void Clock::on_pushButton_4_clicked()
{
    this->showMinimized();
}

//倒计时切换
void Clock::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton->setStyleSheet("background-color: rgba(39,207,129,0.9); border-radius:4px;");
    ui->label->setStyleSheet("color: rgb(39, 207, 129);");
    ui->pushButton_2->setStyleSheet("background-color: rgb(14, 19, 22);");
    ui->label_2->setStyleSheet("color: rgb(255, 255, 255);");
    ui->pushButton_3->setStyleSheet("background-color: rgb(14, 19, 22);");
    ui->label_3->setStyleSheet("color: rgb(255, 255, 255);");

    ui->pushButton->setFlat(0);
    ui->pushButton_2->setFlat(1);
    ui->pushButton_3->setFlat(1);
}

//闹钟窗口切换
void Clock::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->pushButton_2->setStyleSheet("background-color: rgba(39,207,129,0.9); border-radius:4px;");
    ui->label_2->setStyleSheet("color: rgb(39, 207, 129);");
    ui->pushButton->setStyleSheet("background-color: rgb(14, 19, 22);");
    ui->label->setStyleSheet("color: rgb(255, 255, 255);");
    ui->pushButton_3->setStyleSheet("background-color: rgb(14, 19, 22);");
    ui->label_3->setStyleSheet("color: rgb(255, 255, 255);");

    ui->pushButton->setFlat(1);
    ui->pushButton_2->setFlat(0);
    ui->pushButton_3->setFlat(1);
}

//秒表窗口切换
void Clock::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->pushButton_3->setStyleSheet("background-color:rgba(39,207,129,0.9); border-radius:4px;");
    ui->label_3->setStyleSheet("color: rgb(39, 207, 129);");
    ui->pushButton_2->setStyleSheet("background-color: rgb(14, 19, 22);");
    ui->label_2->setStyleSheet("color: rgb(255, 255, 255);");
    ui->pushButton->setStyleSheet("background-color: rgb(14, 19, 22);");
    ui->label->setStyleSheet("color: rgb(255, 255, 255);");

    ui->pushButton->setFlat(1);
    ui->pushButton_2->setFlat(1);
    ui->pushButton_3->setFlat(0);
}


//------------------------------------------------------------闹钟----------------------------------

//闹钟上方电子表
void Clock::text_timerUpdate()
{
    QTime time = QTime::currentTime();
    ui->label_6->setText(time.toString("hh")+":"+time.toString("mm")+":"+time.toString("ss"));
}


//动态监控闹钟与本地时间
void Clock::timerUpdate()
{

    //qDebug() << "timerupdate" << n++;

    QTime time = QTime::currentTime();
    int timeH = time.hour();
    int timeM = time.minute();
    int timeS = time.second();

    ui->label_6->setText(time.toString("hh")+":"+time.toString("mm")+":"+time.toString("ss"));

    int rowNum = model->rowCount();
    for(int i=0; i<rowNum; i++)
    {

        if( model->index(i, 3).data().toInt() == 1){
            //qDebug() << "---------------continut--"<<"--"<< i<<"--"<<model->index(i, 3).data().toInt();
            continue;

        }
        if(timeH == model->index(i, 0).data().toInt()
                && timeM == model->index(i, 1).data().toInt()
                && timeS == 0)
        {
            mediaList->addMedia(QUrl::fromLocalFile(model->index(i, 2).data().toString()));
            mediaList->setCurrentIndex(i);
            player->setPlaylist(mediaList);
            qDebug() << mediaList;
            player->setVolume(99);
            player->setMedia(QUrl::fromLocalFile("/home/hyd/桌面/sax.mp3"));
            player->play();

            QMessageBox::warning(this, "警告", "时间到！", QMessageBox::Yes);
        }
    }
    update();
}

//重绘窗口，更新闹钟
void Clock::updateAlarmClock()
{
    int rowNum = model->rowCount();

    for(int alarmNum=0; alarmNum<rowNum; alarmNum++)
    {
        aItem[alarmNum] =new QListWidgetItem;
        aItem[alarmNum]->setSizeHint(QSize(376,58));
        aItem[alarmNum]->setTextColor(QColor(255, 0, 0, 255));
        ui->listWidget->addItem(aItem[alarmNum]);
        ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        w1[alarmNum] = new item_new(ui->listWidget);
        ui->listWidget->setItemWidget(aItem[alarmNum],w1[alarmNum]);

        change_time_NUM(model->index(alarmNum, 0).data().toInt(),model->index(alarmNum, 1).data().toInt());//转换int为QString
        w1[alarmNum]->alarmLabel0->setText(alarmHour_str+" : "+alarmMinute_str);

        //闹钟开关
        if(model->index(alarmNum, 3).data().toInt() == 1){
            w1[alarmNum]->alarm_on_off0->setStyleSheet("border-image: url(:/alarm_off.png);background-color: rgb();");
        }else {
            w1[alarmNum]->alarm_on_off0->setStyleSheet("border-image: url(:/alarm_on.png);background-color: rgb();");
        }
        w1[alarmNum]->alarmLabel_w0->setText(model->index(alarmNum, 14).data().toString());
        w1[alarmNum]->alarmLabel_s0->setText(model->index(alarmNum, 5).data().toString());

        connect( w1[alarmNum]->alarm_on_off0, SIGNAL(clicked()), this, SLOT(On_Off_Alarm()) );
    }
}

//修改时间单数 为两位数
void Clock::change_time_NUM(int alarmHour, int alarmMinute)
{
    if(alarmHour < 10){
        QString hours_str = QString::number(alarmHour);
        alarmHour_str = "0"+hours_str;
    }else {
        alarmHour_str = QString::number(alarmHour);
    }

    if(alarmMinute < 10){
        QString minute_str = QString::number(alarmMinute);
        alarmMinute_str = "0"+minute_str;
    }else {
        alarmMinute_str = QString::number(alarmMinute);
    }
}

void Clock::cancelAlarmClock()
{
    dialog->close();
}

void Clock::stopPlayMusic()
{
    player->stop();
}

void Clock::selectMusic()
{
    musicPath = QFileDialog::getOpenFileName(this, "选择铃声",
                                             "G:/歌曲", "*.mp3");
}
void Clock::rePlayMusic()
{
    player->play();
}

//增加item
void Clock::aItem_new()
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

//新建闹钟按钮回调
void Clock::set_Alarm_Clock()
{
    ui->set_page->raise();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();
    ui->set_alarm_savebtn->show();
    ui->set_alarm_cancelbtn->show();
    timer_set_page->start();
    ui->label_13->setText("新建闹钟");
    repeat_new_or_edit_flag = 0;

    repeat_str_model = tr("不重复");
    ui->pushButton_6->setText(repeat_str_model);
    time_music_str_model = tr("1分钟(默认)");
    ui->pushButton_17->setText(time_music_str_model);
    music_str_model = tr("鸟鸣(默认)");
    ui->pushButton_11->setText(music_str_model);
    clock_name = "闹钟";
    ui->pushButton_18->setText(clock_name);
}

//闹钟新建界面保存回调
void Clock::set_alarm_save()
{
    int rowNum;

    rowNum = model->rowCount();
    qDebug() << rowNum << "闹钟数";
    if(rowNum < 20)
    {
        model->insertRow(rowNum);
        model->setData(model->index(rowNum, 0), timer_alarm_start24->m_currentValue);
        model->setData(model->index(rowNum, 1), timer_alarm_start60->m_currentValue);
        model->setData(model->index(rowNum, 2), music_str_model);
        model->setData(model->index(rowNum, 3), int(0));
        model->setData(model->index(rowNum, 4), int(model->index(rowNum-1, 4).data().toInt()+1));
        qDebug()<<repeat_str_model<<"r111111111111111";
        model->setData(model->index(rowNum, 5), repeat_str_model);
        model->setData(model->index(rowNum, 13), time_music_str_model);
        model->setData(model->index(rowNum, 14), clock_name);
        qDebug() << repeat_str;

        for (int i=0; i<7; i++) {
            if(repeat_day[i])
            {
                model->setData(model->index(rowNum, i+6), 1);
            }
            else {
                model->setData(model->index(rowNum, i+6), 0);
            }
        }

        model->submitAll();

        for(int i=0; i<rowNum; i++)
        {
            delete aItem[i];
            delete w1[i];
        }
        qDebug() << model->index(rowNum, 0).data().toString()
                 << model->index(rowNum, 1).data().toString()
                 << QFileInfo( model->index(rowNum, 2).data().toString() ).fileName();

        updateAlarmClock();
    }
    else
    {
        QMessageBox::warning(this, "警告", "闹钟数量已达上限！", QMessageBox::Yes);
    }
    ui->stackedWidget_3->raise();
    this->raise();
    ui->stackedWidget->raise();//将页面放置最前方
    timer_set_page->stop();
}

//闹钟新建与重编辑界面剩余时间显示
void Clock::verticalscroll_ring_time()
{
    int x_h, x_m ;

    QTime time = QTime::currentTime();
    int timeH = time.hour();
    int timeM = time.minute();

    int hour_time = timer_alarm_start24->m_currentValue;
    int minute_time= timer_alarm_start60->m_currentValue;

    if(hour_time > timeH){
        x_h = hour_time - timeH;
    }else{
        x_h = hour_time + 24 - timeH;
    }

    if(minute_time > timeM){
        x_m = minute_time - timeM;
    }else {
        x_m = minute_time + 60 - timeM;
        x_h --;
    }
    if(x_m == 60)
    {
        x_m = 0;
        x_h++;
    }
    ui->label_12->setText(QString::number(x_h)+"小时"+QString::number(x_m)+"分钟后铃响");
}

//闹钟新建界面取消回调
void Clock::alarm_Cancel_save()
{
    ui->stackedWidget_3->raise();
    this->raise();
    ui->stackedWidget->raise();
    timer_set_page->stop();
}

//双击闹钟打开重编辑页面
void Clock::listdoubleClickslot()
{
    ui->pushButton_8->show();
    ui->pushButton_9->show();
    ui->set_alarm_savebtn->hide();
    ui->set_alarm_cancelbtn->hide();
    timer_alarm_start24->m_currentValue=model->index(ui->listWidget->currentRow(), 0).data().toInt();
    timer_alarm_start60->m_currentValue=model->index(ui->listWidget->currentRow(), 1).data().toInt();
    ui->set_page->raise();
    timer_set_page->start();
    ui->label_13->setText("编辑闹钟");
    repeat_new_or_edit_flag = 1;

    int num = ui->listWidget->currentRow();

    qDebug() << num  <<model->index(num, 5).data().toString();
    qDebug() << num  <<model->index(num, 2).data().toString();

    ui->pushButton_6->setText(model->index(num, 5).data().toString());
    repeat_str_model = model->index(num, 5).data().toString();
    ui->pushButton_11->setText(model->index(num, 2).data().toString());
    music_str_model = model->index(num, 2).data().toString();
    ui->pushButton_17->setText(model->index(num, 13).data().toString());
    time_music_str_model = model->index(num, 13).data().toString();
    clock_name = model->index(num, 14).data().toString();
    ui->pushButton_18->setText(clock_name);
}


//闹钟重编辑保存回调
void Clock::on_pushButton_9_clicked()
{
    int rowNum = ui->listWidget->currentRow();

    qDebug() << rowNum << "要修改的闹钟号";

    model->setData(model->index(rowNum, 0), timer_alarm_start24->m_currentValue);
    model->setData(model->index(rowNum, 1), timer_alarm_start60->m_currentValue);
    model->setData(model->index(rowNum, 2), music_str_model);
    model->setData(model->index(rowNum, 5), repeat_str_model);
    model->setData(model->index(rowNum, 13), time_music_str_model);
    model->setData(model->index(rowNum, 14), clock_name);

    for (int i=0; i<7; i++) {
        if(repeat_day[i])
        {
            model->setData(model->index(rowNum, i+6), 1);
        }
        else {
            model->setData(model->index(rowNum, i+6), 0);
        }
    }

    // alarmLabel
    model->submitAll();

    int m = model->rowCount();
    for(int i=0; i<m; i++)  //每次updateAlarmClock()之前，删除全部闹钟相关控件
    {
        delete aItem[i];
        delete w1[i];
    }

    qDebug() << model->index(rowNum, 0).data().toString()
             << model->index(rowNum, 1).data().toString()
             << QFileInfo( model->index(rowNum, 2).data().toString() ).fileName();

    updateAlarmClock();

    ui->stackedWidget_3->raise();
    this->raise();
    ui->stackedWidget->raise();//将页面放置最前方
    timer_set_page->stop();

}


//单击闹钟显示铃声剩余时间
void Clock::listClickslot()
{

    timer_21111->start();

    int x_h, x_m ;
    int num=ui->listWidget->currentRow();
   // qDebug() <<num;

    QTime time = QTime::currentTime();
    int timeH = time.hour();
    int timeM = time.minute();

    int hour_time = model->index(num, 0).data().toInt();
    int minute_time= model->index(num, 0).data().toInt();

    if(hour_time > timeH){
        x_h = hour_time - timeH;
    }else{
        x_h = hour_time + 24 - timeH;
    }

    if(minute_time > timeM){
        x_m = minute_time - timeM;
    }else {
        x_m = minute_time + 60 - timeM;
        x_h --;
    }
    if(num < 0){
        ui->label_7->setText(QApplication::translate("Clock", "\347\202\271\345\207\273\351\227\271\351\222\237\346\230\276\347\244\272\345\211\251\344\275\231\346\227\266\351\227\264", nullptr));
    }else{
        ui->label_7->setText(QString::number(x_h)+"小时"+QString::number(x_m)+"分钟后铃响");
    }
}

//闹钟重编辑页面删除闹钟回调
void Clock::deleteAlarm()
{
    int num=ui->listWidget->currentRow();
    int rowNum = model->rowCount();

    model->removeRows(num, 1);
    qDebug() << "delete " <<num;

    int ok = QMessageBox::warning(this, "删除当前闹钟！",
                                  "您确定删除当前闹钟吗？",
                                  QMessageBox::Yes, QMessageBox::No);
    if(ok == QMessageBox::No)
    {
        model->revertAll();
        qDebug() << rowNum;
    }
    else
    {
        for(int i=0; i<rowNum; i++)
        {
            delete aItem[i];
            delete w1[i];
        }

        model->submitAll();   //否则提交, 在数据库中删除该行

        updateAlarmClock();

        rowNum = model->rowCount();

        qDebug() << rowNum;

        ui->stackedWidget_3->raise();
        this->raise();
        ui->stackedWidget->raise();//将页面放置最前方
    }
    timer_set_page->stop();
}

//闹钟开关
void Clock::On_Off_Alarm()
{
    int i=0 ;
    QPushButton *btn = qobject_cast<QPushButton*>(QObject::sender());
    while (btn != w1[i]->alarm_on_off0) {
        i++;
    }
    if(model->index(i, 3).data().toInt() == 0){
        btn->setStyleSheet("border-image: url(:/alarm_off.png);background-color: rgb();");
        qDebug() << "off";

        model->setData(model->index(i, 3), int(1));
        model->submitAll();
    } else {

        btn->setStyleSheet("border-image: url(:/alarm_off.png);background-color: rgb();");
        qDebug() << "on";

        model->setData(model->index(i, 3), int(0));
        model->submitAll();
    }


    int rowNum = model->rowCount();
    for(int i=0; i<rowNum; i++)
    {
        delete aItem[i];
        delete w1[i];
    }
    updateAlarmClock();
}

//------------------------------------------------------倒计时--------------------------------------------------------------------

//倒计时执行
void Clock::stat_countdown(){
    QString h; QString m; QString s;

    if(countdown_hour < 10){
        QString hours_str = QString::number(countdown_hour);
        h = "0"+hours_str;
    }else {
        h = QString::number(countdown_hour);
    }

    if(countdown_minute < 10){
        QString minute_str = QString::number(countdown_minute);
        m = "0"+minute_str;
    }else {
        m = QString::number(countdown_minute);
    }

    if(countdown_second < 10){
        QString second_str = QString::number(countdown_second);
        s = "0"+second_str;
    }else {
        s = QString::number(countdown_second);
    }

    ui->label_9->setText(h+":"+m+":"+s);

    if(countdown_hour==0 && countdown_minute==0 && countdown_second==0){
        player->setMedia(QUrl::fromLocalFile("/home/hyd/桌面/sax.mp3"));
        player->play();
        QMessageBox::warning(this, "Warning", "该休息了");
        player->stop();
        countdown_timer->stop();
        startbtn_countdown();
    }

    countdown_second--;
    if(countdown_second==-1){
        countdown_minute--;
        countdown_second=59;
    }
    if(countdown_minute==-1){
        countdown_hour--;
        countdown_minute=59;
    }
    int ringmax = timer_ring99->m_currentValue*3600 + timer_ring60->m_currentValue*60 + timer_ring60_2->m_currentValue;
    ui->page_5->RoundBar3->time_max = ringmax;
}
//倒计时开始-结束
void Clock::startbtn_countdown(){
    if (!countdown_isStarted){
        if(timer_ring99->m_currentValue==0 && timer_ring60->m_currentValue==0 && timer_ring60_2->m_currentValue==0){
            return;
        }
        //int ringmax = timer_ring99->m_currentValue*3600 + timer_ring60->m_currentValue*60 + timer_ring60_2->m_currentValue;
        ui->page_5->RoundBar3->ring_max = 1002;

        ui->count_stat->setStyleSheet("width:100px;\
                                      height:32px;\
                        background:rgba(44,44,46,1);\
                        border:1px solid rgba(68,68,71,1);\
                        border-radius:4px;\
                        font: 11pt 'Sans Serif'");

        countdown_timer->start();
        ui->page_5->timer->start();
        countdown_isStarted=1;
        ui->count_stat->setText("结束");
        ui->stackedWidget_4->setCurrentIndex(1);

        setcoutdown_number(timer_ring99->m_currentValue, timer_ring60->m_currentValue, timer_ring60_2->m_currentValue);//获取转轮当前值

    } else {
        ui->count_stat->setStyleSheet("color: rgb(255, 255, 255);\
                                      background-color: rgba(39,207,129,0.9);\
                                       border-radius:4px;\
                                      font: 11pt 'Sans Serif';\
;");

        countdown_timer->stop();
        ui->page_5->timer->stop();
        countdown_isStarted=0;
        ui->count_stat->setText("开始");
        ui->label_9->setText("00:00:00");
        ui->label_8->setText("00:00:00");
        ui->stackedWidget_4->setCurrentIndex(0);
    }
    return;
}
//设置初始时间
void Clock::setcoutdown_number(int h1, int m1, int s1){
    countdown_hour=h1; countdown_minute=m1 ; countdown_second=s1;
    QString h; QString m; QString s;

    if(countdown_hour < 10){
        QString hours_str = QString::number(countdown_hour);
        h = "0"+hours_str;
    }else {
        h = QString::number(countdown_hour);
    }

    if(countdown_minute < 10){
        QString minute_str = QString::number(countdown_minute);
        m = "0"+minute_str;
    }else {
        m = QString::number(countdown_minute);
    }

    if(countdown_second < 10){
        QString second_str = QString::number(countdown_second);
        s = "0"+second_str;
    }else {
        s = QString::number(countdown_second);
    }

    ui->label_9->setText(h+":"+m+":"+s);
    ui->label_8->setText(h+":"+m+":"+s);
    //ui->page_5->a =countdown_hour*3600+countdown_minute*60+countdown_second;

    get_countdown_over_time();
}

//倒计时5分钟
void Clock::on_min_5btn_clicked()
{
    timer_ring99->m_currentValue = 0;
    timer_ring60->m_currentValue = 5;
    timer_ring60_2->m_currentValue = 0;
    setcoutdown_number(0, 5, 0);
}
//倒计时10分钟
void Clock::on_min_10btn_clicked()
{
    timer_ring99->m_currentValue = 0;
    timer_ring60->m_currentValue = 10;
    timer_ring60_2->m_currentValue = 0;
    setcoutdown_number(0, 10, 0);
}
//倒计时20分钟
void Clock::on_min_20btn_clicked()
{
    timer_ring99->m_currentValue = 0;
    timer_ring60->m_currentValue = 20;
    timer_ring60_2->m_currentValue = 0;
    setcoutdown_number(0, 20, 0);
}
//倒计时30分钟
void Clock::on_min_30btn_clicked()
{
    timer_ring99->m_currentValue = 0;
    timer_ring60->m_currentValue = 30;
    qDebug() << timer_ring60->m_currentValue <<"---timer_ring60->m_currentValue";
    timer_ring60_2->m_currentValue = 0;
    setcoutdown_number(0, 30, 0);
}
//倒计时60分钟
void Clock::on_min_60btn_clicked()
{
    timer_ring99->m_currentValue = 1;
    timer_ring60->m_currentValue = 0;
    timer_ring60_2->m_currentValue = 0;
    setcoutdown_number(1,0, 0);
}
//获取倒计时结束时间
void Clock::get_countdown_over_time()
{
    int x_h, x_m ;
    QTime time = QTime::currentTime();
    int timeH = time.hour();
    int timeM = time.minute();

    x_h = countdown_hour + timeH;
    x_m = countdown_minute + timeM;

    if(x_m >= 60){
        x_m = x_m - 60;
        x_h ++;
    }
    if(x_h >= 24){
        x_h = x_h - 24;
        ui->label_11->setText("明日"+QString::number(x_h)+":"+QString::number(x_m));
    }else if(x_h >= 12){
        x_h = x_h - 12;
        ui->label_11->setText("下午"+QString::number(x_h)+":"+QString::number(x_m));
    }else {
        ui->label_11->setText("上午"+QString::number(x_h)+":"+QString::number(x_m));
    }
}
//倒计时-暂停开始
void Clock::on_count_push_clicked()
{
    if (!countdown_isStarted){
        ui->count_push->setStyleSheet("border-image: url(:/push_1.png);");
        countdown_timer->start();
        ui->page_5->timer->start();
        countdown_isStarted=1;

    } else {
        ui->count_push->setStyleSheet("border-image: url(:/continu.png);");
        countdown_timer->stop();
        ui->page_5->timer->stop();
        countdown_isStarted=0;
    }
    return;
}
//倒计时初始数字转盘
void Clock::countdown_set_start_time()
{
    DotLineDemo *ring_widget = new DotLineDemo(ui->page_4);
    ring_widget->move(0,0);

    timer_ring99 = new VerticalScroll_99(ring_widget);
    QLabel * h_in_m = new QLabel (ring_widget);
    timer_ring60 = new VerticalScroll_60(ring_widget);
    QLabel * m_in_s = new QLabel (ring_widget);
    timer_ring60_2 = new VerticalScroll_60(ring_widget);

    QLabel * hour_ring = new QLabel (ring_widget);
    QLabel * min_ring = new QLabel (ring_widget);
    QLabel * sec_ring = new QLabel (ring_widget);

    hour_ring->resize(30,30);
    hour_ring->setText(tr("时"));
    hour_ring->setStyleSheet("font: 13pt 'Sans Serif';color: rgb(148, 148, 148);");
    min_ring->resize(30,30);
    min_ring->setText(tr("分"));
    min_ring->setStyleSheet("font: 13pt 'Sans Serif';color: rgb(148, 148, 148);");
    sec_ring->resize(30,30);
    sec_ring->setText(tr("秒"));
    sec_ring->setStyleSheet("font: 13pt 'Sans Serif';color: rgb(148, 148, 148);");

    h_in_m->resize(10,40);
    h_in_m->setText(":");
    h_in_m->setStyleSheet("font: 30pt 'Sans Serif';");
    m_in_s->resize(10,40);
    m_in_s->setText(":");
    m_in_s->setStyleSheet("font: 30pt 'Sans Serif';");

    timer_ring99->move(129, 115);
    hour_ring->move(145,110);
    h_in_m->move(185,192);
    timer_ring60->move(201, 115);
    min_ring->move(217,110);
    m_in_s->move(257,192);
    timer_ring60_2->move(273, 115);
    sec_ring->move(289,110);
}




//-----------------------------------------闹钟初始化--------------------------------------------
//闹钟初始化数字转盘
void Clock::alarm_set_start_time()
{
    timer_alarm_start24 = new VerticalScroll_24(ui->set_page);
    QLabel * h_in_m = new QLabel (ui->set_page);
    timer_alarm_start60 = new VerticalScroll_60(ui->set_page);

    QLabel * hour_ring = new QLabel (ui->set_page);
    QLabel * min_ring = new QLabel (ui->set_page);

    h_in_m->resize(10,40);
    h_in_m->setText(":");
    h_in_m->setStyleSheet("font: 30pt 'Sans Serif';");

    hour_ring->resize(30,30);
    hour_ring->setText(tr("时"));
    hour_ring->setStyleSheet("font: 13pt 'Sans Serif';color: rgb(148, 148, 148);");
    min_ring->resize(30,30);
    min_ring->setText(tr("分"));
    min_ring->setStyleSheet("font: 13pt 'Sans Serif';color: rgb(148, 148, 148);");

    timer_alarm_start24->move(161, 105);
    hour_ring->move(177,100);
    h_in_m->move(217,182);
    timer_alarm_start60->move(233, 105);
    min_ring->move(249,100);
}
//闹钟初始化工作日选择
void Clock::alarm_repeat()
{
    int num;
    if(repeat_new_or_edit_flag)
        num = ui->listWidget->currentRow();
    else {
        num= model->rowCount();
    }

    if(dialog_repeat)
    {
        alarm_repeat_flag = 0;
        dialog_repeat->close();
        repeat_str = "";
        dialog_repeat = nullptr;
    }
    else {
        dialog_repeat = new  set_alarm_repeat_Dialog(ui->set_page, 9);
        dialog_repeat->setWindowFlags(Qt::FramelessWindowHint);
        dialog_repeat->move(87,412);
        dialog_repeat->widget[0]->alarmLabel0->setText(tr("不重复"));
        dialog_repeat->widget[1]->alarmLabel0->setText(tr("工作日"));
        dialog_repeat->widget[2]->alarmLabel0->setText(tr("周一"));
        dialog_repeat->widget[3]->alarmLabel0->setText(tr("周二"));
        dialog_repeat->widget[4]->alarmLabel0->setText(tr("周三"));
        dialog_repeat->widget[5]->alarmLabel0->setText(tr("周四"));
        dialog_repeat->widget[6]->alarmLabel0->setText(tr("周五"));
        dialog_repeat->widget[7]->alarmLabel0->setText(tr("周六"));
        dialog_repeat->widget[8]->alarmLabel0->setText(tr("周日"));
        for (int i=0; i<7; i++) {
            if(model->index(num, 6+i).data().toInt())
            {
                dialog_repeat->widget[i+2]->alarmLabel1->setIcon(repeat_on_Pixmap);
                repeat_day[i] = 1;
            }
            else {
                dialog_repeat->widget[i+2]->alarmLabel1->setIcon(repeat_off_Pixmap);
                repeat_day[i] = 0;
            }
        }
        dialog_repeat->show();
        connect(dialog_repeat->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(repeat_listClickslot()));
    }
}
//重复选项单击回调
void Clock::repeat_listClickslot()
{
    int num=dialog_repeat->listWidget->currentRow();
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
         ui->pushButton_6->setText(tr("不重复"));
         repeat_str_model = "不重复";
         for (int i=0; i<7; i++) {
             repeat_day[i] = 0;
             qDebug() << repeat_day[i];
             dialog_repeat->widget[i+2]->alarmLabel1->setIcon(repeat_off_Pixmap);
         }
         dialog_repeat->close();
         dialog_repeat = nullptr;
         return;
         break;
     case 1:
         ui->pushButton_6->setText(tr("工作日"));
         repeat_str_model = "工作日";
         for (int i=0; i<5; i++) {
             repeat_day[i] = 1;
             qDebug() << repeat_day[i];
             dialog_repeat->widget[i+2]->alarmLabel1->setIcon(repeat_on_Pixmap);
         }
         dialog_repeat->widget[7]->alarmLabel1->setIcon(repeat_on_Pixmap);
         dialog_repeat->widget[8]->alarmLabel1->setIcon(repeat_on_Pixmap);
         dialog_repeat->close();
         dialog_repeat = nullptr;
         return;
         break;
     case 2:
         if(repeat_day[0] == 0 )
         {
             repeat_day[0] = 1;
             dialog_repeat->widget[2]->alarmLabel1->setIcon(repeat_on_Pixmap);
         }else {
             repeat_day[0] = 0;
             dialog_repeat->widget[2]->alarmLabel1->setIcon(repeat_off_Pixmap);
         }
         break;
     case 3:
         if(repeat_day[1] == 0 )
         {
             repeat_day[1] = 1;
             dialog_repeat->widget[3]->alarmLabel1->setIcon(repeat_on_Pixmap);
         }else {
             repeat_day[1] = 0;
             dialog_repeat->widget[3]->alarmLabel1->setIcon(repeat_off_Pixmap);
         }
         break;
    case 4:
        if(repeat_day[2] == 0 )
        {
            repeat_day[2] = 1;
            dialog_repeat->widget[4]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }else {
            repeat_day[2] = 0;
            dialog_repeat->widget[4]->alarmLabel1->setIcon(repeat_off_Pixmap);
        }
        break;
    case 5:
        if(repeat_day[3] == 0 )
        {
            repeat_day[3] = 1;
            dialog_repeat->widget[5]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }else {
            repeat_day[3] = 0;
            dialog_repeat->widget[5]->alarmLabel1->setIcon(repeat_off_Pixmap);
        }
        break;
    case 6:

        if(repeat_day[4] == 0 )
        {
            repeat_day[4] = 1;
            dialog_repeat->widget[6]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }else {
            repeat_day[4] = 0;
            dialog_repeat->widget[6]->alarmLabel1->setIcon(repeat_off_Pixmap);
        }
        break;
    case 7:

        if(repeat_day[5] == 0 )
        {
            repeat_day[5] = 1;
            dialog_repeat->widget[7]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }else {
            repeat_day[5] = 0;
            dialog_repeat->widget[7]->alarmLabel1->setIcon(repeat_off_Pixmap);
        }
        break;
    case 8:

        if(repeat_day[6] == 0 )
        {
            repeat_day[6] = 1;
            dialog_repeat->widget[8]->alarmLabel1->setIcon(repeat_on_Pixmap);
        }else {
            repeat_day[6] = 0;
            dialog_repeat->widget[8]->alarmLabel1->setIcon(repeat_off_Pixmap);
        }
        break;
    default:
        break;
    }
    for (int i=0; i<7; i++) {
        if(repeat_day[i])
        {
            repeat_str=repeat_str+day[i];
        }
    }
    ui->pushButton_6->setText(repeat_str);
    repeat_str_model = repeat_str;
    repeat_str="";
}

//闹钟初始化音乐选择界面回调
void Clock::select_Music()
{
    int num;
    if(repeat_new_or_edit_flag)
        num = ui->listWidget->currentRow();
    else {
        num= model->rowCount();
    }

    if(dialog_music)
    {
        alarm_repeat_flag = 0;
        dialog_music->close();
        dialog_music = nullptr;
    }
    else {
        dialog_music = new  set_alarm_repeat_Dialog(ui->set_page, 6);
        dialog_music->setWindowFlags(Qt::FramelessWindowHint);
        dialog_music->move(87,465);
        dialog_music->widget[0]->alarmLabel0->setText(tr("鸟鸣(默认)"));
        dialog_music->widget[1]->alarmLabel0->setText(tr("雨声"));
        dialog_music->widget[2]->alarmLabel0->setText(tr("滴滴提示声"));
        dialog_music->widget[3]->alarmLabel0->setText(tr("轰鸣声"));
        dialog_music->widget[4]->alarmLabel0->setText(tr("歌曲1"));
        dialog_music->widget[5]->alarmLabel0->setText(tr("歌曲2"));

        dialog_music->show();
        connect(dialog_music->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(music_listClickslot()));
    }
}
//闹钟初始化单击选择音乐
void Clock::music_listClickslot()
{
    int num=dialog_music->listWidget->currentRow();

    switch (num)
    {
    case 0:
        music_str_model=tr("鸟鸣(默认)");
        ui->pushButton_11->setText(music_str_model);
        break;
    case 1:
        music_str_model=tr("雨声");
        ui->pushButton_11->setText(music_str_model);
        break;
    case 2:
        music_str_model=tr("滴滴提示声");
        ui->pushButton_11->setText(music_str_model);
        break;
    case 3:
        music_str_model=tr("轰鸣声");
        ui->pushButton_11->setText(music_str_model);
        break;
    case 4:
        music_str_model=tr("歌曲1");
        ui->pushButton_11->setText(music_str_model);
        break;
    case 5:
        music_str_model=tr("歌曲2");
        ui->pushButton_11->setText(music_str_model);
        break;
    default:
        break;
    }
    dialog_music->close();
    dialog_music = nullptr;
}

void Clock::time_Music()
{
    int num;
    if(repeat_new_or_edit_flag)
        num = ui->listWidget->currentRow();
    else {
        num= model->rowCount();
    }

    if(time_music)
    {
        alarm_repeat_flag = 0;
        time_music->close();
        time_music = nullptr;
    }
    else {
        time_music = new  set_alarm_repeat_Dialog(ui->set_page, 6);
        time_music->setWindowFlags(Qt::FramelessWindowHint);
        time_music->move(87,515);
        time_music->widget[0]->alarmLabel0->setText(tr("1分钟(默认)"));
        time_music->widget[1]->alarmLabel0->setText(tr("2分钟"));
        time_music->widget[2]->alarmLabel0->setText(tr("3分钟"));
        time_music->widget[3]->alarmLabel0->setText(tr("4分钟"));
        time_music->widget[4]->alarmLabel0->setText(tr("5分钟"));
        time_music->widget[4]->alarmLabel0->setText("");

        time_music->show();
        connect(time_music->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(time_music_listClickslot()));
    }
}

void Clock::time_music_listClickslot()
{
    int num=time_music->listWidget->currentRow();
    switch (num)
    {
    case 0:
        time_music_str_model=tr("1分钟(默认)");
        ui->pushButton_17->setText(time_music_str_model);
        break;
    case 1:
        time_music_str_model=tr("2分钟");
        ui->pushButton_17->setText(time_music_str_model);
        break;
    case 2:
        time_music_str_model=tr("3分钟");
        ui->pushButton_17->setText(time_music_str_model);
        break;
    case 3:
        time_music_str_model=tr("4分钟");
        ui->pushButton_17->setText(time_music_str_model);
        break;
    case 4:
        time_music_str_model=tr("5分钟");
        ui->pushButton_17->setText(time_music_str_model);
        break;
    default:
        break;
    }
    time_music->close();
    time_music = nullptr;
}

void Clock::clack_rename()
{
    if(lineEdit)
    {
        clock_name = lineEdit->text();
        ui->pushButton_18->setText(clock_name);
        lineEdit->close();
        lineEdit = nullptr;
    }
    else {
    lineEdit = new QLineEdit(ui->set_page);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
    lineEdit->setGeometry(QRect(60, 220, 280, 36));
    lineEdit->move(87,365);
    lineEdit->setStyleSheet(QString::fromUtf8("width:280px;\n"
"height:36px;\n"
"background:rgba(72,72,76,1);\n"
"border:1px solid;\n"
"font-size:14px;"
"border-image:linear-gradient(0deg, rgba(39,207,129,1), rgba(39,207,129,1)) 10 10;\n"
"border-radius:4px;\n"
"\n"
""));
    lineEdit->show();
    lineEdit->setText("闹钟");
    }
}
