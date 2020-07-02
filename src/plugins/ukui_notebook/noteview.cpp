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
#include "noteview.h"
#include "listViewModeDelegate.h"
#include <QDebug>
#include <QPainter>
#include <QApplication>
#include <QAbstractItemView>
#include <QPaintEvent>
#include <QSortFilterProxyModel>
#include <QTimer>
#include <QScrollBar>

NoteView::NoteView(QWidget *parent)
    : QListView( parent )
    , m_isScrollBarHidden(true)
    , m_animationEnabled(true)
    , m_isMousePressed(false)
    , m_rowHeight(38)
{
    //不可编辑
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setAttribute(Qt::WA_TranslucentBackground);//设置窗口透明显示(毛玻璃效果)
    //一次性定时器,槽函数只处理一次
    QTimer::singleShot(0, this, SLOT(init()));
}

NoteView::~NoteView()
{
}

void NoteView::animateAddedRow(const QModelIndex& parent, int start, int end)
{
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    Q_UNUSED(parent)
    Q_UNUSED(end)

    //model(): 返回此视图显示的模型。
    QModelIndex idx = model()->index(start,0);
    // Note: 这一行添加了flikering，当动画运行缓慢时可以看到
    // QItemSelectionModel::ClearAndSelect 将清除完整的选择 | 将选择所有指定的索引
    // selectionModel(): Returns the current selection model.
    // select(): 使用指定的命令选择模型项索引，并发出selectionChanged（）
    selectionModel()->select(idx, QItemSelectionModel::ClearAndSelect);

    listViewModeDelegate* delegate = static_cast<listViewModeDelegate*>(itemDelegate());
    if(delegate != Q_NULLPTR){
        delegate->setState(listViewModeDelegate::Insert, idx);

        // TODO find a way to finish this function till the animation stops
        while(delegate->animationState() == QTimeLine::Running){
            qApp->processEvents();
        }
    }
}

void NoteView::animateRemovedRow(const QModelIndex& parent, int start, int end)
{
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    Q_UNUSED(parent)
    Q_UNUSED(end)

    //model(): 返回此视图显示的模型。
    QModelIndex idx = model()->index(start,0);
    // Note: 这一行添加了flikering，当动画运行缓慢时可以看到
    // QItemSelectionModel::ClearAndSelect 将清除完整的选择 | 将选择所有指定的索引
    // selectionModel(): Returns the current selection model.
    // select(): 使用指定的命令选择模型项索引，并发出selectionChanged（）
    selectionModel()->select(idx, QItemSelectionModel::ClearAndSelect);

    listViewModeDelegate* delegate = static_cast<listViewModeDelegate*>(itemDelegate());
    if(delegate != Q_NULLPTR){
        delegate->setCurrentSelectedIndex(QModelIndex());
        delegate->setState(listViewModeDelegate::Remove, idx);

        // TODO find a way to finish this function till the animation stops
        while(delegate->animationState() == QTimeLine::Running){
            qApp->processEvents();
        }
    }
}

void NoteView::paintEvent(QPaintEvent *e)
{
    listViewModeDelegate* delegate = static_cast<listViewModeDelegate*>(itemDelegate());
    if(delegate != Q_NULLPTR)
    {
        delegate->setCurrentSelectedIndex(currentIndex());
    }

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);

    p.setBrush(opt.palette.color(QPalette::Base));
    //qDebug() << "paintEvent" << p.brush().color().value();
    p.setOpacity(0.3);
    p.setPen(Qt::NoPen);

    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    //p.drawRoundedRect(opt.rect,6,6);
    //style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    //QListView::paintEvent(e);
}

void NoteView::rowsInserted(const QModelIndex &parent, int start, int end)
{
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    if(start == end && m_animationEnabled)
        animateAddedRow(parent, start, end);

    QListView::rowsInserted(parent, start, end);
}

void NoteView::rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end)
{
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    if(start == end){
        listViewModeDelegate* delegate = static_cast<listViewModeDelegate*>(itemDelegate());
        if(delegate != Q_NULLPTR){
            QModelIndex idx = model()->index(start,0);
            delegate->setCurrentSelectedIndex(QModelIndex());

            if(m_animationEnabled){
                qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
                delegate->setState(listViewModeDelegate::Remove, idx);
            }else{
                delegate->setState(listViewModeDelegate::Normal, idx);
            }

            // TODO find a way to finish this function till the animation stops
            while(delegate->animationState() == QTimeLine::Running){
                qApp->processEvents();
            }
        }
    }

    QListView::rowsAboutToBeRemoved(parent, start, end);
}

void NoteView::rowsAboutToBeMoved(const QModelIndex &sourceParent, int sourceStart, int sourceEnd,
                                  const QModelIndex &destinationParent, int destinationRow)
{
    Q_UNUSED(sourceParent)
    Q_UNUSED(sourceEnd)
    Q_UNUSED(destinationParent)
    Q_UNUSED(destinationRow)

    if(model() != Q_NULLPTR){
        QModelIndex idx = model()->index(sourceStart,0);
        listViewModeDelegate* delegate = static_cast<listViewModeDelegate*>(itemDelegate());
        if(delegate != Q_NULLPTR){

            if(m_animationEnabled){
                delegate->setState(listViewModeDelegate::MoveOut, idx);
            }else{
                delegate->setState(listViewModeDelegate::Normal, idx);
            }

            // TODO find a way to finish this function till the animation stops
            while(delegate->animationState() == QTimeLine::Running){
                qApp->processEvents();
            }
        }
    }
}

void NoteView::rowsMoved(const QModelIndex &parent, int start, int end,
                         const QModelIndex &destination, int row)
{
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    Q_UNUSED(parent)
    Q_UNUSED(start)
    Q_UNUSED(end)
    Q_UNUSED(destination)

    QModelIndex idx = model()->index(row,0);
    setCurrentIndex(idx);

    listViewModeDelegate* delegate = static_cast<listViewModeDelegate*>(itemDelegate());
    if(delegate == Q_NULLPTR)
        return;

    if(m_animationEnabled){
        delegate->setState(listViewModeDelegate::MoveIn, idx );
    }else{
        delegate->setState(listViewModeDelegate::Normal, idx);
    }

    // TODO find a way to finish this function till the animation stops
    while(delegate->animationState() == QTimeLine::Running){
        qApp->processEvents();
    }
}

void NoteView::init()
{
    setMouseTracking(true);
    setUpdatesEnabled(true);
    //当鼠标进入或离开小部件时，强制Qt生成绘制事件
    viewport()->setAttribute(Qt::WA_Hover);

    setupSignalsSlots();
}

void NoteView::mouseMoveEvent(QMouseEvent* e)
{
    if(!m_isMousePressed){
        QListView::mouseMoveEvent(e);
    }
}

void NoteView::mousePressEvent(QMouseEvent* e)
{
    m_isMousePressed = true;
    QListView::mousePressEvent(e);
}

void NoteView::mouseReleaseEvent(QMouseEvent* e)
{
    m_isMousePressed = false;
    QListView::mouseReleaseEvent(e);
}

bool NoteView::viewportEvent(QEvent* e)
{
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    if(model() != Q_NULLPTR){
        switch (e->type()) {
        case QEvent::Leave:{
            QPoint pt = mapFromGlobal(QCursor::pos());
            QModelIndex index = indexAt(QPoint(10, pt.y()));
            if(index.row() > 0){
                index = model()->index(index.row()-1, 0);
                listViewModeDelegate* delegate = static_cast<listViewModeDelegate*>(itemDelegate());
                if(delegate != Q_NULLPTR){
                    delegate->setHoveredIndex(QModelIndex());
                    viewport()->update(visualRect(index));
                }
            }
            break;
        }
        //鼠标按键按下
        case QEvent::MouseButtonPress:{
            qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
            //将全局屏幕坐标pos转换为小部件坐标
            QPoint pt = mapFromGlobal(QCursor::pos());
            //返回在内容坐标中包含点x，y的可见项的索引。如果在指定的点上没有项，或者项不可见，则返回-1。
            QModelIndex index = indexAt(QPoint(10, pt.y()));
            if(!index.isValid())
                emit viewportPressed();

            break;
        }
        default:
            break;
        }
    }

    return QListView::viewportEvent(e);
}

void NoteView::setCurrentRowActive(bool isActive)
{
    qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    listViewModeDelegate* delegate = static_cast<listViewModeDelegate*>(itemDelegate());
    if(delegate == Q_NULLPTR)
        return;

    delegate->setActive(isActive);
    viewport()->update(visualRect(currentIndex()));
}

void NoteView::setAnimationEnabled(bool isEnabled)
{
    m_animationEnabled = isEnabled;
}

void NoteView::setupSignalsSlots()
{
    // remove/add separator
    // current selectected row changed
    connect(selectionModel(), &QItemSelectionModel::currentRowChanged, [this]
            (const QModelIndex & current, const QModelIndex & previous){

        if(model() != Q_NULLPTR){
            if(current.row() < previous.row()){
                if(current.row() > 0){
                    QModelIndex prevIndex = model()->index(current.row()-1, 0);
                    viewport()->update(visualRect(prevIndex));
                }
            }

            if(current.row() > 1){
                QModelIndex prevPrevIndex = model()->index(current.row()-2, 0);
                viewport()->update(visualRect(prevPrevIndex));
            }
        }
    });

    // row was entered
    connect(this, &NoteView::entered,[this](QModelIndex index){
        if(model() != Q_NULLPTR){
            if(index.row() > 1){
                QModelIndex prevPrevIndex = model()->index(index.row()-2, 0);
                viewport()->update(visualRect(prevPrevIndex));

                QModelIndex prevIndex = model()->index(index.row()-1, 0);
                viewport()->update(visualRect(prevIndex));

            }else if(index.row() > 0){
                QModelIndex prevIndex = model()->index(index.row()-1, 0);
                viewport()->update(visualRect(prevIndex));
            }

            listViewModeDelegate* delegate = static_cast<listViewModeDelegate *>(itemDelegate());
            if(delegate != Q_NULLPTR)
                delegate->setHoveredIndex(index);
        }
    });

    // viewport was entered
    connect(this, &NoteView::viewportEntered,[this](){
        qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
        if(model() != Q_NULLPTR && model()->rowCount() > 1){
            listViewModeDelegate* delegate = static_cast<listViewModeDelegate *>(itemDelegate());
            if(delegate != Q_NULLPTR)
                delegate->setHoveredIndex(QModelIndex());

            QModelIndex lastIndex = model()->index(model()->rowCount()-2, 0);
            viewport()->update(visualRect(lastIndex));
        }
    });

    // remove/add offset right side
    connect(this->verticalScrollBar(), &QScrollBar::rangeChanged,[this](int min, int max){
        Q_UNUSED(min)

        listViewModeDelegate* delegate = static_cast<listViewModeDelegate*>(itemDelegate());
        if(delegate != Q_NULLPTR){
            if(max > 0){
                delegate->setRowRightOffset(2);
            }else{
                delegate->setRowRightOffset(0);
            }
            viewport()->update();
        }
    });
}

