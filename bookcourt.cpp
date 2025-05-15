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

void BookCourt::setCurrentUserId(const QString &userId)
{
    currentUserId = userId;
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
         qDebug() << "Before booking1: currentUserId=" << currentUserId;
        court.clientId = currentUserId;
        court.bookingDate = QDate::currentDate();
        court.bookingTime = QTime::currentTime();
        QMessageBox::information(this, "Done", "Court booked successfully.");
    } else {
        if (currentUserId.isEmpty()) {
            QMessageBox::warning(this, "Error", "User ID is missing.");
            return;
        }
        if (court.waitingListVIP.contains(currentUserId) || court.waitingListNormal.contains(currentUserId)) {
            QMessageBox::information(this, "Already in Waiting List", "You are already in the waiting list.");
            return;
        }
        if (isCurrentUserVIP) {
            court.waitingListVIP.push_back(currentUserId);
            QMessageBox::information(this, "Added to Waiting List", "You are added to the VIP waiting list.");
        } else {
            court.waitingListNormal.push_back(currentUserId);
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
    QDateTime courtTime(court.date, court.time);

    if (!courtTime.isValid()) {
        QMessageBox::warning(this, "Invalid Booking Time", "Booking date/time is invalid.");
        return;
    }

    qint64 secondsToCourt = now.secsTo(courtTime);


    if (secondsToCourt <= 0 || secondsToCourt < 3 * 3600) {
        QMessageBox::warning(this, "Too Late", "You can only cancel bookings at least 3 hours before the time.");
        return;
    }



    QString courtId = court.id;

    while (!court.waitingListVIP.isEmpty() && court.waitingListVIP.front().isEmpty()) {
        court.waitingListVIP.pop_front();
    }
    while (!court.waitingListNormal.isEmpty() && court.waitingListNormal.front().isEmpty()) {
        court.waitingListNormal.pop_front();
    }


    if (!court.waitingListVIP.isEmpty()) {
        QString nextVIP = court.waitingListVIP.dequeue();
        qDebug() << "VIP assigned: " << nextVIP;
        court.clientId = nextVIP;
        court.isBooked = true;
        QMessageBox::information(this, "Reassigned", "Court assigned to VIP user: " + nextVIP);
    }
    else if (!court.waitingListNormal.isEmpty()) {
        QString nextNormal = court.waitingListNormal.dequeue();
        qDebug() << "Normal assigned: " << nextNormal;
        court.clientId = nextNormal;
        court.isBooked = true;
        QMessageBox::information(this, "Reassigned", "Court assigned to user: " + nextNormal);
    }
    else {
        court.clientId = "";
        court.isBooked = false;
        QMessageBox::information(this, "Canceled", "Booking canceled. Court is now available.");
        qDebug() << "No one in waiting list. clientId cleared.";
    }

       qDebug() << "After cancel: clientId=" << court.clientId;
    emit courtBooked();
    // this->close();

}
