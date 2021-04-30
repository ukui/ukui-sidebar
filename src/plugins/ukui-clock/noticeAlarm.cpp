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
#include <QPainterPath>
#include <X11/Xlib.h>
#include "xatom-helper.h"

extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);

Natice_alarm::Natice_alarm(int close_time, int num, QWidget *parent ) :
    QWidget(parent),
    num_flag(num),
    timer_value(close_time),
    ui(new Ui::Natice_alarm)
{
    //setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);

    Qt::WindowFlags m_flags = windowFlags();
    this->setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);

    // 添加窗管协议
    MotifWmHints hints;
    hints.flags = MWM_HINTS_FUNCTIONS|MWM_HINTS_DECORATIONS;
    hints.functions = MWM_FUNC_ALL;
    hints.decorations = MWM_DECOR_BORDER;
    XAtomHelper::getInstance()->setWindowMotifHint(this->winId(), hints);

    this->setFixedSize(270,162);
    QPixmap dialogPixmap = QPixmap(":/clock.ico");
    this->setWindowTitle(tr("Ring prompt"));
    this->setWindowIcon(dialogPixmap);

    ui->label_2->setAlignment(Qt::AlignHCenter);
    ui->label_3->setAlignment(Qt::AlignHCenter);
    ui->label_4->setAlignment(Qt::AlignHCenter);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::gray);
    ui->label_4->setPalette(pa);

    //this->setProperty("blurRegion", QRegion(QRect(1, 1, 1, 1)));

    timer_value2 = timer_value;

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(set_dialog_close()) );
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(set_dialog_close()) );
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(show_again()) );

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(close_music()));
    timer->setInterval(1000);
    timer->start();

    timer_xumhuan = new QTimer();
    //每秒执行一次
    connect(timer_xumhuan, SIGNAL(timeout()), this, SLOT(ring()));
    timer_xumhuan->setInterval(1000);

    natice_init();
    setAttribute(Qt::WA_DeleteOnClose);
    //ui->widget->installEventFilter(this);

    QPalette palette = ui->pushButton_3->palette();
    QColor ColorPlaceholderText(61,107,229,255);
    QBrush brush2;
    brush2.setColor(ColorPlaceholderText);
    palette.setColor(QPalette::Button,QColor(61,107,229,255));
    palette.setBrush(QPalette::ButtonText, QBrush(Qt::white));
    ui->pushButton_3->setPalette(palette);

    QPalette palette1 = ui->pushButton->palette();
    QColor ColorPlaceholderText1(255,255,255,0);
    QBrush brush;
    brush.setColor(ColorPlaceholderText1);
    palette.setBrush(QPalette::Button, brush);
    ui->pushButton->setPalette(palette1);

    ui->pushButton->setIcon(QIcon::fromTheme("window-close-symbolic"));
    ui->pushButton->setProperty("isWindowButton", 0x2);
    ui->pushButton->setProperty("useIconHighlightEffect", 0x8);
    ui->pushButton->setFlat(true);

    this->setWindowIcon(QIcon::fromTheme("kylin-alarm-clock",QIcon(":/image/kylin-alarm-clock.svg")));
    ui->titleIcon->setPixmap(QIcon::fromTheme("kylin-alarm-clock").pixmap(24,24));
    //固定字体大小，避免放大覆盖
    QFont font;
    font.setPixelSize(14);
    ui->label->setStyleSheet("font-size : 14px;");
    ui->label_3->setStyleSheet("font-size : 14px;");
    ui->label_4->setStyleSheet("font-size : 14px;");
    ui->pushButton_2->setFont(font);
    ui->pushButton_3->setFont(font);
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
        if(model->index(num_flag, 2).data().toString().compare(tr("glass"))==0){
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/ukui-clock/glass.ogg"));
        } else if (model->index(num_flag, 2).data().toString().compare(tr("bark"))==0) {
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/ukui-clock/bark.ogg"));
        } else if (model->index(num_flag, 2).data().toString().compare(tr("sonar"))==0) {
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/ukui-clock/sonar.ogg"));
        } else if (model->index(num_flag, 2).data().toString().compare(tr("drip"))==0) {
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/ukui-clock/drip.ogg"));
        }
    } else {
        if (model_setup->index(0, 19).data().toString().compare(tr("glass"))==0) {
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/ukui-clock/glass.ogg"));
        } else if(model_setup->index(0, 19).data().toString().compare(tr("bark"))==0) {
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/ukui-clock/bark.ogg"));
        } else if(model_setup->index(0, 19).data().toString().compare(tr("sonar"))==0) {
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
//重新加载最新音乐
void Natice_alarm::refreshMusic()
{
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("clock");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model_setup->select();
    playlist->clear();
    if(num_flag >= 0)

        {
            if(model->index(num_flag, 2).data().toString().compare(tr("glass"))==0){
                playlist->addMedia(QUrl::fromLocalFile("/usr/share/ukui-clock/glass.ogg"));
            } else if (model->index(num_flag, 2).data().toString().compare(tr("bark"))==0) {
                playlist->addMedia(QUrl::fromLocalFile("/usr/share/ukui-clock/bark.ogg"));
            } else if (model->index(num_flag, 2).data().toString().compare(tr("sonar"))==0) {
                playlist->addMedia(QUrl::fromLocalFile("/usr/share/ukui-clock/sonar.ogg"));
            } else if (model->index(num_flag, 2).data().toString().compare(tr("drip"))==0) {
                playlist->addMedia(QUrl::fromLocalFile("/usr/share/ukui-clock/drip.ogg"));
            }
        } else {
            if (model_setup->index(0, 19).data().toString().compare(tr("glass"))==0) {
                playlist->addMedia(QUrl::fromLocalFile("/usr/share/ukui-clock/glass.ogg"));
            } else if(model_setup->index(0, 19).data().toString().compare(tr("bark"))==0) {
                playlist->addMedia(QUrl::fromLocalFile("/usr/share/ukui-clock/bark.ogg"));
            } else if(model_setup->index(0, 19).data().toString().compare(tr("sonar"))==0) {
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
    if(num_flag >= 0)
    {
        this->close();
    }else{
        this->hide();
    }
}
//关闭音乐
//Turn off music
void Natice_alarm::close_music()
{
    if (timer_value == 0) {
        set_dialog_close();
    }
        ui->label_4->setText(QString::number(timer_value)+tr(" Seconds to close"));
    timer_value--;
}
//绘制背景
// Draw background
void Natice_alarm::paintEvent(QPaintEvent *event)
{
//    if (!full_flag) {
//        return;
//    }
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    QPainterPath rectPath;
    rectPath.addRect(this->rect());
    p.fillPath(rectPath,palette().color(QPalette::Base));
}
//再次弹出
//Eject again
void Natice_alarm::show_again()
{
    this->hide();
    //刷新数据
    model_setup->select();
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
//Ring a bell 每一秒减一
void Natice_alarm::ring()
{
    ring_num--;
    if (ring_num == 0) {
        natice_init();
        this->show();
        timer->start();
        refreshMusic();
//        music->play();
    }
}


//bool Natice_alarm::eventFilter(QObject *watched, QEvent *event)
//{
//    if(watched == ui->widget && event->type() == QEvent::Paint)
//    {
//        showPaint(); //响应函数
//    }
//    return QWidget::eventFilter(watched,event);
//}

////实现响应函数
//void Natice_alarm::showPaint()
//{
//    QPainter p(ui->widget);
//    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
//    QPainterPath rectPath;
//    rectPath.addRoundedRect(ui->widget->rect().adjusted(6, 6, -6, -6), 6, 6);

//    // 画一个黑底
//    QPixmap pixmap(ui->widget->rect().size());
//    pixmap.fill(Qt::transparent);
//    QPainter pixmapPainter(&pixmap);
//    pixmapPainter.setRenderHint(QPainter::Antialiasing);
//    pixmapPainter.setPen(Qt::transparent);
//    pixmapPainter.setBrush(Qt::gray);
//    pixmapPainter.drawPath(rectPath);
//    pixmapPainter.end();

//    // 模糊这个黑底
//    QImage img = pixmap.toImage();
//    qt_blurImage(img, 10, false, false);

//    // 挖掉中心
//    pixmap = QPixmap::fromImage(img);
//    QPainter pixmapPainter2(&pixmap);
//    pixmapPainter2.setRenderHint(QPainter::Antialiasing);
//    pixmapPainter2.setCompositionMode(QPainter::CompositionMode_Clear);
//    pixmapPainter2.setPen(Qt::transparent);
//    pixmapPainter2.setBrush(QColor(0,0,0));
//    pixmapPainter2.drawPath(rectPath);

//    // 绘制阴影
//    p.drawPixmap(ui->widget->rect(), pixmap, pixmap.rect());
//    p.setOpacity(0.9);
//    // 绘制一个背景
//    p.save();
//    p.fillPath(rectPath,palette().color(QPalette::Base));
//    p.restore();
//}

void Natice_alarm::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->dragPosition = event->globalPos() - frameGeometry().topLeft();
        this->mousePressed = true;
    }
    QWidget::mousePressEvent(event);
}

void Natice_alarm::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->mousePressed = false;
    }

    QWidget::mouseReleaseEvent(event);
    this->setCursor(Qt::ArrowCursor);
}

void Natice_alarm::mouseMoveEvent(QMouseEvent *event)
{
    if (this->mousePressed) {
        move(event->globalPos() - this->dragPosition);
        this->setCursor(Qt::ClosedHandCursor);
    }

    QWidget::mouseMoveEvent(event);
}

void Natice_alarm::closeEvent(QCloseEvent *event)
{
    timer->stop();
    music->stop();
    if(num_flag >= 0)
    {
        event->accept();//接受
        this->close();
    }else{
        event->ignore();//忽视
        this->hide();
    }
}
