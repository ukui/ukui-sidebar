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

#define KYLIN_BLUETOOTH_NORMAL_NAME     "kylin-bluetooth-normal"
#define KYLIN_BLUETOOTH_HOVER_NAME      "kylin-bluetooth-hover"
#define KYLIN_BLUETOOTH_PRESS_NAME      "kylin-bluetooth-pressed"

#define KYLIN_BLUETOOTH_NORMAL_PATH     ":/image/bluetooth-normal.svg"
#define KYLIN_BLUETOOTH_HOVER_PATH      ":/image/bluetooth-hover.svg"
#define KYLIN_BLUETOOTH_PRESS_PATH      ":/image/bluetooth-pressed.svg"

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
    switchButton    *m_pNoteButton;
    QLabel          *m_pNoteLabel;

    QVBoxLayout     *m_pVboxButtonLayout;
    QVBoxLayout     *m_pVboxLayout;

    QStyle          *m_pStyleNormal;

    QStringList      m_IconPathList;
    QStringList      m_IconNameList;

private slots:
    void NoteButtonClickSlots();

Q_SIGNALS:

};

#endif // NOTEBOOKBUTTONWIDGET_H
