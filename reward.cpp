#include "reward.h"
#include "ui_reward.h"

reward::reward(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reward)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::SubWindow | Qt::FramelessWindowHint |Qt::WindowStaysOnTopHint );
}

reward::~reward()
{
    delete ui;
}
