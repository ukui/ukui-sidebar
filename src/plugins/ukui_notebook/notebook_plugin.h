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
#ifndef NOTEBOOK_PLUGIN_H
#define NOTEBOOK_PLUGIN_H
#include <ukui-noodbook_pluginiface.h>

#include <QWidget>
class notebook_plugin : public QObject, public nood_bookInterface
{
public:
    notebook_plugin();


    Q_OBJECT
    //Q_INTERFACES宏用于告诉Qt该类实现的接口
    Q_INTERFACES(nood_bookInterface)
    //Q_PLUGIN_METADATA宏用于描述插件元数据
    Q_PLUGIN_METADATA(IID NotebookInterface_iid FILE "notebook.json")
    //申明该类有D-BUS服务接口
    //Q_CLASSINFO("D-Bus Interface", "com.scorpio.test.value")
    bool NoteBookFlag;

    ~notebook_plugin();
    void show();

    QWidget*  mp_notebook;
    QWidget*  centerWidget();
    void onNotification() ;
   // void UI_in_sidebar();

signals:
    void    notebook_ification();

};

#endif // NOTEBOOK_PLAGIN_H
