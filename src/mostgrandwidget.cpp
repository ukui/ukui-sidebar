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
#include "mostgrandwidget.h"

static mostGrandWidget* global_Most_Grand_Widgets_instance = nullptr;

mostGrandWidget::mostGrandWidget(QWidget *parent)
{
    Q_UNUSED(parent)
    this->setContentsMargins(0,0,0,0);
    m_pmostGrandWidgetVLaout = new QVBoxLayout();
    m_pmostGrandWidgetVLaout->setContentsMargins(0,0,0,0);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
}

mostGrandWidget::~mostGrandWidget()
{

}

void mostGrandWidget::mostGrandWidgetInit()
{
    mostGrandWidget::getInstancemostGrandWidget();
    return;
}

mostGrandWidget* mostGrandWidget::getInstancemostGrandWidget()
{
    if (global_Most_Grand_Widgets_instance == nullptr) {
        global_Most_Grand_Widgets_instance = new mostGrandWidget();
    }
    return global_Most_Grand_Widgets_instance;
}

/* last Laout MostGrand Widget */
void mostGrandWidget::LaoutSidebarWidget()
{
    this->setLayout(m_pmostGrandWidgetVLaout);
    return;
}

void mostGrandWidget::setMostGrandwidgetSize(int w, int h)
{
    this->setFixedSize(w,h);
    return;
}

void mostGrandWidget::setMostGrandwidgetCoordinates(int x, int y)
{
    this->move(x, y);
    return;
}
