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
#ifndef SINGLEITEMWIDGET_H
#define SINGLEITEMWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
namespace Ui {
class SingleItemWidget;
}

class SingleItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SingleItemWidget(QWidget *parent = nullptr);
    ~SingleItemWidget();
signals:
    void childDelEvent();

public:
    Ui::SingleItemWidget *ui;

private slots:
    void clickDelBtn();

private:
    void SingleItem_init();
    void SingleItem_conn();
};

#endif // SINGLEITEMWIDGET_H
