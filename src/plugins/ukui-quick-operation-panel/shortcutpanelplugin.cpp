/*
* Copyright (C) 2020 Tianjin KYLIN Information Technology Co., Ltd.
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
#include "shortcutpanelplugin.h"

shortcutPanelPlugin::shortcutPanelPlugin(QObject *parent)
{
    Q_UNUSED(parent);
    initMemberVariables();      // 初始化插件成员变量
    initShortButtonWidget();    // 初始化8个快捷按钮界面
    setButtonIcon();            // 设置按钮图标
    initsetShortWidget();       // 布局快捷按钮界面
    setWidget();                // 将切换按钮和ListView界面set进插件主界面
}

/* 初始化插件成员变量 */
void shortcutPanelPlugin::initMemberVariables()
{
    m_pMainVLayout = new QVBoxLayout;
    m_pMainVLayout->setContentsMargins(0, 0, 0, 0);
    m_pMainVLayout->setSpacing(0);

    m_pButtonHLaout = new QHBoxLayout;
    m_pButtonHLaout->setContentsMargins(0, 0, 0, 0);
    m_pButtonHLaout->setSpacing(0);

    m_pShortGtoplayout = new QHBoxLayout;//快捷操作面板上半部分布局
    m_pShortGtoplayout->setContentsMargins(0, 0, 0, 0);
    m_pShortGtoplayout->setSpacing(0);


    m_pShortGLayout = new QHBoxLayout;//快捷操作面板下半部分布局
    m_pShortGLayout->setContentsMargins(0, 0, 0, 0);
    m_pShortGLayout->setSpacing(0);


    m_pShortAssembly =new QGridLayout; //左边组件的布局
    m_pShortAssembly->setContentsMargins(18, 0, 0, 0); //左上右下
    m_pShortAssembly->setHorizontalSpacing(25); //控件间隔
    m_pShortAssembly->setVerticalSpacing(0);//垂直间距


    m_pScrollingArea =new QHBoxLayout;//右边组件的布局
    m_pScrollingArea->setContentsMargins(0, 0, 0, 0);
    m_pScrollingArea->setSpacing(0);


    m_pMainWidget  = new MainWidget;
    m_pMainWidget->setContentsMargins(0, 0, 0, 0);
    m_pMainWidget->setFixedSize(392, 486);
    m_pButtonWidget = new QWidget;
    m_pButtonWidget->setContentsMargins(0, 0, 0, 0);
    m_pButtonWidget->setFixedHeight(15);

    /* 账户信息界面 */
    m_PAccountInfoWidget = new AccountInformation();
    m_PAccountInfoWidget->setFixedSize(392, 48);

    /* 快捷操作面板界面 */
    m_pShortWidget   = new QWidget;
    m_pShortWidget->setFixedSize(380, 266);
    m_pShortWidget->setContentsMargins(0, 0, 0, 0);

    /* 调整音量与屏幕亮度界面 */
    m_pScrollingAreaWidget = new ScrollingAreaWidget();
    m_pScrollingAreaWidget->setFixedSize(150, 200);

    /* 显示天气界面 */
    m_pWeatherWidget = new weatherWidget();
    m_pWeatherWidget->setFixedSize(392, 20);

    /* WIFI与蓝牙界面 */
    m_pWIFIBluetooth = new QWidget;
    m_pWIFIBluetooth->setFixedSize(380, 56);

    m_SpreadButtonIconList << SPREAD_BUTTON_NORMAL << SPREAD_BUTTON_HOVER << SPREAD_BUTTON_PRESS;
    m_FoldButtonIconList   << FOLD_BUTTON_NORMAL   << FOLD_BUTTON_HOVER   << FOLD_BUTTON_PRESS;

    m_SpreadButtonIconNameList << SPREAD_BUTTON_NORMAL_NAME << SPREAD_BUTTON_HOVER_NAME << SPREAD_BUTTON_PRESS_NAME;
    m_FoldButtonIconNameList   << FOLD_BUTTON_NORMAL_NAME << FOLD_BUTTON_HOVER_NAME << FOLD_BUTTON_PRESS_NAME;

    m_pSpreadButton  = new PushButton(m_SpreadButtonIconList, m_SpreadButtonIconNameList);
    connect(m_pSpreadButton, &QPushButton::clicked, this, &shortcutPanelPlugin::spreadClikedSlots);
    m_pSpreadButton->setFixedSize(45, 15);

    m_pfoldButton = new PushButton(m_FoldButtonIconList, m_FoldButtonIconNameList);
    connect(m_pfoldButton, &QPushButton::clicked, this, &shortcutPanelPlugin::foldClikedSlots);
    m_pfoldButton->setFixedSize(45, 15);
    return;
}

/* 初始化8个快捷按钮界面 */
void shortcutPanelPlugin::initShortButtonWidget()
{
    /* 清空链表中的数据，初始化 */
    ShortButtonWidgetList.clear();

    /* 勿扰模式 */
    m_pnodisturbWidget = new nodisturbWidget();
    ShortButtonWidgetList.append(m_pnodisturbWidget);

    /* 自动旋转功能 */
    m_pAutomaticRotationWidget = new AutomaticRotationWidget();
    ShortButtonWidgetList.append(m_pAutomaticRotationWidget);

    /* 平板模式 */
    m_ppadWidget       = new padWidget();
    ShortButtonWidgetList.append(m_ppadWidget);


    /* 控制面板*/
    m_psettingWidget = new settingWidget();
    ShortButtonWidgetList.append(m_psettingWidget);


    /* 热点 */
    m_photspotWidget = new hotspotWidget();
    ShortButtonWidgetList.append(m_photspotWidget);

    /* 计算器 */
    m_pcalculatorWidget = new calculatorWidget();
    ShortButtonWidgetList.append(m_pcalculatorWidget);

    /* 截图 */
    m_pscreenshotWidget = new screenshotWidget();
    ShortButtonWidgetList.append(m_pscreenshotWidget);



    /* Wifi */
    m_pWifiWidget = new WifiWidget();
    ShortButtonWidgetList.append(m_pWifiWidget);

    /* 蓝牙 */
    m_pBluetoothWidgetModify = new ModifybluetoothWidget();
    ShortButtonWidgetList.append(m_pBluetoothWidgetModify);

    qDebug() << "12312312312312312312312" << ShortButtonWidgetList.count();
    return;
}

/* 布局8个快捷方式的按钮, 初始化 */
void shortcutPanelPlugin::initsetShortWidget()
{
    if (true && true) {
        m_pShortAssembly->addWidget(ShortButtonWidgetList.at(0), 0, 0, 1, 1);
    }
    if (true && true) {
        m_pShortAssembly->addWidget(ShortButtonWidgetList.at(1), 0, 1, 1, 1);
    }
    if (true && true) {
        m_pShortAssembly->addWidget(ShortButtonWidgetList.at(2), 1, 0, 1, 1);
    }
    if (true && true) {
        m_pShortAssembly->addWidget(ShortButtonWidgetList.at(3), 1, 1, 1, 1);
    }
    if (true && true) {
        m_pShortAssembly->addWidget(ShortButtonWidgetList.at(4), 2, 0, 1, 1);
    }
    if (true && true) {
        m_pShortAssembly->addWidget(ShortButtonWidgetList.at(5), 2, 1, 1, 1);
    }
    if (true && true) {
        //m_pShortGLayoutL->addWidget(ShortButtonWidgetList.at(6), 3, 2, 1, 1);
    }
    if (true && true) {
        m_pScrollingArea->addWidget(m_pScrollingAreaWidget);
    }
    if (true&&true) {

         m_pShortGtoplayout->addItem(new QSpacerItem(32, 10));
         m_pShortGtoplayout->addWidget(ShortButtonWidgetList.at(7));
         m_pShortGtoplayout->addItem(new QSpacerItem(32, 10));
         m_pShortGtoplayout->addWidget(ShortButtonWidgetList.at(8));
         m_pShortGtoplayout->addItem(new QSpacerItem(32, 10));
    }
    return;
}

/* 当收到控制面板发出的gsetting信号值变化时，重新布局按钮界面 */
void shortcutPanelPlugin::resetShortWidget()
{
    if (true && true) {
        m_pShortAssembly->addWidget(ShortButtonWidgetList.at(0), 0, 0, 1, 1);
    }
    if (true && true) {
        m_pShortAssembly->addWidget(ShortButtonWidgetList.at(1), 0, 1, 1, 1);
    }
    if (true && true) {
        m_pShortAssembly->addWidget(ShortButtonWidgetList.at(2), 0, 2, 1, 1);
    }
    if (true && true) {
        m_pShortAssembly->addWidget(ShortButtonWidgetList.at(3), 0, 3, 1, 1);
    }
    if (true && true) {
        m_pShortAssembly->addWidget(ShortButtonWidgetList.at(4), 1, 0, 1, 1);
    }
    if (true && true) {
        m_pShortAssembly->addWidget(ShortButtonWidgetList.at(5), 1, 1, 1, 1);
    }
    if (true && true) {
       // m_pShortGLayout->addWidget(ShortButtonWidgetList.at(6), 1, 2, 1, 1);
    }
    if (true && true) {
       m_pScrollingArea->addWidget(m_pScrollingAreaWidget);
    }
//    if (true&&true) {
//        m_pShortGLayout->addWidget(ShortButtonWidgetList.at(8), 2, 0, 1, 1);
//    }
    return;
}

/* 设置按钮图标 */
void shortcutPanelPlugin::setButtonIcon()
{
    /* 设置展开按钮悬浮和点击状态按钮图片 */
    m_pSpreadButton->setIcon(QIcon(":/image/open-normal.svg"));

    /* 设置折叠按钮悬浮和点击状态按钮图片 */
    m_pfoldButton->setIcon(QIcon(":/image/fold-normal.svg"));
    return;
}

/* 将切换按钮和ListView界面set进插件主界面 */
void shortcutPanelPlugin::setWidget()
{
    m_pButtonHLaout->addItem(new QSpacerItem(20, 173));
    m_pButtonHLaout->addWidget(m_pSpreadButton);
    m_pButtonHLaout->addWidget(m_pfoldButton);
    m_pShortGLayout->addLayout(m_pShortAssembly);
    m_pShortGLayout->addLayout(m_pScrollingArea);

    m_pButtonWidget->setLayout(m_pButtonHLaout);
    m_pSpreadButton->setVisible(false);

   // m_pShortGtoplayout
    m_pWIFIBluetooth->setLayout(m_pShortGtoplayout);


    m_pShortWidget->setLayout(m_pShortGLayout);
    m_pMainVLayout->addWidget(m_pButtonWidget);
    m_pMainVLayout->addWidget(m_PAccountInfoWidget);
    m_pMainVLayout->addWidget(m_pWIFIBluetooth);
    m_pMainVLayout->addWidget(m_pShortWidget);
    m_pMainVLayout->addWidget(m_pWeatherWidget);
    m_pMainWidget->setLayout(m_pMainVLayout);
    return;
}

/* 获取快捷操作面板界面 */
QWidget* shortcutPanelPlugin::getShortCutPanelWidget()
{
    if (m_pMainWidget == nullptr) {
        return nullptr;
    }
    return m_pMainWidget;
}

/* 获取接口代号 */
InterfaceEnum shortcutPanelPlugin::getInterfaceMark(QString key)
{

    if ("" == key) {
        qDebug() << "获取接口代号失败， 传入参数有误";
        return InterfaceEnum::Else;
    }
    if (m_InterfaceHash.contains(key)) {
        return m_InterfaceHash.value(key);
    } else
        return InterfaceEnum::Else;
}

/* 移除Hash中接口 */
void shortcutPanelPlugin::removeInterfaceMark(QString key)
{
    if ("" == key) {
        qDebug() << "移除Hash中接口失败， 传入参数有误";
        return;
    }
    if (m_InterfaceHash.contains(key))
        m_InterfaceHash.remove(key);
    return;
}

/* 插入接口和代号往Hash表中 */
void shortcutPanelPlugin::insertInterfaceMark(QString key, InterfaceEnum value)
{
    if ("" == key || value < 0) {
        qDebug() << "插入数据失败， 传入参数有误";
        return;
    }
    if (m_InterfaceHash.contains(key)) {
        qDebug() << "此Key值已存在";
        return;
    }
    m_InterfaceHash.insert(key, value);
    return;
}

/* 展开按钮槽函数 */
void shortcutPanelPlugin::spreadClikedSlots()
{
    m_pSpreadButton->setVisible(false);
    m_pfoldButton->setVisible(true);
    m_pWeatherWidget->setVisible(true);
    m_pWIFIBluetooth->setVisible(true);
    m_pShortWidget->setVisible(true);
    int height = m_pMainWidget->height();
    int width  = m_pMainWidget->width();
    m_pMainWidget->setFixedSize(392, height*4 + 86);
    return;
}

/* 折叠按钮槽函数 */
void shortcutPanelPlugin::foldClikedSlots()
{
    m_pSpreadButton->setVisible(true);
    m_pfoldButton->setVisible(false);
    m_pWeatherWidget->setVisible(false);
    m_pWIFIBluetooth->setVisible(false);
    m_pShortWidget->setVisible(false);
    int height = m_pMainWidget->height();
    int width  = m_pMainWidget->width();
    m_pMainWidget->setFixedSize(width, 100);

    return;
}
