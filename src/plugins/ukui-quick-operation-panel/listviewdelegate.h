#ifndef LISTVIEWDELEGATE_H
#define LISTVIEWDELEGATE_H
#include <QItemDelegate>
#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QStandardItemModel>
#include <QObject>

class ListViewDelegate : public QItemDelegate
{
public:
    ListViewDelegate(QObject *parent = 0);
    ~ListViewDelegate();

    //重写重画函数
    virtual void paint(QPainter * painter,const QStyleOptionViewItem & option,const QModelIndex & index) const;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual bool editorEvent(QEvent *event,QAbstractItemModel *model,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index);
    virtual void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;
    virtual bool eventFilter(QObject *object, QEvent *event);
    virtual void drawFocus(QPainter *painter, const QStyleOptionViewItem &option,
                           const QRect &rect) const;

//    QWidget *createEditor(QWidget *parent,const QStyleOptionViewItem &option,
//                          const QModelIndex &index) const override;
//    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
//    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
//    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,
//                              const QModelIndex &index) const override;

public slots:
    void onHoverIndexChanged(const QModelIndex& index);

private:
    int m_hoverRow;
    bool hoverStatus;

};

#endif // LISTVIEWDELEGATE_H
