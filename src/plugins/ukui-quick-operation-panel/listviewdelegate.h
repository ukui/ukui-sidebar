#ifndef LISTVIEWDELEGATE_H
#define LISTVIEWDELEGATE_H
#include <QItemDelegate>
#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QStandardItemModel>
#include <QObject>
#include <QGSettings>

#define NIGHT_MODE_KEY        "nightmodestatus"
#define NIGHT_MODE_LIGHT      "light"
#define NIGHE_MODE_NIGHT      "night"
#define NIGHT_MODE_CONTROL    "org.ukui.control-center.panel.plugins"

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

Q_SIGNALS:
    void test();

public slots:
    void onHoverIndexChanged(const QModelIndex& index);

private:
    int m_hoverRow;
    QGSettings    *m_pTabletModeGsetting = nullptr;
    bool m_bModelStatus;

};

#endif // LISTVIEWDELEGATE_H
