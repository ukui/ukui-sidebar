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
#include <QBitmap>
#include <QPainter>

#include "noteExitWindow.h"
#include "ui_noteExitWindow.h"
#include "widget.h"
#include "ui_widget.h"

noteExitWindow::noteExitWindow(Widget* page, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::noteExitWindow)
{
    ui->setupUi(this);
    pNotebook = page;

    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
}

noteExitWindow::~noteExitWindow()
{
    delete ui;
}

void noteExitWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);

    p.setBrush(opt.palette.color(QPalette::Base));
    //p.setOpacity(0.3);
    p.setPen(Qt::NoPen);

    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.drawRoundedRect(opt.rect,6,6);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void noteExitWindow::on_pushButton_clicked()
{
    this->close();
}

void noteExitWindow::on_pushButton_2_clicked()
{
    //qDebug() << "当前文件 :" << __FILE__ << "当前函数 :" << __FUNCTION__ << "当前行号 :" << __LINE__;
    this->close();
    pNotebook->close();
    if(ui->checkBox->isChecked()==true)
    {
        //emit requestSetNoteNull();
        for (auto it = pNotebook->m_editors.begin(); it!= pNotebook->m_editors.end();it++) {
            (*it)->close();
//            qDebug() << "before swap" << pNotebook->m_editors.size();
//            std::vector<Edit_page*> tmp;
//            pNotebook->m_editors.swap(tmp);
//            qDebug() << "after swap" << pNotebook->m_editors.size();
        }
    }
}


