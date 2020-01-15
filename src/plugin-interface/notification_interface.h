#ifndef NOTIFICATION_INTERFACE_H
#define NOTIFICATION_INTERFACE_H

#include <QWidget>

//定义接口
class NotificationInterface
{
public:
    virtual ~NotificationInterface() {}
//    virtual void set_text() = 0;
//    virtual QPushButton* create_pushbutton(QString &button_name) = 0;
//    virtual QTextEdit* create_lineedit() = 0;

    //返回一个Widget设置到centerwidget中进行显示
    virtual QWidget* centerWidget() = 0;
//    virtual void Notify(QString strAppName, QString strIconPath, QString strSummary, QString strTime, QString strBody) = 0;
};

//声明接口
#define NotificationInterface_iid "org.qt-project.Qt.QGenericPluginFactoryInterface"
Q_DECLARE_INTERFACE(NotificationInterface, NotificationInterface_iid)

#endif // NOTIFICATION_INTERFACE_H
