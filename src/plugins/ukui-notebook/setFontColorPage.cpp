/*
* Copyright (C) 2020 Tianjin KYLIN Information Technology Co., Ltd.
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

#include "setFontColorPage.h"
#include "ui_setFontColorPage.h"

SetFontColor::SetFontColor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetFontColor)
{
    ui->setupUi(this);

    initSetup();
}

SetFontColor::~SetFontColor()
{
    delete ui;
    //释放内存
    for (int i=0; i < 10;i++)
    {
        delete list_aItem[i];
    }
}

void SetFontColor::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
//    系统默认 255 、 248  深色模式 30 34
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);

    p.setBrush(opt.palette.color(QPalette::Base));
    //qDebug() << "paintEvent" << p.brush().color().value();
    //p.setOpacity(0.3);
    p.setOpacity(0.9);
    p.setPen(Qt::NoPen);

    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.drawRoundedRect(opt.rect,6,6);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SetFontColor::setColor()
{
    color[0]="background:rgba(76,119,231,1);";
    color[1]="background:rgba(250,108,99,1);";
    color[2]="background:rgba(15,161,90,1);";
    color[3]="background:rgba(255,151,47,1);";
    color[4]="background:rgba(186,123,216,1);";
    color[5]="background:rgba(248,209,93,1);";
    color[6]="background:rgba(42,162,217,1);";
    color[7]="background:rgba(110,207,67,1);";
    color[8]="background:rgba(144,101,255,1);";
//    color[9]="background:rgba(236,238,242,1);";

    //监听主题改变
    const QByteArray id(THEME_QT_SCHEMA);
    if(QGSettings::isSchemaInstalled(id)){
        QGSettings *styleSettings = new QGSettings(id, QByteArray(), this);
        QString style = styleSettings->get(MODE_QT_KEY).toString();
        if(style == "ukui-default" || style == "ukui-white"
                || style == "ukui-light" || style == "ukui"){
            color[9]="background:rgba(0,0,0,1);";
        }else if(style == "ukui-dark" || style == "ukui-black"){
            color[9]="background:rgba(255,255,255,1);";
        }
        connect(styleSettings, &QGSettings::changed, this, [=](const QString &key){
            if (key == "styleName"){
                QString currentTheme = styleSettings->get(MODE_QT_KEY).toString();
                if(currentTheme == "ukui-default" || currentTheme == "ukui-white"
                        || currentTheme == "ukui-light" || currentTheme == "ukui"){
                    color[9]="background:rgba(0,0,0,1);";
                    list_page[9]->ui->label->setStyleSheet(color[9]+"border-radius:3px;");
                }else if(currentTheme == "ukui-dark" || currentTheme == "ukui-black"){
                    color[9]="background:rgba(255,255,255,1);";
                    list_page[9]->ui->label->setStyleSheet(color[9]+"border-radius:3px;");
                }
            }
        });
    }
}

void SetFontColor::initSetup()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    setAttribute(Qt::WA_TranslucentBackground);
    setColor();

    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget->setSelectionMode(QAbstractItemView::NoSelection);

    for(int i=22; i<32 ; i++){
        int n = i-22;
        list_aItem[n] = new QListWidgetItem;
        list_aItem[n]->setSizeHint(QSize(30,27));

        ui->listWidget->addItem(list_aItem[n]);

        list_page[n] = new paletteButton(this);
        list_page[n]->resize(QSize(30,23));

        ui->listWidget->setItemWidget(list_aItem[n],list_page[n]);
        list_page[n]->ui->label->setStyleSheet(color[n]+"border-radius:3px;");
    }   
}
