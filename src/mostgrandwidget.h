#ifndef MOSTGRANDWIDGET_H
#define MOSTGRANDWIDGET_H

#include <QtWidgets>
#include <QWidget>
#include <QVBoxLayout>
#include <QObject>

class mostGrandWidget : public QWidget
{
    Q_OBJECT
public:
    mostGrandWidget(QWidget *parent = nullptr);
    ~mostGrandWidget();

    static void mostGrandWidgetInit();
    static mostGrandWidget* getInstancemostGrandWidget();
    void LaoutSidebarWidget();
    void setMostGrandwidgetSize(int w, int h);
    void setMostGrandwidgetCoordinates(int x, int y);
    QVBoxLayout *m_pmostGrandWidgetVLaout;
};

#endif // MOSTGRANDWIDGET_H
