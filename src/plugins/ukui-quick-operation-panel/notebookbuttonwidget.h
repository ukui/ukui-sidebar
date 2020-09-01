#ifndef NOTEBOOKBUTTONWIDGET_H
#define NOTEBOOKBUTTONWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QProcess>
#include "switchbutton.h"
#include "customstyle_switchNormalStatus.h"

#define KYLIN_BLUETOOTH_NORMAL_NAME     "kylin-icon-notes"
#define KYLIN_BLUETOOTH_SET_NAME        "kylin-icon-notes-s"

#define KYLIN_BLUETOOTH_NORMAL_PATH     ":/images/icon-notes.svg"
#define KYLIN_BLUETOOTH_SET_PATH        ":/images/icon-notes-s.svg"

class notebookButtonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit notebookButtonWidget(QWidget *parent = nullptr);

private:
    void initMemberVariables();
    void initLayout();

private:
    QWidget         *m_pButtonWidget;
    QPushButton     *m_pNoteButton;
    QLabel          *m_pNoteLabel;

    QVBoxLayout     *m_pVboxButtonLayout;
    QVBoxLayout     *m_pVboxLayout;

    QStyle          *m_pStyleNormal;

private slots:
    void NoteButtonClickSlots();

Q_SIGNALS:

};

#endif // NOTEBOOKBUTTONWIDGET_H
