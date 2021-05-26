/*
 * Copyright (C) 2020, KylinSoft Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "adaptscreeninfo.h"

adaptScreenInfo::adaptScreenInfo(QObject *parent) : QObject(parent)
{
    //返回桌面小部件（也称为根窗口）。
    //桌面可能由多个屏幕组成，因此尝试在窗口的几何图形中居中某个窗口小部件是不正确的
    m_pDeskWgt = QApplication::desktop();
    //初始化主屏坐标
    InitializeHomeScreenGeometry();
    //初始化屏幕宽高
    initScreenSize();
    //当改变屏幕分辨率时 重新计算 主屏坐标 屏幕宽高
    connect(QApplication::primaryScreen(), &QScreen::geometryChanged, this, &adaptScreenInfo::onResolutionChanged);
    //主屏发生变化槽函数 重新计算 主屏坐标 屏幕宽高
    connect(m_pDeskWgt, &QDesktopWidget::primaryScreenChanged, this, &adaptScreenInfo::primaryScreenChangedSlot);
    //屏幕数量改变时 重新计算 主屏坐标 屏幕宽高
    connect(m_pDeskWgt, &QDesktopWidget::screenCountChanged, this, &adaptScreenInfo::screenCountChangedSlots);
    //屏幕list
    m_pListScreen = QGuiApplication::screens();
}

/* 当屏幕数量发生改变时，重新赋值m_pListScreen 未发现调用 */
void adaptScreenInfo::screenNumChange()
{
    m_pListScreen = QGuiApplication::screens();
}


/* 初始化屏幕高度， 宽度 */
void adaptScreenInfo::initScreenSize()
{
    QList<QScreen*> screen = QGuiApplication::screens();
    int count = m_pDeskWgt->screenCount();
    if (count > 1) {
        m_screenWidth  = screen[0]->geometry().width() + m_nScreen_x;
        m_screenHeight = screen[0]->geometry().height() + m_nScreen_y;
    } else {
        m_screenWidth = m_pDeskWgt->width() + m_nScreen_x;
        m_screenHeight = m_pDeskWgt->height() + m_nScreen_y;
    }
    qDebug() << "屏幕高度m_screenWidth" << m_screenWidth;
    qDebug() << "屏幕宽度m_screenHeight" << m_screenHeight;
    return;
}

/* 初始化主屏坐标 */
void adaptScreenInfo::InitializeHomeScreenGeometry()
{
    QList<QScreen*> screen = QGuiApplication::screens();
    int count = m_pDeskWgt->screenCount();
    if (count > 1) {
        m_nScreen_x = screen[0]->geometry().x();
        m_nScreen_y = screen[0]->geometry().y();
    } else {
        m_nScreen_x = 0;
        m_nScreen_y = 0;
    }
    qDebug() << "偏移的x坐标" << m_nScreen_x;
    qDebug() << "偏移的Y坐标" << m_nScreen_y;
}

//当改变屏幕分辨率时重新获取屏幕分辨率
void adaptScreenInfo::onResolutionChanged(const QRect argc)
{
    Q_UNUSED(argc);
    initScreenSize();                               //获取屏幕可用高度区域
    InitializeHomeScreenGeometry();
    return;
}

/* 主屏发生变化槽函数 */
void adaptScreenInfo::primaryScreenChangedSlot()
{
    InitializeHomeScreenGeometry();
    initScreenSize();
    return;
}

/* 屏幕数量改变时对应槽函数 */
void adaptScreenInfo::screenCountChangedSlots(int count)
{
    Q_UNUSED(count);
    InitializeHomeScreenGeometry();
    initScreenSize();
    return;
}
