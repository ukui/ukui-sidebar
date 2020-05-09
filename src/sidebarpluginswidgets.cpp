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

    /* 初始化desktop文件名称放入链表中 */
//    addDesktopFileName();

    /* 将闹钟、用户反馈等图标加入到界面 */
//    parsingDesktopFile();

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
}

/* 上半部分 剪贴板 小插件 俩按钮 groupBox初始化布局 */
void sidebarPluginsWidgets::initUpGroupBoxButton()
{
    m_pButtonWidget = new QWidget(this);
    m_pButtonWidget->setContentsMargins(0,0,0,0);
    m_pButtonWidget->setFixedSize(400, 60);

    m_pGrouBoxUpButtonHLayout = new QHBoxLayout;
    m_pGrouBoxUpButtonHLayout->setContentsMargins(0,5,0,0);

    m_pClipboardButton = new SmallPluginsButton();
    m_pClipboardButton->setText(tr("Clipboard"));
    m_pClipboardButton->setObjectName("ClipboardButton");
    m_pClipboardButton->setFixedSize(90,34);


    m_pSidebarPluginButton = new SmallPluginsButton();
    m_pSidebarPluginButton->setText(tr("Plugins"));
    m_pSidebarPluginButton->setObjectName("SidebarPluginButton");
    m_pSidebarPluginButton->setFixedSize(90,34);

    m_pBlueBackgroundButton = new QPushButton();
    m_pBlueBackgroundButton->setFixedSize(90, 34);
    m_pBlueBackgroundButton->setObjectName("BlueBackgroundButton");
    m_pBlueBackgroundButton->setChecked(false);

    m_pBlueBackgroundButton->setVisible(false);


    QSpacerItem *item1 = new QSpacerItem(10, 20);
    QSpacerItem *item2 = new QSpacerItem(10, 20);
    QSpacerItem *item3 = new QSpacerItem(202,20);
    m_pGrouBoxUpButtonHLayout->addItem(item1);
    m_pGrouBoxUpButtonHLayout->addWidget(m_pClipboardButton);
    m_pGrouBoxUpButtonHLayout->addItem(item2);
    m_pGrouBoxUpButtonHLayout->addWidget(m_pSidebarPluginButton);
    m_pGrouBoxUpButtonHLayout->addItem(item1);
    m_pGrouBoxUpButtonHLayout->addWidget(m_pBlueBackgroundButton);
    m_pGrouBoxUpButtonHLayout->addItem(item3);
    m_pButtonWidget->setLayout(m_pGrouBoxUpButtonHLayout);
    m_pGrouBoxUpButtonHLayout->setSpacing(0);
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
}


/* 最后将所有空间加入到Widget中 */
void sidebarPluginsWidgets::AddPluginWidgetInterface()
{
    m_pWidgetOutVLayout->addWidget(m_pButtonWidget);                //加载俩个按钮界面
    m_pWidgetOutVLayout->addWidget(m_pClipboardWidget);             //剪贴板Widget
    m_pWidgetOutVLayout->addWidget(m_pPluginsButtonWidget);         //显示小插件的Widget
    m_pWidgetOutVLayout->setSpacing(0);
    this->setLayout(m_pWidgetOutVLayout);

    /* 状态机初始化 */
    m_pMachine = new QStateMachine();
    m_pClipBoardState = new QState(m_pMachine);
    m_pSmallPluginsState = new QState(m_pMachine);

    /* 给状态机分配属性 状态一，剪贴板状态 */
    m_pClipBoardState->assignProperty(m_pClipboardWidget, "geometry", QRectF(0, 50, 400, 250));
    m_pClipBoardState->assignProperty(m_pPluginsButtonWidget, "geometry", QRectF(400, 50, 400, 250));

    /* 给状态机分配属性 状态二，小插件页面状态 */
    m_pSmallPluginsState->assignProperty(m_pClipboardWidget, "geometry", QRectF(400, 50, 400, 250));
    m_pSmallPluginsState->assignProperty(m_pPluginsButtonWidget, "geometry", QRectF(0, 50, 400, 250));

    /* 给状态机配置状态转换信号 */
    QAbstractTransition *t1 = m_pClipBoardState->addTransition(m_pSidebarPluginButton, SIGNAL(enterButtonSignal()), m_pSmallPluginsState);
    t1->addAnimation(new QPropertyAnimation(m_pPluginsButtonWidget, "geometry"));

    QAbstractTransition *t2 = m_pSmallPluginsState->addTransition(m_pClipboardButton, SIGNAL(enterButtonSignal()), m_pClipBoardState);
    t2->addAnimation(new QPropertyAnimation(m_pClipboardWidget, "geometry"));

    /* 初始化状态机时所要做的事情 */
    connect(m_pClipBoardState, &QState::propertiesAssigned, this, [=]{
        if (resizeFlagOne) {
            m_pPluginsButtonWidget->setVisible(true);
            m_pPluginsButtonWidget->show();
            resizeFlagOne = false;
            m_pSidebarPluginButton->SendSingal();
            qDebug() << "剪贴板界面 --> 进入小插件界面";
        }

        if (ClipBoardBool) {
            qDebug() << "修改分辨率后状态已转换完成，当前状态在剪贴板界面";
            mostGrandWidget::getInstancemostGrandWidget()->hide();
            ClipBoardBool = false;
        }
    });

    connect(m_pSmallPluginsState, &QState::propertiesAssigned, this, [=]{
        if (m_pBoolStates) {
            m_pPluginsButtonWidget->setVisible(true);
            m_pBoolStates = false;
            m_pClipboardButton->SendSingal();
            qDebug() << "小插件界面 --> 进入剪贴板界面";
            mostGrandWidget::getInstancemostGrandWidget()->hide();
        }

        if (SmallPluginsBool) {
            qDebug() << "修改分辨率后状态已转换完成，当前状态在小插件界面";
            mostGrandWidget::getInstancemostGrandWidget()->hide();
            SmallPluginsBool = false;
        }
    });

    /* 进入状态机一需要将小插件按钮的背景设置成空白 */
    connect(m_pClipBoardState, &QState::entered, this, [=](){
        setSmallPluginsButtonBackgroudIsBlank();
//        m_pSidebarPluginButton->setStyle(BlankButtonStyle);
        m_pBlueBackgroundButton->setVisible(true);
        m_pAnimationRightLeft->start();
        m_statusFlag = KYLIN_STATE_CLIPBOARD;
    });

    /* 进入状态机二时将按钮小插件的背景设置成空白 */
    connect(m_pSmallPluginsState, &QState::entered, this, [=](){
        setClipboardButtonBackgroundIsBlank();
//        m_pClipboardButton->setStyle(BlankButtonStyle);
        m_pBlueBackgroundButton->setVisible(true);
        m_pAnimationLeftRight->start();
        m_statusFlag = KYLIN_STATE_SMALL_PLUGINS;
    });

    m_pPluginsButtonWidget->setVisible(false);
    m_pMachine->setInitialState(m_pClipBoardState);
    m_pMachine->start();
}

/* 移动到剪贴板按钮需要修改的界面 */
void sidebarPluginsWidgets::m_pClipBoardStateSlots()
{
    m_pBlueBackgroundButton->setVisible(false);
    setClipboardButtonBackgroundIsBlue();
    setSmallPluginsButtonBackgroudIsBlank();
}

/* 移动到小插件界面按钮需要做的界面修改 */
void sidebarPluginsWidgets::m_pSmallPluginsStateSlots()
{
    m_pBlueBackgroundButton->setVisible(false);
    setClipboardButtonBackgroundIsBlank();
    setSmallPluginsButtonBackgroudIsBlue();
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
    qDebug() << "设置小剪贴板的界面大小---->" << ClipHight;
    this->setFixedSize(400, ClipHight);
    m_pClipboardWidget->setFixedSize(400, ClipHight - 50);

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
    m_desktopfpList << "kylin-assistant.desktop" << "kylin-video.desktop" << "kylin-update-manager.desktop";
    return;
}

/* 解析链表中保存desktop文件 */
void sidebarPluginsWidgets::parsingDesktopFile()
{
    int tmp = m_desktopfpList.size();
    QSpacerItem *item1 = new QSpacerItem(10, 20);
    int add_x = 0;
    int add_y = 1;
    for (int i = 0; i < tmp; i++) {
        QString desktopfp = "/usr/share/applications/" + m_desktopfpList.at(i);
        QString icon=getAppIcon(desktopfp);
        QString name=getAppName(desktopfp);
        QToolButton *p_button = StructToolButtol(icon, name);
        m_pGroupBoxUnSmallPluginsGLayout->addItem(item1, add_x, add_y - 1);
        m_pGroupBoxUnSmallPluginsGLayout->addWidget(p_button, add_x, add_y);
        add_y += 2;
        if (add_y > 8) {
            add_x++;
            add_y = 1;
        }
    }
    QSpacerItem *item2 = new QSpacerItem(400 - 100*(add_y/2), 20);
    m_pGroupBoxUnSmallPluginsGLayout->addItem(item2, add_x, add_y - 1);
    m_pGroupBoxUnSmallPluginsGLayout->setContentsMargins(0, 19, 0, 250 - 90*(add_x + 1));
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
    qDebug() << "加载插件的个数" << pluginsNum;
    int Sequence = 1;
    int add_x = 0;
    int add_y = 1;
    QSpacerItem *item1 = new QSpacerItem(10, 20);
    while (pluginsNum) {
        QHash<PluginInterface*, SidebarSmallPluginInterface*> ::const_iterator iter1 = SmallPluginsManage::getInstance()->m_pSmallPluginsHash.constBegin();
        while (iter1 != SmallPluginsManage::getInstance()->m_pSmallPluginsHash.constEnd()) {
                qDebug() << "当前插件加载的序号 --> " << iter1.value()->pluginsLoadingSequence();
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
                    qDebug() << "插件接口名称" << iter1.value()->PluginButtonName();
                    p_ToolButton->setIconSize(QSize(iter1.value()->PluginIconSize_W(), iter1.value()->PluginIconSize_H()));
                    m_pGroupBoxUnSmallPluginsGLayout->addItem(item1, add_x, add_y - 1);
                    m_pGroupBoxUnSmallPluginsGLayout->addWidget(p_ToolButton, add_x, add_y);
                    connect(p_ToolButton, &QToolButton::clicked, this, [=]() {
                        iter1.value()->PluginsShowInterface();
                    });
                    pluginsNum--;
                    add_y += 2;
                    if (add_y > 8) {
                        add_x++;
                        add_y = 1;
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
    qDebug() << "x -->" << add_x << "y -->" << add_y;
    QSpacerItem *item2 = new QSpacerItem(400 - 100*(add_y/2), 20);
    m_pGroupBoxUnSmallPluginsGLayout->addItem(item2, add_x, add_y - 1);
    m_pGroupBoxUnSmallPluginsGLayout->setContentsMargins(0, 19, 0, 250 - 90*(add_x + 1));
}
