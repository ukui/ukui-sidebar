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
#include <QSqlError>
#include <QListWidgetItem>
#include <QDesktopWidget>
#include <iostream>
#include <QTranslator>
#include <QStandardPaths>
#include "ui_ukui_notebook.h"
#include "ui_singleitemwidget.h"
#include "mythrow.h"

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
    QTranslator *translator;                        //国际化
    void error_throw();                             //异常处理抛出

private:
    Ui::Widget *ui;                                 //主ui
    ukui_NoteBook *ukui_notebook;                   //笔记本类指针
    QString sqlFilePath;                            //数据库文件存储地址
    QSqlDatabase sqlDb;                             //数据库连接
    QSqlTableModel *sqlModel;                       //数据库模型
    QPoint m_lastPoint;                             //记录鼠标位置
    SingleItemWidget *s;                            //item listwidget窗体组合
    QListWidgetItem *aItem;                         //item指针
    int index;                                      //鼠标位置标记
    int txtNum;
    int rowNum;
    QString ukui_textEdit;                          //文本编辑区内容
    QString filename;                               //获取到的保存文件的 路径+文件名
    QString modifyTime;                             //文件最后修改时间

    QListWidgetItem *item[100];
    SingleItemWidget *singleItem[100];
    //QString fileContent;//读到的文件内容

    void ukui_init();                               //加载界面组件
    void ukui_conn();                               //绑定槽函数

    void sqlInit();                                 //加载数据库
    void sqlAddItem();                              //插入数据库，同步插入item
    void sqlUpdateItem();                           //同步数据库，同步更新item

    void getFileModifyTime(QString fileInfo);       //获取文件创建时间、修改时间
    void mouseMoveEvent(QMouseEvent *event);        //重写鼠标移动事件
    void mousePressEvent(QMouseEvent *event);       //重写鼠标按下事件
    //void paintEvent(QPaintEvent *);


private slots:
    void exitSlot();                                //关闭按钮槽函数
    void miniSlot();                                //最小化按钮槽函数
    void editSlot();                                //编辑按钮槽函数
    void newSlot();                                 //新建按钮槽函数
    void listClickSlot();                           //item点击事件槽函数
    void listDoubleClickSlot();                     //item双击事件槽函数
    void listDelSingleSlot();                       //item删除按钮槽函数
    void fileSavedSlot(QString data);               //文件已保存槽函数
};

#endif // WIDGET_H
