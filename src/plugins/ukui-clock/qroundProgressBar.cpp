/*
 * QRoundProgressBar - a circular progress bar Qt widget.
 *
 * Sintegrial Technologies (c) 2015-now
 *
 * The software is freeware and is distributed "as is" with the complete source codes.
 * Anybody is free to use it in any software projects, either commercial or non-commercial.
 * Please do not remove this copyright message and remain the name of the author unchanged.
 *
 * It is very appreciated if you produce some feedback to us case you are going to use
 * the software.
 *
 * Please send your questions, suggestions, and information about found issues to the
 *
 * sintegrial@gmail.com
 *
 */


#include "qroundProgressBar.h"

#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QDebug>
#include <QStyleOption>
//#include <QGSettings>


QRoundProgressBar::QRoundProgressBar(QWidget *parent) :
    QWidget(parent),
    m_min(0), m_max(100),
    m_value(25),
    m_nullPosition(PositionTop),
    m_barStyle(StyleDonut),
    m_outlinePenWidth(0.96),
    m_dataPenWidth(1),
    m_rebuildBrush(false),
    m_format("%p%"),
    m_decimals(1),
    m_updateFlags(UF_PERCENT)
{
    settingsStyle();
}

void QRoundProgressBar::setRange(double min, double max)
{
    m_min = min;
    m_max = max;

    if (m_max < m_min)
        qSwap(m_max, m_min);

    if (m_value < m_min)
        m_value = m_min;
    else if (m_value > m_max)
        m_value = m_max;

    if (!m_gradientData.isEmpty())
        m_rebuildBrush = true;

    update();
}

void QRoundProgressBar::setMinimum(double min)
{
    setRange(min, m_max);
}

void QRoundProgressBar::setMaximum(double max)
{
    setRange(m_min, max);
}

void QRoundProgressBar::setValue(double val)
{
    if (m_value != val) {
        if (val < m_min)
            m_value = m_min;
        else if (val > m_max)
            m_value = m_max;
        else
            m_value = val;
        update();
    }
}

void QRoundProgressBar::setValue()
{
    ring_max = ring_max - 3600/(time_max);
    setValue(double(ring_max));
}

void QRoundProgressBar::setNullPosition(double position)
{
    if (position != m_nullPosition) {
        m_nullPosition = position;
        if (!m_gradientData.isEmpty())
            m_rebuildBrush = true;
        update();
    }
}

void QRoundProgressBar::setBarStyle(QRoundProgressBar::BarStyle style)
{
    if (style != m_barStyle) {
        m_barStyle = style;
        update();
    }
}

void QRoundProgressBar::setOutlinePenWidth(double penWidth)
{
    if (penWidth != m_outlinePenWidth) {
        m_outlinePenWidth = penWidth;
        update();
    }
}

void QRoundProgressBar::setDataPenWidth(double penWidth)
{
    if (penWidth != m_dataPenWidth) {
        m_dataPenWidth = penWidth;
        update();
    }
}

void QRoundProgressBar::setDataColors(const QGradientStops &stopPoints)
{
    if (stopPoints != m_gradientData) {
        m_gradientData = stopPoints;
        m_rebuildBrush = true;
        update();
    }
}

void QRoundProgressBar::setFormat(const QString &format)
{
    if (format != m_format) {
        m_format = format;

        valueFormatChanged();
    }
}

void QRoundProgressBar::resetFormat()
{
    m_format = QString::null;
    valueFormatChanged();
}

void QRoundProgressBar::setDecimals(int count)
{
    if (count >= 0 && count != m_decimals) {
        m_decimals = count;
        valueFormatChanged();
    }
}

void QRoundProgressBar::paintEvent(QPaintEvent* /*event*/)
{
    QPainter painter(this);
    painter.save();
    painter.setPen(mainColor);
    painter.setBrush(mainColor);
    QPainterPath bigCircle;
    bigCircle.addEllipse(65, 13, 266, 266);
    QPainterPath path = bigCircle ;
    painter.drawPath(path);
    painter.restore();

    double outerRadius = 133;
    QRectF baseRect(198 - outerRadius, 146 - outerRadius, outerRadius * 2, outerRadius * 2);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    // data brush
    rebuildDataBrushIfNeeded();
    // background
    drawBackground(p, rect());
    double innerRadius = 133;
    QRectF innerRect = QRectF((198 - outerRadius) + 5, (146 - outerRadius) + 5, (outerRadius - 5) * 2 , (outerRadius - 5) * 2 );

    //calculateInnerRect(baseRect, outerRadius, innerRect, innerRadius);
    double arcStep = 360.0 / (m_max - m_min) * m_value;
    // base circle
    drawBase(p, baseRect,innerRect);
    // data circle
    drawValue(p, baseRect, m_value, arcStep,innerRect, innerRadius);
    // finally draw the bar
    p.end();
}


void QRoundProgressBar::drawBackground(QPainter &p, const QRectF &baseRect)
{
    p.fillRect(baseRect, palette().background());
}


void QRoundProgressBar::drawBase(QPainter &p, const QRectF &baseRect,const QRectF &innerRect)
{

    QStyleOption opt;
    opt.init(this);
    switch (m_barStyle)
    {
    case StyleDonut:
//        p.setPen(QPen(QColor(160, 160, 160), 4, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));
//        p.setBrush(Qt::NoBrush);
//        p.drawEllipse(QPointF(227, 180),155,155);
        break;
    case StylePie:
        p.setPen(QPen(palette().base().color(), m_outlinePenWidth, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));
        p.setBrush(palette().base());
        p.drawEllipse(baseRect);
        break;
    case StyleLine:
        p.setPen(QPen(palette().base().color(), m_outlinePenWidth ,Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));
        p.setBrush(Qt::NoBrush);
        p.drawEllipse(baseRect.adjusted(m_outlinePenWidth/2, m_outlinePenWidth/2, -m_outlinePenWidth/2, -m_outlinePenWidth/2));
        break;
    default:;
    }
}

void QRoundProgressBar::drawValue(QPainter &p
                                  , const QRectF &baseRect
                                  , double value
                                  , double arcLength
                                  , const QRectF & innerRect
                                  , double innerRadius)
{
    // nothing to draw
    if (value == m_min)
        return;

    // for Pie and Donut styles
    QPainterPath dataPath;
    dataPath.setFillRule(Qt::WindingFill);
    dataPath.moveTo(baseRect.center());
    dataPath.arcTo(baseRect, m_nullPosition, -arcLength);//大家都是先绘制外圆的弧长

    if(m_barStyle == StyleDonut) {
        // draw dount outer
        QPointF currentPoint = dataPath.currentPosition();//绘制完外圆弧长后，获取绘制完的位置绘制一个直线到达内圆
        currentPoint = baseRect.center() + (currentPoint - baseRect.center()) * m_innerOuterRate;//计算内圆的坐标点，m_innerOuterRate替代了原作者写的0.75，代表内圆是外圆的0.75倍
        dataPath.lineTo(currentPoint);//绘制外圆到内圆的直线
        dataPath.moveTo(baseRect.center());//坐标点回到中心准备绘制内圆弧形
        dataPath.arcTo(innerRect, m_nullPosition-arcLength, arcLength);//绘制内圆的弧形
        currentPoint = dataPath.currentPosition();//准备绘制内圆到外圆的直线，形成封闭区域
        currentPoint = baseRect.center() + ((currentPoint - baseRect.center()) * (2-m_innerOuterRate));//绘制内圆到外圆的直线，这里2-m_innerOuterRate其实是对应(1 + (1 -m_innerOuterRate))的
        dataPath.lineTo(currentPoint);
        p.setPen(Qt::NoPen);//这个很重要不然就会有绘制过程的一些轮廓了
    }

    p.setBrush(palette().highlight());
    p.setBrush(QColor(235, 163, 19, 255));

    p.drawPath(dataPath);
}

void QRoundProgressBar::calculateInnerRect(const QRectF &/*baseRect*/, double outerRadius, QRectF &innerRect, double &innerRadius)
{
    // for Line style
    if (m_barStyle == StyleLine) {
        innerRadius = outerRadius - m_outlinePenWidth;
    } else {
        innerRadius = outerRadius * m_outlinePenWidth;
    }

    double delta = (outerRadius - innerRadius) / 2;
    innerRect = QRectF(delta, delta, innerRadius, innerRadius);
//    innerRect = QRectF(227 - outerRadius, 220 - outerRadius, innerRadius * 2, innerRadius * 2);
}

void QRoundProgressBar::drawInnerBackground(QPainter &p, const QRectF &innerRect)
{
    if (m_barStyle == StyleDonut) {
        p.setBrush(palette().alternateBase());
        p.drawEllipse(innerRect);
    }
}

void QRoundProgressBar::drawText(QPainter &p, const QRectF &innerRect, double innerRadius, double value)
{
    if (m_format.isEmpty())
        return;

    // !!! to revise
    QFont f(font());
    f.setPixelSize(innerRadius * qMax(0.05, (0.35 - (double)m_decimals * 0.08)));
    p.setFont(f);

    QRectF textRect(innerRect);
    p.setPen(palette().text().color());
    p.drawText(textRect, Qt::AlignCenter, valueToText(value));
}

QString QRoundProgressBar::valueToText(double value) const
{
    QString textToDraw(m_format);

    if (m_updateFlags & UF_VALUE)
        textToDraw.replace("%v", QString::number(value, 'f', m_decimals));

    if (m_updateFlags & UF_PERCENT) {
        double procent = (value - m_min) / (m_max - m_min) * 100.0;
        textToDraw.replace("%p", QString::number(procent, 'f', m_decimals));
    }

    if (m_updateFlags & UF_MAX)
        textToDraw.replace("%m", QString::number(m_max - m_min + 1, 'f', m_decimals));
    return textToDraw;
}

void QRoundProgressBar::valueFormatChanged()
{
    m_updateFlags = 0;

    if (m_format.contains("%v"))
        m_updateFlags |= UF_VALUE;
    if (m_format.contains("%p"))
        m_updateFlags |= UF_PERCENT;
    if (m_format.contains("%m"))
        m_updateFlags |= UF_MAX;
    update();
}

void QRoundProgressBar::rebuildDataBrushIfNeeded()
{
    if (m_rebuildBrush) {
        m_rebuildBrush = false;
        QConicalGradient dataBrush;
        dataBrush.setCenter(0.5,0.5);
        dataBrush.setCoordinateMode(QGradient::StretchToDeviceMode);
        // invert colors
        for (int i = 0; i < m_gradientData.count(); i++) {
            dataBrush.setColorAt(1.0 - m_gradientData.at(i).first, m_gradientData.at(i).second);
        }
        // angle
        dataBrush.setAngle(m_nullPosition);
        QPalette p(palette());
        p.setBrush(QPalette::Window,Qt::NoBrush);
        p.setBrush(QPalette::AlternateBase,Qt::NoBrush);
        p.setBrush(QPalette::Highlight, dataBrush);
        setPalette(p);
    }
}

/*
*监听主题
*/
void QRoundProgressBar::settingsStyle()
{
    const QByteArray style_id(ORG_UKUI_STYLE);
    QStringList stylelist;
    QGSettings *style_settings = new QGSettings(style_id);

    stylelist<<STYLE_NAME_KEY_DARK<<STYLE_NAME_KEY_BLACK; //<<STYLE_NAME_KEY_DEFAULT;
    if(QGSettings::isSchemaInstalled(style_id)){
        style_settings = new QGSettings(style_id);
        if(stylelist.contains(style_settings->get(STYLE_NAME).toString())){
            mainColor = QColor(255, 255, 255, 40);
        }else{
            mainColor = QColor(255, 255, 255, 107);
        }
    }

    connect(style_settings, &QGSettings::changed, this, [=] (const QString &key){
        if(key==STYLE_NAME){
            if(stylelist.contains(style_settings->get(STYLE_NAME).toString())){
                mainColor = QColor(255, 255, 255, 40);
            }else{
                mainColor = QColor(255, 255, 255, 107);
            }
        }
    });
}


