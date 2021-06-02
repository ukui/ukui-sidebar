#include "tableviewdelegate.h"
#include "swichButtonOpenStatus.h"
#include "customstyle_switchNormalStatus.h"
#include "recordsequencefile.h"
#include <QDebug>
#include <QPainter>
#include <QPushButton>

TableViewDelegate::TableViewDelegate(QObject *parent)
{   
}

TableViewDelegate::~TableViewDelegate()
{
}

void TableViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    if(index.isValid())
//    {
//        painter->save();

//        QString shortcutName = index.data(Qt::DisplayRole).toString();
//        //qDebug()<<"shortcutName:"<<shortcutName;
//        QStyleOptionViewItem viewOption(option); //用来在视图中画一个item

//        QRectF rect;
//        rect.setX(option.rect.x());
//        rect.setY(option.rect.y());
//        rect.setWidth(option.rect.width()-1);
//        rect.setHeight(option.rect.height()-1);

//        //画图标背景图
//        QPalette ple;
//        QBrush br = ple.button();
//        //qDebug()<<"br:"<<br.color();
//        painter->setPen(QColor(br.color().red(), br.color().green(), br.color().blue()));
//        painter->setBrush(QColor(br.color().red(), br.color().green(), br.color().blue()));
//        painter->drawEllipse(QPoint(rect.x()+20+20,rect.y()+20+20),20,20); //（圆心，横轴半径，纵轴半径）
//        //画图标
//        static RecordSequenceFile *record = new RecordSequenceFile();
//        QMap<QString,QString> map = record->shortcutShowMap;
//        QMap<QString,QString>::iterator iter;
//        for(iter = map.begin(); iter != map.end(); iter++){
//            if(iter.key() == shortcutName){
//               painter->drawPixmap(rect.x()+30,rect.y()+30,20,20,QPixmap(iter.value()));  //添加对应图标
//               break;
//            }
//        }
//        //画文字
//        painter->setPen(QPen(Qt::blue));
//        painter->setBrush(QColor(229, 241, 255));
////        painter->setPen(QPen(Qt::black));
//        painter->setFont(QFont("Times", 12, QFont::Bold));
//        painter->drawText(QRect(rect.x()+10,rect.y()+58,80,20),Qt::AlignLeft,shortcutName); //绘制名字



//        painter->restore();
//    }
}

QSize TableViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
}

//QWidget *TableViewDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    QPushButton* button = new  QPushButton(parent);
//    QStyle *m_pStyleOpen   = new CustomStyle_SwitchOpenStatus("ukui-default");
//    QStyle *m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");
//    button->setStyle(m_pStyleNormal);

//    return button;
//}

//void TableViewDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
//{
//    //indeData = index.model()->data(index,Qt::DisplayRole).toString();
//    //MyButton *btnWid = static_cast<MyButton*>(editor);
//    //btnWid->m_pLabel->setText(QObject::tr("0000"));

//}

//void TableViewDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
//{

//}

//void TableViewDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{

//}
