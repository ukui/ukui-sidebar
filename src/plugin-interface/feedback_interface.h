#ifndef FEEDBACK_INTERFACE_H
#define FEEDBACK_INTERFACE_H

#include <QWidget>

//定义接口
class FeedbackInterface
{
public:
    virtual ~FeedbackInterface() {}
    virtual void show() =0;

    //返回一个Widget设置到centerwidget中进行显示
    virtual QWidget* centerWidget() = 0;
};

//声明接口
#define feedbackInterface_iid "org.qt-project.Qt.QGenericPluginFactoryInterface_feedback"
Q_DECLARE_INTERFACE(FeedbackInterface, feedbackInterface_iid)



#endif // FEEDBACK_INTERFACE_H
