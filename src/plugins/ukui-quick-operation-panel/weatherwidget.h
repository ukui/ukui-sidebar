#ifndef WEATHERWIDGET_H
#define WEATHERWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QFont>
#include <QIcon>

class weatherWidget : public QWidget
{
    Q_OBJECT
public:
    explicit weatherWidget(QWidget *parent = nullptr);
    void initMemberVariables();
    void initLabelData();
    void initLayout();

private:
    QLabel  *m_pWeatherIconLabel;
    QLabel  *m_pAreaLabel;
    QLabel  *m_pWeatherNumLabel;
    QHBoxLayout *m_pMainHLayout;

Q_SIGNALS:

};

#endif // WEATHERWIDGET_H
