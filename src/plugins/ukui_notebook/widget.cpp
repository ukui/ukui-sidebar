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
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{    
    translator = new QTranslator;
    QLocale locale;
    //获取系统语言环境
    if ( locale.language() == QLocale::Chinese ) {
        translator->load(QString(":/new/translation/ukui_notebook_zh_CN.qm"));  //选择翻译文件
        QApplication::installTranslator(translator);
    }
    ui->setupUi(this);
    sqlInit();
    ukui_init();
    ukui_conn();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::error_throw()
{
    try
    {
        MY_THROW(ExceptionDerived,"error throw");
    }
    catch(ExceptionDerived &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void Widget::ukui_init()
{
    //窗口属性
    setWindowFlags(Qt::FramelessWindowHint);//开启窗口无边框
    setWindowOpacity(0.8);//窗口透明度
    //弹出位置
    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
    //组件属性
    //ui->listWidget->setAttribute(Qt::WA_TranslucentBackground);//设置透明度
    //ui->toolButton->setAttribute(Qt::WA_TranslucentBackground);
    //标题
    this->setWindowTitle(tr("Note"));
    setWindowIcon(QIcon(":/new/prefix1/SVG/kylin-notebook.svg"));
    ui->ukui_labelTitle->setStyleSheet("width:47px;        \
                                        height:23px;        \
                                        font-size:20px;     \
                                        font-family:Noto Sans CJK SC;       \
                                        font-weight:400;        \
                                        line-height:40px;           \
                                        background-color: rgb(0, 0, 0);     \
                                        color: rgb(255, 255, 255);");
    //按钮
    ui->pushButton_Mini->setStyleSheet("QPushButton#pushButton_Mini{image:   \
                                                url(:/new/prefix1/SVG/dark_theme/min.svg);}"
                                       "QPushButton#pushButton_Mini:hover{image:     \
                                                url(:/new/prefix1/SVG/dark_theme/min-hover.svg);}"
                                       "QPushButton#pushButton_Mini:pressed{image: \
                                                url(:/new/prefix1/SVG/dark_theme/min-click.svg);}"
                                       "border-radius:4px;");
    ui->pushButton_Exit->setStyleSheet("QPushButton#pushButton_Exit{image:   \
                                                url(:/new/prefix1/SVG/dark_theme/close.svg);}"
                                       "QPushButton#pushButton_Exit:hover{image:     \
                                                url(:/new/prefix1/SVG/dark_theme/close-hover.svg);}"
                                       "QPushButton#pushButton_Exit:pressed{image:      \
                                                url(:/new/prefix1/SVG/dark_theme/close-click.svg);}"
                                       "border-radius:4px;");
    ui->toolButton->setStyleSheet("QToolButton#toolButton{image:url(:/new/prefix1/SVG/new-b.svg);}"
                             "QToolButton#toolButton:hover{image:url(:/new/prefix1/SVG/new-b-hover.svg);}"
                             "QToolButton#toolButton:pressed{image:url(:/new/prefix1/SVG/new-b-click.svg);}");
    //全局new
    ukui_notebook = new ukui_NoteBook;
    //搜索框
    //ui->ukui_SearchLine->setToolTip(tr("搜索"));
    //ui->ukui_SearchLine->setText(tr("搜索"));

    /*********ListWidget init ************/
    //ui->listWidget->setIconSize(QSize(16,16));
    //ui->listWidget->setViewMode(QListWidget::IconMode);//设置图片文本 垂直显示
    //ui->listWidget->setMovement(QListWidget::Static);
    //ui->listWidget->openPersistentEditor(false);//设置item可编辑
    //设置滚动条样式(使用.qss)
    //ui->listWidget->verticalScrollBar()->setCursor(Qt::PointingHandCursor);
    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏垂直滚动条
    ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏水平滚动条

//    ui->listWidget->setStyleSheet("QListWidget::Item:hover{background-color:rgb(0,0,0);}"
//                                    "QlistWidget::Item:selected{background-color:rgb(0,0,0);}"
//                                    "QListWidget::Item:selected:!active{active{background-color:red;}");
    //ui->listWidget->verticalScrollBar()->setStyleSheet("QScrollBar{width:1px;}");

}

void Widget::ukui_conn()
{
    qDebug() << "conn";
    connect(ui->pushButton_Exit,SIGNAL(clicked()),this,SLOT(exitSlot()));
    connect(ui->pushButton_Mini,SIGNAL(clicked()),this,SLOT(miniSlot()));
    connect(ui->toolButton,SIGNAL(clicked()),this,SLOT(newSlot()));
    connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(listDoubleClickSlot()));
    connect(ui->listWidget,SIGNAL(itemPressed(QListWidgetItem*)),this,SLOT(listClickSlot()));
    //connect(singleItem[txtNum]->pushButtonDel,SIGNAL(clicked()),this,SLOT(listDelSingleSlot()));      //子窗口Del点击事件
    qDebug() << "connect end";
}

void Widget::sqlInit()
{
    sqlFilePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) +
                "/.config/notebookSql.db";
    qDebug() << "db file path = " << sqlFilePath;
    if(sqlFilePath.isEmpty())
        return;
    qDebug() << QSqlDatabase::drivers();
    sqlDb = QSqlDatabase::addDatabase("QSQLITE");
    sqlDb.setDatabaseName(sqlFilePath);
    if(!sqlDb.open())
    {
        qDebug() << "sqlDb open failed";
        QMessageBox::warning(this,"Error","open sqlDb failed",QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }

    QSqlQuery sqlQuery;
    sqlQuery.exec(QString(
      "create table fileInfo (fileName QString)"));

    sqlModel = new QSqlTableModel(this,sqlDb);  //数据表
    sqlModel->setTable("fileInfo");
    sqlModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    if(!sqlModel->select())                     //查询数据
    {
//        qDebug() << "sqlModel select failed";
//        QMessageBox::critical(this,"Error","open sqlModel failed,error message\n"
//                              +sqlModel->lastError().text(),
//                              QMessageBox::Ok,QMessageBox::NoButton);
//        return;
    }
    sqlUpdateItem();
}

//读取数据库，更新Item
void Widget::sqlUpdateItem(){
     rowNum = sqlModel->rowCount();
     qDebug() << "sqlUpdateItem" << rowNum;

     QString currentFileName;
     QString fileContent;
     for(int txtNum = 0; txtNum < rowNum; txtNum++){
        qDebug() << "txtNum = " << txtNum;                
        item[txtNum] =new QListWidgetItem();
        item[txtNum]->setSizeHint(QSize(569,74));
        ui->listWidget->addItem(item[txtNum]);
        singleItem[txtNum]= new SingleItemWidget(ui->listWidget);
        ui->listWidget->setItemWidget(item[txtNum],singleItem[txtNum]);

        currentFileName = sqlModel->index(txtNum,0).data().toString();
        QFile currentFile(currentFileName);
        qDebug() << "currentFile """ << currentFile;
        qDebug() << "currentfilename ::" << currentFileName;
        if(!currentFile.open(QIODevice::ReadOnly | QIODevice::Text))
            qDebug() << "open file failed";
        QTextStream aStream(&currentFile);//用文本流读取文件
        aStream >> fileContent;
        //aStream.setAutoDetectUnicode(true);//自动检测unicode,才能显示汉字
        getFileModifyTime(currentFileName);
        qDebug() << "astream.readall" << aStream.readAll() << fileContent;
        singleItem[txtNum]->ui->label_Item->setText(fileContent);
        singleItem[txtNum]->ui->label_ItemDate->setText(modifyTime);
        currentFile.close();
        //子窗口Del点击事件
        connect(singleItem[txtNum],SIGNAL(childDelEvent()),this,SLOT(listDelSingleSlot()));
     }
}

//添加Item，保存到数据库
void Widget::sqlAddItem(){
    rowNum = sqlModel->rowCount();
    int flag = 0;
//    QDateTime dateTime = QDateTime::currentDateTime();//获取当前系统时间
    qDebug() << "添加Item，保存到数据库";
    qDebug() << "sqlAddItem rowNum = " << rowNum;
    qDebug() << "sqlAddItem filename = " << filename;

    for(int i = 0;i <= rowNum;i++)
    {
        if(filename == sqlModel->index(i,0).data().toString())
        {
            flag = 1;
        }
    }
    if(flag != 1)
    {
        sqlModel->insertRow(rowNum);
        sqlModel->setData(sqlModel->index(rowNum, 0), filename);
        //model->setData(model->index(rowNum, 1), dateTime);
        bool tttt = sqlModel->submitAll();
        qDebug()<<tttt<<"tttt";
    }

    for(int i=0; i < rowNum; i++)
    {
        delete item[i];
        delete singleItem[i];
    }

    sqlUpdateItem();
}

void Widget::getFileModifyTime(QString fileInfo)
{
    QFileInfo info(fileInfo);
    if(info.exists())
    {
        //QDateTime dt = info.created();
        QDateTime dt = info.lastModified();
        modifyTime = tr("%1").arg(dt.toString("yyyy/MM/dd hh:mm"));
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {

            move(event->globalPos() - m_lastPoint);

            event->accept();

        }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit this->listItemClicked(index);
    }
    if (event->button() == Qt::LeftButton) {

            m_lastPoint = event->globalPos() - frameGeometry().topLeft();

            event->accept();

    }
}

//void Widget::paintEvent(QPaintEvent *)
//{
//    QStyleOption opt;
//    opt.init(this);
//    QPainter p(this);

//    p.setBrush(QBrush(QColor("#161617")));
//    p.setOpacity(0.42);
//    p.setPen(Qt::NoPen);

//    p.drawRoundedRect(opt.rect,0,0);
//    p.drawRect(opt.rect);
//    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);

//     QPainter p(this);
//     p.setCompositionMode( QPainter::CompositionMode_Clear );
//     p.fillRect( 10, 10, 300, 300, Qt::SolidPattern );

//}



//********************Slots************************//

void Widget::exitSlot(){
    this->close();
}

void Widget::miniSlot()
{
    this->showMinimized();
}

void Widget::editSlot()
{
    qDebug() << "edit";
}

void Widget::newSlot()
{
    qDebug() << "widget new";
    //新建一个笔记本
    ukui_notebook =  new ukui_NoteBook;
    ukui_notebook->show();


    qDebug() << "子窗口向父窗口传filename参数";
    connect(ukui_notebook,SIGNAL(fileSaved(QString)),this,SLOT(fileSavedSlot(QString)));
}

void Widget::listClickSlot()
{
    int listnum = ui->listWidget->currentRow();
    rowNum = sqlModel->rowCount();
    qDebug() << rowNum;
    for (int i = 0;i < rowNum; i++)
    {
        singleItem[i]->pushButtonDel->hide();
    }
    qDebug() << "listClickSLot  listnum = " << listnum;
    singleItem[listnum]->pushButtonDel->show();
}

void Widget::listDoubleClickSlot()
{
    connect(ukui_notebook,SIGNAL(fileSaved(QString)),this,SLOT(fileSavedSlot(QString)));
    QString currentFileName;
    qDebug() << "listDoubleclick";
    qDebug() << "currentRow" << ui->listWidget->currentRow();
    //获取当前选中的item下标
    //打开下标对应数据库中存储的文件路径加名称
    ukui_notebook->fileName = sqlModel->index(ui->listWidget->currentRow(), 0).data().toString();
    QFile currentFile(ukui_notebook->fileName);
    qDebug() << "listDoubleclick currentFileName = " << ukui_notebook->fileName;
    if(!currentFile.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "open file failed";
    QTextStream aStream(&currentFile);//用文本流读取文件
    aStream.setAutoDetectUnicode(true);//自动检测unicode,才能显示汉字
    ukui_notebook->ui->textEdit->setPlainText(aStream.readAll());
    currentFile.close();
    ukui_notebook->show();
}

void Widget::listDelSingleSlot(){
    qDebug() << "del list";
    int num=ui->listWidget->currentRow();
    int rowNum = sqlModel->rowCount();

    qDebug() << "数据库行号"  << rowNum <<"   ======================================";
    qDebug() << "item计数"   << num    <<"     =====================================";

    sqlModel->removeRows(num, 1);
    qDebug() << "delete " <<num;

    for(int i=0; i<rowNum; i++)
    {
        delete item[i]; 
        delete singleItem[i];
    }
    sqlModel->submitAll();   //提交
    sqlUpdateItem();
}

void Widget::fileSavedSlot(QString data)
{
    qDebug() << "fileSavedSlot";
    filename = data;
    sqlAddItem();
}

