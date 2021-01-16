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
#include "stopwatchItem.h"
#include<QApplication>
#include <QDebug>

stopwatch_item::stopwatch_item(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    this->setFixedSize(340, 58);
    stopwatch1 = new QLabel(this);//计次
    stopwatch1->move(24, 11);
    stopwatch1->setFixedSize(100, 17);
    stopwatch1->setText("计次");


    stopwatch2 = new QLabel( this);//间隔
    stopwatch2->move(24, 32);
    stopwatch2->setFixedSize(110, 17);
    stopwatch2->setText("工作日");
    stopwatch2->setVisible(true);

    stopwatch3 = new QLabel(this);//记次时间
    stopwatch3->move(173,13);
    stopwatch3->setFixedSize(145, 54);
    stopwatch3->setStyleSheet("font-size:24px;");
    stopwatch3->setAlignment(Qt::AlignRight);
    stopwatch3->setText("00:00");
    stopwatch3->setVisible(true);
    settingsStyle();
}

stopwatch_item::~stopwatch_item()
{
}

void stopwatch_item::setupUi(QWidget *stopwatch_item)
{
    if (stopwatch_item->objectName().isEmpty())
        stopwatch_item->setObjectName(QString::fromUtf8("stopwatch_item"));
    stopwatch_item->resize(340, 58);

    retranslateUi(stopwatch_item);

    QMetaObject::connectSlotsByName(stopwatch_item);
} // setupUi

void stopwatch_item::retranslateUi(QWidget *stopwatch_item)
{
    stopwatch_item->setWindowTitle(QApplication::translate("stopwatch_item", "Form", nullptr));
} // retranslateUi

/*
*监听主题
*/
void stopwatch_item::settingsStyle()
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

//黑色主题
void stopwatch_item::blackStyle()
{
    stopwatch1->setStyleSheet("color:rgba(255, 255, 255, 0.9);font-size:12px;");
    stopwatch2->setStyleSheet("font-size:12px;color:rgba(255, 255, 255, 0.55);");
    stopwatch3->setStyleSheet("color: rgba(255, 255, 255, 0.9)");
}
//白色主题
void stopwatch_item::whiteStyle()
{
    stopwatch1->setStyleSheet("color:rgba(49, 66, 89, 1);font-size:12px;");
    stopwatch2->setStyleSheet("font-size:12px;color:rgba(49, 66, 89, 0.5);");
    stopwatch3->setStyleSheet("color: rgba(49, 66, 89, 0.9)");
}
