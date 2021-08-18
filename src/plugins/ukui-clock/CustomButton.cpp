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
#include "CustomButton.h"
#include <QDebug>

CustomButton::CustomButton(QWidget *parent,int width, int height, int status) : QPushButton(parent),m_width(width),m_height(height),position(0),Status(status)
{
    max = qMax(m_width,m_height);
    min = m_width>m_height?m_height:m_width;
    length = max - min;
    init(status);
}

//开
void CustomButton::openSlot()
{
    //滑动动画
    animation1 = new QPropertyAnimation(myLabel, "geometry");
    animation1->setDuration(100);
    animation1->setKeyValueAt(0, QRect(2, 2, 20, 20));
    animation1->setEndValue(QRect(31, 2, 20, 20));
    animation1->start();
    this->setStyleSheet(openBcack);
    myLabel->setStyleSheet(openbtn);
    Status = 1;
}

//关
void CustomButton::closeSlot()
{
    animation1 = new QPropertyAnimation(myLabel, "geometry");
    animation1->setDuration(100);
    animation1->setKeyValueAt(0, QRect(31, 2, 20, 20));
    animation1->setEndValue(QRect(2, 2, 20, 20));
    animation1->start();
    this->setStyleSheet(closeBcack);
    myLabel->setStyleSheet(closeBtn);
    Status = 0;
}

void CustomButton::colorUpdate()
{
    switch(Status)
    {
    case 0:
            this->setStyleSheet(closeBcack);
            myLabel->setStyleSheet(closeBtn);
        break;

    case 1:
            this->setStyleSheet(openBcack );
            myLabel->setStyleSheet(openbtn);
        break;
    }
}

void CustomButton::init(int status)
{
    this->resize(m_width,m_height);
    settingsStyle();
    myLabel = new QLabel(this);
    myLabel->setObjectName("myLabel");
    myLabel->resize(20,20);
    this->setStyleSheet(openBcack);
    myLabel->setStyleSheet(openbtn);
    this->setFixedSize(m_width,m_height);
}

void CustomButton::initClose()
{
    this->setStyleSheet(closeBcack);
    myLabel->setStyleSheet(closeBtn);
    Status = 0;
    myLabel->move(2,2);
}

void CustomButton::initOpen()
{
    Status = 1;
    myLabel->move(31,2);
    this->setStyleSheet(openBcack);
    myLabel->setStyleSheet(openbtn);
}

/*
*监听主题
*/
void CustomButton::settingsStyle()
{
    const QByteArray style_id(ORG_UKUI_STYLE);
    QStringList stylelist;
    QGSettings *style_settings = new QGSettings(style_id);

    stylelist<<STYLE_NAME_KEY_DARK<<STYLE_NAME_KEY_BLACK;
    if(QGSettings::isSchemaInstalled(style_id)){
        style_settings = new QGSettings(style_id);
        if(stylelist.contains(style_settings->get(STYLE_NAME).toString())){
            blackStyle();
        }else{
            whiteStyle();
        }
    }

    connect(style_settings, &QGSettings::changed, this, [=] (const QString &key){
        if(key==STYLE_NAME){
            if(stylelist.contains(style_settings->get(STYLE_NAME).toString())){
                blackStyle();
            }else{
                whiteStyle();
            }
            colorUpdate();
        }
    });
}

//黑色主题
void  CustomButton::blackStyle()
{
    closeBcack = QString("CustomButton{background-color:rgba(240, 247, 255, 0.2);border-radius:%1px;}").arg(min/2);
    closeBtn = QString("#myLabel{background-color:rgba(235, 244, 255, 0.55);border-radius:%1px}").arg(20/2);
    openBcack = QString("CustomButton{background-color:rgb(65, 128, 217);border-radius:%1px;}").arg(min/2);
    openbtn = QString("#myLabel{background-color:rgba(255, 255, 255, 0.88);border-radius:%1px}").arg(20/2);

}
//白色主题
void  CustomButton::whiteStyle()
{
     closeBcack = QString("CustomButton{background-color:rgba(180, 195, 212, 1);border-radius:%1px;}").arg(min/2);
     closeBtn = QString("#myLabel{background-color: rgb(240, 245, 250);border-radius:%1px}").arg(20/2);
     openBcack = QString("CustomButton{background-color:rgba(65, 128, 217, 1);border-radius:%1px;}").arg(min/2);
     openbtn = QString("#myLabel{background-color: /*lightgrey*/rgba(255, 255, 255, 0.88);border-radius:%1px}").arg(20/2);
}
