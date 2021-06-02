#ifndef TABLEVIEWCUSTOM_H
#define TABLEVIEWCUSTOM_H

#include <QTableView>
#include <QLabel>
#include <QMouseEvent>
#include <QStandardItemModel>

class TableViewCustom : public QTableView
{
    Q_OBJECT
public:
    TableViewCustom(QWidget *parent = Q_NULLPTR);

    //此函数包装了自带的setModel，只是记录了model指针方便内部调用
    void SetModel(QStandardItemModel *model);

Q_SIGNALS:
    //拖拽结束后会发出此信号，可绑定槽函数实现你的其他功能，比如把新的顺序存到文件
    void sigRowChange(int from, int to);

protected:
    //根据鼠标事件开启拖拽
    void mousePressEvent ( QMouseEvent * event ) ;
    void mouseMoveEvent(QMouseEvent *event);

    //拖拽响应事件
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

private:
    void DoDrag();                      //执行拖拽
    void ResetOrder();                  //重置第一列序号
    void MoveRow(int from, int to);     //真正执行移动行的功能
    void MoveRow(int RowFrom, int ColumnFrom, int RowTo, int ColumnTo);

private:
    QStandardItemModel *mModel;
    QLabel* mLabel;             //高度设为2，用做指示线
    int mRowHeight;             //表格的行高
    int mColumnWidet;

    bool mValidPress;           //在鼠标移动时，判断之前按下时是否是在有效行上
    int mRowFrom;				//拖动起始行
    int mColumnFrom;

    int mRowTo;                 //拖动时(还没松开时)鼠标位置代表的行，会绘制一条指示线，类似QQ好友列表拖拽效果
    int mColumnTo;

    QPixmap pix;
    QString mDragText;          //拖拽过程中跟随鼠标显示的内容
    QPoint mDragPoint;          //拖拽起点
    QPoint mDragPointAtItem;    //记录按下时鼠标相对该行的位置，在拖动过程中保持该相对位置

};

#endif // MYTABLEVIEW_H
