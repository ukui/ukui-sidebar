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
}

void CustomStyle::drawComplexControl(QStyle::ComplexControl cc, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const
{
    switch (cc) {
    case CC_Slider :
        if (const QStyleOptionSlider *slider = qstyleoption_cast<const QStyleOptionSlider *>(option)) {
            //Size and location of each rectangle used
            QRectF rect = option->rect;
            QRectF rectHandle = proxy()->subControlRect(CC_Slider, option, SC_SliderHandle, widget);
            QRectF rectSliderTickmarks = proxy()->subControlRect(CC_Slider, option, SC_SliderTickmarks, widget);
            QRect rectGroove = proxy()->subControlRect(CC_Slider, option, SC_SliderGroove, widget);
            QPen pen;
            //Drawing chute (line)
            if (option->subControls & SC_SliderGroove) {
                pen.setStyle(Qt::CustomDashLine);
                QVector<qreal> dashes;
                //qreal space = 1.3;
                qreal space = 0;
                dashes << 0.1 << space;
                // dashes << -0.1 << space;
                pen.setDashPattern(dashes);
                pen.setWidthF(3);
                pen.setColor(QColor(39,207,129));//拉之后
                painter->setPen(pen);
                painter->setRenderHint(QPainter::Antialiasing);
                if (slider->orientation == Qt::Horizontal) {
                    painter->drawLine(QPointF(rectGroove.left(), rectHandle.center().y()), QPointF(rectHandle.left(), rectHandle.center().y()));
                    pen.setColor(QColor(61,61,65));
                    painter->setPen(pen);
                    painter->drawLine(QPointF(rectGroove.right(), rectHandle.center().y()), QPointF(rectHandle.right(), rectHandle.center().y()));
                } else {
                    painter->drawLine(QPointF(rectGroove.center().x(), rectGroove.bottom()), QPointF(rectGroove.center().x(),  rectHandle.bottom()));
                    pen.setColor(Qt::green);
                    painter->setPen(pen);
                    painter->drawLine(QPointF(rectGroove.center().x(),  rectGroove.top()), QPointF(rectGroove.center().x(),  rectHandle.top()));
                }
            }

            //Painting slider
            if (option->subControls & SC_SliderHandle) {
                pen.setStyle(Qt::SolidLine);
                painter->setPen(Qt::NoPen);
                painter->setBrush(QColor(39,207,129));
                painter->drawEllipse(rectHandle);
            }

            //Drawing scale
            if ((option->subControls & SC_SliderTickmarks) && slider->tickInterval) {
                painter->setPen(Qt::green);
                int available = proxy()->pixelMetric(PM_SliderSpaceAvailable, slider, widget);
                int interval = slider->tickInterval;
                //int tickSize = proxy()->pixelMetric(PM_SliderTickmarkOffset, opt, w);
                //int ticks = slider->tickPosition;
                int v = slider->minimum;
                int len = proxy()->pixelMetric(PM_SliderLength, slider, widget);
                while (v <= slider->maximum + 1) {
                    const int v_ = qMin(v, slider->maximum);
                    int pos = sliderPositionFromValue(slider->minimum, slider->maximum, v_, available) + len / 2;

                    if (slider->orientation == Qt::Horizontal) {
                        if (slider->tickPosition == QSlider::TicksBothSides) {
                            painter->drawLine(pos, int(rect.top()), pos, int(rectHandle.top()));
                            painter->drawLine(pos, int(rect.bottom()), pos, int(rectHandle.bottom()));
                        } else {
                            painter->drawLine(pos, int(rectSliderTickmarks.top()), pos, int(rectSliderTickmarks.bottom()));
                        }
                    } else {
                        if (slider->tickPosition == QSlider::TicksBothSides) {
                            painter->drawLine(int(rect.left()), pos, int(rectHandle.left()), pos);
                            painter->drawLine(int(rect.right()), pos, int(rectHandle.right()), pos);
                        } else {
                            painter->drawLine(int(rectSliderTickmarks.left()), pos, int(rectSliderTickmarks.right()), pos);
                        }
                    }
                    // in the case where maximum is max int
                    int nextInterval = v + interval;
                    if (nextInterval < v)
                        break;
                    v = nextInterval;
                }
            }
            return;
        }
    default:
        break;
    }
    return QProxyStyle::drawComplexControl(cc, option, painter, widget);


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
    return QProxyStyle::pixelMetric(metric, option, widget);
}

//
void CustomStyle::polish(QWidget *widget)
{
    widget->setAttribute(Qt::WA_Hover);
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
    QColor lightBlue(200, 0, 0);
    palette.setBrush(QPalette::Highlight, lightBlue);
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
