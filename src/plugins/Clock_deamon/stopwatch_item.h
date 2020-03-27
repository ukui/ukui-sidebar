#ifndef STOPWATCH_ITEM_H
#define STOPWATCH_ITEM_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class stopwatch_item;
}

class stopwatch_item : public QWidget
{
    Q_OBJECT

public:
    explicit stopwatch_item(QWidget *parent = nullptr);
    ~stopwatch_item();
    void setupUi(QWidget *stopwatch_item);
    void retranslateUi(QWidget *stopwatch_item);

    QLabel *stopwatch1;
    QLabel *stopwatch2;
    QLabel *stopwatch3;

    QFrame *stopwatch_line;

private:
    Ui::stopwatch_item *ui;
};

#endif // STOPWATCH_ITEM_H
