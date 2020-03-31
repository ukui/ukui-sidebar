#include "verticalscroll_24.h"
#include <QMouseEvent>
#include <QDebug>
#include <QApplication>
VerticalScroll_24::VerticalScroll_24(QWidget *parent) :
    QWidget(parent),
    m_minRange(0),      //最小值默认为0
    m_maxRange(24),    //最大值默认24
    m_currentValue(0), //当前值默认0
    isDragging(false),
    m_deviation(0),     //默认偏移量为0
    m_numSize(4),
    interval(1),      //间隔默认1
    devide(4)           //默认分成4格
{
    setupUi(this);

    homingAni = new QPropertyAnimation(this, "deviation");
    homingAni->setDuration(300);
    homingAni->setEasingCurve(QEasingCurve::OutQuad);
}

VerticalScroll_24::~VerticalScroll_24()
{
    //delete ui;
}
/*
 * 设置范围
 * int min 最小值
 * int max 最大值
*/
void VerticalScroll_24::setRange(int min, int max)
{
    m_minRange = min;
    m_maxRange = max;
    if (m_currentValue < min)
    {
        m_currentValue = min;
    }
    if (m_currentValue > max)
    {
        m_currentValue = max;
    }
    repaint();
}
//获取当前值
int VerticalScroll_24::readValue()
{
    return m_currentValue;
}

void VerticalScroll_24::mousePressEvent(QMouseEvent *e)
{
    qDebug()<<"mouse pressed on vertical scroll";

    homingAni->stop();
    isDragging = true;
    m_mouseSrcPos = e->pos().y();
    QWidget::mousePressEvent(e);
}

void VerticalScroll_24::mouseMoveEvent(QMouseEvent *e)
{
    if (isDragging)
    {
        if( m_currentValue == m_minRange && e->pos().y() >= m_mouseSrcPos )
        {
            m_currentValue = m_maxRange;
        }
        else if( m_currentValue == m_maxRange && e->pos().y() <= m_mouseSrcPos )
        {
            m_currentValue = m_minRange;
        }

        m_deviation = e->pos().y() - m_mouseSrcPos;
        //若移动速度过快，则进行限制
        if (m_deviation > (height() - 1) / devide)
        {
            m_deviation = (height() - 1) / devide;
        }
        else if (m_deviation < -(height() - 1) / devide)
        {
            m_deviation = -( height() - 1) / devide;
        }

        emit deviationChange((int)m_deviation / ((height() - 1) / devide));
        repaint();
    }
}

void VerticalScroll_24::mouseReleaseEvent(QMouseEvent *)
{
    if (isDragging)
    {
        isDragging = false;
        homing();
    }
}

void VerticalScroll_24::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0){

         if(m_currentValue <= m_minRange)
         {
             m_currentValue = m_maxRange;
         }
         else
            m_currentValue-=1;
    }else{

        if(m_currentValue >= m_maxRange)
        {
            m_currentValue = m_minRange;
        }
        else
            m_currentValue+=1;
    }
    update();
    event->accept();
}

void VerticalScroll_24::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    int Height = height() - 1;

    if ( m_deviation >= Height / devide && m_currentValue > m_minRange )
    {
        m_mouseSrcPos += Height / devide;
        m_deviation -= Height / devide;
        m_currentValue -= interval;
    }

    if ( m_deviation <= -Height / devide && m_currentValue < m_maxRange )
    {
        m_mouseSrcPos -= Height / devide;
        m_deviation += Height / devide;
        m_currentValue += interval;
    }

    //middle number
    paintNum(painter, m_currentValue, m_deviation);

    //两侧数字1
    if (m_currentValue != m_minRange)
    {
        paintNum(painter, m_currentValue - interval, m_deviation - Height / devide);
    }else {
        paintNum(painter, m_maxRange, m_deviation - Height / devide);
}

    if (m_currentValue != m_maxRange)
    {
        paintNum(painter, m_currentValue + interval, m_deviation + Height / devide);
    }else {
        paintNum(painter, m_minRange, m_deviation + Height / devide);
}

    for (int i=2; i <= devide/2; ++i)
    {
        if (m_currentValue - interval * i >= m_minRange)
        {
            paintNum(painter, m_currentValue - interval * i, m_deviation - Height / devide * i);
        }

        if (m_currentValue + interval * i <= m_maxRange)
        {
            paintNum(painter, m_currentValue + interval * i, m_deviation + Height / devide * i);
        }
    }

}
/*
 * 根据偏移量描绘数字
 * int num 需要显示的数字
 * int deviation 数字相对中间的偏移量
*/
void VerticalScroll_24::paintNum(QPainter &painter, int num, int deviation)
{
    int Width = width() - 1;
    int Height = height() - 1;
    int size = (Height - qAbs(deviation)) / m_numSize; //偏移量越大，数字越小
    int transparency = 255 - 255 * qAbs(deviation) / Height;
    int height = Height / devide;
    int y = Height / 2 + deviation - height / 2;

    QFont font;
    font.setPixelSize(size);
    painter.setFont(font);
    painter.setPen(QColor(255,255,255,transparency));
    //painter.setFontFeatureSettings();
    if ( y >= 0 && y + height < Height)
    {
        //painter.drawRect(0, y, Width, height);
        painter.drawText(QRectF(0, y, Width, height),
                         Qt::AlignCenter,
                         //QString::number(num, 'd', 1));
                         QString::number(num));
    }
}

/*
 * 使选中的数字回到屏幕中间
*/
void VerticalScroll_24::homing()
{
    if ( m_deviation > height() / 10)
    {
        homingAni->setStartValue( ( height() - 1 ) / 8 - m_deviation);
        homingAni->setEndValue(0);
        m_currentValue -= interval;
    }
    else if ( m_deviation > -height() / 10 )
    {
        homingAni->setStartValue(m_deviation);
        homingAni->setEndValue(0);
    }
    else if ( m_deviation < -height() / 10 )
    {
        homingAni->setStartValue(-(height() - 1) / 8 - m_deviation);
        homingAni->setEndValue(0);
        m_currentValue += interval;
    }

    emit currentValueChanged(m_currentValue);
    homingAni->start();
}

int VerticalScroll_24::readDeviation()
{
    return m_deviation;
}

void VerticalScroll_24::setDeviation(int n)
{
    m_deviation = n;
    repaint();
}


void VerticalScroll_24::setupUi(QWidget *VerticalScroll_24)
{
    if (VerticalScroll_24->objectName().isEmpty())
        VerticalScroll_24->setObjectName(QString::fromUtf8("VerticalScroll_24"));
    VerticalScroll_24->resize(50, 200);

    retranslateUi(VerticalScroll_24);

    QMetaObject::connectSlotsByName(VerticalScroll_24);
} // setupUi

void VerticalScroll_24::retranslateUi(QWidget *VerticalScroll_24)
{
    VerticalScroll_24->setWindowTitle(QApplication::translate("VerticalScroll_24", "VerticalScroll_24", nullptr));
} // retranslateUi


