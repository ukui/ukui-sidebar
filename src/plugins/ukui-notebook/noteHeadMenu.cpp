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

#include <QPainterPath>
#include <QDebug>

#include "noteHeadMenu.h"
#include "ui_noteHeadMenu.h"

static QPixmap drawSymbolicColoredPixmap (const QPixmap&, QPushButton *);

noteHeadMenu::noteHeadMenu(QWidget *parent) :
    QWidget(parent)
  , ui(new Ui::noteHeadMenu)
  , color_widget(15,161,90)
{
    ui->setupUi(this);
    setMinimumSize(250,34);
    btnInit();
    slotsInit();
}

noteHeadMenu::~noteHeadMenu()
{
    delete ui;
}

void noteHeadMenu::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    QPainterPath rectPath;
    rectPath.addRect(this->rect());
    p.fillPath(rectPath,QBrush(color_widget));
    QWidget::paintEvent(event);
}

//void noteHeadMenu::mouseDoubleClickEvent(QMouseEvent *event)
//{
//    requestFullscreen();
//}

void noteHeadMenu::slotsInit()
{
    connect(ui->pushButtonNew, &QPushButton::clicked, this, [=](){
        qDebug() << "emit requestNewNote";
        requestNewNote();
    });
}

void noteHeadMenu::btnInit()
{
    ui->pushButtonExit->setIcon(drawSymbolicColoredPixmap(QIcon::fromTheme("window-close-symbolic").pixmap(16,16), ui->pushButtonExit));
    ui->pushButtonMenu->setIcon(drawSymbolicColoredPixmap(QIcon::fromTheme("open-menu-symbolic").pixmap(16,16), ui->pushButtonMenu));
    ui->pushButtonPalette->setIcon(drawSymbolicColoredPixmap(QIcon::fromTheme(":/image/1x/note_color.png").pixmap(16,16), ui->pushButtonPalette));

    QString _Stylesheet = "QPushButton{background-color: rgba(0,0,0,0);}"
                  "QPushButton:hover{background-color: rgba(0,0,0,0.12);}"
                  "QPushButton:pressed{background-color: rgba(0,0,0,0.2);}";

    ui->pushButtonNew->setStyleSheet("QPushButton{border-image:url(:/image/1x/new-normal.png);}"
                                "QPushButton:hover{border-image:url(:/image/1x/new-hover.png);}"
                                "QPushButton:pressed{border-image:url(:/image/1x/new-click.png);}");

    ui->pushButtonExit->setStyleSheet(_Stylesheet);
    ui->pushButtonMenu->setStyleSheet(_Stylesheet);
    ui->pushButtonPalette->setStyleSheet(_Stylesheet);

    QPalette palette = ui->pushButtonExit->palette();
    palette.setColor(QPalette::Highlight, Qt::transparent); /* 取消按钮高亮 */
    ui->pushButtonExit->setPalette(palette);
    ui->pushButtonMenu->setPalette(palette);
    ui->pushButtonPalette->setPalette(palette);

    QMenu *m_menu = new QMenu(ui->pushButtonMenu);
    QMenu *m_childMenu = new QMenu(m_menu);
    QAction *m_menuAction = new QAction(m_menu);

    m_menuActionDel = new QAction(m_menu);
    m_topAction = new QAction(m_menu);
    QAction *m_jpgAction = new QAction(m_childMenu);
    QAction *m_pdfAction = new QAction(m_childMenu);
    QAction *m_mailAction = new QAction(m_childMenu);

    m_menu->setProperty("fillIconSymbolicColor", true);
    m_menuAction->setText(tr("Open note list"));
    m_topAction->setText(tr("Always in the front"));
    m_menuActionDel->setText(tr("Delete this note"));
    m_childMenu->setTitle(tr("Share"));

    m_jpgAction->setText("Export to jpg");
    m_pdfAction->setText("Export to pdf");
    m_mailAction->setText("Mail");

    m_childMenu->addAction(m_jpgAction);
    m_childMenu->addAction(m_pdfAction);
    m_childMenu->addAction(m_mailAction);

    //m_menu->addMenu(m_childMenu);
    m_menu->addAction(m_topAction);
    m_menu->addAction(m_menuActionDel);
    m_menu->addAction(m_menuAction);
    ui->pushButtonMenu->setMenu(m_menu);

    connect(m_menuAction, &QAction::triggered, this, [=](){
        requestShowNote();
    });
    connect(m_topAction, &QAction::triggered, this, [=](){
        requestTopMost();
    });
    //隐藏menu下箭头
    //ui->pushButtonMenu->setStyleSheet("QPushButton::menu-indicator{image:none}");
    ui->pushButtonMenu->setProperty("isOptionButton", true);
    //设置是否自动凸起
    ui->pushButtonMenu->setIconSize(QSize(16, 16));

    //zybAdd 解决story6496:深色模式下pushButtonMenu
    //ui->pushButtonMenu->setProperty("isWindowButton", 0x1);

    ui->pushButtonMenu->setProperty("useIconHighlightEffect", 0x2);
    ui->pushButtonNew->setToolTip(tr("Create New Note"));
    ui->pushButtonExit->setToolTip(tr("Close"));
    ui->pushButtonMenu->setToolTip(tr("Menu"));

    ui->pushButtonPalette->setProperty("isOptionButton", true);
    ui->pushButtonPalette->setIconSize(QSize(16,16));
    ui->pushButtonPalette->setProperty("useIconHighlightEffect", true);
    ui->pushButtonPalette->setProperty("iconHighlightEffectMode", 1);
    ui->pushButtonPalette->setToolTip(tr("Palette"));
}

QPixmap drawSymbolicColoredPixmap(const QPixmap& source, QPushButton *btn)
{
    QColor whiteColor = QColor(0, 0, 0);   //zybAdd 解决story6496:深色模式下，便签页头部按钮颜色显示异常，返回浅色模式后，新建的便签页也会显示异常的问题
    QColor baseColor = btn->palette().color(QPalette::Text).light(150);
    QImage img = source.toImage();

    qDebug() << "drawSymbolicColoredPixmap" << baseColor.red() << baseColor.green() <<baseColor.blue();
    for (int x = 0; x < img.width(); ++x) {
        for (int y = 0; y < img.height(); ++y) {
            auto color = img.pixelColor(x, y);
#if 0
            color.setRed(255 - baseColor.red());
            color.setGreen(255 - baseColor.green());
            color.setBlue(255 - baseColor.blue());
#else
            //zybAdd 解决story6496:深色模式下，便签页头部按钮颜色显示异常，返回浅色模式后，新建的便签页也会显示异常的问题
            color.setRed(255 - whiteColor.red());
            color.setGreen(255 - whiteColor.green());
            color.setBlue(255 - whiteColor.blue());
#endif
            img.setPixelColor(x, y, color);
        }
    }

    return QPixmap::fromImage(img);
}
