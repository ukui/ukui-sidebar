#ifndef LISTVIEWCUSTOM_H
#define LISTVIEWCUSTOM_H
#include <QListView>
#include <QLabel>
#include <QMouseEvent>
#include <QStringListModel>

class ListViewCustom : public QListView
{
    Q_OBJECT
public:
    ListViewCustom(QWidget *parent = Q_NULLPTR);
    //此函数包装了自带的setModel，只是记录了model指针方便内部调用
    void SetModel(QStringListModel *model);
Q_SIGNALS:
    //拖拽结束后会发出此信号，可绑定槽函数实现你的其他功能，比如把新的顺序存到文件
    void sigRowChange(int from, int to);

protected:
    //根据鼠标事件开启拖拽
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

    //拖拽响应事件
    void dragEnterEvent(QDragEnterEvent *e);
    void dragMoveEvent(QDragMoveEvent *e);
    void dropEvent(QDropEvent *e);
private:
    void doDrag();                      //执行拖拽
    void resetOrder();                  //重置第一列序号
    void moveRow(int RowFrom, int ColumnFrom, int RowTo, int ColumnTo);//真正执行拖拽排序的功能

private:
    bool m_editMode;

    QStringListModel *m_model;
    QLabel* m_label;             //高度设为2，用做目标位置指示线(拖动时(还没松开时)鼠标位置代表的行，会绘制一条指示线)
    uint m_cellHeight;             //表格的行高列宽
    uint m_cellWidet;

    bool m_validPress;           //在鼠标移动时，判断之前按下时是否是在有效行上

    uint m_rowFrom;				//拖动起始位置行列号
    uint m_columnFrom;
    uint m_cellFrom;

    uint m_rowTo;                 //拖拽目标位置的行列号
    uint m_columnTo;

    QPixmap m_thumbnailImg;      //拖拽缩略图
    QString m_dragText;          //拖拽过程中跟随鼠标显示的内容
    QPoint m_dragPoint;          //拖拽起点
    QPoint m_dragPointAtItem;    //记录按下时鼠标相对该行的位置，在拖动过程中保持该相对位置
};

#endif // LISTVIEWCUSTOM_H
