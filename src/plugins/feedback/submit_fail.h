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
#ifndef SUBMIT_FAIL_H
#define SUBMIT_FAIL_H

#include <QDialog>

namespace Ui {
class submit_fail;
}

class submit_fail : public QDialog
{
    Q_OBJECT

public:
    explicit submit_fail(QWidget *parent = nullptr);
    ~submit_fail();

    void show_faillinfo(int errorcode);

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::submit_fail *ui;
};

#endif // SUBMIT_FAIL_H
