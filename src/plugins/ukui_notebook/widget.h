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
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlError>
#include <QListWidgetItem>
#include <QDesktopWidget>
#include <iostream>
#include <QTranslator>
#include <QStandardPaths>
//#include <QStringLiteral>
#include <QPushButton>
#include <QSettings>
#include <QThread>
#include <QSortFilterProxyModel>
#include <QTimer>
#include <QLabel>
#include <QProgressDialog>
#include <QFutureWatcher>
#include <QtConcurrent>
#include <QCheckBox>
#include <QBitmap>
#include <vector>
#include <QTableView>

#include "mythrow.h"
#include "noteview.h"
#include "noteTable.h"
#include "notedata.h"
#include "notemodel.h"
#include "dbmanager.h"
#include "edit_page.h"
#include "noteExitWindow.h"
#include "ui_edit_page.h"

extern int sink;

#define     tristateButton(className,imageUrl)     (""#className"{image:url("#imageUrl".svg);}   \
    "#className":hover{image:url("#imageUrl"-hover.svg);}  \
    "#className":pressed{image:url("#imageUrl"-click.svg);}")


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    Ui::Widget *ui;                                                 //主ui
    std::vector<Edit_page*> m_editors;                              //c++数组容器
    QTranslator *translator;                                        //国际化

    int m_isThemeChanged;                                           //主题
    void error_throw();                                             //异常处理抛出

private:
    Edit_page *m_notebook;                                          //新建便签指针

    QPixmap pixmap1;
    QPixmap pixmap2;
    QPixmap pixmap3;
    QPixmap pixmap4;
    QPixmap pixmap5;
    QPixmap pixmap6;
    QPixmap pixmap7;
    QPixmap pixmap8;
    QPixmap pixmap9;
    QPixmap pixmap10;
    QPixmap pixmap11;
    QPixmap pixmap12;
    QPixmap pixmap13;
    QPixmap pixmap14;
    QPixmap pixmap15;
    QPixmap pixmap16;

    int listflag;                                                   //平铺/展开列表切换
    int sortflag;                                                   //升降序切换
    noteExitWindow* m_noteExitWindow=nullptr;                       //退出弹窗
    QAction *searchAction;                                          //搜索栏图标
    QAction *delAction;                                             //搜索栏删除图标
    QTimer* m_autoSaveTimer;                                        //自动保存定时器
    QSettings* m_settingsDatabase;                                  //配置文件
    QLineEdit* m_ukui_SearchLine;                                   //搜索栏
    QPushButton* m_newKynote;                                       //新建按钮
    QPushButton* m_trashButton;                                     //删除按钮
    QLabel* m_countLabel;                                           //item记数
    QPushButton* m_sortLabel;                                       //升/降序按钮
    QPushButton* m_changePage;                                      //列表/平铺切换按钮
    NoteView* m_noteView;                                           //listview
    QTableView* m_noteTable;                                        //tableview
    NoteModel* m_noteModel;                                         //便签模板
    NoteModel* m_deletedNotesModel;                                 //删除模板
    QSortFilterProxyModel* m_proxyModel;                            //对项目进行排序，过滤
    QModelIndex m_currentSelectedNoteProxy;                         //当前列表
    QModelIndex m_tmpIndex;                                         //编辑时临时列表
    QModelIndex m_tmpColorIndex;                                    //调色板临时列表
    QQueue<QString> m_searchQueue;                                  //搜索队列
    DBManager* m_dbManager;                                         //数据库
    QThread* m_dbThread;                                            //数据库线程

    int m_noteCounter;                                              //便签总数
    int m_trashCounter;                                             //废纸篓总数
    bool m_isContentModified;                                       //便签内容是否修改
    bool m_isColorModified;                                         //便签颜色是否修改
    bool m_isOperationRunning;



    void kyNoteInit();                                              //加载界面组件
    void kyNoteConn();                                              //绑定槽函数
    void initListModel();                                           //初始化列表
    void initTableModel();                                          //初始化表格
    void black_show();                                              //黑色主题
    void light_show();                                              //白色主题
    void set_all_btn_attribute();                                   //初始化按钮
    void searchInit();                                              //初始化搜索栏
    void createNewNote();                                           //新建便签
    void deleteNote(const QModelIndex& noteIndex, bool isFromUser=true);//删除便签
    void deleteSelectedNote();                                      //获取选中便签/列表
    void setupDatabases();                                          //配置数据库
    void initializeSettingsDatabase();                              //初始化配置文件
    void createNewNoteIfEmpty();                                    //初始时创建一个便签
    void setupModelView();                                          //代理列表模板
    void setupTableView();                                          //代理表格模板
    void saveNoteToDB(const QModelIndex& noteIndex);                //保存到数据库
    NoteData* generateNote(const int noteID);                       //新建便签时初始化
    QString getFirstLine(const QString& str);                       //获取文本内容第一行
    QString getNoteDateEditor (QString dateEdited);                 //获取时间
    QDateTime getQDateTime(QString date);                           //获取日期
    void showNoteInEditor(const QModelIndex& noteIndex);            //加载便签页内容
    void selectFirstNote();                                         //选中列表头便签
    void moveNoteToTop();                                           //移动便签到列表头
    void clearSearch();                                             //清空搜索栏
    void findNotesContain(const QString &keyword);                  //过滤字符串
    void selectNote(const QModelIndex& noteIndex);                  //双击前选中目标列表
    void checkMigration();                                          //迁移sync
    void migrateNote(QString notePath);                             //便签数据迁移



private slots:
    void InitData();                                                //初始化加载第一个便签
    void loadNotes(QList<NoteData *> noteList, int noteCounter);    //加载便签列表
    void exitSlot();                                                //关闭按钮槽函数
    void miniSlot();                                                //最小化按钮槽函数
    void editSlot();                                                //编辑按钮槽函数
    void newSlot();                                                 //新建按钮槽函数
    void listClickSlot(const QModelIndex &index);                   //item单击事件槽函数
    void listDoubleClickSlot(const QModelIndex &);                  //item双击事件槽函数
    void onTextEditTextChanged(int noteId, int i);                  //文本改变槽函数
    void onColorChanged(const QColor &color, int noteId);           //便签颜色改变槽函数
    void onTrashButtonClicked();                                    //删除槽函数
    void onSearchEditTextChanged(const QString& keyword);           //搜索栏文本改变槽函数
    void sortSlot();                                                //升/降序槽函数
    void changePageSlot();                                          //列表平铺切换槽函数
    void on_sort_2_btn_clicked();                                   //主题切换槽函数
    void delAction_del_SearchLine();                                //搜索清空按钮槽函数
    void on_SearchLine_textChanged(const QString &arg1);            //搜索栏图标显示
    void setNoteNullSlot();                                         //便签页关闭置空槽函数

signals:
    void requestNotesList();                                        //加载列表请求信号
    void requestOpenDBManager(QString path, bool doCreate);         //打开数据库信号
    void requestCreateUpdateNote(NoteData* note);                   //数据库更新信号
    void requestDeleteNote(NoteData* note);                         //数据库同步删除信号
    void requestRestoreNotes(QList<NoteData *> noteList);           //重加载信号
    void requestImportNotes(QList<NoteData *> noteList);            //导入信号
    void requestExportNotes(QString fileName);                      //导出信号
    void requestMigrateNotes(QList<NoteData *> noteList);           //迁移信号
    void requestMigrateTrash(QList<NoteData *> noteList);           //迁移废纸篓信号
    void requestForceLastRowIndexValue(int index);                  //请求返回受结果的SQL语句影响的行数信号
};

#endif // WIDGET_H
