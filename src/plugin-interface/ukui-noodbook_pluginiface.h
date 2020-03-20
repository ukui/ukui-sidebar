#ifndef UKUINOODBOOK_PLUGINIFACE_H
#define UKUINOODBOOK_PLUGINIFACE_H
#include <QWidget>

//定义接口
class nood_bookInterface
{
public:
    virtual ~nood_bookInterface() {}
    virtual void show() =0;

    //返回一个Widget设置到centerwidget中进行显示
    virtual QWidget* centerWidget() = 0;
};

//声明接口
#define NotebookInterface_iid "org.qt-project.Qt.QGenericPluginFactoryInterface_Notebook"
Q_DECLARE_INTERFACE(nood_bookInterface, NotebookInterface_iid)




#endif // UKUINOODBOOK_PLUGINIFACE_H
