
#include "progress.h"

progress::progress(QWidget* parent)
{
    this->setWindowFlags(Qt::SubWindow | Qt::FramelessWindowHint |Qt::WindowStaysOnTopHint );
    this->setStyleSheet("background-color:red;font-size:60px;");
}

void progress::anime(){
    QParallelAnimationGroup *group=new QParallelAnimationGroup;
    QPropertyAnimation *animation1 = new QPropertyAnimation(this,"geometry");
    animation1->setDuration(10000);
    animation1->setStartValue(QRect(472,520,300,8));
    animation1->setEndValue(QRect(472,520,0,8));
    group->addAnimation(animation1);
    animation1->start();
}

progress::~progress(){}
