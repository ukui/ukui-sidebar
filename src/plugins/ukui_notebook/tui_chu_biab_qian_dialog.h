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
#ifndef TUI_CHU_BIAB_QIAN_DIALOG_H
#define TUI_CHU_BIAB_QIAN_DIALOG_H

#include <QDialog>

namespace Ui {
class tui_chu_biab_qian_Dialog;
}

class tui_chu_biab_qian_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit tui_chu_biab_qian_Dialog(QWidget *parent = nullptr);
    ~tui_chu_biab_qian_Dialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::tui_chu_biab_qian_Dialog *ui;
};

#endif // TUI_CHU_BIAB_QIAN_DIALOG_H
