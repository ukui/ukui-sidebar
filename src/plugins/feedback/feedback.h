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
#ifndef FEEDBACK_H
#define FEEDBACK_H


#include "submit_fail.h"
#include "submit_success.h"
#include <QMainWindow>
#include <QLabel>
#include <QDialog>
#include <QDebug>
#include <QFile>
#include <sys/utsname.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <QProcess>
#include <fstream>
#include <iostream>
#include <cstring>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <vector>
#include <QJsonObject>
#include <QJsonDocument>

class QPushButton;
class QLabel;

using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class feedback; }
QT_END_NAMESPACE

class feedback : public QMainWindow
{
    Q_OBJECT

public:
    feedback(QWidget *parent = nullptr);
    ~feedback();

    void window_ui_init();
    void systeminfo_show();
    void systeminfo_hide();
    void add_systeminfo();
    void add_file_change_window();
    void del_file_change_window();
    void feedback_info_init();

    void add_fileinfo_model();
    void update_add_file_window();
    void update_linedit_add_or_del_file();
    bool all_file_size_than_10M();
    void httpclient_init();
    void set_request_header();
    void send_file_httpserver(QString uid);
    QFile* add_file_to_Part(QString filepath,QString file_type,QString file_name);
    vector<QFile*> m_filesArray;


signals:
    void syslog();

private slots:
    void on_pushButton_clicked();


    void on_textEdit_textChanged();



    void on_checkBox_stateChanged(int state);

    void on_checkBox_2_stateChanged(int state);

    void on_checkBox_3_stateChanged(int state);

    void on_checkBox_4_stateChanged(int state);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_textEdit_2_textChanged();
    void del_file_button_clicked();
    void finishedSlot(QNetworkReply*);

private:
    Ui::feedback *ui;

    submit_fail * fail_dialog;
    submit_success * success_dialog;


//logflag
    int syslogflag = 0;
    int apportlogflag = 0;
    int dpkglogflag = 0;
    int describeflag = 0;
    int emailflag = 0;
    int get_systeminfoflag = 0;

    QString feedback_type = "系统问题";  //反馈类型
    QString email_str;   //邮箱
    QString filename;
    QString textContent;// 详细描述

    QString all_systeminfo;

    //控件坐标变量
    //window size
    int window_w = 600;
    int window_h =695;
    //checkBox_4
    int checkbox4_x = 35;
    int checkbox4_y = 570;
    int checkbox4_w = 121;
    int checkbox4_h = 24;
    //pushButton_3
    int pushbutton3_x = 140;
    int pushbutton3_y = 570;
    int pushbutton3_w = 70;
    int pushbutton3_h = 24;
    //verticalWidget
    int widget_x = 100;
    int widget_y = 593;
    int widget_w = 240;
    int widget_h = 130;
    //pushButton_2
    int pushbutton2_x = 440;
    int pushbutton2_y = 600;
    int pushbutton2_w = 120;
    int pushbutton2_h = 45;

    //文件名字宽度
    //int filename_width;
    //int filesize_width;
    int filename_x = 140;
    int filename_y = 480;
    int filename_w = 200;
    int filename_h = 24;
    QString system_info_str; //系统版本信息
    QString encoding_info_str; //系统编码格式
    QString desktop_info_str;  //系统桌面环境


    QString send_os_info;
    QString send_encoding_info;
    QString send_dekstop_info;



    QPushButton *deletefileBtn[5];
    QLabel *filename_label[5];
    QLabel *filesize_label[5];

    //httpclient
    QNetworkAccessManager *accessManager;
    QNetworkAccessManager *accessManager_file;
    QNetworkRequest request;
    QNetworkRequest request_file;

    QString urlstring;

    int send_fail_flags = 0;

    QHttpMultiPart *multiPart;


    QList<QString> file_name_list;
    QList<QString> file_size_list;
    QList<QString> file_path_list;




};
#endif // FEEDBACK_H
