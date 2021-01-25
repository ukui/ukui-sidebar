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


#include "editorwidget.h"
#include <QFile>
#include <QTextFrameFormat>
#include <QTimer>


EditorWidget::EditorWidget()
{
    installEventFilter(this);
    this->setFixedSize(400, 338);
    this->setContentsMargins(0, 0, 0, 0);
    this->setWindowTitle(QObject::tr("edit box"));
    this->setWindowIcon(QIcon::fromTheme("kylin-clipboard"));
    this->setProperty("useSystemStyleBlur", true);
    m_pMainQVBoxLayout = new QVBoxLayout();
    m_pMainQVBoxLayout->setContentsMargins(0, 0, 0, 0);

    editBox();
    operationBox();
    m_pConfirmButton->setObjectName("ConfirmButton");
    m_pCancelButton->setObjectName("CancelButton");
    connect(m_pConfirmButton, &QPushButton::clicked, this, &EditorWidget::accept);
    connect(m_pCancelButton, &QPushButton::clicked, this, &EditorWidget::reject);
    connect(m_pConfirmButton, &QPushButton::clicked, globalClipboardSignal, &ClipboardSignal::CLipBoardEditConfirmButtonSignal);
    connect(m_pCancelButton, &QPushButton::clicked, globalClipboardSignal, &ClipboardSignal::CLipBoardEditConfirmButtonSignal);
    m_pEditingArea->setObjectName("EditingArea");
    m_pEditingArea->setAcceptRichText(false);
    m_pEditWidget->setObjectName("EditBox");
    m_pOperationWidget->setObjectName("OperationBox");
    this->setObjectName("EditorWidget");

    m_pMainQVBoxLayout->setContentsMargins(18, 0, 0, 0);
    m_pMainQVBoxLayout->addItem(new QSpacerItem(20, 24));
    m_pMainQVBoxLayout->addWidget(m_pEditWidget);
    m_pMainQVBoxLayout->addItem(new QSpacerItem(20, 15));
    m_pMainQVBoxLayout->addWidget(m_pOperationWidget);
    m_pMainQVBoxLayout->addItem(new QSpacerItem(20, 18));
    m_pMainQVBoxLayout->setSpacing(0);
    this->setWindowFlags(Qt::FramelessWindowHint);

    QScreen* pScreen = QGuiApplication::primaryScreen();
    QRect ScreenSize = pScreen->availableGeometry();
    int m_nScreenWidth = ScreenSize.width();        //屏幕分辨率的宽
    int m_nScreenHeight = ScreenSize.height();      //屏幕分辨率的高
    move(m_nScreenWidth/2-130, m_nScreenHeight/2-180);
    setLayout(m_pMainQVBoxLayout);
    setAttribute(Qt::WA_TranslucentBackground);
}

/* 标题和编辑框界面 */
void EditorWidget::editBox()
{
    m_pEditingArea = new QTextEdit();
    m_pEditingArea->setFixedSize(362, 200);
    m_pEditingArea->setFrameShape(QFrame::NoFrame);
    QColor color(255,255,255,16);
    QPalette paletteTextEdit = m_pEditingArea->palette();
    paletteTextEdit.setBrush(QPalette::Base, color);
    m_pEditingArea->setPalette(paletteTextEdit);
    QFont font = m_pEditingArea->font();
    font.setFamily("Noto Sans CJK SC");
    font.setPixelSize(14);
    m_pEditingArea->setFont(font);

    m_ptileLable = new QLabel(QObject::tr("Edit"));
    m_ptileLable->setFixedHeight(20);
    QTimer::singleShot(1, m_ptileLable, [=](){
        QFont font = m_ptileLable->font();
        font.setPixelSize(20);
        font.setFamily("Noto Sans CJK SC");
        m_ptileLable->setFont(font);
    });

    m_pEditLaout = new QVBoxLayout;
    m_pEditLaout->addWidget(m_ptileLable);
    m_pEditLaout->addItem(new QSpacerItem(12, 22));
    m_pEditLaout->addWidget(m_pEditingArea);
    m_pEditLaout->setSpacing(0);
    m_pEditWidget = new QWidget();
    m_pEditWidget->setAttribute(Qt::WA_TranslucentBackground);
    m_pEditWidget->setLayout(m_pEditLaout);
    m_pEditLaout->setContentsMargins(0, 0, 0, 0);
    return;
}

/* 确认和取消按钮 */
void EditorWidget::operationBox()
{
    m_pConfirmButton = new QPushButton(QObject::tr("Confirm"));
    m_pConfirmButton->setFixedSize(120, 34);
    m_pConfirmButton->setStyle(new CustomStyle("ukui-default"));

    m_pCancelButton  = new QPushButton(QObject::tr("Cancel"));
    m_pCancelButton->setFixedSize(120, 34);
    m_pCancelButton->setStyle(new CustomStyle_pushbutton_2("ukui-default") );

    m_pOperationLayout = new QHBoxLayout;

    m_pOperationLayout->setContentsMargins(0, 0, 0, 0);
    m_pOperationLayout->addItem(new QSpacerItem(106, 20, QSizePolicy::Expanding));
    m_pOperationLayout->addWidget(m_pCancelButton);
    m_pOperationLayout->addItem(new QSpacerItem(16, 20));
    m_pOperationLayout->addWidget(m_pConfirmButton);
    m_pOperationLayout->addItem(new QSpacerItem(20, 20));
    m_pOperationLayout->setSpacing(0);
    m_pOperationWidget = new QWidget();
    m_pOperationWidget->setContentsMargins(0, 0, 0, 0);
    m_pOperationWidget->setLayout(m_pOperationLayout);
    return;
}

/* 重绘时间 */
void EditorWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);

//    p.setBrush(QBrush(QColor("#131314")));
    p.setBrush(opt.palette.color(QPalette::Base));
    p.setOpacity(0.7);
    p.setPen(Qt::NoPen);

    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.drawRoundedRect(opt.rect,6,6);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void EditorWidget::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
}
