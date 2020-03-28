#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
class MessageBox : public QWidget
{
  Q_OBJECT

public:
  MessageBox(QWidget* parent = 0 , double TOTAL_TIME = 0 );
  ~MessageBox();
  QTimer*      timer_countdown;
  double       TOTAL_TIME = 10.0;

private:
  QPushButton* btn;
  QMessageBox* msgbox;
  QPushButton* okbtn;
  double       msgbox_time_;
public slots:
  void count_time();
  void btnclick();
};
#endif // WIDGET_H
