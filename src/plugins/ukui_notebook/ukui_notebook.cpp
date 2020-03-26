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
    //窗口属性
    setWindowFlags(Qt::FramelessWindowHint);//开启窗口无边框
    setWindowOpacity(0.8);//设置窗口透明度
    ui->textEdit->setWindowOpacity(0.9);
    //窗口弹出位置
    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
    this->setWindowTitle(tr("NoteBook"));
    //this->setStyleSheet("background-color: rgb(0,0,0)");
    //按钮属性
    ui->ukui_NoteClose->setStyleSheet("QPushButton{image:url(:/new/prefix1/SVG/dark_theme/close.svg);}"
                                      "QPushButton:hover{image:     \
                                               url(:/new/prefix1/SVG/dark_theme/close-hover.svg);}"
                                      "QPushButton:pressed{image:      \
                                               url(:/new/prefix1/SVG/dark_theme/close-click.svg);}"
                                      "border-width:0;              \
                                       border-style:outset;");
    ui->ukui_NoteNew->setStyleSheet("QPushButton{image:url(:/new/prefix1/SVG/new-s.svg);}"
                                    "QPushButton:hover{image:url(:/new/prefix1/SVG/new-s-hover.svg);}"
                                    "QPushButton:pressed{image:url(:/new/prefix1/SVG/new-s-click.svg);}");
    ui->ukui_NoteFont->setStyleSheet("QToolButton{image:url(:/new/prefix1/SVG/font.svg);}"
                                     "QToolButton:hover{image:url(:/new/prefix1/SVG/font-hover.svg);}"
                                     "QToolButton:pressed{image:url(:/new/prefix1/SVG/font-click.svg);}");

    ui->ukui_NoteJpg->setStyleSheet("QToolButton{image:url(:/new/prefix1/SVG/exportJPG.svg);}"
                                    "QToolButton:hover{image:url(:/new/prefix1/SVG/exportJPG-hover.svg);}"
                                    "QToolButton:pressed{image:url(:/new/prefix1/SVG/exportJPG-click.svg);}");

    ui->ukui_NotePdf->setStyleSheet("QToolButton{image:url(:/new/prefix1/SVG/exportPDF.svg);}"
                                    "QToolButton:hover{image:url(:/new/prefix1/SVG/exportPDF-hover.svg);}"
                                    "QToolButton:pressed{image:url(:/new/prefix1/SVG/exportPDF-click.svg);}");

    ui->ukui_NoteDate->setStyleSheet("QToolButton{image:url(:/new/prefix1/SVG/insertTime.svg);}"
                                     "QToolButton:hover{image:url(:/new/prefix1/SVG/insertTime-hover.svg);}"
                                     "QToolButton:pressed{image:url(:/new/prefix1/SVG/insertTime-click.svg);}");

    ui->ukui_NoteDel->setStyleSheet("QToolButton{image:url(:/new/prefix1/SVG/delete.svg);}"
                                    "QToolButton:hover{image:url(:/new/prefix1/SVG/delete-hover.svg);}"
                                    "QToolButton:pressed{image:url(:/new/prefix1/SVG/delete-click.svg);}");
    ui->ukui_NoteClose->setFocusPolicy(Qt::NoFocus);
    //字体初始化
    setting = new QSettings("config.ini",QSettings::IniFormat);

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
        this->setWindowTitle(fileName.mid(fileName.lastIndexOf('/')+1)+" - Note");
        fileContent = ui->textEdit->document()->toPlainText();
        qDebug() << "fileContent = " <<ui->textEdit->document()->toPlainText() ;
        qDebug() << "emit filesaved";
        emit fileSaved(fileName);
    }else{
        QMessageBox box(QMessageBox::Question,"Tips","Failed to save file!");
        box.setIcon(QMessageBox::Warning);
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText (QMessageBox::Ok,QString("OK"));
        box.exec();
    }
//    QFileInfo info(fileName);
//    qDebug() << info.created();
//    qDebug() << info.lastModified();
//    qDebug() << info.fileName();

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
        QMessageBox box(QMessageBox::Question,"NoteBook","Save current text or not");
        box.setIcon(QMessageBox::NoIcon);
        box.setStandardButtons (QMessageBox::Ok|QMessageBox::Ignore|QMessageBox::Cancel);
        box.setButtonText (QMessageBox::Ok,QString("Yes"));
        box.setButtonText (QMessageBox::Ignore,QString("No"));
        box.setButtonText (QMessageBox::Cancel,QString("Cancel"));
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
    //新建的文件
    if(fileName.isEmpty())
    {   //如果文本内容不为空
        if(!ui->textEdit->document()->isEmpty())
        {
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
        }
        //文本内容为空
        else{
            QMessageBox box(QMessageBox::Question,"Tips","Text content is empty");
            box.setIcon(QMessageBox::Warning);
            box.setStandardButtons (QMessageBox::Ok);
            box.setButtonText (QMessageBox::Ok,QString("OK"));
            box.exec();
        }
    }
    //打开的已存在文件
    else
    {   //文本内容为空
        if(ui->textEdit->document()->isEmpty()){
                QMessageBox box(QMessageBox::Question,"Tips","Text content is empty");
                box.setIcon(QMessageBox::Warning);
                box.setStandardButtons (QMessageBox::Ok);
                box.setButtonText (QMessageBox::Ok,QString("OK"));
                box.exec();
        }
//        else if(fileContent == ui->textEdit->document()->toPlainText())
//        {
//            qDebug() << "fileContent = " << fileContent;
//            QMessageBox box(QMessageBox::Question,"提示","文本未修改");
//            box.setIcon(QMessageBox::Warning);
//            box.setStandardButtons (QMessageBox::Ok);
//            box.setButtonText (QMessageBox::Ok,QString("确定"));
//            box.exec();
//        }
        else if(!ui->textEdit->document()->isModified())
        {
            QMessageBox box(QMessageBox::Question,"Tips","Text not modified");
            box.setIcon(QMessageBox::Warning);
            box.setStandardButtons (QMessageBox::Ok);
            box.setButtonText (QMessageBox::Ok,QString("OK"));
            box.exec();
        }
        else
            this->saveFile();

    }

}

void ukui_NoteBook::saveFileAsSlot()
{
    qDebug() << "saveFileAsSlot";
    QString f;
    if(ui->textEdit->document()->isEmpty()){
        QMessageBox box(QMessageBox::Question,"Tips","Text content is empty");
        box.setIcon(QMessageBox::Warning);
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText (QMessageBox::Ok,QString("OK"));
        box.exec();
    }
    //如果文本不为空
    else{
        //弹出保存文件对话框
        f = QFileDialog::getSaveFileName(this, tr("Open file"),QDir::homePath(),tr("Text file (*.*);;"));
        if(!f.isEmpty()){
            //添加文件名后缀
            if(QFileInfo(f).suffix().isEmpty())
            {
                f.append(".txt");
                fileName = f;
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
    QString file = QFileDialog::getSaveFileName(this, "Export pdf", "", "Pdf file(*.pdf);;");
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

    QString pic = QFileDialog::getSaveFileName(this,"Export picture","","Images(*.jpg)");
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


