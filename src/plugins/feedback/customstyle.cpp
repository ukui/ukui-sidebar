/*
 * Copyright (C) 2019 Tianjin KYLIN Information Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2.1, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/&gt;.
 *
 */

#include "customstyle.h"

#include <QStyleOptionToolButton>
#include <QPainter>
#include <QApplication>

#if QT_CONFIG(toolbutton)
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
#endif // QT_CONFIG(toolbutton)

CustomStyle::CustomStyle(const QString &proxyStyleName, QObject *parent) : QProxyStyle (proxyStyleName)
{

}
CustomStyle::~CustomStyle()
{
};

void CustomStyle::drawComplexControl(QStyle::ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p, const QWidget *widget) const
{

    //    if(control == CC_ToolButton)
    //    {
    //        /// 我们需要获取ToolButton的详细信息，通过qstyleoption_cast可以得到
    //        /// 对应的option，通过拷贝构造函数得到一份备份用于绘制子控件
    //        /// 我们一般不用在意option是怎么得到的，大部分的Qt控件都能够提供了option的init方法

    //    }

    return QProxyStyle::drawComplexControl(cc, opt, p, widget);
}

void CustomStyle::drawControl(QStyle::ControlElement element, const QStyleOption *opt, QPainter *p, const QWidget *widget) const
{
    return QProxyStyle::drawControl(element, opt, p, widget);
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
    //绘制 ToolButton
    case PE_PanelButtonTool:{
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing,true);
        painter->setPen(Qt::NoPen);
        //        painter->setBrush(QColor(0xff,0xff,0xff,0xff));
        painter->drawRoundedRect(option->rect,6,6);
        if (option->state & State_MouseOver) {
            if (option->state & State_Sunken) {
                painter->setRenderHint(QPainter::Antialiasing,true);
                painter->setPen(Qt::NoPen);
                painter->setBrush(QColor(0xff,0xff,0xff,0x0f));
                painter->drawRoundedRect(option->rect,6,6);
            } else {
                painter->setRenderHint(QPainter::Antialiasing,true);
                painter->setPen(Qt::NoPen);
                painter->setBrush(QColor(0xff,0xff,0xff,0x1f));
                painter->drawRoundedRect(option->rect.adjusted(2,2,-2,-2),6,6);
            }
        }
        painter->restore();
        return;
    }break;

    case PE_PanelButtonCommand:{
        painter->save();
        painter->setRenderHint(QPainter::TextAntialiasing,true);
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::blue);
        if (option->state & State_MouseOver) {
            if (option->state & State_Sunken) {
                painter->setRenderHint(QPainter::Antialiasing,true);
                painter->setPen(Qt::NoPen);
                painter->setBrush(QColor(0xff,0x00,0x00));
                painter->drawRoundedRect(option->rect,6,6);
            } else {
                painter->setRenderHint(QPainter::Antialiasing,true);
                painter->setPen(Qt::NoPen);
                painter->setBrush(QColor(0x00,0xff,0x00));
                painter->drawRoundedRect(option->rect.adjusted(2,2,-2,-2),6,6);
            }
        }
        painter->restore();
        return;
    }break;

    case PE_FrameLineEdit://UKUI Line edit style
    {
        // Conflict with qspinbox and so on, The widget text cannot use this style
        if (widget) {
            if (widget->parentWidget())
                if (widget->parentWidget()->inherits("QDoubleSpinBox")|widget->parentWidget()->inherits("QSpinBox")|widget->parentWidget()->inherits("QComboBox")) {
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
    }break;



    case PE_PanelLineEdit://UKUI Line edit style
    {
        // Conflict with qspinbox and so on, The widget text cannot use this style

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
    }break;
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

//
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

//
void CustomStyle::polish(QWidget *widget)
{
    widget->setAttribute(Qt::WA_Hover);
//    auto palette = widget->palette();
//    polish(palette);
//    widget->setPalette(palette);
    return QProxyStyle::polish(widget);
}

void CustomStyle::polish(QApplication *application)
{
    return QProxyStyle::polish(application);
}

//
void CustomStyle::polish(QPalette &palette)
{
    //    return QProxyStyle::polish(palette);
    //    QProxyStyle::polish(palette);
    //    palette.setBrush(QPalette::Foreground, Qt::black);
    palette.setBrush(QPalette::Text, Qt::black);
    // QColor lightBlue(200, 0, 0);

    palette.setBrush(QPalette::Base, Qt::white);

    //palette.setBrush(QPalette::Highlight, lightBlue);
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

