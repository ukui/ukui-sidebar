#ifndef POPMENU_H
#define POPMENU_H
#include <QObject>
#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QGSettings>

#define SETTING_ICON    ":/images/icon-setting.svg"
#define SETTING_NAME    "Setting"
#define EDIT_ICON       ":/images/icon-sedit.svg"
#define EDIT_NAME       "Edit"

#define UKUI_TRANSPARENCY_SETTING "org.ukui.control-center.personalise"

class PopMenu : public QMenu
{
    Q_OBJECT
public:
    PopMenu(QWidget *parent = nullptr);
    void createAction();
    void getTransParency();
    void setTransParency();
    void paintEvent(QPaintEvent *event);

private:
    QGSettings *m_pTransparency;
    double      m_dtranSparency;
};

#endif // POPMENU_H
