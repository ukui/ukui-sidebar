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
#include "ui_feedback.h"
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
#include <QStyleFactory>
#include <QTimer>
#include <QAbstractItemView>
feedback::feedback(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::feedback)
{


    ui->setupUi(this);
    window_ui_init();


}

feedback::~feedback()
{
    //程序结束时删除所有数据------
    //---------------------------

    delete ui;
}
void feedback::window_ui_init()
{
    //http客户端初始化
    httpclient_init();
    setWindowTitle(tr("用户反馈"));
    setFixedSize(600,695);
    setWindowIcon(QIcon(":/image/kylin-feedback.png"));
    ui->lineEdit->setReadOnly(true);
    ui->pushButton_3->setFeedBack(this);
    ui->pushButton_3->setFlat(true);    //隐藏按钮边框
    //ui->pushButton_3->setCursor(QCursor(Qt::PointingHandCursor));   //设置鼠标接触按钮变为手形
    ui->verticalWidget->hide();
    ui->verticalWidget->setStyleSheet(QString::fromUtf8("border:0.5px solid black"));

    ui->label_13->hide();
    add_systeminfo();//将系统信息添加到信息框

    ui->pushButton_2->setEnabled(false);

    //-----
    ui->verticalWidget->setAttribute(Qt::WA_TranslucentBackground);//设置窗口透明
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setOffset(4,4);
    effect->setColor(QColor(0,0,0));
    effect->setBlurRadius(10);
    ui->frame_2->setGraphicsEffect(effect);
    //数据库初始化
    //设置描述邮箱输入框提示信息
    ui->textEdit->setPlaceholderText(tr("请输入内容"));//设置详细输入框的提示信息
    ui->lineEdit->setPlaceholderText(tr("文件大小不能超过3MB"));


    ui->checkBox_4->setStyleSheet(" spacing: 6px;");
    //设置反馈类型的样式
    ui->errorMailMessage->setVisible(false);
    ui->textEdit_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    this->setStyleSheet("background-color:rgb();");
    ui->label->setStyleSheet("font: 24px;color: rgb()");
    ui->label_2->setStyleSheet("font: 14px;color: rgb()");
    ui->label_3->setStyleSheet("font: 14px;color: rgb()");
    ui->label_4->setStyleSheet("font: 14px;color: rgb()");
    ui->label_8->setStyleSheet("font: 14px;color: rgb()");
    ui->label_9->setStyleSheet("font: 12px;color: rgb()");
    ui->label_7->setStyleSheet("font: 14px;color: rgb()");
    ui->label_10->setStyleSheet("font: 14px;color: rgb()");
    ui->label_11->setStyleSheet("font: 14px;color: rgb()");
    ui->label_12->setStyleSheet("font: 14px;color: rgb()");
    ui->checkBox_4->setStyleSheet("font: 14px;color: rgb()");
    ui->verticalWidget->setStyleSheet("");
    ui->pushButton_2->setStyleSheet("");
    ui->pushButton->setStyleSheet("");
    ui->lineEdit->setStyleSheet("");
    ui->textEdit->setStyleSheet("");
    ui->textEdit_2->setStyleSheet("");
    ui->frame->setStyleSheet("");

    if(QStyleFactory::keys().contains("ukui")){
        QTimer::singleShot(500, this, [=](){
            ui->comboBox->view()->setStyle(QStyleFactory::create("ukui"));
        });
    }
}
//获取图片
void feedback::on_pushButton_clicked()
{
    filename=QFileDialog::getOpenFileName(this,tr("select image"),"/","Image file(*.gif *.jpg *.png)",0);
    //判断文件是否重复添加
    if (file_name_list.size() ==0)
    {
        //添加附件框改变
        ui->lineEdit->setText(filename);
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
            ui->lineEdit->setText(filename);
            add_fileinfo_model();

        }
    }
}

//设置详细描述框最大字符数
void feedback::on_textEdit_textChanged()
{
    textContent = ui->textEdit->toPlainText();
    if (textContent.isEmpty()){
        describeflag = 0;
    }
    else

        describeflag = 1;//详细描述是否填写
    if (emailflag == 1 && describeflag == 1){//邮箱和详细描述都已经填写
        ui->pushButton_2->setEnabled(true);//设置提交按钮属性
      //  ui->pushButton_2->setStyleSheet("font: 18px ;border-radius:4px;background-color:rgb(61,107,229);color: rgb(255, 255, 255)");
    }
    else
    {
        ui->pushButton_2->setEnabled(false);//设置提交按钮属性
    }

    int length = textContent.count();

    int maxLength = 200; // 最大字符数

    if(length > maxLength) {
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.movePosition(QTextCursor::End);
        if(cursor.hasSelection()) {
            cursor.clearSelection();
        }
        cursor.deletePreviousChar();
        //设置当前的光标为更改后的光标ing>

        ui->textEdit->setTextCursor(cursor);
    }

    length = ui->textEdit->toPlainText().count();

}
//系统信息显示
void feedback::systeminfo_show()
{
    ui->verticalWidget->show();
}
//系统信息隐藏
void feedback::systeminfo_hide()
{
    ui->verticalWidget->hide();
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
    ui->label_10->setText(system_info_str);
    //2.获取桌面环境信息
    char * desktop = getenv("DESKTOP_SESSION");
    desktop_info.append(desktop);
    send_dekstop_info.append(desktop);
    desktop_info_str = QString::fromStdString(desktop_info);
    ui->label_12->setText(desktop_info_str);
    //3.获取编码格式
    char * encoding = getenv("GDM_LANG");
    encoding_info.append(encoding);
    send_encoding_info.append(encoding);
    encoding_info_str = QString::fromStdString(encoding_info);
    ui->label_11->setText(encoding_info_str);
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
    feedback_type = ui->comboBox->currentText();
}
//提交按钮
void feedback::on_pushButton_2_clicked()
{
    ui->pushButton_2->setEnabled(false);
 //   ui->pushButton_2->setStyleSheet("font: 18px;border-radius:4px;background-color:rgb(65,95,196);color: rgb(255, 255, 255)");
    //判断文件总大小是否超过10M，如果超过，提示
    if(all_file_size_than_10M() == true)
    {
        ui->label_13->show();
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
//邮箱是否填写
void feedback::on_textEdit_2_textChanged()
{
    email_str = ui->textEdit_2->toPlainText();
    if (email_str.isEmpty()){
        emailflag = 0;
    }
    else{
        //使用正则表达式来判断邮箱地址
        QRegExp rx("^[\\w-]+(\\.[\\w-]+)*@[\\w-]+(\\.[\\w-]+)+");
        int pos=0;
        QRegExpValidator v(rx, 0);
        if(2==v.validate(email_str,pos)){
            ui->errorMailMessage->setVisible(false);
            emailflag = 1;
        }
        else{
            ui->errorMailMessage->setVisible(true);
            emailflag=0;
        }

    }
    if (describeflag == 1 && emailflag == 1){//邮箱和详细描述都已经填写
        ui->pushButton_2->setEnabled(true);
    }
    else
    {
        ui->pushButton_2->setEnabled(false);//设置提交按钮属性
    //    ui->pushButton_2->setStyleSheet("font: 18px;border-radius:4px;background-color:rgb(233, 233, 233);color: rgb(255, 255, 255)");
    }
}

//删除文件按钮槽函数
void feedback::del_file_button_clicked()
{
    int rowNum =file_name_list.size();

    //QObject::sender()返回发送信号的对象的指针
    QPushButton *btn = qobject_cast<QPushButton*>(QObject::sender());

    if( btn == deletefileBtn[0] )
    {
        file_name_list.removeAt(0);
        file_size_list.removeAt(0);
        file_path_list.removeAt(0);
        qDebug() << "delete 0";
    }
    else if( btn == deletefileBtn[1] )
    {
        file_name_list.removeAt(1);
        file_size_list.removeAt(1);
        file_path_list.removeAt(1);

        qDebug() << "delete 1";
    }
    else if( btn == deletefileBtn[2] )
    {
        file_name_list.removeAt(2);
        file_size_list.removeAt(2);
        file_path_list.removeAt(2);
        qDebug() << "delete 2";
    }
    else if( btn == deletefileBtn[3] )
    {
        file_name_list.removeAt(3);
        file_size_list.removeAt(3);
        file_path_list.removeAt(3);
    }
    else if( btn == deletefileBtn[4])
    {
        file_name_list.removeAt(4);
        file_size_list.removeAt(4);
        file_path_list.removeAt(4);
    }
    for(int i=0; i<rowNum; i++)
    {
        delete filename_label[i];
        delete filesize_label[i];
        delete deletefileBtn[i];
    }


    update_add_file_window();
    del_file_change_window();


    //删除文件后 把上传附件中内容更新
    update_linedit_add_or_del_file();
}
//删除附件后调整窗口
void feedback::del_file_change_window()
{
    int rowNum = file_name_list.size();
    window_h -= 29;
    pushbutton2_y -= 29;
    pushbutton3_y -= 29;
    checkbox4_y -= 29;
    widget_y -= 29;


    ui->pushButton_2->setGeometry(pushbutton2_x,pushbutton2_y,pushbutton2_w,pushbutton2_h);
    ui->pushButton_3->setGeometry(pushbutton3_x,pushbutton3_y,pushbutton3_w,pushbutton3_h);
    ui->checkBox_4->setGeometry(checkbox4_x,checkbox4_y,checkbox4_w,checkbox4_h);
    ui->verticalWidget->setGeometry(widget_x,widget_y,widget_w,widget_h);
    setFixedSize(600,window_h);
}
//添加附件后调整窗口
void feedback::add_file_change_window()
{
    if(filename.isEmpty()){
        return;
    }

    window_h += 29;
    pushbutton2_y += 29;
    pushbutton3_y += 29;
    checkbox4_y += 29;
    widget_y += 29;


    ui->pushButton_2->setGeometry(pushbutton2_x,pushbutton2_y,pushbutton2_w,pushbutton2_h);
    ui->pushButton_3->setGeometry(pushbutton3_x,pushbutton3_y,pushbutton3_w,pushbutton3_h);
    ui->checkBox_4->setGeometry(checkbox4_x,checkbox4_y,checkbox4_w,checkbox4_h);
    ui->verticalWidget->setGeometry(widget_x,widget_y,widget_w,widget_h);
    setFixedSize(600,window_h);
}

//点击继续反馈信息之后 清空程序内所有信息
void feedback::feedback_info_init(){
    ui->comboBox->setCurrentIndex(0);
    ui->textEdit->setText("");
    ui->label_9->show();
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->lineEdit->setText("");
    ui->textEdit_2->setText("");
    for(int i=0; i<file_name_list.size(); i++)
    {
        delete filename_label[i];
        delete filesize_label[i];
        delete deletefileBtn[i];
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

    ui->checkBox_4->setChecked(false);

    //变量初始化
    //控件坐标变量
    //window size
    window_w = 600;
    window_h =695;
    //checkBox_4
    checkbox4_x = 35;
    checkbox4_y = 570;
    checkbox4_w = 121;
    checkbox4_h = 24;
    //pushButton_3
    pushbutton3_x = 140;
    pushbutton3_y = 570;
    pushbutton3_w = 60;
    pushbutton3_h = 24;
    //verticalWidget
    widget_x = 100;
    widget_y = 593;
    widget_w = 240;
    widget_h = 130;
    //pushButton_2
    pushbutton2_x = 440;
    pushbutton2_y = 600;
    pushbutton2_w = 120;
    pushbutton2_h = 45;
    //文件名字宽度
    //int filename_width;
    //int filesize_width;
    filename_x = 140;
    filename_y = 480;
    filename_w = 200;
    filename_h = 24;

    syslogflag = 0;
    apportlogflag = 0;
    dpkglogflag = 0;
    describeflag = 0;
    emailflag = 0;
    get_systeminfoflag = 0;
    send_fail_flags = 0;

    ui->pushButton_2->setGeometry(pushbutton2_x,pushbutton2_y,pushbutton2_w,pushbutton2_h);
    ui->pushButton_3->setGeometry(pushbutton3_x,pushbutton3_y,pushbutton3_w,pushbutton3_h);
    ui->checkBox_4->setGeometry(checkbox4_x,checkbox4_y,checkbox4_w,checkbox4_h);
    ui->verticalWidget->setGeometry(widget_x,widget_y,widget_w,widget_h);
    setFixedSize(600,window_h);

}
//添加文件后把文件信息加入数据库
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
    if(file_name_list.size() < 5){
        file_name_list.append(file_name);
        file_size_list.append(file_size);
        file_path_list.append(filename);
    }
    for(int i=0; i<file_name_list.size()-1; i++)
    {
        delete filename_label[i];
        delete filesize_label[i];
        delete deletefileBtn[i];
    }
    update_add_file_window();
    add_file_change_window();
}

//根据数据库 刷新窗口
void feedback::update_add_file_window()
{
    if(filename.isEmpty()){
        return;
    }
    int rowNum = file_name_list.size();
    for(int filenum=0; filenum<rowNum; filenum++)
    {
        filename_label[filenum] = new QLabel(this);
        filename_label[filenum]->move(filename_x,filename_y+(filenum * 29));
        filename_label[filenum]->setText(file_name_list.at(filenum));
        filename_label[filenum]->setStyleSheet("font: 12px ;color: rgb(68,68,68);");
        filename_label[filenum]->adjustSize();
        filename_label[filenum]->show();
        int filename_width = filename_label[filenum]->geometry().width();

        filesize_label[filenum] = new QLabel(this);
        filesize_label[filenum]->setGeometry(filename_x+filename_width+20,filename_y+ (filenum * 29),filename_w,filename_h);
        filesize_label[filenum]->setText(("( "+file_size_list.at(filenum)+" )"));
        filesize_label[filenum]->setStyleSheet("font: 12px;color: rgb(179,179,179)");
        filesize_label[filenum]->adjustSize();
        filesize_label[filenum]->show();
        int filesize_width = filesize_label[filenum]->geometry().width();

        deletefileBtn[filenum] = new QPushButton(this);
        deletefileBtn[filenum]->setGeometry(filename_x+filename_width+20+filesize_width+20,filename_y+ (filenum * 29),31,26);
        deletefileBtn[filenum]->setText(tr("删除"));
        deletefileBtn[filenum]->setStyleSheet("font: 12px ;color: rgb(61,107,229)");
        deletefileBtn[filenum]->setFlat(true);
        deletefileBtn[filenum]->show();
        connect( deletefileBtn[filenum], SIGNAL(clicked()), this, SLOT(del_file_button_clicked()) );
    }
}
//在删除文件之后更新文件信息框
void feedback::update_linedit_add_or_del_file()
{
    int rowNum = file_name_list.size();
    if (rowNum == 0){
        ui->lineEdit->setText("");
    }
    else{
        ui->lineEdit->setText(file_name_list.at(rowNum -1));
    }
}
//判断总文件大小是否超过10M
bool feedback::all_file_size_than_10M()
{
    int all_filesize = 0;
    QFileInfo file_info;
    int rowNum = file_name_list.size();
    for(int filenum=0; filenum<rowNum; filenum++)
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
void feedback::httpclient_init()
{
    accessManager = new QNetworkAccessManager(this);
    connect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply* )));
}

void feedback::finishedSlot(QNetworkReply *reply)
{
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


void feedback::set_request_header()
{
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
}



