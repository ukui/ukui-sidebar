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

/****************Slots*******************/

void SingleItemWidget::clickDelBtn()
{
    qDebug() << "child  click del";
    emit childDelEvent();
}

void SingleItemWidget::SingleItem_init()
{
    qDebug() << "";
    //文本框属性
    //ui->textEdit_Item->setReadOnly(true);//只读
    //ui->textEdit_Item->setFocusPolicy(Qt::NoFocus);//无焦点
    //ui->textEdit_ItemDate->setReadOnly(true);
    //按钮属性
    pushButtonDel = new singleitemButton();
    pushButtonDel->setObjectName("pushButtonDel");
    pushButtonDel->setGeometry(QRect(510,20,34,34));
    pushButtonDel->setParent(this);
    pushButtonDel->hide();

//    m_pGrouBoxUpButtonHLayout = new QHBoxLayout;
//    m_pGrouBoxUpButtonHLayout->setContentsMargins(0,5,0,0);
//    m_pGrouBoxUpButtonHLayout->addWidget(pushbuttonDel);
//    this->setLayout(m_pGrouBoxUpButtonHLayout);

//    ui->pushButtonDel->setFixedSize(34,34);
//    ui->pushButtonDel->setIconSize(QSize(16,16));
//    QIcon pushdelIcon;
//    pushdelIcon.addFile(":/new/prefix1/SVG/delete-b.svg");
//    ui->pushButtonDel->setIcon(pushdelIcon);

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


void SingleItemWidget::SingleItem_conn()
{
    connect(this->pushButtonDel,SIGNAL(buttonclick()),this,SLOT(clickDelBtn()));
}


