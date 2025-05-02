#include "bookcourt.h"
#include "ui_bookcourt.h"

BookCourt::BookCourt(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BookCourt)
{
    ui->setupUi(this);
}

BookCourt::~BookCourt()
{
    delete ui;
}
