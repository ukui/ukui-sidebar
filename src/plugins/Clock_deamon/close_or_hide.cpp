#include "close_or_hide.h"
#include "ui_close_or_hide.h"

close_or_hide::close_or_hide(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::close_or_hide)
{
    ui->setupUi(this);
    this->setProperty("blurRegion", QRegion(QRect(1, 1, 1, 1)));
    setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    ui->radioButton_2->setChecked(1);
}

close_or_hide::~close_or_hide()
{
    delete ui;
}

void close_or_hide::on_closebtn_clicked()
{
    this->hide();
    close_flag = 0;
}

void close_or_hide::on_surebtn_clicked()
{
    if(ui->radioButton_2->isChecked()==true){
        this->hide();
         close_flag = 1;
    }else{
        this->hide();
        close_flag = 2;
    }
}

void close_or_hide::on_cancelbtn_clicked()
{
    this->hide();
}
