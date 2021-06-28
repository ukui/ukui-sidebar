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
#include "setAlarmRepeatDialog.h"
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QBitmap>
#include <QPainter>
#include <QDebug>
#include <QScroller>
#include <QPainterPath>

extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);

set_alarm_repeat_Dialog::set_alarm_repeat_Dialog(int width, int Length, int rowNum , QWidget *parent ) :
    rowNum_all(rowNum),
    width_num(width),
    Length_num(Length),
    QWidget(parent)
{
    setupUi(this);
    this->resize(width_num, Length_num);

    this->setWindowTitle(tr("Alarm"));

    setWindowFlags(Qt::Dialog);
//    this->setAttribute(Qt::WA_TranslucentBackground);
//    QPainterPath blurPath;
//    blurPath.addRoundedRect(rect().adjusted(10, 10, -10, -10), 10, 10);      //增加圆角
//    setProperty("useSystemStyleBlur", true);
//    setProperty("blurRegion", QRegion(blurPath.toFillPolygon().toPolygon()));//使用QPainterPath的api生成多边形Region

    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.setRenderHint(QPainter::Antialiasing);
    p.drawRoundedRect(bmp.rect(),10,10);
    setMask(bmp);

    for (int i = 0; i < rowNum_all; i++) {
        set_aItem(i);
    }

    settingsStyle();
}

set_alarm_repeat_Dialog::~set_alarm_repeat_Dialog()
{
    for (int i =0 ; i <rowNum_all; i++) {
        delete widget[i];
        delete aItem[i];
    }
    delete listWidget;
}

/*
*监听主题
*/
void set_alarm_repeat_Dialog::settingsStyle()
{
    const QByteArray style_id(ORG_UKUI_STYLE);
    QStringList stylelist;
    QGSettings *style_settings = new QGSettings(style_id);

    stylelist<<STYLE_NAME_KEY_DARK<<STYLE_NAME_KEY_BLACK; //<<STYLE_NAME_KEY_DEFAULT;
    if(QGSettings::isSchemaInstalled(style_id)){
        style_settings = new QGSettings(style_id);
        if(stylelist.contains(style_settings->get(STYLE_NAME).toString())){
            blackStyle();
        }else{
            whiteStyle();
        }
    }

    connect(style_settings, &QGSettings::changed, this, [=] (const QString &key){
        if(key==STYLE_NAME){
            if(stylelist.contains(style_settings->get(STYLE_NAME).toString())){
                blackStyle();
            }else{
                whiteStyle();
            }
        }
    });
}


void set_alarm_repeat_Dialog::set_aItem(int rowNum)
{
    aItem[rowNum] =new QListWidgetItem;
    aItem[rowNum]->setSizeHint(QSize(340, 38));
    aItem[rowNum]->setTextColor(QColor(255, 0, 0, 255));
    listWidget->addItem(aItem[rowNum]);
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    widget[rowNum] = new set_alarm_repeat_widget(listWidget);
    listWidget->setItemWidget(aItem[rowNum],widget[rowNum]);
    QScroller::grabGesture(listWidget,QScroller::LeftMouseButtonGesture); //设置鼠标左键拖动
    listWidget -> setVerticalScrollMode(QAbstractItemView::ScrollPerPixel); // 设置像素级滑动
}

void set_alarm_repeat_Dialog::setupUi(QWidget( *set_alarm_repeat_Dialog))
{
    if (set_alarm_repeat_Dialog->objectName().isEmpty())
        set_alarm_repeat_Dialog->setObjectName(QString::fromUtf8("set_alarm_repeat_Dialog"));
    listWidget = new QListWidget(set_alarm_repeat_Dialog);
    listWidget->setObjectName(QString::fromUtf8("listWidget"));
    listWidget->setGeometry(QRect(0, 0, 280, 162));
    listWidget->move(10,10);

    retranslateUi(set_alarm_repeat_Dialog);

    QMetaObject::connectSlotsByName(set_alarm_repeat_Dialog);
}   // setupUi

void set_alarm_repeat_Dialog::retranslateUi(QWidget( *set_alarm_repeat_Dialog))
{
    set_alarm_repeat_Dialog->setWindowTitle(QApplication::translate("set_alarm_repeat_Dialog", "Dialog", nullptr));
}   // retranslateUi

void set_alarm_repeat_Dialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    QPainterPath rectPath;
    rectPath.addRoundedRect(this->rect().adjusted(10, 10, -10, -10), 10, 10);
    // 画一个黑底
    QPixmap pixmap(this->rect().size());
    pixmap.fill(Qt::transparent);
    QPainter pixmapPainter(&pixmap);
    pixmapPainter.setRenderHint(QPainter::Antialiasing);
    pixmapPainter.setPen(Qt::transparent);
    pixmapPainter.setBrush(QColor(0,0,0,100));
    pixmapPainter.drawPath(rectPath);
    pixmapPainter.end();

    // 模糊这个黑底
    QImage img = pixmap.toImage();
    qt_blurImage(img, 10, false, false);

    // 挖掉中心
    pixmap = QPixmap::fromImage(img);
    QPainter pixmapPainter2(&pixmap);
    pixmapPainter2.setRenderHint(QPainter::Antialiasing);
    pixmapPainter2.setCompositionMode(QPainter::CompositionMode_Clear);
    pixmapPainter2.setPen(Qt::transparent);
    pixmapPainter2.setBrush(Qt::transparent);
    pixmapPainter2.drawPath(rectPath);

    // 绘制阴影
    p.drawPixmap(this->rect(), pixmap, pixmap.rect());

    QStyleOption opt;
    opt.init(this);
    QColor mainColor;
    if(QColor(255,255,255) == opt.palette.color(QPalette::Base) || QColor(248,248,248) == opt.palette.color(QPalette::Base))
    {
        mainColor = QColor(228, 235, 242,196.35);
    }else{
        mainColor = QColor(94, 98, 102,191.25);
    }

    // 绘制一个背景
    p.save();
    p.fillPath(rectPath,mainColor);
    p.restore();

}


//黑色主题
void  set_alarm_repeat_Dialog::blackStyle()
{
    listWidget->setStyleSheet("QListWidget{background-color: rgba(0, 0, 0, 0);}\
                                  QListWidget::item::selected{background-color:rgba("+hoverColor+");border-radius:4px;border:1px solid rgba(131, 131, 131,0);}\
                                  QListWidget::item:hover{background-color:rgba("+hoverColor+");border-radius:4px;}\
                                  ");

}
//白色主题
void  set_alarm_repeat_Dialog::whiteStyle()
{
    listWidget->setStyleSheet("QListWidget{background-color: rgba(0, 0, 0, 0);}\
                                  QListWidget::item::selected{background-color:rgba("+hoverColor+");border-radius:4px;border:1px solid rgba(131, 131, 131,0);}\
                                  QListWidget::item:hover{background-color:rgba("+hoverColor+");border-radius:4px;}\
                                  ");

}

set_alarm_repeat_widget::set_alarm_repeat_widget(QWidget *parent):
    QWidget(parent)
{
    this->setFixedSize(340, 38);
    //选项
    alarmLabel0 = new QLabel(this);
    alarmLabel0->move(16, 0);
    alarmLabel0->setFixedSize(160, 38);
    alarmLabel0->setStyleSheet("background-color: rgb();");
    alarmLabel0->setText("选项");

    //对号
    alarmLabel1 = new ClickableLabel(this);
    alarmLabel1->move(296, 0);
    alarmLabel1->setFixedSize(34, 38);
    alarmLabel1->setText("");
    alarmLabel1->setProperty("useIconHighlightEffect", true);
    alarmLabel1->setProperty("iconHighlightEffectMode", 1);

}

set_alarm_repeat_widget::~set_alarm_repeat_widget()
{

}

