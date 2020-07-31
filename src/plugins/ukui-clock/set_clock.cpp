#include "set_clock.h"
#include "ui_set_clock.h"

set_clock::set_clock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::set_clock)
{
    ui->setupUi(this);
}

set_clock::~set_clock()
{
    delete ui;
}
