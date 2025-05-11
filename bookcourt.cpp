 #include "bookcourt.h"
#include <QMessageBox>
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

void BookCourt::setCourtMap(QMap<int, Court> &map)
{
    courtMap = &map;
}

void BookCourt::on_Book_clicked()
{
    if (!courtMap)
        return;

    QString idText = ui->ID->text();
    bool ok;
    int id = idText.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Invalid", "Please enter a valid ID.");
        return;
    }

    if (courtMap->contains(id)) {
        if ((*courtMap)[id].isBooked) {
            QMessageBox::warning(this, "Already Booked", "This court is already booked.");
            return;
        }

        (*courtMap)[id].isBooked = true;
        (*courtMap)[id].clientId = currentUserId;
        emit courtBooked();
        QMessageBox::information(this, "Done", "Court booked!");
        this->close();
    } else {
        QMessageBox::warning(this, "Not Found", "Court ID not found.");
    }
}
