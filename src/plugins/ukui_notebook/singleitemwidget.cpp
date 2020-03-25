#include "singleitemwidget.h"
#include "ui_singleitemwidget.h"

SingleItemWidget::SingleItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleItemWidget)
{
    ui->setupUi(this);

    SingleItem_init();
    SingleItem_conn();
}

SingleItemWidget::~SingleItemWidget()
{
    delete ui;
}



void SingleItemWidget::SingleItem_conn()
{
    connect(ui->pushButtonDel,SIGNAL(clicked()),this,SLOT(clickDelBtn()));
}


/****************Slots*******************/

void SingleItemWidget::clickDelBtn()
{
    qDebug() << "child  click del";
    emit childDelEvent();
}

void SingleItemWidget::SingleItem_init()
{
    qDebug() << "";
//    //设置图片大小
//    ui->toolButtonDel->setIconSize(QSize(12,16));
//    ui->toolButtonLock->setIconSize(QSize(12,16));
    //文本框属性
    //ui->textEdit_Item->setReadOnly(true);//只读
    //ui->textEdit_Item->setFocusPolicy(Qt::NoFocus);//无焦点
    //ui->textEdit_ItemDate->setReadOnly(true);
    //按钮属性
    ui->pushButtonDel->setFixedSize(QSize(16,16));
    //ui->pushButtonDel->setSizePolicy(QSize());
    ui->pushButtonDel->setStyleSheet("QPushButton{image:url(:/new/prefix1/SVG/delete-b.svg);}"
                             "QPushButton:hover{image:url(:/new/prefix1/SVG/delete-b-hover.svg);}"
                             "QPushButton:pressed{image:url(:/new/prefix1/SVG/delete-b-click.svg);}");
    ui->label_Item->setStyleSheet("font-size:14px;      \
                                  font-family:Noto Sans CJK SC;     \
                                  font-weight:400;      \
                                  color:rgba(255,255,255,1);        \
                                  background-color: rgb(0, 0, 0);      \
                                  line-height:40px;");
    ui->label_ItemDate->setStyleSheet("font-size:12px;   \
                             font-family:Noto Sans CJK SC;  \
                             font-weight:400;   \
                             color:rgba(255,255,255,1);     \
                             background-color: rgb(0, 0, 0);      \
                             line-height:40px;");
}




