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

    if (!courtMap->contains(id)) {
        QMessageBox::warning(this, "Not Found", "Court ID not found.");
        return;
    }

    Court &court = (*courtMap)[id];


    if (court.clientId == currentUserId) {
        QMessageBox::information(this, "Already Booked", "You have already booked this court.");
        return;
    }

    if (!court.isBooked) {
        court.isBooked = true;
        court.clientId = currentUserId;
        court.bookingDate = QDate::currentDate();
        court.bookingTime = QTime::currentTime();
        QMessageBox::information(this, "Done", "Court booked successfully.");
    } else {

        if (isCurrentUserVIP) {
            court.waitingListVIP.enqueue(currentUserId);
            QMessageBox::information(this, "Added to Waiting List", "You are added to the VIP waiting list.");
        } else {
            court.waitingListNormal.enqueue(currentUserId);
            QMessageBox::information(this, "Added to Waiting List", "You are added to the regular waiting list.");
        }
    }

    emit courtBooked();
    //  this->close();


}



void BookCourt::on_cancel_clicked()
{
    if (!courtMap)
        return;

    QString idText = ui->ID->text();
    bool ok;
    int id = idText.toInt(&ok);
    if (!ok || !courtMap->contains(id)) {
        QMessageBox::warning(this, "Invalid", "Please enter a valid court ID.");
        return;
    }

    Court &court = (*courtMap)[id];

    if (court.clientId != currentUserId) {
        QMessageBox::warning(this, "Unauthorized", "You can only cancel your own bookings.");
        return;
    }


    QDateTime now = QDateTime::currentDateTime();
    QDateTime courtTime(court.bookingDate, court.bookingTime);
    if (now.secsTo(courtTime) < 3 * 3600) {
        QMessageBox::warning(this, "Too Late", "You can only cancel bookings at least 3 hours before the time.");
        return;
    }


    QString courtId = court.id;

    if (!court.waitingListVIP.isEmpty()) {
        QString nextVIP = court.waitingListVIP.dequeue();
        court.clientId = nextVIP;
        court.isBooked = true;
        QMessageBox::information(this, "Reassigned", "Court assigned to VIP user: " + nextVIP);
    }
    else if (!court.waitingListNormal.isEmpty()) {
        QString nextNormal = court.waitingListNormal.dequeue();
        court.clientId = nextNormal;
        court.isBooked = true;
        QMessageBox::information(this, "Reassigned", "Court assigned to user: " + nextNormal);
    }
    else {
        court.clientId = "";
        court.isBooked = false;
        QMessageBox::information(this, "Canceled", "Booking canceled. Court is now available.");
    }

    emit courtBooked();
    // this->close();

}
