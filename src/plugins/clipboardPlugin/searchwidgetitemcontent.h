#ifndef SEARCHWIDGETITEMCONTENT_H
#define SEARCHWIDGETITEMCONTENT_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QAction>
#include "clipboardwidgetentry.h"
class SearchWidgetItemContent:public QWidget
{
    Q_OBJECT
public:
    SearchWidgetItemContent();
    QPushButton *m_pClearTextEdit;
    QPushButton *m_pClearListWidgetButton;
    QLineEdit   *m_pLineEditArea;
    QHBoxLayout *m_pHBoxLayout;
};

#endif // SEARCHWIDGETITEMCONTENT_H
