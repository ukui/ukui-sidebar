#include "listviewcustom.h"
#include "recordsequencefile.h"
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QPainter>
#include <QHeaderView>
#include <QDebug>
#include <QVariant>

ListViewCustom::ListViewCustom(QWidget *parent): QListView(parent)
{
    setAcceptDrops(true);
    //设置拖拽提示线的样式
    m_label = new QLabel(this);
    m_label->setFixedHeight(80);
    m_label->setGeometry(1, 0, 2, height());
    m_label->setStyleSheet("border: 1px solid #8B7500;");
    m_label->hide();

    //m_editMode = false;
    m_editMode = true;//测试用
    m_model = NULL;
    m_cellHeight = 85;
    m_cellWidet = 92;
    m_validPress = false;
    m_rowFrom = 0;
    m_rowTo = 0;

    //设置ListView属性      实现流式布局和多列效果
    this->setViewMode(QListView::IconMode);//多列效果
    this->setFlow(QListView::LeftToRight);
    this->setResizeMode(QListView::Adjust);//自动换行
    //this->setLayoutMode(QListView::Batched);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    const QSize size(m_cellWidet,m_cellHeight);    //设置网格大小
    this->setGridSize(size);
}
void ListViewCustom::SetModel(QStringListModel *model)
{
    m_model = model;
    QListView::setModel(model);
}
void ListViewCustom::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        QModelIndex index = QListView::indexAt(e->pos());
        qDebug()<<"index.row():"<<index.row();;
        if (index.isValid())
        {
            m_validPress = true;
            m_dragPoint = e->pos(); //记录按下时位置
            QVariant var= m_model->data(index,Qt::EditRole);  //获取拖拽单元格中的内容
            m_dragText = var.toString();
            qDebug()<<"m_dragText:"<<m_dragText;
            //m_dragPointAtItem = m_dragPoint - QPoint((index.row()%4)*m_cellWidet,(index.row()/4)*m_cellHeight); //获取拖拽点在该单元格的相对位置
            m_rowFrom = index.row()/4;      //记录移动的起始行列号
            m_columnFrom = index.row()%4;
            m_cellFrom = index.row();
        }
    }
    else if (e->button() == Qt::RightButton) //右键弹出设置菜单
    {
        //待实现
    }
    QListView::mousePressEvent(e);
}

void ListViewCustom::mouseMoveEvent(QMouseEvent *e)
{
    if(!m_editMode)
        return;
    if (!m_validPress)
        return;
    if (!(e->buttons() & Qt::LeftButton))
        return;
    if ((e->pos() - m_dragPoint).manhattanLength()  < QApplication::startDragDistance())  //拖动量过小不进行拖动操作
        return;

    m_label->show();
    doDrag();           //开始拖拽，完成拖拽后才会继续往下走
    m_label->hide();
    m_validPress = false;
}

void ListViewCustom::doDrag()
{
    //[1]把拖拽数据放在QMimeData容器中
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    mimeData->setText(m_dragText);
    drag->setMimeData(mimeData);

    //[2]设置拖拽时的缩略图
    RecordSequenceFile *record = new RecordSequenceFile;
    QVector<QMap<QString,QString>> dataVector = record->shortcutShowVector;
    QString iconPath = dataVector.at(m_cellFrom).begin().value();
    m_thumbnailImg.load(iconPath);
    m_thumbnailImg = m_thumbnailImg.scaled(25, 25, Qt::KeepAspectRatio);

    drag->setPixmap(m_thumbnailImg);
    QPoint hotspot(25,25);
    drag->setHotSpot(hotspot);  //鼠标在拖动期间在pixmap上的位置

    //***注意：此句会阻塞，进入drag的拖拽消息循环，会依次触发dragEnterEvent、dragMoveEvent、dropEvent消息
    if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
    {
        // 确认移动操作
    }
}

void ListViewCustom::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasText())
    {
        e->acceptProposedAction();
    }
    else
    {
        e->ignore();
        QListView::dragEnterEvent(e);
    }
}

void ListViewCustom::dragMoveEvent(QDragMoveEvent *e)
{
    if(e->mimeData()->hasText())
    {
        int curRow = 0;
        int curColumn = 0;
        QModelIndex index = QListView::indexAt(e->pos());
        //获取目标点的行列号
        if (index.isValid())
        {
            if(e->pos().x() - (index.row()%4)*m_cellWidet >= m_cellWidet){
                curColumn = (index.row()%4) + 1;
            }
            else{
                curColumn = index.row()%4;
            }

            if(e->pos().y() - (index.row()/4)*m_cellHeight >= m_cellHeight)
            {
                curRow = (index.row()/4) + 1;
            }
            else
            {
                curRow = index.row()/4;
            }
        }
        else
        {
            curColumn = 0;
            curRow = 0;
        }
        //更新目标指示线的位置
        //if (curRow != m_rowFrom || curColumn != m_columnFrom) //加上这个判断的话，在自己单元格移动将不显示指示标
        {
            m_rowTo = curRow;
            m_columnTo = curColumn;
            m_label->setGeometry(curColumn*m_cellWidet, curRow*m_cellHeight,2,m_cellHeight);
        }
        e->acceptProposedAction();
        return;
    }
    e->ignore();
    QListView::dragMoveEvent(e);
}

void ListViewCustom::dropEvent(QDropEvent *e)
{
    if(e->mimeData()->hasText())
    {
        if (m_rowTo != m_rowFrom || m_columnTo != m_columnFrom)
        {
            //moveRow(mRowFrom, mRowTo);
            moveRow(m_rowFrom, m_columnFrom, m_rowTo, m_columnTo);
        }
        e->acceptProposedAction();
        return;
    }
    e->ignore();
    QListView::dropEvent(e);
}

void ListViewCustom::resetOrder()
{

}

void ListViewCustom::moveRow(int from, int to)
{

}

void ListViewCustom::moveRow(int rowFrom, int columnFrom, int rowTo, int columnTo)
{
    qDebug()<<"---";
    qDebug()<<"RowFrom : ColumnFrom "<<rowFrom <<" : " <<columnFrom;
    qDebug()<<"RowTo : ColumnTo "<<rowTo <<" : " <<columnTo;
    if(rowFrom==rowTo && columnFrom==columnTo){
        return;
    }
    //移动行思路：将Vector中的数据重新排列，然后清空模型，再讲Vector中的数据添加进去
    //->
    //[1]重新排序
    static RecordSequenceFile *record = new RecordSequenceFile();
    QVector<QMap<QString,QString>> vectorData = record->shortcutShowVector;
    if(rowFrom > rowTo || columnFrom > columnTo)  //后面移到前面，先删除后插入
    {
        qDebug()<<"先删除后插入";
        //删除
        uint num = rowFrom*4+columnFrom;
        QMap<QString,QString> tmpMap = vectorData.at(num);
        vectorData.remove(num);
        //插入
        num = rowTo*4+columnTo;
        vectorData.insert(num, tmpMap);
    }
    else  //前面移动后面，先插入后删除
    {
        qDebug()<<"先插入后删除";
        //插入
        uint numFrom = rowFrom*4+columnFrom;
        QMap<QString,QString> tmpMap = vectorData.at(numFrom);
        uint numTo = rowTo*4+columnTo;
        vectorData.insert(numTo,tmpMap);
        //删除
        vectorData.remove(numFrom);
    }
    //[2]清空模型，再将数据重新添加到模型中
    QStringList dataList;
    for (int i = 0; i < vectorData.size(); ++i) {
        dataList << vectorData.at(i).begin().key();
    }
    m_model->setStringList(dataList);

    emit sigRowChange(m_rowFrom*4+m_columnFrom,m_rowTo*4+m_columnTo);
}
