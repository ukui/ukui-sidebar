/*
* Copyright (C) 2020 Tianjin KYLIN Information Technology Co., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, see <http://www.gnu.org/licenses/&gt;.
*
*/

#include <QStyleOptionToolButton>
#include <QPainter>
#include <QApplication>

#include "customStyle.h"

//#if QT_CONFIG(toolbutton)
static void drawArrow(const QStyle *style, const QStyleOptionToolButton *toolbutton,
                      const QRect &rect, QPainter *painter, const QWidget *widget = 0)
{
    QStyle::PrimitiveElement pe;
    switch (toolbutton->arrowType) {
    case Qt::LeftArrow:
        pe = QStyle::PE_IndicatorArrowLeft;
        break;
    case Qt::RightArrow:
        pe = QStyle::PE_IndicatorArrowRight;
        break;
    case Qt::UpArrow:
        pe = QStyle::PE_IndicatorArrowUp;
        break;
    case Qt::DownArrow:
        pe = QStyle::PE_IndicatorArrowDown;
        break;
    default:
        return;
    }
    QStyleOption arrowOpt = *toolbutton;
    arrowOpt.rect = rect;
    style->drawPrimitive(pe, &arrowOpt, painter, widget);
}
//#endif // QT_CONFIG(toolbutton)

CustomStyle::CustomStyle(const QString &proxyStyleName, QObject *parent) : QProxyStyle (proxyStyleName)
{

}
CustomStyle::~CustomStyle()
{
}
void CustomStyle::drawComBoxIndicator(SubControl which, const QStyleOptionComplex *option,
                                      QPainter *painter) const
{
    PrimitiveElement arrow=PE_IndicatorArrowDown;
    QRect buttonRect=option->rect.adjusted(+0,+0,-1,-1);
    buttonRect.translate(buttonRect.width()/2,0);
    buttonRect.setWidth((buttonRect.width()+1)/2);
    QStyleOption buttonOpt(*option);
    painter->save();
    painter->setClipRect(buttonRect,Qt::IntersectClip);
    if(!(option->activeSubControls&which))
        buttonOpt.state&=~(State_MouseOver|State_On|State_Sunken);
    QStyleOption arrowOpt(buttonOpt);
    arrowOpt.rect=subControlRect(CC_ComboBox,option,which).adjusted(+0,+0,-0,+0);
    if(arrowOpt.rect.isValid())
        proxy()->drawPrimitive(arrow,&arrowOpt,painter);
    painter->restore();
}
void CustomStyle::drawComplexControl(QStyle::ComplexControl cc, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const
{

    switch (cc) {
    case CC_ScrollBar:
    {
        if (const QStyleOptionSlider* slider = qstyleoption_cast<const QStyleOptionSlider *>(option)) {
            QStyleOptionSlider sr = *slider;
            sr.palette.setBrush(QPalette::WindowText,QColor("#778899"));
            return QProxyStyle::drawComplexControl(cc, &sr, painter, widget);
        } else {
            break;
        }
    }
    case CC_ComboBox:
    {
        if (const QStyleOptionComboBox* combobox = qstyleoption_cast<const QStyleOptionComboBox *>(option)) {
            if (!(option->state & State_Enabled)) {
                painter->save();
                painter->setPen(QColor("#cfcfcf"));
                painter->setBrush(Qt::white);
                painter->setRenderHint(QPainter::Antialiasing,true);
                painter->drawRoundedRect(option->rect,4,4);
                painter->restore();
                return;
            }

            QRectF rect=subControlRect(CC_ComboBox,option,SC_ComboBoxFrame);

            painter->save();
            painter->setPen(QColor("#cfcfcf"));
            //painter->setBrush(option->palette.color(QPalette::Button));
            painter->setBrush(Qt::white);
            painter->setRenderHint(QPainter::Antialiasing,true);
            painter->drawRoundedRect(rect,4,4);
            painter->restore();


            drawComBoxIndicator(SC_ComboBoxArrow,option,painter);


            if ((combobox->state & (State_Sunken | State_On)))

                if (combobox->state & State_MouseOver ) {
                    painter->save();
                    painter->setBrush(Qt::NoBrush);
                    painter->setPen(QColor("#3D6BE5"));
                    painter->setRenderHint(QPainter::Antialiasing,true);
                    // painter->setOpacity(opacity);
                    painter->drawRoundedRect(rect,4,4);
                    painter->restore();
                    return;
                }
            return;
        }
    }
    default:
        break;
    }
    return QProxyStyle::drawComplexControl(cc, option, painter, widget);
}

void CustomStyle::drawControl(QStyle::ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    switch(element){
    case CE_ComboBoxLabel: {
        auto comboBoxOption = qstyleoption_cast<const QStyleOptionComboBox*>(option);
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing,true);
        //        painter->setPen(option->palette.color(QPalette::ButtonText));
        painter->setPen(Qt::black);
        //选中颜色
        //        if (option->state & State_Selected) {
        //            if (option->state & State_Sunken) {
        //                painter->setPen(option->palette.color(QPalette::ButtonText));
        //            } else {
        //                painter->setPen(option->palette.color(QPalette::ButtonText));
        //            }
        //        }
        painter->drawText(option->rect.adjusted(+4,+0,+0,+0), comboBoxOption->currentText, QTextOption(Qt::AlignVCenter));
        painter->restore();
        return;
    }
        break;
    case CE_PushButton: {
        painter->save();
        painter->setRenderHint(QPainter::TextAntialiasing,true);
        painter->setPen(Qt::yellow);
        painter->setBrush(Qt::red);
        if (option->state & State_MouseOver) {
            if (option->state & State_Sunken) {
                painter->setRenderHint(QPainter::Antialiasing,true);
                painter->setPen(Qt::NoPen);
                painter->setBrush(Qt::white);
                painter->drawRoundedRect(option->rect,6,6);
            } else {
                painter->setRenderHint(QPainter::Antialiasing,true);
                painter->setPen(Qt::black);
                painter->setBrush(Qt::red);
                painter->drawRoundedRect(option->rect.adjusted(2,2,-2,-2),6,6);
            }
        }
        painter->restore();
        return;
    }
    default:
        return QProxyStyle::drawControl(element, option, painter, widget);
    }
    return QProxyStyle::drawControl(element, option, painter, widget);
}

void CustomStyle::drawItemPixmap(QPainter *painter, const QRect &rectangle, int alignment, const QPixmap &pixmap) const
{
    return QProxyStyle::drawItemPixmap(painter, rectangle, alignment, pixmap);
}

void CustomStyle::drawItemText(QPainter *painter, const QRect &rectangle, int alignment, const QPalette &palette, bool enabled, const QString &text, QPalette::ColorRole textRole) const
{
    return QProxyStyle::drawItemText(painter, rectangle, alignment, palette, enabled, text, textRole);
}

//绘制简单的颜色圆角等
void CustomStyle::drawPrimitive(QStyle::PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    switch (element) {
    case PE_PanelButtonCommand: {
        painter->save();
        painter->setRenderHint(QPainter::TextAntialiasing,true);
        painter->setPen(Qt::black);
        painter->setBrush(Qt::yellow);
        if (option->state & State_MouseOver) {
            if (option->state & State_Sunken) {
                painter->setRenderHint(QPainter::Antialiasing,true);
                painter->setPen(Qt::NoPen);
                painter->setBrush(Qt::white);
                painter->drawRoundedRect(option->rect,6,6);
            } else {
                painter->setRenderHint(QPainter::Antialiasing,true);
                painter->setPen(Qt::black);
                painter->setBrush(Qt::red);
                painter->drawRoundedRect(option->rect.adjusted(2,2,-2,-2),6,6);
            }
        }
        painter->restore();
        return;
    }
        break;
    case PE_FrameLineEdit: {
        // Conflict with qspinbox and so on, The widget text cannot use this style
        if (widget) {
            if (widget->parentWidget())
                if (widget->parentWidget()->inherits("QDoubleSpinBox")
                        |widget->parentWidget()->inherits("QSpinBox")
                        |widget->parentWidget()->inherits("QComboBox")) {
                    return;
                }
        }
        painter->save();
        if (const QStyleOptionFrame *panel = qstyleoption_cast<const QStyleOptionFrame *>(option)) {
            painter->setRenderHint(QPainter::Antialiasing,true);
            //Setpen is set to avoid a bug that collides with a white background
            painter->setPen(QColor("#CFCFCF"));
            //            painter->setBrush(option->palette.color(QPalette::Base));
            painter->setBrush(Qt::red);
            // if (panel->lineWidth > 0)
            // proxy()->drawPrimitive(PE_FrameLineEdit, panel, painter, widget);
            if (widget->isEnabled()) {
                if (option->state &State_MouseOver) {
                    painter->setBrush(option->palette.button().color().lighter());
                }
                if(option->state &State_HasFocus) {
                    painter->setPen(QColor("#3D6BE5"));
                    painter->setBrush(option->palette.color(QPalette::Base));
                }
            }
            painter->drawRoundedRect(panel->rect,4,4);
        }
        painter->restore();
        return;
    }
        break;
    case PE_PanelLineEdit: {
        painter->save();
        if (const QStyleOptionFrame *panel = qstyleoption_cast<const QStyleOptionFrame *>(option)) {
            painter->setRenderHint(QPainter::Antialiasing,true);
            //Setpen is set to avoid a bug that collides with a white background
            painter->setPen(QColor("#CFCFCF"));
            painter->setBrush(Qt::white);
            QPalette *palete=new QPalette();
            palete->setBrush(QPalette::Text, Qt::black);
            // if (panel->lineWidth > 0)
            // proxy()->drawPrimitive(PE_FrameLineEdit, panel, painter, widget);
            if (widget->isEnabled()) {
                if (option->state &State_MouseOver) {
                    //                    painter->setBrush(option->palette.button().color().lighter());
                    painter->setBrush(Qt::white);
                }
                if(option->state &State_HasFocus) {
                    painter->setPen(QColor("#3D6BE5"));
                    //                    painter->setBrush(option->palette.color(QPalette::Base));
                    painter->setBrush(Qt::white);
                }
            }
            painter->drawRoundedRect(panel->rect,4,4);
        }
        painter->restore();
        return;
    }
        break;
    case PE_IndicatorArrowDown:
    case PE_IndicatorArrowUp:
    case PE_IndicatorArrowLeft:
    case PE_IndicatorArrowRight: {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing,true);
        painter->setBrush(Qt::NoBrush);
        if(option->state & State_Enabled){
            painter->setPen(QPen(Qt::black, 1.2));
            if (option->state & State_MouseOver) {
                painter->setPen(QPen(Qt::black, 1.2));
            }
        }
        else {
            painter->setPen(QPen(option->palette.color(QPalette::Text), 1.1));
        }

        QPolygon points(4);
        int x = option->rect.x();
        int y = option->rect.y();
        //If the height is too high, the arrow will be very ugly. If the height is too small, the arrow will not be painted
        //         int w = option->rect.width() / 3;
        //         int h =  option->rect.height() / 4;
        int w = 8;
        int h =  4;
        x += (option->rect.width() - w) / 2;
        y += (option->rect.height() - h) / 2;

        //When the arrow is too small, you can not draw
        if (option->rect.width() - w < 1 || option->rect.height() - h < 1) {
            return;
        } else if (option->rect.width() - w <= 2 || option->rect.height() - h <= 2) {
            w = 5;
            h =  3;
        }
        if (element == PE_IndicatorArrowDown) {
            points[0] = QPoint(x-4, y);
            points[1] = QPoint(x-4 + w / 2, y + h);
            points[2] = QPoint(x-4 + w / 2, y + h);
            points[3] = QPoint(x-4 + w, y);
        } else if (element == PE_IndicatorArrowUp) {
            points[0] = QPoint(x, y + h);
            points[1] = QPoint(x + w / 2, y);
            points[2] = QPoint(x + w / 2, y);
            points[3] = QPoint(x + w, y + h);
        } else if (element == PE_IndicatorArrowLeft) {
            points[0] = QPoint(x + h , y);
            points[1] = QPoint(x, y+w/2);
            points[2] = QPoint(x, y+w/2);
            points[3] = QPoint(x + w , y + w);
        } else if (element == PE_IndicatorArrowRight) {
            points[0] = QPoint(x , y);
            points[1] = QPoint(x+h, y+w/2);
            points[2] = QPoint(x+h , y+w/2);
            points[3] = QPoint(x, y+w);
        }
        painter->drawLine(points[0],  points[1] );
        painter->drawLine(points[2],  points[3] );
        painter->restore();
        return;
    }
    default:
        return QProxyStyle::drawPrimitive(element, option, painter, widget);
    }
    return QProxyStyle::drawPrimitive(element, option, painter, widget);
}

QPixmap CustomStyle::generatedIconPixmap(QIcon::Mode iconMode, const QPixmap &pixmap, const QStyleOption *option) const
{
    return QProxyStyle::generatedIconPixmap(iconMode, pixmap, option);
}

QStyle::SubControl CustomStyle::hitTestComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex *option, const QPoint &position, const QWidget *widget) const
{
    return QProxyStyle::hitTestComplexControl(control, option, position, widget);
}

QRect CustomStyle::itemPixmapRect(const QRect &rectangle, int alignment, const QPixmap &pixmap) const
{
    return QProxyStyle::itemPixmapRect(rectangle, alignment, pixmap);
}

QRect CustomStyle::itemTextRect(const QFontMetrics &metrics, const QRect &rectangle, int alignment, bool enabled, const QString &text) const
{
    return QProxyStyle::itemTextRect(metrics, rectangle, alignment, enabled, text);
}

int CustomStyle::pixelMetric(QStyle::PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
    switch (metric){
    case PM_ToolBarIconSize:{
        return (int)48*qApp->devicePixelRatio();
    }
    default:
        break;
    }
    return QProxyStyle::pixelMetric(metric, option, widget);
}

void CustomStyle::polish(QWidget *widget)
{
    widget->setAttribute(Qt::WA_Hover);
    auto palette = widget->palette();
    polish(palette);
    widget->setPalette(palette);
    return QProxyStyle::polish(widget);
}

void CustomStyle::polish(QApplication *application)
{
    return QProxyStyle::polish(application);
}

void CustomStyle::polish(QPalette &palette)
{
    palette.setBrush(QPalette::Text, Qt::black);
    palette.setBrush(QPalette::Base, Qt::white);
}

void CustomStyle::unpolish(QWidget *widget)
{
    return QProxyStyle::unpolish(widget);
}

void CustomStyle::unpolish(QApplication *application)
{
    return QProxyStyle::unpolish(application);
}

QSize CustomStyle::sizeFromContents(QStyle::ContentsType type, const QStyleOption *option, const QSize &contentsSize, const QWidget *widget) const
{
    return QProxyStyle::sizeFromContents(type, option, contentsSize, widget);
}

QIcon CustomStyle::standardIcon(QStyle::StandardPixmap standardIcon, const QStyleOption *option, const QWidget *widget) const
{
    return QProxyStyle::standardIcon(standardIcon, option, widget);
}

QPalette CustomStyle::standardPalette() const
{
    return QProxyStyle::standardPalette();
}

//如果需要背景透明也许需要用到这个函数
int CustomStyle::styleHint(QStyle::StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
{
    switch (hint) {
    /// 让ScrollView viewport的绘制区域包含scrollbar和corner widget
    /// 这个例子中没有什么作用，如果我们需要绘制一个背景透明的滚动条
    /// 这个style hint对我们的意义应该很大，因为我们希望视图能够帮助
    /// 我们填充滚动条的背景区域，否则当背景透明时底下会出现明显的分割
    case SH_ScrollView_FrameOnlyAroundContents: {
        return false;
    }
    default:
        break;
    }
    return QProxyStyle::styleHint(hint, option, widget, returnData);
}

QRect CustomStyle::subControlRect(QStyle::ComplexControl control, const QStyleOptionComplex *option, QStyle::SubControl subControl, const QWidget *widget) const
{
    return QProxyStyle::subControlRect(control, option, subControl, widget);
}

QRect CustomStyle::subElementRect(QStyle::SubElement element, const QStyleOption *option, const QWidget *widget) const
{
    return QProxyStyle::subElementRect(element, option, widget);
}

