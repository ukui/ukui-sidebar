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
#ifndef CLOSEBUTTON_H
#define CLOSEBUTTON_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QIcon>
#include <QMouseEvent>
#include <QGSettings/QGSettings>

class CloseButton : public QLabel
{
    Q_OBJECT
public:
    explicit CloseButton(QWidget *parent = nullptr,const QString &filePath = "",const QString &hoverPath = "");

    //Render icon from theme
    const QPixmap renderSvg(const QIcon &icon, QString color);
    // change svg picture's color
    QPixmap drawSymbolicColoredPixmap(const QPixmap &source, QString color);
    void setIcon(const QIcon &icon);
    void setIconSize(int size);
    void setBkg(const QColor &color);
    void setHoverIn(const QString &hoverIn);
    void setHoverOut(const QString &hoverOut);

    ~CloseButton();
protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
private:
    QIcon *m_icon;
    QIcon *m_customIcon;
    QIcon *m_hoverIcon;
    bool m_bIsChecked;
    bool m_bIsPressed;
    QColor m_colorBkg;
    int m_cSize;
    bool m_settedBkg;
    QColor m_customBkg;
    QString m_szHoverOut;
    QString m_szHoverIn;
    QGSettings *m_qtThemeSetting;
    QGSettings *m_gtkThemeSetting;

Q_SIGNALS:
    void clicked(bool checked = true);
};

#endif // CLOSEBUTTON_H
