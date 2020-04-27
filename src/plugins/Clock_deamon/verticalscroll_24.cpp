/*
* Copyright (C) 2019 Tianjin KYLIN Information Technology Co., Ltd.
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
#include "verticalscroll_24.h"
#include <QMouseEvent>
#include <QDebug>
#include <QApplication>
#include "clock.h"
#include "ui_clock.h"
#include <QProcess>
VerticalScroll_24::VerticalScroll_24(QWidget *parent, Clock *clock) :
    QWidget(parent),
    m_minRange(0),      //最小值默认为0
    m_maxRange(23),    //最大值默认24
    m_currentValue(0), //当前值默认0
    isDragging(false),
    m_deviation(0),     //默认偏移量为0
    m_numSize(4),
    interval(1),      //间隔默认1
    devide(4)           //默认分成4格
{
    setupUi(this);
    m_Pclock = clock;
    homingAni = new QPropertyAnimation(this, "deviation");
    homingAni->setDuration(300);
    homingAni->setEasingCurve(QEasingCurve::OutQuad);
}

VerticalScroll_24::~VerticalScroll_24()
{
    delete homingAni;

    qDebug()<<"-------VerticalScroll_24---------";
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
    QProcess process;
    process.start("gsettings get org.ukui.control-center.panel.plugins hoursystem");
    process.waitForFinished();
    QByteArray output = process.readAllStandardOutput();
    QString str_output = output;

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

    if( m_Pclock->model_setup->index(0, 2).data().toInt() == 1 )
    {
        paintNum_24( painter, Height);
    }else if( m_Pclock->model_setup->index(0, 2).data().toInt() == 2 ){
        paintNum_12( painter, Height);
    }else{
        if(str_output.compare("'24'\n") == 0){
            paintNum_24( painter, Height);
        }else{
            paintNum_12( painter, Height);
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
    if ( y >= 0 && y + height < Height)
    {
        painter.drawText(QRectF(0, y, Width, height),
                         Qt::AlignCenter,
                         change_NUM_to_str(num));
    }
}

//单位变双位
QString VerticalScroll_24::change_NUM_to_str(int alarmHour)
{
    QString str;
    if(alarmHour < 10){
        QString hours_str = QString::number(alarmHour);
        str = "0"+hours_str;
    }else {
        str = QString::number(alarmHour);
    }
    return str;
}

void VerticalScroll_24::paintNum_24(QPainter &painter, int Height)
{
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
    m_Pclock->ui->label_17->hide();
}

void VerticalScroll_24::paintNum_12(QPainter &painter, int Height)
{
    int system_12_Value = m_currentValue;
    if(m_currentValue > 12){
        system_12_Value = m_currentValue - 12;
        paintNum(painter, system_12_Value, m_deviation);
    }else
    {
        if(m_currentValue == 0){
            system_12_Value = 12;
            paintNum(painter, system_12_Value, m_deviation);
        }else{
            system_12_Value = m_currentValue;
            paintNum(painter, system_12_Value, m_deviation);
        }
    }

    if (system_12_Value != m_minRange)
    {
        if(system_12_Value == 1){
            paintNum(painter, 12, m_deviation - Height / devide);
        }else{
            paintNum(painter, system_12_Value - interval, m_deviation - Height / devide);
        }
    }
    else{
        paintNum(painter, m_maxRange, m_deviation - Height / devide);
    }


    if (system_12_Value != m_maxRange)
    {
        if(system_12_Value == 12){
            paintNum(painter, 1, m_deviation + Height / devide);
        }else{
            paintNum(painter, system_12_Value + interval, m_deviation + Height / devide);
        }
    }else {
        paintNum(painter, m_minRange, m_deviation + Height / devide);
    }
    m_Pclock->ui->label_17->show();
    if(m_currentValue>12){
        m_Pclock->ui->label_17->setText(tr("下午"));
    }else{
        m_Pclock->ui->label_17->setText(tr("上午"));
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
    VerticalScroll_24->resize(53, 200);

    retranslateUi(VerticalScroll_24);

    QMetaObject::connectSlotsByName(VerticalScroll_24);
} // setupUi

void VerticalScroll_24::retranslateUi(QWidget *VerticalScroll_24)
{
    VerticalScroll_24->setWindowTitle(QApplication::translate("VerticalScroll_24", "VerticalScroll_24", nullptr));
} // retranslateUi


