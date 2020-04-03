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
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
class MessageBox : public QWidget
{
  Q_OBJECT

public:
  MessageBox(QWidget* parent = 0 , double TOTAL_TIME = 0 );
  ~MessageBox();
  QTimer*      timer_countdown;
  double       TOTAL_TIME = 10.0;

private:
  QPushButton* btn;
  QMessageBox* msgbox;
  QPushButton* okbtn;
  double       msgbox_time_;
public slots:
  void count_time();
  void btnclick();
};
#endif // WIDGET_H
