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
#include "feedback_plugin.h"
#include "feedback.h"
#include <QWidget>
#include <QDesktopWidget>
#include <QApplication>
#include <QTranslator>

feedback_plugin::feedback_plugin()
{
    QString locale = QLocale::system().name();
    QTranslator *translator_feedback;
    translator_feedback = new QTranslator();
    //英文环境加载en.qm
    if(locale == "en_US"){
        translator_feedback->load(QString(":/Resource/feedback_en.qm"));  //选择翻译文件
        QApplication::installTranslator(translator_feedback);
    }
      mp_feedback = new feedback ;
      FeedBackFlag = false;

}

void feedback_plugin::onNotification() {
    qDebug()<< "onNotification";
}

void feedback_plugin::PluginsShowInterface() {
    if (FeedBackFlag) {
        mp_feedback = new feedback ;
    }
    QDesktopWidget *desk = QApplication::desktop();
    QRect deskRect = desk->availableGeometry();
    mp_feedback->show();
    mp_feedback->move((deskRect.width()-mp_feedback->width())/2, (deskRect.height()-mp_feedback->height())/2);
    FeedBackFlag = true;
}

feedback_plugin::~feedback_plugin() {
    if( mp_feedback)
    {
        delete mp_feedback;
    }
    mp_feedback = nullptr;
}

QWidget* feedback_plugin::centerWidget()
{
    return  mp_feedback;

}
