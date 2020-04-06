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
#include <QDebug>
#include <QMouseEvent>
#include <QScrollBar>
#include "ukui_notebook.h"
#include "singleitemwidget.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QListWidgetItem>
#include <QTranslator>
#include "ui_ukui_notebook.h"
#include "ui_singleitemwidget.h"
#include "sql_create.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

signals:
    void listItemClicked(int);

public:
    QTranslator *translator;                        //国际化
    static bool ukui_sql_load();


private:
    Ui::Widget *ui;
    ukui_NoteBook *ukui_notebook;
    ukui_NoteBook *ukui_notebookOpen;
    QSqlTableModel *model;  //数据库
    QPoint m_lastPoint;//记录鼠标位置
    SingleItemWidget *s;
    QListWidgetItem *aItem;
    int index;
    int txtNum;
    int rowNum;
    QString ukui_textEdit;
    QString filename;
    QListWidgetItem *item[100];
    SingleItemWidget *singleItem[100];
    //QString fileContent;//读到的文件内容
    //QDateTime dateTime;

    void ukui_init();
    void ukui_conn();

    void ukui_sql_init();
    void ukui_addItem();
    //更新Item列表
    void ukui_updateItem();

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private slots:
    void exitSlot();
    void miniSlot();
    void editSlot();
    void newSlot();
    void listDoubleClickSlot();
    void listDelSingleSlot();
    void fileSavedSlot(QString data);
};

#endif // WIDGET_H
