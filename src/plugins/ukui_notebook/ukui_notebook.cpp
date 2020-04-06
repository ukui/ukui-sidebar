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
#include "ukui_notebook.h"
#include "ui_ukui_notebook.h"

ukui_NoteBook::ukui_NoteBook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ukui_NoteBook)
{
    ui->setupUi(this);
    ukuiNoteBook_init();
    ukuiNoteBook_connect();
}

ukui_NoteBook::~ukui_NoteBook()
{
    if(notebook == nullptr){
        qDebug() <<"notebook == null";
    }
    else {
        notebook = nullptr;
        qDebug() << "notebook = null";
    }
    delete ui;
    qDebug() << "delete ui";
    delete ui;
}


void ukui_NoteBook::ukuiNoteBook_init()
{
    qDebug() << "ukuiNoteBook_init";
    //字体初始化
    setting = new QSettings("config.ini",QSettings::IniFormat);
    setWindowFlags(Qt::FramelessWindowHint);//开启窗口无边框
    this->setWindowTitle(tr("NoteBook"));
    setWindowIcon(QIcon(":/new/prefix1/SVG/kylin-notebook.svg"));
}

void ukui_NoteBook::ukuiNoteBook_connect()
{
    qDebug() << "ukuiNoteBook_connect";
    connect(ui->ukui_NoteNew,SIGNAL(clicked()),this,SLOT(newWindowsSlot()));
    connect(ui->ukui_NoteClose,SIGNAL(clicked()),this,SLOT(exitFileSlot()));
    connect(ui->ukui_NoteSave,SIGNAL(clicked()),this,SLOT(saveFileSlot()));
    connect(ui->ukui_NoteSaveAs,SIGNAL(clicked()),this,SLOT(saveFileAsSlot()));
    connect(ui->ukui_NoteFont,SIGNAL(clicked()),this,SLOT(fontChooseSlot()));
    connect(ui->ukui_NoteDate,SIGNAL(clicked()),this,SLOT(insertTimeDateSlot()));
    connect(ui->ukui_NotePdf,SIGNAL(clicked()),this,SLOT(exportPdfSlot()));
    connect(ui->ukui_NoteJpg,SIGNAL(clicked()),this,SLOT(exportJpgSlot()));
}

void ukui_NoteBook::realOpenFile()
{
    qDebug() << "..";
}

void ukui_NoteBook::saveFile()
{
    qDebug() << "saveFile";
    qDebug() << fileName;//路径+文件名

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        out << ui->textEdit->document()->toPlainText();
        file.close();
        //this->setWindowTitle(fileName.mid(fileName.lastIndexOf('/')+1)+" - Note");
        fileContent = ui->textEdit->document()->toPlainText();
        qDebug() << "fileContent = " <<ui->textEdit->document()->toPlainText() ;
    }else{
        QMessageBox box(QMessageBox::Question,tr("Tips"),tr("Failed to save file!"));
        box.setIcon(QMessageBox::Warning);
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText (QMessageBox::Ok,QString(tr("OK")));
        box.exec();
    }
//    QFileInfo info(fileName);
//    qDebug() << info.created();
//    qDebug() << info.lastModified();
//    qDebug() << info.fileName();
    emit fileSaved(fileName);
    qDebug() << "fileName = " << fileName;
    qDebug() << "emid filesaved";
}

void ukui_NoteBook::saveTextToFile()
{
    qDebug() << "..";
}

void ukui_NoteBook::ukui_setShortCut()
{
    qDebug() << "..";
}

void ukui_NoteBook::mousePressEvent(QMouseEvent *event)
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

void ukui_NoteBook::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);

    p.setBrush(QBrush(QColor("#161617")));
    p.setOpacity(0.42);
    p.setPen(Qt::NoPen);

    p.drawRoundedRect(opt.rect,0,0);
    p.drawRect(opt.rect);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}

void ukui_NoteBook::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - m_lastPoint);
        event->accept();
    }
}


/***************Slots**************/
void ukui_NoteBook::newFileSlot()
{
    qDebug() << "..";
}

void ukui_NoteBook::exitFileSlot()
{
    qDebug() << "exitFileSlot";
    //文档已经修改
    if(ui->textEdit->document()->isModified()&& !ui->textEdit->document()->isEmpty() && fileContent != ui->textEdit->document()->toPlainText()){
        QMessageBox box(QMessageBox::Question,tr("NoteBook"),tr("Save current text"));
        box.setIcon(QMessageBox::NoIcon);
        box.setStandardButtons (QMessageBox::Ok|QMessageBox::Ignore|QMessageBox::Cancel);
        box.setButtonText (QMessageBox::Ok,QString(tr("Yes")));
        box.setButtonText (QMessageBox::Ignore,QString(tr("No")));
        box.setButtonText (QMessageBox::Cancel,QString(tr("Cancel")));
        int result = box.exec();
        if(result == QMessageBox::Ok){
            if(fileName.isEmpty()){//新建
                //弹出保存文件对话框
                fileName = QFileDialog::getSaveFileName(this, tr("Save File"),QDir::homePath(),tr("Text File (*.txt*);;"));
                if(!fileName.isEmpty()){
                    if(QFileInfo(fileName).suffix().isEmpty()){
                        fileName.append(".txt");
                        qDebug() << fileName;
                    }
                    //保存文件
                    this->saveFile();
//                    else if (!(QFileInfo(fileName).suffix() == ".txt")) {
//                        QMessageBox box(QMessageBox::Question,"提示","保存文件失败！");
//                        box.setIcon(QMessageBox::Warning);
//                        box.setStandardButtons (QMessageBox::Ok);
//                        box.setButtonText (QMessageBox::Ok,QString("确定"));
//                        box.exec();
//                    }
                }
            }else{
                this->saveFile();
            }

        }else  if(result == QMessageBox::Ignore){
            //不保存 关闭
            this->close();
        }
    }else{
        this->close();
    }
}

void ukui_NoteBook::insertTimeDateSlot()
{
    qDebug() << "..";
    QDateTime time = QDateTime::currentDateTime();//获取当前系统时间
    ui->textEdit->append(time.toString("hh:mm yyyy-MM-dd"));
}

void ukui_NoteBook::newWindowsSlot()
{
    qDebug() << "newWindowsSlot";
    notebook =  new ukui_NoteBook;
    notebook->show();
}

void ukui_NoteBook::openFileSlot()
{
    qDebug() << "..";
}

void ukui_NoteBook::saveFileSlot()
{
    qDebug() << "saveFileSlot";
    if(ui->textEdit->document()->isModified() && !ui->textEdit->document()->isEmpty()
            && fileContent != ui->textEdit->document()->toPlainText())
    {
        //判断是新建还是读取的文本
        if(fileName.isEmpty())
        {//新建
            //弹出保存文件对话框
            //this->setStyleSheet("QFileDialog{background-color:rgb(0,0,0);}");
            fileName = QFileDialog::getSaveFileName(this, tr("Save File"),QDir::homePath(),tr("Text File(*.txt*);;"));
            if(!fileName.isEmpty())
            {
                if(QFileInfo(fileName).suffix().isEmpty())
                {
                    fileName.append(".txt");
                }
                //保存文件
                this->saveFile();
            }
        }else{//读取的文本
            this->saveFile();
        }
    }
    else if(ui->textEdit->document()->isEmpty()){
        QMessageBox box(QMessageBox::Question,tr("Tips"),tr("Text content is empty"));
        box.setIcon(QMessageBox::Warning);
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText (QMessageBox::Ok,QString(tr("OK")));
        box.exec();
    }
    else if (fileContent == ui->textEdit->document()->toPlainText()) {
            QMessageBox box(QMessageBox::Question,tr("Tips"),tr("Text not modified"));
            box.setIcon(QMessageBox::Warning);
            box.setStandardButtons (QMessageBox::Ok);
            box.setButtonText (QMessageBox::Ok,QString(tr("OK")));
            box.exec();
    }
    else if(!ui->textEdit->document()->isModified())
    {
        QMessageBox box(QMessageBox::Question,tr("Tips"),tr("Text not modified"));
        box.setIcon(QMessageBox::Warning);
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText (QMessageBox::Ok,QString(tr("OK")));
        box.exec();
    }
}

void ukui_NoteBook::saveFileAsSlot()
{
    qDebug() << "saveFileAsSlot";

    if(ui->textEdit->document()->isEmpty()){
        QMessageBox box(QMessageBox::Question,tr("Tips"),tr("Text content is empty"));
        box.setIcon(QMessageBox::Warning);
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText (QMessageBox::Ok,QString(tr("OK")));
        box.exec();
    }
    //如果文本不为空
    else{
        //弹出保存文件对话框
        fileName = QFileDialog::getSaveFileName(this, tr("Open file"),QDir::homePath(),tr("Text file (*.*);;"));
        if(!fileName.isEmpty()){
            //添加文件名后缀
            if(QFileInfo(fileName).suffix().isEmpty())
            {
                fileName.append(".txt");
            }
            //保存文件
            this->saveFile();
        }
    }
}

void ukui_NoteBook::textStatusSlot()
{
    qDebug() << "..";
}

void ukui_NoteBook::exportPdfSlot()
{
    qDebug() << "..";
    QString file = QFileDialog::getSaveFileName(this, tr("Export pdf"), "", tr("Pdf file(*.pdf);;"));
    if(!file.isEmpty()){
        if(QFileInfo(file).suffix().isEmpty()){
            file.append(".pdf");
        }
    }
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(file);
    ui->textEdit->document()->print(&printer);
}

void ukui_NoteBook::exportJpgSlot()
{
    qDebug() << "export jpg";
    int w,h;
    w = ui->textEdit->width();
    h = ui->textEdit->height();
    QPixmap exportImage(w,h);
    exportImage.fill(Qt::white);
    QPainter painter(&exportImage);
    QPixmap axisPixmap = ui->textEdit->grab(QRect(0,0,-1,-1));
    painter.drawPixmap(0,0,axisPixmap);

    QString pic = QFileDialog::getSaveFileName(this,tr("Export picture"),"",tr("Images(*.jpg)"));
    if(!pic.isEmpty()){
        if(QFileInfo(pic).suffix().isEmpty()){
            pic.append(".jpg");
        }
        exportImage.save(pic);
    }
}

void ukui_NoteBook::fontChooseSlot()
{
    qDebug() << "..";
    QFont textFont=  ui->textEdit->font();
    bool ok;
    QFont font = QFontDialog::getFont(&ok, textFont,this,tr("Font selection"));
    if (ok) {
        ui->textEdit->setFont(font);

        setting->beginGroup("config");//beginGroup与下面endGroup 相对应，“config”是标记
        setting->setValue("family",QVariant(font.family()));
        setting->setValue("point_size",QVariant(font.pointSize()));
        setting->setValue("italic",QVariant(font.italic() == true ?"1":"0"));
        setting->setValue("bold",QVariant(font.bold()== true ?"1":"0"));
        setting->setValue("overline",QVariant(font.overline()== true ?"1":"0"));
        setting->setValue("underline",QVariant(font.underline()== true ?"1":"0"));
        setting->endGroup();
    }
}


