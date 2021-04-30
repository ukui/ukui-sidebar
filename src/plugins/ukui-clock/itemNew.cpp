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
#include "itemNew.h"
#include<QApplication>
#include <QDebug>
#include <QFontDatabase>

item_new::item_new(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    this->setFixedSize(340, 108);

    alarmLabel_w0 = new QLabel(this);//闹钟用途//Alarm function
    alarmLabel_w0->move(27  ,6);
    alarmLabel_w0->setFixedSize(200, 25);
    alarmLabel_w0->setText("闹钟");

    alarmLabel_s0 = new QLabel( this);//闹钟重复//Repetition of alarm clock
    alarmLabel_s0->move(27, 74);
    alarmLabel_s0->setFixedSize(270, 17);
    alarmLabel_s0->setText("工作日");
    alarmLabel_s0->setVisible(true);

    alarmLabel0 = new QLabel(this);//闹钟//Alarm clock
    alarmLabel0->move(25,24);
    alarmLabel0->setFixedSize(125, 56);
    alarmLabel0->setText("00:00");
    alarmLabel0->setVisible(true);
    alarmLabel0->show();

    alarmLabel1 = new QLabel(this);//上下午//Last afternoon
    alarmLabel1->move(155,22);
    alarmLabel1->setFixedSize(31, 56);
    alarmLabel1->setStyleSheet("font: 10pt;background-color: rgb();");
    alarmLabel1->setText("上午");
    alarmLabel1->setVisible(true);

    alarm_on_off0 = new CustomButton(this,54,24,1);//闹钟开关// Alarm switch
    alarm_on_off0->move(263,43);
    alarm_on_off0->setFlat(true);
    alarm_on_off0->setVisible(true);
    alarm_on_off0->myLabel->move(32,1);
    settingsStyle();
}

item_new::~item_new()
{

}

void item_new::setupUi(QWidget *item_new)
{
    if (item_new->objectName().isEmpty())
        item_new->setObjectName(QString::fromUtf8("item_new"));
    item_new->resize(376, 56);
    item_new->setStyleSheet(QString::fromUtf8("border-radius:12px;\n"
                                              ""));
    retranslateUi(item_new);

    QMetaObject::connectSlotsByName(item_new);
} // setupUi

void item_new::retranslateUi(QWidget *item_new)
{
    item_new->setWindowTitle(QApplication::translate("item_new", "Form", nullptr));
} // retranslateUi

/*
*监听主题
*/
void item_new::settingsStyle()
{
    const QByteArray style_id(ORG_UKUI_STYLE);
    QStringList stylelist;
    QGSettings *style_settings = new QGSettings(style_id);

    stylelist<<STYLE_NAME_KEY_DARK<<STYLE_NAME_KEY_BLACK; //<<STYLE_NAME_KEY_DEFAULT;
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
        }
    });
}

//强制字体
QString item_new::loadFontFamilyFromTTF()
{
    static QString font;
    static bool loaded = false;
    if(!loaded)
    {
        loaded = true;
        int loadedFontID = QFontDatabase::addApplicationFont(":/image/DFPKingGothicGB-Semibold-2.ttf");
        QStringList loadedFontFamilies = QFontDatabase::applicationFontFamilies(loadedFontID);
        if(!loadedFontFamilies.empty())
            font = loadedFontFamilies.at(0);
    }
    return font;
}

//黑色主题
void item_new::blackStyle()
{
    alarmLabel_w0->setStyleSheet("color:rgba(255,255,255,0.6);font-size:12px;"); //名字
    alarmLabel0->setStyleSheet("font-size:30px;");//时间
    alarmLabel_s0->setStyleSheet("font-size:14px;color:rgba(255,255,255,0.94);font-size:12px;");//重复
}
//白色主题
void item_new::whiteStyle()
{
    alarmLabel_w0->setStyleSheet("color:rgba(0,0,0,0.5);font-size:12px;"); //名字
    alarmLabel0->setStyleSheet("font-size:30px;");//时间
    alarmLabel_s0->setStyleSheet("font-size:14px;color:rgba(0,0,0,0.8);font-size:12px;");//重复
}
