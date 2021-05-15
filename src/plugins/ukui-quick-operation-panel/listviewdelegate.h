#ifndef LISTVIEWDELEGATE_H
#define LISTVIEWDELEGATE_H
#include <QItemDelegate>
#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QStandardItemModel>

class ListViewDelegate : public QItemDelegate
{
public:
    ListViewDelegate(QObject *parent = 0);
    ~ListViewDelegate();

    //重写重画函数
    void paint(QPainter * painter,const QStyleOptionViewItem & option,const QModelIndex & index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;


//    QWidget *createEditor(QWidget *parent,const QStyleOptionViewItem &option,
//                          const QModelIndex &index) const override;
//    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
//    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
//    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,
//                              const QModelIndex &index) const override;

};

#endif // LISTVIEWDELEGATE_H
