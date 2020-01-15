#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QWidget>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QGroupBox>
#include <QLabel>
#include <QFont>
#include <QGuiApplication>
#include <QScreen>
#include <QRect>
#include <QDebug>
class EditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EditorWidget();
    QPushButton  *m_pConfirmButton;
    QPushButton  *m_pCancelButton;
    QTextEdit    *m_pEditingArea;
    QLabel       *m_ptileLable;
    QGroupBox    *m_pTitleBox;
    QGroupBox    *m_pEditBox;
    QGroupBox    *m_pOperationBox;
    QVBoxLayout  *m_pMainQVBoxLayout;                                     //主界面垂直布局器
    QHBoxLayout  *m_ptileLayout;
    QHBoxLayout  *m_pEditLaout;
    QHBoxLayout  *m_pOperationLayout;

    void titleBox();
    void editBox();
    void operationBox();
};

#endif // EDITORWIDGET_H
