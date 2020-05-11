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

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <browse_button.h>
#include <systeminfo_button.h>
#include "closeBtn_hover.h"
#include  <QListWidget>
#include <QStyleOption>
#include <QPainter>
#include <QPixmap>
#include "fileitem_init.h"
#include <QTimer>
#include"hidebtnhover.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QBitmap>
#include <QGraphicsDropShadowEffect>
class QSqlTableModel;
class QPushButton;
class QLabel;

using namespace std;

class feedback : public QMainWindow
{
    Q_OBJECT

public:
    feedback(QWidget *parent = nullptr);
    ~feedback();


    //ui***********************
    QWidget *centralwidget;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_3;
    QFrame *frame;
    QTextEdit *textEdit;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *email_err_msg_label;
    QLineEdit *lineEdit_2;
    QLabel *label_7;
    QLineEdit *lineEdit;
    browse_button *pushButton;
    QCheckBox *checkBox_4;
    QPushButton *pushButton_2;
    systeminfo_button *pushButton_3;
    QLabel *label_2;
    QWidget *verticalWidget;
    QFrame *frame_2;
    QGraphicsDropShadowEffect *effect;
    QLabel *label_10;
    QLabel *label_12;
    QLabel *label_11;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_13;
    hideBtn_hover *pushButton_mix;
    closeBtn_hover *pushButton_close;
    QListWidget * file_listwidget;
    QListWidgetItem * file_listwidget_item[5];
    fileitem_init* file_widget[5];
    QPixmap submitting_pixmap[8];

    //*************************

    void UI_init();
    void systeminfo_show(QPointF pt);
    void systeminfo_hide();
    void add_systeminfo();

    void feedback_init();

    void feedback_info_init();

    void set_all_disable_in_submit();
    void set_all_enable_after_submit();
    QByteArray get_today_syslog();

    void add_fileinfo_model();
    void update_add_file_window();
    void update_linedit_add_or_del_file();
    bool all_file_size_than_10M();
    void httpclient_init();
    void set_request_header();
    void send_file_httpserver(QString uid);
    void window_close();
    void resend_info_when_sendfail();
    void add_file_to_Part(QString filepath,QString file_type,QString file_name);

    void finishedSlot(QNetworkReply*);


protected:
    void paintEvent(QPaintEvent*);


signals:
    void syslog();

private slots:
    void on_pushButton_clicked();


    void on_textEdit_textChanged();
    void on_pushButton_mix_clicked();
    void on_pushButton_close_clicked();

    void on_checkBox_stateChanged(int state);

    void on_checkBox_2_stateChanged(int state);

    void on_checkBox_3_stateChanged(int state);

    void on_checkBox_4_stateChanged(int state);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_lineEdit_2_textChanged();
    void del_file_button_clicked();

    void sendfile_finished(QNetworkReply* );

    void submit_change_load_image();

private:

    submit_fail *fail_dialog=nullptr;
    submit_success * success_dialog=nullptr;


//logflag
    int syslogflag = 0;
    int apportlogflag = 0;
    int dpkglogflag = 0;
    int describeflag = 0;
    int emailflag = 0;
    int get_systeminfoflag = 0;

    bool timeout_http_flag = false;

    QString feedback_type = "系统问题";  //反馈类型
    QString email_str;   //邮箱
    QString filename;
    QString textContent;// 详细描述

    QString system_info_str; //系统版本信息
    QString encoding_info_str; //系统编码格式
    QString desktop_info_str;  //系统桌面环境

    QTimer *submitting_timer=nullptr;


    QString send_os_info;
    QString send_encoding_info;
    QString send_dekstop_info;

    QPushButton *deletefileBtn[5];
    QLabel *filename_label[5];
    QLabel *filesize_label[5];

    //httpclient
    QNetworkAccessManager *accessManager=nullptr;
    QNetworkAccessManager *accessManager_file=nullptr;
    QNetworkRequest request;
    QNetworkRequest request_file;
    QString urlstring;//服务器地址

    QVariant statusCode_file;
    QVariant reason_file ;
    QVariant statusCode_info;
    QVariant reason_info ;
    QByteArray bytes_info;
    QByteArray bytes_file;


    QJsonObject feedback_info_json;
    QJsonDocument json_doc;
    QByteArray post_feedback_info_array;


    QString uid_value;
    QJsonParseError jsonerror;
    QJsonDocument document;
    QJsonObject object;



    QHttpMultiPart *multiPart=nullptr;

    QList<QString> file_name_list;
    QList<QString> file_size_list;
    QList<QString> file_path_list;

    int pixmap_i = 0;

    bool window_is_close_flag  = false;
    bool file_send_failed_flag = true;

};
#endif // FEEDBACK_H
