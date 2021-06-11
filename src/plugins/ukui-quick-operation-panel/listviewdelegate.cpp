#include "listviewdelegate.h"
#include "swichButtonOpenStatus.h"
#include "customstyle_switchNormalStatus.h"
#include "recordsequencefile.h"
#include <QDebug>
#include <QPainter>
#include <QPushButton>
#include <QEvent>
#include <QMouseEvent>
#include <QObject>

ListViewDelegate::ListViewDelegate(QObject *parent): QItemDelegate(parent)
{
    qDebug()<<"实例化 代理 ListViewDelegate";

    const QByteArray id(NIGHT_MODE_CONTROL);
    if (QGSettings::isSchemaInstalled(id)) {
        m_pTabletModeGsetting = new QGSettings(id);
        if (m_pTabletModeGsetting->keys().contains(NIGHT_MODE_KEY)) {
            m_bModelStatus = m_pTabletModeGsetting->get(NIGHT_MODE_KEY).toBool();
        }
//        QMetaObject::connect(m_pTabletModeGsetting, &QGSettings::changed, this, [=](const QString &key) {
//            if (key == NIGHT_MODE_KEY) {

//            }
//        });
    }
}

ListViewDelegate::~ListViewDelegate()
{
}

void ListViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //qDebug()<<"--- 绘制 listview paint..."<<index.row();
    //获取系统主题
    bool m_bModelStatus = true;
    if (m_pTabletModeGsetting->keys().contains(NIGHT_MODE_KEY)) {
        m_bModelStatus = m_pTabletModeGsetting->get(NIGHT_MODE_KEY).toBool();
        //qDebug()<<"111111111:"<<m_bModelStatus;
    }
     

    if(index.isValid())
    {
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing, true);
        
        QString shortcutName = index.data(Qt::DisplayRole).toString();
        //qDebug()<<"---shortcutName:"<<shortcutName;
        QStyleOptionViewItem viewOption(option); //用来在视图中画一个item
        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth(option.rect.width()-1);
        rect.setHeight(option.rect.height()-1);

        if(m_bModelStatus){  //深色主题
            //qDebug()<<"深色主题渲染";

        }
        else{   //浅色主题
            //qDebug()<<"浅色主题渲染";
            RecordSequenceFile *record = RecordSequenceFile::getInstance();
            if(index.row() == record->m_hoverIndex && record->m_hoverStatus){  //鼠标悬停渲染
                //绘制图标背景图
                painter->setPen(QColor(0x40,0xA9,0xFB));
                painter->setBrush(QColor(0x40,0xA9,0xFB));
                painter->drawEllipse(QPoint(rect.x()+18+24,rect.y()+12+24),24,24); //（圆心，横轴半径，纵轴半径）
                //绘制图标
                RecordSequenceFile *record = RecordSequenceFile::getInstance();
                QVector<QMap<QString,QString>> vector = record->getShortcutShowVector();
                for (int i = 0; i < vector.size(); ++i) {
                    QString name = vector.at(i).begin().key();
                    if(shortcutName == name){
                        QString icon = vector.at(i).begin().value();
                        painter->drawPixmap(rect.x()+18+24-12,rect.y()+12+24-12,24,24,QPixmap(icon));  //添加对应图标
                        break;
                    }
                }
                //绘制文字
                painter->setPen(QColor(0x40, 0x40, 0x40));
                painter->setBrush(QColor(0x40, 0x40, 0x40));
                painter->setFont(QFont("Times", 12, QFont::Bold));
                painter->drawText(QRect(rect.x(),rect.y()+12+48+1 ,80,20),Qt::AlignCenter,shortcutName); //绘制名字
            }
            else if(0){ //鼠标点击渲染
                //不明确点击效果需求,暂时不做这个功能
            }
            else{
                //绘制图标背景图
                painter->setPen(QColor(0xF0,0xF0,0xF0));
                painter->setBrush(QColor(0xF0,0xF0,0xF0));
                painter->drawEllipse(QPoint(rect.x()+18+24,rect.y()+12+24),24,24); //（圆心，横轴半径，纵轴半径）
                //绘制图标
                RecordSequenceFile *record = RecordSequenceFile::getInstance();
                QVector<QMap<QString,QString>> vector = record->getShortcutShowVector();
                for (int i = 0; i < vector.size(); ++i) {
                    QString name = vector.at(i).begin().key();
                    if(shortcutName == name){
                        QString icon = vector.at(i).begin().value();
                        painter->drawPixmap(rect.x()+18+24-12,rect.y()+12+24-12,24,24,QPixmap(icon));  //添加对应图标
                        break;
                    }
                }
                //绘制文字
                painter->setPen(QColor(0x40, 0x40, 0x40));
                painter->setBrush(QColor(0x40, 0x40, 0x40));
                painter->setFont(QFont("Times", 12, QFont::Bold));
                painter->drawText(QRect(rect.x(),rect.y()+12+48+1 ,80,20),Qt::AlignCenter,shortcutName); //绘制名字
            }
        }




        painter->restore();





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
