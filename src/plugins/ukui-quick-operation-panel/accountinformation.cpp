#include <stdio.h>
#include <pwd.h>
#include <unistd.h>
#include "accountinformation.h"

AccountInformation::AccountInformation(QWidget *parent) : QWidget(parent)
{
    initMemberVariable();
    registeredAccountsDbus();
    setAllControlsLabelInfo();
    initLayout();
}

void AccountInformation::initMemberVariable()
{
    m_pHeadPortraitIconLabel = new IconLabel();
    m_pHeadPortraitIconLabel->setFixedSize(48, 48);
    connect(m_pHeadPortraitIconLabel, &IconLabel::LabelClicked, this, &AccountInformation::openContorlCenterWidgetSlots);

    m_pNameLabel = new QLabel();
    m_pNameLabel->setFixedHeight(24);
    QFont font = m_pNameLabel->font();
    font.setPixelSize(16);
    m_pNameLabel->setFont(font);
    this->update();
    m_pIdentityLabel = new QLabel();
    m_pIdentityLabel->setFixedHeight(24);
    font = m_pIdentityLabel->font();
    font.setPixelSize(12);
    m_pIdentityLabel->setFont(font);

    m_pShutDownButton = new QPushButton();
    m_pShutDownButton->setFixedSize(48, 48);
    connect(m_pShutDownButton, &QPushButton::clicked, this, &AccountInformation::openShutdownWidgetSlots);
    QPalette palette = m_pShutDownButton->palette();
    QColor color = palette.color(QPalette::Button);
    color.setAlphaF(0);
    palette.setBrush(QPalette::Button, QBrush(color));
    m_pShutDownButton->setPalette(palette);
    m_pMainLayout = new QHBoxLayout();
    m_pMainLayout->setContentsMargins(0, 0, 0, 0);
    m_pMainLayout->setSpacing(0);

    m_pVLabelLayout = new QVBoxLayout();
    m_pVLabelLayout->setContentsMargins(0, 0, 0, 0);
    m_pVLabelLayout->setSpacing(0);

    m_pInfoWidget = new QWidget();
    m_pInfoWidget->setContentsMargins(0, 0, 0, 0);
    m_pInfoWidget->setFixedHeight(48);
}

void AccountInformation::initLayout()
{
    /* 设置中间俩个label界面 */
    m_pVLabelLayout->addWidget(m_pNameLabel, Qt::AlignVCenter);
    m_pVLabelLayout->addWidget(m_pIdentityLabel, Qt::AlignVCenter);
    m_pVLabelLayout->addItem(new QSpacerItem(1, 5));
    m_pInfoWidget->setLayout(m_pVLabelLayout);

    m_pMainLayout->addItem(new QSpacerItem(32, 10));
    m_pMainLayout->addWidget(m_pHeadPortraitIconLabel, Qt::AlignVCenter);
    m_pMainLayout->addItem(new QSpacerItem(8, 5));
    m_pMainLayout->addWidget(m_pInfoWidget);
    m_pMainLayout->addItem(new QSpacerItem(188, 20, QSizePolicy::Expanding));
    m_pMainLayout->addWidget(m_pShutDownButton);
    m_pMainLayout->addItem(new QSpacerItem(20, 10));
    this->setLayout(m_pMainLayout);
}

void AccountInformation::registeredAccountsDbus()
{
    m_pSystemUserIface = new QDBusInterface("org.freedesktop.Accounts",
                                     "/org/freedesktop/Accounts",
                                     "org.freedesktop.Accounts",
                                     QDBusConnection::systemBus());
}

QStringList AccountInformation::getUserObjectPath()
{
    QStringList users;
    QDBusReply<QList<QDBusObjectPath> > reply = m_pSystemUserIface->call("ListCachedUsers");
    if (reply.isValid()) {
        for (QDBusObjectPath op : reply.value())
            users << op.path();
    }
    return users;
}

UserInfomation AccountInformation::GetUserInformation(QString objpath)
{
    UserInfomation user;

    //默认值
    user.current = false;
    user.logined = false;
    user.autologin = false;
    QDBusInterface * iproperty = new QDBusInterface("org.freedesktop.Accounts",
                                            objpath,
                                            "org.freedesktop.DBus.Properties",
                                            QDBusConnection::systemBus());

    QDBusReply<QMap<QString, QVariant> > reply = iproperty->call("GetAll", "org.freedesktop.Accounts.User");
    if (reply.isValid()) {
        QMap<QString, QVariant> propertyMap;
        propertyMap = reply.value();
        user.username = propertyMap.find("UserName").value().toString();
        qDebug() << "当前的dbus获取到的用户名" << user.username << "使用glib库获取到用户名" << QString(g_get_user_name());
        if (user.username == QString(g_get_user_name())) {
            user.current = true;
            user.logined = true;
        }
        user.accounttype = propertyMap.find("AccountType").value().toInt();
        user.iconfile = propertyMap.find("IconFile").value().toString();
        user.passwdtype = propertyMap.find("PasswordMode").value().toInt();
        user.uid = propertyMap.find("Uid").value().toInt();
        user.autologin = false;
        user.objpath = objpath;
        qDebug() << "当前的icon路径" << user.iconfile;
        delete iproperty;
        return user;
    } else
        qDebug() << "reply failed";
//    return nullptr;
}

void AccountInformation::setAllControlsLabelInfo()
{
    QStringList objectpaths = getUserObjectPath();
    UserInfomation user;
    for (QString objectpath : objectpaths){
        user = GetUserInformation(objectpath);
        if(user.current == true && user.logined == true){
            break; 
         }
    }

    m_pNameLabel->setText(user.username);

    if (user.accounttype == 1 ){
        m_pIdentityLabel->setText(QObject::tr("administrators"));
    } else {
        m_pIdentityLabel->setText(QObject::tr("Standard users"));
    }

    char * iconpath = user.iconfile.toLatin1().data();
    if (!g_file_test(iconpath, G_FILE_TEST_EXISTS)){
        user.iconfile = DEFAULTFACE;
    }
    const auto ratio=devicePixelRatioF();
    QPixmap facePixmap(user.iconfile);
    facePixmap = facePixmap.scaled(48*ratio, 48*ratio,  Qt::KeepAspectRatio, Qt::SmoothTransformation);
    facePixmap = PixmapToRound(facePixmap, 48*ratio/2);
    facePixmap.setDevicePixelRatio(qApp->devicePixelRatio());
    m_pHeadPortraitIconLabel->setFixedSize(48, 48);
    m_pHeadPortraitIconLabel->setPixmap(facePixmap);
    m_pShutDownButton->setIcon(QIcon::fromTheme(KYLIN_SHUT_DOWN_ICON_NAME, QIcon(KYLIN_SHUT_DOWN_ICON_PATH)));
    m_pShutDownButton->setIconSize(QSize(24, 24));
}

QPixmap AccountInformation::PixmapToRound(const QPixmap &src, int radius)
{
    if (src.isNull()) {
        return QPixmap();
    }

    QPixmap pixmapa(src);
    QPixmap pixmap(radius*2,radius*2);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QPainterPath path;
    path.addEllipse(0, 0, radius*2, radius*2);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, radius*2, radius*2, pixmapa);
    return pixmap;
}

void AccountInformation::openShutdownWidgetSlots()
{
    QProcess p(0);
    p.startDetached("ukui-session-tools");
    p.waitForStarted();
    return;
}

void AccountInformation::openContorlCenterWidgetSlots()
{
    QProcess p(0);
    p.startDetached("ukui-control-center -u");
    p.waitForStarted();
    return;
}
