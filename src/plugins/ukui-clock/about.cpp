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
#include "about.h"
#include "ui_about.h"
#include <X11/Xlib.h>
#include "xatom-helper.h"

extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    // 添加窗管协议
    MotifWmHints hints;
    hints.flags = MWM_HINTS_FUNCTIONS|MWM_HINTS_DECORATIONS;
    hints.functions = MWM_FUNC_ALL;
    hints.decorations = MWM_DECOR_BORDER;
    XAtomHelper::getInstance()->setWindowMotifHint(this->winId(), hints);

    setWindowTitle(tr("About"));
    //setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    //setAttribute(Qt::WA_TranslucentBackground);
    //当小部件接受了关闭事件时，使Qt删除此小部件（请参阅QWidget :: closeEvent（））。
    setAttribute(Qt::WA_DeleteOnClose);
    //启用主题框架不需要代码
//    this->setWindowIcon(QIcon::fromTheme("kylin-alarm-clock",QIcon(":/image/kylin-alarm-clock.svg")));
    //左上角闹钟图标
    ui->titleIcon->setPixmap(QIcon::fromTheme("kylin-alarm-clock").pixmap(24,24));
    //右上角关闭X
    ui->closeBtn->setIcon(QIcon::fromTheme("window-close-symbolic"));
    ui->closeBtn->setProperty("isWindowButton", 0x2);
    ui->closeBtn->setProperty("useIconHighlightEffect", 0x8);
    //按钮边框是否凸起 默认false
    ui->closeBtn->setFlat(true);
    connect(ui->closeBtn, &QPushButton::clicked, this, [=](){
        this->close();
    });
    //in order to use the same world in English
    ui->titlename->setText(tr(CLOCK_TITLE_NAME));
    //麒麟闹钟
    ui->appnameLabel->setText(tr(KYLIN_CLOCK_APP_NAME));
    ui->appnameLabel->setStyleSheet("QLabel{ font-size: 18px; color: palette(windowText);}"
                                    "QLabel{font-family: NotoSansCJKsc-Medium, NotoSansCJKsc;}");
    ui->versionLabel->setText(tr("Version: ")+"2021.2.0");
    settingsStyle();
    //中间大图标
    ui->appiconLabel->setPixmap(QIcon::fromTheme("kylin-alarm-clock").pixmap(96,96));
    //介绍的超链接 url 时text里的a标签
    connect(ui->introduceLabel, &QLabel::linkActivated, this, [=](const QString url){
         QDesktopServices::openUrl(QUrl(url));
     });
    //该窗口小部件不具有上下文菜单，上下文菜单的处理将延迟到该窗口小部件的父级。
    ui->introduceLabel->setContextMenuPolicy(Qt::NoContextMenu);
    //    主题框架1.0.6-5kylin2

    //关闭按钮去掉聚焦状态
    ui->closeBtn->setFocusPolicy(Qt::NoFocus);

}

About::~About()
{
    delete ui;
}
#define SYSTEM_FONT_EKY            "system-font-size"
/*
*监听主题
*/
void About::settingsStyle()
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
        if (style_settings->get(SYSTEM_FONT_EKY).toInt()) {
            const int size = style_settings->get(SYSTEM_FONT_EKY).toInt();
            this->CURRENT_FONT_SIZE=size;
            updateLabelFront(ui->appnameLabel,round(size*1.63));
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
        if(key==STYLE_ICON_NAME || key==STYLE_ICON){
            //主题框架不能更新 titleIcon
            ui->titleIcon->setPixmap(QIcon::fromTheme("kylin-alarm-clock").pixmap(24,24));
            ui->appiconLabel->setPixmap(QIcon::fromTheme("kylin-alarm-clock").pixmap(96,96));
        }
        if (key == "systemFontSize") {
            const int size = style_settings->get(SYSTEM_FONT_EKY).toInt();
            this->CURRENT_FONT_SIZE=size;
            updateLabelFront(ui->appnameLabel,round(size*1.63));
        }
    });
}

void About::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    //绘制器路径
    QPainterPath rectPath;
    rectPath.addRect(this->rect());
    p.fillPath(rectPath,palette().color(QPalette::Base));
}

//黑色主题
void About::blackStyle()
{
    ui->introduceLabel->setText(tr("Service & Support: ") +
                                "<a href=\"mailto://support@kylinos.cn\""
                                "style=\"color:white\">"
                                "support@kylinos.cn</a>");
}
//白色主题
void About::whiteStyle()
{
    ui->introduceLabel->setText(tr("Service & Support: ") +
                                "<a href=\"mailto://support@kylinos.cn\""
                                "style=\"color:black\">"
                                "support@kylinos.cn</a>");
}
/**
 * @brief 更新麒麟闹钟字体
 */
void About::updateLabelFront(QLabel *label, int size)
{
    QString styleSheet = "QLabel{ font-size: ";
    styleSheet.append(QString::number(size)).append("px;");
    styleSheet.append("color: palette(windowText);}""QLabel{font-family: NotoSansCJKsc-Medium, NotoSansCJKsc;}");
    label->setStyleSheet(styleSheet);
}
