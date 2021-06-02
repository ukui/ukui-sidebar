#ifndef TABLEVIEWDELEGATE_H
#define TABLEVIEWDELEGATE_H
#include <QItemDelegate>
#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QStandardItemModel>

class TableViewDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit TableViewDelegate(QObject *parent = 0);
    ~TableViewDelegate();
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

#endif // TABLEVIEWDELEGATE_H





