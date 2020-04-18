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

feedback_plugin::feedback_plugin()
{
    QString locale = QLocale::system().name();
    translator_feedback = new QTranslator();
    //英文环境加载en.qm
    if(locale == "en_US"){
        translator_feedback->load(QString("://translation/feedback_en_US.qm"));  //选择翻译文件
        QApplication::installTranslator(translator_feedback);
    }
}

void feedback_plugin::onNotification() {
    qDebug()<< "onNotification";
}

void feedback_plugin::PluginsShowInterface() {
    if (!mp_feedback) {
        mp_feedback = new feedback ;
    }
    (static_cast<feedback*>(mp_feedback))->feedback_info_init();
    QDesktopWidget *desk = QApplication::desktop();
    QRect deskRect = desk->availableGeometry();
    mp_feedback->show();
    window_is_close_flag=false;
    mp_feedback->showNormal();
    mp_feedback->move((deskRect.width()-mp_feedback->width())/2, (deskRect.height()-mp_feedback->height())/2);
}

feedback_plugin::~feedback_plugin() {
    if( mp_feedback)
    {
        delete mp_feedback;
    }
    mp_feedback = nullptr;

    delete translator_feedback;

}

QWidget* feedback_plugin::centerWidget()
{
    return  mp_feedback;

}
