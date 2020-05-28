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
//#include "view-type-menu.h"
//#include "sort-type-menu.h"
//#include "operation-menu.h"

//#include "directory-view-container.h"
//#include "directory-view-widget.h"
//#include "advanced-location-bar.h"

//#include "directory-view-factory-manager.h"
//#include "directory-view-plugin-iface2.h"

#include <QHBoxLayout>
#include <QUrl>
#include <QMessageBox>
#include <QProcess>
#include <QDir>
#include <QStyleOptionToolButton>
#include <QEvent>
//#include <KWindowSystem>
#include <QDebug>
//#include <gio/gio.h>

#include "headerbar.h"
#include "widget.h"



static HeaderBarStyle *global_instance = nullptr;
static QString terminal_cmd = nullptr;

HeaderBar::HeaderBar(Widget *parent) : QToolBar(parent)
{
    setMouseTracking(true);
    setStyle(HeaderBarStyle::getStyle());

    m_window = parent;
    //disable default menu
    setContextMenuPolicy(Qt::CustomContextMenu);
    //setAttribute(Qt::WA_OpaquePaintEvent);
    setStyleSheet(".HeaderBar{"
                  "background-color: transparent;"
                  "border: 0px solid transparent;"
                  "margin: 4px 5px 4px 5px;"
                  "};");

    setMovable(false);

    auto a = addAction(QIcon::fromTheme("view-grid-symbolic"), tr("View Type"));
    auto viewType = qobject_cast<QToolButton *>(widgetForAction(a));
    viewType->setAutoRaise(false);
//    viewType->setFixedSize(QSize(57, 40));
    viewType->setFixedSize(QSize(32, 32));
    viewType->setIconSize(QSize(16, 16));
    viewType->setPopupMode(QToolButton::InstantPopup);

//    m_view_type_menu = new ViewTypeMenu(viewType);
//    viewType->setMenu(m_view_type_menu);

//    connect(m_view_type_menu, &ViewTypeMenu::switchViewRequest, this, [=](const QString &id, const QIcon &icon, bool resetToZoomLevel){
//        viewType->setText(id);
//        viewType->setIcon(icon);
//        this->viewTypeChangeRequest(id);
//        if (resetToZoomLevel) {
//            auto viewId = m_window->getCurrentPage()->getView()->viewId();
//            auto factoryManger = Peony::DirectoryViewFactoryManager2::getInstance();
//            auto factory = factoryManger->getFactory(viewId);
//            int zoomLevelHint = factory->zoom_level_hint();
//            m_window->getCurrentPage()->setZoomLevelRequest(zoomLevelHint);
//        }
//    });

//    connect(m_view_type_menu, &ViewTypeMenu::updateZoomLevelHintRequest, this, &HeaderBar::updateZoomLevelHintRequest);

    addSpacing(2);

//    a = addAction(QIcon::fromTheme("view-sort-ascending-symbolic"), tr("Sort Type"));
    a = addAction(QIcon(":/image/1x/array.png"), tr("Sort Type"));
    auto sortType = qobject_cast<QToolButton *>(widgetForAction(a));
    //sortType->setStyleSheet("QToolButton{background-color:rgba(19,20,20,0);}");
    sortType->setAutoRaise(false);
    sortType->setFixedSize(QSize(32, 32));
    sortType->setIconSize(QSize(16, 16));
    sortType->setPopupMode(QToolButton::InstantPopup);

//    m_sort_type_menu = new SortTypeMenu(this);
//    sortType->setMenu(m_sort_type_menu);

//    connect(m_sort_type_menu, &SortTypeMenu::switchSortTypeRequest, m_window, &MainWindow::setCurrentSortColumn);
//    connect(m_sort_type_menu, &SortTypeMenu::switchSortOrderRequest, m_window, [=](Qt::SortOrder order){
//        if (order == Qt::AscendingOrder) {
//            sortType->setIcon(QIcon::fromTheme("view-sort-ascending-symbolic"));
//        } else {
//            sortType->setIcon(QIcon::fromTheme("view-sort-descending-symbolic"));
//        }
//        m_window->setCurrentSortOrder(order);
//    });
//    connect(m_sort_type_menu, &QMenu::aboutToShow, m_sort_type_menu, [=](){
//        m_sort_type_menu->setSortType(m_window->getCurrentSortColumn());
//        m_sort_type_menu->setSortOrder(m_window->getCurrentSortOrder());
//    });

    addSpacing(2);
    for (auto action : actions()) {
        auto w = widgetForAction(action);
        w->setProperty("useIconHighlightEffect", true);
        w->setProperty("iconHighlightEffectMode", 1);
    }
}


void HeaderBar::addSpacing(int pixel)
{
    for (int i = 0; i < pixel; i++) {
        addSeparator();
    }
}

void HeaderBar::mouseMoveEvent(QMouseEvent *e)
{
    QToolBar::mouseMoveEvent(e);
    QCursor c;
    c.setShape(Qt::ArrowCursor);
    this->topLevelWidget()->setCursor(c);
}

//HeaderBarToolButton
HeaderBarToolButton::HeaderBarToolButton(QWidget *parent) : QToolButton(parent)
{
    setAutoRaise(false);
    setIconSize(QSize(16, 16));
}

//HeadBarPushButton
HeadBarPushButton::HeadBarPushButton(QWidget *parent) : QPushButton(parent)
{
    setIconSize(QSize(16, 16));
}

//HeaderBarStyle
HeaderBarStyle *HeaderBarStyle::getStyle()
{
    if (!global_instance) {
        global_instance = new HeaderBarStyle;
    }
    return global_instance;
}

int HeaderBarStyle::pixelMetric(QStyle::PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
    switch (metric) {
    case PM_ToolBarIconSize:
        return 16;
    case PM_ToolBarSeparatorExtent:
        return 1;
    case PM_ToolBarItemSpacing: {
        return 1;
    }
    default:
        return QProxyStyle::pixelMetric(metric, option, widget);
    }
}

void HeaderBarStyle::drawComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const
{
    //This is a "lie". We want to use instant popup menu for tool button, and we aslo
    //want use popup menu style with this tool button, so we change the related flags
    //to draw in our expected.
    //qDebug() << "drawComplexControl";
    if (control == CC_ToolButton) {
        //qDebug() << "######";
        QStyleOptionToolButton button = *qstyleoption_cast<const QStyleOptionToolButton *>(option);
        //The button has a popup menu.
        //if (button.features.testFlag(QStyleOptionToolButton::HasMenu)) {
            //qDebug() << "drawComplexControl 1111";
            button.features = QStyleOptionToolButton::None;
            if (!widget->property("isOptionButton").toBool()) {
                //qDebug() << "drawComplexControl 2222";
                button.features |= QStyleOptionToolButton::HasMenu;
                button.features |= QStyleOptionToolButton::MenuButtonPopup;
                //QStyle::SubControls 此枚举描述可用的子控件
                //QStyle::SC_ToolButtonMenu 用于在工具按钮中打开弹出菜单的子控件。
                button.subControls |= QStyle::SC_ToolButtonMenu;
            }
            return QProxyStyle::drawComplexControl(control, &button, painter, widget);
        //}
    }
    //qDebug() << "drawComplexControl 3333";
    return QProxyStyle::drawComplexControl(control, option, painter, widget);
}

void HeaderBarStyle::drawPrimitive(QStyle::PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    if (element == PE_IndicatorToolBarSeparator) {
        return;
    }
    return QProxyStyle::drawPrimitive(element, option, painter, widget);
}
