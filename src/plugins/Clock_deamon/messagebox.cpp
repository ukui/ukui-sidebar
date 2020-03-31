#include "messagebox.h"
#define INTERVAL 0.1
MessageBox::MessageBox(QWidget* parent, double TIME ):
    TOTAL_TIME(TIME),
    QWidget(parent)
{
  msgbox = new QMessageBox(parent);
  msgbox->setGeometry(QRect(200, 150, 400, 300));
  okbtn     = new QPushButton("立即关闭");
  msgbox->addButton(okbtn, QMessageBox::AcceptRole);
  msgbox->setStyleSheet("QPushButton {min-width: 5em; min-height: 2em;}");
  msgbox->setWindowTitle(tr("时间到"));
  okbtn->setFixedSize(180,45);
  timer_countdown = new QTimer(this);
  connect(timer_countdown, SIGNAL(timeout()), this, SLOT(count_time()));
  btnclick();
}

MessageBox::~MessageBox()
{
}

void MessageBox::count_time()
{
  double letf_time = TOTAL_TIME - msgbox_time_;
  if( letf_time <= 0 )
  {
    okbtn->click();
    return;
  }
  else
  {
    QString output;
    output.sprintf("%2.1f秒 后关闭音乐 ", letf_time);
    msgbox->setText(output);
  }
  msgbox_time_ += INTERVAL;
}

void MessageBox::btnclick()
{
  timer_countdown->start(INTERVAL*1000);
  msgbox_time_ = 0.0;
  msgbox->exec();
  if (msgbox->clickedButton() == okbtn)
  {
    timer_countdown->stop();
  }
  else
  {
    timer_countdown->stop();
  }
}
