#include "card0.h"
#include "ui_card0.h"

Card0::Card0(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Card0)
{
    ui->setupUi(this);
}

Card0::~Card0()
{
    delete ui;
}
