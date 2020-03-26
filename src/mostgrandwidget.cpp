#include "mostgrandwidget.h"

static mostGrandWidget* global_Most_Grand_Widgets_instance = nullptr;

mostGrandWidget::mostGrandWidget(QWidget *parent)
{
    Q_UNUSED(parent)
    this->setContentsMargins(0,0,0,0);
    m_pmostGrandWidgetVLaout = new QVBoxLayout();
    m_pmostGrandWidgetVLaout->setContentsMargins(0,0,0,0);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
}

mostGrandWidget::~mostGrandWidget()
{

}

void mostGrandWidget::mostGrandWidgetInit()
{
    mostGrandWidget::getInstancemostGrandWidget();
    return;
}

mostGrandWidget* mostGrandWidget::getInstancemostGrandWidget()
{
    if (global_Most_Grand_Widgets_instance == nullptr) {
        global_Most_Grand_Widgets_instance = new mostGrandWidget();
    }
    return global_Most_Grand_Widgets_instance;
}

/* last Laout MostGrand Widget */
void mostGrandWidget::LaoutSidebarWidget()
{
    this->setLayout(m_pmostGrandWidgetVLaout);
    return;
}

void mostGrandWidget::setMostGrandwidgetSize(int w, int h)
{
    this->setFixedSize(w,h);
    return;
}

void mostGrandWidget::setMostGrandwidgetCoordinates(int x, int y)
{
    this->move(x, y);
    return;
}
