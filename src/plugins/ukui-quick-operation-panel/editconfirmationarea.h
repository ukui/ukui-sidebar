#ifndef EDITCONFIRMATIONAREA_H
#define EDITCONFIRMATIONAREA_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>

class EditConfirmationArea : public QWidget
{
    Q_OBJECT
public:
    explicit EditConfirmationArea(QWidget *parent = nullptr);
    void   initMemberVariables();
    void   initLayout();
public:
    QPushButton     *m_pAddButton;
    QPushButton     *m_pCompleteAreaButton;
    QLabel          *m_pUnfoldIconLabel;
    QHBoxLayout     *m_pHboxAreaLayout;

Q_SIGNALS:

};

#endif // EDITCONFIRMATIONAREA_H
