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
#ifndef CLOCK_PLUGIN_H
#define CLOCK_PLUGIN_H
#include <QPushButton>
#include <QMainWindow>
#include "sidebarSmallPluginInterface.h"

class clock_plugin : public QObject, public SidebarSmallPluginInterface
{

    Q_OBJECT
    //Q_INTERFACES宏用于告诉Qt该类实现的接口
    //Q_PLUGIN_METADATA宏用于描述插件元数据
    Q_PLUGIN_METADATA(IID SidebarSmallPluginInterface_iid FILE "Clock.json")
    Q_INTERFACES(SidebarSmallPluginInterface)

public:
    bool Clockflag = false;
    clock_plugin();
    ~clock_plugin();
    //plugin implement 统一接口
    const QString name() override {return QObject::tr("闹钟");}
    PluginType pluginType() override {return PluginType::SmallPlugin;}
    const QString description() override {return QObject::tr("闹钟插件");}
    const QIcon icon() override {return QIcon::fromTheme("alarm-clock", QIcon::fromTheme("alarm-clock"));}
    void setEnable(bool enable) override {Q_UNUSED(enable)}
    bool isEnable() override {return true;}

    virtual int PluginButtonLocation_X() override {return 0;}
    virtual int PluginButtonLocation_Y() override {return 2;}

    virtual QString PluginButtonName() override {return QObject::tr("闹钟");}
    virtual int     pluginsLoadingSequence() override {return 1;}

    virtual QString PluginIconName() override {return QObject::tr("闹钟");}
    virtual int PluginIconSize_W() override {return 48;}
    virtual int PluginIconSize_H()  override {return 48;}

    virtual void PluginsShowInterface() override;

    QWidget *m_pClock;
    QWidget*  centerWidget();
    void onNotification() ;

signals:
    void    Clock_ification();
};


#endif // CLOCK_PLUGIN_H
