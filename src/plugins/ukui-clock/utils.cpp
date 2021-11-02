#include "utils.h"

Utils::Utils()
{

}
/**
 * @brief 移到鼠标所在屏幕中央。兼容990
 */
void Utils::centerToScreen(QWidget *widget)
{
    if (!widget)

       return;

     QDesktopWidget* m = QApplication::desktop();

     QRect desk_rect = m->screenGeometry(m->screenNumber(QCursor::pos()));

     int desk_x = desk_rect.width();

     int desk_y = desk_rect.height();

     int x = widget->width();

     int y = widget->height();

     widget->move(desk_x / 2 - x / 2 + desk_rect.left(), desk_y / 2 - y / 2 + desk_rect.top());
}


