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
#include "sidebarpluginswidgets.h"

static sidebarPluginsWidgets *global_Plugin_Widgets_instance = nullptr;
sidebarPluginsWidgets::sidebarPluginsWidgets(QWidget *parent) : QWidget(parent)
{
    Q_UNUSED(parent);

    this->setContentsMargins(0,0,0,0);
    this->setFixedSize(400,300);
    this->setStyleSheet("QWidget{background:rgba(255, 255, 0, 0);}");
    flagnumClipboardState = 0;

    m_pBoolStates = true;
    resizeFlagOne = true;

    ClipBoardBool = false;
    SmallPluginsBool = false;

    m_pWidgetOutVLayout = new QVBoxLayout();
    m_pWidgetOutVLayout->setContentsMargins(0,0,0,0);

    /* 上半部分 剪贴板 小插件 俩按钮 groupBox初始化布局 */
    initUpGroupBoxButton();

    /* 下半部分 显示插件的界面 */
    initUnGroupBox();

    initLableBackgroundAnimation();
    initSmallPluginsAnimation();                               //初始化小插件动画类

    /* 初始化desktop文件名称放入链表中 */
    addDesktopFileName();

    /* 将闹钟、用户反馈等图标加入到界面 */
    parsingDesktopFile();

    QFile file(KYLIN_SIDEBAR_SMALL_PLUGINS);
    if (file.open(QFile::ReadOnly)) {
        QString strQss = QLatin1String(file.readAll());
        this->setStyleSheet(strQss);
        file.close();
    }
}

sidebarPluginsWidgets::~sidebarPluginsWidgets()
{

}

/* 返回全局的Widget指针 */
sidebarPluginsWidgets* sidebarPluginsWidgets::getInstancePluinsWidgets()
{
    if (global_Plugin_Widgets_instance == nullptr) {
        global_Plugin_Widgets_instance = new sidebarPluginsWidgets();
    }
    return global_Plugin_Widgets_instance;
}

/* 初始化sidebarPluginsWidgets类 */
void sidebarPluginsWidgets::initPluginsWidgets()
{
    getInstancePluinsWidgets();
    return;
}

/* 上半部分 剪贴板 小插件 俩按钮 groupBox初始化布局 */
void sidebarPluginsWidgets::initUpGroupBoxButton()
{
    m_pButtonWidget = new QWidget(this);
    m_pButtonWidget->setContentsMargins(0,0,0,0);
    m_pButtonWidget->setFixedSize(400, 60);

    m_pGrouBoxUpButtonHLayout = new QHBoxLayout;
    m_pGrouBoxUpButtonHLayout->setContentsMargins(0,5,0,0);

    //剪贴板按钮
    m_pClipboardButton = new SmallPluginsButton();
    m_pClipboardButton->setText(tr("Clipboard"));
    m_pClipboardButton->setObjectName("ClipboardButton");
    m_pClipboardButton->setFixedSize(90,34);
    connect(m_pClipboardButton, &SmallPluginsButton::clicked, this, &sidebarPluginsWidgets::m_ClipboardButtonSlots);

    //小插件按钮
    m_pSidebarPluginButton = new SmallPluginsButton();
    m_pSidebarPluginButton->setText(tr("Plugins"));
    m_pSidebarPluginButton->setObjectName("SidebarPluginButton");
    m_pSidebarPluginButton->setFixedSize(90,34);
    connect(m_pSidebarPluginButton, &SmallPluginsButton::clicked, this, &sidebarPluginsWidgets::m_SidebarPluginButtonSlots);

    setClipboardButtonBackgroundIsBlue();
    setSmallPluginsButtonBackgroudIsBlank();

    m_pFoldButton            = new QPushButton(QObject::tr("折叠"));
    m_pFoldButton->setFixedSize(90, 34);
    m_pSpreadButton          = new QPushButton(QObject::tr("展开"));
    m_pSpreadButton->setFixedSize(90, 34);
    m_pSpreadButton->setVisible(false);

    connect(m_pFoldButton, &QPushButton::clicked, this, &sidebarPluginsWidgets::m_pFoldButtonSlots);
    connect(m_pSpreadButton, &QPushButton::clicked, this, &sidebarPluginsWidgets::m_pSpreadButtonSlots);

    //蓝色背景块按钮
    m_pBlueBackgroundButton = new QPushButton();
    m_pBlueBackgroundButton->setFixedSize(90, 34);
    m_pBlueBackgroundButton->setObjectName("BlueBackgroundButton");
    m_pBlueBackgroundButton->setChecked(false);

    m_pBlueBackgroundButton->setVisible(false);

    m_pGrouBoxUpButtonHLayout->addItem(new QSpacerItem(10, 20));
    m_pGrouBoxUpButtonHLayout->addWidget(m_pClipboardButton);
    m_pGrouBoxUpButtonHLayout->addItem(new QSpacerItem(10, 20));
    m_pGrouBoxUpButtonHLayout->addWidget(m_pSidebarPluginButton);
    m_pGrouBoxUpButtonHLayout->addItem(new QSpacerItem(10, 20));
//    m_pGrouBoxUpButtonHLayout->addWidget(m_pFoldButton);
//    m_pGrouBoxUpButtonHLayout->addWidget(m_pSpreadButton);
    m_pGrouBoxUpButtonHLayout->addWidget(m_pBlueBackgroundButton);
    m_pGrouBoxUpButtonHLayout->addItem(new QSpacerItem(202, 20));
    m_pButtonWidget->setLayout(m_pGrouBoxUpButtonHLayout);
    m_pGrouBoxUpButtonHLayout->setSpacing(0);
//    m_pButtonWidget->setStyleSheet("QWidget{ border: 1px solid rgba(255,255,0,1);}");
    return;
}

/* 显示插件的界面下半部分 */
void sidebarPluginsWidgets::initUnGroupBox()
{
    /* 小插件GroupBox指针 */
    m_pPluginsButtonWidget = new QWidget();
    m_pPluginsButtonWidget->setFixedSize(400, 250);
    m_pPluginsButtonWidget->setContentsMargins(0,0,0,0);

    /* 设置按钮图表 */
    m_pGroupBoxUnSmallPluginsGLayout = new QGridLayout();
    m_pPluginsButtonWidget->setLayout(m_pGroupBoxUnSmallPluginsGLayout);
    m_pGroupBoxUnSmallPluginsGLayout->setSpacing(0);
    return;
}


/* 最后将所有空间加入到Widget中 */
void sidebarPluginsWidgets::AddPluginWidgetInterface()
{
    m_pstackWidget = new QStackedWidget();
    m_pstackWidget->setContentsMargins(0, 0, 0, 0);
    m_pstackWidget->addWidget(m_pClipboardWidget);                  //剪贴板Widget
    m_pstackWidget->addWidget(m_pPluginsButtonWidget);              //显示小插件的Widget
    m_pWidgetOutVLayout->addWidget(m_pButtonWidget);                //加载俩个按钮界面
    m_pWidgetOutVLayout->addWidget(m_pstackWidget);
    m_pWidgetOutVLayout->setSpacing(0);
    this->setLayout(m_pWidgetOutVLayout);
    return;
}

/* 移动到剪贴板按钮需要修改的界面 */
void sidebarPluginsWidgets::m_pClipBoardStateSlots()
{
    m_pBlueBackgroundButton->setVisible(false);
    setClipboardButtonBackgroundIsBlue();
    setSmallPluginsButtonBackgroudIsBlank();
    return;
}

/* 移动到小插件界面按钮需要做的界面修改 */
void sidebarPluginsWidgets::m_pSmallPluginsStateSlots()
{
    m_pBlueBackgroundButton->setVisible(false);
    setClipboardButtonBackgroundIsBlank();
    setSmallPluginsButtonBackgroudIsBlue();
    return;
}

/* 剪贴板按钮槽函数 */
void sidebarPluginsWidgets::m_ClipboardButtonSlots()
{
    if (!ClipBoardBool) {
        setSmallPluginsButtonBackgroudIsBlank();
        m_pstackWidget->setCurrentIndex(0);
        m_pAnimationClipbarod->start();
        m_pBlueBackgroundButton->setVisible(true);
        m_pAnimationRightLeft->start();
        SmallPluginsBool = false;
        ClipBoardBool = true;
    }
    return;
}

/* 小插件按钮槽函数 */
void sidebarPluginsWidgets::m_SidebarPluginButtonSlots()
{
    if (!SmallPluginsBool) {
        setClipboardButtonBackgroundIsBlank();
        m_pstackWidget->setCurrentIndex(1);
        m_pAnimationSmallWidget->start();
        m_pBlueBackgroundButton->setVisible(true);
        m_pAnimationLeftRight->start();
        ClipBoardBool = false;
        SmallPluginsBool = true;
    }
    return;
}

/* 折叠按钮槽函数 */
void sidebarPluginsWidgets::m_pFoldButtonSlots()
{
    m_pstackWidget->hide();
    this->setFixedSize(400, 60);
    m_pSpreadButton->setVisible(true);
    m_pFoldButton->setVisible(false);
    return;
}

/* 展开按钮槽函数 */
void sidebarPluginsWidgets::m_pSpreadButtonSlots()
{
    m_pstackWidget->show();
    this->setFixedSize(400, m_cliboardHight);
    m_pSpreadButton->setVisible(false);
    m_pFoldButton->setVisible(true);
    return;
}

/* 新建Lable的动画类 */
void sidebarPluginsWidgets::initLableBackgroundAnimation()
{
    m_pAnimationLeftRight = new QPropertyAnimation(m_pBlueBackgroundButton, "geometry");
    m_pAnimationLeftRight->setDuration(200);
    m_pAnimationLeftRight->setStartValue(QRect(10, 15, 90, 34));
    m_pAnimationLeftRight->setEndValue(QRect(108, 15, 90, 34));
    m_pAnimationRightLeft = new QPropertyAnimation(m_pBlueBackgroundButton, "geometry");
    m_pAnimationRightLeft->setDuration(200);
    m_pAnimationRightLeft->setStartValue(QRect(108, 15, 90, 34));
    m_pAnimationRightLeft->setEndValue(QRect(10, 15, 90, 34));
    connect(m_pAnimationLeftRight, &QPropertyAnimation::finished, this, &sidebarPluginsWidgets::m_pSmallPluginsStateSlots);
    connect(m_pAnimationRightLeft, &QPropertyAnimation::finished, this, &sidebarPluginsWidgets::m_pClipBoardStateSlots);
    return;
}

/* 初始化剪贴板动画 */
void sidebarPluginsWidgets::initCliboardAnimation()
{
   m_pAnimationClipbarod = new QPropertyAnimation(m_pClipboardWidget, "geometry");
   m_pAnimationClipbarod->setDuration(300);
   m_pAnimationClipbarod->setStartValue(QRect(400, 0, 400, m_cliboardHight));
   m_pAnimationClipbarod->setEndValue(QRect(0, 0, 400, m_cliboardHight));
   connect(m_pAnimationClipbarod, &QPropertyAnimation::finished, this, &sidebarPluginsWidgets::m_AnimationClipbarodEndSlots);
   return;
}

/* 初始化小插件动画 */
void sidebarPluginsWidgets::initSmallPluginsAnimation()
{
    m_pAnimationSmallWidget = new QPropertyAnimation(m_pPluginsButtonWidget, "geometry");
    m_pAnimationSmallWidget->setDuration(300);
    m_pAnimationSmallWidget->setStartValue(QRect(400, 0, 400, m_cliboardHight));
    m_pAnimationSmallWidget->setEndValue(QRect(0, 0, 400, m_cliboardHight));
    connect(m_pAnimationSmallWidget, &QPropertyAnimation::finished, this, &sidebarPluginsWidgets::m_AnimationSmallWidgetEndSlots);
    return;
}

void sidebarPluginsWidgets::m_AnimationClipbarodEndSlots()
{
}

void sidebarPluginsWidgets::m_AnimationSmallWidgetEndSlots()
{
}

/* 设置侧边栏的按钮背景色为蓝色 */
void sidebarPluginsWidgets::setClipboardButtonBackgroundIsBlue()
{
    m_pClipboardButton->setStyleSheet("QPushButton#ClipboardButton{background:rgba(61,107,229,1);}");
}

void sidebarPluginsWidgets::setSmallPluginsButtonBackgroudIsBlue()
{
    m_pSidebarPluginButton->setStyleSheet("QPushButton#SidebarPluginButton{background:rgba(61,107,229,1);}");
}

void sidebarPluginsWidgets::setClipboardButtonBackgroundIsBlank()
{
    m_pClipboardButton->setStyleSheet("QPushButton#ClipboardButton{background:rgba(61,107,229,0);}");
}

void sidebarPluginsWidgets::setSmallPluginsButtonBackgroudIsBlank()
{
    m_pSidebarPluginButton->setStyleSheet("QPushButton#SidebarPluginButton{background:rgba(61,107,229,0);}");
}

/* 设置剪贴板的高度 */
void sidebarPluginsWidgets::setClipboardWidgetSize(int ClipHight)
{
    m_cliboardHight = ClipHight;
    qDebug() << "设置小剪贴板的界面大小---->" << ClipHight;
    this->setFixedSize(400, ClipHight);
    m_pClipboardWidget->setFixedSize(400, ClipHight - 50);
    m_pPluginsButtonWidget->setFixedSize(400, ClipHight - 50);
    return;
}

/* 解析Desktop文件，获取应用的图标 */
QString sidebarPluginsWidgets::getAppIcon(QString desktopfp)
{
    GError** error=nullptr;
    GKeyFileFlags flags=G_KEY_FILE_NONE;
    GKeyFile* keyfile=g_key_file_new ();

    QByteArray fpbyte=desktopfp.toLocal8Bit();
    char* filepath=fpbyte.data();
    g_key_file_load_from_file(keyfile,filepath,flags,error);
    char* icon=g_key_file_get_locale_string(keyfile,"Desktop Entry","Icon", nullptr, nullptr);
    g_key_file_free(keyfile);
    return QString::fromLocal8Bit(icon);
}

//获取应用命令
QString sidebarPluginsWidgets::getAppExec(QString desktopfp)
{
    GError** error=nullptr;
    GKeyFileFlags flags=G_KEY_FILE_NONE;
    GKeyFile* keyfile=g_key_file_new ();

    QByteArray fpbyte=desktopfp.toLocal8Bit();
    char* filepath=fpbyte.data();
    g_key_file_load_from_file(keyfile,filepath,flags,error);
    char* exec=g_key_file_get_locale_string(keyfile,"Desktop Entry","Exec", nullptr, nullptr);
    g_key_file_free(keyfile);
    return QString::fromLocal8Bit(exec);
}

/* 获取应用名称 */
QString sidebarPluginsWidgets::getAppName(QString desktopfp)
{
    GError** error=nullptr;
    GKeyFileFlags flags=G_KEY_FILE_NONE;
    GKeyFile* keyfile=g_key_file_new ();

    QByteArray fpbyte=desktopfp.toLocal8Bit();
    char* filepath=fpbyte.data();
    g_key_file_load_from_file(keyfile,filepath,flags,error);

    char* name=g_key_file_get_locale_string(keyfile,"Desktop Entry","Name", nullptr, nullptr);
    QString namestr=QString::fromLocal8Bit(name);
    g_key_file_free(keyfile);
    return namestr;
}

/* 将小插件desktop文件名称放入到desktopfpList中 */
void sidebarPluginsWidgets::addDesktopFileName()
{
    m_desktopfpList.append("clock.desktop"); "feedback.desktop";
    m_desktopfpList.append("ukui_notebook.desktop");
#if (QT_VERSION >= QT_VERSION_CHECK(5, 7, 0))
    m_desktopfpList.append("feedback.desktop");
#endif
    return;
}

/* 解析链表中保存desktop文件 */
void sidebarPluginsWidgets::parsingDesktopFile()
{
    int tmp = m_desktopfpList.size();
    QSpacerItem *item1 = new QSpacerItem(10, 20);
    for (int i = 0; i < tmp; i++) {
        QString desktopfp = "/usr/share/applications/" + m_desktopfpList.at(i);
        QString icon = getAppIcon(desktopfp);
        QString name = getAppName(desktopfp);
        QString Exec = getAppExec(desktopfp);
        QToolButton *p_button = StructToolButtol(icon, name);
        connect(p_button, &QToolButton::clicked, this, [=](){
            QProcess p(0);
            p.startDetached(Exec);
            p.waitForStarted();
            return;
        });
        if (p_button == nullptr) {
            continue;
            i--;
        }
        m_pGroupBoxUnSmallPluginsGLayout->addItem(item1, m_add_x, m_add_y - 1);
        m_pGroupBoxUnSmallPluginsGLayout->addWidget(p_button, m_add_x, m_add_y);
        m_add_y += 2;
        if (m_add_y > 8) {
            m_add_x++;
            m_add_y = 1;
        }
        qDebug() << "add_y" << m_add_y << "add_x" << m_add_x;
    }
    return;
}

/* 构建小插件图标 */
QToolButton* sidebarPluginsWidgets::StructToolButtol(QString icon, QString name)
{
    QToolButton *p_ToolButton = new QToolButton();
    p_ToolButton->setFixedSize(90,90);
    QPixmap pixmap = QIcon::fromTheme(icon).pixmap(QSize(45, 45));
    QLabel *IconLabel = new QLabel();
    IconLabel->setFixedSize(45, 45);
    IconLabel->setPixmap(pixmap);
    QLabel *textLabel = new QLabel();
    textLabel->setText(name);
    QVBoxLayout *ToolButtonLaout = new QVBoxLayout();
    ToolButtonLaout->setContentsMargins(0, 0, 0, 0);
    ToolButtonLaout->addItem(new QSpacerItem(10, 12, QSizePolicy::Expanding));
    ToolButtonLaout->addWidget(IconLabel, 0, Qt::AlignCenter);
    ToolButtonLaout->addItem(new QSpacerItem(10, 9, QSizePolicy::Expanding));
    ToolButtonLaout->addWidget(textLabel, 0, Qt::AlignCenter);
    ToolButtonLaout->addSpacerItem(new QSpacerItem(10, 7));
    p_ToolButton->setLayout(ToolButtonLaout);
    p_ToolButton->setStyle(new CustomStyle("ukui-default"));
    qDebug() << "插件接口名称" << name;
    return p_ToolButton;
}

void sidebarPluginsWidgets::setButtonFont()
{
    QPalette paletteButton = QApplication::palette();
    paletteButton.setBrush(QPalette::Text,paletteButton.color(QPalette::WindowText));
    qDebug() << "color -->" << paletteButton.color(QPalette::WindowText);
    m_pClipboardButton->setPalette(paletteButton);
    m_pSidebarPluginButton->setPalette(paletteButton);
    return;
}

//重新绘制背景色
void sidebarPluginsWidgets::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    /* 获取当前剪贴板中字体的颜色，作为背景色；
     * 白字体 --> 黑背景
     * 黑字体 --> 白字体
    */
//    p.setBrush(opt.palette.color(QPalette::Base).lighter(85));
    p.setBrush(opt.palette.color(QPalette::Base));
//    p.setBrush(QBrush(QColor("#161617")));
    p.setOpacity(0.42);
    p.setPen(Qt::NoPen);

    p.setRenderHint(QPainter::Antialiasing);                        //反锯齿
    p.drawRoundedRect(opt.rect,0,0);
    p.drawRect(opt.rect);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

/* 小插件加载 */
void sidebarPluginsWidgets::loadSmallPlugins()
{
    /* Iterative m_pSmallPluginsHash hash table */
    int pluginsNum = SmallPluginsManage::getInstance()->m_PluginsNum;
    int Sequence = 1;
    QSpacerItem *item1 = new QSpacerItem(10, 20);
    while (pluginsNum) {
        QHash<PluginInterface*, SidebarSmallPluginInterface*> ::const_iterator iter1 = SmallPluginsManage::getInstance()->m_pSmallPluginsHash.constBegin();
        while (iter1 != SmallPluginsManage::getInstance()->m_pSmallPluginsHash.constEnd()) {
                if (iter1.value()->pluginsLoadingSequence() == Sequence) {
                    QToolButton *p_ToolButton = new QToolButton();
                    p_ToolButton->setFixedSize(90,90);
                    QPixmap pixmap = iter1.value()->icon().pixmap(QSize(45, 45));
                    QLabel *IconLabel = new QLabel();
                    IconLabel->setFixedSize(45, 45);
                    IconLabel->setPixmap(pixmap);
                    QLabel *textLabel = new QLabel();
                    textLabel->setText(iter1.value()->PluginButtonName());
                    QVBoxLayout *ToolButtonLaout = new QVBoxLayout();
                    ToolButtonLaout->setContentsMargins(0, 0, 0, 0);
                    ToolButtonLaout->addItem(new QSpacerItem(10, 12, QSizePolicy::Expanding));
                    ToolButtonLaout->addWidget(IconLabel, 0, Qt::AlignCenter);
                    ToolButtonLaout->addItem(new QSpacerItem(10, 9, QSizePolicy::Expanding));
                    ToolButtonLaout->addWidget(textLabel, 0, Qt::AlignCenter);
                    ToolButtonLaout->addSpacerItem(new QSpacerItem(10, 7));
                    p_ToolButton->setLayout(ToolButtonLaout);
                    p_ToolButton->setStyle(new CustomStyle("ukui-default"));
                    p_ToolButton->setIconSize(QSize(iter1.value()->PluginIconSize_W(), iter1.value()->PluginIconSize_H()));
                    m_pGroupBoxUnSmallPluginsGLayout->addItem(item1, m_add_x, m_add_y - 1);
                    m_pGroupBoxUnSmallPluginsGLayout->addWidget(p_ToolButton, m_add_x, m_add_y);
                    connect(p_ToolButton, &QToolButton::clicked, this, [=]() {
                        iter1.value()->PluginsShowInterface();
                    });
                    pluginsNum--;
                    m_add_y += 2;
                    if (m_add_y > 8) {
                        m_add_x++;
                        m_add_y = 1;
                    }
                    break;
                }
                ++iter1;
        }
        Sequence++;
        if (Sequence > KYLIN_PLUGINS_NUM) {
            break;
        }
    }
    qDebug() << "x -->" << m_add_x << "y -->" << m_add_y;
    if (m_add_x < 1) {
        m_pGroupBoxUnSmallPluginsGLayout->addItem(new QSpacerItem(400 - 100*(m_add_y/2), 0), m_add_x, m_add_y - 1);
        m_pGroupBoxUnSmallPluginsGLayout->setContentsMargins(0, 0, 0, 250 - 90*(m_add_x + 1));
        m_pGroupBoxUnSmallPluginsGLayout->setVerticalSpacing(10);
    } else {
        m_pGroupBoxUnSmallPluginsGLayout->setContentsMargins(0, 0, 0, 30);
    }
//    m_pGroupBoxUnSmallPluginsGLayout->setVerticalSpacing(0);
//    m_pGroupBoxUnSmallPluginsGLayout->setHorizontalSpacing(0);
//    m_pGroupBoxUnSmallPluginsGLayout->setSpacing(0);
    return;
}
