#include "listviewdelegate.h"
#include "swichButtonOpenStatus.h"
#include "customstyle_switchNormalStatus.h"
#include "recordsequencefile.h"
#include <QDebug>
#include <QPainter>
#include <QPushButton>

ListViewDelegate::ListViewDelegate(QObject *parent)
{
    qDebug()<<"----------------ListViewDelegate";
}

ListViewDelegate::~ListViewDelegate()
{
}

void ListViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug()<<"----------------开始绘制";
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

        //绘制图标背景图
        QPalette ple;
        QBrush br = ple.button();
        //qDebug()<<"br:"<<br.color();
        painter->setPen(QColor(br.color().red(), br.color().green(), br.color().blue()));
        painter->setBrush(QColor(br.color().red(), br.color().green(), br.color().blue()));
        painter->drawEllipse(QPoint(rect.x()+20+20,rect.y()+20+20),20,20); //（圆心，横轴半径，纵轴半径）
        //绘制图标
        static RecordSequenceFile *record = new RecordSequenceFile();
        QVector<QMap<QString,QString>> vector = record->shortcutShowVector;
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

        painter->restore();
    }
}

QSize ListViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}
