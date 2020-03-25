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

#include "sidebarSmallPluginInterface.h"

#include <QWidget>
class notebook_plugin : public QObject, public SidebarSmallPluginInterface
{
    Q_OBJECT
    //Q_INTERFACES宏用于告诉Qt该类实现的接口
    Q_INTERFACES(SidebarSmallPluginInterface)
    //Q_PLUGIN_METADATA宏用于描述插件元数据
    Q_PLUGIN_METADATA(IID SidebarSmallPluginInterface_iid FILE "notebook.json")

public:
    bool Notebookflag = false;
    notebook_plugin();
    ~notebook_plugin();

    //plugin implement 统一接口
    const QString name() override {return QObject::tr("NoteBook");}
    PluginType pluginType() override {return PluginType::SmallPlugin;}
    const QString description() override {return QObject::tr("Open a notebook");}
    const QIcon icon() override {return QIcon::fromTheme("notebook", QIcon::fromTheme("noteBook",QIcon(":/new/prefix1/SVG/kylin-notebook.svg")));}
    void setEnable(bool enable) override {Q_UNUSED(enable)}
    bool isEnable() override {return true;}

    virtual int PluginButtonLocation_X() override {return 0;}
    virtual int PluginButtonLocation_Y() override {return 3;}

    virtual QString PluginButtonName() override {return QObject::tr("NoteBook");}
    virtual int pluginsLoadingSequence() override {return 2;}

    virtual QString PluginIconName() override {return QObject::tr("NoteBook");}
    virtual int PluginIconSize_W() override {return 48;}
    virtual int PluginIconSize_H()  override {return 48;}

    virtual void PluginsShowInterface() override;

    QWidget*  mp_notebook;
    QWidget*  centerWidget();
    void onNotification() ;

signals:
    void    notebook_ification();

};

#endif // NOTEBOOK_PLAGIN_H
