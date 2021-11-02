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


#include "submitFail.h"
#include "submitSuccess.h"
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
#include <browseButton.h>
#include <systeminfoButton.h>
#include <QListWidget>
#include <QStyleOption>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include"hidebtnHover.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QBitmap>
#include <QGraphicsDropShadowEffect>
#include <QGSettings/qgsettings.h>
#include <QMouseEvent>

#include "fileitemInit.h"

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
    QWidget *centralWidget;
    QLabel *feedbackLabel;
    QComboBox *typeComboBox;
    QLabel *descriptionLabel;
    QFrame *descriptionFrame;
    QTextEdit *descriptionTextEdit;
    QLabel *emailLabel;
    QLabel *starLabel;
    QLabel *starsLabel;
    QLabel *emailErrMsgLabel;
    QLineEdit *emailLineEdit;
    QLabel *uploadLabel;
    QLabel *addfileLabel;
    QLabel *tipLabel;
    browseButton *browseBtn;
    QCheckBox *getInfoCheckBox;
    QPushButton *submitBtn;
    systeminfo_button *sysInfoBtn;
    QLabel *typeLabel;
    QWidget *verticalWidget;
    QFrame *verticalFrame;
    QGraphicsDropShadowEffect *effect;
    QLabel *sysInfoLabel;
    QLabel *desktopInfoLabel;
    QLabel *codeLabel;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QCheckBox *syslogCheckBox;
    QCheckBox *apportLogCheckBox;
    QCheckBox *dpkgLogCheckBox;
    QLabel *logFileLabel;
    QLabel *tipsLabel;
    QLabel *errorTipLabel;
    QPushButton *minBtn;
    QPushButton *closeBtn;
    QListWidget * fileListWidget;
    QListWidgetItem * fileListWidgetItem[5];
    fileItemInit* fileWidget[5];
    QPixmap submittingPixmap[8];
    QGSettings *styleSettings;
    QPalette paletteBlue;
    QPalette paletteGray;
    QLabel *logoLabel;
    QLabel *titleLabel;
    QPushButton * titleBtn;


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
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

signals:
    void syslog();

private slots:
    void on_browseBtn_clicked();

    void on_textEdit_textChanged();

    void on_minBtn_clicked();

    void on_closeBtn_clicked();

    void on_syslogCheckBox_stateChanged(int state);

    void on_apportLogCheckBox_stateChanged(int state);

    void on_dpkgLogCheckBox_stateChanged(int state);

    void on_getInfoCheckBox_stateChanged(int state);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_submitBtn_clicked();

    void on_emailLineEdit_textChanged();

    void del_file_button_clicked();

    void sendfile_finished(QNetworkReply* );

    void submit_change_load_image();
    void style_changed(QString);

private:

    submit_fail *fail_dialog=nullptr;
    submit_success * success_dialog=nullptr;

    QPoint dragPosition;                                            //拖动坐标
    bool mousePressed;                                              //鼠标是否按下


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
