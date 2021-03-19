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
#include "customstyle_switchNormalStatus.h"
#include <QWidget>

#include <QStyleOption>
#include <QPainter>
#include <QApplication>
#include <QDebug>

customstyle_switchNormalStatus::customstyle_switchNormalStatus(const QString &proxyStyleName, QObject *parent) : QProxyStyle (proxyStyleName)
{
    Q_UNUSED(parent);
}

void customstyle_switchNormalStatus::drawComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const
{
    switch (control) {
    case CC_Slider: {
        QRect groove = subControlRect(CC_Slider, option, SC_SliderGroove, widget);
        QRect handle = subControlRect(CC_Slider, option, SC_SliderHandle, widget);
        painter->save();
        if(const QSlider *ms = qobject_cast<const QSlider *>(widget))
        {
            if(const QStyleOptionSlider *sl = qstyleoption_cast<const QStyleOptionSlider *>(option))
            {
                QStyleOptionSlider sll = *sl;
                if ((option->subControls & QStyle::SC_SliderGroove) && groove.isValid() && handle.isValid())// 背景
                {
                    painter->setRenderHint(QPainter::Antialiasing, true);
                    QPen pen;
                    pen.setColor(QColor(204,204,204,255));
                    QBrush brush;
                    brush.setColor(QColor(204,204,204,255));
                    brush.setStyle(Qt::SolidPattern);
                    painter->setPen(pen);
                    painter->setBrush(brush);

                    painter->drawChord(QRect(groove.x(), ms->height()/2-5,10,10),90*16,180*16);
                    painter->drawRect(QRect(groove.x()+5, ms->height()/2-5,groove.width()-10,10)); //矩形
                    painter->drawChord(QRect(groove.width()-11, ms->height()/2-5,10,10),90*16,-180*16);

                    QPen pen2;
                    pen2.setColor(QColor(47,179,232,255));
                    QBrush brush2;
                    brush2.setColor(QColor(47,179,232,255));
                    brush2.setStyle(Qt::SolidPattern);
                    painter->setPen(pen2);
                    painter->setBrush(brush2);
                    if(handle.x()<=0){;
                        painter->drawChord(QRect(groove.x(), ms->height()/2-5,10,10),90*16,180*16);
                        painter->drawChord(QRect(handle.x(), ms->height()/2-5,10,10),90*16,-180*16);
                    }
                    else
                    {
                        painter->drawChord(QRect(groove.x(), ms->height()/2-5,10,10),90*16,180*16);
                        painter->drawRect(QRect(groove.x()+5, ms->height()/2-5,handle.x(),10)); //矩形
                        painter->drawChord(QRect(handle.x(), ms->height()/2-5,10,10),90*16,-180*16);
                    }
                    QPen pen3;
                    pen3.setColor(QColor(255,255,255,255));
                    QBrush brush3;
                    brush3.setColor(QColor(255,255,255,255));
                    brush3.setStyle(Qt::SolidPattern);
                    painter->setPen(pen3);
                    painter->setBrush(brush3);
                    painter->drawRect(QRect(handle.x()+4, ms->height()/2-2,1,4)); //小矩形

                }
                //return QProxyStyle::drawComplexControl(control, &sll, painter, widget);
            }
        }
        //return QProxyStyle::drawComplexControl(control, option, painter, widget);
    }
        break;
    default:
        break;
    }

    //return QProxyStyle::drawComplexControl(control, option, painter, widget);
}

void customstyle_switchNormalStatus::drawControl(QStyle::ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    switch (element) {
    case QStyle::CE_PushButton: {
        QStyleOptionButton button = *qstyleoption_cast<const QStyleOptionButton *>(option);
        button.palette.setColor(QPalette::HighlightedText, button.palette.buttonText().color());
        return QProxyStyle::drawControl(element, &button, painter, widget);
        break;
    }
    default:
        break;
    }
    return QProxyStyle::drawControl(element, option, painter, widget);
}

void customstyle_switchNormalStatus::drawItemPixmap(QPainter *painter, const QRect &rectangle, int alignment, const QPixmap &pixmap) const
{
    return QProxyStyle::drawItemPixmap(painter, rectangle, alignment, pixmap);
}

void customstyle_switchNormalStatus::drawItemText(QPainter *painter, const QRect &rectangle, int alignment, const QPalette &palette, bool enabled, const QString &text, QPalette::ColorRole textRole) const
{
    return QProxyStyle::drawItemText(painter, rectangle, alignment, palette, enabled, text, textRole);
}

/// 我们重写button的绘制方法，通过state和当前动画的状态以及value值改变相关的绘制条件
/// 这里通过判断hover与否，动态的调整painter的透明度然后绘制背景
/// 需要注意的是，默认控件的绘制流程只会触发一次，而动画需要我们在一段时间内不停绘制才行，
/// 要使得动画能够持续，我们需要使用QWidget::update()在动画未完成时，
/// 手动更新一次，这样button将在一段时间后再次调用draw方法，从而达到更新动画的效果
///
/// 需要注意绘制背景的流程会因主题不同而产生差异，所以这一部分代码在一些主题中未必正常，
/// 如果你需要自己实现一个主题，这同样是你需要注意和考虑的点
void customstyle_switchNormalStatus::drawPrimitive(QStyle::PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    if (element == PE_PanelButtonCommand) {
        if (widget) {
            if (option->state & State_MouseOver) {
                if (option->state & State_Sunken) {
                    painter->save();
                    painter->setRenderHint(QPainter::Antialiasing,true);
                    painter->setPen(Qt::NoPen);
                    QColor color(107,142,235,255);
                    painter->setBrush(color);
                    painter->setOpacity(1);
                    painter->drawRoundedRect(option->rect, 28, 28);
                    painter->restore();
                } else {
                    painter->save();
                    painter->setRenderHint(QPainter::Antialiasing,true);
                    painter->setPen(Qt::NoPen);
                    QColor color(107,142,235,255);
                    painter->setBrush(color);
                    painter->setOpacity(1);
                    painter->drawRoundedRect(option->rect, 28, 28);
                    painter->restore();
                }
            } else {
                painter->save();
                painter->setRenderHint(QPainter::Antialiasing,true);
                painter->setPen(Qt::NoPen);
                painter->setBrush(qApp->palette().color(QPalette::Button));
                painter->setOpacity(1);
                painter->drawRoundedRect(option->rect, 28, 28);
                painter->restore();
            }
            return;
        }
    }
    return QProxyStyle::drawPrimitive(element, option, painter, widget);
}

QPixmap customstyle_switchNormalStatus::generatedIconPixmap(QIcon::Mode iconMode, const QPixmap &pixmap, const QStyleOption *option) const
{
    return QProxyStyle::generatedIconPixmap(iconMode, pixmap, option);
}

QStyle::SubControl customstyle_switchNormalStatus::hitTestComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex *option, const QPoint &position, const QWidget *widget) const
{
    return QProxyStyle::hitTestComplexControl(control, option, position, widget);
}

QRect customstyle_switchNormalStatus::itemPixmapRect(const QRect &rectangle, int alignment, const QPixmap &pixmap) const
{
    return QProxyStyle::itemPixmapRect(rectangle, alignment, pixmap);
}

QRect customstyle_switchNormalStatus::itemTextRect(const QFontMetrics &metrics, const QRect &rectangle, int alignment, bool enabled, const QString &text) const
{
    return QProxyStyle::itemTextRect(metrics, rectangle, alignment, enabled, text);
}

int customstyle_switchNormalStatus::pixelMetric(QStyle::PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
    return QProxyStyle::pixelMetric(metric, option, widget);
}

/// 我们需要将动画与widget一一对应起来，
/// 在一个style的生命周期里，widget只会进行polish和unpolish各一次，
/// 所以我们可以在polish时将widget与一个新的动画绑定，并且对应的在unpolish中解绑定
void customstyle_switchNormalStatus::polish(QWidget *widget)
{
    return QProxyStyle::polish(widget);
}

void customstyle_switchNormalStatus::polish(QApplication *application)
{
    return QProxyStyle::polish(application);
}

void customstyle_switchNormalStatus::polish(QPalette &palette)
{
    return QProxyStyle::polish(palette);
}

void customstyle_switchNormalStatus::unpolish(QWidget *widget)
{
    return QProxyStyle::unpolish(widget);
}

void customstyle_switchNormalStatus::unpolish(QApplication *application)
{
    return QProxyStyle::unpolish(application);
}

QSize customstyle_switchNormalStatus::sizeFromContents(QStyle::ContentsType type, const QStyleOption *option, const QSize &contentsSize, const QWidget *widget) const
{
    return QProxyStyle::sizeFromContents(type, option, contentsSize, widget);
}

QIcon customstyle_switchNormalStatus::standardIcon(QStyle::StandardPixmap standardIcon, const QStyleOption *option, const QWidget *widget) const
{
    return QProxyStyle::standardIcon(standardIcon, option, widget);
}

QPalette customstyle_switchNormalStatus::standardPalette() const
{
    return QProxyStyle::standardPalette();
}

int customstyle_switchNormalStatus::styleHint(QStyle::StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
{
    return QProxyStyle::styleHint(hint, option, widget, returnData);
}

QRect customstyle_switchNormalStatus::subControlRect(QStyle::ComplexControl control, const QStyleOptionComplex *option, QStyle::SubControl subControl, const QWidget *widget) const
{
    return QProxyStyle::subControlRect(control, option, subControl, widget);
}

QRect customstyle_switchNormalStatus::subElementRect(QStyle::SubElement element, const QStyleOption *option, const QWidget *widget) const
{
    return QProxyStyle::subElementRect(element, option, widget);
}
