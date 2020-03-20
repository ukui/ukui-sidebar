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
#ifndef UKUI_NOTEBOOK_H
#define UKUI_NOTEBOOK_H

#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QSettings>
#include <QFontDialog>
#include <QDateTime>
#include <QPainter>
#include <QPrinter>
#include <QMouseEvent>
#include <QTextEdit>
#include <QStyleOption>
namespace Ui {
class ukui_NoteBook;
}

class ukui_NoteBook : public QWidget
{
    Q_OBJECT

public:
    explicit ukui_NoteBook(QWidget *parent = nullptr);
    ~ukui_NoteBook();

signals:
    void listItemClicked(int);
    void fileSaved(QString);

public:
    QString fileName;//文件路径
    Ui::ukui_NoteBook *ui;
private slots:
    //新建文件
    void newFileSlot();
    //退出软件
    void exitFileSlot();
    //插入时间/日期
    void insertTimeDateSlot();
    //新建窗口
    void newWindowsSlot();
    //打开文件前的判断
    void openFileSlot();
    //保存文件
    void saveFileSlot();
    //文件另存为
    void saveFileAsSlot();
    //文本保存状态
    void textStatusSlot();

    //导出pdf
    void exportPdfSlot();
    //导出jpg/png
    void exportJpgSlot();
    //字体
    void fontChooseSlot();


private:
    //Ui::ukui_NoteBook *ui;
    ukui_NoteBook *notebook;

    QString fileContent;//读到的文件内容
    QSettings *setting;
    int index;
    QPoint m_lastPoint;//记录鼠标位置
    //保存文本到文件
    void saveTextToFile();
    //初始化
    void ukuiNoteBook_init();
    //关联槽函数
    void ukuiNoteBook_connect();
    //打开文件
    void realOpenFile();
    //保存文件
    void saveFile();
    //设置快捷键
    void ukui_setShortCut();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
};

#endif // UKUI_NOTEBOOK_H
