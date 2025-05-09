#include "addtraining.h"
#include "ui_addtraining.h"

addTraining::addTraining(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addTraining)
{
    ui->setupUi(this);
}

addTraining::~addTraining()
{
    delete ui;
}
