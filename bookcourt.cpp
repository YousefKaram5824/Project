#include "bookcourt.h"
#include "ui_bookcourt.h"
#include <QMessageBox>
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

void BookCourt::setCourtMap(QMap<int, Court> &map)
{
    courtMap = &map;
}
/*
void BookCourt::bookSelectedCourt(QMap<int, Court> &courtMap)
{
    QString idText = ui->ID->text();
    bool ok;
    int id = idText.toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Invalid ID", "Please enter a valid numeric ID.");
        return;
    }


    if (courtMap.contains(id)) {

        Court &court = courtMap[id];
        court.isBooked = true;

        QMessageBox::information(this, "Success", "Court booked successfully.");
    } else {
        QMessageBox::warning(this, "Not Found", "Court ID not found.");
    }

}
 */
void BookCourt::on_Book_clicked()
{
    if (!courtMap) return;

    QString idText = ui->ID->text();
    bool ok;
    int id = idText.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Invalid", "Please enter a valid ID.");
        return;
    }

    if (courtMap->contains(id)) {
        (*courtMap)[id].isBooked = true;
        QMessageBox::information(this, "Done", "Court booked!");
        this->close();
    } else {
        QMessageBox::warning(this, "Not Found", "Court ID not found.");
    }
    if (courtMap->contains(id)) {
        (*courtMap)[id].isBooked = true;
        emit courtBooked();
        QMessageBox::information(this, "Done", "Court booked!");
        this->close();
    }
}

