#include "notification_plugin.h"
#include "scrollareawidget.h"
#include <QSvgRenderer>



NotificationPlugin::NotificationPlugin()
{
    m_pMainWidget = new QWidget;

    //插件的总VBoxLayout布局器
    QVBoxLayout* pNotificationVBoxLayout = new QVBoxLayout;
    pNotificationVBoxLayout->setContentsMargins(10,21,0,0);
    pNotificationVBoxLayout->setSpacing(0);

    //装第一行通知中心的Widget
    QWidget* pWidget1= new QWidget;
    pWidget1->setFixedWidth(390);

    //第一行通知中心标题栏，左侧标题“通知中心”，右侧收纳按钮
    QHBoxLayout* pQHBoxLayout1 = new QHBoxLayout;
    pQHBoxLayout1->setContentsMargins(11,0,28,0);
    pQHBoxLayout1->setSpacing(0);
    QLabel* pLabel = new QLabel("通知中心");
    pLabel->setStyleSheet("QLabel{border:0px solid #242424;padding:0px;}");
    QFont font("NotoSansCJKsc-Regular", 20, 50);
    pLabel->setFont(font);

    //收纳按钮
    QToolButton* pQToolButton = new QToolButton();
    pQToolButton->setStyleSheet("QToolButton{border:0px solid #242424;padding:0px;background:transparent;}");
    pQToolButton->resize(22, 24);
    //QToolButton添加svg图片
    QSvgRenderer* pSvgRender = new QSvgRenderer;
    QString strSvg = ":/images/收纳盒.svg";
    pSvgRender->load(strSvg);
    QPixmap* pPixmap = new QPixmap(22, 24);
    pPixmap->fill(Qt::transparent);
    QPainter painter(pPixmap);
    pSvgRender->render(&painter);
    pQToolButton->setIcon(QIcon(*pPixmap));

    pQHBoxLayout1->addWidget(pLabel, 0, Qt::AlignLeft);
    pQHBoxLayout1->addWidget(pQToolButton, 0, Qt::AlignRight);
    pWidget1->setLayout(pQHBoxLayout1);
    pNotificationVBoxLayout->addWidget(pWidget1);

    QSpacerItem* pVFixedSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
    pNotificationVBoxLayout->addSpacerItem(pVFixedSpacer);

    //装第二行重要信息中的Widget
    QWidget* pWidget2= new QWidget;
    pWidget2->setFixedWidth(390);

    //第二行左侧标签“重要的信息”，右侧一个清空按钮，一个设置按钮
    QHBoxLayout* pQHBoxLayout2 = new QHBoxLayout;
    pQHBoxLayout2->setContentsMargins(12,0,10,10);
    pQHBoxLayout2->setSpacing(0);
    pLabel = new QLabel("重要的信息");
    pLabel->setStyleSheet("QLabel{border:0px solid #242424;padding:0px;}");
    pLabel->resize(70, 14);
    QFont font1("NotoSansCJKsc-Regular", 14, 50);
    pLabel->setFont(font1);

    QSpacerItem* pHSpacer = new QSpacerItem(300, 10, QSizePolicy::Expanding, QSizePolicy::Fixed);

    QPushButton* pClearAllToolButton = new QPushButton();
    connect(pClearAllToolButton, SIGNAL(clicked()), this, SLOT(clearAllMessage()));
    pClearAllToolButton->setText("清空");
    pClearAllToolButton->setFixedSize(80,34);
//    pClearAllToolButton->setStyleSheet("QToolButton{border-style:flat;}");

    QSpacerItem* pFixSpacer = new QSpacerItem(5, 10, QSizePolicy::Fixed, QSizePolicy::Fixed);

    QPushButton* pSettingToolButton = new QPushButton();
    connect(pSettingToolButton, SIGNAL(clicked()), this, SLOT(callControlPanel()));
    pSettingToolButton->setText("设置");
    pSettingToolButton->setFixedSize(80,34);


    pQHBoxLayout2->addWidget(pLabel, 0, Qt::AlignLeft);
    pQHBoxLayout2->addSpacerItem(pHSpacer);
    pQHBoxLayout2->addWidget(pClearAllToolButton, 0, Qt::AlignRight);
    pQHBoxLayout2->addSpacerItem(pFixSpacer);
    pQHBoxLayout2->addWidget(pSettingToolButton, 0, Qt::AlignRight);
    pWidget2->setLayout(pQHBoxLayout2);
    pNotificationVBoxLayout->addWidget(pWidget2, 0);

    //通知列表
    ScrollAreaWidget* pQScrollArea = new ScrollAreaWidget();

    m_pScrollAreaVBoxLayout = new QVBoxLayout();
    m_pScrollAreaVBoxLayout->setContentsMargins(0, 0, 0, 0);

    QWidget* pInQWidget = new QWidget();  //收纳通知列表的最内层部件
    pInQWidget->setLayout(m_pScrollAreaVBoxLayout);
    pQScrollArea->setWidget(pInQWidget);
//    pQScrollArea->widget()->adjustSize();

    m_pMessageCenterLabel = new QLabel("没有新通知");
    m_pMessageCenterLabel->setStyleSheet("QLabel{padding:0px 0px 0px 11px;}");
    m_pScrollAreaVBoxLayout->addWidget(m_pMessageCenterLabel);
    QSpacerItem* pVSpacer = new QSpacerItem(10, 10, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_pScrollAreaVBoxLayout->addSpacerItem(pVSpacer);


    pNotificationVBoxLayout->addWidget(pQScrollArea, 0);

    m_pMainWidget->setLayout(pNotificationVBoxLayout);
    return;
}


QWidget* NotificationPlugin::centerWidget()
{
    return  m_pMainWidget;
}

uint NotificationPlugin::Notify(QString strAppName, uint uId, QString strIconPath, QString strSummary, QString strBody, QStringList actions, QVariantMap hint, int nTimeout)
{
    Q_UNUSED(uId);
    Q_UNUSED(actions);
    Q_UNUSED(hint);
    Q_UNUSED(nTimeout);

    qDebug() <<"NotificationPlugin::Notify strAppName=" <<strAppName;
    if(0 == m_listSingleMsg.count() && 2 == m_pScrollAreaVBoxLayout->count()) //当列表信息为空表明第一次来通知
    {
        m_pScrollAreaVBoxLayout->removeWidget(m_pMessageCenterLabel);
        delete m_pMessageCenterLabel;
    }

    QDateTime dateTime(QDateTime::currentDateTime());

    SingleMsg* pSingleMsg = new SingleMsg(this, strAppName, strIconPath, strSummary, dateTime, strBody);
    m_listSingleMsg.append(pSingleMsg);
    m_pScrollAreaVBoxLayout->insertWidget((m_pScrollAreaVBoxLayout->count() - 1), pSingleMsg);

    return 1;
}

void NotificationPlugin::onClearMsg(SingleMsg* pSingleMsg)
{
    int nIndex = m_listSingleMsg.indexOf(pSingleMsg);
    if(-1 == nIndex)
    {
        qDebug()<<"Widget::onClearMsg 在链表中未找到pSingleMsg指针";
        return;
    }

    m_listSingleMsg.removeAt(nIndex);
    m_pScrollAreaVBoxLayout->removeWidget(pSingleMsg);
    pSingleMsg->deleteLater();

    if(0 == m_listSingleMsg.count() && 1 == m_pScrollAreaVBoxLayout->count())
    {
        m_pMessageCenterLabel = new QLabel("没有新通知");
        m_pMessageCenterLabel->setStyleSheet("QLabel{padding:0px 0px 0px 11px;}");
        m_pScrollAreaVBoxLayout->insertWidget((m_pScrollAreaVBoxLayout->count() - 1), m_pMessageCenterLabel);
    }
    return;
}

void NotificationPlugin::clearAllMessage()
{
    while (m_listSingleMsg.count() > 0)
    {
        SingleMsg* pSingleMsg = m_listSingleMsg.at(0);
        m_pScrollAreaVBoxLayout->removeWidget(pSingleMsg);
        pSingleMsg->deleteLater();
        m_listSingleMsg.removeAt(0);
    }

    if(1 == m_pScrollAreaVBoxLayout->count())
    {
        m_pMessageCenterLabel = new QLabel("没有新通知");
        m_pMessageCenterLabel->setStyleSheet("QLabel{padding:0px 0px 0px 11px;}");
        m_pScrollAreaVBoxLayout->insertWidget((m_pScrollAreaVBoxLayout->count() - 1), m_pMessageCenterLabel);
    }

    return;
}


