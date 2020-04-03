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
#include "messagebox.h"
#define INTERVAL 0.1
MessageBox::MessageBox(QWidget* parent, double TIME ):
    TOTAL_TIME(TIME),
    QWidget(parent)
{
  msgbox = new QMessageBox(parent);
  msgbox->setGeometry(QRect(200, 150, 400, 300));
  okbtn     = new QPushButton("立即关闭");
  msgbox->addButton(okbtn, QMessageBox::AcceptRole);
  msgbox->setStyleSheet("QPushButton {min-width: 5em; min-height: 2em;}");
  msgbox->setWindowTitle(tr("时间到"));
  okbtn->setFixedSize(180,45);
  timer_countdown = new QTimer(this);
  connect(timer_countdown, SIGNAL(timeout()), this, SLOT(count_time()));
  btnclick();
}

MessageBox::~MessageBox()
{
}

void MessageBox::count_time()
{
  double letf_time = TOTAL_TIME - msgbox_time_;
  if( letf_time <= 0 )
  {
    okbtn->click();
    return;
  }
  else
  {
    QString output;
    output.sprintf("%2.1f秒 后关闭音乐 ", letf_time);
    msgbox->setText(output);
  }
  msgbox_time_ += INTERVAL;
}

void MessageBox::btnclick()
{
  timer_countdown->start(INTERVAL*1000);
  msgbox_time_ = 0.0;
  msgbox->exec();
  if (msgbox->clickedButton() == okbtn)
  {
    timer_countdown->stop();
  }
  else
  {
    timer_countdown->stop();
  }
}
