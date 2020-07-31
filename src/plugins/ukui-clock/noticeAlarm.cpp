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
#include "noticeAlarm.h"
#include "ui_noticeAlarm.h"
#include <QPalette>
#include <QSqlTableModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDebug>

Natice_alarm::Natice_alarm(int close_time, int num, QWidget *parent ) :
    QWidget(parent),
    num_flag(num),
    timer_value(close_time),
    ui(new Ui::Natice_alarm)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);
    QPixmap dialogPixmap = QPixmap(":/clock.ico");
    this->setWindowTitle(tr("响铃提示"));
    this->setWindowIcon(dialogPixmap);
    ui->label->setAlignment(Qt::AlignHCenter);
    ui->label_2->setAlignment(Qt::AlignHCenter);
    ui->label_3->setAlignment(Qt::AlignHCenter);
    ui->label_4->setAlignment(Qt::AlignHCenter);


    this->setProperty("blurRegion", QRegion(QRect(1, 1, 1, 1)));

    timer_value2 = timer_value;

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(set_dialog_close()) );
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(set_dialog_close()) );
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(show_again()) );


    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(close_music()));
    timer->setInterval(1000);
    timer->start();

    timer_xumhuan = new QTimer();
    connect(timer_xumhuan, SIGNAL(timeout()), this, SLOT(ring()));
    timer_xumhuan->setInterval(1000);

    natice_init();
    setAttribute(Qt::WA_DeleteOnClose);
}

Natice_alarm::~Natice_alarm()
{
    delete timer;
    delete timer_xumhuan;
    delete ui;
}

void Natice_alarm::natice_init()
{
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("clock");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model_setup = new QSqlTableModel(this);
    model_setup->setTable("setup");
    model_setup->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_setup->select();

    model_setup->select();

    full_flag=model_setup->index(0, 3).data().toInt();
    if(full_flag)
    {
        showFullScreen();
    }
    music = new QMediaPlayer(this);//初始化音乐
                                   // Initialize music
    playlist = new QMediaPlaylist(this);//初始化播放列表
                                        // Initialize playlist
    if(num_flag >= 0)
    {
        if(model->index(num_flag, 2).data().toString().compare(tr("玻璃"))==0){
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/ukui-clock/glass.ogg"));
        } else if (model->index(num_flag, 2).data().toString().compare(tr("犬吠"))==0) {
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/ukui-clock/bark.ogg"));
        } else if (model->index(num_flag, 2).data().toString().compare(tr("声呐"))==0) {
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/ukui-clock/sonar.ogg"));
        } else if (model->index(num_flag, 2).data().toString().compare(tr("雨滴"))==0) {
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/ukui-clock/drip.ogg"));
        }
    } else {
        if (model_setup->index(0, 19).data().toString().compare(tr("玻璃"))==0) {
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/ukui-clock/glass.ogg"));
        } else if(model_setup->index(0, 19).data().toString().compare(tr("犬吠"))==0) {
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/ukui-clock/bark.ogg"));
        } else if(model_setup->index(0, 19).data().toString().compare(tr("声呐"))==0) {
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/ukui-clock/sonar.ogg"));
        } else {
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/ukui-clock/drip.ogg"));
        }
    }

    playlist->setPlaybackMode(QMediaPlaylist::Loop);//设置播放模式(顺序播放，单曲循环，随机播放等)
                                                    // Set playback mode (sequential playback, single loop, random playback, etc.)
    music->setPlaylist(playlist);  //设置播放列表
                                   // Set up playlist
    music->setVolume(  model_setup->index(0, 6).data().toInt() );
    music->play();
}

//窗口关闭
//window closing
void Natice_alarm::set_dialog_close()
{
    timer->stop();
    music->stop();
    this->close();
}
//关闭音乐
//Turn off music
void Natice_alarm::close_music()
{
    if (timer_value == 0) {
        set_dialog_close();
    }
        ui->label_4->setText(QString::number(timer_value)+tr("秒后自动关闭"));
    timer_value--;
}
//绘制背景
// Draw background
void Natice_alarm::paintEvent(QPaintEvent *)
{
    if (!full_flag) {
        return;
    }
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    p.setBrush(QBrush(QColor("#161617")));
    p.setOpacity(0.5);
    p.setPen(Qt::NoPen);

    p.setRenderHint(QPainter::Antialiasing);//反锯齿  Antialiasing
    p.drawRoundedRect(opt.rect,0,0);
    p.drawRect(opt.rect);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
//再次弹出
//Eject again
void Natice_alarm::show_again()
{
    this->hide();
    int remind = model_setup->index(0, 4).data().toInt();
    if (remind == 0) {
        ring_num = 120;
    } else if(remind == 1) {
        ring_num = 300;
    } else if(remind == 2) {
        ring_num = 600;
    } else if(remind == 3) {
        ring_num = 1800;
    } else if(remind == 4) {
        ring_num = 3600;
    }
    timer_value =  timer_value2;
    timer_xumhuan->start();
    timer->stop();
    music->stop();
}
//响铃
//Ring a bell
void Natice_alarm::ring()
{
    ring_num--;
    if (ring_num == 0) {
        natice_init();
        this->show();
        timer->start();
        music->play();
    }
}
