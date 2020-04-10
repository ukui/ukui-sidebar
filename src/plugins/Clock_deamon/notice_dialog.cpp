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
#include "notice_dialog.h"
#include <QSqlTableModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDebug>

Notice_Dialog::Notice_Dialog(QWidget *parent, int close_time, int num) :
    QDialog(parent),
    num_flag(num),
    timer_value(close_time)
{
    setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);   /* 开启窗口无边框 */
    //setAttribute(Qt::WA_TranslucentBackground);
    setWindowOpacity(0.7);
    this->setStyleSheet("QDialog{background-color: rgba(0, 0, 0, 0.5);}");
    QPixmap bgPixmap = QPixmap(":/window-close-symbolic.png");
    QPixmap dialogPixmap = QPixmap(":/clock.ico");

    this->setWindowTitle(tr("响铃提示"));
    this->setWindowIcon(dialogPixmap);

    pushButton->setIcon(bgPixmap);
    label->setAlignment(Qt::AlignHCenter);
    label_2->setAlignment(Qt::AlignHCenter);


    connect(pushButton, SIGNAL(clicked()), this, SLOT(set_dialog_close()) );
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(close_music()));
    timer->setInterval(1000);
    timer->start();

    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("clock");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select(); //选取整个表的所有行

    QSqlTableModel *model_setup = new QSqlTableModel(this);
    model_setup->setTable("setup");
    model_setup->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_setup->select();

    music = new QMediaPlayer(this);//初始化音乐
    playlist = new QMediaPlaylist(this);//初始化播放列表
    if(num >= 0)
    {
        if(model->index(num, 2).data().toString().compare(tr("玻璃"))==0){
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/sounds/gnome/default/alerts/glass.ogg"));
        }else if (model->index(num, 2).data().toString().compare(tr("犬吠"))==0) {
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/sounds/gnome/default/alerts/bark.ogg"));
        }else if (model->index(num, 2).data().toString().compare(tr("声呐"))==0) {
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/sounds/gnome/default/alerts/sonar.ogg"));
        }else if (model->index(num, 2).data().toString().compare(tr("雨滴"))==0){
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/sounds/gnome/default/alerts/drip.ogg"));
        }
    }else{
        if(model_setup->index(0, 19).data().toString().compare(tr("玻璃"))==0){
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/sounds/gnome/default/alerts/glass.ogg"));
        }else if(model_setup->index(0, 19).data().toString().compare(tr("犬吠"))==0){
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/sounds/gnome/default/alerts/bark.ogg"));
        }else if(model_setup->index(0, 19).data().toString().compare(tr("声呐"))==0){
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/sounds/gnome/default/alerts/sonar.ogg"));
        }else{
            playlist->addMedia(QUrl::fromLocalFile("/usr/share/sounds/gnome/default/alerts/drip.ogg"));
        }
    }

    playlist->setPlaybackMode(QMediaPlaylist::Loop);//设置播放模式(顺序播放，单曲循环，随机播放等)
    music->setPlaylist(playlist);  //设置播放列表
    music->setVolume(  model_setup->index(0, 6).data().toInt() );
    music->play();

}

Notice_Dialog::~Notice_Dialog()
{
  timer->stop();
   music->stop();
    delete timer;
    delete music;
    delete playlist;

    delete gridLayout_4;
    delete horizontalLayout_2;
    delete horizontalSpacer_2;
    delete verticalLayout;
    delete horizontalLayout_5;
    delete horizontalSpacer_4;
    delete label_2;
    delete horizontalSpacer_5;
    delete label;
    delete horizontalSpacer_3;
    delete verticalSpacer;
    delete horizontalLayout;
    delete label_3;
    delete label_4;
    delete horizontalSpacer;
    delete pushButton;
    delete verticalSpacer_2;
   qDebug()<<"------Notice_Dialog---------";
}

void Notice_Dialog::set_dialog_close()
{

    this->close();
    timer->stop();
    music->stop();
}

void Notice_Dialog::close_music()
{
    if(timer_value == 0)
    {
        set_dialog_close();
    }
    if(num_flag >= 0){
        label_2->setText(QString::number(timer_value));
    }else{
        label_2->setText(tr("倒计时时间结束"));
    }
    timer_value--;
}

void Notice_Dialog::setupUi(QDialog *Notice_Dialog)
{
    if (Notice_Dialog->objectName().isEmpty())
        Notice_Dialog->setObjectName(QString::fromUtf8("Notice_Dialog"));
    Notice_Dialog->resize(529, 342);
    Notice_Dialog->setStyleSheet(QString::fromUtf8("background-color: rgb(83, 83, 83);"));
    gridLayout_4 = new QGridLayout(Notice_Dialog);
    gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer_2);

    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    horizontalLayout_5 = new QHBoxLayout();
    horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
    horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_5->addItem(horizontalSpacer_4);

    label_2 = new QLabel(Notice_Dialog);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setStyleSheet(QString::fromUtf8("font: 25 28pt \"Noto Sans CJK SC\";\n"
"color: rgb(39, 207, 129);\n"
""));

    horizontalLayout_5->addWidget(label_2);

    horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_5->addItem(horizontalSpacer_5);


    verticalLayout->addLayout(horizontalLayout_5);

    label = new QLabel(Notice_Dialog);
    label->setObjectName(QString::fromUtf8("label"));
    label->setStyleSheet(QString::fromUtf8("font: 87 28pt \"Noto Sans CJK SC\";\n"
"color: rgb(39, 207, 129);\n"
"\n"
""));

    verticalLayout->addWidget(label);


    horizontalLayout_2->addLayout(verticalLayout);

    horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer_3);


    gridLayout_4->addLayout(horizontalLayout_2, 2, 0, 1, 1);

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout_4->addItem(verticalSpacer, 3, 0, 1, 1);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    label_3 = new QLabel(Notice_Dialog);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setStyleSheet(QString::fromUtf8("color: rgb(39, 207, 129);"));

    horizontalLayout->addWidget(label_3);

    label_4 = new QLabel(Notice_Dialog);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setStyleSheet(QString::fromUtf8("color: rgb(39, 207, 129);"));

    horizontalLayout->addWidget(label_4);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    pushButton = new QPushButton(Notice_Dialog);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setMaximumSize(QSize(30, 30));
    pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(83, 83, 83);"));

    horizontalLayout->addWidget(pushButton);


    gridLayout_4->addLayout(horizontalLayout, 0, 0, 1, 1);

    verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout_4->addItem(verticalSpacer_2, 1, 0, 1, 1);


    retranslateUi(Notice_Dialog);

    QMetaObject::connectSlotsByName(Notice_Dialog);
} // setupUi

void Notice_Dialog::retranslateUi(QDialog *Notice_Dialog)
{
    Notice_Dialog->setWindowTitle(QApplication::translate("Notice_Dialog", "Dialog", nullptr));
    label_2->setText(QString());
    label->setText(QApplication::translate("Notice_Dialog", "\347\247\222\345\220\216\345\205\263\351\227\255\351\223\203\345\243\260", nullptr));
    label_3->setText(QApplication::translate("Notice_Dialog", "\351\227\271\351\222\237:", nullptr));
    label_4->setText(QApplication::translate("Notice_Dialog", "\350\265\267\345\272\212\351\223\203", nullptr));
    pushButton->setText(QString());
} // retranslateUi
