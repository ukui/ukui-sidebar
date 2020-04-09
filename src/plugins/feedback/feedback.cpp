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
#include "feedback.h"
#include "submit_fail.h"
#include "submit_success.h"
#include <QFileDialog>
#include <QApplication>
#include <QDebug>
#include <QFileInfo>
#include <QFile>
#include <QModelIndex>
#include <QLabel>
#include <QLocale>
#include <QPushButton>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QEventLoop>
#include <QTextCodec>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QHttpPart>
#include <QGraphicsDropShadowEffect>
#include <QTranslator>
#include <QLocale>
#include <QStandardPaths>
#include "fileitem_init.h"
#include <QTimer>
#include "customstyle.h"

feedback::feedback(QWidget *parent)
    : QMainWindow(parent)
{

    UI_init();
    feedback_init();
}

feedback::~feedback()
{
    //程序结束时删除所有数据------

    //---------------------------
}
void feedback::UI_init()
{

    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("feedback"));
    this->resize(600, 917);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
    this->setSizeIncrement(QSize(0, 0));
    this->setWindowTitle(tr("用户反馈"));
    this->setFixedSize(600,550);
    this->setWindowIcon(QIcon(":/image/kylin-feedback.png"));
    this->setWindowFlags(Qt::FramelessWindowHint);//设置窗口无边框


    //--------设置圆角
    QBitmap bmp(this->size());

    bmp.fill();

    QPainter p(&bmp);

    p.setPen(Qt::NoPen);

    p.setBrush(Qt::black);

    p.setRenderHint(QPainter::Antialiasing);

    p.drawRoundedRect(bmp.rect(),6,6);

    setMask(bmp);
    //----- ------------------------

    centralwidget = new QWidget(this);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));

    label = new QLabel(centralwidget);
    label->setText(tr("问题反馈"));
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(35, 40, 160, 41));
    label->setStyleSheet(QString::fromUtf8("font: 24px \"Sans Serif\";\n"
                                           "color: rgb(68, 68, 68);"));

    label_2 = new QLabel(centralwidget);
    label_2->setText(tr("问题类型"));
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(35, 105, 61, 20));
    label_2->setStyleSheet(QString::fromUtf8("font: 14px;\n"
                                             "color: rgb(68, 68, 68);\n"
                                             ""));
    comboBox = new QComboBox(centralwidget);
    comboBox->addItem(QString(tr("系统问题")));
    comboBox->addItem(QString(tr("意见建议")));
    comboBox->addItem(QString(tr("商务合作")));
    comboBox->addItem(QString(tr("其他")));
    comboBox->setObjectName(QString::fromUtf8("comboBox"));
    comboBox->setGeometry(QRect(140, 105, 320, 20));
    comboBox->setStyleSheet(QString::fromUtf8("min-height: 30px;background-color: rgb(255, 255, 255);"
                                              "color: rgb(68, 68, 68);font: 14px ;"));
    label_3 = new QLabel(centralwidget);
    label_3->setText(tr("问题描述"));
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setGeometry(QRect(35, 145, 61, 20));
    label_3->setStyleSheet(QString::fromUtf8("font: 14px ;\n"
                                             "color: rgb(68, 68, 68);\n"
                                             ""));
    frame = new QFrame(centralwidget);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setGeometry(QRect(140, 145, 320, 120));
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);
    textEdit = new QTextEdit(frame);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));
    textEdit->setGeometry(QRect(10, 10, 300, 100));
    textEdit->setFrameShape(QFrame::NoFrame);
    QPalette palette_textedit = textEdit->palette();
    palette_textedit.setBrush(QPalette::Base,Qt::white);
    palette_textedit.setBrush(QPalette::Text,Qt::black);
    palette_textedit.setBrush(QPalette::PlaceholderText,QColor("#CCCCCC"));
    textEdit->setPalette(palette_textedit);
    textEdit->setPlaceholderText(tr("请输入内容"));//设置详细输入框的提示信息



    label_4 = new QLabel(centralwidget);
    label_4->setText(tr("邮箱"));
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setGeometry(QRect(35, 275, 32, 23));
    label_4->setStyleSheet(QString::fromUtf8("font: 14px;\n"
                                             "color: rgb(68, 68, 68);\n"
                                             ""));

    email_err_msg_label = new QLabel(centralwidget);
    email_err_msg_label->setText(tr("邮箱格式输入不正确"));
    email_err_msg_label->setGeometry(QRect(140,305,240,15));
    email_err_msg_label->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
    email_err_msg_label->hide();

    label_5 = new QLabel(centralwidget);
    label_5->setText(tr("*"));
    label_5->setObjectName(QString::fromUtf8("label_5"));
    label_5->setGeometry(QRect(93, 142, 16, 16));
    label_5->setStyleSheet(QString::fromUtf8("font: 11pt \"Sans Serif\";\n"
                                             "color: rgb(255, 0, 0);"));
    label_6 = new QLabel(centralwidget);
    label_6->setText(tr("*"));
    label_6->setObjectName(QString::fromUtf8("label_6"));
    label_6->setGeometry(QRect(68, 277, 16, 16));
    label_6->setStyleSheet(QString::fromUtf8("font: 11pt \"Sans Serif\";\n"
                                             "color: rgb(255, 0, 0);"));
    lineEdit_2 = new QLineEdit(centralwidget);
    lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
    lineEdit_2->setGeometry(QRect(140, 275, 320, 30));
    lineEdit_2->setStyle(new CustomStyle("ukui"));
    QPalette palette_lineedit_2 = lineEdit_2->palette();
    palette_lineedit_2.setBrush(QPalette::Text,Qt::black);
    palette_lineedit_2.setBrush(QPalette::PlaceholderText,QColor("#CCCCCC"));
    lineEdit_2->setPalette(palette_lineedit_2);

    label_7 = new QLabel(centralwidget);
    label_7->setText(tr("上传附件"));
    label_7->setObjectName(QString::fromUtf8("label_7"));
    label_7->setGeometry(QRect(35,365, 61, 30));
    label_7->setStyleSheet(QString::fromUtf8("font: 14px ;\n"
                                             "color: rgb(68, 68, 68);\n"
                                             ""));
    lineEdit = new QLineEdit(centralwidget);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
    lineEdit->setGeometry(QRect(140, 367, 320, 30));
    lineEdit->setReadOnly(true);
    lineEdit->setFrame(true);
    lineEdit->setPlaceholderText(tr("文件大小不能超过10MB"));
    lineEdit->setStyle(new CustomStyle("ukui"));
    QPalette palette_lineedit = lineEdit->palette();
    palette_lineedit.setBrush(QPalette::Text,Qt::black);
    palette_lineedit.setBrush(QPalette::PlaceholderText,QColor("#CCCCCC"));
    lineEdit->setPalette(palette_lineedit);

    pushButton = new browse_button(centralwidget);
    pushButton->setText(tr("浏览..."));
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setGeometry(QRect(470, 367, 80, 30));
    pushButton->setStyleSheet(QString::fromUtf8("font: 14px;\n"
                                                "background-color: rgb(233, 233, 233);\n"
                                                "color: rgb(68, 68, 68);\n"
                                                "border:4px ;"));
    checkBox_4 = new QCheckBox(centralwidget);
    checkBox_4->setText(tr("同意获取我的"));
    checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
    checkBox_4->setGeometry(QRect(35, 490, 121, 24));
    checkBox_4->setStyleSheet(" spacing: 6px;");
    checkBox_4->setStyleSheet(QString::fromUtf8("font: 14px;color:rgb(0,0,0)"));
    pushButton_2 = new QPushButton(centralwidget);
    pushButton_2->setText(tr("提交"));
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_2->setGeometry(QRect(440, 475, 120, 45));
    pushButton_2->setEnabled(false);
    pushButton_2->setStyleSheet(QString::fromUtf8("font: 18px;\n"
                                                  "color: rgb(255, 255, 255);\n"
                                                  "background-color: rgb(233, 233, 233);\n"
                                                  "border:4px ;"));
    pushButton_3 = new systeminfo_button(centralwidget);
    pushButton_3->setText(tr("系统信息"));
    pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
    pushButton_3->setGeometry(QRect(140, 490, 68, 24));
    pushButton_3->setFeedBack(this);
    pushButton_3->setFlat(true);
    pushButton_3->setEnabled(false);
    pushButton_3->setStyleSheet(QString::fromUtf8("font: 14px;\n"
                                                  "color: rgb(85, 85, 255);"));


    verticalWidget = new QWidget();
    verticalWidget->setObjectName(QString::fromUtf8("verticalWidget"));
    verticalWidget->setWindowFlags(Qt::FramelessWindowHint);
    verticalWidget->hide();
    verticalWidget->setAttribute(Qt::WA_TranslucentBackground);//设置窗口透明

    verticalWidget->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255);\n"
                                                    "border-top-left-radius:4px;\n"
                                                    "\n"
                                                    "border-top-right-radius:4px;\n"
                                                    "\n"
                                                    "border-bottom-left-radius:4px;\n"
                                                    "\n"
                                                    "border-bottom-right-radius:4px;\n"
                                                    "border:0.5px solid black;\n"
                                                    ""));
    frame_2 = new QFrame(verticalWidget);
    frame_2->setObjectName(QString::fromUtf8("frame_2"));
    frame_2->setGeometry(QRect(0, 0, 217,77));
    frame_2->setFrameShape(QFrame::StyledPanel);
    frame_2->setFrameShadow(QFrame::Raised);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setOffset(4,4);
    effect->setColor(QColor(0,0,0));
    effect->setBlurRadius(10);
    frame_2->setGraphicsEffect(effect);
    frame_2->setStyleSheet("border-color: rgba(255, 255, 255,0.1);");

    label_10 = new QLabel(frame_2);
    label_10->setObjectName(QString::fromUtf8("label_10"));
    label_10->setGeometry(QRect(15, 10, 200, 20));
    label_10->setStyleSheet(QString::fromUtf8("border-color: rgb(255, 255, 255);color:rgb(0,0,0);font:12px;"));
    label_12 = new QLabel(frame_2);
    label_12->setObjectName(QString::fromUtf8("label_12"));
    label_12->setGeometry(QRect(15, 30, 200, 20));
    label_12->setStyleSheet(QString::fromUtf8("border-color: rgb(255, 255, 255);color:rgb(0,0,0);font:12px;"));
    label_11 = new QLabel(frame_2);
    label_11->setObjectName(QString::fromUtf8("label_11"));
    label_11->setGeometry(QRect(15, 50, 200, 20));
    label_11->setStyleSheet(QString::fromUtf8("border-color: rgb(255, 255, 255);color:rgb(0,0,0);font:12px;"));

    label_8 = new QLabel(centralwidget);
    label_8->setText(tr("日志文件"));
    label_8->setObjectName(QString::fromUtf8("label_8"));
    label_8->setGeometry(QRect(35, 325, 71, 23));
    label_8->setStyleSheet(QString::fromUtf8("font: 14px;\n"
                                             "color: rgb(68, 68, 68);\n"
                                             ""));
    label_9 = new QLabel(centralwidget);
    label_9->setText(tr("限200字"));
    label_9->setObjectName(QString::fromUtf8("label_9"));
    label_9->setGeometry(QRect(470, 145, 44, 18));
    label_9->setStyleSheet(QString::fromUtf8("color: rgb(136, 136, 136);\n"
                                             "font: 12px;"));


    layoutWidget = new QWidget(centralwidget);
    layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
    layoutWidget->setGeometry(QRect(140, 327,  320, 23));
    horizontalLayout = new QHBoxLayout(layoutWidget);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    horizontalLayout->setGeometry(QRect(140,325, 320, 23));
    checkBox = new QCheckBox(layoutWidget);
    checkBox->setText(tr("syslog"));
    checkBox->setObjectName(QString::fromUtf8("checkBox"));
    checkBox->setStyleSheet(QString::fromUtf8("font: 14px;\n"
                                              "color:rgb(0,0,0);\n"
                                              ""));

    horizontalLayout->addWidget(checkBox);

    checkBox_2 = new QCheckBox(layoutWidget);
    checkBox_2->setText(tr("apport.log"));
    checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
    checkBox_2->setStyleSheet(QString::fromUtf8("font: 14px ;\n"
                                                "spacing: 5px;"
                                                "color:rgb(0,0,0);\n"
                                                ""));

    horizontalLayout->addWidget(checkBox_2);

    checkBox_3 = new QCheckBox(layoutWidget);
    checkBox_3->setText(tr("dpkg.log"));
    checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
    checkBox_3->setStyleSheet(QString::fromUtf8("font: 14px;\n"
                                                "spacing: 5px;\n"
                                                "color:rgb(0,0,0);\n"
                                                ""));

    horizontalLayout->addWidget(checkBox_3);


    label_13 = new QLabel(centralwidget);
    label_13->setText(tr("文件大小超过了10MB或文件格式不支持"));
    label_13->setObjectName(QString::fromUtf8("label_13"));
    label_13->setGeometry(QRect(140, 470, 241, 16));
    label_13->hide();
    label_13->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
    this->setCentralWidget(centralwidget);


    //最小化和关闭按钮
    pushButton_mix = new hideBtn_hover(centralwidget);
    pushButton_mix->setGeometry(QRect(532, 4, 30, 30));
    pushButton_mix->setStyleSheet("background-color: rgb(255,255,255);border-image:url(:/image/mix_default.png);border-radius:4px;");


    connect(pushButton_mix,SIGNAL(clicked()),this,SLOT(on_pushButton_mix_clicked()));

    pushButton_close = new closeBtn_hover(centralwidget);
    pushButton_close->setGeometry(QRect(566, 4, 30, 30));
    pushButton_close->setStyleSheet("background-color: rgb(255,255,255);border-image:url(:/image/close_default.png);border-radius:4px;");

    //添加附件列表
    file_listwidget = new QListWidget(this);
    file_listwidget->setGeometry(QRect(140,407,320,53));
    file_listwidget->setStyleSheet("background-color: rgb(255,255,255);selection-background-color: rgb(255,255,255);");
    file_listwidget->setFrameShape(QListWidget::NoFrame);
    //设置横向纵向无下拉条
    file_listwidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    file_listwidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //添加提交图片
    submitting_pixmap[0] =QPixmap(":/image/conning-a/1.png");
    submitting_pixmap[1] =QPixmap(":/image/conning-a/2.png");
    submitting_pixmap[2] =QPixmap(":/image/conning-a/3.png");
    submitting_pixmap[3] =QPixmap(":/image/conning-a/4.png");
    submitting_pixmap[4] =QPixmap(":/image/conning-a/5.png");
    submitting_pixmap[5] =QPixmap(":/image/conning-a/6.png");
    submitting_pixmap[6] =QPixmap(":/image/conning-a/7.png");
    submitting_pixmap[7] =QPixmap(":/image/conning-a/8.png");

    connect(pushButton_close,SIGNAL(clicked()),this,SLOT(on_pushButton_close_clicked()));
    connect(pushButton,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
    connect(pushButton_2,SIGNAL(clicked()),this,SLOT(on_pushButton_2_clicked()));
    connect(checkBox,SIGNAL(stateChanged(int)),this,SLOT(on_checkBox_stateChanged(int)));
    connect(checkBox_2,SIGNAL(stateChanged(int)),this,SLOT(on_checkBox_2_stateChanged(int)));
    connect(checkBox_3,SIGNAL(stateChanged(int)),this,SLOT(on_checkBox_3_stateChanged(int)));
    connect(checkBox_4,SIGNAL(stateChanged(int)),this,SLOT(on_checkBox_4_stateChanged(int)));
    connect(comboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_comboBox_currentIndexChanged(QString)));
    connect(textEdit,SIGNAL(textChanged()),this,SLOT(on_textEdit_textChanged()));
    connect(lineEdit_2,SIGNAL(textChanged(QString)),this,SLOT(on_lineEdit_2_textChanged()));


    add_systeminfo();//将系统信息添加到信息框



}
void feedback::feedback_init()
{
    //http客户端初始化
    httpclient_init();



    submitting_timer = new QTimer();

    submitting_timer->setInterval(100);
    connect(submitting_timer,SIGNAL(timeout()),this,SLOT(submit_change_load_image()));
}
//点击提交之后按钮更换加载图片
void feedback::submit_change_load_image()
{
    pushButton_2->setText("");
    pushButton_2->setIcon(submitting_pixmap[pixmap_i]);
    pixmap_i++;
    if(pixmap_i == 8 ){
        pixmap_i = 0;
    }

}
void feedback::feedback_quit()
{
    this->close();
}
//最小化窗口
void feedback::on_pushButton_mix_clicked()
{
    this->showMinimized();
}
//关闭窗口
void feedback::on_pushButton_close_clicked()
{
    this->close();
    accessManager->disconnect();
    delete accessManager;
    submitting_timer->stop();
}
void feedback::window_close()
{
    this->close();
}
//发送失败后 重新发送
void feedback::resend_info_when_sendfail()
{
    this->on_pushButton_2_clicked();
}
//获取图片
void feedback::on_pushButton_clicked()
{
    pushButton->setStyleSheet("font: 14px;border-radius:4px;background-color:rgb(65,95,196);color: rgb(68, 68, 68)");
    filename=QFileDialog::getOpenFileName(this,tr("选择图片"),"/","Image file(*.gif *.jpg *.png)",0);

    //判断文件是否重复添加
    if (file_name_list.size() ==0)
    {
        //添加附件框改变
        lineEdit->setText(filename);
        add_fileinfo_model();
    }
    //最多传五个附件
    else if(file_name_list.size() >= 5)
    {
        return ;
    }
    else{
        int file_diff_flags = 0;
        for(int fileNum=0; fileNum<file_path_list.size(); fileNum++)
        {
            if(filename.compare(file_path_list.at(fileNum)) == 0)
            {
                //添加的文件已经添加过
                file_diff_flags++;
            }
        }
        if(file_diff_flags == 0)
        {
            //添加附件框改变
            lineEdit->setText(filename);
            add_fileinfo_model();

        }
    }
}

//设置详细描述框最大字符数
void feedback::on_textEdit_textChanged()
{
    textContent = textEdit->toPlainText();
    if (textContent.isEmpty()){
        describeflag = 0;
    }
    else

        describeflag = 1;//详细描述是否填写
    if (emailflag == 1 && describeflag == 1){//邮箱和详细描述都已经填写
        pushButton_2->setEnabled(true);//设置提交按钮属性
        pushButton_2->setStyleSheet("font: 18px ;border-radius:4px;background-color:rgb(61,107,229);color: rgb(255, 255, 255)");
    }
    else
    {
        pushButton_2->setEnabled(false);//设置提交按钮属性
        pushButton_2->setStyleSheet("font: 18px ;border-radius:4px;background-color:rgb(233, 233, 233);color: rgb(255, 255, 255)");
    }

    int length = textContent.count();

    int maxLength = 200; // 最大字符数

    if(length > maxLength) {
        QTextCursor cursor = textEdit->textCursor();
        cursor.movePosition(QTextCursor::End);
        if(cursor.hasSelection()) {
            cursor.clearSelection();
        }
        cursor.deletePreviousChar();
        //设置当前的光标为更改后的光标ing>

        textEdit->setTextCursor(cursor);
    }

    length = textEdit->toPlainText().count();

}
//系统信息显示
void feedback::systeminfo_show(QPointF pt)
{
    verticalWidget->setGeometry(pt.x()+5,pt.y()+15,220,80);
    verticalWidget->show();
}
//系统信息隐藏
void feedback::systeminfo_hide()
{
    verticalWidget->hide();
}
//添加系统信息
void feedback::add_systeminfo()
{
    string encoding_info = "系统语言: ";
    string desktop_info = "桌面环境: ";
    string os_info = "操作系统: ";

    if((QLocale::system().name()) == "en_US"){
        encoding_info = "Lang: ";
        desktop_info = "Deskenv: ";
        os_info= "Osrelease: ";
    }
    //获取系统信息
    //1.获取系统版本
    string system_info;
    string system_name;
    string system_version_id;
    string s;
    ifstream fp("/etc/os-release");
    if(!fp){
        system_info = "None";
    }
    else{
        while (getline(fp,s)){
            string::size_type idx;
            idx = s.find("=");//字符串中查找字符串
            if (idx == string::npos){//不存在
            }
            else{
                string str2 = s.substr(0,idx);//截取字符串中=前面的内容
                if(str2 == "NAME"){
                    system_name = s.substr(5);//截取"NAME="后面的内容
                }
                else if(str2 =="VERSION_ID"){
                    system_version_id = s.substr(11);//截取"VERSION_ID="后面的内容
                }
            }
        }

        system_info = os_info +system_name +" " + system_version_id;
    }
    send_os_info = QString::fromStdString(system_name +" " + system_version_id);
    system_info_str = QString::fromStdString(system_info);//string 转QString
    system_info_str.remove(QChar('"'), Qt::CaseInsensitive);  //将字符串中"字符删除
    label_10->setText(system_info_str);
    //2.获取桌面环境信息
    char * desktop = getenv("DESKTOP_SESSION");
    desktop_info.append(desktop);
    send_dekstop_info.append(desktop);
    desktop_info_str = QString::fromStdString(desktop_info);
    label_12->setText(desktop_info_str);
    //3.获取编码格式
    char * encoding = getenv("GDM_LANG");
    encoding_info.append(encoding);
    send_encoding_info.append(encoding);
    encoding_info_str = QString::fromStdString(encoding_info);
    label_11->setText(encoding_info_str);


}

//syslog点选
void feedback::on_checkBox_stateChanged(int state)
{


    if (state == Qt::Checked) // "选中"
    {
        emit syslog();
        syslogflag = 1;
    }
    else // 未选中 - Qt::Unchecked
    {
        syslogflag = 0;
    }
}
//apport.log点选
void feedback::on_checkBox_2_stateChanged(int state)
{
    if (state == Qt::Checked) // "选中"
    {
        emit syslog();
        apportlogflag = 1;
    }
    else // 未选中 - Qt::Unchecked
    {
        apportlogflag = 0;
    }

}
//dpkglog点选
void feedback::on_checkBox_3_stateChanged(int state)
{
    if (state == Qt::Checked) // "选中"
    {
        emit syslog();
        dpkglogflag = 1;
    }
    else // 未选中 - Qt::Unchecked
    {
        dpkglogflag = 0;
    }
}

//是否获取系统信息
void feedback::on_checkBox_4_stateChanged(int state)
{
    if (state == Qt::Checked) // "选中"
    {
        get_systeminfoflag = 1;
    }
    else // 未选中 - Qt::Unchecked
    {
        get_systeminfoflag = 0;
    }
}


//获取反馈类型
void feedback::on_comboBox_currentIndexChanged(const QString &arg1)
{
    feedback_type = comboBox->currentText();
}

//提交按钮
void feedback::on_pushButton_2_clicked()
{
    //判断邮箱格式

    QRegExp rx("^[\\w-]+(\\.[\\w-]+)*@[\\w-]+(\\.[\\w-]+)+");
    int pos=0;
    QRegExpValidator v(rx, 0);
    if(2==v.validate(email_str,pos)){
        email_err_msg_label->hide();
    }
    else{
        email_err_msg_label->show();
        pushButton_2->setEnabled(false);//设置提交按钮属性
        pushButton_2->setStyleSheet("font: 18px;border-radius:4px;background-color:rgb(233, 233, 233);color: rgb(255, 255, 255)");
        return ;
    }


    pushButton_2->setEnabled(false);
    pushButton_2->setStyleSheet("font: 18px;border-radius:4px;background-color:rgb(65,95,196);color: rgb(255, 255, 255)");

    submitting_timer->start();

    qDebug()<<"submitting_timer->start();";

    //判断文件总大小是否超过10M，如果超过，提示
    if(all_file_size_than_10M() == true)
    {
        label_13->show();
        return;
    }
    QJsonObject feedback_info_json;
    //反馈信息类型
    feedback_info_json.insert("subject",feedback_type);
    //详细描述
    feedback_info_json.insert("description",textContent);
    //邮箱
    feedback_info_json.insert("email",email_str);
    //系统信息发送
    if(get_systeminfoflag == 1){
        feedback_info_json.insert("version",send_os_info);
        feedback_info_json.insert("desktop",send_dekstop_info);
        feedback_info_json.insert("language",send_encoding_info);
    }
    else{
        feedback_info_json.insert("version","");
        feedback_info_json.insert("desktop","");
        feedback_info_json.insert("language","");
    }
    QString url_filepath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) +"/.config/ukui/url.conf";
    //从配置文件中读服务器地址
    QFile  file_url(url_filepath);
    QFileInfo url_fileinfo(url_filepath);
    if(!url_fileinfo.isFile())
    {
        file_url.open(QIODevice::ReadWrite | QIODevice::Text);
        file_url.write("http://feedback.ubuntukylin.com/v1/issue/");
        urlstring.append("http://feedback.ubuntukylin.com/v1/issue/");

    }
    else{
        file_url.open(QIODevice::ReadWrite | QIODevice::Text);
        urlstring = file_url.readLine();
    }
    file_url.close();
    //去掉从配置文件中读出的换行符(删除最后一个字符)
    //urlstring.remove(urlstring.length()-1,1);
    //设置request属性
    set_request_header();
    request.setUrl(QUrl(urlstring));

    qDebug()<<"url:"<<urlstring;
    //发送JSON表单
    QJsonDocument json_doc;
    json_doc.setObject(feedback_info_json);
    QByteArray post_feedback_info_array = json_doc.toJson(QJsonDocument::Compact);

    qDebug()<<post_feedback_info_array;

    accessManager->post(request,post_feedback_info_array);



}
QFile* feedback::add_file_to_Part(QString filepath,QString file_type,QString file_name)
{
    qDebug()<<"this is add_file_to_Part";
    QHttpPart upload_part;
    upload_part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString("form-data; name=\"%1\";filename=\"%2\"").arg(file_type).arg(file_name)));
    QFile *upload_file =  new QFile(filepath);
    if(!(upload_file->open(QIODevice::ReadOnly))){
        qDebug()<<"file open fail";
    }
    upload_part.setBody(upload_file->readAll());
    multiPart->append(upload_part);
    return upload_file;
}
void feedback::send_file_httpserver(QString uid)
{
    qDebug()<<"this is send file http server";
    qDebug()<<"uid:"<<uid;
    //初始化http发送文件请求
    accessManager_file = new QNetworkAccessManager(this);
    connect(accessManager_file, SIGNAL(finished(QNetworkReply*)), this, SLOT(sendfile_finished(QNetworkReply* )));

    //设置请求头
    request_file.setHeader(QNetworkRequest::ContentTypeHeader,"multipart/form-data");
    //设置url
    QString urlstring_file =   urlstring + "annex/";
    request_file.setUrl(QUrl(urlstring_file));

    qDebug()<<urlstring_file<<"---";
    //构建发送信息
    multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    //**************自我添加部分****************************
    QString bd = "X-INSOMNIA-BOUNDARY";
    multiPart->setBoundary(bd.toLatin1());
    request_file.setHeader(QNetworkRequest::ContentTypeHeader,"multipart/form-data;boundary="+bd);

    //把发送反馈信息服务器返回的uid 加入此次发送中
    QHttpPart uid_part;

    uid_part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"issue_uid\""));
    uid_part.setBody(uid.toUtf8());
    multiPart->append(uid_part);


    //判断三个log文件哪个点选了
    if(dpkglogflag ==1){
        //var/log/dpkg.log
        QFile *file_dpkglog = add_file_to_Part("/var/log/dpkg.log","dpkg","dpkg.log");
        m_filesArray.push_back(file_dpkglog);
    }
    if(apportlogflag == 1){
        //var/log/apport.log
        QFile *file_apportlog = add_file_to_Part("/var/log/apport.log","apport","apport.log");
        m_filesArray.push_back(file_apportlog);
    }
    if(syslogflag== 1){
        //var/log/syslog.log
        QFile *file_syslog = add_file_to_Part("/var/log/syslog","syslog","syslog");
        m_filesArray.push_back(file_syslog);
    }
    //获取添加的附件，文件名
    for(int filenum=0; filenum<file_path_list.size(); filenum++)
    {
        //发送文件
        QFile *file_image = add_file_to_Part(file_path_list.at(filenum),"img"+QString::number(filenum+1),file_name_list.at(filenum));
        m_filesArray.push_back(file_image);
    }


    accessManager_file->post(request_file,multiPart);
}
//发送文件请求结束槽函数
void feedback::sendfile_finished(QNetworkReply* reply)
{
    qDebug()<<"this is send file finished";

    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid())
        qDebug() << "status code=" << statusCode.toInt();

    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    if(reason.isValid())
        qDebug() << "reason=" << reason.toString();

    QByteArray bytes = reply->readAll();
    //panduan ==200
    qDebug() << bytes;


}
//邮箱是否填写
void feedback::on_lineEdit_2_textChanged()
{
    email_str = lineEdit_2->text();
    if (email_str.isEmpty()){
        emailflag = 0;
        email_err_msg_label->hide();
    }
    else
        emailflag =1;
    if (describeflag == 1 && emailflag == 1){//邮箱和详细描述都已经填写
        pushButton_2->setEnabled(true);
        pushButton_2->setStyleSheet("font: 18px;border-radius:4px;background-color:rgb(65,95,196);color: rgb(255, 255, 255)");
    }
    else
    {
        pushButton_2->setEnabled(false);//设置提交按钮属性
        pushButton_2->setStyleSheet("font: 18px;border-radius:4px;background-color:rgb(233, 233, 233);color: rgb(255, 255, 255)");
    }
}


//删除文件按钮槽函数
void feedback::del_file_button_clicked()
{
    //QObject::sender()返回发送信号的对象的指针
    QPushButton *btn = qobject_cast<QPushButton*>(QObject::sender());

    qDebug()<<file_name_list.size()<<"before";

    int listnum = file_name_list.size();

    if( btn == file_widget[0]->deletebtn0 )
    {
        file_name_list.removeAt(0);
        file_size_list.removeAt(0);
        file_path_list.removeAt(0);
        qDebug() << "delete 0";
    }
    else if( btn == file_widget[1]->deletebtn0 )
    {
        file_name_list.removeAt(1);
        file_size_list.removeAt(1);
        file_path_list.removeAt(1);

        qDebug() << "delete 1";
    }
    else if( btn == file_widget[2]->deletebtn0 )
    {
        file_name_list.removeAt(2);
        file_size_list.removeAt(2);
        file_path_list.removeAt(2);
        qDebug() << "delete 2";
    }
    else if( btn == file_widget[3]->deletebtn0 )
    {
        file_name_list.removeAt(3);
        file_size_list.removeAt(3);
        file_path_list.removeAt(3);
    }
    else if( btn == file_widget[4]->deletebtn0)
    {
        file_name_list.removeAt(4);
        file_size_list.removeAt(4);
        file_path_list.removeAt(4);
    }
    qDebug()<<file_name_list.size()<<"after";
    foreach(auto item,file_name_list)
    {
        qDebug()<<item<<"after";
    }
    for(int i=0; i<listnum; i++)
    {
        delete file_listwidget_item[i];
        delete file_widget[i];
    }


    update_add_file_window();


    //删除文件后 把上传附件中内容更新
    update_linedit_add_or_del_file();

}



//点击继续反馈信息之后 清空程序内所有信息
void feedback::feedback_info_init(){
    comboBox->setCurrentIndex(0);

    textEdit->setText("");

    lineEdit_2->setText("");

    for(int i=0; i<file_name_list.size(); i++)
    {
        delete file_listwidget_item[i];
        delete file_widget[i];
    }
    foreach(auto item,file_name_list)
    {
        file_name_list.removeOne(item);
    }
    foreach(auto item,file_size_list)
    {
        file_name_list.removeOne(item);
    }
    foreach(auto item,file_path_list)
    {
        file_name_list.removeOne(item);
    }
    lineEdit->setText("");
    label_13->hide();
    email_err_msg_label->hide();
    checkBox->setChecked(false);
    checkBox_2->setChecked(false);
    checkBox_3->setChecked(false);
    checkBox_4->setChecked(false);

}
//添加文件后把文件信息加入qlist
void feedback::add_fileinfo_model()
{
    if(filename.isEmpty()){
        return;
    }
    //获取文件名字
    int nIndex = filename.lastIndexOf('/');
    QString file_name = filename.mid(nIndex+1);
    //获取文件大小
    QFileInfo info;
    QString file_size;
    info.setFile(filename);
    //判断文件大小单位是K 还是M

    file_size = QString::number((float)info.size()/(float)1000,'f',1) + "K";

    if((float)info.size()/(float)1000 > 1000)
        file_size = QString::number((float)info.size()/(float)1000000,'f',1) + "M";


    //向stringlist 添加数据
    qDebug()<<"向stringlist 添加数据"<<file_name_list.size()<<"--"<<file_size_list.size()<<"---"<<file_path_list.size();
    //限制添加的文件最多五个
    if(file_name_list.size() < 5){
        file_name_list.append(file_name);
        file_size_list.append(file_size);
        file_path_list.append(filename);
    }
    for(int i=0; i<file_name_list.size()-1; i++)
    {
        delete file_listwidget_item[i];
        delete file_widget[i];
    }
    update_add_file_window();
}
//根据数据列表 刷新窗口
void feedback::update_add_file_window()
{
    if(filename.isEmpty()){
        return;
    }


    for(int filenum=0; filenum<file_name_list.size(); filenum++)
    {
        file_listwidget_item[filenum] = new QListWidgetItem;
        file_listwidget_item[filenum]->setSizeHint(QSize(320,20));
        //file_listwidget_item[filenum]->setTextColor(QColor());
        file_listwidget->addItem(file_listwidget_item[filenum]);
        file_widget[filenum] = new fileitem_init(file_listwidget);
        file_listwidget->setItemWidget(file_listwidget_item[filenum],file_widget[filenum]);


        file_widget[filenum]->filename_label0->move(0,0);
        file_widget[filenum]->filename_label0->setText(file_name_list.at(filenum));
        file_widget[filenum]->filename_label0->setStyleSheet("font: 12px ;color: rgb(68,68,68);");
        file_widget[filenum]->filename_label0->adjustSize();

        int filename_width = file_widget[filenum]->filename_label0->geometry().width();

        file_widget[filenum]->filesize_label0->move(filename_width+10,0);
        file_widget[filenum]->filesize_label0->setText(file_size_list.at(filenum));
        file_widget[filenum]->filesize_label0->setStyleSheet("font: 12px ;color: rgb(68,68,68);");
        file_widget[filenum]->filesize_label0->adjustSize();

        int filesize_width = file_widget[filenum]->filesize_label0->geometry().width();

        file_widget[filenum]->deletebtn0->setGeometry(filename_width+filesize_width+20,0,25,15);
        file_widget[filenum]->deletebtn0->setText(tr("删除"));
        file_widget[filenum]->deletebtn0->setStyleSheet("font: 12px ;color: rgb(61,107,229)");
        file_widget[filenum]->deletebtn0->setFlat(true);

        connect( file_widget[filenum]->deletebtn0, SIGNAL(clicked()), this, SLOT(del_file_button_clicked()) );

    }
}
//在删除文件之后更新文件信息框
void feedback::update_linedit_add_or_del_file()
{
    int rowNum = file_name_list.size();
    if (rowNum == 0){
        lineEdit->setText("");
    }
    else{
        lineEdit->setText(file_path_list.at(file_path_list.size()-1));
    }
}
//判断总文件大小是否超过10M
bool feedback::all_file_size_than_10M()
{
    int all_filesize = 0;
    QFileInfo file_info;
    for(int filenum=0; filenum<file_path_list.size(); filenum++)
    {
        file_info.setFile(file_path_list.at(filenum));
        all_filesize += file_info.size();
    }

    if(dpkglogflag ==1){
        file_info.setFile("/var/log/dpkg.log");
        all_filesize += file_info.size();
    }
    if(apportlogflag == 1){
        file_info.setFile("/var/log/apport.log");
        all_filesize += file_info.size();
    }
    if(syslogflag== 1){
        file_info.setFile("/var/log/syslog");
        all_filesize += file_info.size();
    }
    //qDebug()<<all_filesize;
    if(all_filesize > 10*1024*1024)
    {
        return true;
    }
    else
        return false;
}
//http客户端初始化
void feedback::httpclient_init()
{
    accessManager = new QNetworkAccessManager(this);
    connect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply* )));
}
//http请求完成
void feedback::finishedSlot(QNetworkReply *reply)
{
    //定时器结束
    submitting_timer->stop();
    pushButton_2->setText(tr("提交"));
    pushButton_2->setEnabled(false);
    pushButton_2->setStyleSheet(QString::fromUtf8("font: 18px;\n"
                                                  "color: rgb(255, 255, 255);\n"
                                                  "background-color: rgb(233, 233, 233);\n"
                                                  "border:4px ;"));
    pushButton_2->setIcon(QIcon());

    qDebug()<<"this is send feedbackinfo finished";

    // 获取http状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid())
        qDebug() << "status code=" << statusCode.toInt();
    if(statusCode.toInt() == 201){
        QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
        if(reason.isValid())
            qDebug() << "reason=" << reason.toString();

        QByteArray bytes = reply->readAll();
        //panduan ==200
        qDebug() << bytes;
        send_fail_flags = 0;
        success_dialog = new submit_success(this);
        success_dialog->setModal(true);
        success_dialog->show();

        //解析JSON 获取uid annex_uid
        QString uid_value;
        QJsonParseError jsonerror;
        QJsonDocument document = QJsonDocument::fromJson(bytes,&jsonerror);


        if(!document.isNull() &&(jsonerror.error == QJsonParseError::NoError))
        {
            if(document.isObject()){
                QJsonObject object = document.object();
                uid_value = object["uid"].toString();
            }
        }
        //发送文件
        send_file_httpserver(uid_value);
    }
    else
    {
        send_fail_flags = 1;
        qDebug() << "finishedSlot errors here";
        qDebug( "found error .... code: %d\n", (int)reply->error());
        qDebug()<<qPrintable(reply->errorString());
        fail_dialog = new submit_fail(this);
        //判断错误类型
        fail_dialog->show_faillinfo((int)reply->error());
        fail_dialog->setModal(true);
        fail_dialog->show();
    }
    reply->deleteLater();

    for (auto iter = m_filesArray.cbegin(); iter != m_filesArray.cend(); iter++)
    {
        (*iter)->close() ;
    }
    m_filesArray.clear();
}
//http设置请求头(发送反馈信息)
void feedback::set_request_header()
{
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
}

void feedback::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    p.save();
    p.setBrush(Qt::white);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(opt.rect,0,0);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    p.restore();

}


