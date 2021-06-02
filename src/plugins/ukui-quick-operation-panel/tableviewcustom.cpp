#include "tableviewcustom.h"
#include "recordsequencefile.h"
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QPainter>
#include <QHeaderView>
#include <QDebug>
#include <QVariant>

TableViewCustom::TableViewCustom(QWidget *parent)
    : QTableView(parent)
{
    setAcceptDrops(true);

    mLabel = new QLabel(this);
    mLabel->setFixedHeight(80);
    mLabel->setGeometry(1, 0, 2, height());
    mLabel->setStyleSheet("border: 1px solid #8B7500;");
    mLabel->hide();

    mModel = NULL;
    mRowHeight = 40;
    mColumnWidet = 40;
    mValidPress = false;
    mRowFrom = 0;
    mRowTo = 0;

    //设置TableView属性
    this->setFixedWidth(320);
    this->setFixedHeight(240);
    this->horizontalHeader()->setVisible(false); //隐藏列头(带列头的情况需要修改代码，重新计算高度偏移)
    this->verticalHeader()->setVisible(false);   //隐藏行头
    this->verticalHeader()->setDefaultSectionSize(80);         //默认列高
    this->horizontalHeader()->setDefaultSectionSize(80);       //默认列宽
    //this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //数据列宽度自适应, 横向填满表格
    this->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);           //设置默认居中对齐
    this->setEditTriggers(QTableView::NoEditTriggers);		   //不能编辑
    this->setSelectionMode(QTableView::SingleSelection);       //单行选中
    this->setAlternatingRowColors(false);                      //取消行间隔色
    this->setShowGrid(false);                                  //去掉网格线
    this->setGridStyle(Qt::NoPen);
    this->setFocusPolicy(Qt::NoFocus);                         //去掉item选中时虚线框

    //设置样式 (设置网格为底色，做到去掉网格效果)
    //this->setStyleSheet("QTableView {border: none; solid white;background: white;}\
                      QTableView::gridline-color:white; \
                      QTableView::item{color:white;}\
                      QTableView::item:section{color:white;background: white;}\
                      QTableView::item:selected{color:white;background: white;}"); //  按下样式
    this->setStyleSheet("QTableView {border: none;}\
                    QTableView::gridline-color:black; \
                    QTableView::item:section{color:white;background: white;}\
                    QTableView::item:selected{color:white;background: white;}"); //  按下样式


}

void TableViewCustom::SetModel(QStandardItemModel *model)
{
    mModel = model;
    QTableView::setModel(model);
}

void TableViewCustom::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        qDebug()<<"e->pos():"<<e->pos();
        QModelIndex index = indexAt(e->pos());
        if (index.isValid())
        {
            mValidPress = true;
            mDragPoint = e->pos();
            mDragText = mModel->item(index.row(),index.column())->text();
            mDragPointAtItem = mDragPoint - QPoint(index.column()*mColumnWidet,index.row()*mRowHeight);
            mRowFrom = index.row();
            mColumnFrom = index.column();
        }

        QVariant var = mModel->data(index,Qt::DecorationRole);
        //qDebug()<<":::var"<<var;
        QIcon icon = var.value<QIcon>();
        //qDebug()<<":::icon"<<icon;
        pix = icon.pixmap(16,16);
        //qDebug()<<":::pix"<<pix;
    }
    QTableView::mousePressEvent(e);
}

void TableViewCustom::mouseMoveEvent ( QMouseEvent * e )
{
    if (!mValidPress)
    {
        return;
    }
    if (!(e->buttons() & Qt::LeftButton))
        return;

    if ((e->pos() - mDragPoint).manhattanLength()  < QApplication::startDragDistance())
        return;

    mLabel->show();

    DoDrag();           //开始拖拽，完成拖拽后才会继续往下走

    mLabel->hide();
    mValidPress = false;
}

void  TableViewCustom::dragEnterEvent ( QDragEnterEvent * e )
{
    if (e->mimeData()->hasText())
    {
        e->acceptProposedAction();
    }
    else
    {
        e->ignore();
        QTableView::dragEnterEvent(e);
    }
}

void  TableViewCustom::dragMoveEvent ( QDragMoveEvent * e )
{
    if(e->mimeData()->hasText())
    {
        int nCurRow = 0;
        int nCurColumn = 0;
        QModelIndex index = indexAt(e->pos());
        if (index.isValid())
        {
            if(e->pos().x() - index.column()*mColumnWidet >= mColumnWidet){
                nCurColumn = index.column() + 1;
            }
            else{
                nCurColumn = index.column();
            }

            if(e->pos().y() - index.row()*mRowHeight >= mRowHeight)
            {
                nCurRow = index.row() + 1;
            }
            else
            {
                nCurRow = index.row();
            }

        }
        else
        {
            nCurColumn = mModel->columnCount();
            nCurRow = mModel->rowCount();
        }
//        if (nCurRow != mRowFrom)
        {
            mRowTo = nCurRow;
            mColumnTo = nCurColumn;

            mLabel->setGeometry(nCurColumn*this->columnWidth(0), nCurRow*this->rowHeight(0),2,mRowHeight); //提示光标
        }
        e->acceptProposedAction();
        return;
    }

    e->ignore();
    QTableView::dragMoveEvent(e);
}

void  TableViewCustom::dropEvent ( QDropEvent * e )
{
    if(e->mimeData()->hasText())
    {
        if (mRowTo != mRowFrom || mColumnTo!=mColumnFrom)
        {
            //MoveRow(mRowFrom, mRowTo);
            MoveRow(mRowFrom, mColumnFrom, mRowTo, mColumnTo);
        }
        e->acceptProposedAction();
        return;
    }

    e->ignore();
    QTableView::dropEvent(e);
}

void TableViewCustom::DoDrag()
{
    //[1]把拖拽数据放在QMimeData容器中
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    mimeData->setText(mDragText);
    drag->setMimeData(mimeData);

    //[2]设置拖拽时的缩略图
    drag->setPixmap(pix);
    drag->setHotSpot(mDragPointAtItem);

    //***注意：此句会阻塞，进入drag的拖拽消息循环，会依次触发dragEnterEvent、dragMoveEvent、dropEvent消息
    if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
    {
        // 确认移动操作
    }
}

void TableViewCustom::ResetOrder()
{
}

void TableViewCustom::MoveRow(int from, int to)
{
    if (from == to)
    {
        return;
    }
    QStandardItem * item = mModel->item(from, 1);
    if (item)
    {
        QString strText = item->text();

        QList<QStandardItem*> items;
        QStandardItem* item0 = new QStandardItem("");
        QStandardItem* item1 = new QStandardItem(strText);
        items.append(item0);
        items.append(item1);
        item0->setTextAlignment(Qt::AlignCenter);

        //移动行思路：就是先在要移动到的位置新建同样内容的行，然后删除被移动的行
        mModel->insertRow(to, items);
        if (from < to)
        {
            mModel->removeRow(from);
            selectRow(to-1);
        }
        else
        {
            mModel->removeRow(from+1);
            selectRow(to);
        }
        emit sigRowChange(mRowFrom,mRowTo);

    }

}

void TableViewCustom::MoveRow(int RowFrom, int ColumnFrom, int RowTo, int ColumnTo)
{
//    qDebug()<<"---";
//    qDebug()<<"RowFrom : ColumnFrom "<<RowFrom <<" : " <<ColumnFrom;
//    qDebug()<<"RowTo : ColumnTo "<<RowTo <<" : " <<ColumnTo;
//    if(RowFrom==RowTo && ColumnFrom==ColumnTo){
//        return;
//    }
//    //移动行思路：将map中的数据重新排列，然后清空模型，再讲map中的数据添加进去
//    //->
//    //[1]重新排序
//    static RecordSequenceFile *record = new RecordSequenceFile();
//    QMap<QString,QString> map = record->shortcutShowMap;
//    if(RowFrom>RowTo || ColumnFrom>ColumnTo){   //后面移到前面，先删除后插入
//        qDebug()<<"先删除后插入";
//        QMap<QString,QString>::iterator iter;

//        QVector<QStringList> tmpVector;
//        for(iter=map.begin(); iter!=map.end();iter++){
//            QStringList list;
//            list.append(iter.key());
//            list.append(iter.value());
//            tmpVector.append(list);
//        }

//        //删除
//        int num = RowFrom*ColumnFrom+ColumnFrom;
//        QStringList tmpList = tmpVector.at(num);
//        tmpVector.remove(num);
//        for(int i=0;i<tmpVector.size();i++){
//            qDebug()<<"000 "<<tmpVector.at(i).at(0);
//        }
//        //插入
//        num = RowTo*ColumnTo+ColumnTo;
//        tmpVector.insert(num,tmpList);
//        for(int i=0;i<tmpVector.size();i++){
//            qDebug()<<"111 "<<tmpVector.at(i).at(0);
//        }

//        map.clear();



//        QMap<QString,QString> map2;
//        for(int i=0;i<tmpVector.size();i++){
//            QStringList list = tmpVector.at(i);
//            qDebug()<<"222 "<<list.at(0);
//            QMap<QString,QString>::iterator iter3;
//            iter3 = map2.insert(list.at(0),list.at(1));

//            QMap<QString,QString>::iterator itt=map2.begin();
//            for(itt=map2.begin();itt!=map2.end();itt++){
//                qDebug()<<"=== "<<itt.key();
//            }
//        }
////        QMap<QString,QString>::iterator itt=map2.begin();
////        //qDebug()<<"=== "<<itt.key();


////        for(itt=map2.begin();itt!=map2.end();itt++){
////            qDebug()<<"=== "<<itt.key();
////        }

//    }
////    else{                                       //前面移动后面，先插入后删除
////        qDebug()<<"先插入后删除";
////        QMap<QString,QString>::iterator iter = map.begin();
////        //插入
////        iter = map.begin();
////        iter += RowTo*ColumnTo+ColumnTo;
////        QString key = iter.key();
////        QString value = iter.value();
////        map.insert(iter,key,value);
////        //删除
////        iter = map.begin();
////        iter += RowFrom*ColumnFrom+ColumnFrom;
////        map.erase(iter);
////    }
////    //[2]清空模型，再将数据重新添加到模型中
////    mModel->clear();
////    QMap<QString,QString>::iterator iter = map.begin();
////    int i=0;
////    for(iter=map.begin(); iter!=map.end();iter++){
////        QStandardItem *item = new QStandardItem;
////        item->setText(iter.key());
////        mModel->setItem(i/4,i%4,item);
////        i++;
////    }

//    emit sigRowChange(mRowFrom,mRowTo);

//    //-<
}
