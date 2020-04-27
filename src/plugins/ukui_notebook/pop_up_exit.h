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
#ifndef TANCHUANG_H
#define TANCHUANG_H

#include <QDialog>
#include <QPainter>

class Widget;
namespace Ui {
class tanchuang;
}
///class Notebook;
class Pop_ip_exit : public QDialog
{
    Q_OBJECT

public:
    explicit Pop_ip_exit(Widget* page,QWidget *parent=nullptr);
    ~Pop_ip_exit();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void color_clicked();

private:
    Ui::tanchuang *ui;

    void light_show();
    void black_show();

    Widget* pNotebook;


};

#endif // TANCHUANG_H
