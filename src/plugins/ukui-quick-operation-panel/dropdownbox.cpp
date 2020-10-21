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
#include "dropdownbox.h"

EntryWidget::EntryWidget(QString iconName, QString iconPath, QString entryName, QString key, QWidget *parent) : QWidget(parent)
{
    IconName    = iconName;
    IconPath    = iconPath;
    EntryName   = entryName;
    gsettingKey = key;
    initMemberVariables();
    initLayout();
}

void EntryWidget::initMemberVariables()
{
    m_pPixmapLabel = new QLabel();
    m_pPixmapLabel->setFixedSize(16, 16);
    QPixmap pixmap = QIcon::fromTheme(IconName, QIcon(IconPath)).pixmap(QSize(16, 16));
    m_pPixmapLabel->setPixmap(pixmap);

    m_pTextLabel   = new QLabel();
    m_pTextLabel->setFixedHeight(19);
    m_pTextLabel->setText(EntryName);

    m_pHEntryLayout = new QHBoxLayout();
    m_pHEntryLayout->setContentsMargins(0, 0, 0, 0);
    m_pHEntryLayout->setSpacing(0);

    this->setContentsMargins(0, 0, 0, 0);
}

void EntryWidget::initLayout()
{
    m_pHEntryLayout->addItem(new QSpacerItem(11, 5, QSizePolicy::Fixed));
    m_pHEntryLayout->addWidget(m_pPixmapLabel);
    m_pHEntryLayout->addItem(new QSpacerItem(11, 5, QSizePolicy::Fixed));
    m_pHEntryLayout->addWidget(m_pTextLabel);
    m_pHEntryLayout->addItem(new QSpacerItem(60, 5, QSizePolicy::Expanding));
    this->setLayout(m_pHEntryLayout);
    this->setFixedSize(112, 32);
}

void EntryWidget::leaveEvent(QEvent *event)
{
    status = NORMAL;
    this->update();
    QWidget::leaveEvent(event);
}

void EntryWidget::enterEvent(QEvent *event)
{
    status = HOVER;
    QWidget::enterEvent(event);
}

void EntryWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    switch (status) {
        case NORMAL: {
            QColor color(255, 255, 255);
            p.setBrush(QBrush(color));
            break;
        }
        case HOVER: {
            QColor color(156, 156, 156);
            p.setBrush(QBrush(color));
            this->update();
            break;
        }
    }
    p.setOpacity(1);
    p.setPen(Qt::NoPen);
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.drawRoundedRect(opt.rect, 4, 4);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

void EntryWidget::mousePressEvent(QMouseEvent *event)
{
    emit WidgetClickSignal(gsettingKey);
    status = NORMAL;
    QWidget::mousePressEvent(event);
    return;
}

dropDownBox::dropDownBox(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();

    initGsettingValue();

    initListData();

    initButtonInfoArrayData();

    initListWidgetEntry();

    initLayout();
}

void dropDownBox::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QRect rect = this->rect();
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    p.setBrush(QBrush(QColor("#FFFFFF")));
    p.setOpacity(1);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(rect, 6, 6);
    QWidget::paintEvent(event);
}

/* 初始化成员变量 */
void dropDownBox::initMemberVariables()
{
    m_pListWidget = new QListWidget();
    m_pListWidget->setStyleSheet("QListWidget {background:rgba(19, 19, 20, 0);}");
    m_pListWidget->setFixedSize(112, 64);
    m_pListWidget->setContentsMargins(0, 0, 0, 0);
    m_pListWidget->setFrameShape(QListWidget::NoFrame);

    m_pHboxLayout = new QHBoxLayout();
    m_pHboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pHboxLayout->setSpacing(0);
    this->setContentsMargins(0, 0, 0, 0);
    return;
}

/* 初始化gsetting值 */
void dropDownBox::initGsettingValue()
{
    const QByteArray id(SHORTCUT_BUTTON_GSETTING_PATH);
    if(QGSettings::isSchemaInstalled(id))
        m_pGsettingButtonData = new QGSettings(id);
    if (m_pGsettingButtonData != nullptr)
        connect(m_pGsettingButtonData, &QGSettings::changed, this, &dropDownBox::resetDropDownWidget);
    return;
}

/* 初始化链表数据 */
void dropDownBox::initListData()
{
    m_listIconName << KYLIN_EYE_MODE_SET_NAME << KYLIN_ALARM_NORMAL_NAME_SET \
                   << KYLIN_HOTSPOT_SET_NAME << KYLIN_SCREENSHOT_SET_NAME \
                   << KYLIN_NOTEBOOK_SET_NAME << KYLIN_BLUETOOTH_SET_NAME \
                   << KYLIN_VPN_SET_PATH << KYLIN_NODISTURB_SET_NAME \
                   << KYLIN_PAD_SET_NAME << KYLIN_CALCULATOR_SET_NAME \
                   << KYLIN_SETTING_SET_NAME << KYLIN_POWER_SAVING_SET_NAME \
                   << KYLIN_FEEDBACK_SET_PATH;

    m_listIconPath << KYLIN_EYE_MODE_SET_PATH << KYLIN_AlARM_SET_PATH  \
                   << KYLIN_HOTSPOT_SET_PATH  << KYLIN_SCREENSHOT_SET_PATH  \
                   << KYLIN_NOTEBOOK_SET_PATH << KYLIN_BLUETOOTH_SET_PATH  \
                   << KYLIN_VPN_SET_PATH      << KYLIN_NODISTURB_SET_PATH  \
                   << KYLIN_PC_SET_PATH       << KYLIN_CALCULATOR_SET_PATH  \
                   << KYLIN_SETTING_SET_PATH  << KYLIN_POWER_SAVING_SET_PATH \
                   << KYLIN_FEEDBACK_SET_PATH;

    m_listEntryName << QObject::tr("Eye care mode") << QObject::tr("Alarm") \
                    << QObject::tr("Hotspot") << QObject::tr("Screenshots") \
                    << QObject::tr("NoteBook") << QObject::tr("Bluetooth") \
                    << QObject::tr("VPN") << QObject::tr("No disturbing") \
                    << QObject::tr("Tablet mode") << QObject::tr("Calculator") \
                    << QObject::tr("Setting") << QObject::tr("Energy-saving mode") \
                    << QObject::tr("feedback");
    return;
}

/* 初始化所有按钮信息数据 */
void dropDownBox::initButtonInfoArrayData()
{
    if (m_pGsettingButtonData != nullptr)
        m_listGsettingKey = m_pGsettingButtonData->keys();

    int count = m_listGsettingKey.count();
    for (int i = 0; i < count; i++) {
        m_pButtonInfoArray[i] = new ButtonInfo;
        m_pButtonInfoArray[i]->iconName  = m_listIconName.at(i);
        m_pButtonInfoArray[i]->iconPath  = m_listIconPath.at(i);
        m_pButtonInfoArray[i]->entryName = m_listEntryName.at(i);
        insertButtonData(m_listGsettingKey.at(i), m_pButtonInfoArray[i]);
    }
}

/* 初始化下拉框界面 */
void dropDownBox::initListWidgetEntry()
{
    int count = m_listGsettingKey.count();
    for (int i = 0; i < count; i++) {
        if (!m_pGsettingButtonData->get(m_listGsettingKey.at(i)).toBool()) {
            ButtonInfo* s_ptrButtonInfo = getButtonInfoData(m_listGsettingKey.at(i));
            EntryWidget *p_EntryWidget  = new EntryWidget(s_ptrButtonInfo->iconName, s_ptrButtonInfo->iconPath, \
                                                          s_ptrButtonInfo->entryName, m_listGsettingKey.at(i));
            connect(p_EntryWidget, &EntryWidget::WidgetClickSignal, this, &dropDownBox::modifyButtonGsettingValue);
            QListWidgetItem *pItem      = new QListWidgetItem();
            pItem->setFlags(Qt::NoItemFlags);
            p_EntryWidget->setFixedSize(112, 32);
            pItem->setSizeHint(p_EntryWidget->size());
            m_pListWidget->addItem(pItem);
            m_pListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            m_pListWidget->setItemWidget(pItem, p_EntryWidget);
        }
    }
}

/* 初始化布局 */
void dropDownBox::initLayout()
{
    m_pHboxLayout->addWidget(m_pListWidget);
    this->setFixedSize(120, 64);
//    this->setFixedWidth(120);
//    this->setMaximumHeight(162);
    this->setLayout(m_pHboxLayout);
    return;
}

/* 插入接口和代号往Hash表中 */
void dropDownBox::insertButtonData(QString key, ButtonInfo *value)
{
    if ("" == key || value == nullptr)
        return;

    if (EntryData.contains(key))
        return;

    EntryData.insert(key, value);
    return;
}

/* 获取接口代号 */
ButtonInfo* dropDownBox::getButtonInfoData(QString key)
{
    if ("" == key) {
        qDebug() << "获取接口代号失败， 传入参数有误";
        return nullptr;
    }
    if (EntryData.contains(key)) {
        return EntryData.value(key);
    } else
        return nullptr;
}

/* 当getting值发生变化时，将会重新布局添加界面 */
void dropDownBox::resetDropDownWidget()
{
    int tmp   = m_pListWidget->count() + 1;
    qDebug() << "当前链表中条目个数" << tmp;
    for (int i = 0; i < tmp; i++) {
        QListWidgetItem *item =  m_pListWidget->takeItem(i); //删除Item;
        delete item;
    }
    m_pListWidget->clear();
    initListWidgetEntry();
}

/* 收到信号时， 设置gsetting值 */
void dropDownBox::modifyButtonGsettingValue(QString key)
{
    if (m_pGsettingButtonData != nullptr && m_pGsettingButtonData->keys().contains(key)) {
        m_pGsettingButtonData->set(key, true);
    }
    return;
}
