#include "set_alarm_repeat_dialog.h"
#include <QLabel>
#include <QPushButton>
#include <QApplication>
set_alarm_repeat_Dialog::set_alarm_repeat_Dialog(QWidget *parent , int rowNum ) :
    rowNum_all(rowNum),
    QWidget(parent)
{
    setupUi(this);

    for (int i = 0; i < rowNum_all; i++) {
        set_aItem(i);
    }
}

set_alarm_repeat_Dialog::~set_alarm_repeat_Dialog()
{
   delete this;
}

void set_alarm_repeat_Dialog::set_aItem(int rowNum)
{
    aItem[rowNum] =new QListWidgetItem;
    aItem[rowNum]->setSizeHint(QSize(276, 32));
    aItem[rowNum]->setTextColor(QColor(255, 0, 0, 255));
    listWidget->addItem(aItem[rowNum]);
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    widget[rowNum] = new set_alarm_repeat_widget(listWidget);
    listWidget->setItemWidget(aItem[rowNum],widget[rowNum]);
}

void set_alarm_repeat_Dialog::setupUi(QWidget( *set_alarm_repeat_Dialog))
{
    if (set_alarm_repeat_Dialog->objectName().isEmpty())
        set_alarm_repeat_Dialog->setObjectName(QString::fromUtf8("set_alarm_repeat_Dialog"));
    set_alarm_repeat_Dialog->resize(280, 162);
    listWidget = new QListWidget(set_alarm_repeat_Dialog);
    listWidget->setObjectName(QString::fromUtf8("listWidget"));
    listWidget->setGeometry(QRect(0, 0, 280, 162));
    listWidget->setStyleSheet("selection-background-color: rgba(39,207,129,0.9);");

    retranslateUi(set_alarm_repeat_Dialog);

    QMetaObject::connectSlotsByName(set_alarm_repeat_Dialog);
} // setupUi

void set_alarm_repeat_Dialog::retranslateUi(QWidget( *set_alarm_repeat_Dialog))
{
    set_alarm_repeat_Dialog->setWindowTitle(QApplication::translate("set_alarm_repeat_Dialog", "Dialog", nullptr));
} // retranslateUi




set_alarm_repeat_widget::set_alarm_repeat_widget(QWidget *parent):
    QWidget(parent)
{
    this->setStyleSheet("border-radius:12px;");
    this->setFixedSize(276, 32);

    alarmLabel0 = new QLabel(this);
    alarmLabel0->move(5, 9);
    alarmLabel0->setFixedSize(100, 17);
    alarmLabel0->setStyleSheet("font: 11pt 'Sans Serif';background-color: rgb();");
    alarmLabel0->setText("选项");

    alarmLabel1 = new QPushButton(this);
    alarmLabel1->move(240, 9);
    alarmLabel1->setFixedSize(34, 17);
    alarmLabel1->setStyleSheet("font: 11pt 'Sans Serif';background-color: rgb();");
    alarmLabel1->setText("");
}

set_alarm_repeat_widget::~set_alarm_repeat_widget()
{
    delete this;
}




