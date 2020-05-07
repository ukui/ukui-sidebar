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
#include <QBitmap>
#include <QPainter>

#include "noteExitWindow.h"
#include "ui_noteExitWindow.h"
#include "widget.h"
#include "ui_widget.h"

noteExitWindow::noteExitWindow(Widget* page, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::noteExitWindow)
{
    ui->setupUi(this);
    pNotebook = page;
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.setRenderHint(QPainter::Antialiasing);
    p.drawRoundedRect(bmp.rect(),6,6);
    setMask(bmp);

    this->setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    connect(pNotebook->ui->sort_2_btn,SIGNAL(clicked()),this,SLOT(color_clicked()));
    color_clicked();
}

noteExitWindow::~noteExitWindow()
{
    delete ui;
}

void noteExitWindow::on_pushButton_clicked()
{
    this->close();
}

void noteExitWindow::on_pushButton_2_clicked()
{
    //qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    this->close();
    pNotebook->close();
    if(ui->checkBox->isChecked()==true)
    {
        //emit requestSetNoteNull();
        for (auto it = pNotebook->m_editors.begin(); it!= pNotebook->m_editors.end();it++) {
            (*it)->close();
//            qDebug() << "before swap" << pNotebook->m_editors.size();
//            std::vector<Edit_page*> tmp;
//            pNotebook->m_editors.swap(tmp);
//            qDebug() << "after swap" << pNotebook->m_editors.size();
        }
    }
}

void noteExitWindow::color_clicked()
{
    if(!pNotebook->m_isThemeChanged)
    {
        light_show();
    }else{

        black_show();
    }
}

void noteExitWindow::light_show()
{
    ui->widget->setStyleSheet("QWidget{background-color: rgba(255, 255, 255, 0.4);}");

    ui->label->setStyleSheet("background-color: rgba();\
                             font-size:20px;\
                                font-weight:400;\
                                color:rgba(40,40,40,1);\
                                line-height:34px;\
                                opacity:0.97;\
                                 ");
     ui->checkBox->setStyleSheet("background-color: rgba();\
                                font-size:14px;\
                                font-weight:400;\
                                color:rgba(102,102,102,1);\
                                line-height:40px;\
                                opacity:0.91;");
     ui->pushButton->setStyleSheet(QString::fromUtf8("color:rgba(102,102,102,1);\n"
                                                 "line-height:24px;"));
     ui->pushButton_2->setStyleSheet(QString::fromUtf8("color:rgba(102,102,102,1);\n"
                                                 "line-height:24px;"));
}

void noteExitWindow::black_show()
{
    ui->widget->setStyleSheet("QWidget{background-color: rgba(0, 0, 0, 0.4);}");

    ui->label->setStyleSheet("background-color: rgba();\
                             font-size:20px;\
                                font-weight:400;\
                                color:rgba(255,255,255,1);\
                                line-height:34px;\
                                opacity:0.97;\
                                 ");
     ui->checkBox->setStyleSheet("background-color: rgba();\
                                 font-size:14px;\
                                 font-weight:400;\
                                 color:rgba(255,255,255,1);\
                                 line-height:40px;\
                                 opacity:0.91;");
     ui->pushButton->setStyleSheet(QString::fromUtf8("color:rgba(255,255,255,1);\n"
                                                      "line-height:24px;"));
     ui->pushButton_2->setStyleSheet(QString::fromUtf8("color:rgba(255,255,255,1);\n"
                                                      "line-height:24px;"));
}
