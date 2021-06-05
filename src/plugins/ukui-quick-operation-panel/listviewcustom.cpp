#include "listviewcustom.h"
#include "recordsequencefile.h"
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QPainter>
#include <QHeaderView>
#include <QDebug>
#include <QVariant>
#include <shortcutinterface.h>
#include <QMetaType>
#include <QObject>
#include "listviewdelegate.h"

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
    m_validRelease = true;
    m_rowFrom = 0;
    m_rowTo = 0;
    m_cellFrom = 0;

    //设置ListView属性      实现流式布局和多列效果
    this->setViewMode(QListView::IconMode);//多列效果
    this->setFlow(QListView::LeftToRight);
    this->setResizeMode(QListView::Adjust);//自动换行
    //this->setLayoutMode(QListView::Batched);
    this->setEditTriggers(QListView::NoEditTriggers);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    const QSize size(m_cellWidet,m_cellHeight);    //设置网格大小
    this->setGridSize(size);
    this->setFrameShape(QListView::NoFrame);


    this->setMouseTracking(true);

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
        qDebug()<<"index.isValid():"<<index.isValid();
        qDebug()<<"index.row():"<<index.row();
        if (index.isValid())
        {
            m_validPress = true;
            m_dragPoint = e->pos(); //记录按下时位置
            QVariant var= m_model->data(index,Qt::EditRole);  //获取拖拽单元格中的内容
            m_cellName = var.toString();
            qDebug()<<"m_cellName:"<<m_cellName;
            //m_dragPointAtItem = m_dragPoint - QPoint((index.row()%4)*m_cellWidet,(index.row()/4)*m_cellHeight); //获取拖拽点在该单元格的相对位置
            m_rowFrom = index.row()/4;      //记录移动的起始行列号
            m_columnFrom = index.row()%4;
            m_cellFrom = index.row();
        }
        else{
            m_cellName.clear();
        }
    }
    else if (e->button() == Qt::RightButton) //右键弹出设置菜单
    {
        //待实现
    }
    QListView::mousePressEvent(e);
}

void ListViewCustom::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton && m_validRelease){
        qDebug()<<"鼠标左键释放...";
        if(!m_cellName.isEmpty()){
            //shortcutFunction(m_cellName); //动态创建该快捷键对象，并执行快捷操作
            emit clickBtn(m_cellName);
        }

    }
    else if(e->button() == Qt::RightButton && m_validRelease){
        qDebug()<<"鼠标右键释放...";
    }
    m_validRelease = true;
}

void ListViewCustom::leaveEvent(QEvent *e)
{
    emit mouseLeave(true);
}

void ListViewCustom::mouseMoveEvent(QMouseEvent *e)
{
    QModelIndex index = QListView::indexAt(e->pos());
    emit hoverIndexChanged(index);
    qDebug()<<"鼠标移动："<<index.row();


    if(!m_editMode)
        return;
    if (!m_validPress){
        return;
    }
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
    RecordSequenceFile *record = RecordSequenceFile::getInstance();
    QVector<QMap<QString,QString>> dataVector = record->getShortcutShowVector();
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
    m_validRelease = false;
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

void ListViewCustom::moveRow(int rowFrom, int columnFrom, int rowTo, int columnTo)
{
    qDebug()<<"---";
    qDebug()<<"RowFrom : ColumnFrom "<<rowFrom <<" : " <<columnFrom;
    qDebug()<<"RowTo : ColumnTo "<<rowTo <<" : " <<columnTo;
    if(rowFrom==rowTo && columnFrom==columnTo){
        return;
    }
    //移动行思路：将Vector中的数据重新排列，然后清空模型，再讲Vector中的数据添加进去
    //[1]重新排序
    static RecordSequenceFile *record = RecordSequenceFile::getInstance();
    QVector<QMap<QString,QString>> vectorData = record->getShortcutShowVector();
    if(rowFrom > rowTo || columnFrom > columnTo)  //后面移到前面，先删除后插入
    {
        //删除
        uint num = rowFrom*4+columnFrom;
        QMap<QString,QString> tmpMap = vectorData.at(num);
        vectorData.remove(num);
        //插入
        num = rowTo*4+columnTo;
        vectorData.insert(num, tmpMap);

        emit record->orderChange(vectorData);
    }
    else  //前面移动后面，先插入后删除
    {
        //插入
        uint numFrom = rowFrom*4+columnFrom;
        QMap<QString,QString> tmpMap = vectorData.at(numFrom);
        uint numTo = rowTo*4+columnTo;
        vectorData.insert(numTo,tmpMap);
        //删除
        vectorData.remove(numFrom);
        emit record->orderChange(vectorData);
    }
    //[2]清空模型，再将数据重新添加到模型中
    QStringList dataList;
    for (int i = 0; i < vectorData.size(); ++i) {
        dataList << vectorData.at(i).begin().key();
    }
    m_model->setStringList(dataList);

    m_validRelease = true;
    qDebug()<<"------->m_validRelease:"<<m_validRelease;
    emit sigRowChange(m_rowFrom*4+m_columnFrom,m_rowTo*4+m_columnTo);
}


void ListViewCustom::shortcutFunction(QString name)
{
    //反射实现：根据类名字符串将其实例化，方便动态创建
    //工厂模式:使用工厂具体快捷键类的抽象化
    static RecordSequenceFile *record = RecordSequenceFile::getInstance();
    QMap<QString,QString>::iterator iter =  record->m_shortcutClassName.find(name);
    QString className = iter.value();
    className += "*";
    int id = QMetaType::type(className.toLatin1()); //根据类名获取id号
    const QMetaObject *metaObj = QMetaType::metaObjectForType(id); //获取该类的元对象
    QObject *obj = metaObj->newInstance(Q_ARG(QObject*, nullptr));
    ShortcutInterface *instence = qobject_cast<ShortcutInterface*>(obj);
    instence->action();
}
