#include "gettraining.h"
#include "ui_gettraining.h"

GetTraining::GetTraining(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GetTraining)
{
    ui->setupUi(this);
}

GetTraining::~GetTraining()
{
    delete ui;
}
