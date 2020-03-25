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
#include <QDesktopWidget>
#include <iostream>
#include <QTranslator>
#include "ui_ukui_notebook.h"
#include "ui_singleitemwidget.h"
#include "sql_create.h"
//#include "mythrow.h"

#define     Button_tristate(className,imageUrl)     (#className"{border-image:url("#imageUrl")}"  \
                                              #className":houver{border-image:url("#imageUrl"-houver)}"  \
                                              #className":pressed{border-image:url("#imageUrl"-pressed)}")

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
//    void error_throw();
    QTranslator *translator;

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
    QString modifyTime;
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
    //获取文件创建时间、修改时间
    void getFileModifyTime(QString fileInfo);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    //void paintEvent(QPaintEvent *);


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
