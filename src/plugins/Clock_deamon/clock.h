#ifndef CLOCK_H
#define CLOCK_H


//border-radius:12px;
//opacity:0.95;
//border-radius:6px 6px 0px 0px;


//model_repeat->setData(model_repeat->index(0, 0),1);
//model_repeat->submitAll();
//model_repeat->setTable("clockrepeat");
//model_repeat->select();


#include <QWidget>
#include <QTimer>
#include <QQueue>
#include <QSlider>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include <QLCDNumber>
#include <QMediaPlayer>
#include <QFrame>
#include <item_new.h>
#include <QListWidgetItem>
#include "stopwatch_item.h"
#include <QPaintEvent>
#include "verticalscroll_24.h"
#include "verticalscroll_60.h"
#include "verticalscroll_99.h"
#include "DotLineDemo.h"
#include "set_alarm_repeat_dialog.h"
#include <QPointF>
#include <QLineEdit>


class QSpinBox;
class QComboBox;
class QDialog;
class QSpinBox;
class QComboBox;
class QLabel;
class QFont;
class QPushButton;
class QMediaPlaylist;
class QSqlTableModel;
class QTimer;

namespace Ui {
class Clock;
}

class Clock : public QWidget
{
    Q_OBJECT

public:

    explicit Clock(QWidget *parent = nullptr);
    ~Clock();

    void paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.fillRect(this->rect(), QColor(0, 0, 0, 0x20)); /* 设置透明颜色 */
    }
    //Qt::FramelessWindowHint会导致窗口不能被拖动。通过捕获鼠标移动事件从而实现窗口移动
    void mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton) {
            m_startPoint = frameGeometry().topLeft() - event->globalPos(); /* 捕获按下时坐标 */
        }
    }
    void mouseMoveEvent(QMouseEvent *event)
    {
        this->move(event->globalPos() + m_startPoint); /* 移动窗口 */
    }

    QPointF rotateAngle(int angle, int len);

protected:
    void paintEvent1(QPaintEvent *);

private slots:
    void Count_down();//int Hour,int minute ,int second);

    void on_pushButton_Start_clicked();

    void on_pushButton_ring_clicked();

    void on_pushButton_timeselect_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void timerUpdate();

    void text_timerUpdate();

    void set_Alarm_Clock();                                                          //新建闹钟按钮回调

    void cancelAlarmClock();                                                         //添加闹钟dialog关闭

    void updateAlarmClock();

    void On_Off_Alarm();                                                             //闹钟开关

    void deleteAlarm();

    void stopPlayMusic();

    void selectMusic();

    void rePlayMusic();

    void aItem_new();

    void listdoubleClickslot();                                                          //双击闹钟打开重编辑页面

    void listClickslot();

    void on_pushButton_9_clicked();

    void stat_countdown();

    void setcoutdown_number(int h, int m, int s);

    void startbtn_countdown();

    void on_min_5btn_clicked();

    void on_min_10btn_clicked();

    void on_min_20btn_clicked();

    void on_min_30btn_clicked();

    void on_min_60btn_clicked();

    void get_countdown_over_time();

    void on_count_push_clicked();

    void stopwatch_jg();

    void change_time_NUM(int Hour,int Minute);

    void countdown_set_start_time();

    void alarm_set_start_time();

    void alarm_Cancel_save();

    void set_alarm_save();

    void verticalscroll_ring_time();

    void alarm_repeat();

    void repeat_listClickslot();

    void select_Music();                                                                  //闹钟初始化音乐选择界面回调

    void music_listClickslot();                                                           //闹钟初始化单击选择音乐

    void time_Music();                                                                   //闹钟初始化单击选择音乐播放时长

    void time_music_listClickslot();

    void clack_rename();                                                           //闹钟命名
private:
    QPoint m_startPoint;
    Ui::Clock *ui;
    QTimer *timer = nullptr;
    QTimer *countdown_timer = nullptr;
    QTimer *timer_2 = nullptr;
    int hour, minute, second, pushflag ;
    int stopwatch_hour, stopwatch_minute, stopwatch_second ;
    int countdown_hour, countdown_minute, countdown_second, countdown_pushflag ;
    bool isStarted;
    bool countdown_isStarted;
    bool stopwatch_isStarted;
    QMediaPlayer *player = new QMediaPlayer;
    QString ring;//铃声名字

    int alarmHour;
    int alarmMinute;
    int cPauseTime;

    QPixmap pixmap1;
    QPixmap pixmap2;
    QPixmap pixmap3;
    QPixmap pixmap4;
    QPixmap pixmap5;
    QPixmap pixmap6;
    QPixmap pixmap7;
    QPixmap pixmap8;
    QPixmap pixmap9;
    QPixmap pixmap10;
    QPixmap pixmap11;

    QPixmap bgPixmap;
    QPixmap repeat_on_Pixmap;
    QPixmap repeat_off_Pixmap;
    QPixmap hourPixmap;
    QPixmap minutePixmap;
    QPixmap secondPixmap;
    QPixmap delBtnPixmap;
    QPixmap on_pixmap;
    QPixmap off_pixmap;

    QLabel *cTimeLabe;

    QDialog *dialog;
    QFont alarmFont;
    QSpinBox *hourBox;
    QSpinBox *minuteBox;
    QComboBox *pauseTime;

    QMediaPlayer *player_alarm;
    QMediaPlaylist *mediaList; //播放列表
    QSqlTableModel *model;  //数据库
    QSqlTableModel *model_repeat;
    QString musicPath;

    item_new *w1[20];
    QListWidgetItem *aItem[20];
    stopwatch_item *stopwatch_w[100];
    QListWidgetItem *stopwatch_aItem[100];
    QString stopwatch_h;QString stopwatch_m;QString stopwatch_s;
    QString stopwatch_jg_h ="00";QString stopwatch_jg_m= "00";QString stopwatch_jg_s= "00";
    QString alarmHour_str; QString alarmMinute_str;

    int stopwatch_item_flag = 0;
    int clock_num = 0;
    int on_off_flag = 0;
    int add_change_flag = 0;
    int change_alarm_line = 0;
    int n = 0;
    int medel_flag = 0;
    int continu_flag = 0;
    int alarm_repeat_flag = 0;


    QTimer *timer_21111;
    QTimer *timer_set_page;
    VerticalScroll_99 * timer_ring99;
    VerticalScroll_60 * timer_ring60;
    VerticalScroll_60 * timer_ring60_2;
    VerticalScroll_24 * timer_alarm_start24;
    VerticalScroll_60 * timer_alarm_start60;

    set_alarm_repeat_Dialog *dialog_repeat = nullptr;
    set_alarm_repeat_Dialog *dialog_music = nullptr;
    set_alarm_repeat_Dialog *time_music = nullptr;
    QString repeat_str;
    QString repeat_str_model;
    QString music_str_model;
    QString time_music_str_model;
    QString clock_name;
    QLineEdit *lineEdit= nullptr ;

    int repeat_day[9];   //重复日选择保存中介
    int repeat_new_or_edit_flag;  //重复日判断 是新建,还是重编辑,两者获取数据库号不同;
};


#endif // CLOCK_H
