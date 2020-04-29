#include "delete_msg.h"
#include "ui_delete_msg.h"

delete_msg::delete_msg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_msg)
{
    ui->setupUi(this);
    this->setProperty("blurRegion", QRegion(QRect(1, 1, 1, 1)));
    setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
}

delete_msg::~delete_msg()
{
    delete ui;
}

void delete_msg::on_closebtn_clicked()
{
    close_sure = 0;
    this->close();
}

void delete_msg::on_surebtn_clicked()
{
    close_sure = 1;
    this->close();
}

void delete_msg::on_cancelbtn_clicked()
{
    close_sure = 0;
    this->close();
}
