#include "listviewdelegate.h"
#include "swichButtonOpenStatus.h"
#include "customstyle_switchNormalStatus.h"
#include "recordsequencefile.h"
#include <QDebug>
#include <QPainter>
#include <QPushButton>
#include <QEvent>
#include <QMouseEvent>

ListViewDelegate::ListViewDelegate(QObject *parent): QItemDelegate(parent)
{
    qDebug()<<"实例化 代理 ListViewDelegate";
}

ListViewDelegate::~ListViewDelegate()
{
}

void ListViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //qDebug()<<"--- 绘制 listview paint..."<<index.row();
    if(index.isValid())
    {
        painter->save();

        QString shortcutName = index.data(Qt::DisplayRole).toString();
        //qDebug()<<"---shortcutName:"<<shortcutName;
        QStyleOptionViewItem viewOption(option); //用来在视图中画一个item
        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth(option.rect.width()-1);
        rect.setHeight(option.rect.height()-1);

        if(m_hoverRow == index.row()){
            //鼠标悬停渲染
            qDebug()<<"鼠标悬停渲染";
            //绘制图标背景图
            QPalette ple;
            QBrush br = ple.button();
            //qDebug()<<"br:"<<br.color();
            painter->setPen(QColor(0, 0, br.color().blue()));
            painter->setBrush(QColor(0, 0, br.color().blue()));
            painter->drawEllipse(QPoint(rect.x()+20+20,rect.y()+20+20),20,20); //（圆心，横轴半径，纵轴半径）
        }
        else{
            //绘制图标背景图
            QPalette ple;
            QBrush br = ple.button();
            //qDebug()<<"br:"<<br.color();
            painter->setPen(QColor(br.color().red(), br.color().green(), br.color().blue()));
            painter->setBrush(QColor(br.color().red(), br.color().green(), br.color().blue()));
            painter->drawEllipse(QPoint(rect.x()+20+20,rect.y()+20+20),20,20); //（圆心，横轴半径，纵轴半径）
            //绘制图标
            RecordSequenceFile *record = RecordSequenceFile::getInstance();
            QVector<QMap<QString,QString>> vector = record->getShortcutShowVector();
            for (int i = 0; i < vector.size(); ++i) {
                QString name = vector.at(i).begin().key();
                if(shortcutName == name){
                    QString icon = vector.at(i).begin().value();
                    painter->drawPixmap(rect.x()+30,rect.y()+30,20,20,QPixmap(icon));  //添加对应图标
                    break;
                }
            }
            //绘制文字
            painter->setPen(QPen(Qt::blue));
            painter->setBrush(QColor(229, 241, 255));
    //        painter->setPen(QPen(Qt::black));
            painter->setFont(QFont("Times", 12, QFont::Bold));
            painter->drawText(QRect(rect.x()+10,rect.y()+58,80,20),Qt::AlignLeft,shortcutName); //绘制名字
        }



        painter->restore();


        //绘制焦点区


    }
}
//注：使用委托渲染视图时，使用paint和sizeHint都需要重写。如果不重写sizeHint会出现视图渲染不出来的情况
QSize ListViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize( 200, 100 ); //这个返回值很重要，暂时还不清楚是什么作用，取值不当会造成listView获取到的index错误
    //https://zhidao.baidu.com/question/2015052398295995068.html
}

bool ListViewDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    //代理中获取点击index,可对此index做编辑
    qDebug()<<"---editorEvent::"<<index.row();
    return false;
}

void ListViewDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug()<<"---updateEditorGeometry::"<<index.row();
}

bool ListViewDelegate::eventFilter(QObject *object, QEvent *event)
{
    qDebug()<<"---eventFilter::"<<object->objectName();
     if(event->type() == QEvent::MouseMove){
        qDebug()<<"---eventFilter::"<<object->objectName();
     }
}

void ListViewDelegate::drawFocus(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect) const
{
    qDebug()<<"---drawFocus::";
}

void ListViewDelegate::onHoverIndexChanged(const QModelIndex &index)
{
    qDebug()<<"---onHoverIndexChanged::"<<index.row();
    m_hoverRow = index.row();
}
