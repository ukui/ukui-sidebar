#ifndef CLIPBOARDWIDGETENTRY_H
#define CLIPBOARDWIDGETENTRY_H
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QIcon>
#define  EDIT_SVG_PATH  ":/image/编辑.svg"
#define  COPY_SVG_PATH  ":/image/复制.svg"
#define  REMOVE_SVG_PATH  ":/image/删除.svg"
class ClipboardWidgetEntry : public QWidget
{
public:
    ClipboardWidgetEntry(QWidget *parent = nullptr);
    QPushButton *m_pPopButton;
    QPushButton *m_pEditButon;
    QPushButton *m_pRemoveButton;
    QLabel      *m_pCopyDataLabal;
    QHBoxLayout *m_pHLayout;
};

#endif // CLIPBOARDWIDGETENTRY_H
